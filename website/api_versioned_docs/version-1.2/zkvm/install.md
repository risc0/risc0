# Installation

These instructions guide you through installing or updating RISC Zero tools to build your own RISC Zero zkVM projects. You will install the [`cargo-risczero`][cargo-risczero] tool for creating and building RISC Zero zkVM projects, as well as the RISC Zero toolchain used to build zkVM guest programs in Rust.

## Prerequisites

The RISC Zero zkVM requires [Rust]. If you don't already have Rust and [rustup] installed, start by [installing Rust and rustup][install-rust]. Please follow the recommended Rust installation instructions using [rustup], as RISC Zero specifically depends on the [rustup] tool.

## Installation for x86-64 Linux and arm64 macOS

`rzup` is the RISC Zero toolchain installer. We recommend using `rzup` to manage the installation of RISC Zero.

1. Install `rzup` by running the following command:
   ```sh
   curl -L https://risczero.com/install | bash
   ```
2. Run `rzup` to install RISC Zero:
   ```sh
   rzup install
   ```

Running `rzup` will install the latest version of the RISC Zero toolchain.

For a specific version, use `rzup install cargo-risczero <version>`, where the `<version>` is a [release tag] (e.g `v1.1.1`).

See `rzup --help` for more options. You can find out more about `rzup` [here][rzup-repo].

### Manual Installation and installation for all other systems (e.g. x86-64 macOS, arm64 Linux)

For users who prefer manual installation or those who use systems such as x86-64 macOS, arm64 Linux, follow these steps:

- Clone the repository with `git clone https://github.com/risc0/risc0.git`.
- In the root of the repository, install `rzup` with `cargo install --path rzup`.
- Build and install the rust toolchain with `rzup build rust`. This command may require utilities such as `cmake` and the `ninja` build system to be installed.
- Build and install the `cargo-risczero` by first checking out the branch `release-*` where `*` is `[major release number].[minor release number]` of your desired zkVM version. For example, if you would like to install version 1.1.0, run `git checkout origin/release-1.1` and run `cargo install --path risc0/cargo-risczero`.

For x86-64 linux and arm64 macOS, install the C++ toolchains by running:

```sh
rzup install cpp
```

## Update

To update your installation:

1. Run `rzup update` to update the RISC Zero toolchain to the latest [release tag] version.

After you update your installation, be sure to update your project's RISC Zero crates. To do this, you must update all RISC Zero dependencies in your project's host and guest `Cargo.toml` files. In most projects, this is done by updating the host and guest `risc0-zkvm` crate and the `risc0-build` build dependency. They should be updated to use the version number displayed by `cargo risczero --version`.

[cargo-risczero]: https://crates.io/crates/cargo-risczero
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[release tag]: https://github.com/risc0/risc0/releases
[Rust]: https://www.rust-lang.org
[rustup]: https://rustup.rs
[rzup-repo]: https://github.com/risc0/risc0/tree/release-1.2/rzup
