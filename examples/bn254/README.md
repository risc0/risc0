# BN254 Example

This example demonstrates the core pairing functionality that could be used to make cryptographic operations like signature schemes; it is a toy example and should not be used directly except as an example.

The specific operation demonstrated is that, given base points g1 ∈ G1 and g2 ∈ G2 as well as random scalars a and b, the result of the batch pairing operation
```
pair(a × g1, b × g2) * pair(g1, -ab × g2)
```
is the identity.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with
```bash
cargo run --release
```
or run tests with
```bash
cargo test
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples