# Factors

The _factors_ example is a minimalistic RISC Zero zkVM proof. The prover demonstrates that they know two nontrivial factors (i.e. both greater than 1) of a number, without revealing what those factors are. Thus, the prover demonstrates that a number is composite -- and that they know the factors -- without revealing any further information about the number.

This example was chosen because it is very straightforward. Implementing the verified multiplication and reporting the result in the receipt involves no complexity beyond what is necessary to run the zkVM at all. We therefore hope this example is a good place to look to see all the steps necessary to use the RISC Zero zkVM without any superfluous problem-specific details.

Choosing a simple example necessarily excludes all of the more complex use cases -- so if you are looking for anything beyond the basics, we recommend looking at other examples in this repository!

## Run this example

First, make sure [rustup](https://rustup.rs) is installed. This project uses a [nightly](https://doc.rust-lang.org/book/appendix-07-nightly-rust.html) version of [Rust](https://doc.rust-lang.org/book/ch01-01-installation.html). The [`rust-toolchain`](rust-toolchain) file will be used by `cargo` to automatically install the correct version.

To build all methods and execute the method within the zkVM, run the following command:

```
cargo run
```

## Video Tutorial

For a walk-through of this example, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=nWxL21hKV9s&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=3).
Note that this presentation was based on v0.11 of RISC Zero, and some API changes have been made since then.
