/* foot seed(0=real) N [flip values...]
   Same map as ridge/road.c. Prints: seed trapped road share foot fmin lowfrac
   foot = smallest start passing the road; fmin = smallest start whose path tops 1000;
   lowfrac = share of road members whose path visits a value <= 100 before the road.
   Flip values have their up/down step reversed (surgery). */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
typedef uint64_t u64;
static u64 SEED; static int REAL; static u64 FLIP[16]; static int NF=0;
static inline u64 mix(u64 z){z+=0x9e3779b97f4a7c15ULL;z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;z=(z^(z>>27))*0x94d049bb133111ebULL;return z^(z>>31);}
static inline u64 f(u64 n){
  int up = REAL ? (int)(n&1) : (int)(mix(n*0x632be59bd9b4e019ULL ^ SEED)&1);
  for(int i=0;i<NF;i++) if(n==FLIP[i]) up=!up;
  return up ? (3*n+1)/2 : n/2;
}
#define CAP 20000
#define V 2000000
int main(int argc,char**argv){
  u64 seed=strtoull(argv[1],0,10), N=strtoull(argv[2],0,10);
  for(int i=3;i<argc;i++) FLIP[NF++]=strtoull(argv[i],0,10);
  REAL=(seed==0); SEED=mix(seed);
  unsigned char *st=calloc(N+1,1); st[1]=1;
  u64 trapped=0;
  for(u64 n=2;n<=N;n++){ u64 x=n; int s=0,res;
    for(;;){ x=f(x); s++; if(x<n){res=st[x];break;} if(x==n||s>CAP){res=2;break;} }
    st[n]=res; if(res==2) trapped++; }
  uint32_t *cnt=calloc(V+1,4); u64 fmin=0;
  for(u64 n=1;n<=N;n++){ if(st[n]!=1) continue; u64 x=n; int top=(x>1000);
    if(x>1000&&x<=V) cnt[x]++;
    while(x!=1){ x=f(x); if(x>1000){ top=1; if(x<=V) cnt[x]++; } }
    if(top&&!fmin) fmin=n; }
  u64 r=0; uint32_t best=0; for(u64 v=1001;v<=V;v++) if(cnt[v]>best){best=cnt[v];r=v;}
  u64 foot=0, low=0;
  for(u64 n=1;n<=N;n++){ if(st[n]!=1) continue; u64 x=n; int lo=(x<=100), hit=(x==r);
    while(!hit && x!=1){ x=f(x); if(x==r) hit=1; else if(x<=100) lo=1; }
    if(hit){ if(!foot) foot=n; if(lo) low++; } }
  printf("%llu %llu %llu %.4f %llu %llu %.3f\n",(unsigned long long)seed,(unsigned long long)trapped,
    (unsigned long long)r,(double)best/N,(unsigned long long)foot,(unsigned long long)fmin,best?(double)low/best:0);
  return 0;
}
