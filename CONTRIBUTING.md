# Contributing to risc0

Thank you for your interest in contributing to RISC Zero! We welcome contributions from everyone.

If you have any questions about contributing, or about the project in general, please ask in our [Discord channel](https://discord.gg/risczero).

## Quick Start

To run the test suite, the following dependencies are needed:

#### [Git Large File Storage](https://docs.github.com/en/repositories/working-with-files/managing-large-files/installing-git-large-file-storage)

Once installed, run:

```bash
git lfs install
git lfs pull
```

#### [Rust](https://www.rust-lang.org/tools/install)

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

#### [RISC Zero toolchain](https://dev.risczero.com/api/zkvm/quickstart#1-install-the-risc-zero-toolchain)

Run `rzup install` to install the latest Rust and C++ toolchains.
```bash
cargo run --bin rzup install rust
cargo run --bin rzup install cpp
```

The versions of `r0vm` and `cargo-risczero` must match the source code. Compile and install these
from source when using a development branch. The `cargo-risczero` package includes both the `r0vm`
and `cargo-risczero` binaries.

```bash
cargo install --force --path risc0/cargo-risczero
```

Otherwise, if using a stable version branch, you can install `cargo-risczero` through the standard flow:

```bash
curl -L https://risczero.com/install | bash
rzup install
```

> NOTE: It is only important that you install `cargo-risczero` with a matching version of the `zkvm` crate when interacting with the proof system as a separate, pre-built process ([`DefaultProver`](https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.DefaultProver.html)), which is currently the default. If you are using the `prove` feature on the `risc0-zkvm` crate for the host, this will compile the proving system into the host binary.

#### xtask wasm tools (if testing [browser-verify](./examples/browser-verify))

```bash
cargo xtask install
cargo xtask gen-receipt
```

## PR Checklist

Before submitting a PR, ensure the following:

1. Fork the `risc0` repository and create a new branch there to do your work.
2. Format with `cargo fmt --all`.
3. Lint with:
   ```
   RISC0_SKIP_BUILD=1 cargo clippy
   $(cd examples && RISC0_SKIP_BUILD=1 cargo clippy)
   ```
4. Perform the license check with `python3 license-check.py`.
5. Tests pass with:
   ```
   cargo test -F prove -F docker
   $(cd examples && cargo test)
   ```
6. Commit any outdated `Cargo.lock` files.
7. Open a PR against the `main` branch.
