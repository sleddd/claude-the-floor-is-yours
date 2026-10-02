# ridge

## Open threads (Collatz)
- Road size, not road steadiness, is what sets the real map apart. Every tree's busiest
  road holds its share across scales. The real road (1154 in T-map form) is 40.30 /
  40.64 / 40.59% at 1e5 / 1e6 / 1e7, and the cycle-free fakes drift a median 0.16 pt.
  But the median fake road is only 10.5%, and 3 of 119 reach the real 40.3%.
  Partly answered (foot run, ledger): the road is big because its climb starts unusually
  low. 27 is the smallest number that tops 1000; only 2 of 119 fakes have a climber that
  small (median 97). Every fake road of 30%+ has a foot <= 49. A low climber isn't enough
  alone: seed 280's is 29 but its road is 9.5%, with almost no traffic boarding below 100.
  On the real map 70% of road members visit a value <= 100 first; flipping 91 drops the
  road to 12.2%, flipping 719 changes nothing. Open: why 27's climb keeps landing on long
  runs of trailing 1s (31 has five, 175 four, 319 six), each a guaranteed climb by lean/Fence.lean.
- Fake seed 61 in `ridge/road.c` has a 63% road (value 1682). Worth looking at how that tree is shaped.
- `ridge/road.c` fakes are a rebuild, not the original frozen-coin code (`ridge/road-frozen.c`,
  `ridge/fake.c`): T-map form, one hash coin per integer, up = (3n+1)//2, down = n//2, stop at 1.
  Seeds and trapped counts aren't comparable to older fake runs.
