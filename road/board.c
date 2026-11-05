/* Values per start in octaves 2^12..2^21, split by how a path first meets 27's path:
   free (never touches 27's climb 27..9232, so never passes 9232), high (first road value 9232), low (first road value < 9232). Starts uniform in [1, 10^9].
   gcc -O2 -o board board.c && ./board 10000000 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
static u64 rng = 0x9e3779b97f4a7c15ULL;
static u64 next64(void) { rng ^= rng << 13; rng ^= rng >> 7; rng ^= rng << 17; return rng; }
static unsigned char road[10000];
int main(int argc, char **argv) {
  u64 S = strtoull(argv[1], 0, 10), N = 1000000000ULL;
  for (u64 x = 27;; x = (x & 1) ? 3 * x + 1 : x / 2) { road[x] = 1; if (x == 9232) break; }  /* the climb: 27 .. 9232 */
  double cnt[3][64] = {{0}}, n[3] = {0}, fin[64] = {0};
  u64 top[10000] = {0};
  int kv[2000];
  for (u64 s = 0; s < S; s++) {
    u64 x = next64() % N + 1; int len = 0, g = 0, bpos = -1; u64 bv = 0;
    for (;;) {
      kv[len++] = 63 - __builtin_clzll(x);
      if (!bv && x < 10000 && road[x]) { bv = x; bpos = len - 1; }
      if (x == 1) break;
      x = (x & 1) ? 3 * x + 1 : x / 2;
    }
    if (!bv) g = 0; else g = (bv == 9232) ? 1 : 2;
    if (g) top[bv]++;
    n[g]++;
    for (int i = 0; i < len; i++) {
      if (g && i > bpos) break;            /* only the part of the path before boarding */
      cnt[g][kv[i]]++;
    }
    if (g == 1) for (int i = bpos - 4; i < bpos; i++) if (i >= 0) fin[kv[i]]++;
    /* after boarding, the path is 27's: add its fixed contribution separately below */
  }
  /* road tail contribution: 27's path from the boarding value on, per octave */
  double tail[3][64] = {{0}};
  for (u64 b = 1; b < 10000; b++) if (top[b]) {
    int g = (b == 9232) ? 1 : 2;
    for (u64 x = b;; x = (x & 1) ? 3 * x + 1 : x / 2) { int k = 63 - __builtin_clzll(x); if (x != b) tail[g][k] += top[b]; if (x == 1) break; }
  }
  const char *nm[3] = {"free", "high", "low"};
  printf("group  share   ");
  for (int k = 12; k <= 21; k++) printf("  2^%-4d", k);
  printf("\n");
  for (int g = 0; g < 3; g++) {
    printf("%-5s  %.4f ", nm[g], n[g] / S);
    for (int k = 12; k <= 21; k++) printf(" %7.3f", (cnt[g][k] + tail[g][k]) / n[g]);
    printf("\n");
  }
  printf("all    1.0000 ");
  for (int k = 12; k <= 21; k++) printf(" %7.3f", (cnt[0][k] + tail[0][k] + cnt[1][k] + tail[1][k] + cnt[2][k] + tail[2][k]) / S);
  printf("\nhigh boarders, last 4 values before 9232, per high start, by octave:");
  for (int k = 12; k <= 21; k++) printf(" 2^%d %.3f", k, fin[k] / n[1]);
  printf("\nhigh share of road-bound: %.4f\ntop boarding values:", n[1] / (n[1] + n[2]));
  for (int r = 0; r < 8; r++) { u64 bi = 0; for (u64 b = 1; b < 10000; b++) if (top[b] > top[bi]) bi = b;
    printf(" %llu (%.4f)", (unsigned long long)bi, top[bi] / (n[1] + n[2])); top[bi] = 0; }
  printf("\n");
  return 0;
}
