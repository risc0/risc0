# Installation

These instructions guide you through installing or updating RISC Zero tools to build your own RISC Zero zkVM projects. You will install the [`cargo-risczero`][cargo-risczero] tool for creating and building RISC Zero zkVM projects, as well as the RISC Zero toolchain used to build zkVM guest programs in Rust.

## Prerequisites

The RISC Zero zkVM requires [Rust]. If you don't already have Rust and [rustup] installed, start by [installing Rust and rustup][install-rust]. Please follow the recommended Rust installation instructions using [rustup], as RISC Zero specifically depends on the [rustup] tool.

## Install

`rzup` is the RISC Zero toolchain installer. We recommend using `rzup` to manage the installation of RISC Zero.

1. Install `rzup` by running the following command:

   ```sh
   curl -L https://risczero.com/install | bash
   ```

2. Run `rzup` to install RISC Zero:

   ```sh
   rzup
   ```

Running `rzup` will install the latest version of the RISC Zero toolchain.

For a specific version, use `rzup --version <version>`, where the `<version>` is a [release tag].

See `rzup --help` for more options. You can find out more about `rzup` [here](https://github.com/risc0/risc0/tree/main/rzup).

### Manual Installation

For users who prefer manual installation, follow these steps:

1. Install the [`cargo risczero`][cargo-risczero] tool and use its [`install` command][cargo-risczero] to install the Rust and C++ toolchains by running:

   ```sh
   cargo install cargo-binstall
   cargo binstall cargo-risczero
   cargo risczero install
   ```

   > Note: To install a specific version instead of using the latest stable version, use `cargo binstall cargo-risczero@<version>`, where the version is a [release tag].
   >
   > The version used must match the `risc0-zkvm` version from your guest and host.

2. For x86-64 macOS, you must run `cargo risczero build-toolchain` instead of `cargo risczero install`.

## Update

To update your installation:

1. Run `rzup` to update the RISC Zero toolchain to the latest [release tag] version.

After you update your installation, be sure to update your project's RISC Zero crates. To do this, you must update all RISC Zero dependencies in your project's host and guest `Cargo.toml` files. In most projects, this is done by updating the host and guest `risc0-zkvm` crate and the `risc0-build` build dependency. They should be updated to use the version number displayed by `cargo risczero --version`.

[Rust]: https://www.rust-lang.org/
[cargo-risczero]: https://crates.io/crates/cargo-risczero
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[rustup]: https://rustup.rs/
[release tag]: https://github.com/risc0/risc0/releases
