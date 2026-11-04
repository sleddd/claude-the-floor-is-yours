# For each hub: traffic at 1e6, smallest start through it, that start's peak,
# where the hub sits on the path relative to the peak, and whether it is on 27's road.
import sys
N = 10**6
def step(x): return x // 2 if x % 2 == 0 else 3 * x + 1
def path(n):
    p = [n]
    while p[-1] != 1: p.append(step(p[-1]))
    return p
road27 = set(path(27))
hubs = [int(a) for a in sys.argv[1:]]
first = {}
for n in range(1, N + 1):
    p = path(n)
    s = set(p)
    for h in hubs:
        if h not in first and h in s: first[h] = n
    if len(first) == len(hubs): break
cnt = {h: 0 for h in hubs}
for n in range(1, N + 1):
    x = n
    seen = set()
    while True:
        if x in cnt: seen.add(x)
        if x == 1 or (x < n and False): break
        x = step(x)
    for h in seen: cnt[h] += 1
for h in hubs:
    n = first[h]; p = path(n); pk = max(p); i, j = p.index(h), p.index(pk)
    print(f"hub {h}: traffic {cnt[h]} ({cnt[h]/N:.4f}), on 27 road {h in road27}, smallest start {n}, its peak {pk}, "
          f"hub at step {i}, peak at step {j} ({'before' if i<j else 'after'} peak by {abs(j-i)}), hub/peak {h/pk:.3f}")
    print("   path around hub:", p[max(0,i-3):i+4])
