/* Van Eck checks for the Oct 15 2026 run: P1-P3 and the values in item 3, to N=1e7.
   a(1)=0; a(n+1) = n - m, m < n the last index with a(m) = a(n), else 0. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define N 10000000L
int main(){
  int32_t *a=malloc(sizeof(int32_t)*(N+2)), *last=malloc(sizeof(int32_t)*(N+2));
  for(long i=0;i<=N+1;i++) last[i]=-1;
  a[1]=0;
  for(long n=1;n<N;n++){ long v=a[n]; a[n+1]= last[v]<0 ? 0 : n-last[v]; last[v]=n; }
  printf("first 20:"); for(int i=1;i<=20;i++) printf(" %d",a[i]); printf("\n");
  long p2bad=0; for(long n=1;n<N;n++) if(a[n+1]>n-1) p2bad++;
  printf("P2 violations (a(n+1) > n-1), n < 1e7: %ld\n",p2bad);
  char *seen=calloc(N+2,1); long Z=0, D=0, Dprev=0;
  for(long n=1;n<=N;n++){ if(a[n]==0) Z++; if(n==N) Dprev=D; if(!seen[a[n]]){seen[a[n]]=1;D++;} }
  printf("Z(1e7)=%ld  distinct in first 1e7 = %ld  distinct in first 1e7-1 = %ld\n",Z,D,Dprev);
  double sum=0; long mx=0; for(long n=1;n<=N;n++){ sum+=a[n]; if(a[n]>mx) mx=a[n]; }
  printf("mean a(n), n<=1e7 = %.1f  max a(n) = %ld\n",sum/N,mx);
  double best=0; long bn=0, low=0, cnt=0, dec[10]={0};
  for(long n=1000000;n<=N;n++){ double r=(double)a[n]/n; if(r>best){best=r;bn=n;}
    if(r<0.01) low++;
    int d=(int)(r*10); if(d>9) d=9;
    dec[d]++; cnt++; }
  printf("n in [1e6,1e7]: max a(n)/n = %.6f at n=%ld; share a(n)/n < 0.01 = %.4f\ndeciles:",best,bn,(double)low/cnt);
  for(int d=0;d<10;d++) printf(" %.4f",(double)dec[d]/cnt);
  printf("\n");
  return 0;
}
