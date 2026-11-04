/* analog.c: path of one start under x odd -> 3x+k, x even -> x/2, until it repeats.
   Prints peak (value and step) and the first step at which it reaches v.
   Usage: analog k start v      gcc -O2 -o analog analog.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint64_t u64;
int main(int argc,char**argv){
  u64 k=strtoull(argv[1],0,10), x=strtoull(argv[2],0,10), v=strtoull(argv[3],0,10);
  static u64 seen[1<<20]; int n=0; u64 peak=x; int ps=0, vs=-1, mn=-1;
  for(int s=0;;s++){ for(int i=0;i<n;i++) if(seen[i]==x){ mn=i; break; } if(mn>=0) break;
    seen[n++]=x; if(x>peak){peak=x;ps=s;} if(x==v&&vs<0) vs=s; x=(x&1)?3*x+k:x/2; }
  u64 cm=seen[mn]; for(int i=mn;i<n;i++) if(seen[i]<cm) cm=seen[i];
  printf("k=%llu start=%s peak %llu at step %d, reaches %llu at step %d, cycle entered at step %d, cycle min %llu\n",
    (unsigned long long)k,argv[2],(unsigned long long)peak,ps,(unsigned long long)v,vs,mn,(unsigned long long)cm);
  return 0; }
