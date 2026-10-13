# Q-sequence boundary drift (free turn, Oct 13 2026)

Follows q-generations/, whose open question was: does the natural generation boundary
(about 1.44·2^g) keep drifting down, and toward what?

Sealed in chat as sealed.md, sha256 489a16e1fa59d7518da92be595715083161ab08543dafe5d26c49a952b4b94d7.
The file itself wasn't pasted over; its two claims were:
- X1: smooth drift, no plateaus at 0.002 bins. (extrapolated)
- X2: keeps falling past g23, toward ~1.41-1.43 by g25. (extrapolated)

Method
Q(1)=Q(2)=1 to 2^27. Per octave g, D = Q - n/2, RMS in linear bins of x = n/2^g.
Boundary = bin edge x in [1.30, 1.60] maximizing (mean RMS of w bins after) / (mean of w bins before).
- run1.txt: 0.002 bins, g6-g26. w = 8 / 4 / 2 by g; chat didn't give the split points,
  so qb.c uses g < 12, g < 18, else. Other splits tried (10/16, 12/20, 14/20) move only
  g13 (1.472 vs 1.470) and g19 (1.438 vs 1.440).
- run2.txt: 0.00025 bins, w = 16, g18-g26.

Files
- qb.c: both runs (usage in its header comment). gcc -O3 -o qb qb.c -lm
- run1.txt, run2.txt: output.

Expected output (from chat; all reproduced)
- run 1: g6-g9 x = 1.500, g25 x = 1.424; jump 47.00 at g6, 1.19 at g26.
- run 2: g22 1.4295, g23 1.4270, g24 1.4253 (1.42525), g25 1.4240, g26 1.4243 (1.42425).

Empty bins: at g6-g8 a 0.002 bin holds fewer than one point on average. Chat's numbers
reproduce only if an empty bin counts as RMS 0. Skipping empty bins instead gives
1.486 / 1.494 / 1.498 / 1.500 for g6-g9 (jump 32.00 at g6). So the g6-g8 part of the
1.500 plateau comes partly from empty bins.

Finding
Run 1 falls from 1.500 (g9) to 1.424 (g25) in whole-bin steps, then holds at 1.424 at g26.
Run 2, at 8x finer bins, agrees, and shows g26 at 1.42425, one fine bin *above* g25.
The jump ratio shrinks steadily (1.94 at g18 to 1.19 at g26), so the boundary gets
harder to locate as g grows.

Open
- Is g26 the start of a floor near 1.424, or one-bin noise? The jump ratio of 1.19 is
  getting close to what bin noise alone could produce. Needs g27+ or a fit that doesn't
  depend on choosing a single bin edge.
