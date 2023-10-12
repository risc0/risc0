# Installation

These instructions tell you how to install (or update) RISC Zero tools so you can build your own RISC Zero zkVM projects. By following these instructions, you will install the [`cargo risczero`] tool for creating and building RISC Zero zkVM projects, as well as the RISC Zero toolchain used to build zkVM guest programs in Rust.

[`cargo risczero`]: https://docs.rs/cargo-risczero/0.18.0/cargo_risczero/index.html

## Prerequisites

The RISC Zero zkVM requires Rust, so start by [installing Rust and `rustup`][install-rust] if you don't already have it. Please note that you will need to follow the recommended Rust installation instructions that use [rustup] rather than any of the alternative Rust installation options, as RISC Zero depends on the [rustup] tool specifically.

[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[rustup]: https://rustup.rs/

## Install

Next, install the [`cargo risczero`] tool and use its [`install` command] to install the toolchain by running

```bash
cargo install cargo-risczero
cargo risczero install
```

If this is successful, it will finish by printing the message

```text
The risc0 toolchain is now ready to use.
```

You can verify the toolchain was installed correctly by running

```bash
rustup toolchain list --verbose | grep risc0
```

which should list `risc0` along with its path.

[`install` command]: https://docs.rs/cargo-risczero/0.18.0/cargo_risczero/index.html#install

## Update

To update your installation:

1. Run `cargo install cargo-risczero` to update the `cargo risczero` tool, and
2. Run `cargo risczero install` to update the RISC Zero toolchain.
