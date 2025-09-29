# How to use risc0-linux (nommu or abi)

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
- S-mode emulation (for running Linux noMMU) with SBI DBCN emulation
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
# diod is a 9p server, socat is a good to help us redirect sockets
apt-get install diod socat
mkdir -p /risc0-root
# unpack your rootfs tar from buildroot into /risc0-root
diod -l 127.0.0.1:40564 -e /risc0-root -n -f -d 0x01 -U yourusername -S &
RISC0_DEV_MODE=1 RUST_LOG=debug  socat -ddd -t 30 -v EXEC:"r0vm --elf busybox.bin -- opts=p9 /bin/ls -al /",fdin=3,fdout=4 TCP:127.0.0.1:40564 2> log
```

# Experimental: Linux nommu

Grab https://github.com/riscv-collab/riscv-gnu-toolchain/releases/tag/2025.09.16 riscv32-glibc-ubuntu-gcc toolchain (we need this to make a relocatable kernel, bare metal isn't enough), unpack it so that ~/riscv/bin/riscv32-unknown-linux-gnu-gcc exists

Get a copy of linux-6.16.7.tar.xz and unpack it, then in linux-6.16.7
```
patch -p1 < ~/risc0/patches/linux-6.16.7-risc0-nommu-defconfig 
cp ~/risc0/patches/linux-6.16.7-risc0-nommu-defconfig .config
```

And build it:

```
make ARCH=riscv CROSS_COMPILE=~/riscv/bin/riscv32-unknown-linux-gnu- -j$(nproc) vmlinux
```

cp the vmlinux into your risc0 and
```
target/debug/elf-to-bin --guest-elf vmlinux --kernel-elf risc0/zkos/linux/elfs/vmlinuz.elf --output vmlinux.bin

RUST_BACKTRACE=1 RISC0_DEV_MODE=1 r0vm --elf vmlinux.bin
```

and you should see it start up and fail to mount a root file system

# Buildroot with uclibc and flat binaries (static binaries), for Linux noMMU

Do as before but now (in a new fresh directory) with these options instead:

```
Target options -> MMU support disabled
Filesystem images -> cpio the root file system
```

and

```
make -j `nproc`
```

We now go over to the kernel and bundle the resulting initramfs with the kernel image:

```
make ARCH=riscv CROSS_COMPILE=~/riscv/bin/riscv32-unknown-linux-gnu- CONFIG_INITRAMFS_SOURCE=$HOME/buildroot-2025.05.1/output/images/rootfs.cpio -j$(nproc) vmlinux
```

and we now elf-to-bin and r0vm again -- and see it boot up a linux userland and then idle