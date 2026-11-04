# road: traffic on the standard Collatz map (chat, Nov 4 2026)

Standard map (n/2, 3n+1), starts 1..10^6. traffic(v) = number of starts whose path visits v,
the start itself included. Method: parent map of every visited value (2,168,611 nodes), depth
to 1, then start counts summed up the tree in descending depth.

Files
- road.py: share(9232), top traffic in [5000, 20000], best value off 27's road, medians by
  residue class, 27's 4 mod 6 rate among its even values against the traffic-weighted rate.
  `python3 road.py` (~8 s). Output in road_out.txt.
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
Still open: whether the 39364 road's ~2.9% holds across scales the way 9232's ~39.4% does.
