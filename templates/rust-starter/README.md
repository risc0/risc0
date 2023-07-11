# RISC Zero Rust Starter Template

Welcome to the RISC Zero Rust Starter Template! This template is intended to give you a starting point for building a project using the RISC Zero zkVM. Throughout the code are comments labelled `TODO` in places where we expect projects will need to modify the code.
To better understand the concepts behind this template, check out our [Understanding the Starter Template] explainer.

TODO: Replace this README with a README for your project
TODO: Verify whether the included `.gitignore`, `LICENSE`, and `rust-toolchain` files are appropriate to your project

## Quick Start

First, make sure [rustup](https://rustup.rs) is installed. This project uses a [nightly](https://doc.rust-lang.org/book/appendix-07-nightly-rust.html) version of [Rust](https://doc.rust-lang.org/book/ch01-01-installation.html). The [`rust-toolchain`](rust-toolchain) file will be used by `cargo` to automatically install the correct version.

To build all methods and execute the method within the zkVM, run the following command:

```
cargo run
```

This is an empty template, and so there is no expected output (until you modify the code).

### Running proofs remotely on Bonsai

*Note: The Bonsai proving service is still in early Alpha; an API key is required for access. [Click here to request access].*

If you have access to the URL and API key to Bonsai you can run your proofs
remotely. To prove in Bonsai mode, invoke `cargo run` with two additional
environment variables:

```
BONSAI_API_KEY="YOUR_API_KEY" BONSAI_API_URL="BONSAI_URL" cargo run
```

[Click here to request access]: https://docs.google.com/forms/d/e/1FAIpQLSf9mu18V65862GS4PLYd7tFTEKrl90J5GTyzw_d14ASxrruFQ/viewform

## How to create a project based on this template

Search this template for the string `TODO`, and make the necessary changes to implement the required feature described by the `TODO` comment. Some of these changes will be complex, and so we have a number of instructional resources to assist you in learning how to write your own code for the RISC Zero zkVM:
 * The [Getting Started section](https://www.risczero.com/docs) of the [RISC Zero website](https://www.risczero.com) is a great place to get started. There are additional explainers and overviews on our website as well.
 * Example projects are available in the [examples folder](https://github.com/risc0/risc0/tree/main/examples) of this repository.
 * Reference documentation for our Rust crates is available at [docs.rs], including the [RISC Zero zkVM crate](https://docs.rs/risc0-zkvm), the [cargo risczero crate](https://docs.rs/cargo-risczero), the [RISC Zero build crate](https://docs.rs/risc0-build), and others (the full list is available at [https://github.com/risc0/risc0/blob/main/README.md]).
 * Our [main repository](https://www.github.com/risc0/risc0).


## Contributor's Guide
We welcome contributions to documentation and code via PRs and GitHub Issues on our [main repository](http://www.github.com/risc0) or any of our other repositories.

## Video Tutorial
For a walk-through of how to build with this template, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=Yg_BGqj_6lg&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=5).

## Questions, Feedback, and Collaborations
We'd love to hear from you on [Discord](https://discord.gg/risczero) or [Twitter](https://twitter.com/risczero).

[Understanding the Starter Template]: https://www.risczero.com/docs/examples/understanding_template
