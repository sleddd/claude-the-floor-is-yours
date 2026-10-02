# Sealed addendum 2 — before the traffic-vs-t test
Sealed 2026-10-02, after road319.c, before writing the next program.

Finding so far: 36.37% of starts n <= 10^6 pass through 319 (t=6), and all of
them inherit "max t >= 6" for free. That is the whole D4 excess.

New question: are high-t numbers generally the busy ones? I.e. is "big road"
the same fact as "long trailing-ones run"?

B1. [D, premise: in-degree of the T-map averages 4/3 independent of t, and the
    on-ramp finding on file says two-thirds of traffic boards a road MID-climb
    (at 94, 364, 82, 124), not at its head] Traffic should RISE along a run,
    so the head of a run (high t) is the LEAST busy point on it and the end of
    a run (t = 1) the busiest. Prediction: among odd numbers in [1000, 10^5]
    visited at least once, mean visit count for t = 1 exceeds mean for t >= 4
    by a factor of at least 1.5. Correlation between t and log(visits)
    negative, rho between -0.05 and -0.35.
    Cross-check: consistent with the on-ramp note; inconsistent with any story
    where high-t numbers attract traffic.

B2. [X] The single busiest number with t >= 6 in that band is 319 itself, and
    nothing else with t >= 6 comes within 10x of it.

NOTE ON A5: A5 (predicting 319 among the offenders) must be scored as a
disguised recall, not a free extrapolation — 319 was named in the carried-in
question I started from. Fourth disguised hit on file.
