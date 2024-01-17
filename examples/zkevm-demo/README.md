# Mini zkEVM on RISC Zero

***Check out our [blogpost](https://www.risczero.com/news/continuations) on this example!***

A demo of how to run an EVM engine within the Risc Zero zkVM. It uses the [revm](https://crates.io/crates/revm) crate as an EVM interpreter and does a pre-flight pass to capture all the relevant data from an Ethereum JSON-RPC interface.

Currently, this demo accepts an Ethereum transaction hash and replays the transaction at the block it happened. It could be extended to run new transactions as well. The zkVM commits the revm state changes to the journal. A verifier of this tool's outputs could, in theory, check the proof and then just commit the state changes to the global state.

## Limitations

* It currently defaults to the revm default forkid which is BERLIN. Older transactions might vary in results.
* This demo only runs pre-existing transactions by tx_hash.

## Dependencies

Follow the [examples guide] to install dependencies and check out the correct version of the example.

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples

## Building

```bash
cargo build --release

# or with CUDA acceleration for the prover
cargo build --release -F cuda
```

## Running

```bash
RUST_LOG=info cargo run --release -- -t 0x671a3b40ecb7d51b209e68392df2d38c098aae03febd3a88be0f1fa77725bbd7 -r <RPC_URL_HERE>

# With GPU:
RUST_LOG=info cargo run --release -F cuda -- -t 0x671a3b40ecb7d51b209e68392df2d38c098aae03febd3a88be0f1fa77725bbd7 -r <RPC_URL_HERE>
```

## Testing

The RPC URL used by tests is: https://rpc.flashbots.net/.

```bash
cargo test
```
