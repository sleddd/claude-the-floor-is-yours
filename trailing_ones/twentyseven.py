import numpy as np, struct

def tones(n): return ((n+1) & -(n+1)).bit_length()-1

def profile(n0):
    x, ts = n0, []
    while x != 1:
        ts.append(tones(x))
        x = 3*x+1
        x >>= (x & -x).bit_length()-1
    return ts

ts27 = profile(27)
print("27: odd steps =", len(ts27))
print("27: t sequence =", ts27)
fresh27 = [ts27[i] for i in range(len(ts27)) if i == 0 or ts27[i-1] <= 1]
print("27: fresh t values =", fresh27, " count =", len(fresh27))
print("27: max t =", max(ts27), " count t>=4 =", sum(1 for t in ts27 if t >= 4),
      " mean t = %.4f" % (sum(ts27)/len(ts27)))
v1 = sum(t-1 for t in fresh27 if t > 1)
print("27: v1 steps total =", v1, " biggest run contributes", max(fresh27)-1,
      "= %.3f" % ((max(fresh27)-1)/v1))

# peak
x, pk = 27, 27
while x != 1:
    x = 3*x+1; x >>= (x & -x).bit_length()-1
    pk = max(pk, x)
print("27: peak =", pk)

# ---- length-matched population from the C dump ----
with open("per_start.bin","rb") as f:
    n, = struct.unpack("Q", f.read(8))
    odd_steps = np.frombuffer(f.read(4*n), dtype=np.uint32)
    maxt      = np.frombuffer(f.read(4*n), dtype=np.uint32)
    cnt4      = np.frombuffer(f.read(4*n), dtype=np.uint32)
    meant     = np.frombuffer(f.read(4*n), dtype=np.float32)
    peakratio = np.frombuffer(f.read(8*n), dtype=np.float64)
    v1big     = np.frombuffer(f.read(4*n), dtype=np.uint32)
print("\nstarts loaded:", n, " (odd n = 2*index+1)")

L = len(ts27)
sel = (odd_steps >= L-2) & (odd_steps <= L+2)
print("length-matched band %d..%d : %d starts" % (L-2, L+2, sel.sum()))
for name, arr, val in (("max t", maxt, max(ts27)),
                       ("count t>=4", cnt4, sum(1 for t in ts27 if t>=4)),
                       ("mean t", meant, sum(ts27)/len(ts27))):
    a = arr[sel]
    pct = (a < val).mean()*100
    print("  %-11s 27=%-8s matched mean=%.3f  p10=%.3f p90=%.3f  27 at %.1f pct"
          % (name, round(val,3), a.mean(), np.percentile(a,10), np.percentile(a,90), pct))

# D4: share of length-matched starts with max t >= 6
print("\nD4 check: share of %d-odd-step starts with max t >= 6 : %.4f  (predicted 0.47)"
      % (L, (maxt[sel] >= 6).mean()))
print("  share over ALL starts with max t >= 6 : %.4f" % (maxt >= 6).mean())
print("  mean odd steps over all starts: %.2f" % odd_steps.mean())

# how rare is 27 overall?
print("\n27's peak/n ratio = %.1f ; share of starts with higher ratio = %.6f"
      % (pk/27, (peakratio > pk/27).mean()))

# X3: top 1% by peak/n
thr = np.percentile(peakratio, 99)
top = peakratio >= thr
print("\nX3: top 1%% by peak/n (n=%d)" % top.sum())
print("  mean t  : top1%% = %.4f   all = %.4f   diff = %+.4f (predicted >= +0.30)"
      % (meant[top].mean(), meant.mean(), meant[top].mean()-meant.mean()))
# length-matched comparison for max t
print("  mean max t: top1%% = %.3f   all = %.3f   diff = %+.3f"
      % (maxt[top].mean(), maxt.mean(), maxt[top].mean()-maxt.mean()))
# match top1% on length
import collections
cnt = collections.Counter(odd_steps[top].tolist())
tot_m, tot_w = 0.0, 0
for L2, w in cnt.items():
    m = odd_steps == L2
    if m.sum() == 0: continue
    tot_m += maxt[m].mean()*w; tot_w += w
print("  mean max t, length-matched baseline = %.3f  diff = %+.3f (predicted >= +1.0)"
      % (tot_m/tot_w, maxt[top].mean()-tot_m/tot_w))
