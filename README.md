<img src="docs/assets/images/Risc0-Logo_Horizontal.svg" height="100">

> WARNING: This software is still experimental, we do not recommend it for
> production use (see Security section).

# RISC Zero

RISC Zero is a zero-knowledge verifiable general computing platform based on
zk-STARKs and the RISC-V microarchitecture.

A zero knowledge proof allows one party (the prover) to convince another party
(the verifier), the something is true without revealing all the details.  In
the case of RISC Zero, the prover can show they correctly executed some code
(known to both parties), while only revealing to the verifier the output of the
code, not any of its inputs or any state during execution.

The code runs in a special virtual machine, called the *ZKVM*.  The RISC Zero
ZKVM emulates a small RISC-V computer, allowing it to run arbitrary code in any
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
execution, the guest code can write to a special append only log called the
*journal* that represents the official output of the computation.

Presuming the method terminated correctly, a *receipt* is produced, which
provides the proof of correct execution. This receipt consists of 3 parts: the
method ID of the method run, the journal written during execution, and a blob
of opaque cryptographic data called the *seal*.

The verifier can then verify the receipt and examine the log.  If any
tampering was done to the method ID, the journal, or the seal, the receipt will
fail to verify.  Additionally, it is cryptographically infeasible to generate a
valid receipt unless the output of the journal is the exactly correct output
for some valid execution of the method whose method ID is in the receipt.
In summary, the receipt acts as a zero knowledge proof of correct execution.

Additionally, since the protocol is zero knowledge, the verifier cannot infer
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

## Examples

In addition to the RISC Zero proof system, we include a number of small
examples, each with their own README, in the 'examples' directory.

## Building RISC Zero

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

