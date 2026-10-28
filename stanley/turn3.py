"""Turn 3 checks: sprints with n counted from a(0), span ratio, per-cycle V, r, c.
The sprint ends at the first i with a(i+30)/a(i) <= 1.02; its end value is a(i+30).
usage: python3 turn3.py big2.txt
c solves r^2 = V * (ln n1 / ln n0)^c, with r = n1/n0 and V = a(n1)/a(n0)."""
import sys, math
a = [int(l) for l in open(sys.argv[1])]
N = len(a)
print("a(119999) [line 120000] =", a[119999], " a(184999) [line 185000] =", a[184999])
sp = []; i = 50
while i + 30 < N:
    if a[i+30] / a[i] > 1.08:
        s = i
        while i + 30 < N and a[i+30] / a[i] > 1.02: i += 1
        sp.append((s, a[s], a[i+30]))  # end value = far edge of the last window
    i += 1
print("sprints (n from a(0), a(n), end value, span ratio):")
for s, v, e in sp: print("  %7d %11d %11d %.3f" % (s, v, e, e / v))
print("cycles (n0 -> n1: V, r, c):")
for (n0, v0, _), (n1, v1, _) in zip(sp, sp[1:]):
    V, r = v1 / v0, n1 / n0
    c = math.log(r*r / V) / math.log(math.log(n1) / math.log(n0))
    print("  %6d -> %6d: V %.4f  r %.4f  c %.3f" % (n0, n1, V, r, c))
n1 = sp[-1][0]
print("offset of last start from 176775: %+.2f%%" % (100 * (n1 / 176775 - 1)))
# formula check: n1 from V = 2.54, c = 1.25, n0 = 108073
n0, x = 108073, 108073 * 1.6
for _ in range(100): x = n0 * math.sqrt(2.54 * (math.log(x) / math.log(n0)) ** 1.25)
print("formula n1 = %.1f" % x)
