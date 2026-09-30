#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#define N 100000
#define LIMIT 20000
#define TRAP -1
static inline uint64_t mix(uint64_t z){z+=0x9e3779b97f4a7c15ULL;z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;z=(z^(z>>27))*0x94d049bb133111ebULL;return z^(z>>31);}
static int memo[N+1];
/* seed 0 = real shortcut map; seed>0 = frozen random coin per integer */
static inline uint64_t step(uint64_t x, uint64_t seed){
  int up = seed ? (int)(mix(seed*0x100000001B3ULL ^ x) & 1) : (int)(x & 1);
  return up ? (3*x+1)/2 : x/2;
}
int main(int argc,char**argv){
  int seeds=atoi(argv[1]);
  for(uint64_t s=0;s<=(uint64_t)seeds;s++){
    memo[1]=0; long trapped=0; double m1=0,m2=0,m3=0; long cnt=0;
    for(uint64_t n=2;n<=N;n++){
      uint64_t x=n; int st=0, res;
      while(1){
        if(x==1){res=st;break;}
        if(x<n){ res = memo[x]==TRAP ? TRAP : st+memo[x]; break;}
        if(st>LIMIT){res=TRAP;break;}
        x=step(x,s); st++;
      }
      memo[n]=res;
      if(res==TRAP) trapped++; else {double v=res; m1+=v; m2+=v*v; m3+=v*v*v; cnt++;}
    }
    double mu=m1/cnt, var=m2/cnt-mu*mu, sk=(m3/cnt-3*mu*m2/cnt+2*mu*mu*mu)/pow(var,1.5);
    printf("%lu %.6f %.2f %.2f %.4f\n", (unsigned long)s, (double)trapped/(N-1), mu, sqrt(var), sk);
  }
  return 0;
}
