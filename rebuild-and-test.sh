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
    make XLEN=32 rv32ui rv32um rv32ud rv32uf rv32ua rv32uc
    cd ../../
fi
cd tools/elf-to-bin
cargo build
cd ../../risc0/zkos/linux
cargo risczero bake
cd ~/risc0
mkdir -p test-bins test-logs
(for x in riscv-tests/isa/*-p-*.dump; do target/debug/elf-to-bin --guest-elf riscv-tests/isa/`basename $x .dump` --kernel-elf risc0/zkos/linux/elfs/vmlinuz.elf --output test-bins/`basename $x .dump`.bin; done)
for x in test-bins/*; do
    echo -n `basename $x` " "
    RISC0_LOG=2 RUST_BACKTRACE=1 RUST_LOG=debug r0vm --elf $x -- /bin/test &> test-logs/`basename $x`.log
    grep -a sys_exit test-logs/`basename $x`.log || (echo -n "crash: no sys_exit, see "; grep -L sys_exit test-logs/`basename $x`.log)
done
