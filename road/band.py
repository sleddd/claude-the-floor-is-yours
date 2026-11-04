# Analysis of band_out.txt: conservation, drift of every window value 10^6 -> 10^9, v*share bands.
import statistics as st, collections
tr = collections.defaultdict(dict)
for line in open("band_out.txt"):
    N, v, t = map(int, line.split()); tr[N][v] = t
Ns = sorted(tr); M = 60000
# 1. conservation: t(v) = [v<=N] + t(2v) + t((v-1)/3) when v = 4 mod 6
bad = 0
for N in Ns:
    for v in range(2, M // 2 + 1):
        rhs = (v <= N) + tr[N][2 * v] + (tr[N][(v - 1) // 3] if v % 6 == 4 else 0)
        bad += rhs != tr[N][v]
print("conservation violations (v <= 30000, all N):", bad)
W = range(5000, 20001)
cls = lambda v: "0mod3" if v % 3 == 0 else ("4mod6" if v % 6 == 4 else ("odd" if v % 2 else "2mod6"))
# 2. drift: share at 1e9 / share at 1e6, per class
lo, hi = Ns[0], Ns[-1]
print(f"\ndrift, share({hi:.0e}) / share({lo:.0e}) over [5000,20000]:")
for c in ["0mod3", "4mod6", "odd", "2mod6"]:
    r = [(tr[hi][v] / hi) / (tr[lo][v] / lo) for v in W if cls(v) == c]
    q = st.quantiles(r, n=100)
    print(f"  {c:6s} n={len(r):5d} median {st.median(r):.3f}  p1 {q[0]:.3f}  p99 {q[98]:.3f}  min {min(r):.3f}  max {max(r):.3f}")
nz = [(v, (tr[hi][v] / hi) / (tr[lo][v] / lo)) for v in W if cls(v) != "0mod3"]
nz.sort(key=lambda p: p[1])
print("  most-drifting non-0mod3, low :", [(v, round(r, 3), tr[lo][v]) for v, r in nz[:5]])
print("  most-drifting non-0mod3, high:", [(v, round(r, 3), tr[lo][v]) for v, r in nz[-5:]])
big = [(v, r) for v, r in nz if tr[lo][v] >= 1000]
print(f"  among values with traffic >= 1000 at 1e6 (n={len(big)}): ratio range {min(r for _,r in big):.3f} .. {max(r for _,r in big):.3f}")
# 3. bands: v * share at 1e9
print(f"\nv * share at N={hi:.0e}, [5000,20000], by class:")
vs = {v: v * tr[hi][v] / hi for v in W}
for c in ["0mod3", "4mod6", "odd", "2mod6"]:
    a = [vs[v] for v in W if cls(v) == c]
    q = st.quantiles(a, n=10)
    print(f"  {c:6s} median {st.median(a):8.3f}  p10 {q[0]:8.3f}  p90 {q[8]:8.3f}  max {max(a):9.2f}")
for v in [9232, 6154, 7288, 5536, 11072, 7381, 9841, 13120]:
    band = st.median([vs[u] for u in W if cls(u) == cls(v)])
    print(f"  {v:6d} {cls(v):6s} v*share {vs[v]:9.2f}  band median {band:7.3f}  x{vs[v]/band:7.1f}")
top = sorted(W, key=lambda v: -vs[v] / st.median([vs[u] for u in W if cls(u) == cls(v)]) if False else -vs[v])[:12]
print("  top v*share in window:", [(v, round(vs[v], 1)) for v in top])
