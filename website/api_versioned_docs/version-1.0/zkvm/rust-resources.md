# Rust Resources

[zkVM applications][zkvm-overview] are written in [Rust]. This page contains
some resources to help you start writing Rust code for the zkVM.

## Getting Started

We recommend the official materials from [Rust]:

- [Rust Installation][install-rust]
- [Rust Book][rust-book]

## RISC Zero's Rust Crates

For writing a basic [zkVM application][zkvm-overview], all the functionality
you'll need is contained in the [`risc0-zkvm` crate][risc0-zkvm]. For more
complex applications, you may also want to check out our [other Rust
crates][rust-libraries].

## Using Rust Crates inside the zkVM

A major advantage of the [RISC Zero zkVM][zkvm-overview] is that you can use
Rust crates inside your [zkVM applications][zkvm-overview]. Being able to easily
import crates means that you can quickly build complex applications.

Each night, we test the top 1000 Rust crates for compatibility with the zkVM. As
of this writing, 71% of those tests are passing. You can see the latest results
in our [Crate Validation Report][crate-validation].

![From Guest Code to Receipt][from-rust-to-receipt]

[crate-validation]: https://benchmarks.risczero.com/crates-validation
[from-rust-to-receipt]: /diagrams/from-rust-to-receipt.png
[install-rust]: https://www.rust-lang.org/tools/install
[risc0-zkvm]: https://docs.rs/risc0-zkvm
[Rust]: https://www.rust-lang.org/
[rust-book]: https://doc.rust-lang.org/book
[rust-libraries]: https://github.com/risc0/risc0#rust-libraries
[zkvm-overview]: ./zkvm_overview.md
