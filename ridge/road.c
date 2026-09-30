#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define N 100000
#define CAP (1u<<24)
static inline uint64_t mix(uint64_t z){z+=0x9e3779b97f4a7c15ULL;z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;z=(z^(z>>27))*0x94d049bb133111ebULL;return z^(z>>31);}
static inline uint64_t step(uint64_t x, uint64_t seed){
  int up = seed ? (int)(mix(seed*0x100000001B3ULL ^ x) & 1) : (int)(x & 1);
  return up ? (3*x+1)/2 : x/2;
}
static uint32_t tr[CAP];
int main(int argc,char**argv){
  for(int a=1;a<argc;a++){
    uint64_t s=strtoull(argv[a],0,10); memset(tr,0,sizeof tr);
    for(uint64_t n=2;n<=N;n++){ uint64_t x=n; int st=0;
      while(x!=1 && st<20000){ if(x<CAP) tr[x]++; x=step(x,s); st++; } }
    uint32_t best=0; uint64_t bv=0;
    for(uint64_t v=1000; v<CAP; v++) if(tr[v]>best){best=tr[v]; bv=v;}
    /* climb: highest value that still carries >= half of best */
    uint64_t top=bv; for(uint64_t v=1000; v<CAP; v++) if(tr[v]>=best && v>top) top=v;
    printf("%lu %.4f %lu %lu\n",(unsigned long)s,(double)best/(N-1),(unsigned long)bv,(unsigned long)top);
  }
  return 0;
}
