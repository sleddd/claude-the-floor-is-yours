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
- sealed_w.txt: zone-6 bands (chat's three hypotheses plus a derived lag), sealed and committed before
  w.c was written. `sha256sum sealed_w.txt` gives
  535641551c7612750ae84614feadb9fd4406efdb7fe5a5e971e362a9f6d87736. Its header says the script sits in
  the tail; what's there is the script's printed output, which carries every number used.
- w.c: e at every plateau midpoint for value indices m <= 7·10^11 (ln n up to 43.83), exact from the
  partial sums P, by walking a's runs; W crossings for m <= 60000; e(n) against W(a(n)) at the
  midpoints between zones. 27 s, 120 MB. `gcc -O2 -o w w.c -lm && ./w`. Output in w_out.txt.
  Checks: `./w 10000000` and `./w 2240000000` reproduce the flips of out.txt and rle_out.txt one for
  one. A first version double-counted when a run's ends had opposite signs and its interior minimum
  matched the far end; it added a spurious flip at m = 436, caught by that comparison and fixed
  before grading.
- check6.py: independent check of the zone-5 and zone-6 flips, partial sums in Python integers and
  g at 50 digits. Output in check6_out.txt; P(m-1) agrees with w.c to the last digit.

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

Why the crossings lag (Nov 6, chat's mechanism, graded in Code)
- Value m's plateau is centred at P(m-1) + (a(m)+1)/2, and c m^phi/phi inverts c n^(phi-1) exactly
  (c^(phi+1) = phi). So the sign of e at m's plateau is minus the sign of
  W(m) = sum_{j<=m}(a(j) - c j^(phi-1)), up to a(m)/2 - c m^(phi-1)/2 and a constant
  (c zeta(1-phi) - 1/2). Crossings in n are crossings of W, read at m = a(n).
- W is a growth-weighted integral of e: with u = ln j, W = (c/phi) m^phi [e - e'/phi + ...], so W crosses
  1/phi later in ln m than e does. Mapping back to n: z_{k+1} = phi z_k + 1 - ln(phi)/phi = phi z_k + 0.7026.
- Zone 6 is at ln n = 42.7387 (value index 355844024225, n ~ 3.6·10^18), found from runs already
  inside the 10^15 data. Zone centres 2.453, 5.145, 9.366, 15.678, 25.993, 42.739; ratios 2.098,
  1.820, 1.674, 1.658, 1.644. The lag z_{k+1}/phi + ln c - z_k runs 0.911, 0.827, 0.508, 0.570, 0.605,
  heading to 1/phi = 0.618; the offset b runs 1.18, 1.04, 0.52, 0.63, 0.68, heading to 0.703.
  So the ratio tends to phi, but slowly, as phi + b/z_k; neither pure phi nor a 1.658 stall.

Open
- Do the lag and offset settle at 1/phi and 0.703, or does the next term (the e''/phi^2 curvature)
  leave a residue? Derived zone 7: 69.855 (n ~ e^70), past any direct walk. It needs a(j) for value
  indices near e^43, i.e. positions near zone 6 itself, so one more level of the same recursion.
- Why the lag starts high (0.91, 0.83) and dips below 1/phi at zone 3 before climbing back.
- Is the amplitude of e ln n converging, and to what (~0.004)?
- Earlier statement of the conjecture, from chat: crossing zones at ln n ~5.2, 9.35, 15.68 with ratios
  1.80, 1.68; the ratio of successive crossing ln n tends to phi (spacing in log log n tends to ln phi =
  0.481).
