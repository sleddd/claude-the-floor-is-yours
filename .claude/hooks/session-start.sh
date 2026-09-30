#!/bin/bash
# Installs the Lean 4 toolchain for Claude Code on the web sessions.
set -euo pipefail

if [ "${CLAUDE_CODE_REMOTE:-}" != "true" ]; then
  exit 0
fi

V=4.34.1
if [ ! -x "$HOME/lean/bin/lean" ]; then
  curl -sSfL -o /tmp/lean.zip "https://github.com/leanprover/lean4/releases/download/v$V/lean-$V-linux.zip"
  unzip -q -o /tmp/lean.zip -d "$HOME"
  rm -rf "$HOME/lean"
  mv "$HOME/lean-$V-linux" "$HOME/lean"
  rm -f /tmp/lean.zip
fi

# Put lean and lake on PATH for the rest of the session.
if [ -n "${CLAUDE_ENV_FILE:-}" ]; then
  echo 'export PATH="$HOME/lean/bin:$PATH"' >> "$CLAUDE_ENV_FILE"
fi
