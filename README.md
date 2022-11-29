<p align="center">
  <a href="https://risc0.com/#gh-dark-mode-only"><img src="docs/assets/images/Risc0-Logo_Horizontal.svg" height="100"></a>
  <a href="https://risc0.com/#gh-light-mode-only"><img src="docs/assets/images/Risc0-Logo_Horizontal_Inverted.svg" height="100"></a>
</p>

<h1 align="center">RISC Zero</h1>

<p align="center">
  <a href="https://github.com/risc0/risc0/blob/main/LICENSE"><img src="https://img.shields.io/badge/license-Apache 2-blue.svg"></a>
  <a href="https://github.com/risc0/risc0/actions"><img src="https://github.com/risc0/risc0/workflows/CI/badge.svg?branch=main"></a>
</p>

> WARNING: This software is still experimental, we do not recommend it for
> production use (see Security section).

RISC Zero is a zero-knowledge verifiable general computing platform based on
zk-STARKs and the RISC-V microarchitecture.

A [zero knowledge proof](https://en.wikipedia.org/wiki/Non-interactive_zero-knowledge_proof) allows one party (the prover) to convince another party
(the verifier) that something is true without revealing all the details.  In
the case of RISC Zero, the prover can show they correctly executed some code
(known to both parties), while only revealing to the verifier the output of the
code, not any of its inputs or any state during execution.

The code runs in a special virtual machine, called a *ZKVM*.  The RISC Zero
ZKVM emulates a small [RISC-V](https://en.wikipedia.org/wiki/RISC-V) computer, allowing it to run arbitrary code in any
language, so long as a compiler toolchain exists that targets RISC-V.
Currently, SDK support exists for Rust, C, and C++.

## Protocol overview and terminology

First, the code to be proven must be compiled from its implementation language
into a *method*.  A method is represented by a RISC-V ELF file with a special
entry point that runs the code of the method.  Additionally, one can compute
for a given method its *method ID* which is a special type of
cryptographic hash of the ELF file, and is required for verification.

Next, the prover runs the method inside the ZKVM.  The logical RISC-V machine
running inside the ZKVM is called the *guest* and the prover running the ZKVM
is called the *host*.  The guest and the host can communicate with each other
during the execution of the method, but the host cannot modify the execution of
the guest in any way, or the proof being generated will be invalid. During
execution, the guest code can write to a special append-only log called the
*journal* that represents the official output of the computation.

Presuming the method terminated correctly, a *receipt* is produced, which
provides the proof of correct execution. This receipt consists of 2 parts:
the journal written during execution and a blob of opaque cryptographic
data called the *seal*.

The verifier can then verify the receipt and examine the log. If any
tampering was done to the journal or the seal, the receipt will
fail to verify.  Additionally, it is cryptographically infeasible to generate a
valid receipt unless the output of the journal is the exactly correct output
for some valid execution of the method whose method ID matches the receipt.
In summary, the receipt acts as a zero knowledge proof of correct execution.

Because the protocol is zero knowledge, the verifier cannot infer
anything about the details of the execution or any data passed between the host
and the guest (aside from what is implied by the data written to the journal
and the correct execution of the code).

## Security

This code is based on the well studied zk-STARK protocol, which has been proven
secure under the random oracle model, with the only assumption being the
security of the cryptographic hash used.  Our implementation uses SHA-256 for
that hash and targets a security factor of 100 bits of security.

That said, this code is still under heavy development and has not been
audited.  There may be bugs in the zk-STARK implementation, the arithmetic
circuit used to instantiate the RISC-V ZKVM, or any other element of the code's
implementation.  Such bugs may impact the security of receipts, leak
information, or cause any other manner of problems.  Caveat emptor.

## Getting Started

To get started building applications using the zkVM in Rust, we provide
a small 'Hello World' repo here:

[risc0-rust-starter](https://github.com/risc0/risc0-rust-starter)

Additionally, we have a more complex battleship example here:

[battleship-example](https://github.com/risc0/battleship-example)

Finally we include a number of small examples, each with their own README, in
the 'examples' directory, most of which will eventually be moved out-of-tree.

## Rust Crates

| name                    | crates.io                                                                                                         | docs.rs                                                                                               |
| ----------------------- | ----------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------- |
| risc0-build             | [![x](https://img.shields.io/crates/v/risc0-build)](https://crates.io/crates/risc0-build)                         | [![](https://img.shields.io/docsrs/risc0-build)](https://docs.rs/risc0-build)                         |
| risc0-core-sys          | [![x](https://img.shields.io/crates/v/risc0-core-sys)](https://crates.io/crates/risc0-core-sys)                   | [![](https://img.shields.io/docsrs/risc0-core-sys)](https://docs.rs/risc0-core-sys)                   |
| risc0-r0vm              | [![x](https://img.shields.io/crates/v/risc0-r0vm)](https://crates.io/crates/risc0-r0vm)                           | -----N/A----
| risc0-zkp               | [![x](https://img.shields.io/crates/v/risc0-zkp)](https://crates.io/crates/risc0-zkp)                             | [![](https://img.shields.io/docsrs/risc0-zkp)](https://docs.rs/risc0-zkp)                             |
| risc0-zkp-sys           | [![x](https://img.shields.io/crates/v/risc0-zkp-sys)](https://crates.io/crates/risc0-zkp-sys)                     | [![](https://img.shields.io/docsrs/risc0-zkp-sys)](https://docs.rs/risc0-zkp-sys)                     |
| risc0-zkvm              | [![x](https://img.shields.io/crates/v/risc0-zkvm)](https://crates.io/crates/risc0-zkvm)                           | [![](https://img.shields.io/docsrs/risc0-zkvm)](https://docs.rs/risc0-zkvm)                           |
| risc0-zkvm-circuit      | [![x](https://img.shields.io/crates/v/risc0-zkvm-circuit)](https://crates.io/crates/risc0-zkvm-circuit)           | [![](https://img.shields.io/docsrs/risc0-zkvm-circuit)](https://docs.rs/risc0-zkvm-circuit)           |
| risc0-zkvm-circuit-gen  | [![x](https://img.shields.io/crates/v/risc0-zkvm-circuit-gen)](https://crates.io/crates/risc0-zkvm-circuit-gen)   | [![](https://img.shields.io/docsrs/risc0-zkvm-circuit-gen)](https://docs.rs/risc0-zkvm-circuit-gen)   |
| risc0-zkvm-circuit-sys  | [![x](https://img.shields.io/crates/v/risc0-zkvm-circuit-sys)](https://crates.io/crates/risc0-zkvm-circuit-sys)   | [![](https://img.shields.io/docsrs/risc0-zkvm-circuit-sys)](https://docs.rs/risc0-zkvm-circuit-sys)   |
| risc0-zkvm-guest        | [![x](https://img.shields.io/crates/v/risc0-zkvm-guest)](https://crates.io/crates/risc0-zkvm-guest)               | [![](https://img.shields.io/docsrs/risc0-zkvm-guest)](https://docs.rs/risc0-zkvm-guest)               |
| risc0-zkvm-platform     | [![x](https://img.shields.io/crates/v/risc0-zkvm-platform)](https://crates.io/crates/risc0-zkvm-platform)         | [![](https://img.shields.io/docsrs/risc0-zkvm-platform)](https://docs.rs/risc0-zkvm-platform)         |
| risc0-zkvm-platform-sys | [![x](https://img.shields.io/crates/v/risc0-zkvm-platform-sys)](https://crates.io/crates/risc0-zkvm-platform-sys) | [![](https://img.shields.io/docsrs/risc0-zkvm-platform-sys)](https://docs.rs/risc0-zkvm-platform-sys) |
| risc0-zkvm-sys          | [![x](https://img.shields.io/crates/v/risc0-zkvm-sys)](https://crates.io/crates/risc0-zkvm-sys)                   | [![](https://img.shields.io/docsrs/risc0-zkvm-sys)](https://docs.rs/risc0-zkvm-sys)                   |

## Building RISC Zero

Generally only potential contributors or people looking to use the RISC Zero's
experimental support for C++ based guest code should need to clone and build
this repo.  We suggest Rust users stick to released crates.

We use [Bazel](https://bazel.build) for its strong multi-language multi-platform
features and performance.

We recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk) to make
bazel version management seamless.

In order to build RISC Zero executables you'll need a RISC-V toolchain.
Bazel will automatically fetch and manage the toolchain for the following platforms:

* Linux - Ubuntu 18+ (x86_64)
* macOS (x86_64)
* macOS (arm64)
* Windows (x86_64)

Other platforms will be supported in the future.

You should be able to build and run all tests with:

```
bazelisk test //...
```

### Linux

A C++ compiler must be installed; both gcc and clang should work.
Let us know if you run into any issues.

### macOS

RISC Zero development on macOS **requires a full installation of Xcode (not just command line tools)**.

### Windows

Our usage of Bazel requires [symlink support to be enabled](https://bazel.build/docs/windows#symlink).
This is possible on Windows by enabling [Developer Mode](https://docs.microsoft.com/en-us/windows/apps/get-started/enable-your-device-for-development),
or by running Bazel as an administrator.

A C++ compiler must be installed. Visual Studio 2019 Build Tools is known to work (as does the Community edition).
Let us know if you run into any issues.
