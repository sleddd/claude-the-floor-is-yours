#include <stdio.h>
#include <stdlib.h>
static inline int tones(unsigned long long n){ return __builtin_ctzll(n+1ULL); }
int main(int argc,char**argv){
    unsigned long long N=(argc>1)?strtoull(argv[1],0,10):1000000ULL;
    long long hit319=0,tot=0, band=0, band319=0, bandmax6=0, band319max6=0, bandother6=0;
    /* also: among starts that do NOT visit 319, share with max t>=6 */
    long long no319=0, no319max6=0;
    for(unsigned long long n0=1;n0<=N;n0+=2){
        unsigned long long x=n0; int steps=0,mx=0,h=0;
        while(x!=1ULL){ int t=tones(x); if(t>mx)mx=t; if(x==319ULL)h=1; steps++;
            x=3ULL*x+1ULL; x>>=__builtin_ctzll(x); }
        tot++; if(h)hit319++;
        if(!h){ no319++; if(mx>=6) no319max6++; }
        if(steps>=39&&steps<=43){ band++; if(h)band319++; if(mx>=6)bandmax6++;
            if(h&&mx>=6)band319max6++; if(!h&&mx>=6)bandother6++; }
    }
    printf("starts %lld\n",tot);
    printf("visit 319            : %lld  (%.4f)\n",hit319,(double)hit319/tot);
    printf("max t>=6 among NON-319 starts : %lld/%lld = %.4f\n",no319max6,no319,(double)no319max6/no319);
    printf("\n39-43 odd-step band: %lld starts\n",band);
    printf("  visit 319          : %.4f\n",(double)band319/band);
    printf("  max t>=6 overall   : %.4f\n",(double)bandmax6/band);
    printf("  max t>=6 | 319     : %.4f\n",(double)band319max6/band319);
    printf("  max t>=6 | no 319  : %.4f\n",(double)bandother6/(band-band319));
    return 0;
}
