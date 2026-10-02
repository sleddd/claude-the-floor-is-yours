#include <stdio.h>
#include <stdlib.h>
#include <math.h>
static inline int tones(unsigned long long n){ return __builtin_ctzll(n+1ULL); }
#define LIM 100000
int main(int argc,char**argv){
    unsigned long long N=(argc>1)?strtoull(argv[1],0,10):1000000ULL;
    long long *v=calloc(LIM,sizeof(long long));
    for(unsigned long long n0=1;n0<=N;n0+=2){
        unsigned long long x=n0;
        while(x!=1ULL){ if(x<LIM) v[x]++; x=3ULL*x+1ULL; x>>=__builtin_ctzll(x); }
    }
    double s1=0,s2=0,ss1=0,ss2=0,s12=0; long long cnt=0;
    double sum[12]; long long num[12];
    for(int i=0;i<12;i++){sum[i]=0;num[i]=0;}
    for(int i=3;i<LIM;i+=2){
        if(v[i]==0) continue;
        int t=tones(i); if(t>11)t=11;
        sum[t]+=v[i]; num[t]++;
        double a=t,b=log((double)v[i]);
        s1+=a;s2+=b;ss1+=a*a;ss2+=b*b;s12+=a*b;cnt++;
    }
    printf("odd numbers in [3,%d) visited at least once: %lld\n",LIM,cnt);
    printf(" t   count      mean visits\n");
    for(int t=1;t<=8;t++) if(num[t]) printf("%2d %8lld %14.1f\n",t,num[t],sum[t]/num[t]);
    double n_=cnt, cov=s12/n_-(s1/n_)*(s2/n_);
    double va=ss1/n_-(s1/n_)*(s1/n_), vb=ss2/n_-(s2/n_)*(s2/n_);
    printf("corr(t, log visits) = %.4f\n",cov/sqrt(va*vb));
    printf("ratio mean(t=1)/mean(t>=4) = %.3f\n",
        (sum[1]/num[1]) / ((sum[4]+sum[5]+sum[6]+sum[7]+sum[8])/(double)(num[4]+num[5]+num[6]+num[7]+num[8])));
    /* busiest t>=6 numbers in band */
    printf("\nbusiest numbers with t>=6 in [3,%d):\n",LIM);
    for(int r=0;r<6;r++){ long long best=-1; int bi=0;
        for(int i=3;i<LIM;i+=2) if(tones(i)>=6 && v[i]>best){best=v[i];bi=i;}
        if(best<=0)break; printf("  %7d  t=%d  visits=%lld\n",bi,tones(bi),best); v[bi]=-1; }
    /* and including below 1001, for context */
    printf("\n319 visits = (see road319)  busiest t>=6 overall check below 1001:\n");
    return 0;
}
