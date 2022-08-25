# risc0_zkp::core

This module contains the core objects that are used by the zk-STARK prover and verifier.

This includes support for:
* [fp]: The base finite field
* [fp4]: The finite field extension
* [ntt]: Number-theoretic transform (NTT)
* [sha]: SHA-256 hashing support
* [sha_rng]: Cryptographic random number generator (CRNG) based on SHA-256
* Other basic ZKP utilities
