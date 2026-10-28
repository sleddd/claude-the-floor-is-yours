/* Greedy 3-AP-free (Stanley) sequence from two seeds.
   usage: stanley s0 s1 N [MAXV]   (default MAXV 1e9) -> one term per line on stdout
   Bitset of forbidden values: on adding x, mark 2x - a[i] for every earlier a[i]
   with 2x - a[i] < MAXV (a is increasing, so binary search for the first such i). */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static uint64_t *forb;
static inline int isf(uint64_t v){ return (forb[v>>6]>>(v&63))&1; }
static inline void setf(uint64_t v){ forb[v>>6]|=1ULL<<(v&63); }
int main(int argc,char**argv){
  if(argc<4){fprintf(stderr,"usage: stanley s0 s1 N [MAXV]\n");return 1;}
  uint64_t s0=strtoull(argv[1],0,10), s1=strtoull(argv[2],0,10);
  long N=atol(argv[3]);
  uint64_t MAXV = argc>4 ? (uint64_t)atof(argv[4]) : 1000000000ULL;
  forb=calloc(MAXV/64+1,8);
  uint64_t *a=malloc(N*sizeof *a);
  a[0]=s0; a[1]=s1; setf(2*s1-s0);
  printf("%llu\n%llu\n",(unsigned long long)s0,(unsigned long long)s1);
  uint64_t x=s1+1;
  for(long n=2;n<N;n++){
    while(x<MAXV && isf(x)) x++;
    if(x>=MAXV){fprintf(stderr,"MAXV reached at n=%ld\n",n);return 1;}
    /* first i with 2x - a[i] < MAXV, i.e. a[i] > 2x - MAXV */
    long lo=0;
    if(2*x>=MAXV){ uint64_t lim=2*x-MAXV; long hi=n; while(lo<hi){long m=(lo+hi)/2; if(a[m]>lim) hi=m; else lo=m+1;} }
    for(long i=lo;i<n;i++) setf(2*x-a[i]);
    a[n]=x; printf("%llu\n",(unsigned long long)x); x++;
  }
  return 0;
}
