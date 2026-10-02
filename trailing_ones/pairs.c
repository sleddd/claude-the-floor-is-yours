#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* For each odd n <= N exactly once:
     t = trailing ones of n
     apply T (odd -> oddpart(3n+1)) exactly t times -> u, the next run's fresh value
     record pair (t, t(u)).
   No trajectory following, so no merge weighting. */

static inline int tones(unsigned long long n){ return __builtin_ctzll(n+1ULL); }

#define CAP 16
static long long joint[CAP][CAP];
static long long rowtot[CAP], coltot[CAP], total=0;
static double s1=0,s2=0,ss1=0,ss2=0,s12=0;

int main(int argc,char**argv){
    unsigned long long N=(argc>1)?strtoull(argv[1],0,10):10000000ULL;
    for(unsigned long long n=1;n<=N;n+=2){
        int t=tones(n);
        unsigned long long x=n;
        int ok=1;
        for(int i=0;i<t;i++){
            if(x > (0xFFFFFFFFFFFFFFFFULL-1)/3ULL){ok=0;break;}
            x=3ULL*x+1ULL; x>>=__builtin_ctzll(x);
        }
        if(!ok) continue;
        int j=tones(x);
        int tc=t<CAP-1?t:CAP-1, jc=j<CAP-1?j:CAP-1;
        joint[tc][jc]++; rowtot[tc]++; coltot[jc]++; total++;
        double a=t,b=j; s1+=a;s2+=b;ss1+=a*a;ss2+=b*b;s12+=a*b;
    }
    printf("N=%llu pairs=%lld\n",N,total);
    double n_=total;
    double cov=s12/n_-(s1/n_)*(s2/n_);
    double v1=ss1/n_-(s1/n_)*(s1/n_), v2=ss2/n_-(s2/n_)*(s2/n_);
    printf("mean t=%.6f  mean t(u)=%.6f  corr=%.6f\n",s1/n_,s2/n_,cov/__builtin_sqrt(v1*v2));
    printf("\nmarginal of t(u):  j  count  share  2^-j  rel_err\n");
    for(int j=1;j<=10;j++){
        double sh=(double)coltot[j]/total, pr=1.0/(1ULL<<j);
        printf(" %2d %12lld %.7f %.7f %+.4f\n",j,coltot[j],sh,pr,(sh-pr)/pr);
    }
    printf("\nP(t(u)=j | t=t)   rows t=1..8, cols j=1..7, then n\n");
    for(int t=1;t<=8;t++){
        if(!rowtot[t])continue;
        printf(" t=%d:",t);
        for(int j=1;j<=7;j++) printf(" %.5f",(double)joint[t][j]/rowtot[t]);
        printf("   n=%lld\n",rowtot[t]);
    }
    printf("\nratio to independent (cell / 2^-j), rows t=1..8\n");
    for(int t=1;t<=8;t++){
        if(!rowtot[t])continue;
        printf(" t=%d:",t);
        for(int j=1;j<=7;j++){
            double sh=(double)joint[t][j]/rowtot[t], pr=1.0/(1ULL<<j);
            printf(" %6.3f",sh/pr);
        }
        printf("\n");
    }
    return 0;
}
