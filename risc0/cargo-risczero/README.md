# cargo-risczero

Cargo extension to help create, manage, and test [RISC Zero][risc-zero] projects. The default template generated from the `cargo risczero new` command supports both local and remote proving. Refer to the README in [the rust-starter template][rust-starter] for more information.

## Installation

To install this Cargo subcommand, first you'll want to [install Rust][install-rust] and then you'll execute:

```bash
cargo install cargo-risczero
```

After that you can verify it works via:
```bash
cargo risczero --version
```

## install

The `install` command installs the latest RISC Zero toolchain. This toolchain is needed to compile guest programs into ELF binaries that the zkVM can execute.

```bash
cargo risczero install
```

You can verify it was installed correctly by running:

```bash
rustup toolchain list --verbose | grep risc0
```

Note that the following pre-built host targets are available:

* `aarch64-apple-darwin`
* `x86_64-apple-darwin`
* `x86_64-unknown-linux-gnu`

If you'd like to install the toolchain on a host not listed above, you can use the `build-toolchain` command to build the toolchain locally.

## new

The `new` command will create a new project from an existing template. It defaults to the [rust-starter template] but can be used with other templates locally or hosted on github.

### Examples

```bash
# Create a project from the main template
cargo risczero new my_project

# Create a project with 'std' support in the guest
cargo risczero new my_project --std

# Disable git initialization
cargo risczero new my_project --no-git

# Create from github template
cargo risczero new my_project --template https://github.com/risc0/risc0-rust-starter
```

## build-toolchain

Use the `build-toolchain` command to build the toolchain locally for your host. Warning: this may take a long time. The resulting toolchain will be automatically installed via `rustup toolchain link`.

[risc-zero]: https://risczero.com
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[rust-starter]: https://github.com/risc0/risc0/tree/main/templates/rust-starter
