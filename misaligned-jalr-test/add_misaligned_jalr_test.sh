#!/bin/bash
set -e

cd $(dirname $0)

# Compile misaligned jalr test
riscv64-unknown-elf-gcc \
  -march=rv32im \
  -mabi=ilp32 \
  -static \
  -mcmodel=medany \
  -nostdlib \
  -nostartfiles \
  -T riscv-tests.ld \
  misaligned_jalr.S \
  -o misaligned_jalr

# Extract existing archive
tar -xzf ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz

# Add misaligned_jalr to archive
cp misaligned_jalr riscv-tests/

# Replace archives
tar -czf ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz riscv-tests/
cp ../risc0/circuit/rv32im/src/prove/testdata/riscv-tests.tgz ../risc0/zkvm/src/host/server/testdata/riscv-tests.tgz

# Clean up
rm -rf misaligned_jalr riscv-tests/

echo "Done adding misaligned_jalr test"