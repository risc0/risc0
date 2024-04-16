# Contributing to risc0

Thank you for your interest in contributing to RISC Zero! We welcome contributions from everyone.

If you have any questions about contributing, or about the project in general, please ask in our [Discord channel](https://discord.gg/risczero).

## Quick Start

To run the test suite, the following dependencies are needed:

#### [Git Large File Storage](https://docs.github.com/en/repositories/working-with-files/managing-large-files/installing-git-large-file-storage)

Once installed, run:

```console
git lfs install
git lfs pull
```

#### [Rust](https://www.rust-lang.org/tools/install)

```console
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

#### [RISC Zero toolchain](https://dev.risczero.com/api/zkvm/quickstart#1-install-the-risc-zero-toolchain)

The RISC Zero toolchain must match the version of crates you are compiling.

When testing and running examples within this library, you can install `cargo-risczero` from source:

```console
cargo install --force --path risc0/cargo-risczero
cargo risczero install
```

Otherwise, if using a stable version branch, you can install `cargo-risczero` through the standard flow:

```console
cargo install cargo-binstall
cargo binstall cargo-risczero
cargo risczero install
```

Optionally, you can specify which version of `cargo-risczero` to install with:

```console
cargo binstall cargo-risczero@<version>
```

> NOTE: It is only important that you install `cargo-risczero` with a matching version of the `zkvm` crate when interacting with the proof system as a separate, pre-built process ([`ExternalProver`](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ExternalProver.html)), which is currently the default. If you are using the `prove` feature on the `risc0-zkvm` crate for the host, this will compile the proving system into the host binary.

#### [Foundry](https://book.getfoundry.sh/getting-started/installation)

```console
curl -L https://foundry.paradigm.xyz | bash
foundryup
```

#### xtask wasm tools (if testing [browser-verify](./examples/browser-verify))

```console
cargo xtask install
cargo xtask gen-receipt
```

## PR Checklist

Before submitting a PR, ensure the following:

1. Fork the `risc0` repository and create a new branch there to do your work.
2. Format with `cargo fmt --all`.
3. Lint with `cargo clippy --all-targets`.
4. Tests pass with `cargo test -F default -F prove --workspace`
5. Open a PR against the `main` branch.
