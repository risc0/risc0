# Benchmarks

### `big_sha2`

Computes the SHA2-256 hash of large random buffers of various sizes.

### `iter_sha2`

Computes the SHA2-256 hash of a given buffer for a given amount of iterations.

### `big_keccak`

Computes the Keccak hash of large random buffers of various sizes.

### `iter_keccak`

Computes the Keccak hash of a given buffer for a given amount of iterations.

### `big_blake2b`

Computes the Blake2b hash of large random buffers of various sizes.

### `iter_blake2b`

Computes the Blake2b hash of a given buffer for a given amount of iterations.

### `big_blake3`

Computes the Blake3 hash of large random buffers of various sizes.

### `iter_blake3`

Computes the Blake3 hash of a given buffer for a given amount of iterations.

### `ecdsa_verify`

Verifies a given ECDSA signature (on the secp256k1 curve).

## Running the benchmarks

```console
$ RUST_LOG=info cargo run --release -- --out metrics.csv all
```
