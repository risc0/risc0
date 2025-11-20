#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -ne 3 ]; then
  echo "usage: $0 input.s output.bin output.symtab" >&2
  exit 1
fi

in_s="$1"
out_bin="$2"
out_sym="$3"

# Temporary object file
tmp_o="$(mktemp "${TMPDIR:-/tmp}/asmblobXXXX.o")"
trap 'rm -f "$tmp_o"' EXIT

# 1) assemble .s -> .o
# You can swap 'as' for 'gcc -c' if you prefer.
as -o "$tmp_o" "$in_s"

# 2) extract raw .text -> flat binary
objcopy -O binary -j .text "$tmp_o" "$out_bin"

# 3) dump symbol_name<TAB>offset (offset is within .text)
nm -n --defined-only "$tmp_o" \
  | awk '$2 ~ /[Tt]/ { printf "constexpr uint32_t gsym_%s = 0x%s;\n", $3, $1 }' > "$out_sym"
