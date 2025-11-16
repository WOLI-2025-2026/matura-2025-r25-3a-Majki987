#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
  echo "Użycie: $0 nazwa{numer}_{numer}.txt"
  exit 2
fi

FILE="$1"

echo "$(pwd)"

# katalog skryptu: tests/
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

RESOLVED="$REPO_ROOT/src/$FILE"           # plik od studenta
EXPECTED="$SCRIPT_DIR/expected/$FILE"     # wzorzec

if [[ ! -f "$RESOLVED" ]]; then
  echo "Brak pliku rozwiązania: $RESOLVED"
  exit 1
fi
if [[ ! -f "$EXPECTED" ]]; then
  echo "Brak pliku wzorcowego: $EXPECTED"
  exit 1
fi

# Opcjonalnie ignoruj białe znaki: ustaw IGNORE_WS=1 w env teście
DIFF_OPTS=(--strip-trailing-cr)
if [[ "${IGNORE_WS:-0}" != "0" ]]; then
  DIFF_OPTS+=(-w)
fi

if diff -u "${DIFF_OPTS[@]}" "$EXPECTED" "$RESOLVED" > /dev/null; then
  echo "OK: $RESOLVED zgodny z $EXPECTED"
  exit 0
else
  echo "BŁĄD: $RESOLVED różni się od wzorca"
  diff -u "${DIFF_OPTS[@]}" "$EXPECTED" "$RESOLVED" || true
  exit 1
fi
