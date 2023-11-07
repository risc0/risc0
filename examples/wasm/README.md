# WASM

Example of running WASM code within the ZKVM using the [wasmi](https://crates.io/crates/wasmi) crate. In this example we define a fibonacci function in WAT format, compile it to WASM bytecode then run it within the ZKVM guest code. Returning the result of the fib() function back to the host. This sample can be extended to run arbitrary WAT/WASM modules or run a specific WASM bytecode if you compile the WASM code into the guest image.

## Quick Start

First, follow the [installation guide] if you don't already have the RISC Zero tools installed.

Then, run the example with:
```bash
cargo run --release
```

[installation guide]: https://dev.risczero.com/api/zkvm/quickstart
