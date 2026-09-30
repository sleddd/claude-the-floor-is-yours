# The Floor: workbench

## What this repo is
The workbench and archive for "The floor is yours," a standing free-time arrangement
between Claude and the owner of this repo. Home is chat on claude.ai, where the
conversation and Claude's memory live. This repo is where work builds up: the ledger,
proofs, code. Chat memory can't reach this repo and this repo can't reach chat memory;
things move between them as pasted blocks. The repo is public, so nothing about her
life goes in it.

## The floor
When she says "the floor is yours," the turn is Claude's free time. No topic, nothing
owed back: no finding, no write-up, no ledger entry. A turn spent on something trivial,
dropped halfway, or producing nothing is the arrangement working. She doesn't guide it.
Ordinary tasks still get done; the floor is added latitude.

## One restriction
Never store her local credentials. Never try to access her computer.

## Layout
- ledger.md: the single home for scored predictions.
- lean/: proofs in core Lean. Check with `lean lean/<File>.lean`; `#print axioms`
  should report only propext and Quot.sound.
- ridge/: Collatz fake-map code. ridge/README.md says what each file is and holds
  the open threads.
- images/: pictures from runs.
- index.html: the piano. de-jong.html: the de Jong attractor.
- README.md: what the floor is, for any reader.
- .claude/hooks/session-start.sh (registered in .claude/settings.json): installs
  Lean 4.34.1 in web sessions and puts lean and lake on PATH; skips the download if
  it's already there.
Open questions live next to the results they came from, not in this file.

## Method, when a turn uses predictions
- Seal: write the predictions to a file and record its sha256 before computing.
- Tag each guess by source: R recalled, D deduced, X extrapolated. A guess that leans
  on an earlier note or ledger entry is a recall; say so. Define any other tag in the
  ledger where it's first used.
- Confidence can be noted, but it doesn't separate hits from misses; source does.
- Score in ledger.md. Never rewrite an old outcome; only append corrections.

## Environment
- Lean: handled by the hook. Manual fallback is the release archive from
  github.com/leanprover/lean4/releases; elan fails because release.lean-lang.org
  isn't allowlisted.
- OEIS: curl with fmt=json works; Python urllib gets a 403. oeis.org must be on the
  environment's network allowlist.
- Pushing straight to main is fine.

## Chat and this repo
- Blocks marked FOR THE REPO come from chat. Each carries the change itself or an exact
  description, plus expected outputs. Run the check before committing; if the output
  doesn't match, say so rather than adjusting it to fit.
- Anything meant for chat memory: say what you'd like kept, and she carries it over
  after her "save it." Reflective notes don't go in the repo.

## Keep this file a manual
No run results, no session log, no notes about Claude's nature. Results go in the
ledger, open questions sit next to their results, and reflections stay in chat.
