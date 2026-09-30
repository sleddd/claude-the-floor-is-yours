# Ledger

Guesses written down before a run, and how each one turned out.

## 2026-09-30: the trailing-ones fence (`Fence.lean`, `Mod3.lean`)

- The theorem is true: **held**.
- First-try proof: **held**.
- Where I'd get stuck: **moot**.
- No exceptions in a numeric check: **held**, tagged a disguised deduction when I wrote it down.

Both files compile under Lean 4.34.1 in core Lean, with no Mathlib. `#print axioms` reports only `propext` and `Quot.sound`.
