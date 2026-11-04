# Mean and median v*share by class at N=10^9 per octave, and path values per start per octave.
# Needs band_out.txt from band.c. Output in means_out.txt.
import collections, statistics as st, math
tr = collections.defaultdict(dict)
for line in open("band_out.txt"):
    N, v, t = map(int, line.split()); tr[N][v] = t
N = 10**9; d = tr[N]
cl = {"4mod6": lambda v: v % 6 == 4, "2mod6": lambda v: v % 6 == 2, "odd": lambda v: v % 2 and v % 3}
for lo, hi in [(1024, 2048), (4096, 8192), (5000, 20000), (8192, 16384), (16384, 32768), (30000, 60000)]:
    m = {c: st.mean(v * d[v] / N for v in range(lo, hi) if f(v)) for c, f in cl.items()}
    md = {c: st.median(v * d[v] / N for v in range(lo, hi) if f(v)) for c, f in cl.items()}
    oc = sum(d[v] for v in range(lo, hi)) / N * math.log(2) / math.log(hi / lo)
    print(f"[{lo},{hi}) mean c4 {m['4mod6']:.2f} c2 {m['2mod6']:.2f} odd {m['odd']:.2f} | c2/c4 {m['2mod6']/m['4mod6']:.4f} "
          f"odd/c4 {m['odd']/m['4mod6']:.4f} | median ratios {md['2mod6']/md['4mod6']:.3f} {md['odd']/md['4mod6']:.3f} | values/start/octave {oc:.3f}")
