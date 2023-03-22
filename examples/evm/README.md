# Mini zkEVM on Risc Zero

A Demo of how to run a EVM engine within the Risc Zero zkvm. It uses the [revm](https://crates.io/crates/revm) crate as a EVM interpreter and does a pre-flight pass to capture all the relevant data from a Ethereum JSON-RPC interface.

Currently this demo accepts a ethereum Transaction hash and replays the transaction at the block it happened. But it could be extended to run new transactions as well. The zkvm commits the revm state changes to the journal. So a verifier of this tools outputs could in theory, check the proof and then just commit the state changes to the global state.

## Limitations

* While we build in support for EC precompiles using the [k256](https://crates.io/crates/k256) crate running them within the zkvm is expensive enough to trigger our cycle count limit. So this is not compatible with all eth transactions
* It currently defaults to the revm default forkid which is BERLIN. Older transactions might vary in results
* only runs pre-existing transactions by tx_hash

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

```bash
RPC_URL=<RPC_URL_HERE> cargo test
```