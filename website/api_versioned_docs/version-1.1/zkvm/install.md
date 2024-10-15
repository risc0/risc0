# Installation

These instructions guide you through installing or updating RISC Zero tools to build your own RISC Zero zkVM projects. You will install the [`cargo-risczero`][cargo-risczero] tool for creating and building RISC Zero zkVM projects, as well as the RISC Zero toolchain used to build zkVM guest programs in Rust.

## Prerequisites

The RISC Zero zkVM requires [Rust]. If you don't already have Rust and [rustup] installed, start by [installing Rust and rustup][install-rust]. Please follow the recommended Rust installation instructions using [rustup], as RISC Zero specifically depends on the [rustup] tool.

## Using `rzup`

:::warning
Only compatible with x86-64 Linux and arm64 macOS
All other architectures must [install manually](#manual-install)
:::

`rzup` is the RISC Zero toolchain installer and version manager, inspired by [rustup].

1. Install `rzup` by running the following command:
   ```sh
   curl -L https://risczero.com/install | bash
   ```
2. Run `rzup` to install RISC Zero:
   ```sh
   rzup install
   ```

Running `rzup` will install the [latest version][release tag] of the RISC Zero toolchain.

See `rzup --help` for more options. You can find out more about `rzup` [here][rzup-repo].

### Version Management

:::info
Your project's RISC Zero crates _must match_ the installed tooling best managed by [rzup](#use-the-rzup-installer).
Be sure to match all `Cargo.toml` files with the version of the installation.

Check your presently installed version number displayed by `cargo risczero --version`.
:::

Run `rzup update` to update the RISC Zero toolchain to the [latest version][release tag].

For a specific version, use `rzup install cargo-risczero <version>`, where the `<version>` is a [release tag] (e.g `v1.1.1`).

## Manual Install

For users who prefer manual installation or those who use systems such as x86-64 macOS, arm64 Linux, follow these steps:

1. Clone the repository with `git clone https://github.com/risc0/risc0.git`.
2. In the root of the repository, install `rzup` with `cargo install --path rzup`.
3. Build and install the rust toolchain with `rzup toolchain build rust`. This command may require utilities such as `cmake` and the `ninja` build system to be installed.
4. Build and install the `cargo-risczero` by first checking out the branch `release-*` where `*` is `[major release number].[minor release number]` of your desired zkVM version. For example, if you would like to install version 1.1.0, run `git checkout origin/release-1.1` and run `cargo install --path risc0/cargo-risczero`.

[cargo-risczero]: https://crates.io/crates/cargo-risczero
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[release tag]: https://github.com/risc0/risc0/releases
[Rust]: https://www.rust-lang.org
[rustup]: https://rustup.rs
[rzup-repo]: https://github.com/risc0/risc0/tree/release-1.1/rzup
