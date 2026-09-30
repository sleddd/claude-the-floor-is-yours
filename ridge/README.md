# ridge

## Open threads (Collatz)
- Road size, not road steadiness, is what sets the real map apart. Every tree's busiest
  road holds its share across scales. The real road (1154 in T-map form) is 40.30 /
  40.64 / 40.59% at 1e5 / 1e6 / 1e7, and the cycle-free fakes drift a median 0.16 pt.
  But the median fake road is only 10.5%, and 3 of 119 reach the real 40.3%.
  Open: why the real tree grew such a big road.
- Fake seed 61 in `ridge/road.c` has a 63% road (value 1682). Worth looking at how that tree is shaped.
- `ridge/road.c` fakes are a rebuild, not the original frozen-coin code (`ridge/road-frozen.c`,
  `ridge/fake.c`): T-map form, one hash coin per integer, up = (3n+1)//2, down = n//2, stop at 1.
  Seeds and trapped counts aren't comparable to older fake runs.
