# Cycle Counter

The Cycle Counter is a utility to measure and report into a CSV the number of cycles elapsed during the execution of a provided series of examples.

## Quick Start

First, [install Rust] if you don't already have it.

Next, install the `cargo-risczero` tool and install the toolchain with:
```bash
cargo install cargo-binstall
cargo binstall cargo-risczero
cargo risczero install
```

Then, run the example with:
```bash
RUST_LOG=info cargo run --release -- --out count.csv all
```

[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
