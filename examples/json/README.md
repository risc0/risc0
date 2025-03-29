# JSON Example

This code demonstrates how to prove that a JSON file contains a specific field and value using the RISC Zero zkVM. The JSON file is identified by SHA-256 hash, allowing users to commit to a specific JSON file and then prove some of its contents without revealing the full file.

## Performance

JSON parsing and validation in the zkVM can be resource-intensive. For development and testing purposes, we recommend running this example on [Bonsai] or using the [`DEV_MODE`][DEV_MODE] for faster execution.

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

## Video Tutorial

For a walk-through of this example, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=6vIgBHx61vc\&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5\&index=7).

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[Bonsai]: https://dev.bonsai.xyz/apply
[DEV_MODE]: https://dev.risczero.com/api/generating-proofs/dev-mode
