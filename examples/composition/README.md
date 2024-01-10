# Composition Example

This example demonstrates a basic usage of the proof composition feature.
It builds upon the [hello world example](../hello-world), where the [guest program] verified that the prover knows a factorization of a composite number.

See the [`src/main.rs`] file for the [host] side implementation of composition, and [`methods/guest/src/main.rs`] for the guest side.

## Quick Start

First, follow the [installation guide] if you don't already have the RISC Zero tools installed.

Then, run the example with:

```bash
cargo run --release
```

[installation guide]: https://dev.risczero.com/api/zkvm/quickstart

## Use Cases

Composition is a feature of the zkVM supporting verification of RISC Zero [receipts] in a guest program.
With this, multiple zkVM programs can be _composed_ and produce a single receipt that verifies all computation done to reach the final result.

Composition is supported through the [`env::verify`] method in the [guest program].
The result of an earlier proof can be used as input to this method, allowing the verified results of another guest to be used in a new computation.

### Examples

Some use cases for composition include:

* Splitting a program into multiple parts, proven by different parties, to preserve privacy and data ownership of each party.
  * E.g. Produce a proof for a database query by joining receipts from the query over each privately held shard.
* Aggregating many proofs into one for efficeint batch verification.
  * E.g. Produce a proof for a block of transactions, where each trasaction is itself verified by a proof.
* Creating a single receipt for a workflow that might be split into many different operations.
  * E.g. Produce a single receipt for the result of an image processing pipeline, where different filters are in their own guests.

[`env::verify`]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.verify.html

[`src/main.rs`]: /src/main.rs
[`methods/guest/src/main.rs`]: methods/guest/src/main.rs
[host]: https://dev.risczero.com/terminology#host
[guest program]: https://dev.risczero.com/terminology#guest-program
[receipts]: https://dev.risczero.com/terminology#receipt
