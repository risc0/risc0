# Precompiles

RISC Zero's rv32im implementation includes a number of specialized extension
circuits, including "precompiles" for cryptographic and algebraic functions: SHA-256,
RSA, elliptic curve, and modular multiplication operations.
By implementing these operations directly in the "hardware" of
the zkVM, programs that use these precompiles execute faster and can be proven
with significantly less resources [^1].

To see statistics on precompile usage in your guest program, use `RISC0_INFO=1`.

## Patched Crates

We have patched several popular cryptographic Rust crates to create
"accelerated" versions that integrate our precompiles.

For the most up to date tags to use for the following crates, see the `/releases` in
each fork's repository on GitHub.

| Crate                                                                         | Versions supported             | Patch Statement Example                                                                                    | Requires Unstable Flag? |
| ----------------------------------------------------------------------------- | ------------------------------ | ---------------------------------------------------------------------------------------------------------- | ----------------------- |
| [`sha2`](https://github.com/risc0/RustCrypto-hashes/releases)                 | 0.10.8, 0.10.7, 0.10.6, 0.9.9  | `sha2 = { git = "https://github.com/risc0/RustCrypto-hashes", tag = "sha2-v0.10.8-risczero.0" }`           | No                      |
| [`tiny-keccak`](https://github.com/risc0/tiny-keccak/releases)                | 2.0.2                          | `tiny-keccak = { git = "https://github.com/risc0/tiny-keccak", tag = "tiny-keccak/v2.0.2-risczero.0" }`    | [Yes]                   |
| [`k256`](https://github.com/risc0/RustCrypto-elliptic-curves/releases)        | 0.13.4, 0.13.3, 0.13.2, 0.13.1 | `k256 = { git = "https://github.com/risc0/RustCrypto-elliptic-curves", tag = "k256/v0.13.3-risczero.1" }`  | [Yes]                   |
| [`p256`](https://github.com/risc0/RustCrypto-elliptic-curves/releases)        | 0.13.2                         | `p256 = { git = "https://github.com/risc0/RustCrypto-elliptic-curves", tag = "p256/v0.13.2-risczero.1" }`  | [Yes]                   |
| [`curve25519-dalek`](https://github.com/risc0/curve25519-dalek/releases)      | 4.1.2, 4.1.1, 4.1.0            | `ed25519-dalek = { git = "https://github.com/risc0/ed25519-dalek", tag = "curve25519-4.1.2-risczero.0" }`  | No                      |
| [`rsa`](https://github.com/risc0/RustCrypto-RSA/releases)                     | 0.9.6                          | `rsa = { git = "https://github.com/risc0/RustCrypto-RSA", tag = "v0.9.6-risczero.0" }`                     | [Yes]                   |
| [`substrate-bn`](https://github.com/risc0/paritytech-bn/releases)             | 0.6.0                          | `substrate-bn = { git = "https://github.com/risc0/paritytech-bn", tag = "v0.6.0-risczero.0" }`             | [Yes]                   |
| [`bls12_381`](https://github.com/risc0/zkcrypto-bls12_381/releases)           | 0.8.0                          | `bls12_381 = { git = "https://github.com/risc0/zkcrypto-bls12_381", tag = "v0.8.0-risczero.0" }`           | [Yes]                   |
| [`blst`](https://github.com/risc0/blst/releases)                              | 0.3.14                         | `blst = { git = "https://github.com/risc0/blst", tag = "blst/v0.3.14-risczero.0" }`                        | [Yes]                   |
| [`crypto-bigint`](https://github.com/risc0/RustCrypto-crypto-bigint/releases) | 0.5.5, 0.5.4, 0.5.3, 0.5.2     | `crypto-bigint = { git = "https://github.com/risc0/RustCrypto-crypto-bigint", tag = "v0.5.5-risczero.0" }` | [Yes]                   |

Make sure that your dependency gives the same patch version of the crate as listed in
the git tag of the patch. If you need other patch versions or crates than listed here, please reach
out to us on [Discord][discord-url] or otherwise!

If using `tag = "sha2-v0.10.8-risczero.0"`, the dependency should be defined as a
[git dependency][git-dep]:

```toml
[dependencies]
sha2 = "=0.10.8"

[patch.crates-io]
sha2 = { git = "https://github.com/risc0/RustCrypto-hashes", tag = "sha2-v0.10.8-risczero.0" }
```

In some situations, for example when a patch is used indirectly, you may
need to update the version specifically to update your lockfile for your guest.
For example:

```sh
cargo update -p sha2 --precise 0.10.8
```

> Note: To ensure that the patch is being applied, search for the crate in the `Cargo.lock` file
> of your guest to ensure that it references the fork repository. It is generally good practice to
> [commit the `Cargo.lock` file to git][commit-lockfile], to ensure versions don't get accidentally updated.

When using cryptography indirectly, e.g. via the `cookie`, `oauth2`, or `revm`,
crates it may be possible to enable precompile support without code changes by
applying a [Cargo patch][cargo-patch].

An example of how to use these crates to accelerate ECDSA signature verification
can be in the [ECDSA example][ecdsa]. Note the [use of the patched
versions][ecdsa-patched] of `sha2`, `crypto-bigint` and `k256` crates used in
the guest's `Cargo.toml`.

Some crates will allow you a choice of different backend crates, and you may be
able to use this to select a crate we have already published a patch for. An
example is Revm's `revm-precompile` crate, which by default uses `k256`; in this
case you can use [our patch for `k256`][k256-patch]. However, if you set the
[`secp256k1` feature flag][revm-precompile-toml], it will use the `secp256k1`
crate instead, where we don't currently provide a patch.

If you need a precompile patched into a different crate than the ones listed
here, please reach out and let us know!

## Adding Precompile Support To Crates

It's possible to add precompile support for your own crates.

An example of how to do this can be found in this [diff of RISC Zero's k256
crate fork][k256-diff], which shows the code changes needed to accelerate
RustCrypto's secp256k1 ECDSA library. This fork starts from the base
implementation, and changes the core operations to use the precompiled 256-bit
elliptic curve instructions. E.g. [`lincomb`][lincomb].

## Stability

Certain versions of patches for some crates (e.g. `k256`, `rsa`) depend on more optimized
precompiles that are still undergoing revision and review, and so users must opt-in to these
features by setting the `"unstable"` [feature flag][feature-flag] on the `risc0-zkvm` crate used by
the zkVM guest and by the `risc0-build` crate used to build the guest. These also require using
versions `>=1.2.0` of `risc0` crates. For users who need a stable, production-ready version we are
working on stabilizing these precompiles as soon as possible, and the `"unstable"` feature flag will
no longer be required.

## Timing Attacks

These precompiles do not currently provide strict guarantees about constant-time execution and
proving time. Be very careful if using any of these precompiles with private data, such as signing
a message within the zkvm where an observer can measure the proving time or view cycle counts.

[^1]: This is similar to the cryptography support such as [AES-NI] or the [SHA
    extensions] for x86 processors. In both cases, the circuitry is extended to
    compute otherwise expensive operations in fewer instruction cycles.

[AES-NI]: https://en.wikipedia.org/wiki/AES_instruction_set#x86_architecture_processors
[cargo-patch]: https://doc.rust-lang.org/cargo/reference/overriding-dependencies.html#the-patch-section
[commit-lockfile]: https://blog.rust-lang.org/2023/08/29/committing-lockfiles.html
[discord-url]: https://discord.gg/risczero
[ecdsa]: https://github.com/risc0/risc0/tree/release-1.2/examples/ecdsa
[ecdsa-patched]: https://github.com/risc0/risc0/blob/release-1.2/examples/ecdsa/k256/methods/guest/Cargo.toml#L13-L18
[feature-flag]: https://doc.rust-lang.org/cargo/reference/features.html#dependency-features
[git-dep]: https://doc.rust-lang.org/cargo/reference/specifying-dependencies.html#specifying-dependencies-from-git-repositories
[k256-diff]: https://github.com/risc0/RustCrypto-elliptic-curves/compare/k256/v0.13.3..k256/v0.13.3-risczero.1
[k256-patch]: https://github.com/risc0/RustCrypto-elliptic-curves/tree/k256/v0.13.3-risczero.1
[lincomb]: https://github.com/risc0/RustCrypto-elliptic-curves/blob/k256/v0.13.3-risczero.1/k256/src/arithmetic/mul.rs#L349-L377
[revm-precompile-toml]: https://github.com/bluealloy/revm/blob/45581c451a440776fd59576d7b27c366b1528724/crates/precompile/Cargo.toml
[SHA extensions]: https://en.wikipedia.org/wiki/Intel_SHA_extensions
[Yes]: #stability
