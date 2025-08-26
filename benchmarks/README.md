# Benchmarks

## How to Update the ghpages

On every PR merged to `main`, the benchmark results will be pushed to the [https://github.com/risc0/ghpages/tree/dev](https://github.com/risc0/ghpages/tree/dev) branch. After reviewing the result, you should create a PR on the ghpages repo to publish on [https://reports.risczero.com/](https://reports.risczero.com/).

All `ghpages` static files reside in the `ghpages` folder of the `risc0` repo. Any modifications to `ghpages` should be made via the `risc0` repo henceforth.

For previewing results:

- Switch to the `dev` branch of the `ghpages` repo.
- Use a development server like [five-server](https://github.com/yandeu/five-server) for HTML previewing; VSCode users can find an extension

## Running All the Benchmarks

### CPU

```console
cargo run --release
```

### Metal

```console
cargo run --release -F metal
```

### CUDA

```console
cargo run --release -F cuda
```

## Running Specific Benchmark

```console
cargo run --release -F metal -- big-sha2
```

### `big-sha2`

Computes the SHA2-256 hash of large random buffers of various sizes.

### `iter-sha2`

Computes the SHA2-256 hash of a given buffer for a given number of iterations.

### `big-keccak`

Computes the Keccak hash of large random buffers of various sizes.

### `iter-keccak`

Computes the Keccak hash of a given buffer for a given number of iterations.

### `big-blake2b`

Computes the Blake2b hash of large random buffers of various sizes.

### `iter-blake2b`

Computes the Blake2b hash of a given buffer for a given number of iterations.

### `big-blake3`

Computes the Blake3 hash of large random buffers of various sizes.

### `iter-blake3`

Computes the Blake3 hash of a given buffer for a given number of iterations.

### `ecdsa-verify`

Verifies a given ECDSA signature (on the secp256k1 curve).

### `ed25519-verify`

Verifies a given Ed25519 signature (on the ed25519 curve).

### `fibonacci`

Computes the Fibonacci sequence of a given number.

### `membership`

Computes the membership proof for a given authenticated path from a leaf to a merkle tree root. It uses SHA2-256 as hash function.

### `sudoku`

Verifies a given Sudoku solution.
