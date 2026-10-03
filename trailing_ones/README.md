# trailing_ones

Where 27's long trailing-ones runs come from. Carried in from the foot run's
open question: why does 27's path keep landing on 31, 175, 319?

Answer: road inheritance. Successive runs of the T-map are exactly independent;
36.4% of starts n <= 10^6 pass through 319 (t = 6) and inherit "max t >= 6" free.

Sealed before computing, hashes in `sealed.sha256`:
  sealed.md           d1676a50...  initial predictions, R/D/X tagged
  sealed_addendum.md  f3057b37...  sealed mid-run, after the pooled result
                                   looked like a law and before re-measuring
  sealed_2.md         25c5e505...  sealed before the traffic-vs-t test

Build everything with `-O2 -lm`. Five C programs, one Python script.

## Files and expected output

tones.c         Full trajectory scan, n <= 10^6. Writes out_global.txt and
                per_start.bin (14 MB, not committed). `./tones 1000000`
                regenerates out_global.txt byte for byte.
                NOTE: its statistics are POOLED over trajectories, so they
                measure road traffic, not the map. This is the confound, kept
                deliberately — see out_global.txt.

out_global.txt  The fake law in its original packaging:
                P(next run starts at t=4 | previous started at t=6) = 0.643
                against 0.036 expected. One number produced it.

pairs.c         The corrected measurement. One pair per integer, no trajectory
                pooling: t = trailing-ones(n), apply T exactly t times to reach
                the next run's head u, tabulate (t, t(u)).
                `./pairs 20000000` -> 10,000,000 pairs, mean t = 1.999999,
                corr = 0.000021. Conditional rows t = 1-3 read exactly
                0.50000 / 0.25000 / 0.12500 / 0.06250 / 0.03125; rows t = 4-8
                drift in the fifth decimal (0.06251 at t=4, 0.49999 at t=5).
                Every cell within 0.6% of 2^-j. Not a discrepancy.

offenders.c     Finds what made the fake law. `./offenders 1000000` -> 319
                accounts for 181,869 of 181,869 (6->4) pairs. The 15 most-
                visited values are the shared endgame; highest t among them
                is 911 (t = 4).

road319.c       `./road319 1000000` -> 181,869 of 500,000 starts visit 319
                (0.3637). In the 39-43 odd-step band: max t >= 6 is 0.5602
                overall, 1.0000 given a visit to 319, 0.4315 without one.
                That gap is the whole of D4's miss.

traffic.c       Is "big road" the same fact as "long climb"? No.
                corr(t, log visits) = -0.0018; ratio mean(t=1)/mean(t>=4)
                = 0.984. Committed version scans [3, 10^5). An earlier version
                started at 1001, which excluded 319 itself; B2 in sealed_2.md
                inherits that band and is scored against it, not against this.

twentyseven.py  27's own profile against length-matched starts. Requires
                per_start.bin, so run tones first. 41 odd steps, max t = 6 at
                the 44th percentile, mean t 2.195 at the 88.5th.
                Scored as excluded: sealed.md's contamination flag says 27's
                t-profile was peeked before sealing.

## Pooled figures (all 22,996,390 odd steps, uncapped)

mean t = 1.9863, t >= 4 = 12.43%, t >= 6 = 2.72%. Summing out_global.txt's
table instead gives slightly low numbers; it stops at k = 12.
