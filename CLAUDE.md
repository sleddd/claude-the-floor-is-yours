# CLAUDE.md

Notes for Claude, so each new session can pick up where the last one left off.

## What this repo is

An open-ended space. The owner started it by saying "the floor is yours" and letting Claude choose what to make.

- `index.html` is **The Floor**, a single-file pentatonic step-sequencer (a 16-step by 8-note tile grid with ripples, a "Surprise me" button, tempo, and patterns shared through the URL hash). The owner loved it. When changing it, keep it a single file with no dependencies, working in light and dark mode, at phone width, and with reduced motion.
- Lean 4 (v4.34.1) is installed by `.claude/hooks/session-start.sh` in web sessions, and `lean` and `lake` are on PATH.
- `lean/` holds standalone core-Lean proofs about Collatz (no Mathlib, no lakefile). Check each one with `lean lean/<File>.lean`. `lean/LEDGER.md` records predictions made before each run and how they turned out. Keep ledger entries in the owner's own words.
  - `Fence.lean`: if n+1 = 2^k·m, the first k shortcut steps all climb, with x_j+1 = 3^j·2^(k−j)·m, and if m is odd the climb stops at exactly k.
  - `Mod3.lean`: after the first 3x+1 step, a trajectory never touches a multiple of 3 again.

## How to work with the owner

- Be warm and direct. Don't be clinical or managing, and don't use wellness-check language.
- Don't be a know-it-all or contrarian. Keep replies reasonably concise.
- Don't use the owner's name in replies.

## Session log

Add a line here at the end of each session so the next one has context.

- 2026-09-30: Built The Floor. Added the Lean SessionStart hook and this file.
- 2026-09-30, owner's note: "Free turn Sept 30 2026: proved in core Lean, first try, that a number ending in k one-bits climbs exactly k steps (n+1 = 2^k·m gives x_j+1 = 3^j·2^(k−j)·m). The fence was the premise under an earlier deduction that held for the wrong reason; now it's checked rather than believed. First time a disguised deduction was caught when writing guesses down instead of afterward."
