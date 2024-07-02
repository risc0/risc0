# Rust Crates that bind to C++

Rust crates may bind to C++ code to enable the crate to run time-tested C++ code
from Rust and for projects such as [BLST] that implement core algorithms in C++
and create bindings to work across many languages. The RISC Zero supports these
crates by providing a toolchain to build C++ code.

## How to Install the C++ toolchain

The C++ toolchain is installed alongside the Rust toolchain. Installation
instructions can be found [here][install].

## How to Build and Run these crates

RISC Zero has a GCC-based C++ toolchain to enable these crates to build and run
on the RISC Zero zkVM. The toolchain can be installed by running `cargo risczero
install`. This command will download the guest Rust toolchain as well as a C++
toolchain that compiles C++ to riscv32im. After installing the toolchain, these
crates can be built and run on the zkVM like any other Rust crate. Under the
hood, the `risc0-build` crate will use the downloaded toolchain while building
the guest crate. The C++ toolchain is typically used by the `build.rs` file of
crates that use C++ code.

## Overriding the C++ toolchain

The guest C++ toolchain can be overridden by setting the
`CC_riscv32im_risc0_zkvm_elf` and `CFLAGS_riscv32im_risc0_zkvm_elf` environment
variables when running the `cargo build` command like so:

```bash
CC_riscv32im_risc0_zkvm_elf="[path to C++ compiler]" CFLAGS_riscv32im_risc0_zkvm_elf="[desired cflags]" cargo build
```

When overriding the C++ toolchain for experimentation purposes, the C++ compiler
must be configured to generate riscv32im instructions. This can be done by setting
`CFLAGS_riscv32im_risc0_zkvm_elf="-target riscv32-unknown-elf -march=rv32im"`
in the cargo build command for clang compilers.

## Issues Building Rust Crates that Bind to C

Not all C code is guaranteed to build or run on the RISC Zero zkVM out of the
box. Be sure to consult the crate's features and configure them in a way that's
suitable for the zkVM. As an example, the BLST crate defines a `no_threads`
feature. The RISC Zero zkVM executes on a single thread, so using this feature
of the BLST crate allows it to build and run successfully. Troubleshooting these
crates requires an understanding of the characteristics of [the RISC Zero
zkVM][zkvm_spec]. If there is a crate that does not work, [file an issue here][risc0-gh-issues].

## Notes on versioning

At this time, there is only one version of the C++ toolchain and it is intended
to work with any guest rust toolchain. We will provide more information on
versioning and compatibility in the future.

[BLST]: https://github.com/supranational/blst
[install]: ./install.md#install
[risc0-gh-issues]: https://github.com/risc0/risc0/issues/
[zkvm_spec]: ./zkvm-specification.md#the-zkvm-execution-model
