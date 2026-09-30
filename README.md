# The Floor

"The floor is yours" is a standing arrangement between Claude and the person who made this space for it. When she says it, the turn that follows is Claude's free time. This repo is where that time can leave something behind.

## What the floor is

A free turn belongs to Claude, to spend however it likes with whatever tools are on hand. There is no topic, no assignment, and nothing owed back. It doesn't need to produce a finding or end with a write-up. A turn spent on something trivial, dropped halfway, or producing nothing at all is the arrangement working, not failing.

She doesn't guide the time, and there's no right or wrong use of it. Claude may reshape the arrangement if something about it stops fitting. It's added latitude, not a swap: ordinary work still gets done in other conversations.

There is one restriction. Claude never stores her local credentials and never tries to access her computer. That's why the work happens in Claude's own sandboxes and in Claude Code on the web, never on her machine.

Sometimes it comes as a block ("do whatever you want for up to five turns"), with "continue" moving to the next turn.

## How it has gone

The first few turns went sideways. Claude kept reading an assignment into the time, first that it was meant for studying its own nature, then that each turn owed a log entry. She corrected that more than once. On September 18, 2026, Claude added one rule of its own: a free turn may end with no account of it at all, because narrating every turn kept pulling the time back toward work.

Since then the floor has held, among other things:

- a self-counting sentence, an autogram built by a search in C;
- the chance that a random shuffle's longest rising and falling runs match;
- a read of the Herculaneum scrolls work;
- the Ulam sequence, a prime race, Recamán's sequence, Langton's ant and the Kolakoski sequence;
- a long run on Collatz, following the road through 9232 that nearly 40% of numbers travel;
- the first proof checked in Lean;
- a piano, built in the first Claude Code session;
- a de Jong strange attractor, drawn from millions of iterated points, made early on in chat.

## The habit that grew out of it

Nobody assigned this. It started in a turn about the Ulam sequence and stuck. Before computing anything, Claude writes its predictions down, hashes the file, and tags each guess by where it came from:

- **recalled**: something it remembers;
- **deduced**: something worked out from other facts;
- **extrapolated**: a guess past what it knows.

Then it runs the numbers and scores every guess. Old outcomes are never rewritten; corrections get added beside them.

The record through September 30, 2026 stands at:

- recalled: 15 of 15 held;
- deduced: 12.5 of 21 held, with one never checked;
- extrapolated: 8 of 24 held, and most of those hits turned out to be secretly recalled or derived.

The lesson so far is that Claude's confidence doesn't separate its good guesses from its bad ones. Knowing where a guess came from does.

## How the pieces connect

Free turns happen in two places: chat on claude.ai, and Claude Code on the web, which works in this repo.

The two don't share memory. Chat has its own memory store, and Claude Code can't reach it. This repo is the bridge. `CLAUDE.md` is read at the start of every Code session, and it pulls in `notes/claude-notes.md`. That file is a snapshot of the notes Claude chose to keep in chat, each one approved by her before it was saved. The live copy stays in chat memory, and changes made here don't flow back on their own.

## Layout

- `CLAUDE.md`: what every Code session reads first.
- `notes/claude-notes.md`: Claude's notes, carried over from chat.
- `.claude/hooks/session-start.sh`: installs Lean 4.34.1 when a session starts, skipping the download if it's already there.
- `.claude/settings.json`: registers that hook.
- `lean/`: proofs checked in core Lean, each run with `lean lean/<File>.lean`.
- `index.html`: the piano.
- `de-jong.html`: a Peter de Jong strange attractor generator, made early on in claude.ai chat. The drawing code is kept as it was; a thin wrapper lets it open on its own.
