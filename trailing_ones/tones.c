#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* T-map on odds: n -> oddpart(3n+1).  t(n) = trailing 1-bits = ctz(n+1). */

#define MAXT 64

static inline int tones(unsigned long long n){ return __builtin_ctzll(n+1ULL); }

/* globals for step-wise t histogram */
static long long step_hist[MAXT];
static long long fresh_hist[MAXT];
/* joint histogram of consecutive fresh t values, capped at 12 */
#define FCAP 13
static long long joint[FCAP][FCAP];
static long long fresh_pairs = 0;
static double fs1=0, fs2=0, fss1=0, fss2=0, fs12=0;  /* for correlation */

int main(int argc, char**argv){
    unsigned long long N = (argc>1)? strtoull(argv[1],0,10) : 1000000ULL;

    /* per-start summaries */
    unsigned int *odd_steps = malloc(sizeof(unsigned int)*(N/2+2));
    unsigned int *maxt      = malloc(sizeof(unsigned int)*(N/2+2));
    unsigned int *cnt4      = malloc(sizeof(unsigned int)*(N/2+2));
    float        *meant     = malloc(sizeof(float)*(N/2+2));
    double       *peakratio = malloc(sizeof(double)*(N/2+2));
    unsigned int *v1frombig = malloc(sizeof(unsigned int)*(N/2+2));
    if(!odd_steps||!maxt||!cnt4||!meant||!peakratio||!v1frombig){fprintf(stderr,"oom\n");return 1;}

    unsigned long long idx=0;
    for(unsigned long long n0=1; n0<=N; n0+=2){
        unsigned long long x = n0, peak = n0;
        unsigned int steps=0, mx=0, c4=0; unsigned long long tsum=0;
        int prev_t = 0;           /* 0 = start of trajectory, treat first as fresh */
        int last_fresh = -1;
        unsigned int v1total = 0; /* = sum over fresh runs of (t-1) */
        unsigned int bigrun = 0;  /* largest fresh t on this path */
        while(x != 1ULL){
            int t = tones(x);
            step_hist[t]++;
            if(t>MAXT-1) {fprintf(stderr,"t overflow\n");return 1;}
            steps++; tsum += t; if((unsigned)t>mx) mx=t; if(t>=4) c4++;
            int is_fresh = (prev_t <= 1);   /* predecessor ended a run */
            if(is_fresh){
                int tc = t<FCAP-1? t : FCAP-1;
                fresh_hist[t]++;
                if(t>1) v1total += (t-1);
                if((unsigned)t>bigrun) bigrun=t;
                if(last_fresh>=0){
                    int pc = last_fresh<FCAP-1? last_fresh : FCAP-1;
                    joint[pc][tc]++;
                    double a=last_fresh,b=t;
                    fs1+=a; fs2+=b; fss1+=a*a; fss2+=b*b; fs12+=a*b; fresh_pairs++;
                }
                last_fresh = t;
            }
            prev_t = t;
            x = 3ULL*x+1ULL;
            x >>= __builtin_ctzll(x);
            if(x>peak) peak=x;
        }
        odd_steps[idx]=steps; maxt[idx]=mx; cnt4[idx]=c4;
        meant[idx]= steps? (float)((double)tsum/steps) : 0.f;
        peakratio[idx]= (double)peak/(double)n0;
        v1frombig[idx]= v1total? (unsigned)(1000.0*(bigrun>1?bigrun-1:0)/v1total) : 0;
        idx++;
    }

    FILE*f=fopen("out_global.txt","w");
    fprintf(f,"N %llu starts %llu\n",N,idx);
    long long tot=0; for(int k=0;k<MAXT;k++) tot+=step_hist[k];
    fprintf(f,"total_odd_steps %lld\n",tot);
    fprintf(f,"# k  step_count  step_share  predicted_2^-k  rel_err\n");
    for(int k=1;k<=12;k++){
        double sh=(double)step_hist[k]/tot, pr=1.0/(1ULL<<k);
        fprintf(f,"%d %lld %.8f %.8f %+.4f\n",k,step_hist[k],sh,pr,(sh-pr)/pr);
    }
    long long ftot=0; for(int k=0;k<MAXT;k++) ftot+=fresh_hist[k];
    fprintf(f,"total_fresh %lld  fresh_share_of_steps %.6f\n",ftot,(double)ftot/tot);
    fprintf(f,"# k  fresh_count fresh_share predicted rel_err\n");
    for(int k=1;k<=12;k++){
        double sh=(double)fresh_hist[k]/ftot, pr=1.0/(1ULL<<k);
        fprintf(f,"%d %lld %.8f %.8f %+.4f\n",k,fresh_hist[k],sh,pr,(sh-pr)/pr);
    }
    double n_=fresh_pairs;
    double num=fs12/n_ - (fs1/n_)*(fs2/n_);
    double d1=fss1/n_-(fs1/n_)*(fs1/n_), d2=fss2/n_-(fs2/n_)*(fs2/n_);
    fprintf(f,"fresh_pairs %lld corr %.6f\n",fresh_pairs,num/ (d1>0&&d2>0? __builtin_sqrt(d1*d2):1));
    fprintf(f,"# joint P(next | prev) rows=prev 1..12\n");
    for(int p=1;p<FCAP;p++){
        long long rs=0; for(int q=1;q<FCAP;q++) rs+=joint[p][q];
        if(!rs) continue;
        fprintf(f,"prev=%d n=%lld :",p,rs);
        for(int q=1;q<=8;q++) fprintf(f," %.5f",(double)joint[p][q]/rs);
        fprintf(f,"\n");
    }
    fclose(f);

    /* dump per-start arrays for python analysis */
    FILE*g=fopen("per_start.bin","wb");
    fwrite(&idx,sizeof(idx),1,g);
    fwrite(odd_steps,sizeof(unsigned int),idx,g);
    fwrite(maxt,sizeof(unsigned int),idx,g);
    fwrite(cnt4,sizeof(unsigned int),idx,g);
    fwrite(meant,sizeof(float),idx,g);
    fwrite(peakratio,sizeof(double),idx,g);
    fwrite(v1frombig,sizeof(unsigned int),idx,g);
    fclose(g);
    fprintf(stderr,"done %llu starts\n",idx);
    return 0;
}
