# Debugging Your zkVM Application with GDB

[gdb][gdb] can be used to debug your zkVM application. This
works via gdb's ability to debug a remote process. Your application will be loaded up in the
executor, then gdb can be attached.

## Installation
A special riscv version of gdb must be used which can be installed using `rzup`.  First, make sure
you have an `rzup` version >= 0.5.0. Then install it by running `rzup install gdb`.

## Compilation
Make sure your guest program has debug symbols enabled, without them it will be difficult to use the
debugger. For Rust, see the [debug cargo option][debug cargo option]

## Running and Attaching gdb
Run your guest program using the `r0vm` binary, but pass the `--with-debugger` flag
```bash
r0vm --elf <guest-program>.bin --with-debugger
```

This will output a command that starts with `riscv32im-gdb ...` which you should run in a separate
terminal.

This should attach gdb to the guest program. Once attached, set any breakpoints you want, the run
`continue` to start execution.

Here is an example of capturing a backtrace from the beginning of `main`.
```bash
> riscv32im-gdb -ex "target remote 127.0.0.1:35051" /tmp/.tmpULKkyS.elf
...
Reading symbols from /tmp/.tmpULKkyS.elf...
Remote debugging using 127.0.0.1:35051
0xc0000000 in ?? ()
(gdb) break main
Breakpoint 1 at 0x200d38: file /risc0/zkvm/src/guest/mod.rs, line 143.
(gdb) continue
Continuing.

Breakpoint 1, risc0_zkvm_platform::syscall::syscall_3 () at /risc0/zkvm/platform/src/syscall.rs:238
238                     ::core::arch::asm!(
(gdb) bt
#0  risc0_zkvm_platform::syscall::syscall_3 () at /risc0/zkvm/platform/src/syscall.rs:238
#1  risc0_zkvm_platform::syscall::sys_write () at /risc0/zkvm/platform/src/syscall.rs:685
#2  risc0_zkvm::guest::env::write::FdWriter::write_bytes<risc0_zkvm::guest::env::journal::{closure_env#0}> ()
    at /risc0/zkvm/src/guest/env/write.rs:53
#3  risc0_zkvm::guest::env::write::{impl#2}::write_slice<risc0_zkvm::guest::env::journal::{closure_env#0},u8> ()
    at /risc0/zkvm/src/guest/env/write.rs:64
#4  risc0_zkvm::guest::env::commit_slice<u8> () at /risc0/zkvm/src/guest/env/mod.rs:398
#5  hello_commit::main () at src/bin/hello_commit.rs:23
#6  hello_commit::zkvm_generated_main::main () at /risc0/zkvm/src/guest/mod.rs:143
(gdb)
```

[gdb]: https://en.wikipedia.org/wiki/GNU_Debugger
[debug cargo option]: https://doc.rust-lang.org/cargo/reference/profiles.html#debug
