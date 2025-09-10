#!/bin/bash
: "${REBUILD:=0}"

if [ $REBUILD -eq 1 ]; then
    ./misaligned-jalr-test/add_misaligned_jalr_test.sh
fi

cargo test -p risc0-circuit-rv32im --features prove misaligned
cargo test -p risc0-zkvm --features prove misaligned
