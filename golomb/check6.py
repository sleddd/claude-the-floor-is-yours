# independent exact check of the zone-5 and zone-6 flips: P by two-level run sums in Python integers,
# g at 50 digits. a(j) = v on v's run; v's run has length a(v); a(v) = w on w's run (length a(w)).
from array import array
from decimal import Decimal as D, getcontext
import sys
getcontext().prec = 50
T = 22000000
a = array('i', [0, 1]) ; a.extend([0] * (T - 1))
for n in range(1, T - 1): a[n + 1] = 1 + a[n + 1 - a[a[n]]]
def P_and_v(m):           # P(m-1), a(m)
    P = 0; J0 = 1; v = 1
    while True:
        L = a[v]
        if J0 + L - 1 >= m: return P + v * (m - J0), v
        P += v * L; J0 += L; v += 1
phi = (1 + D(5).sqrt()) / 2; ex = phi - 1; c = ((2 - phi) * phi.ln()).exp()
for m in (11392035, 11392036, 355844024224, 355844024225):
    P, v = P_and_v(m)
    mid = D(P) + D(v + 1) / 2
    g = D(m) - c * (ex * mid.ln()).exp()
    print(m, "a(m) =", v, "P(m-1) =", P, "ln mid = %.4f" % float(mid.ln()), "g = %.4e" % g)
