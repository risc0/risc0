# JSON Example

This code demonstrates how to prove that a JSON file contains a specific field and value using the RISC Zero zkVM. The JSON file is identified by SHA-256 hash, allowing users to commit to a specific JSON file and then prove some of its contents without revealing the full file.

## Quick Start

First, [install Rust] if you don't already have it.

Next, install the `cargo-risczero` tool and install the toolchain with:
```bash
cargo install cargo-risczero
cargo risczero install
```

Then, run the example with:
```bash
cargo run --release
```

[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html

## Video Tutorial

For a walk-through of this example, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=6vIgBHx61vc&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=7).
