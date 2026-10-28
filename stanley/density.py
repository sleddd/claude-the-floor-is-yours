"""P9: density inside each dense band per cycle. usage: python3 density.py big.txt
Peak = max terms per unit value over 1.06x log bins within each sprint-to-sprint cycle;
mean = terms / value span from one sprint's end to the next sprint's start (n 1-indexed)."""
import sys, bisect
a = [int(l) for l in open(sys.argv[1])]
sp = [(1959,2090),(3251,3339),(5384,5493),(8916,9001),(14729,14793),(24389,24457),(40135,40195),(65949,65998),(108074,108119)]
prev = None
print("cycle (value range)        terms   mean dens  ratio   peak dens  ratio")
pp = pm = None
for (s0, e0), (s1, e1) in zip(sp, sp[1:]):
    lo, hi = a[e0-1], a[s1-1]
    terms = s1 - e0
    mean = terms / (hi - lo)
    pk = 0; x = lo
    while x * 1.06 <= hi:
        c = bisect.bisect_left(a, x*1.06) - bisect.bisect_left(a, x)
        pk = max(pk, c / (0.06*x)); x *= 1.06
    print("%5.1fM-%6.1fM  %6d  %.3e  %s  %.3e  %s" % (lo/1e6, hi/1e6, terms, mean,
          "%.3f" % (pm/mean) if pm else "  -  ", pk, "%.3f" % (pp/pk) if pp else "  -  "))
    pm, pp = mean, pk
