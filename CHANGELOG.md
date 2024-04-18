# CHANGELOG

## Next (upcoming release)
TBD

### 🚨 Breaking Changes
* The `Prover` trait's `prove()` function now returns a `ProveInfo`. This struct
  contains the receipt as well as cycle and segment information gathered during
  the proof generation. The following is the definition of `ProveInfo` and
  `SessionStats` structs:
```Rust
/// Information returned by the prover including receipt as well as other information useful for debugging
pub struct ProveInfo {
    /// receipt from the computation
    pub receipt: Receipt,
    /// stats about cycle counts of the execution
    pub stats: SessionStats,
}

/// Struct containing information about a prover's cycle count after running the guest program
pub struct SessionStats {
    /// Count of segments in this proof request
    pub segments: usize,
    /// Total cycles run within guest
    pub total_cycles: u64,
    /// User cycles run within guest
    pub user_cycles: u64,
}
```
For those upgrading from v0.21.0, the following code change is necessary on the host side to retrieve the receipt.
```diff
-   let receipt = prover.prove(env, BEVY_GUEST_ELF).unwrap();
+   let receipt = session.prove().unwrap().receipt;
 ```
# [v0.21.0 (2024-03-11)](https://github.com/risc0/risc0/releases/tag/v0.21.0)

### 🛠 Fixes
* Fix an issue where the temporary directory is not being removed when the
`Session` goes out of scope. This helps prevent the depletion of disk space.

* Verification of groth16 receipts in rust that are compatible with Bonsai

### ⚡️ Features

* Add an improved Poseidon2 hashing function that replaces Poseidon for recursive proofs.

### 🚨 Breaking Changes
* For recursive proofs, the Poseidon hash function is replaced by the Poseidon2 hash function. Users can still create receipts using the older Poseidon hash function but these receipts will not be usable by Bonsai or any proof composition or rollup use cases.

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
