# Collatz traffic (standard map: n/2, 3n+1) for starts 1..N.
# traffic(v) = number of starts n<=N whose trajectory visits v (n itself included).
import sys, statistics
N = int(sys.argv[1]) if len(sys.argv) > 1 else 10**6
parent = {1: 0}
for n in range(2, N + 1):
    x = n
    while x not in parent:
        y = x // 2 if x % 2 == 0 else 3 * x + 1
        parent[x] = y
        x = y
print("nodes", len(parent))
depth = {1: 0}
def d(x):
    stack = []
    while x not in depth:
        stack.append(x); x = parent[x]
    k = depth[x]
    for y in reversed(stack):
        k += 1; depth[y] = k
    return k
for v in parent: d(v)
order = sorted(parent, key=lambda v: -depth[v])
t = {v: (1 if v <= N else 0) for v in parent}
for v in order:
    if v != 1: t[parent[v]] += t[v]
print("share(9232) %.6f" % (t[9232] / N))
road = []; x = 27
while True:
    road.append(x)
    if x == 1: break
    x = x // 2 if x % 2 == 0 else 3 * x + 1
roadset = set(road)
win = sorted((v for v in t if 5000 <= v <= 20000), key=lambda v: -t[v])
print("window top", [(v, t[v]) for v in win[:5]])
off = [v for v in win if v not in roadset][0]
print("best off-road", off, "%.6f" % (t[off] / N), "| on-road in window:", sorted(v for v in road if 5000 <= v <= 20000))
def meds(vals, label):
    a = [t[v] for v in vals if v % 3 == 0]
    b = [t[v] for v in vals if v % 6 == 4]
    c = [t[v] for v in vals if v % 3 != 0 and v % 6 != 4]
    ma, mb, mc = statistics.median(a), statistics.median(b), statistics.median(c)
    print(f"medians [{label}] 0mod3={ma} (n={len(a)}) 4mod6={mb} (n={len(b)}) other={mc} (n={len(c)}) ratio={ma/mb:.5f}")
meds(list(t), "all visited")
meds([v for v in t if 5000 <= v <= 20000], "window")
meds([v for v in t if v <= N], "v<=N")
ev = [v for v in road if v % 2 == 0]
r27 = sum(v % 6 == 4 for v in ev) / len(ev)
print(f"27 even values: {len(ev)}, 4mod6 rate {r27:.4f}")
for label, vals in [("all visited", list(t)), ("window", [v for v in t if 5000 <= v <= 20000]), ("v<=N", [v for v in t if v <= N])]:
    e = [v for v in vals if v % 2 == 0]
    w = sum(t[v] for v in e); w4 = sum(t[v] for v in e if v % 6 == 4)
    print(f"traffic-weighted 4mod6 rate among evens [{label}]: {w4/w:.4f}")
# per-step weighting: over all trajectories' even steps (= traffic-weighted over all visited evens)
