# ECDSA P256 (secp256r1) Example

This example demonstrates how to verify an ECDSA signature inside the zkVM using secp256r1 signatures, also known as NIST P-256. The secp256r1 curve is widely used in TLS, secure hardware enclaves, and various security protocols.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Use Cases

Verifying digital signatures is a primary method of authentication for many protocols, and ECDSA is
a widely deployed cryptographic signature scheme. This example shows how to efficiently verify an
ECDSA signature on curve secp256r1 (NIST P-256), which is commonly used in:

* TLS/SSL security protocols
* Trusted Execution Environment (TEE) attestations
* Secure hardware modules
* Smart cards and security tokens
* Various government and industry standards

Signature verification can be combined with other application logic for powerful results such as
[anonymous group signatures][1], [applying transformations to authenticated data][2], and [fully succinct
transaction ledgers][3].

## P256 Precompile Implementation

ECDSA verification is relatively expensive in the zkVM guest without acceleration. To speed this up, the zkVM implements specialized precompile circuits for elliptic curve operations. The RISC Zero patched version of the `p256` crate uses these precompiles to significantly accelerate operations.

Using these precompiles, **ECDSA signature verification on the P-256 curve takes about 220K cycles**, down from ~12M cycles without acceleration - an improvement of approximately 55x.

The precompile works by optimizing the core elliptic curve operations:

* Point addition
* Point doubling
* Scalar multiplication

### How to Use the P256 Precompile

To use the P256 precompile in your own project:

1. Add the patched dependency to your guest's Cargo.toml:

```toml
[dependencies]
p256 = { version = "=0.13.2", features = ["serde", "expose-field", "std", "ecdsa"] }

[patch.crates-io]
p256 = { git = "https://github.com/risc0/RustCrypto-elliptic-curves", tag = "p256/v0.13.2-risczero.1" }
sha2 = { git = "https://github.com/risc0/RustCrypto-hashes", tag = "sha2-v0.10.8-risczero.0" }
crypto-bigint = { git = "https://github.com/risc0/RustCrypto-crypto-bigint", tag = "v0.5.5-risczero.0" }
```

2. Enable the "unstable" feature in your risc0-zkvm dependency:

```toml
risc0-zkvm = { version = "1.2.0", default-features = false, features = ["std", "unstable"] }
```

3. Use the p256 crate as you normally would - the optimizations are automatically applied:

```rust
use p256::{
    ecdsa::{signature::Verifier, Signature, VerifyingKey},
    EncodedPoint,
};

// ... code to load key and signature ...

// This verification will be accelerated automatically
verifying_key
    .verify(&message, &signature)
    .expect("ECDSA signature verification failed");
```

You can see the complete working example in the source code of this example. For more reference implementation details, look at:

* [p256\_verify.rs](methods/guest/src/bin/p256_verify.rs) - Guest code that uses the precompile
* [main.rs](src/main.rs) - Host code that calls the guest

For more information on how to use the precompile and other available precompiles, see the [precompile documentation][5].

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples

[RustCrypto]: https://docs.rs/p256/latest/p256/

[1]: https://semaphore.appliedzkp.org/

[2]: https://medium.com/@boneh/using-zk-proofs-to-fight-disinformation-17e7d57fe52f

[3]: https://minaprotocol.com/

[4]: methods/guest/Cargo.toml

[5]: https://dev.risczero.com/api/zkvm/precompiles
