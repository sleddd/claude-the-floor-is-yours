"""Checks for stanley/ (Oct 27 2026). usage: python3 analyze.py big.txt
n is 1-indexed: a(1)=0, a(2)=4."""
import sys, math, random, bisect
a = [int(l) for l in open(sys.argv[1])]
A = lambda n: a[n-1]
N = len(a)

print("a(40000) =", A(40000), " a(120000) =", A(120000))

# sprint detector
starts = []; i = int(sys.argv[2]) if len(sys.argv) > 2 else 1000
while i + 30 <= N:
    if A(i+30) / A(i) > 1.08:
        s = i
        while i + 30 <= N and A(i+30) / A(i) > 1.02: i += 1
        starts.append((s, A(s), i))
    i += 1
print("sprints (start n, a(n), end n):")
for s in starts: print("  ", s)
print("index ratios", " ".join("%.3f" % (starts[k+1][0]/starts[k][0]) for k in range(len(starts)-1)))
print("value ratios", " ".join("%.3f" % (starts[k+1][1]/starts[k][1]) for k in range(len(starts)-1)))
print("a ln n/n^2 at starts", " ".join("%.4f" % (v*math.log(n)/n**2) for n, v, _ in starts))

# P1, P2: a ln n/n^2 and a/n^2 over 10^3..3*10^4 (1-2-5-ish grid and every 1000)
print("n  a(n)  a/n^2  a*ln n/n^2")
for n in [1000,1500,2000,3000,4000,5000,6000,7000,8000,10000,12000,15000,20000,25000,30000]:
    v = A(n); print(n, v, "%.4f" % (v/n**2), "%.4f" % (v*math.log(n)/n**2))
grid = range(1000, 30001, 100)
r = [A(n)/n**2 for n in grid]
print("a/n^2 on step-100 grid 1e3..3e4: rises %d, falls %d" % (sum(r[k+1]>r[k] for k in range(len(r)-1)), sum(r[k+1]<r[k] for k in range(len(r)-1))))
# sprint-start (same phase) values in range
print("a/n^2 at sprint starts:", " ".join("%d:%.4f" % (n, v/n**2) for n, v, _ in starts))

# P3: local exponent near 3e4 for several windows
for w in [100, 500, 1000, 2000, 5000, 10000]:
    n1, n2 = 30000 - w//2, 30000 + w//2
    print("local exponent at 3e4, window %5d: %.3f" % (w, math.log(A(n2)/A(n1))/math.log(n2/n1)))
for n1, n2 in [(14728, 24388), (24388, 40134), (10000, 30000), (20000, 40000), (15000, 60000)]:
    print("exponent %d..%d: %.3f" % (n1, n2, math.log(A(n2)/A(n1))/math.log(n2/n1)))
