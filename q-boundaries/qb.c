/* Q-sequence generation boundaries. Q(1)=Q(2)=1 to 2^27.
   Per octave g: D = Q(n) - n/2, RMS of D in linear bins of x = n/2^g (nb bins per unit x).
   Boundary = bin edge x in [1.30, 1.60] maximizing
   (mean RMS of the w bins after) / (mean RMS of the w bins before). An empty bin counts as RMS 0 (matters only at g6-g8
   with 0.002 bins; skipping empties instead gives 1.486 / 1.494 / 1.498 there).
   usage: qb nb gmin gmax w_lo w_mid w_hi g_mid g_hi
   (w = w_lo for g < g_mid, w_mid for g < g_hi, else w_hi)
   run 1: qb 500 6 26 8 4 2 12 18     run 2: qb 4000 18 26 16 16 16 99 99 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LOG 27
int main(int argc,char**argv){
  long nb=atol(argv[1]); int gmin=atoi(argv[2]), gmax=atoi(argv[3]);
  int w0=atoi(argv[4]), w1=atoi(argv[5]), w2=atoi(argv[6]), gm=atoi(argv[7]), gh=atoi(argv[8]);
  long N=1L<<LOG; int *Q=malloc(N*sizeof(int)); Q[1]=Q[2]=1;
  for(long n=3;n<N;n++) Q[n]=Q[n-Q[n-1]]+Q[n-Q[n-2]];
  double *ss=malloc(nb*sizeof(double)), *rms=malloc(nb*sizeof(double)); long *c=malloc(nb*sizeof(long));
  for(int g=gmin; g<=gmax && g<LOG; g++){
    int w = g<gm ? w0 : g<gh ? w1 : w2; long G=1L<<g;
    for(long k=0;k<nb;k++){ss[k]=0;c[k]=0;}
    for(long n=G;n<2*G;n++){ long k=(n-G)*nb/G; double d=Q[n]-n/2.0; ss[k]+=d*d; c[k]++; }
    for(long k=0;k<nb;k++) rms[k]= c[k] ? sqrt(ss[k]/c[k]) : 0;
    double best=0; long bk=-1;
    for(long k=(long)ceil(0.30*nb-1e-9); k<=(long)floor(0.60*nb+1e-9); k++){
      double a=0,b=0; int na=0,nbf=0;
      for(int j=0;j<w;j++){ if(k+j<nb){a+=rms[k+j];na++;} if(k-1-j>=0){b+=rms[k-1-j];nbf++;} }
      if(!na||!nbf||b==0) continue;
      double r=(a/na)/(b/nbf); if(r>best){best=r;bk=k;}
    }
    printf("g%2d w=%2d boundary x=%.5f jump %.2f\n", g, w, 1.0+(double)bk/nb, best);
  }
  return 0;
}
