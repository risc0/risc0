# WASM

Example of running WASM code within the ZKVM using the [wasmi](https://crates.io/crates/wasmi) crate. In this example we define a fibonacci function in WAT format, compile it to WASM bytecode then run it within the ZKVM guest code. Returning the result of the fib() function back to the host. This sample can be extended to run arbitrary WAT/WASM modules or run a specific WASM bytecode if you compile the WASM code into the guest image.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
