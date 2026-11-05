/* In-octave parity for paths of sampled starts. For each value v on the path with LO <= v < HI:
   count it, count it odd, add log2(next/v). Bucketed by start bit length. p = q/(1-q), q = odd share of
   in-octave values (each odd standard value is one odd shortcut step).
   gcc -O2 -o parity parity.c -lm && ./parity 10000000 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
typedef uint64_t u64;
#define LO 16384
#define HI 32768
static u64 rng = 0x9e3779b97f4a7c15ULL;
static u64 next64(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
int main(int argc, char **argv) {
  u64 S = strtoull(argv[1], 0, 10), N = 1000000000ULL;
  double cnt[31] = {0}, odd[31] = {0}, drift[31] = {0}, starts[31] = {0};
  for (u64 s = 0; s < S; s++) {
    u64 n = next64() % N + 1, x = n; int b = 64 - __builtin_clzll(n);
    starts[b]++;
    while (x != 1) {
      u64 y = (x & 1) ? 3 * x + 1 : x / 2;
      if (x >= LO && x < HI) { cnt[b]++; odd[b] += x & 1; drift[b] += log2((double)y / x); }
      x = y;
    }
  }
  double C = 0, O = 0, D = 0, St = 0;
  printf("bits  starts      values/start  q        p        count*|drift|\n");
  for (int b = 1; b <= 30; b++) {
    if (!starts[b]) continue;
    C += cnt[b]; O += odd[b]; D += drift[b]; St += starts[b];
    if (b < 16 || !cnt[b]) continue;
    double q = odd[b] / cnt[b];
    printf("%2d  %10.0f  %8.4f  %.5f  %.5f  %.4f\n", b, starts[b], cnt[b] / starts[b], q, q / (1 - q), cnt[b] / starts[b] * fabs(drift[b] / cnt[b]));
  }
  double q = O / C;
  printf("all  %10.0f  %8.4f  %.5f  %.5f  %.4f\n", St, C / St, q, q / (1 - q), C / St * fabs(D / C));
  return 0;
}
