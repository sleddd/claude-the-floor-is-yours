#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc,char**argv){
  long N = argc>1 ? atol(argv[1]) : 1000000;
  uint32_t *r = calloc(N+1,4); int32_t *sm = calloc(N+1,4);
  int32_t *U = malloc(sizeof(int32_t)*N); long K=0;
  U[K++]=1; U[K++]=2; r[3]=1; sm[3]=1;
  for(long n=3;n<=N;n++){
    if(r[n]==1){
      for(long i=0;i<K;i++){ long m=n+U[i]; if(m>N) break; r[m]++; sm[m]=U[i]; }
      U[K++]=n;
    }
  }
  FILE*f=fopen("r.bin","wb"); fwrite(r,4,N+1,f); fclose(f);
  f=fopen("sm.bin","wb"); fwrite(sm,4,N+1,f); fclose(f);
  f=fopen("U.bin","wb"); fwrite(U,4,K,f); fclose(f);
  printf("N=%ld K=%ld density=%.6f\n",N,K,(double)K/N);
}
