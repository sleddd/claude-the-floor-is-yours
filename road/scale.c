/* Share of starts 1..N passing each target value, standard Collatz map, at 1-10 steps to Nmax.
   ps[n] bit i = start n's path visits T[i]. Walk until x < n, then inherit ps[x].
   gcc -O2 -o scale scale.c && ./scale 100000000 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
static const u64 T[] = {9232, 39364, 9841, 7381, 5536, 13120};
#define K 6
int main(int argc, char **argv) {
  u64 N = strtoull(argv[1], 0, 10);
  unsigned char *ps = calloc(N + 1, 1);
  u64 c[K] = {0}, next = 10000;
  printf("%-10s", "N"); for (int i = 0; i < K; i++) printf(" %9llu", (unsigned long long)T[i]); printf("\n");
  for (u64 n = 1; n <= N; n++) {
    unsigned char m = 0; u64 x = n;
    for (;;) {
      for (int i = 0; i < K; i++) if (x == T[i]) m |= 1 << i;
      if (x == 1) break;
      x = (x & 1) ? 3 * x + 1 : x / 2;
      if (x < n) { m |= ps[x]; break; }
    }
    ps[n] = m;
    for (int i = 0; i < K; i++) c[i] += (m >> i) & 1;
    if (n == next) {
      printf("%-10llu", (unsigned long long)n);
      for (int i = 0; i < K; i++) printf(" %9.6f", (double)c[i] / n);
      printf("\n"); next *= 10;
    }
  }
  return 0;
}
