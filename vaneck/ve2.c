#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
int main(){
  long N=100000000;
  int32_t *last=malloc(sizeof(int32_t)*(N+2));
  for(long i=0;i<=N+1;i++) last[i]=-1;
  long cur=0,zeros=0; long next_report=1000;
  long smallest=1;
  for(long n=1;n<=N;n++){
    if(cur==0) zeros++;
    long nxt = last[cur]<0 ? 0 : n-last[cur];
    last[cur]=n; cur=nxt;
    if(n==next_report){
      while(last[smallest]>=0) smallest++;
      double L=log((double)n);
      printf("N=%-10ld Z=%-9ld Z*lnN/N=%.4f  Z*(lnN-1)/N=%.4f  smallest_unseen=%ld\n",n,zeros,zeros*L/n,zeros*(L-1)/n,smallest);
      // step: 1,2,5 per decade
      long d=1; while(d*10<=next_report) d*=10;
      long m=next_report/d;
      next_report = (m==1? 2*d : m==2? 5*d : 10*d);
    }
  }
  return 0;
}
