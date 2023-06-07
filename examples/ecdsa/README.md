# ECDSA Example

This example demonstrates how to verify an ECDSA signature inside the zkVM.

## Use Cases

Verifying digital signatures is a primary method of authentication for many protocols, and ECDSA is
a very notable and widely deployed cryptographic signature scheme. This example shows how to
efficiently verify an ECDSA signature on curve secp256k1, which is used on Ethereum and Bitcoin.

On it's own, this is not immediately useful, but it can be combined with other application logic for
powerful results such as anonymous group signatures, applying transformations to authenticated data,
and fully succinct transaction ledgers.

## Guest Acceleration

ECDSA verification is relatively expensive in the zkVM guest. Using the [RustCrypto] `k256` crate
with RISC Zero v0.15, it takes about 5M cycles to verify a signature.

In order to speed this up, the zkVM implements a 256-bit big integer arithmetic multiplication accelerator, which targets
the main bottleneck for signature verification. Additionally, RISC Zero implements patched versions
of the `crypto-bigint` and `k256` crates which use this accelerator. Using these patches, **ECDSA
signature verification takes about 870k cycles**

You can see an example of how to apply these patches in the [`methods/guest/Cargo.toml`](methods/guest/Cargo.toml) file.

The same patches accelerate all arithmetic on the secp256k1 curve, so they can be used to implement
other cryptographic primitives as well. Additionally, the [changes] made to `k256` can provide an
example of how to use the big integer accelerator circuit to speed up other cryptographic operations
(e.g. P-256, or RSA).

[RustCrypto]: https://docs.rs/k256/latest/k256/
[changes]: https://github.com/risc0/RustCrypto-elliptic-curves/pull/1
