# 728 follow-up (Nov 12 2026). See sealed2.txt. python3 inverse728.py (~10 s)
# Baselines: median A(w), w == r mod m, floor(r/1.5) <= w <= 1.5r, w != r.
# "path kept" leaves 27's climb values in the window (chat's addendum run);
# "path out" drops them (sealed.txt, as run in side.c).
import statistics as st
N = 10**6; W = 32768; A = [0] * W
for n in range(1, N + 1):
    x = n
    while True:
        if x < W: A[x] += 1
        if x == 1: break
        x = 3 * x + 1 if x & 1 else x // 2
path = [27]
while path[-1] != 9232:
    x = path[-1]; path.append(3 * x + 1 if x & 1 else x // 2)
P = set(path)

def base(r, m=27, keep_path=False):
    ws = [w for w in range(int(r / 1.5), 3 * r // 2 + 1)
          if w % m == r % m and w != r and (keep_path or w not in P)]
    return st.median([A[w] for w in ws]) if ws else None

def ratio(r, **kw):
    b = base(r, **kw); return A[r] / b if b else None

def preds(v):  # predecessors whose window fits under W
    out = [2 * v] + ([(v - 1) // 3] if v % 6 == 4 and v > 4 else [])
    return [u for u in out if 3 * u // 2 < W]

def fmt(x): return "  -  " if x is None else f"{x:5.2f}"

v = 728; walk = [v]
for _ in range(10):
    v = max(preds(v), key=lambda u: A[u]); walk.append(v)
print("heaviest-predecessor walk from 728")
print("    w      A   base27(kept) ratio | base27(out) ratio | ratio54(kept) ratio54(out)")
for w in walk:
    print(f"{w:5d} {A[w]:6d} {base(w, keep_path=True):11.1f} {fmt(ratio(w, keep_path=True))} |"
          f" {base(w):10.1f} {fmt(ratio(w))} | {fmt(ratio(w, m=54, keep_path=True)):>12} {fmt(ratio(w, m=54)):>10}")

print("\ninverse tree of 728, depth 1..10 (nodes with 1.5u < 32768)")
lvl = [728]; tree = []
for d in range(1, 11):
    lvl = [u for v in lvl for u in preds(v)]
    tree += [(u, d) for u in lvl]
print("nodes:", len(tree))
for m in (27, 54):
    for kp in (True, False):
        rs = sorted(((ratio(u, m=m, keep_path=kp), u, d) for u, d in tree if ratio(u, m=m, keep_path=kp)), reverse=True)
        above3 = [(u, d, round(r, 2)) for r, u, d in rs if r > 3]
        odd = [(u, d, round(r, 2)) for r, u, d in rs if u % 2][:3]
        print(f"mod {m}, path {'kept' if kp else 'out '}: ratio>3 {above3}; best odd {odd}")

print("\nfirst test, parity-matched (mod 54, path out)")
rat = []; sb = 0; npath = sum(1 for i, v in enumerate(path) if i > 0)
for i, v in enumerate(path):
    if i == 0 or v % 2: continue
    c = [2 * v] + ([(v - 1) // 3] if v % 6 == 4 else [])
    r = [u for u in c if u != path[i - 1]]
    if not r: continue
    r = r[0]; b = base(r, m=54)
    if b: rat.append(A[r] / b); sb += b
    if r == 728: print(f"728: base {b}, ratio {A[r] / b:.2f}")
rat.sort()
print(f"roots {len(rat)}, median {st.median(rat):.2f}, frac>2 {sum(x > 2 for x in rat) / len(rat):.3f}, "
      f"counterfactual road share {(sb + npath) / N:.4f}")
