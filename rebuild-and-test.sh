cd risc0/r0vm
cargo build
cd ../../tools/elf-to-bin
cargo build
cd ../../risc0/zkos/linux
#CC=~/riscv/bin/riscv32-unknown-elf-gcc +nightly cargo build -Zbuild-std=core --target riscv32im-unknown-none-elf
cargo risczero bake
#cp ~/risc0/target/riscv32im-unknown-none-elf/debug/vmlinuz elfs/vmlinuz.elf
cd ~/risc0
mkdir -p test-bins test-logs
(for x in ~/riscv-tests/isa/*-p-*.dump; do target/debug/elf-to-bin --guest-elf ~/riscv-tests/isa/`basename $x .dump` --kernel-elf ~/risc0/risc0/zkos/linux/elfs/vmlinuz.elf --output test-bins/`basename $x .dump`.bin; done)
for x in test-bins/*; do RISC0_DEV_MODE=1 RUST_LOG=trace target/debug/r0vm --elf $x &> test-logs/`basename $x`.log; done
echo "Exit codes (sys_exit is good, others should ideally indicate the test number but doesn't always):"
grep sys_exit test-logs/*
echo "Crashes totally"
grep -L sys_exit test-logs/*