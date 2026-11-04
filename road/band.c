/* traffic(v) for every v <= M at checkpoints N = 10^6, 10^7, 10^8.
   entry(n) = first value <= M on n's path (n itself if n <= M). Before entry the path is > M,
   so window visits are exactly the values <= M on the path from entry(n). Memo: the path from
   n stays >= n until it first drops below n at x, so entry(n) = entry(x) when x > M, else x.
   Then traffic(v) = sum over y of E[y] * [v on path(y)].
   gcc -O2 -o band band.c && ./band 100000000 > band_out.txt */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
#define M 60000
static u64 E[M + 1];
static void dump(u64 N) {
  static u64 tr[M + 1];
  for (int v = 0; v <= M; v++) tr[v] = 0;
  for (int y = 1; y <= M; y++) if (E[y]) {
    u64 x = y;
    for (;;) { if (x <= M) tr[x] += E[y]; if (x == 1) break; x = (x & 1) ? 3 * x + 1 : x / 2; }
  }
  for (int v = 1; v <= M; v++) printf("%llu %d %llu\n", (unsigned long long)N, v, (unsigned long long)tr[v]);
}
int main(int argc, char **argv) {
  u64 N = strtoull(argv[1], 0, 10), next = 1000000;
  uint16_t *en = malloc((N + 1) * 2);
  for (u64 n = 1; n <= N; n++) {
    u64 e;
    if (n <= M) e = n;
    else {
      u64 x = n;
      do x = (x & 1) ? 3 * x + 1 : x / 2; while (x >= n);
      e = (x <= M) ? x : en[x];
    }
    en[n] = (uint16_t)e; E[e]++;
    if (n == next) { dump(n); next *= 10; }
  }
  return 0;
}
