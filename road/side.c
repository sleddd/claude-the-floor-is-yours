/* Side branches of 27's road (Nov 12 2026). See sealed_side.txt.
   A[w] = starts n <= N whose trajectory (start included) hits w, for w < 32768.
   Side root of path value v (index i > 0): the predecessor of v (2v, or (v-1)/3 when
   v%6==4) that isn't path[i-1]. 27 is its own root. Baseline: median A over
   w in [r/1.5, 1.5r], w == r mod 27, w not on 27's path. CHAT=1 (default) matches
   chat's run: lower bound floored, w == r left out. CHAT=0 is the sealed wording read
   literally (exact bounds, r kept in its own window). ./side 0 for that.
   gcc -O2 -o side side.c && ./side */
#include <stdio.h>
#include <stdlib.h>
#define W 32768
#define N 1000000
static long A[W];
static int onpath[W];
static int cmp(const void *a, const void *b) { long x = *(long *)a, y = *(long *)b; return (x > y) - (x < y); }
static int cmpd(const void *a, const void *b) { double x = *(double *)a, y = *(double *)b; return (x > y) - (x < y); }
int main(int argc, char **argv) {
  int chat = argc > 1 ? atoi(argv[1]) : 1;
  for (long n = 1; n <= N; n++) {
    unsigned long long x = n;
    for (;;) { if (x < W) A[x]++; if (x == 1) break; x = (x & 1) ? 3 * x + 1 : x / 2; }
  }
  long path[100]; int L = 0; long x = 27;
  for (;;) { path[L++] = x; onpath[x] = 1; if (x == 9232) break; x = (x & 1) ? 3 * x + 1 : x / 2; }
  printf("path length %d\n", L);
  long road = A[9232];
  printf("road %ld (%.4f)\n", road, road / (double)N);
  long sumboard = 0, npathstarts = 0; double sumbase = 0;
  double ratios[100]; int nr = 0, above2 = 0;
  long topv[100], topr[100], topA[100]; double topb[100]; int nb = 0;
  printf("\n  i     v  root        A   baseline   ratio  nwin\n");
  for (int i = 0; i < L; i++) {
    long v = path[i], r = -1;
    if (i == 0) r = 27;
    else if (v % 2 == 0) {
      long c1 = 2 * v, c2 = (v % 6 == 4) ? (v - 1) / 3 : -1;
      if (c1 != path[i - 1]) r = c1; else if (c2 > 0 && c2 != path[i - 1]) r = c2;
    }
    if (i > 0 && v <= N) npathstarts++;
    if (r < 0) continue;
    long boardA = (i == 0) ? A[27] : A[r];
    sumboard += boardA;
    long buf[W]; int k = 0;
    long lo = chat ? (long)(r / 1.5) : (2 * r + 2) / 3;
    for (long w = lo; 2 * w <= 3 * r; w++)
      if (w % 27 == r % 27 && !onpath[w] && !(chat && w == r)) buf[k++] = A[w];
    double base = 0;
    if (k) { qsort(buf, k, sizeof(long), cmp); base = (k % 2) ? buf[k / 2] : (buf[k / 2 - 1] + buf[k / 2]) / 2.0; }
    double ratio = base > 0 ? A[r] / base : -1;
    printf("%3d %5ld %5ld %8ld %10.1f %7.2f %5d\n", i, v, r, A[r], base, ratio, k);
    if (base > 0) { ratios[nr++] = ratio; if (ratio > 2) above2++; sumbase += base; }
    if (i > 0) { topv[nb] = v; topr[nb] = r; topA[nb] = A[r]; topb[nb] = base; nb++; }
  }
  qsort(ratios, nr, sizeof(double), cmpd);
  double med = (nr % 2) ? ratios[nr / 2] : (ratios[nr / 2 - 1] + ratios[nr / 2]) / 2;
  printf("\nroots with baselines %d, median ratio %.4f, above 2: %d (%.3f)\n", nr, med, above2, above2 / (double)nr);
  printf("sum boarding (27 included) %ld + %ld path starts = %ld (road %ld)\n", sumboard, npathstarts, sumboard + npathstarts, road);
  for (int a = 0; a < nb; a++) for (int b = a + 1; b < nb; b++) if (topA[b] > topA[a]) {
    long t; double d; t = topv[a]; topv[a] = topv[b]; topv[b] = t; t = topr[a]; topr[a] = topr[b]; topr[b] = t;
    t = topA[a]; topA[a] = topA[b]; topA[b] = t; d = topb[a]; topb[a] = topb[b]; topb[b] = d; }
  printf("\ntop boarding (v, root, A, baseline, ratio, share of road)\n");
  long top4 = 0;
  for (int a = 0; a < 8 && a < nb; a++) {
    printf("%5ld %5ld %7ld %9.1f %5.2f %.4f\n", topv[a], topr[a], topA[a], topb[a], topb[a] > 0 ? topA[a] / topb[a] : -1, topA[a] / (double)road);
    if (a < 4) top4 += topA[a];
  }
  printf("top four carry %ld = %.4f of road\n", top4, top4 / (double)road);
  printf("sum of baselines (the %d roots that have one; 27 has none) + %ld path starts: share %.4f\n", nr, npathstarts, (sumbase + npathstarts) / N);
  return 0;
}
