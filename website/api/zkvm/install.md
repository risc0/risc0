# Installation

These instructions tell you how to install (or update) RISC Zero tools so you
can build your own RISC Zero zkVM projects. By following these instructions, you
will install the [`cargo risczero`][cargo-risczero] tool for creating and
building RISC Zero zkVM projects, as well as the RISC Zero toolchain used to
build zkVM guest programs in Rust.

## Prerequisites

The RISC Zero zkVM requires Rust, so start by [installing Rust and
`rustup`][install-rust] if you don't already have it. Please note that you will
need to follow the recommended Rust installation instructions that use [rustup]
rather than any of the alternative Rust installation options, as RISC Zero
depends on the [rustup] tool specifically.

## Install

Next, install the [`cargo risczero`][cargo-risczero] tool and use its [`install`
command][cargo-risczero] to install the toolchain by running:

```bash
cargo install cargo-binstall
cargo binstall cargo-risczero
cargo risczero install
```

> Note: To install a specific version instead of using the latest stable version, use `cargo binstall cargo-risczero@<version>`, where the version is the crates.io release tag.
>
> The version used must match the `risc0-zkvm` version from your guest and host.

For x86-64 macOS, you must run `cargo risczero build-toolchain` instead of
`cargo risczero install`.

If this is successful, it will finish by printing the message

```text
The risc0 toolchain is now ready to use.
```

You can verify the toolchain was installed correctly by running

```bash
rustup toolchain list --verbose | grep risc0
```

which should list `risc0` along with its path.

## Update

To update your installation:

1. Run `cargo binstall cargo-risczero` to update the `cargo risczero` tool, and
2. Run `cargo risczero install` to update the RISC Zero toolchain. For x86-64
   macOS, run `cargo risczero build-toolchain`.

After you update your installation, be sure to update your project's risc0
crates. To do this, you must update all risc0 dependencies in your project's
host and guest `Cargo.toml` files. In most projects, this is done by updating
the host and guest `risc0-zkvm` crate and the `risc0-build` build dependency.
They should be updated to use the version number displayed by `cargo risczero --version`.

[cargo-risczero]: https://crates.io/crates/cargo-risczero
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[rustup]: https://rustup.rs/
