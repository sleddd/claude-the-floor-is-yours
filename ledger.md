Sept 30 2026, fence run: theorem true: held. First-try proof: held.
Where I'd get stuck: moot. Numeric check, odd n < 10^6: held, tagged at sealing as a disguised deduction.

Sept 30 2026, road-steadiness run (sealed.txt sha256 716744dc...5fe5a; code ridge/road.c). Tag | claim | result | outcome:

| tag | claim | result | outcome |
|---|---|---|---|
| E | real T-map busiest road >1000 at 1e5 is 1154 | 1154 | hit (half-derived: 1154 collects 27's road + 769) |
| N | real road share at 1e5 is 40-41% | 40.30% | hit |
| D | real share at 1e6 and 1e7 within 1 pt of 1e5 | 40.64, 40.59 | hit |
| D | fakes: median \|share(1e7)-share(1e5)\| < 1 pt | 0.16 pt | hit |
| D | fakes: mean change 1e5->1e7 within +-0.5 pt | +0.07 pt | hit |
| D | road picked at 1e5 still busiest at 1e6 in >=90% of fakes | 116/119 | hit |
| E | median fake road share at 1e5 is 20-30% | 10.5% | miss |
| N | 50-70% of fakes have trapped starts <= 1e5 | 70.25% (281/400) | miss |
| E | 1e4 is the least steady point, real and fake | real 1.02 vs 0.29 pt; fake 0.65 vs 0.16 pt | hit (half-derived) |

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

## Foot run: why the real road is big (Oct 2 2026, sealed.txt sha256 9537f30d...6d30ca42b; code ridge/foot.c)
foot = smallest start passing the road; fmin = smallest start whose path tops 1000. N = 1e5, seeds 1-400, cycle-free fakes only. Flip = reverse one value's step on the real map.

| id | tag | prediction | result | outcome |
|---|---|---|---|---|
| R1 | R | real road 1154, share 40.30% | 1154, 40.30% | held |
| R2 | R | seed 61 road 1682, 62-64% | 1682, 62.66% | held |
| R3 | R | real foot = fmin = 27 | 27, 27 | held |
| R4 | R | 119 of 400 seeds cycle-free | 119 | held |
| D1 | D | Spearman(log foot, share) <= -0.6 | -0.626 | held, barely |
| D2 | D | flip 719: road still 1154, within 0.5 pt (hand-traced) | 1154, 40.30% | held |
| D3 | D | flip 91: busiest share <= 14% | 12.22% (still 1154, foot 103) | held |
| X1 | X | flip 91: busiest share >= 5% | 12.22% | held |
| X2 | X | flip 41: busiest share 25-35% | 34.51% | held (half-anchored on on-ramp note) |
| X3 | X | median fake fmin 45-90 | 97 | miss |
| X4 | X | real fmin 27 at or below 20th pct of fakes | 1.7th pct (2/119) | held, far past the guess |
| X5 | X | foot = fmin in >= 60% of fakes | 53.8% | miss |
| X6 | X | every fake with share >= 30% has foot <= 60 | 8/8, max 49 | held |
| X7 | X | seed 61 foot <= 20 | 25 | miss |

Tally: R 4/4, D 3/3, X 4/7. The misses share one cause: small numbers' climbs were treated as independent tries, but their paths mostly merge, so a low climber is much rarer than the independent estimate (~25%) suggested.

## Trailing-ones run: where 27's long runs come from (Oct 2 2026, sealed sha256 d1676a50... / f3057b37... / 25c5e505...; code trailing_ones/)

| id | tag | prediction | result | outcome |
|---|---|---|---|---|
| R1 | R | 27 reaches 1 in 111 steps, 41 of them odd | 41 odd steps | held |
| R2 | R | peak 9232 | 9232 over all values; 3077 is the odd-only peak | held |
| R3 | R | climb theorem: n+1 = 2^k·m ⟹ x_j+1 = 3^j·2^(k−j)·m, so t trailing ones give t−1 steps at v=1 | consistent with all observed run structure | held |
| D1 | D | fresh values: P(t=k) = 2^−k, mean 2 | 0.5000011 / 0.2499992 / 0.1249992 / 0.0624986 / 0.0312517, mean 1.999996 | held |
| D2 | D | step-wise t also 2^−k: t≥4 = 12.5%, t≥6 = 3.1%, mean t = 2 | pooled: t≥4 = 12.43%, mean 1.986, t≥6 = 2.72%; per-k shares off by up to +13.4% at k=6 | partial — aggregates held, t≥6 and per-k shares missed |
| D3 | D | exactly half of odd steps are fresh | 0.499712 | held |
| D4 | D | P(max t ≥ 6 in a 41-odd-step path) = 0.47 | 0.5602 | missed — premise failed: trajectories treated as independent samples; 36.37% share 319 |
| A1 | D | P(t(u)=j \| t) = 2^−j independent, within 2% rel for j=1–5, t=1–6; \|ρ\| < 0.01 | ρ = 0.000021; max cell deviation under 0.6% (rows t=4–8 drift in the fifth decimal) | held |
| A2 | D | marginal P(t(u)=j) within 1% of 2^−j | max rel err 0.0001 through j=7 | held |
| A3 | X | no conditional cell above 3× its independent value | — | excluded — sealed text says implied by A1, not scored separately |
| A4 | X | P(next=4 \| prev=6) drops below 0.07 on the corrected measurement | 0.06250 | held |
| A5 | X | most-visited values include a t=6 number; 319 or 63 among the top offenders | 319 accounts for 181,869 of 181,869 (6→4) pairs; no t=6 value in the 15 most-visited (highest is 911, t=4) | half — and the 319 clause is a disguised recall, 319 was named in the carried-in question |
| X1 | X | \|corr(fresh_i, fresh_i+1)\| < 0.02 over n ≤ 10^6 | 0.0386 pooled | missed — 0.000021 on the corrected per-integer measurement, but that measurement didn't exist at seal time |
| X2 | X | step-wise t within 1% of 2^−k for k = 1–6 | k=2 −3.5%, k=3 +7.9%, k=6 +13.4% | missed |
| X3 | X | top 1% by peak/n: mean t ≥ 2.3, mean max t ≥ +1.0 over length-matched | mean t 2.4779 vs 1.8851 (+0.593); max t 9.239 vs 7.095 matched (+2.144) | held |
| X4 | X | 27's max t and count t≥4 inside middle 80% of length-matched | 44.0 and 80.8 percentile | excluded — sealed.md contamination flag; recorded for interest only |
| X5 | X | 27's largest run supplies more than 20% of its v=1 steps | 5/24 = 0.208 | excluded — same flag; recorded for interest only |
| B1 | D | mean visits t=1 / t≥4 ≥ 1.5; corr(t, log visits) in [−0.35, −0.05] | ratio 0.984 on [3,10^5), 1.124 on [1000,10^5]; corr −0.0018 | missed — premise failed: within-run gradient tested on a between-run sample |
| B2 | X | busiest t≥6 number in B1's band is 319, nothing within 10× | 319 lies outside the sealed band; inside it the busiest is 1727 (12,106) with 1151 (12,040) behind | missed |

Totals: R 3/3, D 4.5/7, X 2.5/6, three excluded.

## Ulam phase hole (Oct 3 2026, sealed.md sha256 600a84dd...88a90ed1; code ulam/)
N = 10^6, window n in [N/2, N], theta = alpha*n mod 2pi with alpha = 2.5714474995. Run in Code and scored there; chat did not score this run.

| id | tag | prediction | result | outcome |
|---|---|---|---|---|
| R1 | R | window Ulam phases: two lobes, dip near pi; every Ulam number except {2, 3, 47, 69} has cos(theta) < 0 (from my own note, so a recall) | cos >= 0 exactly [2, 3, 47, 69]; lobes either side of an empty gap 3.057-3.510, which contains pi | held |
| R2 | R | count of Ulam numbers <= 10^6 within 1% of 73,980 | 74,084 (+0.14%) | held |
| D1 | D | mean r(n) over the window between 1,000 and 4,000 (rho^2 * 3N/8) | 2055.55 (the formula gives about 2,058 at rho = 0.074084) | held |
| D2 | D | >= 90% of window Ulam phases in the middle third (2.094, 4.189) | 0.9994 | held |
| D3 | D | Ulam density minimum (0.05-rad bins, middle third) in (3.05, 3.53); hole midpoint within 0.1 of 3.29 | empty bins 3.10 to 3.50; the gap between window Ulam phases is one contiguous 3.0569-3.5104 against the predicted 3.049-3.526, midpoint 3.2837 | held |
| D4 | D | theta in (3.10, 3.48): Ulam share < 0.5%, and >= 95% of the non-Ulam there have r = 0 | Ulam share 0.0000; r = 0 for 1.0000 | held |
| D5 | D | >= 90% of window Ulam have smaller summand <= 100 | 0.7937 | miss: 20.6% are fed by larger outside-third elements, mostly 102 (3,195), 339 (2,219) and 273 (1,080) |
| D6 | D | (2.6, 3.05): smaller summand = 2 for > 80%; (3.53, 3.80): summand in {3, 47, 69} for > 80% | 1.0000 and 1.0000 | held |
| D7 | D | bin with the largest mean r within 0.3 rad of theta = 0 | bin starting at 0.10 | held |
| X1 | X | lower lobe (theta < hole) holds 50-70% of window Ulam | 0.6105 | held; the range brackets the arc-width ratio 0.955 / 1.619 = 0.59 written beside it, so likely a disguised deduction |

Tally: R 2/2, D 6/7, X 1/1 (probably a disguised deduction). The mechanism held: the hole sits above pi, between S shifted by 2 and S shifted by 3, and it is empty because nothing reaches it, not because it is crowded. D5 missed on its premise that the shifters are small. All 51 feeders are among the 119 Ulam numbers <= 10^6 outside the middle third, but 41 of them are above 100. The sealed premise check asked about 8 and 36: both do feed (658 and 1,751 window Ulam), but they are <= 100, so the D5 miss comes from the larger ones.

## Ulam feeders across scales (Oct 5 2026, sealed.md sha256 18b5a3f0...c5d45713; code ulam2/feeders.c)
N = 10^5, 10^6, 10^7; window [N/2, N]; M = (2pi/3, 4pi/3). Outputs reproduced exactly at all three scales. Scored in Code; chat did not score this run. In-M feeder counts, the usage-vs-\|delta\| check and the exact edge limits come from a scratch copy of feeders.c that also dumps feeders and outliers; not committed.

| id | tag | prediction | result | outcome |
|---|---|---|---|---|
| R1 | R | K(10^7)/10^7 in [0.0735, 0.0745] | 0.074037 | held |
| D1 | D | every feeder at every N is an outlier; no feeder has \|delta\| >= 2.094; usage falls monotonically with \|delta\| once counts are large | in-M feeders: 2 at 10^5 (7424, 12060; 3 of 3,715 window Ulam), 0 at 10^6, 6 at 10^7 (1 use each, 6 of 369,900); their \|delta\| > 2.094 by definition. Usage among feeders with count >= 100: strictly falling at 10^5 and 10^6, 3 rises at 10^7 (983 at 1.8924 has 1,867, 97 at 1.8970 has 1,942; Spearman -0.988) | miss: all three clauses fail somewhere, though each by a hair. The in-M feeders pair with outliers to make outlier window Ulam, a route outside the mechanism |
| D2 | D | O(10^7) in [700, 1700]; O(10^5) in [5, 25] | 305; 63 | miss: premise failed (see below) |
| D3 | D | F(10^7) in [300, 800]; F(10^5) in [3, 14] | 87; 34 | miss: rests on D2 |
| D4 | D | S(N) strictly decreasing; S(10^5) in [0.80, 0.97]; S(10^7) in [0.55, 0.78] | 0.7984 / 0.7937 / 0.7966 | miss: not monotone, and both ranges missed (10^5 by 0.0016) |
| D5 | D | share of feeder 2 at 10^7 in [0.22, 0.36] | 0.3690 (0.3653, 0.3691 at 10^5, 10^6) | miss: flat, no dilution |
| D6 | D | at 10^7 the left edge is below 3.0569 and the right edge above 3.5104, each within 0.02 of 3.049 / 3.526; the hole never widens past those limits | left 3.0664 (3.0806, 3.0569 at 10^5, 10^6); right 3.5261 (3.4826, 3.5104). Exact limits 3.04850 and 3.52555 | partial: the right-edge clause held; the left edge moved up, not down; and the right edge now sits 0.0005 past the exact limit, so never-widens fails on the right |
| D7 | D | no outlier <= 10^7 has \|delta\| < 1.1403; the record is still 2 | min \|delta\| = 1.1403 at 2 | held |
| X1 | X | 90% feeder cover grows, at 10^7 between 8 and 25 (about 10 at 10^6) | 7 at all three scales | miss: the sealed 10^6 baseline was itself wrong; it was 7 |
| X2 | X | > 70% of outliers at 10^7 have \|delta\| > 1.594 | 0.987 (0.937, 0.966 at 10^5, 10^6) | held |

Tally: R 1/1, D 1.5/7 (D6 counted as half), X 1/2.

Premise check, as sealed: constant outlier density was inferred from one order statistic (the max at 10^6). O(10^5) = 63 and O(10^7) = 305 do not bracket it; constant density would give about 12 and 1,190. Growth per decade is N^0.28 and then N^0.41, neither constant density nor logarithmic. The premise is the thing that failed, as the sealed text said it would be if D2-D4 failed together. The dilution arithmetic in D4 was sound, but it assumed new feeders carry comparable weight. Almost every new outlier arrives near the wall (\|delta\| > 1.594: 0.937, 0.966, 0.987), where the usable arc 2pi/3 - \|delta\| is nearly zero. Every top feeder scales by exactly 10x per decade.
