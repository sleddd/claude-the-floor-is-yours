"""Turn 2 checks: bands, pair census, pressure scan, band density per cycle.
usage: python3 bands.py big.txt   (n 1-indexed)"""
import sys, math, random, bisect
a = [int(l) for l in open(sys.argv[1])]
S = set(a)
def reps(t):
    # pairs (x, b), x < b < t, both terms, 2b - x = t
    out = []
    for b in a[bisect.bisect_right(a, t // 2):bisect.bisect_left(a, t)]:
        x = 2*b - t
        if x in S: out.append((x, b))
    return out

print("density, 1.06x log bins from 50M (terms per 1e6 of value):")
lo = 50e6
while lo < a[-1]:
    hi = lo * 1.06
    c = bisect.bisect_left(a, hi) - bisect.bisect_left(a, lo)
    print("  %6.1fM-%6.1fM %6d  %.1f" % (lo/1e6, hi/1e6, c, c/(hi-lo)*1e6))
    lo = hi

random.seed(1)
skipped = []
while len(skipped) < 150:
    t = random.randrange(150_000_000, 175_000_000)
    if t not in S: skipped.append(t)
cnt = []; bin_b = 0; tot = 0; abands = {}
edges = [(0,7e6,"<7M"),(7e6,11e6,"7-11M"),(11e6,18e6,"11-18M"),(18e6,29e6,"18-29M"),(29e6,44e6,"29-44M"),(44e6,74e6,"44-74M"),(74e6,1e10,">=74M")]
for t in skipped:
    r = reps(t); cnt.append(len(r))
    for x, b in r:
        tot += 1; bin_b += 74e6 <= b < 112e6
        for l, h, name in edges:
            if l <= x < h: abands[name] = abands.get(name, 0) + 1
cnt.sort()
print("census: reps min %d median %d max %d; b in 74-112M %.3f" % (cnt[0], cnt[len(cnt)//2], cnt[-1], bin_b/tot))
print("  a bands:", " | ".join("%s %.3f" % (n, abands.get(n,0)/tot) for _,_,n in edges))

random.seed(2)
print("pressure scan (bin start M: mean reps, terms in bin, 6e6*exp(-p)):")
for lo in range(130, 227, 6):
    L, H = lo*10**6, (lo+6)*10**6
    ts = []
    while len(ts) < 60:
        t = random.randrange(L, H)
        if t not in S: ts.append(t)
    p = sum(len(reps(t)) for t in ts) / 60
    c = bisect.bisect_left(a, H) - bisect.bisect_left(a, L)
    print("  %d: %.1f, %d, %.0f" % (lo, p, c, 6e6*math.exp(-p)))
