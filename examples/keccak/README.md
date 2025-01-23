# Keccak Example

This code demonstrates how to provably compute the keccak-256 hash of a string using RISC Zero.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

Notable details:

- Using a patched version of the [tiny-keccak] crate. Including this patch will accelerate _all_ usages of keccak that use the `tiny-keccak` crate in any transitive dependency.
- This will use the RISC Zero keccak precompile in the zkVM guest, which has _much_ higher performance than any software implementation.
- We could have passed the guest a `String` rather than a string literal for the same result.

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[tiny-keccak]: https://docs.rs/crate/tiny-keccak/latest
