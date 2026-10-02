# Sealed predictions — Collatz trailing-ones structure
Sealed 2026-10-02, before running anything.
Open question carried in from the foot run: "why does 27's path keep landing on
long runs of trailing 1s (31, 175, 319)?"

Tags: R = recalled, D = deduced (from a stated premise), X = free extrapolation.
Practice from the sandpile run: each X is cross-checked against the R/D items
below before sealing, AND the premise behind each D is named so it can be
blamed if the D fails.

## Definitions
Work in the T-map on odd numbers: odd n -> odd part of (3n+1).
t(n) = number of trailing 1-bits of odd n.
A "run" = a maximal descending block of t-values along the trajectory.
A "fresh" value = an odd step whose predecessor had t = 1 (i.e. the step that
just landed after a v>=2 halving).

## CONTAMINATION FLAG
Before sealing I hand-listed part of 27's odd trajectory in my head and saw
31 (t=5), 47 (t=4), 175 (t=4), 319 (t=6), 479 (t=5), 719 (t=4). So anything
about 27's own t-profile is PEEKED, not predicted. I will not score those.
Scored items are about the general structure only.

## R — recalled
R1. 27 reaches 1 in 111 steps of the 3n+1/n/2 map, 41 of them odd steps.
    (medium-high confidence on 41; high on 111)
R2. Peak of 27's trajectory = 9232. (high)
R3. Climb theorem, proved in core Lean on Sept 30: if n+1 = 2^k*m with m odd,
    then x_j + 1 = 3^j * 2^(k-j) * m, so an odd n with t trailing ones is
    followed by exactly t-1 steps with v=1. (high)

## D — deduced, with the premise named
D1. [premise: fresh odd values are 2-adically generic] P(t = k) = 2^-k for
    k >= 1 on fresh values; mean fresh t = 2.
D2. [premise: D1 + R3] The t-values along a trajectory descend t, t-1, ..., 1,
    one run per fresh draw, mean run length 2. Therefore the distribution of t
    over ALL odd steps is also 2^-k, not something heavier. Share of odd steps
    with t >= 4 = 1/8 = 12.5%; with t >= 6 = 1/32 = 3.1%; mean t over steps = 2.
D3. [premise: D2] Exactly half of all odd steps are fresh (one fresh per run,
    mean run length 2). Equivalently share of steps with t = 1 is 1/2, which is
    the same as the odd-step v=1 share near 0.5 already on file (deep parity
    0.497 from the thin-tail run). Consistent — this is the cross-check.
D4. [premise: D1 + R1] A 41-odd-step trajectory contains about 20 fresh draws,
    so P(max t >= 6 somewhere in it) = 1 - (1 - 2^-5)^20 = 0.47.
    So a t=6 number in a path of 27's length is a coin flip, not a rarity.
    THIS IS THE PROPOSED ANSWER to the carried-in question.

## X — free extrapolation (each cross-checked against R/D above)
X1. Successive fresh t-values along a trajectory are independent:
    |corr(t_fresh[i], t_fresh[i+1])| < 0.02 over n <= 10^6.
    Cross-check: consistent with D1's premise; if this fails, D1-D3 should
    also show strain, so they fail or hold together.
X2. The measured step-wise t-distribution over all odd n <= 10^6 matches 2^-k
    to within 1% relative error for k = 1..6.
X3. Conditioning, not mechanism: take the top 1% of starts n <= 10^6 by
    peak/n ratio. Their mean t over odd steps exceeds the generic mean by at
    least 0.3 (i.e. >= 2.3), and their mean max-t exceeds the generic
    same-length mean by at least 1.0.
    Cross-check: D2 says high peak/n needs excess v=1 steps, which by R3 needs
    excess high t. So the sign is deduced; the SIZE is the free part.
X4. Compared against starts matched on odd-step count (not all starts), 27's
    t-profile is unremarkable: its max t and its count of t >= 4 both sit
    inside the middle 80% of the matched population.
X5. 27's long climb is driven by ONE big fresh draw, not by a string of them:
    the single largest t on its path accounts for more than 20% of all its
    v=1 steps.

## What would overturn the proposed answer (D4)
If X1 fails with positive correlation, then landings after a long climb really
do favour long trailing-ones runs, and the answer is mechanism, not selection.
That is the thing I actually want to know.
