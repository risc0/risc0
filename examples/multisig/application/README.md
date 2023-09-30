# Private MultiSig Wallet and zkVM Merkle Proofs

This code demonstrates the creation of a private multisig wallet and the generation of zkVM Merkle proofs for its participants. The wallet is used for educational purposes only, and the provided Ethereum addresses and private keys should not be used for real assets.

## Prerequisites

Before running this code, make sure you have the following Node.js libraries installed:

Run `npm install`.

- `secp256k1`: Provides cryptographic functions for working with Ethereum's secp256k1 curve.
- `keccak256`: Computes the Keccak256 hash.
- `merkletreejs`: Implements a Merkle tree for creating Merkle proofs.
- `crypto-js`: A JavaScript library for working with cryptography.


## Usage

1. Clone this repository and navigate to this directory.

2. Run the code with Node.js:

   ```bash
   node prove.js

3. Once executed, you'll notice some output in your terminal telling you to `Run the following command:`. This command executes the guest program with the relevant arguements to create a valid proof. The generic structure to run our Rust program is:
    ```bash
    cargo run -- <signature1><recoveryId1> <signature2><recoveryId2> <merkleProof1><leafIndex1> <merkleProof2><leafIndex2> '<signedMessage>' <merkleLeaves>