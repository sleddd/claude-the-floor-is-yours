/* Per-octave stats over sampled paths (starts uniform in [1, 10^9]) for octaves 2^k..2^(k+1), k = 6..26,
   plus the global shortcut-step odd fraction over values in a wide middle band [2^10, 2^24).
   q = odd share of in-octave values; p = q/(1-q). gcc -O2 -o parity2 parity2.c -lm && ./parity2 10000000 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
typedef uint64_t u64;
static u64 rng = 0x9e3779b97f4a7c15ULL;
static u64 next64(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
int main(int argc, char **argv) {
  u64 S = strtoull(argv[1], 0, 10), N = 1000000000ULL;
  double cnt[64] = {0}, odd[64] = {0}, wc = 0, wo = 0;
  for (u64 s = 0; s < S; s++) {
    u64 x = next64() % N + 1;
    while (x != 1) {
      int k = 63 - __builtin_clzll(x);
      cnt[k]++; odd[k] += x & 1;
      if (x >= (1u << 10) && x < (1u << 24)) { wc++; wo += x & 1; }
      x = (x & 1) ? 3 * x + 1 : x / 2;
    }
  }
  printf("octave  values/start  q        p\n");
  for (int k = 6; k <= 26; k++) { double q = odd[k] / cnt[k]; printf("2^%-2d   %8.4f   %.5f  %.5f\n", k, cnt[k] / S, q, q / (1 - q)); }
  double q = wo / wc, p = q / (1 - q);
  printf("band [2^10,2^24): values/start/octave %.4f  q %.5f  p %.5f  -> (1+p)/(1-1.585p) = %.4f\n",
         wc / S / 14, q, p, (1 + p) / (1 - log2(3) * p));
  return 0;
}
