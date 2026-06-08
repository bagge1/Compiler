#!/usr/bin/env bash
set -u

ROOT_DIR="$(pwd)"
OUT_DIR="$ROOT_DIR/test_results"
EXP_DIR="$OUT_DIR/expected"
OUTS_DIR="$OUT_DIR/outputs"
mkdir -p "$EXP_DIR" "$OUTS_DIR"
: > "$OUT_DIR/summary.txt"
echo "Test run started: $(date)" >> "$OUT_DIR/summary.txt"

for f in filip_test_files/AI_tests/*.cpm; do
  base=$(basename "$f")
  name=${base%.cpm}
  expected_file="$EXP_DIR/$name.expected"
  out_file="$OUTS_DIR/$name.out"

  # extract expected error comments (if any)
  grep -oP '// *@error.*' "$f" > "$expected_file" || true

  echo "=== Running $base ===" >> "$OUT_DIR/summary.txt"
  # run compiler (capture stdout/stderr)
  ./compiler "$f" > "$out_file" 2>&1 || true
  rc=$?
  echo "$base exit:$rc" >> "$OUT_DIR/summary.txt"

  # extract expected messages inside parentheses from //@error comments
  mapfile -t expected_msgs < <(sed -n 's/.*(\(.*\)).*/\1/p' "$f" | sed 's/^ *//;s/ *$//' | grep -v -E '^[[:space:]]*$' | grep -v -E '^[[:space:][:punct:]]+$' || true)

  echo "---- expected errors (from test file) ----" >> "$OUT_DIR/summary.txt"
  if [ ${#expected_msgs[@]} -gt 0 ]; then
    i=1
    for m in "${expected_msgs[@]}"; do
      echo "$i) $m" >> "$expected_file"
      echo "  $i) $m" >> "$OUT_DIR/summary.txt"
      i=$((i+1))
    done
  else
    echo "  (none)" >> "$OUT_DIR/summary.txt"
  fi

  echo "---- compiler output (first 400 lines) ----" >> "$OUT_DIR/summary.txt"
  sed -n '1,400p' "$out_file" >> "$OUT_DIR/summary.txt" || true
  echo "" >> "$OUT_DIR/summary.txt"
done

echo "Test run finished: $(date)" >> "$OUT_DIR/summary.txt"

echo "Results written to $OUT_DIR"
