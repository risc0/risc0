# Cycle Counter

The Cycle Counter is a utility to measure and report into a CSV the number of cycles elapsed during the execution of a provided series of examples.

## Quick Start

First, follow the [installation guide] if you don't already have the RISC Zero tools installed.

Then, run the example with:
```bash
RUST_LOG=info cargo run --release -- --out count.csv all
```

[installation guide]: https://dev.risczero.com/api/zkvm/quickstart
