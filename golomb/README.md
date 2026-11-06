# Golomb's sequence (chat, Nov 5 2026)

OEIS A001462: a(1)=1, a(n+1) = 1 + a(n+1 - a(a(n))); a(n) is the number of times n appears.
a(n) ~ C n^(phi-1) with C = phi^(2-phi) = 1.201783. Error e(n) = a(n)/(C n^(phi-1)) - 1.

Files
- golomb.c: a(n) to 10^7, decade values, raw sign flips and max |e ln n| on [10^3, 10^7], and
  e at plateau midpoints (a plateau is a run of equal a(n); midpoint = (first+last)/2).
  `gcc -O2 -o golomb golomb.c -lm && ./golomb`, under a second. Output in out.txt.
- The predictions were sealed in chat (sha256 d2e11972...d581e4); the file is kept there.

Expected output (from chat): all reproduced exactly. a(10^7) = 25474, a(10^6) = 6137, midpoint
9995215 has e ln n = +0.00093, 11,990 raw flips on [10^3, 10^7], crossing zones at n ~ 87-338,
~10300-13244 and ~6.43e6. The first zone's flips start at midpoint 80 -> 87 and the second's at
10254.5 -> 10300.5; inside a zone e hovers at zero and flips several times (13, 11 and 3 flips).
There are also two flips below 14, before the zones settle.

Open (from chat)
- At plateau midpoints e(n) is a slow wave. Zone centres sit at ln n ~ 5.2, 9.35, 15.68; successive
  ratios 1.80, 1.68. Conjecture: the ratio of successive crossing ln n tends to phi (equivalently,
  the spacing in log log n tends to ln phi = 0.481). Next crossing near ln n ~ 25.4 (n ~ 10^11),
  out of reach of a flat array; it needs a run-length encoding of a, which is itself tiny (a(10^11)
  ~ 1.1·10^7).
