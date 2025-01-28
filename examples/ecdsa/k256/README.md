# ECDSA Example

This example demonstrates how to verify an ECDSA signature inside the zkVM using secp256k1 signatures.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Use Cases

Verifying digital signatures is a primary method of authentication for many protocols, and ECDSA is
a widely deployed cryptographic signature scheme. This example shows how to efficiently verify an
ECDSA signature on curve secp256k1, which is used on Ethereum and Bitcoin.

Signature verification can be combined with other application logic for powerful results such as
[anonymous group signatures][1], [applying transformations to authenticated data][2], and [fully succinct
transaction ledgers][3].

## Precompile Patch

ECDSA verification is relatively expensive in the zkVM guest. Using the [RustCrypto] `k256` crate
with RISC Zero v0.15, it takes about 5M zkVM cycles[^1] to verify a signature.

In order to speed this up, the zkVM implements a 256-bit big integer multiplication accelerator, which targets
the main bottleneck for signature verification. Additionally, RISC Zero implements patched versions
of the `crypto-bigint` and `k256` crates which use this accelerator. Using these patches, **ECDSA
signature verification takes about 870k cycles**[^2]

You can see an example of how to apply these patches in the [`methods/guest/Cargo.toml`][4] file.

The same patches accelerate all arithmetic on the secp256k1 curve, so they can be used to implement
other cryptographic primitives as well. Additionally, the [changes][5] made to `k256` can provide an
example of how to use the big integer accelerator circuit to speed up other cryptographic operations
(e.g. P-256, or RSA).

For more information on how to use the precompile, see the [precompile documentation][6].

[^1]: About 126s to execute and prove on an M1 MacBook Pro using RISC Zero v0.15.

[^2]: About 17s to execute and prove on an M1 MacBook Pro using RISC Zero v0.15.

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[RustCrypto]: https://docs.rs/k256/latest/k256/
[1]: https://semaphore.appliedzkp.org/
[2]: https://medium.com/@boneh/using-zk-proofs-to-fight-disinformation-17e7d57fe52f
[3]: https://minaprotocol.com/
[4]: methods/guest/Cargo.toml
[5]: https://github.com/risc0/RustCrypto-elliptic-curves/pull/1
[6]: https://dev.risczero.com/api/zkvm/precompiles