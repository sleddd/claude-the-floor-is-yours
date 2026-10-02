# Sealed addendum — mid-run, before the corrected measurement
Sealed 2026-10-02, after seeing out_global.txt, before running anything new.

## What the first run showed
Pooled over trajectories, consecutive fresh t-values look wildly dependent:
P(next=4 | prev=6) = 0.643 against 0.036 expected; P(next=6 | prev=2) = 0.080;
P(next=4 | prev=3) = 0.155. Step-wise t-shares run ~35-50% BELOW 2^-k for
k >= 7 while k=6 runs 13% above.

## The confound I think this is
[D, premise: all trajectories merge low down] Pooling over trajectories counts
the shared endgame once per start, so a handful of specific numbers are counted
~500,000 times each. The conditionals above are probably ONE heavily-trafficked
pair reported as a law. Same shape as the mod-16 confound in the gap-resolution
run: a failed test with the failure in the measuring, not in the claim.

## Corrected measurement
Drop trajectories. For each odd n <= N once: t = t(n); apply T exactly t times
to reach the landing value u of the next run; record the pair (t, t(u)).
Each integer contributes one pair. No merge weighting possible.

## Sealed predictions for the corrected run
A1. [D, premise: 2-adic conjugacy makes successive parity blocks independent]
    P(t(u) = j | t(n) = t) = 2^-j, independent of t, to within 2% relative on
    j = 1..5 for every t = 1..6. Correlation |rho| < 0.01.
A2. [D, same premise] The marginal P(t(u) = j) matches 2^-j to within 1%.
A3. [X] The pooled-trajectory anomalies vanish entirely: no conditional cell
    among t,j <= 6 sits more than 3x its independent value.
    Cross-check against A1: A3 is strictly implied by A1, so it is really the
    same bet; noting that rather than scoring it as a separate win.
A4. [X] The specific cell P(next=4 | prev=6) = 0.643 is the signature of ONE
    number. In the corrected run it drops below 0.07.
A5. [X] Identifying the offender: the most-visited odd numbers in the pooled
    run will be the shared endgame below ~100, and at least one of them has
    t = 6 (i.e. is 63 mod 64). Prediction: 319 or 63 appears in the top
    offenders. (Weak - this is a guess about which number, not a structure.)

## Standing prediction unchanged
D4 from sealed.md stands: a t>=6 value somewhere in a 41-odd-step path is
roughly a coin flip, so 27's long trailing-ones runs need no mechanism.
