# RISC Zero Examples

This directory includes a wide range of examples demonstrating how to build and verify zero-knowledge programs using the RISC Zero zkVM. These examples cover use cases from cryptographic primitives and signature verification to zk-powered games, machine learning, and developer tooling.

---

### [Bevy Game Engine Example](https://github.com/risc0/risc0/tree/main/examples/bevy)

Demonstrates how a [Bevy] game engine–based application can run verifiably inside the RISC Zero [zkVM].  
This example shows how game logic can be proven off-chain using zkVM, opening up use cases such as **on-chain rewards based on off-chain gameplay**. It can be combined with ECDSA signatures for associating gameplay to a player. Great for zk-gaming exploration with [Bonsai].

[Bevy]: https://bevyengine.org/
[zkVM]: https://dev.risczero.com/zkvm
[Bonsai]: https://dev.bonsai.xyz

---

### [BLS12_381 Example](https://github.com/risc0/risc0/tree/main/examples/bls12_381)

A simple demo showing how to use the BLS12-381 pairing-friendly elliptic curve within the zkVM.  
Useful for experimenting with pairing-based cryptography and verifying basic zk arithmetic without external dependencies.

---

### [BN254 Example](https://github.com/risc0/risc0/tree/main/examples/bn254)

Demonstrates how to perform pairing operations over the BN254 curve inside zkVM.  
Given base points and scalars, it validates a pairing identity — a building block in many SNARK systems. Ideal for learning about curve operations and ZK math foundations.

---

### [In-Browser Proof Verification](https://github.com/risc0/risc0/tree/main/examples/browser-verify)

Runs zkVM proof verification entirely within the browser using WebAssembly (WASM).  
You can test and verify receipts inside Chrome, Firefox, or Safari without a server. Great for building **fully client-side zk apps** or demos where trustless proof verification is needed in the frontend.

[Node.js]: https://nodejs.org/
[Rust]: https://www.rust-lang.org/tools/install

---

### [C Guest Program Example](https://github.com/risc0/risc0/tree/main/examples/c-guest)

Provides a basic template for writing zkVM guest programs in the C programming language instead of Rust. ⚠️ Experimental and not heavily tested.  
A good starting point if you want to explore **non-Rust language support** or work with legacy-style code inside zkVM.

---

### [C-KZG Crate Test](https://github.com/risc0/risc0/tree/main/examples/c-kzg)

Tests compatibility of Ethereum’s `c-kzg-4844` crate (used in EIP-4844 for blob commitments) inside zkVM.  
Due to workspace limitations, it’s placed outside core modules and executed as a standalone test. Comes with a [video walkthrough from ZK Hack III](https://www.youtube.com/watch?v=vxqxRiTXGBI&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=9) explaining internals.

---

---

### [ZK Checkmate](https://github.com/risc0/risc0/tree/main/examples/chess)

Uses the [shakmaty] crate to prove that a move results in checkmate — without revealing the move itself.  
The server commits to a board state and move; the zkVM verifies legality and result. This enables **zero-knowledge puzzles, games, or reward mechanics** where revealing the solution isn’t required. You can pair this with [Bonsai] to build verifiable chess-based applications.

[shakmaty]: https://docs.rs/shakmaty/latest/shakmaty/

---

### [Proof Composition](https://github.com/risc0/risc0/tree/main/examples/composition)

Demonstrates how to **verify one zkVM proof inside another zkVM guest**, enabling trust chaining and modular computation.  
It builds on the Hello World example and introduces receipt verification with `env::verify()`. This is useful for scenarios like **verifiable encryption, proof aggregation, or composable privacy-preserving apps**.

---

### [Simple Digital Signature](https://github.com/risc0/risc0/tree/main/examples/digital-signature)

A simple implementation of a digital signature system using a passphrase.  
Proves that the sender knows a passphrase (identity) and used it to sign a message. This shows how to build **authenticated ZK messaging** without revealing the private key. Utilizes SHA-256d and receipt commitment to guarantee integrity and origin.

[Wikipedia Digital Signature]: https://en.wikipedia.org/wiki/Digital_signature

---

### [ECDSA Signature Verification (secp256k1)](https://github.com/risc0/risc0/tree/main/examples/ecdsa/k256)

Verifies [secp256k1] signatures (used by Ethereum & Bitcoin) inside the zkVM using the patched `k256` crate.  
Optimized with big-integer precompiles, reducing cycles from 5M to 870k. Ideal for building zk apps that depend on existing blockchain signature verification, such as **zk-rollups, off-chain voting, and group membership proofs**.

[secp256k1]: https://en.bitcoin.it/wiki/Secp256k1

---

### [ECDSA Signature Verification (secp256r1)](https://github.com/risc0/risc0/tree/main/examples/ecdsa/p256)

Verifies signatures on the P-256 (secp256r1) curve, common in web-based cryptography (e.g. WebAuthn, TLS).  
Same optimizations as the k256 example apply here, with precompiles reducing cycle cost to ~220k. Great for integrating **web identity proofs into blockchain-based systems**.

---

### [Groth16 Verifier](https://github.com/risc0/risc0/tree/main/examples/groth16-verifier)

⚠️ Experimental. Verifies [Groth16] zero-knowledge proofs inside zkVM, such as Sudoku or ECDSA circuits generated in Circom/SnarkJS.  
Bridges the gap between zkSNARKs and zkVMs — enabling **zk cross-compatibility**. Uses real Sudoku proofs from [zkSudoku] or ECDSA circuits from [0xPARC].

[Groth16]: https://eprint.iacr.org/2016/260.pdf  
[zkSudoku]: https://github.com/vplasencia/zkSudoku  
[0xPARC]: https://github.com/0xPARC

---

### [Hello World](https://github.com/risc0/risc0/tree/main/examples/hello-world)

The classic "Hello World" for zkVM — proves that you know the factors of 391.  
This is the simplest working example for building and proving a zkVM application. It introduces the concepts of **guest/host architecture**, journal commitment, and receipt generation. Perfect starting point for newcomers.

[tutorial]: https://dev.risczero.com/api/zkvm/tutorials/hello-world

---

### [JSON Field Verifier](https://github.com/risc0/risc0/tree/main/examples/json)

Proves that a JSON file (identified by its SHA-256 hash) contains a specific field with a target value — without revealing the full file.  
Useful for **privacy-preserving document audits**, configuration validations, or whitelisting rules. Includes a [ZK Hack III walkthrough video](https://www.youtube.com/watch?v=6vIgBHx61vc&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=7).

---

### [JWT Validator](https://github.com/risc0/risc0/tree/main/examples/jwt-validator)

Creates a zk-proof verifying that a [JWT] is valid and was signed with a known public key using RS256.  
Ideal for **proving off-chain authentication (e.g., Sign-in-with-Google)** on-chain without exposing sensitive identity details. Built with [jwt-compact] and integrates well with [Bonsai Pay Demo].

[JWT]: https://jwt.io  
[jwt-compact]: https://github.com/slowli/jwt-compact  
[Bonsai Pay Demo]: https://github.com/risc0/demos/tree/main/bonsai-pay

---

### [Keccak Hash](https://github.com/risc0/risc0/tree/main/examples/keccak)

Proves the Keccak-256 hash of a string inside zkVM using patched [tiny-keccak] and the zkVM's Keccak precompile.  
Useful for Ethereum-related hash proofs, Merkle tree validations, and on-chain data integrity assertions.

[tiny-keccak]: https://docs.rs/crate/tiny-keccak/latest

---

### [Password Checker](https://github.com/risc0/risc0/tree/main/examples/password-checker)

Checks password compliance (e.g., length, characters) inside the zkVM and proves it without revealing the password itself.  
Hashes and salts the password, commits result to the journal. Ideal for **ZK logins, private account setups**, or secure onboarding. [ZK Hack III walkthrough](https://www.youtube.com/watch?v=Yg_BGqj_6lg&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=5) included.

---

### [Guest Profiling (Fibonacci)](https://github.com/risc0/risc0/tree/main/examples/profiling)

Profiles zkVM guest code using cycle-level tracing and exports a `.pb` file for flamegraph visualization via `pprof`.  
Compares different Fibonacci implementations (iterative, batched, matrix exponentiation). Ideal for developers optimizing **performance-critical guest logic**.

[pprof]: https://github.com/google/pprof

### [Pro Rata Distribution](https://github.com/risc0/risc0/tree/main/examples/prorata)

Calculates dollar distributions proportionally from a cap table and proves that a recipient’s share is correct without revealing others’ payouts.  
Ideal for **privacy-preserving shareholder payments**. Supports CSV input, [GPG]-signed audit statements, and verifiable receipts. Example: $1B distribution to InGen Corp. investors.

[GPG]: https://gnupg.org/

---

### [Prover Service Example](https://github.com/risc0/risc0/tree/main/examples/prover)

Minimal example showing how to build a proof-serving API using RISC Zero’s public 1.0 interface.  
Not production-ready, but provides a starting point for implementing your own **zkVM-based backend services**. Includes no error handling or batching yet.

---

### [SHA-256 Hashing](https://github.com/risc0/risc0/tree/main/examples/sha)

Proves SHA-256 hashes using either zkVM’s built-in `risc0_zkvm::sha` or patched [RustCrypto] `sha2` crate.  
Uses zkVM precompiles for performance. Also shows how to parse and display `Digest` results on the host side. [Video tutorial available](https://www.youtube.com/watch?v=Nmxe8cnuO-0&list=PLcPzhUaCxlCjHQleuRhYN09zXgj6b_s-e&index=4).

[RustCrypto]: https://docs.rs/sha2/latest/sha2/

---

### [SmartCore ML Inference](https://github.com/risc0/risc0/tree/main/examples/smartcore-ml)

Runs machine learning model inference (e.g. Decision Trees, PCA, SVM) from the [SmartCore] Rust ML library inside the zkVM.  
Proves that a trained model gave a certain result **without revealing the model or the inputs**. Includes Jupyter notebook for training and exporting. Useful for **zkML applications** like private scoring or clustering.

[SmartCore]: https://github.com/smartcorelib/smartcore

---

### [Voting Machine](https://github.com/risc0/risc0/tree/main/examples/voting-machine)

Implements a verifiable voting system inside the zkVM.  
Supports vote submission, freezing, and verification — with a cryptographic receipt for each step. Voters can check that their ballot is included. Perfect for **zk voting protocols and audits** (⚠️ educational use only).

---

### [Where’s Waldo](https://github.com/risc0/risc0/tree/main/examples/waldo)

Proves that you know Waldo’s location in a large image **without revealing the coordinates**.  
Uses a Merkleized image structure and zkVM cut-out logic. A zk-classic that demonstrates **privacy-preserving visual proofs**. [Read the blog post](https://www.risczero.com/news/waldo).

---

### [WASM Execution](https://github.com/risc0/risc0/tree/main/examples/wasm)

Executes and verifies WASM bytecode inside zkVM using the [wasmi] interpreter.  
Can be extended to run arbitrary WASM logic, making it useful for **zk sandboxing**.

[wasmi]: https://crates.io/crates/wasmi

---

### [Wordle in zkVM](https://github.com/risc0/risc0/tree/main/examples/wordle)

Implements the Wordle game with zk verification. The server commits to a word hash and proves fairness.  
Great example of **zk-powered games** where logic is proven but kept secret.

---

### [XGBoost Inference](https://github.com/risc0/risc0/tree/main/examples/xgboost)

Runs XGBoost model inference inside zkVM and proves correctness of results.  
Model is trained in Python using a Rust-based XGBoost implementation and exported as JSON. Ideal for **zkML production use**.

---
