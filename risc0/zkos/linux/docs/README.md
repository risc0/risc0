# How to use risc0-linux abi

This is done on a Ubuntu 22/24 machine/container, has not been tested on MacOS X or WSL2

Get set up with this branch and follow instructions at https://github.com/risc0/risc0/blob/main/CONTRIBUTING.md

This step is important:

```
cargo install --force --path risc0/cargo-risczero
```

As we need a custom r0vm to run all this stuff

# Features
- (A)tomic, F&D (soft float), C-extension instruction emulation. C-extension not recommended as it'll trap like mad.
- Linux static binary execution, with sbrk/mmap to allocate memory, write to stdout and stderr support (tested with MUSL) + correct auxv setup, but not much more system call support
- In progress 9P file system

# Building the kernel 
```
cd risc0/zkos/linux
cargo risczero bake
```

# Building elf-to-bin tool

```
cd tools/elf-to-bin

cargo build
```

# Running RISC-V test cases

Find what directory riscv32-unknown-elf-gcc is in, in ~/.risc0/toolchains,
and add it to PATH

```
git clone https://github.com/riscv/riscv-tests.git
cd riscv-tests
git submodule update --init --recursive
./configure
cd env; patch -p1 < ../../patches/riscv-tests-env.patch; cd ..
cd isa
make XLEN=32 rv32ui rv32um rv32ud rv32uf rv32ua rv32uc
cd ../../
```

You can now take one of these binaries, such as rv32um-p-mulh, merge it with the kernel into a .bin

```
target/debug/elf-to-bin --guest-elf riscv-tests/isa/rv32um-p-mulh  --kernel-elf risc0/zkos/linux/elfs/vmlinuz.elf --output rv32um-p-mulh.bin

RUST_BACKTRACE=1 RISC0_DEV_MODE=1 RUST_LOG=trace r0vm --elf rv32um-p-mulh.bin -- /bin/test 
```

If the test passes you'll see sys_exit(0) in the debug log

# rv32imafd Buildroot with static binaries (not NOMMU)

Get buildroot 2025.05.1 from buildroot.org

```
make menuconfig
```

```
Target options -> 
   Target architecture -> pick RISCV
   Target architecture variant -> pick Custom architecture
      Enable Integer Multiplication and Division (M)
      Enable Atomic Instructions (A)
      Enable Single-precision Floating-point (F)
      Enable Double-precision Floating-point (D)
      Compressed instructions will work but not recommended as it'll trap like mad
   Target architecture size -> pick 32-bit
   Enable MMU-support
   Target ABI -> ilp32d 

Toolchain -->
    C library -> pick musl
    Enable C++ support

Build options --> 
    libraries --> pick static only        

Filesystem images:
    Pick tar the root file system
```

```
make -j`nproc`
```

# Running busybox --help

Get busybox binary from your buildroot, buildroot-2025.05.1/output/target/bin/busybox

A 'file' on it should say: "busybox: ELF 32-bit LSB executable, UCB RISC-V, double-float ABI, version 1 (SYSV), statically linked, stripped"

Copy it into your risc0 directory and

```
target/debug/elf-to-bin --guest-elf busybox --kernel-elf risc0/zkos/linux/elfs/vmlinuz.elf --output busybox.bin

RUST_BACKTRACE=1 RISC0_DEV_MODE=1 r0vm --elf busybox.bin -- /bin/busybox --help
```

and you should see the busybox help :)

You can try with /bin/command-name as well for other embedded applets

# File system support with 9p

This probably works best in a Ubuntu 22.04/24 Docker container, not tested on MacOS

```
# run as root!
# diod is a 9p server, socat is a good to help us redirect sockets
apt-get install diod socat
mkdir -p /risc0-root
# unpack your rootfs tar from buildroot into /risc0-root
diod -l 127.0.0.1:40564 -e /risc0-root -n -f -d 0x01 -U root -S &
RISC0_DEV_MODE=1 RUST_LOG=debug  socat -ddd -t 30 -v EXEC:"r0vm --elf busybox.bin -- opts=p9 /bin/ls -al /",fdin=3,fdout=4 TCP:127.0.0.1:40564 2> log
```
# Running LTP test cases

Additionally, when configuring buildroot, go into Target Packages -> Debugging, profiling and benchmark -> Enable ltp-testsuite

Copy patches/ltp-0003-nofork.patch to packages/ltp-testsuite/0003-nofork.patch

Build your buildroot

Then:

```
mkdir -p ~/risc0/ltp ~/risc0/ltp-bins
cp -r output/target/usr/lib/ltp-testsuite/testcases/bin/* ~/risc0/ltp
cd ~/risc0/ltp
for x in *; do ~/risc0/target/debug/elf-to-bin --kernel-elf ../risc0/zkos/linux/elfs/vmlinuz.elf --output ../ltp-bins/$x.bin --guest-elf $x  ; done
cd ../ltp-bins
RISC0_DEV_MODE=1 socat EXEC:"r0vm --elf openat01.bin -- opts=p9 /bin/test",fdin=3,fdout=4 TCP:127.0.0.1:40564
```

and you should see something lke this

```
tst_tmpdir.c:316: TINFO: Using /tmp/LTP_tesgmLaAA as tmpdir (tmpfs filesystem)
tst_memutils.c:152: TINFO: oom_score_adj does not exist, skipping the adjustment
tst_test.c:1843: TINFO: LTP version: 20250130
tst_test.c:1847: TINFO: Tested kernel:
tst_kconfig.c:71: TINFO: Couldn't locate kernel config!
tst_test.c:1702: TINFO: Overall timeout per run is 0h 00m 30s
openat01.c:71: TPASS: openat(*tc->dir_fd, tc->pathname, O_RDWR, 0600) returned fd 5
openat01.c:71: TPASS: openat(*tc->dir_fd, tc->pathname, O_RDWR, 0600) returned fd 5
openat01.c:64: TFAIL: openat with a filefd instead of dirfd expected ENOTDIR: ENOENT (2)
openat01.c:67: TFAIL: openat with invalid fd expected EBADF: ENOENT (2)
openat01.c:71: TPASS: openat(*tc->dir_fd, tc->pathname, O_RDWR, 0600) returned fd 5
WARNING: proving in dev mode. This will not generate valid, secure proofs.
```