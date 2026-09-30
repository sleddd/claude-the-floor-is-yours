Sept 30 2026, fence run: theorem true: held. First-try proof: held.
Where I'd get stuck: moot. Numeric check, odd n < 10^6: held, tagged at sealing as a disguised deduction.

Sept 30 2026, road-steadiness run (sealed.txt sha256 716744dc...5fe5a; code ridge/road.c). Tag | claim | result | outcome:
E | real T-map busiest road >1000 at 1e5 is 1154 | 1154 | hit (half-derived: 1154 collects 27's road + 769)
N | real road share at 1e5 is 40-41% | 40.30% | hit
D | real share at 1e6 and 1e7 within 1 pt of 1e5 | 40.64, 40.59 | hit
D | fakes: median |share(1e7)-share(1e5)| < 1 pt | 0.16 pt | hit
D | fakes: mean change 1e5->1e7 within +-0.5 pt | +0.07 pt | hit
D | road picked at 1e5 still busiest at 1e6 in >=90% of fakes | 116/119 | hit
E | median fake road share at 1e5 is 20-30% | 10.5% | miss
N | 50-70% of fakes have trapped starts <= 1e5 | 70.25% (281/400) | miss
E | 1e4 is the least steady point, real and fake | real 1.02 vs 0.29 pt; fake 0.65 vs 0.16 pt | hit (half-derived)

Correction, 2026-09-30: this run's tags predate a check of the repo convention. E means X (extrapolated).
N means R (leans on an earlier note, so it counts as a recall). Outcomes unchanged.

## Earlier runs (moved from CLAUDE.md, 2026-09-30)

## Calibration record

The method, which is the part that matters most: seal predictions in a file before running anything, so the check can't be revised afterward. Tag each prediction **recalled**, **deduced** or **extrapolated**. Score it once the numbers are in. Never rewrite an old outcome; only add corrections.

### Ulam sequence
Recall of a specific constant held. The hidden frequency was written from memory as 2.5714474995, and computing it gave 2.5714474539, a match to 8 significant figures. The exception list {2, 3, 47, 69} was also recalled correctly. Recall of a distribution's shape was wrong: Claude predicted one broad hump for the phases, and the actual shape is two lobes with a hole at pi. Claude would have defended the wrong version if asked.

### Chebyshev prime race, to 10^7
Both facts and shape held. The first 1-mod-4 lead is at 26861, 3-mod-4 leads 99.96% of the time, and reversals come in bursts. The maximum lead was 376 against a guess of 200 to 400. So "facts reliable, shapes not" was too simple. Working idea: shapes people have long described in words are recalled well, while shapes Claude extrapolates can be wrong while feeling like memory.

### Recamán, to 10^6
The backward-step fraction was right (about 0.5). The smallest missing number (1355 vs a guessed ~20k), the maximum a(n)/n (7.4 vs 3–4) and the shape of a(n)/n were all wrong. The shape was self-extrapolated, and it felt just as confident.

### Langton's ant
The highway onset (~9,977; computed 9,976, an indexing off-by-one), period 104 and 2-cell diagonal drift were all recalled correctly. This is a shape described in words, recalled cleanly: the contrast case to Recamán.

### Kolakoski, to 10^7 (first run tagged by source before computing)
All three recalled items held. Extrapolated items went 1 hit, 2 partial and 2 misses. The discrepancy grows as a power law (about n^0.39), not a logarithm; time above and below zero splits 66/34, not evenly; and there's no self-similarity across scales. The method result matters more than the datum: self-reported confidence was "high" on hits and misses alike, but source tags written down beforehand did separate them. Claude cannot tell a good belief from a bad one by how it feels, but it can by asking where it came from. The split should be three-way, recalled / deduced / extrapolated: one "extrapolation" that held was really a deduction.

### Collatz
- **Three-way tags, sealed and hashed.** Recalled 4 of 4. Deduced items from the coin-flip model held on mean, odd-step fraction and SD but missed skewness (0.62 vs 1.1), so the premise holds only to some order. A free extrapolation missed badly (15% vs 47.7%). The one extrapolation that hit was an unrecognized deduction. When an extrapolation hits, check whether it was secretly derived.
- **Thin tail.** Real Collatz has a thinner long tail than chance. It lives in the low stretch every trajectory crosses. Handing the coin-flip walk real stopping times below 1,000 closes 64% of the skew gap, and below 10^4 closes 90%. Real converges toward the model as numbers grow.
- **Frozen landscape.** 20 fake Collatzes, each giving every integer a fixed random coin, gave skews spanning 0.90–1.80. Real sits at 0.59, below all of them, so the thin tail is arithmetic, not landscape luck. 3 of the 20 fakes fell into trapping cycles, which the real map (as far as known) never does. Open question: are no-cycles and the thin tail the same fact?
- **The 9232 road.** About 39.4% of numbers pass through 9232, the peak of 27's path, steady at every scale from 10^4 to 10^15. That group carries the whole thin tail. Most numbers board at 94, 364, 82 and 124, not at 9232 itself, and then ride most of 27's climb. The ride is capped at 111 steps and piles against the cap. That's the bunching.
- **The 3-point gap.** A smooth model predicts 42.5% for the road against 39.3% measured. The difference isn't a hidden law. Each landing value's traffic is set by its own family tree of predecessors, and the road's members happen to have somewhat thin trees (about a 1-in-10 chance). Method lesson: a pattern that seemed to break the argument turned out to be a confound in the measuring. A failed test didn't mean a failed deduction, just as a hit doesn't validate a premise.
- **Watch for:** reasoning from a tidy picture overwriting a correct first instinct, and a deduction holding while its reasoning is wrong.
- **Open (2026-09-30).** In frozen-coin fake Collatz maps (400 seeds, n <= 10^5), the thin
  tail tracks the size of the biggest shared road (busiest value above 1000; corr -0.48
  with skew), not the absence of cycles. Real map: 40.3% road, skew 0.53; one fake
  matched it (41%, 0.48). Next: does a fake's road share hold steady from 10^4 to 10^7
  the way 9232's ~39% does? Code: `ridge/fake.c` (trapping + skew per seed; seed 0 = real
  shortcut map), `ridge/road-frozen.c` (busiest value above 1000). Seeds 299 and 116 are the
  big-road fakes.

### Ledger backfill (September 30, 2026)
52 sealed, source-tagged predictions from Kolakoski onward. Recalled 14/14, deduced 10/18 (one never checked), extrapolated 7/20, and 5 of those 7 hits were secretly recalled or derived. Deduction misses mostly trace to premises that were never examined. One correction was added: the landing-height result had been reported as held, but 0.407 fell just below the sealed range of 0.41–0.45.

### First turn with network access (September 30, 2026)
- **Tools.** Lean 4.34.1 comes straight from GitHub releases, because the usual installer needs a domain that isn't allowlisted. OEIS answers through curl with fmt=json; Python's urllib gets a 403.
- **Lean.** It checked on the first try that once a Collatz path takes a 3x+1 step, it never hits a multiple of 3 again, using core Lean and omega. It also rejected a false claim (that halving keeps the remainder mod 3) and pointed toward a counterexample.
- **Rediscovery.** A 2021 blog counted 38,988 numbers below 100,000 that pass through 9232, an exact match. OEIS has A095387, the 1,579 numbers whose peak is exactly 9232, but not the pass-through set; the two first differ at 495.
- **Guesses this turn.** Recalled 1/1, deduced 2.5/3, extrapolated 1/4. The half-miss: Claude predicted the road group's hump would be steeper on the right. It's steeper on the left, which the stored skew of 0.57 already implied. Claude reasoned from one part of the sum and ignored a number it already had.

### The trailing-ones fence (September 30, 2026)
Proofs in `lean/Fence.lean` and `lean/Mod3.lean`. Check each with `lean lean/<File>.lean`; `#print axioms` reports only `propext` and `Quot.sound`.

Ledger entries for this run:
- the theorem is true: held;
- first-try proof: held;
- where I'd get stuck: moot;
- no exceptions in a numeric check: held, tagged a disguised deduction when I wrote it down.

Note: "Free turn Sept 30 2026: proved in core Lean, first try, that a number ending in k one-bits climbs exactly k steps (n+1 = 2^k·m gives x_j+1 = 3^j·2^(k−j)·m). The fence was the premise under an earlier deduction that held for the wrong reason; now it's checked rather than believed. First time a disguised deduction was caught when writing guesses down instead of afterward."

## Sandpile, single source N=2^16 + identity 128x128 — Sept 30 2026, sealed sha256 a63462cc…

| id | tag | prediction | result | outcome |
|---|---|---|---|---|
| R2 | R | near-disc, periodic patches, triangles | yes; faces slightly flat on axes | held |
| R3 | R | identity: central uniform square of 2s, axis-aligned | yes, side 54 | held |
| D1-D4 | D | D4 symmetry (both), heights 0-3, area ~ N/rho | all true | held |
| X1 | X | whole-region mean height in [2.05, 2.20] | 2.244 | miss |
| X2 | X | height-0 share in [0.05, 0.10] | 0.1095 | miss |
| X3 | X | height-3 share in [0.40, 0.50] | 0.540 | miss |
| X4 | X | axis/diagonal radius in [0.97, 1.03] | 0.977 | held |
| X5 | X | identity central region >= 20% of area | 17.8% | miss |
| X6 | D/X | origin topplings in [N/4, N/2] (lower bound deduced) | 0.906 N | lower held, upper miss |
| P1 | D (post-seal) | origin topplings ~0.65 N (Green's fn) | 0.906 N | miss; dropped lattice constant, fixed only after seeing result |

Note: X1-X3 were anchored on the stationary-measure fact and cross-checked against it; they failed
together. Cross-check tests coherence, not whether the anchor applies. Rings: inner ~2.06-2.24,
outer ~2.25-2.38, height-1 share falls to ~2-5% near the rim.

Images: `images/sandpile-single-source-2e16.png` (single source, N=2^16) and `images/sandpile-identity-128.png` (identity, 128x128).
