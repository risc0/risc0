# Zk Multisig Example

This code demonstrates the creation of a private multisig wallet and the generation of zkVM Merkle proofs for its participants.
The zkVM enforces that 2 unique participants of a 2 of X quorum must have signed the transaction data. The zkProof can be later used as a means to authorize a transaction or some other action. 

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