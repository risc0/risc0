# BLS12_381 Example

## Performance

Elliptic curve operations on BLS12_381 can be computationally intensive in a zkVM. For faster development and testing, we recommend running this example on [Bonsai] or using the [`DEV_MODE`][DEV_MODE].

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

Or in [`DEV_MODE`][DEV_MODE] for much faster execution:

```bash
RISC0_DEV_MODE=1 cargo run --release
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[Bonsai]: https://dev.bonsai.xyz/apply
[DEV_MODE]: https://dev.risczero.com/api/generating-proofs/dev-mode
