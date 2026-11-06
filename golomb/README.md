# Golomb's sequence (chat, Nov 5 2026)

OEIS A001462: a(1)=1, a(n+1) = 1 + a(n+1 - a(a(n))); a(n) is the number of times n appears.
a(n) ~ C n^(phi-1) with C = phi^(2-phi) = 1.201783. Error e(n) = a(n)/(C n^(phi-1)) - 1.

Files
- golomb.c: a(n) to 10^7, decade values, raw sign flips and max |e ln n| on [10^3, 10^7], and
  e at plateau midpoints (a plateau is a run of equal a(n); midpoint = (first+last)/2).
  `gcc -O2 -o golomb golomb.c -lm && ./golomb`, under a second. Output in out.txt.
- The predictions were sealed in chat (sha256 d2e11972...d581e4); the file is kept there.
- sealed_rle.txt: Q1-Q4 for the run to 10^15, sealed and committed in Code before rle.c was written.
  `sha256sum sealed_rle.txt` gives d2fc8c8ef56e64de222620ba6cc97c6d8f0186895af46aea794e53c79486fed3.
  Constants and thresholds in it were computed in the sealing step, not typed.
- rle.c: plateau midpoints to positions 10^15 by run length. Value k fills S(k-1)+1..S(k), and a(k)
  is read off the runs of a flat table to 10^7. ~2.3·10^9 plateaus, 4 minutes, 40 MB.
  `gcc -O2 -o rle rle.c -lm && ./rle` (optional argument: max position). Output in rle_out.txt.
  Checks: `./rle 10000000` reproduces out.txt's 27 flips and +0.00093 at 9995215; a flat array
  agrees at a(10^8) = 105729 and a(10^9) = 438744.

Expected output (from chat): all reproduced exactly. a(10^7) = 25474, a(10^6) = 6137, midpoint
9995215 has e ln n = +0.00093, 11,990 raw flips on [10^3, 10^7], crossing zones at n ~ 87-338,
~10300-13244 and ~6.43e6. The first zone's flips start at midpoint 80 -> 87 and the second's at
10254.5 -> 10300.5; inside a zone e hovers at zero and flips several times (11, 11 and 3 flips; first written as 13, 11, 3,
corrected Nov 6).
There are also two flips below 14, before the zones settle.

Run to 10^15 (Nov 6)
- Exactly one new zone: a single flip at ln n = 25.993 (n ~ 1.9·10^11). Zone centres 2.453, 5.145,
  9.366, 15.678, 25.993; ratios 2.098, 1.820, 1.674, 1.658. Distance from phi 0.48, 0.20, 0.056, 0.040.
- Half-wave maxima of |e ln m|: 0.0507, 0.0195, 0.0084, 0.0048, 0.0043. Successive ratios 0.38, 0.43,
  0.57, 0.89: the decay is flattening, which fits e ln n settling to a fixed amplitude.
- Decade values: e ln n is +0.0041 at 10^8, +0.0008 at 10^11, -0.0042 at 10^14.

Open
- Does the ratio go to phi? The last step closed the gap only from 0.056 to 0.040 (after 0.48 -> 0.20
  -> 0.056), which fits a limit near 1.65 about as well as phi. The next zone settles it: 25.993*phi =
  42.06 against 25.993*1.658 = 43.09, i.e. n ~ 2·10^18 vs 5·10^18. rle.c would need ~2·10^11 plateaus
  there (hours); the per-plateau expl is the cost to cut.
- Is the amplitude of e ln n converging, and to what (~0.004)?
- Earlier statement of the conjecture, from chat: crossing zones at ln n ~5.2, 9.35, 15.68 with ratios
  1.80, 1.68; the ratio of successive crossing ln n tends to phi (spacing in log log n tends to ln phi =
  0.481).
