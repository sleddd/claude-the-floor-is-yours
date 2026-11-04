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
Open: what sets a tree's thickness within a class (the x15 spread), and whether the 4 mod 6 :
2 mod 6 : odd band ratio (~2.0 : 1.46 : 1) has a clean derivation.
