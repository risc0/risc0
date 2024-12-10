# Precompiles

RISC Zero's rv32im implementation includes a number of specialized extension
circuits, including "precompiles" for cryptographic and algebraic functions: SHA-256,
RSA, elliptic curve, and modular multiplication operations.
By implementing these operations directly in the "hardware" of
the zkVM, programs that use these precompiles execute faster and can be proven
with significantly less resources [^1].

## Accelerated Crates

We have patched several popular cryptographic Rust crates to create
"accelerated" versions that integrate our precompiles.

For the most up to date tags to use for the following crates, see the `/releases` in
each fork's repository on GitHub.

### Hash Functions

| Crate | Versions supported | Patch Statement Example |
|-------|-------------------|------------------------|
| [`sha2`](https://github.com/risc0/RustCrypto-hashes/releases) | 0.10.8, 0.10.7, 0.10.6, 0.9.9 | `sha2 = { git = "https://github.com/risc0/RustCrypto-hashes", tag = "sha2-v0.10.8-risczero.0" }` |

### ECDSA

| Crate | Versions supported | Patch Statement Example |
|-------|-------------------|------------------------|
| [`k256`](https://github.com/risc0/RustCrypto-elliptic-curves/releases) | 0.13.4, 0.13.3, 0.13.2, 0.13.1 | `k256 = { git = "https://github.com/risc0/RustCrypto-elliptic-curves", tag = "k256/v0.13.3-risczero.1" }` [^2] |

### EDDSA

| Crate | Versions supported | Patch Statement Example |
|-------|-------------------|------------------------|
| [`curve25519-dalek`](https://github.com/risc0/curve25519-dalek/releases) | 4.1.2, 4.1.1, 4.1.0 | `ed25519-dalek = { git = "https://github.com/risc0/ed25519-dalek", tag = "curve25519-4.1.2-risczero.0" }` |

### RSA

| Crate | Versions supported | Patch Statement Example |
|-------|-------------------|------------------------|
| [`rsa`](https://github.com/risc0/RustCrypto-RSA/releases) | 0.9.6 | `rsa = { git = "https://github.com/risc0/RustCrypto-RSA", tag = "v0.9.6-risczero.0" }` [^2] |

### Other Accelerated Crates

| Crate | Versions supported | Patch Statement Example |
|-------|-------------------|------------------------|
| [`crypto-bigint`](https://github.com/risc0/RustCrypto-crypto-bigint/releases) | 0.5.5, 0.5.4, 0.5.3, 0.5.2 | `crypto-bigint = { git = "https://github.com/risc0/RustCrypto-crypto-bigint", tag = "v0.5.5-risczero.0" }` |

Make sure that your dependency gives the same patch version of the crate as listed in
the git tag of the patch. If you need other patch versions or crates than listed here, please reach
out to us on [Discord][discord-url] or otherwise!

If using `tag = "sha2-v0.10.8-risczero.0"`, the dependency should be:

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
crates it may be possible to enable acceleration support without code changes by
applying a [Cargo patch][cargo-patch].

Several of our precompiles are still undergoing revision and
review, and so users must opt-in to these features by setting the `"unstable"`
feature flag on the `risc0-zkvm` crate used by the zkVM guest and by the
`risc0-build` crate used to build the guest. For users who need a stable,
production-ready version we are working on stablizing these precompiles as soon
as possible.

An example of how to use these crates to accelerate ECDSA signature verification
can be in the [ECDSA example][ecdsa]. Note the [use of the patched
versions][ecdsa-patched] of `sha2`, `crypto-bigint` and `k256` crates used in
the guest's `Cargo.toml`.

## Adding Precompile Support To Crates

It's possible to add precompile support for your own crates.

An example of how to do this can be found in this [diff of RISC Zero's k256
crate fork][k256-diff], which shows the code changes needed to accelerate
RustCrypto's secp256k1 ECDSA library. This fork starts from the base
implementation, and changes the core operations to use the accelerated 256-bit
elliptic curve instructions. E.g. [`lincomb`][lincomb].

## Stability

Certain versions of patches for some crates (e.g. `k256`, `rsa`) depend on more optimized
precompiles that are still undergoing revision and review, and so users must opt-in to these
features by setting the `"unstable"` [feature flag][feature-flag] on the `risc0-zkvm` crate used by
the zkVM guest and by the `risc0-build` crate used to build the guest. These also require using
versions `>1.2.0` of `risc0` crates. For users who need a stable, production-ready version we are
working on stablizing these precompiles as soon as possible, and the `"unstable"` feature flag will
no longer be required.


[^1]: This is similar to the cryptography support such as [AES-NI] or the [SHA
    extensions] for x86 processors. In both cases, the circuitry is extended to
    compute otherwise expensive operations in fewer instruction cycles.

[^2]: Some tagged releases of this crate may depend on updated precompiles.
    See [Stability](#stability) for more details.

[AES-NI]: https://en.wikipedia.org/wiki/AES_instruction_set#x86_architecture_processors
[cargo-patch]: https://doc.rust-lang.org/cargo/reference/overriding-dependencies.html#the-patch-section
[commit-lockfile]: https://blog.rust-lang.org/2023/08/29/committing-lockfiles.html
[curve25519-dalek]: https://github.com/risc0/curve25519-dalek/tree/risczero
[discord-url]: https://discord.gg/risczero
[ecdsa]: https://github.com/risc0/risc0/tree/release-1.2/examples/ecdsa
[ecdsa-patched]: https://github.com/risc0/risc0/blob/release-1.2/examples/ecdsa/methods/guest/Cargo.toml#L13-L18
[feature-flag]: https://doc.rust-lang.org/cargo/reference/features.html#dependency-features
[git-dep]: https://doc.rust-lang.org/cargo/reference/specifying-dependencies.html#specifying-dependencies-from-git-repositories
[k256-diff]: https://github.com/risc0/RustCrypto-elliptic-curves/compare/k256/v0.13.3..k256/v0.13.3-risczero.1
[lincomb]: https://github.com/risc0/RustCrypto-elliptic-curves/blob/k256/v0.13.3-risczero.1/k256/src/arithmetic/mul.rs#L349-L377
[RustCrypto-crypto-bigint]: https://github.com/risc0/RustCrypto-crypto-bigint/tree/risczero
[RustCrypto-elliptic-curves]: https://github.com/risc0/RustCrypto-elliptic-curves/tree/risczero
[RustCrypto-hashes]: https://github.com/risc0/RustCrypto-hashes/tree/risczero
[RustCrypto-RSA]: https://github.com/risc0/RustCrypto-RSA/tree/risc0
[SHA extensions]: https://en.wikipedia.org/wiki/Intel_SHA_extensions
