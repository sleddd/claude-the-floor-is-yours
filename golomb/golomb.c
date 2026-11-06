/* Golomb's sequence (OEIS A001462): a(1)=1, a(n+1) = 1 + a(n+1 - a(a(n))).
   a(n) ~ C n^(phi-1), C = phi^(2-phi). e(n) = a(n)/(C n^(phi-1)) - 1.
   gcc -O2 -o golomb golomb.c -lm && ./golomb */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000000
int main(void) {
    int *a = malloc((N + 2) * sizeof *a);
    a[1] = 1;
    for (long n = 1; n < N; n++) a[n + 1] = 1 + a[n + 1 - a[a[n]]];
    const double phi = (1 + sqrt(5)) / 2, C = pow(phi, 2 - phi);
    #define E(n, v) ((v) / (C * pow((double)(n), phi - 1)) - 1)
    printf("C = phi^(2-phi) = %.6f\n", C);
    for (long n = 1000; n <= N; n *= 10)
        printf("n=%-9ld a=%-6d a/n^(phi-1)=%.6f e=%+.6f e*ln n=%+.5f\n",
               n, a[n], a[n] / pow(n, phi - 1), E(n, a[n]), E(n, a[n]) * log(n));
    /* raw sign flips and max |e ln n| on [1e3, 1e7] */
    long flips = 0; int prev = 0; double mx = 0; long at = 0;
    for (long n = 1000; n <= N; n++) {
        double e = E(n, a[n]); int s = e > 0 ? 1 : -1;
        if (prev && s != prev) flips++;
        prev = s;
        double t = fabs(e * log(n)); if (t > mx) { mx = t; at = n; }
    }
    printf("raw sign flips on [1e3,1e7]: %ld\nmax |e ln n| on [1e3,1e7]: %.5f at n=%ld\n", flips, mx, at);
    /* plateau midpoints: runs of equal a(n) wholly inside [1, N] */
    printf("plateau-midpoint sign changes (whole run inside [1,1e7]):\n");
    long start = 1; prev = 0; double lastm = 0, laste = 0; long mcount = 0, minband = 0;
    double best = 1e9; long bestm2 = 0; double beste = 0;
    for (long n = 2; n <= N; n++) {
        if (a[n] != a[start]) {
            long end = n - 1; double m = (start + end) / 2.0;
            double e = E(m, a[start]); int s = e > 0 ? 1 : -1;
            if (prev && s != prev) {
                printf("  between mid %.1f (e ln n %+.5f) and mid %.1f (e ln n %+.5f), ln n ~ %.2f\n",
                       lastm, laste * log(lastm), m, e * log(m), log(m));
                if (lastm >= 1000) mcount++;
            }
            if (fabs(m - 9995215) < best) { best = fabs(m - 9995215); bestm2 = (long)(2 * m); beste = e * log(m); }
            prev = s; lastm = m; laste = e; start = n;
        }
    }
    printf("midpoint sign changes with both midpoints >= 1e3: %ld\n", mcount);
    printf("midpoint nearest 9995215: %.1f, e*ln n = %+.5f\n", bestm2 / 2.0, beste);
    return 0;
}
