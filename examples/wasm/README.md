# WASM

Example of running WASM code within the ZKVM using the [wasmi](https://crates.io/crates/wasmi) crate. In this example we define a fibonacci function in WAT format, compile it to WASM bytecode then run it within the ZKVM guest code. Returning the result of the fib() function back to the host. This sample can be extended to run arbitrary WAT/WASM modules or run a specific WASM bytecode if you compile the WASM code into the guest image.

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
cargo run --release
```

[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
