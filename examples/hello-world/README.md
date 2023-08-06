# Hello World for the RISC Zero zkVM

Welcome! This demo is designed to help you get started building applications for the [RISC Zero] [zkVM]. For a step-by-step guide to building your first zkVM application, we recommend [this tutorial].

## About
The RISC Zero [zkVM] is making it easier than ever before to produce zero-knowledge proofs, for all sorts of applications.
Whether you're building for blockchains or not, RISC Zero offers the most flexible and mature ecosystem for zero-knowledge software development.

This `hello-world` demo is a minimal RISC Zero zkVM [application].

By running the demo, Alice can demonstrate that she knows two nontrivial factors(i.e. both greater than 1) of a number, without revealing what those factors are.
Thus, Alice proves that a number is composite — and that she knows the factors — without revealing any further information about the number.

[zkVM]: https://dev.risczero.com/zkvm
[application]: https://dev.risczero.com/zkvm/developer-guide/zkvm-app-structure

## Quick Start
To see this example in action, [install Rust] and use `cargo run` in this directory to run it:
```sh
cargo run --release
```

Congratulations! You just constructed a zero-knowledge proof that you know the factors of 391.

[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html

## Tutorial: Building your first zkVM Application
For a step-by-step guide to building first zkVM application, we recommend [this tutorial]. For more materials, check out the [developer docs].

[RISC Zero]: https://risczero.com
[this tutorial]: https://github.com/risc0/risc0/tree/main/examples/hello-world/tutorial.md
[developer docs]: https://dev.risczero.com/zkvm





