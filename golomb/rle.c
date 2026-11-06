/* Golomb's sequence by run length, plateau midpoints to positions 10^15.
   Value k fills positions S(k-1)+1..S(k); a(k) itself comes from the run structure of a
   flat table a[1..L] (L = 10^7), since a(k) = j where k lies in value j's run.
   gcc -O2 -o rle rle.c -lm && ./rle [maxpos]    (default 1e15; ~2.3e9 plateaus) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define L 10000000
#define MAXF 100000
typedef long double ld;
int main(int argc, char **argv) {
    unsigned long long maxpos = argc > 1 ? strtoull(argv[1], 0, 10) : 1000000000000000ULL;
    int *a = malloc((L + 2) * sizeof *a);
    a[1] = 1;
    for (long n = 1; n < L; n++) a[n + 1] = 1 + a[n + 1 - a[a[n]]];
    const ld phi = (1 + sqrtl(5)) / 2, C = powl(phi, 2 - phi), ex = phi - 1;
    static double fpos[MAXF], fseg[MAXF + 1]; static int fbad[MAXF]; long nf = 0;
    /* fseg[i] = max |e ln m| on plateaus after flip i-1 up to (not incl.) flip i's right plateau */
    unsigned long long S = 0, nextdec = 1000; int prevsign = 0;
    long j = 1, left = a[1];          /* k lies in value j's run; 'left' values remain in it */
    double segmax = 0; double near_e = 0;
    for (unsigned long long k = 1;; k++) {
        if (left == 0) { j++; if (j > L) { fprintf(stderr, "table too small\n"); return 1; } left = a[j]; }
        left--;
        unsigned long long ak = j;    /* a(k) */
        unsigned long long lo = S + 1, hi = S + ak;
        if (hi > maxpos) break;
        while (nextdec <= hi) {
            if (nextdec >= lo) {
                ld e = (ld)k / (C * powl((ld)nextdec, ex)) - 1;
                printf("n=1e%.0f a=%llu a/n^(phi-1)=%.9Lf e=%+.3Le e*ln n=%+.6Lf\n",
                       log10((double)nextdec), k, (ld)k / powl((ld)nextdec, ex), e, e * logl((ld)nextdec));
            }
            nextdec *= 10;
        }
        ld m = ((ld)lo + (ld)hi) / 2, lm = logl(m);
        ld e = (ld)k / (C * expl(ex * lm)) - 1;
        int s = e > 0 ? 1 : -1;
        if (m == 9995215.0L) { near_e = (double)(e * lm);}
        if (prevsign && s != prevsign) {
            if (nf >= MAXF) { fprintf(stderr, "too many flips\n"); return 1; }
            fseg[nf] = segmax; fpos[nf] = (double)lm;
            fbad[nf] = fabsl(e) < 1e-15L;   /* sign not resolved at long double precision */
            nf++; segmax = 0;
        }
        double t = fabs((double)(e * lm)); if (t > segmax) segmax = t;
        prevsign = s; S = hi;
    }
    fseg[nf] = segmax;
    printf("last full plateau ends at %llu (ln %.4f); midpoint 9995215 e*ln n = %+.5f\n", S, log((double)S), near_e);
    printf("flips: %ld\n", nf);
    /* zones */
    long zs = 0; int z = 0;
    for (long i = 1; i <= nf; i++) {
        if (i == nf || fpos[i] - fpos[i - 1] >= log(2.0)) {
            double c = (fpos[zs] + fpos[i - 1]) / 2;
            double hw = 0; /* max over half-wave before this zone: segments after previous zone's last flip */
            hw = fseg[zs];   /* segment since the previous zone's last flip */
            int bad = 0; for (long q = zs; q < i; q++) bad |= fbad[q];
            printf("zone %d: flips %ld, ln %.4f..%.4f, centre %.4f, max|e ln m| on the half-wave before it %.6f%s\n",
                   ++z, i - zs, fpos[zs], fpos[i - 1], c, hw, bad ? "  [unresolved sign]" : "");
            zs = i;
        }
    }
    printf("max|e ln m| after the last zone %.6f\n", fseg[nf]);
    return 0;
}
