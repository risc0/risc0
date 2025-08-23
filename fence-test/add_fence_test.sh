#!/bin/bash
set -e

cd $(dirname $0)

# Compile fence test
riscv64-unknown-elf-gcc \
  -march=rv32im \
  -mabi=ilp32 \
  -static \
  -mcmodel=medany \
  -nostdlib \
  -nostartfiles \
  -T riscv-tests.ld \
  fence.S \
  -o fence

# Extract existing archive
tar -xzf ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz

# Add fence to archive
cp fence riscv-tests/

# Replace archives
tar -czf ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz riscv-tests/
cp ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz ../risc0/zkvm/src/host/server/testdata/riscv-tests.tgz

# Clean up
rm -rf fence riscv-tests/

echo "Done"
