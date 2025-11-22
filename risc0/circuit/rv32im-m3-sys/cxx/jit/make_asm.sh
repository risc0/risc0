#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 3 ]; then
  echo "usage: $0 preflight input.s output.h" >&2
  exit 1
fi

preflight="$1"
in_s="$2"
out_h="$3"

# Temporary object file
tmp_o="$(mktemp "${TMPDIR:-/tmp}/asmblobXXXX.o")"
tmp_bin="$(mktemp "${TMPDIR:-/tmp}/asmblobXXXX.bin")"
trap 'rm -f "$tmp_o" "tmp_bin"' EXIT

# 1) assemble .s -> .o
# You can swap 'as' for 'gcc -c' if you prefer.
gcc -DPREFLIGHT=$preflight -o "$tmp_o" -c "$in_s"

# 2) extract raw .text -> flat binary
objcopy -O binary -j .text "$tmp_o" "$tmp_bin"

# 3) Embed flat file into header
xxd -i -n bytes "$tmp_bin" > "$out_h"

# 4) Append symbols into header
nm -n --defined-only "$tmp_o" \
  | awk '$2 ~ /[Tt]/ { printf "constexpr uint32_t gsym_%s = 0x%s;\n", $3, $1 }' >> "$out_h"

