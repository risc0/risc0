# CHANGELOG

## Next (upcoming release)

### 🛠 Fixes

* Fix temporary directory not being removed when session goes out of scope. This
  can help prevent out of disk space issues.

### ⚡️ Features

* Improved API for handling private outputs
* Add support for configuration of intermediate segment storage (on-disk,
  in-memory, etc).

### 🚨 Breaking Changes

# [v0.20.1 (2024-02-01)](https://github.com/risc0/risc0/releases/tag/v0.20.1)

### 🛠 Fixes

* Revert change to `Prover::prove` to return a `SuccinctReceipt`. This prevents
  a performance regression for default use cases.

# [v0.20.0 (2024-01-29)](https://github.com/risc0/risc0/releases/tag/v0.20.0)

### 🛠 Fixes

* Restrict software ecall handler address range
* Fix argument handling in client/server mode
* Change jal to call in zkVM entrypoint #1257
* Improve ZKR zip file handling

### ⚡️ Features

* Support for [Proof Composition](https://dev.risczero.com/terminology#composition)
* Add execution statistics when using `RUST_LOG=info`
* Add XGBoost example using Spice AI query to train a model
* Improve CUDA performance by integrating [sppark](https://github.com/supranational/sppark/)
* Add Poseidon2 support to CUDA backend
* Support for verifying Groth16 proofs
* Add exponential backoff to bonsai proof polling
* add `getrandom` feature to toggle getrandom in the guest
* Adjust `Prover::prove` to return a `SuccinctReceipt` by default

### 🚨 Breaking Changes

* Rename `ReceiptMetadata` to `ReceiptClaim`
* Drop `MemoryImage` from the public API
* Drop _elf suffix from API. For example, `Prover::prove_elf` is renamed `Prover::prove`.
