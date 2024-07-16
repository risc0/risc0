# Cryptography Acceleration

RISC Zero’s rv32im implementation includes a number of specialized extension
circuits, including two “accelerators” for cryptographic functions: SHA-256 and
[256-bit modular multiplication][bigint], referred to as "bigint"
multiplication. By implementing these operations directly in the “hardware” of
the zkVM, programs that use these accelerators execute faster and can be proven
with significantly less resources \[^1].

## Accelerated Crates

The SHA-256 and bigint accelerators are currently integrated in "accelerated"
versions of popular cryptographic Rust crates.

These crates include:

- [RustCrypto's `crypto-bigint` crate][RustCrypto-crypto-bigint]
- [RustCrypto's `sha2` crate][RustCrypto-hashes]
- [RustCrypto's `k256` crate][RustCrypto-elliptic-curves]
- [Dalek Cryptography's curve25519-dalek crate][curve25519-dalek]

Each of these are forks of the original source code repository, with
modifications to use RISC Zero cryptography extensions.

### Using Accelerated Crates

When using any of the crates listed above directly, specifying the dependency as
a [git dependency][git-dep]. For example:

```toml
[dependencies.sha2]
git = "https://github.com/risc0/RustCrypto-hashes"
tag = "sha2-v0.10.6-risczero.0"
```

When using cryptography indirectly, e.g. via the `cookie`, `oauth2`, or `revm`,
crates it may be possible to enable acceleration support without code changes by
applying a [Cargo patch][cargo-patch].

An example of how to use these crates to accelerate ECDSA signature verification
can be in the [ECDSA example][ecdsa]. Note the [use of the patched
versions][ecdsa-patched] of `sha2`, `crypto-bigint` and `k256` crates used in
the guest's `Cargo.toml`.

## Adding Accelerator Support To Crates

It's possible to add accelerator support for your own crates.

An example of how to do this can be found in this [diff of RISC Zero's k256
crate fork][k256-diff], which shows the code changes needed to accelerate
RustCrypto's secp256k1 ECDSA library. This fork starts from the base
implementation, and changes the core operations to use the accelerated 256-bit
modular multiplication instruction. E.g. [`FieldElement8x32R0::mul`][field-mul].

\[^1]:
This is similar to the cryptography support such as [AES-NI] or the [SHA
extensions][SHA
    extensions] for x86 processors. In both cases, the circuitry is extended to
compute otherwise expensive operations in fewer instruction cycles.

[AES-NI]: https://en.wikipedia.org/wiki/AES_instruction_set#x86_architecture_processors
[bigint]: https://github.com/risc0/risc0/pull/466
[cargo-patch]: https://doc.rust-lang.org/cargo/reference/overriding-dependencies.html#the-patch-section
[curve25519-dalek]: https://github.com/risc0/curve25519-dalek/tree/risczero
[ecdsa]: https://github.com/risc0/risc0/tree/release-0.20/examples/ecdsa
[ecdsa-patched]: https://github.com/risc0/risc0/blob/release-0.20/examples/ecdsa/methods/guest/Cargo.toml#L13-L18
[field-mul]: https://github.com/risc0/RustCrypto-elliptic-curves/compare/k256/v0.13.1..k256/v0.13.1-risczero.1#diff-ab10e01be1d99a874f90c9a6143bb1c64f37e04dcb220b5ab50b9273d99e0a0cR176-R179
[git-dep]: https://doc.rust-lang.org/cargo/reference/specifying-dependencies.html#specifying-dependencies-from-git-repositories
[k256-diff]: https://github.com/risc0/RustCrypto-elliptic-curves/compare/k256/v0.13.1..k256/v0.13.1-risczero.1
[RustCrypto-crypto-bigint]: https://github.com/risc0/RustCrypto-crypto-bigint/tree/risczero
[RustCrypto-hashes]: https://github.com/risc0/RustCrypto-hashes/tree/risczero
[RustCrypto-elliptic-curves]: https://github.com/risc0/RustCrypto-elliptic-curves/tree/risczero
[SHA extensions]: https://en.wikipedia.org/wiki/Intel_SHA_extensions
