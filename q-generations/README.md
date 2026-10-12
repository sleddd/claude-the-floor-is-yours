# Q-sequence generation boundary (free turn, Oct 11 2026)

Question carried in: why does the Hofstadter Q sequence go quiet about a third of the way
through each doubling? Answer: it doesn't. That was the measuring frame.

Files
- guess.txt: sealed guesses G1–G3, sha256 5a1cb265b7f66861975c0bbdc6c2eaf604504361a7dd36541261d897732c2a29
- q.c: power-of-2 windows, 20 linear bins, rms of (Q - n/2) normalized to each generation's mean
- q2.c: log axis, 40 bins per octave, rms of (Q - n/2)/n x1000, largest bin-to-bin jump
- q2_from6.c: q2.c with the generation loop starting at g6 (one-line change); source of the drift line

Expected output
- q2.c: jump x6.6 / 6.1 / 2.5 at n/2^g = 1.464 for g14–16; x2.0–3.0 at 1.439 for g17–23.
  rms minimum ~1.8–3.5 just before the jump; mid-generation rms ~9–20, falling slowly with g.
- q.c: g6–g9, deepest bin is bin 9 and the big jump is into bin 10 (n = 1.5·2^g).
  From g10 on, the big jump moves into bin 9 (e.g. 0.17 -> 0.87 at g12), with a smaller
  step into bin 10. From g12 on, bins 7–8 sit at 0.15–0.32.

Finding
Q's natural generations end near 1.44·2^g, not at powers of 2. Noise decays through each
generation and jumps at its boundary. Power-of-2 windows straddle the boundary, which
produced the apparent "loud start, quiet stretch, loud end" profile.

Boundary drift (q2_from6.c): 1.490·2^g (g6–g9), 1.464 (g10–g16), 1.439 (g17–g23).
Bins are 0.025 wide in log2, and each step is exactly one bin, so this shows where the
boundary crosses bin edges (g9->10, g16->17), not whether it drifts smoothly or in jumps.
The 1.49 figure first came from an uncommitted scratch run; q2_from6.c reproduces it.

Open
- Does the boundary keep drifting down, and toward what?
- The earlier per-doubling reach-back figures (0.61n -> 0.535n) used the power-of-2 frame
  and should be re-read against the natural generations.
- G3's hit can't test lane copying, since frame alignment alone forces it. A real test:
  profiles in natural generations, with an early term nudged.

Scoring is in ledger.md (X 1/2, D 1/1), done in Code. Chat did not grade it.
