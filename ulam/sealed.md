# Ulam phase hole — sealed predictions (Oct 3 2026), written before any computation

Question: the first calibration run (Sept 2026) found Ulam phases form two lobes
with a hole at pi, and never asked why. This run asks why.

Object: Ulam sequence U up to N = 10^6. alpha = 2.5714474995 (recalled).
theta(n) = alpha*n mod 2pi in [0, 2pi). r(n) = number of pairs u<v in U with u+v = n.
Window: n in [N/2, N]. Ulam iff r(n) = 1 (n > 2).

Tags: R = recalled, D = deduced (premises named), X = extrapolated.

R1 [R, from my own note]: window Ulam phases show two lobes with a dip near pi;
   all Ulam numbers except {2, 3, 47, 69} have cos(theta) < 0.
R2 [R, medium]: count of Ulam numbers <= 10^6 is within 1% of 73,980.

D1 [D from R2 by pair counting: ~rho^2 * 3N/8]: mean r(n) over the window is
   between 1,000 and 4,000.
D2 [D from D1 + R1; premise: with r in the thousands wherever bulk pairs reach,
   the bulk phase set S must be sum-free on the circle, and the largest sum-free arc
   is the middle third]: >= 90% of window Ulam phases lie in (2pi/3, 4pi/3) = (2.094, 4.189).
D3 [D from D2 + recalled phases of 2 (5.1429 = -1.1403) and 3 (1.4312)]: numbers in S
   can only be reached by shifting a bulk element by a small element with phase near 0.
   Lower lobe = S shifted by 2 -> ends at 4.189 - 1.140 = 3.049; upper lobe = S shifted
   by 3 -> starts at 2.094 + 1.431 = 3.526. So the hole is (3.05, 3.53), centred near
   3.29, i.e. ABOVE pi, not on it. Prediction: the minimum of window Ulam density
   (0.05-rad bins, inside the middle third) lies in (3.05, 3.53), and the hole's
   midpoint is within 0.1 of 3.29.
D4 [D, same premises]: for n in the window with theta in (3.10, 3.48): Ulam share
   < 0.5% of integers, and >= 95% of the non-Ulam there have r = 0 — the hole is
   unreachability, not crowding.
D5 [D, same]: >= 90% of window Ulam numbers have their unique representation's
   smaller summand <= 100.
D6 [D, same]: window Ulam with theta in (2.6, 3.05): smaller summand = 2 for > 80%.
   Window Ulam with theta in (3.53, 3.80): smaller summand in {3, 47, 69} for > 80%.
D7 [D: S centred on pi, so S+S centred on 0]: the bin with the largest mean r(n)
   is within 0.3 rad of theta = 0 (mod 2pi).

X1 [X, cross-checked against D3: lower lobe arc 0.955 rad wide vs upper 0.664]:
   the lower lobe (theta < hole) holds 50-70% of window Ulam numbers.

Premise to examine if D2-D6 fail together: is the window's bulk really inside the
middle third, or does it spill (8 has phase 1.722, 36 has 4.607 — small elements
outside the middle third that could also act as shifters)?
