#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
static u64 SEED; static int REAL;
static inline u64 mix(u64 z){z+=0x9e3779b97f4a7c15ULL;z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;z=(z^(z>>27))*0x94d049bb133111ebULL;return z^(z>>31);}
static inline u64 f(u64 n){
  int up = REAL ? (int)(n&1) : (int)(mix(n*0x632be59bd9b4e019ULL ^ SEED)&1);
  return up ? (3*n+1)/2 : n/2;
}
#define CAP 20000
static unsigned char *st, *ps;   /* st: 1 reaches 1, 2 trapped; ps: passes road */
static void memo(u64 N, u64 r){
  st[1]=1; ps[1]=(r==1);
  for(u64 n=2;n<=N;n++){
    u64 x=n; int hit=(n==r), s=0, res=0;
    for(;;){ x=f(x); s++; if(x==r) hit=1;
      if(x<n){ res=st[x]; hit|=ps[x]; break; }
      if(x==n||s>CAP){ res=2; break; } }
    st[n]=res; ps[n]=hit; }
}
int main(int argc,char**argv){   /* road seed(0=real) Nsel Nmax */
  u64 seed=strtoull(argv[1],0,10), Nsel=strtoull(argv[2],0,10), Nmax=strtoull(argv[3],0,10);
  REAL=(seed==0); SEED=mix(seed); u64 V=2000000;
  st=malloc(Nmax+1); ps=malloc(Nmax+1); memo(Nsel,0);
  u64 trapped=0; for(u64 n=1;n<=Nsel;n++) if(st[n]==2) trapped++;
  uint32_t *cnt=calloc(V+1,4);
  for(u64 n=1;n<=Nsel;n++){ if(st[n]!=1) continue; u64 x=n;
    if(x>1000&&x<=V) cnt[x]++; while(x!=1){ x=f(x); if(x>1000&&x<=V) cnt[x]++; } }
  u64 r=0; uint32_t best=0; for(u64 v=1001;v<=V;v++) if(cnt[v]>best){best=cnt[v];r=v;}
  memo(Nmax,r);
  printf("%llu road %llu trapped@sel %llu",(unsigned long long)seed,(unsigned long long)r,(unsigned long long)trapped);
  u64 c=0,t=0,next=10000;
  for(u64 n=1;n<=Nmax;n++){ c+=ps[n]; t+=(st[n]==2);
    if(n==next){ printf(" | N=%llu share %.4f trap %.4f",(unsigned long long)n,(double)c/n,(double)t/n); next*=10; } }
  printf("\n"); return 0;
}
