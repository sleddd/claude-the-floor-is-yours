#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static inline int tones(unsigned long long n){ return __builtin_ctzll(n+1ULL); }

/* Count visits to small odd values across all trajectories from odd n <= N,
   and count the specific fresh->fresh pair (prev=6, next=4) by which number
   produced it. */
#define SMALL 4000000
int main(int argc,char**argv){
    unsigned long long N=(argc>1)?strtoull(argv[1],0,10):1000000ULL;
    long long *visits = calloc(SMALL, sizeof(long long));
    /* which number is the prev=6 in a (6->4) fresh pair */
    long long *six_to_four = calloc(SMALL, sizeof(long long));
    long long *six_any = calloc(SMALL, sizeof(long long));
    for(unsigned long long n0=1;n0<=N;n0+=2){
        unsigned long long x=n0; int prev_t=0; int last_fresh=-1;
        unsigned long long last_fresh_val=0;
        while(x!=1ULL){
            int t=tones(x);
            if(x<SMALL) visits[x]++;
            int is_fresh=(prev_t<=1);
            if(is_fresh){
                if(last_fresh==6 && last_fresh_val<SMALL){
                    six_any[last_fresh_val]++;
                    if(t==4) six_to_four[last_fresh_val]++;
                }
                last_fresh=t; last_fresh_val=x;
            }
            prev_t=t;
            x=3ULL*x+1ULL; x>>=__builtin_ctzll(x);
        }
    }
    /* top visited */
    printf("top 15 most-visited odd values (N=%llu)\n",N);
    for(int r=0;r<15;r++){
        long long best=-1; int bi=0;
        for(int i=1;i<SMALL;i+=2) if(visits[i]>best){best=visits[i];bi=i;}
        printf("  %8d  visits=%12lld  t=%d\n",bi,best,tones(bi));
        visits[bi]=-1;
    }
    printf("\ntop fresh values with t=6 feeding the (6->4) pair\n");
    for(int r=0;r<8;r++){
        long long best=-1; int bi=0;
        for(int i=1;i<SMALL;i+=2) if(six_any[i]>best){best=six_any[i];bi=i;}
        if(best<=0) break;
        printf("  prev=%8d  times_as_prev=%10lld  of which next had t=4: %10lld (%.3f)\n",
               bi,best,six_to_four[bi], best? (double)six_to_four[bi]/best:0.0);
        six_any[bi]=-1;
    }
    return 0;
}
