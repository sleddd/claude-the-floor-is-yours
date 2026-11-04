/* old.c: road under the sealed (pre-fix) measure. Map: n even -> n/2, n odd -> 3n+k.
   Starts: every n <= N, multiples of k included. share(v) = starts whose trajectory
   visits v / N, over 1000 <= v < 10^7, cycle members included (a start reaches every
   element of its cycle). Also prints the best non-cycle v, the best v over starts that
   are not multiples of k (still / N), the cycles reached, and the k*9232-type copy.
   Usage: old k [N]      gcc -O2 -o old old.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
static u64 K;
static inline u64 f(u64 x){ return (x&1) ? 3*x+K : x>>1; }
#define MAXC 64
#define VLO 1000
#define VHI 10000000
static u64 cyc[MAXC][4096]; static int clen[MAXC], nc;
static int cyc_of(u64 x){ for(int c=0;c<nc;c++) for(int i=0;i<clen[c];i++) if(cyc[c][i]==x) return c; return -1; }
static int find_cycle(u64 s){
  u64 pw=1,lam=1,t=s,h=f(s);
  while(t!=h){ if(pw==lam){t=h;pw<<=1;lam=0;} h=f(h); lam++; }
  int c=cyc_of(h); if(c>=0) return c;
  c=nc++; clen[c]=0; u64 x=h; do{ cyc[c][clen[c]++]=x; x=f(x);}while(x!=h); return c;
}
static u64 cmin(int c){ u64 m=cyc[c][0]; for(int i=1;i<clen[c];i++) if(cyc[c][i]<m) m=cyc[c][i]; return m; }
static u64 cmax(int c){ u64 m=cyc[c][0]; for(int i=1;i<clen[c];i++) if(cyc[c][i]>m) m=cyc[c][i]; return m; }
int main(int argc,char**argv){
  K=strtoull(argv[1],0,10); u64 N=argc>2?strtoull(argv[2],0,10):1000000;
  signed char *lab=malloc(N+1);
  for(u64 n=1;n<=N;n++){ u64 x=n; int b; long s=0;
    while(1){ x=f(x); s++; if(x<n){ b=lab[x]; break; } if(x==n||s>100000){ b=find_cycle(n); break; } }
    lab[n]=b; }
  uint32_t *all=calloc(VHI,4), *nm=calloc(VHI,4); u64 bs[MAXC]={0}, bsn[MAXC]={0};
  for(u64 n=1;n<=N;n++){ int b=lab[n], mult=(K>1 && n%K==0); bs[b]++; if(!mult) bsn[b]++;
    u64 x=n, cm=cmax(b);
    while(!(x<=cm && cyc_of(x)==b)){ if(x>=VLO && x<VHI){ all[x]++; if(!mult) nm[x]++; } x=f(x); } }
  for(int b=0;b<nc;b++) for(int i=0;i<clen[b];i++){ u64 v=cyc[b][i]; if(v>=VLO&&v<VHI){ all[v]+=bs[b]; nm[v]+=bsn[b]; } }
  u64 va=0,vc=0,vn=0; uint32_t ba=0,bc=0,bn=0;
  for(u64 v=VLO;v<VHI;v++){ if(all[v]>ba){ba=all[v];va=v;}
    if(nm[v]>bn){bn=nm[v];vn=v;}
    if(all[v]>bc && cyc_of(v)<0){bc=all[v];vc=v;} }
  int reached=0, reachedn=0; for(int b=0;b<nc;b++){ reached+=bs[b]>0; reachedn+=bsn[b]>0; }
  printf("k=%llu SEALED road %.4f at %llu%s | non-cycle best %.4f at %llu | non-multiple starts best %.4f at %llu | cycles reached %d (%d from non-multiples)\n",
    (unsigned long long)K,(double)ba/N,(unsigned long long)va,cyc_of(va)>=0?" (cycle member)":"",
    (double)bc/N,(unsigned long long)vc,(double)bn/N,(unsigned long long)vn,reached,reachedn);
  for(int b=0;b<nc;b++) printf("    cycle min %llu max %llu len %d: %.4f of starts\n",(unsigned long long)cmin(b),(unsigned long long)cmax(b),clen[b],(double)bs[b]/N);
  if(K>1){ /* the scaled 3x+1 copy: best v among multiples of k (only multiples of k visit them) */
    u64 vs=0; uint32_t bsc=0; for(u64 v=VLO;v<VHI;v++) if(v%K==0 && all[v]>bsc){bsc=all[v];vs=v;}
    int rank=1; for(u64 v=VLO;v<VHI;v++) if(all[v]>bsc) rank++;
    printf("    scaled copy: best multiple of k is %llu (= %llu x %llu), share %.4f, rank %d among all v\n",
      (unsigned long long)vs,(unsigned long long)K,(unsigned long long)(vs/K),(double)bsc/N,rank); }
  return 0; }
