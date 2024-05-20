# Rust Resources

[zkVM applications] are written in [Rust].
This page contains some resources to help you start writing Rust code for the zkVM.

## Getting Started

We recommend the official materials from [Rust]:

- [Rust Installation]
- [Rust Book]

## RISC Zero's Rust Crates

For writing a basic [zkVM application], all the functionality you'll need is contained in the [`risc0-zkvm` crate].
For more complex applications, you may also want to check out our [other Rust crates].

## Using Rust Crates inside the zkVM

A major advantage of the [RISC Zero zkVM] is that you can use Rust crates inside your [zkVM applications].
Being able to easily import crates means that you can quickly build complex applications.

Each night, we test the top 1000 Rust crates for compatibility with the zkVM.
As of this writing, 71% of those tests are passing.
You can see the latest results in our [Crate Validation Report].

![From Guest Code to Receipt](/diagrams/from-rust-to-receipt.png)

[RISC Zero zkVM]: ../
[zkVM application]: ../
[zkVM applications]: ../
[Rust]: https://www.rust-lang.org/
[Rust Installation]: https://www.rust-lang.org/tools/install
[Rust Book]: https://doc.rust-lang.org/book/
[Cargo Installation]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[Cargo Book]: https://doc.rust-lang.org/cargo/
[Cargo]: https://doc.rust-lang.org/cargo/
[`risc0-zkvm` crate]: https://docs.rs/risc0-zkvm
[Crate Validation Report]: https://reports.risczero.com/crates-validation
[other Rust crates]: https://github.com/risc0/risc0#rust-libraries
