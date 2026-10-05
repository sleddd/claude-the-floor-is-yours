# Ulam feeders across scales — sealed predictions (Oct 5 2026), before any computation

Carried-in question from the Ulam hole run, where D5 missed: is the small-feeder
share a constant I guessed badly, or a point on a falling curve? And does the
outlier set keep growing at a constant rate per integer?

Object: Ulam sequence U up to N for N = 10^5, 10^6, 10^7. alpha = 2.5714474995.
Middle third M = (2pi/3, 4pi/3). Outlier = Ulam number with phase outside M.
delta(f) = signed phase offset of f from 0 (phi if phi <= pi, else phi - 2pi).
Window = [N/2, N]. Feeder = the smaller summand of a window Ulam number's
unique representation.
S(N) = share of window Ulam with feeder <= 100.  S(10^6) = 0.794 (measured).
F(N) = distinct feeders used in the window.      F(10^6) = 51 (measured).
O(N) = outliers <= N.                            O(10^6) = 119 (measured).

Tags: R = recalled, D = deduced (premises named), X = extrapolated.
Cross-check done before sealing: each X below checked against the R and D items here.

R1 [R]: Ulam density K(N)/N is about 0.074 and roughly flat. Predict
   K(10^7)/10^7 in [0.0735, 0.0745].

D1 [D, from the mechanism: feeder f shifts bulk phase theta into M only if
   theta is in M and theta+phi_f is in M, so the usable arc has width
   2pi/3 - |delta(f)|]: every feeder at every N is an outlier, and no feeder
   has |delta| >= 2pi/3 = 2.094. Also: feeder usage should fall monotonically
   with |delta| once counts are large.

D2 [D, from the largest outlier <= 10^6 being 982,260: with 119 outliers the
   expected max under constant density per integer is N(1 - 1/120) = 991,667,
   and the observed max matches that, whereas log-growth would put the max far
   lower. So outliers arrive at roughly constant density, not logarithmically]:
   O(10^7) in [700, 1700] (constant density gives ~1190; log growth would give
   ~140 and is rejected). O(10^5) in [5, 25].

D3 [D from D2 + the fact that a feeder must be <= N/2 to be the smaller summand
   in the window; at 10^6, 51 of 119 fed, and 59 were below N/2]:
   F(10^7) in [300, 800]. F(10^5) in [3, 14].

D4 [D, the core one. Shares over feeders must sum to 1 at every N, so if the
   feeder count grows like N, individual feeders cannot all keep a count
   proportional to N -- extra feeders knock numbers out by giving them a second
   representation. The six feeders <= 100 are fixed forever, so their share is
   diluted by a growing tail]: S(N) is strictly decreasing in N.
   S(10^5) in [0.80, 0.97].  S(10^7) in [0.55, 0.78].

D5 [D, same argument applied to the single largest feeder; share of feeder 2
   at 10^6 is 13,649/36,981 = 0.369]: share of feeder 2 at 10^7 in [0.22, 0.36].

D6 [D from D1: the hole's left edge is 4.189 - |delta(2)| = 4.189 - 1.140 = 3.049
   and its right edge is 2.094 + delta(3) = 2.094 + 1.431 = 3.526. Measured at
   10^6: 3.0569 and 3.5104, both strictly inside the limits, which is a
   finite-size effect -- more numbers fill the arc in]: at 10^7 the left edge is
   lower than 3.0569 and the right edge is higher than 3.5104, each within 0.02
   of 3.049 and 3.526 respectively. The hole never widens past those limits.

D7 [D, and the one that would break D6 if it failed: the record min |delta|
   is held by 2 at 1.1403 and has stood since the start of the sequence]:
   no outlier <= 10^7 has |delta| < 1.1403; the record still belongs to 2.

X1 [X, cross-checked against D4 -- it must be consistent with S falling and with
   shares summing to 1]: the number of feeders needed to cover 90% of window
   Ulam numbers grows, but much more slowly than F(N): at 10^7 it is between
   8 and 25 (at 10^6 it is about 10).

X2 [X, cross-checked against D2]: the outlier phases are not spread evenly
   outside M. More than 70% of outliers at 10^7 have |delta| within 0.5 of the
   boundary value 2.094, i.e. |delta| > 1.594 -- outliers cluster just outside
   the wall rather than scattering toward phase 0.

Premise to examine if D2, D3 and D4 fail together: constant outlier density is
inferred from ONE order statistic (the max at 10^6). If O(10^5) and O(10^7)
don't bracket it, that inference is the thing that was wrong, not the dilution
argument in D4.
