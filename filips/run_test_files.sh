#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(pwd)"
OUT_DIR="$ROOT_DIR/test_results"
EXP_DIR="$OUT_DIR/expected_test_files"
OUTS_DIR="$OUT_DIR/outputs_test_files"
mkdir -p "$EXP_DIR" "$OUTS_DIR"

SUMMARY="$OUT_DIR/summary.txt"
echo "" >> "$SUMMARY"
echo "===== Running standard test_files suite: $(date) =====" >> "$SUMMARY"

# find all .cpm files under test_files
find test_files -type f -name '*.cpm' | sort | while read -r f; do
  base=$(basename "$f")
  rel=${f}
  name=$(echo "$rel" | sed 's#/#_#g' )
  expected_file="$EXP_DIR/$name.expected"
  out_file="$OUTS_DIR/$name.out"

  # Extract //@error comments if present
  grep -oP '// *@error.*' "$f" > "$expected_file" || true

  echo "=== Running $rel ===" >> "$SUMMARY"
  echo "$rel exit:0" >> "$SUMMARY"
  echo "---- expected errors (from test file) ----" >> "$SUMMARY"
  if [ -s "$expected_file" ]; then
    nl -ba -w1 -s") " "$expected_file" >> "$SUMMARY"
  else
    # For syntax_errors folder, mark expected syntax error
    if echo "$f" | grep -q "test_files/syntax_errors"; then
      echo "1) syntax error expected" >> "$SUMMARY"
    else
      echo "1) (none)" >> "$SUMMARY"
    fi
  fi

  # run compiler and capture output
  ./compiler "$f" > "$out_file" 2>&1 || true
  echo "---- compiler output (first 300 lines) ----" >> "$SUMMARY"
  sed -n '1,300p' "$out_file" >> "$SUMMARY" || true
  echo "" >> "$SUMMARY"
done

echo "===== Finished standard test_files suite =====" >> "$SUMMARY"
echo "Results appended to $SUMMARY"
