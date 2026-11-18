# recovery

Hopfield recovery toy from a free turn (chat, Nov 17 2026). N=200. Baseline A stored at s0=1.
Stress adds eta*T*BB^T/N with eta=0.01. Then 400 days of: random cue, async settle (10 sweeps),
W = (1-0.01)W + r*xx^T/N, diagonal zeroed. Outcome: mode of the last 20 days at |overlap| > 0.9.
40 seeds per cell.

- sealed_p1-p4.txt: P1-P4, sha256 0dd554f6...3023a828
- sealed_f1.txt: the same plus F1, sealed before the r sweep ran, sha256 b1fea864...e768014a

The sim ran in chat, and its script isn't in the repo. Results and grading are in ledger.md.

Open: the r sweep has only three T values (50, 100, 150). A finer T grid at r = 0.01, 0.05 and 0.2,
with more seeds, would show whether the width ordering is more than seed noise.
