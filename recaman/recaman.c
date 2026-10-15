/* Recaman: a(0)=0; a(n)=a(n-1)-n if that is >0 and unseen, else a(n-1)+n.
   usage: recaman N  (bitset of seen values, cap 1e9)
   Prints the figures graded in ledger.md (Oct 14 2026) and the raw window
   n=9960130..9960200 when N reaches it. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define CAP 1000000000ULL
static uint64_t *bits;
static inline int seen(uint64_t v){ return v<CAP ? (bits[v>>6]>>(v&63))&1 : 1; }
static inline void mark(uint64_t v){ if(v>=CAP){fprintf(stderr,"cap\n");exit(1);} bits[v>>6]|=1ULL<<(v&63); }
static uint64_t smallest_missing(uint64_t from){ uint64_t v=from; while(seen(v)) v++; return v; }
int main(int argc,char**argv){
  uint64_t N=strtoull(argv[1],0,10);
  bits=calloc(CAP/64+1,8);
  long first_at[1000]; for(int i=0;i<1000;i++) first_at[i]=-1;
  uint64_t a=0; mark(0); first_at[0]=0;
  long rep_v=-1, rep_n=-1, subs=0, adds=0, aa=0, ss=0, bottom=0, n19=-1;
  uint64_t maxa=0, maxa_n=0; double maxr=0; uint64_t maxr_n=0; int prev=-1;
  uint64_t sm=1;
  for(uint64_t n=1;n<=N;n++){
    int sub = (a>n) && !seen(a-n);       /* a-n > 0 */
    uint64_t b = sub ? a-n : a+n;
    if(sub){subs++; if(prev==1) ss++;} else {adds++; if(prev==0) aa++;}
    prev=sub;
    if(rep_v<0 && seen(b)){rep_v=b; rep_n=n;}
    mark(b); a=b;
    if(b<1000 && first_at[b]<0) first_at[b]=n;
    if(b==19 && n19<0) n19=n;
    if(b>maxa){maxa=b; maxa_n=n;}
    if(n>100 && (double)b/n>maxr){maxr=(double)b/n; maxr_n=n;}
    if(n>=2 && b<n) bottom++;
    if(n>=9960130 && n<=9960200) printf("raw n=%lu a=%lu %c\n",(unsigned long)n,(unsigned long)b,sub?'-':'+');
    if(n%5000000==0){ sm=smallest_missing(sm); printf("checkpoint n=%lu smallest_missing %lu 852655_seen %d\n",(unsigned long)n,(unsigned long)sm,seen(852655)); }
  }
  sm=smallest_missing(sm);
  long miss=0; for(uint64_t v=1;v<852655;v++) if(!seen(v)) miss++;
  int late_v=-1; long late_n=-1; for(int v=0;v<1000;v++) if(first_at[v]>late_n){late_n=first_at[v]; late_v=v;}
  printf("N=%lu\n",(unsigned long)N);
  printf("first repeat %ld at n=%ld\n",rep_v,rep_n);
  printf("19 first at n=%ld\n",n19);
  printf("smallest missing %lu\n",(unsigned long)sm);
  printf("max a(n) %lu at n=%lu\n",(unsigned long)maxa,(unsigned long)maxa_n);
  printf("subtraction fraction %.5f (subs %ld adds %ld) adds-subs %ld\n",(double)subs/N,subs,adds,adds-subs);
  printf("add-add pairs %ld sub-sub pairs %ld\n",aa,ss);
  printf("final a(N) %lu\n",(unsigned long)a);
  printf("missing values below 852655: %ld; 852655 seen %d\n",miss,seen(852655));
  printf("latest-arriving value under 1000: %d at n=%ld (unseen under 1000 count as -1)\n",late_v,late_n);
  printf("steps with a(n)<n, n>=2: %ld\n",bottom);
  printf("max a(n)/n for n>100: %.3f at n=%lu\n",maxr,(unsigned long)maxr_n);
  return 0;
}
