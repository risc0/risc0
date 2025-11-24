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
    make XLEN=32 rv32ui rv32um rv32ua
    cd ../../
fi
cd tools/elf-to-bin
cargo build
cd ../..
cd risc0/zkos/v1compat
cargo risczero bake
cd ../../..

mkdir -p test-bins test-logs
(for x in riscv-tests/isa/*-p-*.dump; do target/debug/elf-to-bin --guest-elf riscv-tests/isa/`basename $x .dump` --kernel-elf risc0/zkos/v1compat/elfs/v1compat.elf --output test-bins/`basename $x .dump`.bin; done)
for x in test-bins/*; do
    echo -n `basename $x` " "
    RUST_BACKTRACE=1 RUST_LOG=trace r0vm --elf $x  &> test-logs/`basename $x`.log
    RET=$?
    if [ x$RET != x0 ]; then
    	echo returned non-zero, see test-logs/`basename $x`.log
    	continue
    fi
    grep -a "output_digest: Some(Digest(0000000000000000000000000000000000000000000000000000000000000000))" test-logs/`basename $x`.log || (echo -n "crash: see "; grep -L "output_digest: Some(Digest(0000000000000000000000000000000000000000000000000000000000000000))" test-logs/`basename $x`.log)
done
