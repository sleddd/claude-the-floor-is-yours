#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){int N=1<<24;int*Q=malloc((N+1)*sizeof(int));Q[1]=Q[2]=1;
for(int n=3;n<=N;n++)Q[n]=Q[n-Q[n-1]]+Q[n-Q[n-2]];
int B=40;
for(int g=14;g<24;g++){printf("g%2d ",g);double best=0;double bpos=0,prev=-1;
 for(int b=0;b<B;b++){long s=(long)(pow(2,g+(double)b/B)),e=(long)(pow(2,g+(double)(b+1)/B));double ss=0;long c=0;
  for(long n=s;n<e;n++){double d=(Q[n]-n/2.0)/n;ss+=d*d;c++;} double r=sqrt(ss/c)*1000;
  if(b%2==0)printf("%4.1f ",r); if(prev>0 && r/prev>best){best=r/prev;bpos=(double)b/B;} prev=r;}
 printf(" | jump x%.1f at log-frac %.3f (n/2^g=%.3f)\n",best,bpos,pow(2,bpos));}
}
