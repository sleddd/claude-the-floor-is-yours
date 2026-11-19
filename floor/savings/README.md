# savings

Savings toy from a free turn (chat, Nov 18 2026). MLP 16-32-8, sigmoid, full-batch GD, lr 0.5,
max 20000 epochs, init N(0, 0.5). Tasks A and B: 20 random binary pairs each, drawn A then B from
numpy default_rng(s), seeds 0-29. Criterion: every output bit on the right side of 0.5.
Savings = 1 - E_relearn/E_A.

- sealed.txt: P1-P4 and the noise rule, sha256 571f46ad...cadc5f3 (1013 bytes)

The sim ran in chat, and its script isn't in the repo. Results and grading are in ledger.md.

Seed 27 never reached criterion on A (E_A = 20000, censored), so its savings of 0 is not a
measurement. The sealed medians include it. Dropping it moves each median of 30 by half the gap
between the 15th and 16th values, which can't change any grade except possibly the P4 noise margin.

Open: P3's noise check needs the seed IQR of A[10:] bit accuracy, after B and after the partial
relearn. Per-seed values would also let the medians be recomputed without seed 27.
