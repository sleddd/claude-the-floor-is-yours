#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(){int N=1<<24;int*Q=malloc((N+1)*sizeof(int));Q[1]=Q[2]=1;
for(int n=3;n<=N;n++)Q[n]=Q[n-Q[n-1]]+Q[n-Q[n-2]];
int B=20;
for(int g=5;g<24;g++){int lo=1<<g,hi=1<<(g+1);double prof[20];double tot=0;
 for(int b=0;b<B;b++){int s=lo+(long)(hi-lo)*b/B,e=lo+(long)(hi-lo)*(b+1)/B;double ss=0;int c=0;
  for(int n=s;n<e;n++){double d=Q[n]-n/2.0;ss+=d*d;c++;} prof[b]=sqrt(ss/c)/(lo*1.5);tot+=prof[b];}
 printf("g%2d ",g);for(int b=0;b<B;b++)printf("%4.2f ",prof[b]/(tot/B));printf("\n");}
}
