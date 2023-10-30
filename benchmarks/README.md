# Benchmarks

## How to update the ghpages

On every PR merged to `main`, the benchmark results will be pushed to the https://github.com/risc0/ghpages/tree/dev branch. After reviewing the result, you should create a PR on the ghpages repo to publish on https://risc0.github.io/ghpages/dev/benchmarks/index.html.

All `ghpages` static files reside in the `ghpages` folder of the `risc0` repo. Any modifications to `ghpages` should be made via the `risc0` repo henceforth.

For previewing results:

- Switch to the `dev` branch of the `ghpages` repo.
- Use a development server like [five-server](https://github.com/yandeu/five-server) for HTML previewing; VSCode users can find an extension

## Running all the benchmarks

### CPU

```console
$ RUST_LOG=info cargo run --release --bin risc0-benchmark -- --out metrics.csv all
```

### Metal

```console
$ RUST_LOG=info cargo run --release --bin risc0-benchmark -F metal -- --out metrics.csv all
```

### CUDA

```console
$ RUST_LOG=info cargo run --release --bin risc0-benchmark -F cuda -- --out metrics.csv all
```

## Running specific benchmark
To run a specific benchmark replace the `all` option used in the previous command with one of the following:
e.g.,
```console
$ RUST_LOG=info cargo run --release -F metal -- --out metrics.csv big-sha2
```

### `big-sha2`

Computes the SHA2-256 hash of large random buffers of various sizes.

### `iter-sha2`

Computes the SHA2-256 hash of a given buffer for a given amount of iterations.

### `big-keccak`

Computes the Keccak hash of large random buffers of various sizes.

### `iter-keccak`

Computes the Keccak hash of a given buffer for a given amount of iterations.

### `big-blake2b`

Computes the Blake2b hash of large random buffers of various sizes.

### `iter-blake2b`

Computes the Blake2b hash of a given buffer for a given amount of iterations.

### `big-blake3`

Computes the Blake3 hash of large random buffers of various sizes.

### `iter-blake3`

Computes the Blake3 hash of a given buffer for a given amount of iterations.

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

### `zeth`

Computes the proof for a given Ethereum block containing a given number of transactions.

## Average benchmark

An average (i.e., a given job runs for several iterations, then the time to prove a single iteration is extracted as its average) version of this benchmark is available by running:

### CPU

```console
$ RUST_LOG=info cargo run --release --bin average -- --out metrics.csv all
```

### Metal

```console
$ RUST_LOG=info cargo run --release --bin average -F metal -- --out metrics.csv all
```

### CUDA

```console
$ RUST_LOG=info cargo run --release --bin average -F cuda -- --out metrics.csv all
```

### Bonsai

```console
$ RISC0_DEV_MODE=false BONSAI_API_URL=<API> BONSAI_API_KEY=<API_KEY> RUST_LOG=debug cargo run --release --bin average -- --out metrics-bonsai.csv all
```
