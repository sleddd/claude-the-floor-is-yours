/* Golomb: e at every plateau midpoint for value indices m <= JMAX (default 7e11, ln n ~ 43.8),
   computed exactly from the partial sums P by walking a's runs; plus W(m) = sum_{j<=m}(a(j) - c j^ex).
   Value m's plateau occupies positions P(m-1)+1..P(m); its midpoint is P(m-1) + (a(m)+1)/2, and
   e_m > 0 iff g(m) = m - c mid_m^ex > 0. On v's run (a(j) = v) mid is linear in j and g is convex,
   so each run needs only its endpoints and its interior minimum.
   gcc -O2 -o w w.c -lm && ./w [jmax] */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 30000000
#define MAXF 1000
typedef long double ld;
typedef unsigned __int128 u128;
static int *a;
static ld C, EX, PHI;
static ld g_at(u128 P0, long long J0, long long v, long long j) {
    ld mid = (ld)P0 + (ld)v * (ld)(j - J0) + ((ld)v + 1) / 2;
    return (ld)j - C * powl(mid, EX);
}
static ld lnmid(u128 P0, long long J0, long long v, long long j) {
    return logl((ld)P0 + (ld)v * (ld)(j - J0) + ((ld)v + 1) / 2);
}
/* first j in (lo, hi] whose sign differs from sign at lo; g monotone on [lo, hi] */
static long long bisect(u128 P0, long long J0, long long v, long long lo, long long hi) {
    int s = g_at(P0, J0, v, lo) > 0;
    while (hi - lo > 1) { long long md = lo + (hi - lo) / 2; if ((g_at(P0, J0, v, md) > 0) == s) lo = md; else hi = md; }
    return hi;
}
int main(int argc, char **argv) {
    long long jmax = argc > 1 ? atoll(argv[1]) : 700000000000LL;
    a = malloc((T + 2) * sizeof *a); a[1] = 1;
    for (long n = 1; n < T; n++) a[n + 1] = 1 + a[n + 1 - a[a[n]]];
    PHI = (1 + sqrtl(5)) / 2; EX = PHI - 1; C = powl(PHI, 2 - PHI);
    /* zeta(-EX) for H(m) = sum_{i<=m} i^EX by Euler-Maclaurin */
    ld H = 0; long NZ = 1000000; for (long i = 1; i <= NZ; i++) H += powl(i, EX);
    ld zeta = H - powl(NZ, PHI) / PHI - powl(NZ, EX) / 2 - EX * powl(NZ, EX - 1) / 12;
    printf("c = %.12Lf, zeta(-ex) = %.9Lf\n", C, zeta);
    /* part 1: W crossings for m <= 60000, brute force */
    { ld W = 0; int ps = 0; printf("W zero crossings, m <= 60000:");
      for (long m = 1; m <= 60000; m++) { W += a[m] - C * powl(m, EX); int s = W > 0 ? 1 : -1; if (ps && s != ps) printf(" %ld", m); ps = s; }
      printf("\n"); }
    /* part 2: zone-to-zone midpoints for S2 (zone centres from rle_out.txt) */
    double zc[6] = {2.4526, 5.1452, 9.3656, 15.6782, 25.9931, 42.7387};   /* zone 6 added after this run found it */
    double nk[5]; for (int k = 0; k < 5; k++) nk[k] = floor(exp((zc[k] + zc[k + 1]) / 2));
    int kq = 0;
    /* part 3: walk runs */
    static double fpos[MAXF]; static long long fj[MAXF]; long nf = 0;
    u128 P0 = 0; long long J0 = 1; int prevs = 0;
    for (long long v = 1; J0 <= jmax; v++) {
        if (v > T) { fprintf(stderr, "table too small\n"); return 1; }
        long long J1 = J0 + a[v] - 1; if (J1 > jmax) J1 = jmax;
        /* S2 queries: position n in plateau of some j in this run? P(j) = P0 + v*(j-J0+1) */
        while (kq < 5 && (ld)nk[kq] <= (ld)P0 + (ld)v * (ld)(J1 - J0 + 1)) {
            long long j = J0 + (long long)ceill(((ld)nk[kq] - (ld)P0) / v) - 1;
            ld e = (ld)j / (C * powl((ld)nk[kq], EX)) - 1;
            ld Pj = (ld)P0 + (ld)v * (ld)(j - J0 + 1);
            ld Hj = powl(j, PHI) / PHI + powl(j, EX) / 2 + zeta + EX * powl(j, EX - 1) / 12;
            ld W = Pj - C * Hj;
            printf("S2 k=%d: ln n = %.4f, a(n) = %lld, e(n) = %+.3Le, W(a(n)) = %+.4Le -> %s\n", kq + 1,
                   log(nk[kq]), j, e, W, (e > 0) != (W > 0) ? "opposite" : "SAME");
            kq++;
        }
        ld g0 = g_at(P0, J0, v, J0), g1 = g_at(P0, J0, v, J1);
        int s0 = g0 > 0 ? 1 : -1, s1 = g1 > 0 ? 1 : -1;
        long long cand[3]; int nc = 0;
        if (prevs && s0 != prevs) cand[nc++] = J0;
        /* interior minimum of the convex g */
        ld midstar = powl(C * EX * v, 1 / (1 - EX));
        ld jstar = J0 + (midstar - ((ld)P0 + ((ld)v + 1) / 2)) / v;
        long long jm = -1;
        if (jstar > J0 && jstar < J1) {
            long long f = (long long)floorl(jstar); jm = f;
            if (f + 1 <= J1 && g_at(P0, J0, v, f + 1) < g_at(P0, J0, v, f)) jm = f + 1;
            if (jm <= J0 || jm >= J1) jm = -1;
        }
        if (jm > 0 && (g_at(P0, J0, v, jm) > 0 ? 1 : -1) != s0) {
            cand[nc++] = bisect(P0, J0, v, J0, jm);
            if (s1 == s0) cand[nc++] = bisect(P0, J0, v, jm, J1);   /* right side changes back only if the ends agree */
        } else if (s1 != s0) {
            cand[nc++] = bisect(P0, J0, v, J0, J1);
        }
        for (int i = 0; i < nc; i++) {
            if (cand[i] > 1000000000LL)
                printf("flip at m = %lld: v = %lld, run start %lld, P(run start - 1) = %llu\n", cand[i], v, J0, (unsigned long long)P0);
            if (nf >= MAXF) return 1;
            fj[nf] = cand[i]; fpos[nf++] = (double)lnmid(P0, J0, v, cand[i]);
        }
        prevs = s1;
        P0 += (u128)v * (u128)(J1 - J0 + 1);
        J0 = J1 + 1;
    }
    printf("walked m <= %lld; last midpoint ln n = %.4f\nflips: %ld\n", jmax, log((double)P0), nf);
    long zs = 0; int z = 0;
    for (long i = 1; i <= nf; i++)
        if (i == nf || fpos[i] - fpos[i - 1] >= log(2.0)) {
            printf("zone %d: flips %ld, ln %.4f..%.4f, centre %.4f, value index m %lld..%lld\n", ++z, i - zs,
                   fpos[zs], fpos[i - 1], (fpos[zs] + fpos[i - 1]) / 2, fj[zs], fj[i - 1]);
            zs = i;
        }
    return 0;
}
