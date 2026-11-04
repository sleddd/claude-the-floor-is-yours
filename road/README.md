# road: biggest shared road across 3x+k (chat, Nov 4 2026)

Map: x odd -> 3x+k, x even -> x/2, for k in {1,5,7,11,13,17,19,23,25}. Starts n <= 10^6.
sealed.txt sha256 1adbb60102537a0cbae3702f94ada213b0e6cdd6f31f196fedb49a5a95644349, kept in
chat. P1-P4 were sealed against a cutoff of 1000 with loop members included; the measure was
fixed afterwards (below). Grading waits on the sealed text.

Measure (as fixed): a start's basin is the cycle it ends in. Multiples of k are left out as
starts (for k > 1 they only ever visit multiples of k). The road of a basin is the value
v > cutoff, not a cycle element, passed by the most of that basin's starts, the start itself
counting; share = those starts / basin starts. Only basins holding >= 5% of all n <= 10^6 are
eligible, and the basin percentage uses all n <= 10^6 as denominator, multiples of k included
(that is what reproduces chat's 37.6% and 6.4%; against non-multiples only, k=25's basin is 39.2%).

Files
- road.c: per-basin roads and the top eligible road for one k and cutoff.
  `gcc -O2 -o road road.c`, then `./road k cutoff [N] [L]`. Counts are kept for v <= L
  (default 5·10^7); `exact=yes` means fewer starts ever exceed L than the road's count, so no
  value above L can beat it.
- out_5000.txt, out_9000.txt, out_20000.txt: all nine k at each cutoff.
  One `exact=NO` line: k=5, basin min 19, cutoff 20000 (not k=5's top basin). Rerun with
  L = 10^9 gives the same road, 21476 at 0.0212, exact=yes.
- analog.c: one start's path, peak, and step of reaching a given value. `./analog 25 79 29512`.

Expected output (from chat): all reproduced exactly.
- cutoff 5000: k=1 0.3941 at 9232; k=5 0.1760 (9184); k=7 0.0463 (5800); k=11 0.0764 (5432);
  k=13 0.1298 (8128); k=17 0.1155 (5776); k=19 0.0881 (9088); k=23 0.3269 at 5816, basin 6.4%;
  k=25 0.5146 at 5392, basin 37.6% (cycle min 17).
- cutoff 20000: k=1 0.0289 (at 22144); k=25 0.4578 at 29512.
- 3x+25, start 79: peak 39316 (step 46), reaches 29512 at step 49, ends in the cycle with min 17.
  For comparison, 3x+1 start 27 peaks at 9232 at step 77.

Cutoff 9000, for the record: k=1 still 0.3941 at 9232; k=25 0.5083 at 9508; k=23 0.3066 at 10268.
k=1's road falls apart between 9232 and 20000 (0.3941 -> 0.0289); k=25's barely moves
(0.5146 -> 0.4578), and k=5, 17, 19 hold within 0.02.

Open (from chat)
- Is a long early climb through busy small numbers what makes a big road, across all k?
