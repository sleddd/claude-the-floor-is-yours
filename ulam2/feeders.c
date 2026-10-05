#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
/* Ulam sieve to N, then feeder statistics for the window [N/2, N]. */
int main(int argc,char**argv){
  long N = argc>1 ? atol(argv[1]) : 1000000;
  const double a=2.5714474995, TP=2*M_PI, LO=TP/3, HI=2*TP/3;
  uint8_t  *r  = calloc(N+1,1);          /* rep count, capped at 2 */
  int32_t  *sm = calloc(N+1,4);          /* smaller summand when r==1 */
  int32_t  *U  = malloc(sizeof(int32_t)*(N/8+1000));
  long K=0;
  U[K++]=1; U[K++]=2; r[3]=1; sm[3]=1;
  for(long n=3;n<=N;n++){
    if(r[n]==1){
      for(long i=0;i<K;i++){
        long m=n+U[i]; if(m>N) break;
        if(r[m]<2){ if(r[m]==0){ r[m]=1; sm[m]=U[i]; } else r[m]=2; }
      }
      U[K++]=n;
    }
  }
  /* outliers */
  long O=0; double minabs=1e9; long rec=0, maxout=0, nearwall=0;
  for(long i=0;i<K;i++){
    double ph=fmod(a*(double)U[i],TP); if(ph<0) ph+=TP;
    if(!(ph>LO && ph<HI)){
      O++; maxout=U[i];
      double d = ph<=M_PI ? ph : ph-TP;
      if(fabs(d)<minabs){ minabs=fabs(d); rec=U[i]; }
      if(fabs(d)>1.594) nearwall++;
    }
  }
  /* window */
  long W=0, small=0, feed2=0;
  long *cnt=calloc(N+1,sizeof(long));   /* usage count per feeder value */
  double lo_edge=0, hi_edge=TP;          /* hole edges: scan Ulam phases in M */
  double *ph_w=malloc(sizeof(double)*K); long nw=0;
  for(long i=0;i<K;i++){
    long u=U[i]; if(u< N/2) continue;
    W++; long f=sm[u];
    if(f<=100) small++;
    if(f==2) feed2++;
    cnt[f]++;
    double ph=fmod(a*(double)u,TP); if(ph<0) ph+=TP;
    ph_w[nw++]=ph;
  }
  /* hole = largest gap between consecutive sorted window-Ulam phases inside M */
  int cmp(const void*x,const void*y){ double p=*(const double*)x,q=*(const double*)y; return p<q?-1:(p>q); }
  qsort(ph_w,nw,sizeof(double),cmp);
  double best=0;
  for(long i=1;i<nw;i++){ double g=ph_w[i]-ph_w[i-1];
    if(g>best){ best=g; lo_edge=ph_w[i-1]; hi_edge=ph_w[i]; } }
  long F=0, big=0; for(long v=0;v<=N;v++) if(cnt[v]>0) F++;
  /* feeders needed to cover 90% of window */
  long *c2=malloc(sizeof(long)*(F>0?F:1)); long j=0;
  for(long v=0;v<=N;v++) if(cnt[v]>0) c2[j++]=cnt[v];
  int cmpl(const void*x,const void*y){ long p=*(const long*)x,q=*(const long*)y; return p<q?1:(p>q?-1:0); }
  qsort(c2,F,sizeof(long),cmpl);
  long acc=0, n90=0; for(long i=0;i<F;i++){ acc+=c2[i]; n90++; if(acc>=0.9*W) break; }
  printf("N=%ld K=%ld density=%.6f\n",N,K,(double)K/N);
  printf("O=%ld maxoutlier=%ld min|delta|=%.4f at %ld  nearwall(|d|>1.594)=%ld (%.3f)\n",
         O,maxout,minabs,rec,nearwall,(double)nearwall/O);
  printf("W=%ld F=%ld S=%.4f share_feeder2=%.4f n90=%ld\n",
         W,F,(double)small/W,(double)feed2/W,n90);
  printf("hole: %.4f to %.4f (width %.4f)\n",lo_edge,hi_edge,best);
  printf("top feeders:");
  for(long i=0;i<12 && i<F;i++) printf(" %ld",c2[i]);
  printf("\n");
  /* name the top feeders */
  printf("top feeder values:");
  for(long t=0;t<12 && t<F;t++){
    long want=c2[t], found=-1;
    for(long v=0;v<=N;v++) if(cnt[v]==want){ found=v; cnt[v]=-1; break; }
    printf(" %ld(%ld)",found,want);
  }
  printf("\n");
  return 0;
}
