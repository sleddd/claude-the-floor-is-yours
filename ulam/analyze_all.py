import numpy as np
from collections import Counter
N=1000000; a=2.5714474995; TP=2*np.pi
r=np.fromfile("r.bin",dtype=np.uint32); sm=np.fromfile("sm.bin",dtype=np.int32)
U=np.fromfile("U.bin",dtype=np.int32)
isU=np.zeros(N+1,bool); isU[U]=True
print("K =",len(U)," cos>=0:",[int(u) for u in U if np.cos(a*u)>=0])
w=np.arange(N//2,N+1); th=(a*w)%TP; rw=r[w]; uw=isU[w]; tu=th[uw]
print("window mean r = %.2f" % rw.mean())
print("window Ulam in middle third = %.4f" % ((tu>TP/3)&(tu<2*TP/3)).mean())
edges=np.arange(0,TP+0.05,0.05); b=np.digitize(th,edges)-1
nb=len(edges)-1
share=np.array([uw[b==i].mean() for i in range(nb)])
mr=np.array([rw[b==i].mean() for i in range(nb)])
print("max mean r bin lo = %.2f" % edges[np.argmax(mr)])
zero=[edges[i] for i in range(nb) if 2.1<edges[i]<4.15 and share[i]==0]
print("empty bins inside middle third: %.2f to %.2f" % (min(zero), max(zero)+0.05))
h=(th>3.10)&(th<3.48)
print("theta in (3.10,3.48): Ulam share %.4f, non-Ulam with r=0 %.4f" % (uw[h].mean(), (rw[h&~uw]==0).mean()))
W=U[U>=N//2]; tw=(a*W)%TP; s=sm[W]
print("smaller summand <=100: %.4f" % (s<=100).mean())
lo=(tw>2.6)&(tw<3.05); up=(tw>3.53)&(tw<3.80)
print("(2.6,3.05) summand==2: %.4f" % (s[lo]==2).mean())
print("(3.53,3.80) summand in {3,47,69}: %.4f" % np.isin(s[up],[3,47,69]).mean())
print("lower lobe (theta<3.29) share: %.4f" % (tw<3.29).mean())
ph=(a*U)%TP; out=~((ph>TP/3)&(ph<2*TP/3))
print("outside-middle-third Ulam <=1e6:",out.sum(),"; distinct feeders in window:",len(set(s.tolist())),
      "; all feeders outside:", set(s.tolist())<=set(U[out].tolist()))
