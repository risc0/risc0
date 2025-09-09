#!/bin/bash
riscv32-unknown-elf-gcc -v 
if [ $? -ne 0 ]; then
    echo "riscv32-unknown-elf-gcc not found, look for it in ~/.risc0/toolchains/v2024.1.5-cpp*/bin/ and add to PATH"
    exit 1
fi
if [ ! -d riscv-tests ]; then
    git clone https://github.com/riscv/riscv-tests.git
    cd riscv-tests
    git submodule update --init --recursive
    ./configure
    cd env; patch -p1 < ../../patches/riscv-tests-env.patch; cd ..
    cd isa
    make XLEN=32 rv32ui rv32um rv32ud rv32uf rv32ua
    cd ../../
fi
cd risc0/r0vm
cargo build
cd ../../tools/elf-to-bin
cargo build
cd ../../risc0/zkos/linux
cargo risczero bake
cd ~/risc0
mkdir -p test-bins test-logs
(for x in riscv-tests/isa/*-p-*.dump; do target/debug/elf-to-bin --guest-elf riscv-tests/isa/`basename $x .dump` --kernel-elf ~/risc0/risc0/zkos/linux/elfs/vmlinuz.elf --output test-bins/`basename $x .dump`.bin; done)
for x in test-bins/*; do RISC0_DEV_MODE=1 RUST_LOG=trace target/debug/r0vm --elf $x &> test-logs/`basename $x`.log; done
echo "Exit codes (sys_exit is good, others should ideally indicate the test number but doesn't always):"
grep sys_exit test-logs/*
echo "Crashes totally"
grep -L sys_exit test-logs/*