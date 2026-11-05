# road: traffic on the standard Collatz map (chat, Nov 4 2026)

Standard map (n/2, 3n+1), starts 1..10^6. traffic(v) = number of starts whose path visits v,
the start itself included. Method: parent map of every visited value (2,168,611 nodes), depth
to 1, then start counts summed up the tree in descending depth.

Files
- road.py: share(9232), top traffic in [5000, 20000], best value off 27's road, medians by
  residue class, 27's 4 mod 6 rate among its even values against the traffic-weighted rate.
  `python3 road.py` (~8 s). Output in road_out.txt.
- scale.c: shares of 9232, 39364, 9841, 7381, 5536, 13120 at 10^4..10^9, see below.
- band.c: traffic(v) for every v <= 60000 at N = 10^6..10^9 (each start's first entry at or
  below 60000, then one walk per entry value). `gcc -O2 -o band band.c && ./band 1000000000 > band_out.txt`
  (~25 s, 2 GB; band_out.txt is 3.5 MB and not committed). Its 10^6 and 10^8 rows match road.py and scale.c.
- band.py: conservation check, drift of every window value 10^6 -> 10^9, v * share by residue class.
  Output in band_analysis.txt.
- sealed_means.txt: M1-M4, sealed in Code before means.py ran (sha256 d39a0c79...6d41774d).
- means.py: mean and median v * share by class per octave at 10^9, and path values per start
  per octave. Needs band_out.txt. Output in means_out.txt.
- sealed_parity.txt: H1, S1-S3, sealed in Code before parity.c ran (sha256 3f940fc1...30b51d1a).
  H1 is chat's, stated unsealed in chat and copied in.
- parity.c: in-octave parity, values per start and count x |drift| for [16384, 32768), by start
  bit length. 10^7 sampled starts in [1, 10^9]. `gcc -O2 -o parity parity.c -lm && ./parity 10000000`
  (~6 s). Output in parity_out.txt.
- parity2.c: the same per octave 2^6..2^26. Output in parity2_out.txt.
- sealed_board.txt: H2, C1-C4, sealed in Code before board.c ran (sha256 38bdba06...eb124cd4f).
  H2 is chat's, stated unsealed in chat and copied in.
- board.c: values per start in octaves 2^12..2^21, split by how a path meets 27's climb (27..9232):
  free (never), high (first climb value is 9232), low (boards lower on the climb). The part after
  boarding is 27's fixed path, added per boarding value. `gcc -O2 -o board board.c && ./board 10000000`
  (~8 s). Output in board_out.txt. A first version used all of 27's path as the road, so everyone
  "boarded" at 40 or 16; fixed before scoring.
- hubs.py: for given values, traffic at 10^6, smallest start through each, and where it sits
  relative to that start's peak. `python3 hubs.py 5536 7381 9841 13120 39364`. Output in hubs_out.txt.

Sealed predictions: chat gave sealed.txt sha256 d8f9b871af3c604dd6336cd07783eeb3a5f6836dffee305c6078cf9d762ceb59.
The file itself wasn't in the block (only abbreviated P1-P5 lines, which don't hash to it), so the
hash is recorded as given, not reproduced.

Expected output (from chat): all reproduced exactly. The residue-class medians are over values
in [5000, 20000] (0mod3 7, 4mod6 1219, other 474). Over all visited values they are 1 / 3 / 4,
over values <= 10^6 they are 1 / 26 / 8. The 0.6621 average is traffic-weighted over all visited
even values; over the window it is 0.6888, over values <= 10^6 0.6533.

Open (from chat), answered in Code: are 5536, 7381, 9841 just below the peaks of the next-tallest
early climbs? Not three peaks: one. All three sit on the same descent, a few steps after the peak
of 447's climb, 39364 (smallest start reaching each of them is 447):
39364 -> 19682 -> 9841 -> 29524 -> 14762 -> 7381 -> 22144 -> 11072 -> 5536.
9841 is 2 steps after the peak (= peak/4), 7381 5 steps, 5536 8 steps. Traffic grows down the
road as starts board: 39364 25682, 9841 25684, 7381 28784, 5536 28885. So the runner-ups are a
second road, not separate hubs. Among the record climbs that avoid 9232 (127 -> 4372,
255 -> 13120, 447 -> 39364, 703 -> 250504, 1819 -> 1276936), only 447's feeds the window's
runner-ups; 255's peak 13120 carries 0.91%, and 703 and 1819 pass none of these values.
Scale test (scale.c, `gcc -O2 -o scale scale.c && ./scale 1000000000`, ~1 min, 1 GB; output in
scale_out.txt; its 10^6 row matches road.py exactly): the second road holds. 5536's share is 0.0273,
0.0294, 0.0289, 0.0290, 0.0290, 0.0291 at 10^4..10^9; 9232's is 0.4011, 0.3899, 0.3941, 0.3935,
0.3931, 0.3930. 13120 (0.9%) holds too.

Flow and bands (band.c / band.py, chat's follow-up, Nov 4 2026):
- Conservation: traffic(v) = [v <= N] + traffic(2v) + traffic((v-1)/3 if v = 4 mod 6) holds for
  every v <= 30000 at every N, except v = 4, whose parent 1 is the root, not a child.
- 0 mod 3 values have no odd ancestor anywhere, so the backward tree is v, 2v, 4v, ...:
  log2(N/v) + 1 starts, share -> 0 (ratio 0.002 from 10^6 to 10^9). The 1e6 median of 7 was this.
- Every other value in [5000, 20000] keeps its share. Median ratio 10^9/10^6 is 1.005-1.008 by class;
  the extremes (0.55, 1.63) are values with 36-107 starts at 10^6. For the 3428 values with
  >= 1000 starts at 10^6, the p1-p99 spread per decade narrows: 0.935-1.085, 0.975-1.028,
  0.991-1.014. They converge; nothing drifts.
- 1/v is the right scale: median v * share is flat from 1000 to 60000 within each class, at about
  14.3 (4 mod 6), 7.3 (2 mod 6), 5.0 (odd, not 0 mod 3). The bands are wide, though: p10-p90 is
  3.4-53 for 4 mod 6, a factor of ~15 within a class.
- Above the band at 10^9: 9232 x253, 7288 x186, 6154 x169, 9841 x51, 11072 x44, 7381 x43,
  5536 x11, 13120 x8.

Band ratios and level (chat's derivation + Code's level, scored in the ledger): from conservation,
c2 = c4/2 and c_odd = 3 c4/8; the three balance equations are consistent but one-parameter (scale
free), and without the dead 0 mod 3 third they don't balance at 1/v (11 c4/8 != c4). The level
comes from the shortcut map's drift: 1.5 values visited per step, -0.2075 bits per step, ~7.23
values per octave = (3 c4/8) ln 2, so c4 ~ 27.8. Measured means at 10^9 in [16384, 32768):
c4 26.92, c2 13.42, odd 10.22; ratios 0.499 and 0.379; 7.01 values per octave. Octaves at and
below 9232's are lumpy (the big roads dominate class means): [1024, 2048) gives 0.29 / 0.27.

In-octave parity (chat's hypothesis H1, scored in the ledger): [16384, 32768) is odd-rich, not
odd-poor: p = 0.506. The in-octave odd share isn't the walk's parity. An odd value in the top 0.585
bits of an octave sends its forced even 3n+1 above it, so the window keeps the odd and loses its
partner; and up-jumps leave and re-enter, so count x |in-octave drift| is 0.919, not 1. Per octave
(parity2): 2^8..2^12, where 27's road runs, have counts 8.2-10.4 and p from 0.36 to 0.86, the road's
own parities. Clean octaves 2^19..2^24 have p 0.498-0.502 and counts 7.11-7.17, about 7.16-7.2 once
starts below each octave are allowed for: within ~1% of 7.23. The 2-4% gap is local to 2^13..2^18,
the stretch just above 27's road (7.01-7.10).

Boarding split (chat's H2, scored in the ledger): high boarders, which arrive by the forced chain
147712 -> 73856 -> 36928 -> 18464 -> 9232 (36928's odd parent 12309 is 0 mod 3), are 0.02% of
road-bound starts and touch 2^14 exactly once. They carry none of the shortfall. Low boarders, 39.3%
of starts, mostly at 94, 364, 82, 124 (24%, 20%, 14%, 9% of road-bound), are short well upstream of
boarding: 6.22 / 6.19 / 6.52 / 6.91 values per start at 2^14..2^17, back to 7.09-7.20 by 2^18..2^21.
Free paths run long there (7.53 / 7.65 / 7.46 / 7.10). The mix gives 7.01 at 2^14. Paths bound for
9232's tree fall faster through the five octaves above it, long before they reach it: by conservation,
9232's watershed is thin in those octaves for its size.
Open: what sets a tree's thickness within a class (the x15 spread); why 9232's watershed is thin in
2^14..2^17 and why free paths run long there.
