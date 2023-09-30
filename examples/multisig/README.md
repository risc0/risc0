# Zk Multisig Example

In this zkVM system, a requirement is in place that mandates the involvement of two distinct participants from a larger quorum of 'X' in order to authorize a transaction. The zkProof generated in this process serves as a future authorization mechanism for transactions or other actions. Importantly, all participants in the multisig arrangement maintain their privacy throughout, facilitated by Merkle proofs.

This is used for educational purposes only, and the provided Ethereum addresses and private keys should not be used for real assets.

## Quick Start

First, [install Rust] if you don't already have it.

Next, install the `cargo-risczero` tool and install the toolchain with:
```bash
cargo install cargo-risczero
cargo risczero install
```

This example comes in two parts. The first part is a helper Javascript program that you can use to create your own multisig setup (see: `multisig/application/prove.js`).
Right now, the guess program is constrainted to a 2 of X setup. However, this could be altered if desirable. 

The second part is the guest code that's using the risc0 zkVM.

## Usage

- Run recommended command after executing `prove.js`. 

OR

- Simply run `cargo test`.