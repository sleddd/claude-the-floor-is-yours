/* road.c: biggest shared road for the map x odd -> 3x+k, x even -> x/2.
   Starts: 1 <= n <= N, n not a multiple of k (k > 1). Each start's basin is the cycle
   it ends in. For each basin holding >= 5% of all n <= N (multiples of k counted in the
   denominator, as chat's figures do), the road is the value v > cutoff,
   not a cycle element, passed by the most of that basin's starts (the start itself
   counts); share = those starts / basin starts. Counts are kept for v <= L; the run
   checks that no value above L could beat the best (starts ever exceeding L).
   Usage: road k cutoff [N] [L]      gcc -O2 -o road road.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
static u64 K;
static inline u64 f(u64 x){ return (x&1) ? 3*x+K : x>>1; }
#define MAXC 64
static u64 cyc[MAXC][4096]; static int clen[MAXC], nc;
static int cyc_of(u64 x){ for(int c=0;c<nc;c++) for(int i=0;i<clen[c];i++) if(cyc[c][i]==x) return c; return -1; }
static int find_cycle(u64 s){           /* Brent; returns cycle id, adding it if new */
  u64 pw=1,lam=1,t=s,h=f(s);
  while(t!=h){ if(pw==lam){t=h;pw<<=1;lam=0;} h=f(h); lam++; if(pw>(1ULL<<30)){fprintf(stderr,"no cycle from %llu\n",(unsigned long long)s);exit(1);} }
  int c=cyc_of(h); if(c>=0) return c;
  if(nc==MAXC||lam>4096){fprintf(stderr,"cycle table full\n");exit(1);}
  c=nc++; clen[c]=0; u64 x=h; do{ cyc[c][clen[c]++]=x; x=f(x);}while(x!=h); return c;
}
static u64 cmax(int c){ u64 m=cyc[c][0]; for(int i=1;i<clen[c];i++) if(cyc[c][i]>m) m=cyc[c][i]; return m; }
static u64 cmin(int c){ u64 m=cyc[c][0]; for(int i=1;i<clen[c];i++) if(cyc[c][i]<m) m=cyc[c][i]; return m; }
int main(int argc,char**argv){
  K=strtoull(argv[1],0,10); u64 cut=strtoull(argv[2],0,10);
  u64 N=argc>3?strtoull(argv[3],0,10):1000000, L=argc>4?strtoull(argv[4],0,10):50000000;
  /* basin label for every x <= N (multiples of k too, so walks can stop early) */
  signed char *lab=malloc(N+1); lab[0]=-1;
  for(u64 n=1;n<=N;n++){ u64 x=n; int b=-1; long s=0;
    while(1){ x=f(x); s++; if(x<n){ b=lab[x]; break; } if(x==n||s>100000){ b=find_cycle(n); break; } }
    lab[n]=b; }
  uint32_t *cnt=calloc(L+1,4); u64 *bs=calloc(MAXC,8), *over=calloc(MAXC,8), tot=0;
  for(u64 n=1;n<=N;n++){ if(K>1 && n%K==0) continue; int b=lab[n]; bs[b]++; tot++;
    u64 x=n, cm=cmax(b); int above=0;
    for(;;){ /* stop at the cycle: a value <= max cycle elt that is in the cycle */
      if(x<=cm && cyc_of(x)==b) break;
      if(x>cut){ if(x<=L) cnt[x]++; else above=1; }
      x=f(x); }
    over[b]+=above; }
  printf("k=%llu cutoff=%llu N=%llu starts=%llu cycles=%d\n",(unsigned long long)K,(unsigned long long)cut,(unsigned long long)N,(unsigned long long)tot,nc);
  u64 topv=0,topb=0; double tops=0;
  for(int b=0;b<nc;b++){ if(!bs[b]) continue; double sh=(double)bs[b]/N;
    u64 bv=0; uint32_t best=0;
    for(u64 v=cut+1;v<=L;v++) if(cnt[v]>best){ /* v in basin b? */
      u64 y=v; int c;
      if(v<=N){ c=lab[v]; } else { /* walk down to a labelled value */
        while(y>N) y=f(y);
        c=lab[y]; }
      if(c==b && cyc_of(v)<0){ best=cnt[v]; bv=v; } }
    if(sh>=0.05 && (double)best/bs[b]>tops){ tops=(double)best/bs[b]; topv=bv; topb=b; }
    printf("  basin min %llu len %d: starts %llu (%.1f%% of n<=N)  road %llu share %.4f  exact=%s%s\n",
      (unsigned long long)cmin(b),clen[b],(unsigned long long)bs[b],100*sh,(unsigned long long)bv,(double)best/bs[b],
      over[b]<best?"yes":"NO",sh>=0.05?"":"  (basin < 5%)"); }
  printf("TOP k=%llu cutoff=%llu share %.4f at %llu (basin min %llu, %.1f%%)\n",(unsigned long long)K,(unsigned long long)cut,tops,(unsigned long long)topv,(unsigned long long)cmin(topb),100.0*bs[topb]/N);
  return 0;
}
