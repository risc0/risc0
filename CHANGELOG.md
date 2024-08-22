# CHANGELOG

## Next (upcoming release)
## [v1.1.0-rc.2 (2024-08-22)](https://github.com/risc0/risc0/releases/tag/v1.1.0-rc.2)
### 🔥 Performance Improvements
* Improve GPU performance by 28%. For more information checkout our [reports page](https://reports.risczero.com/benchmarks#Linux-nvidia_rtx_3090_ti-succinct). (#2211)
* Speed up null builds of guest programs by 20x. (#2208)

### 🛠 Fixes
* Released Rust toolchain `r0.1.79.0-1`. This toolchain fixes a crash in the guest that appears when enabling the heap allocator in combination with `thread_local!` in the zkVM guest.
* Clean up `risc0_core::scope!` macro used to measure performance. (#2217)
* Clippy now works by default on host-side code for rust projects that contain risc0 guest code. To run Clippy on the host-side code for risc0 projects, specify `RISC0_SKIP_BUILD=1` as a part of the Clippy command. (#2210)
* Add linter to website (#2096)

### ⚡️ Features
* Add `cargo risczero datasheet` command. This enables users to run performance benchmarks on their machines locally. (#2196)
* Add the `risc0-circuit-bigint` crate. This is a foundational component for our accelerators. More documentation will follow as we solidify this crate and accelerators. (#2201)
* Add examples and improve verbiage for datasheet. (#2242)
* Add blog link and use a cleaner mermaid theme for code examples on developer documentation website. (#2190)
### 🚨 Breaking Changes
* The poseidon hashing function has been removed from the prover. This hashing function has been superseded by poseidon2 in the prover for a while now. For those who are using default prover configurations and the public API, this has absolutely no impact. For those who are using the old poseidon hash function to generate risc0 proofs, it is highly encouraged to switch to poseidon2 for improved performance.

## [v1.1.0-rc.1 (2024-08-09)](https://github.com/risc0/risc0/releases/tag/v1.1.0-rc.1)

### 🔥 Performance Improvements
* CUDA performance improvements. This results in about a 20-30% performance improvement. https://github.com/risc0/risc0/pull/2054
* Add recursion preflight support for checked bytes/bigint https://github.com/risc0/risc0/pull/1973

### 🛠 Fixes

* Improve zero-knowledge property of the prover by increasing the amount of noise. We have used techniques described in this [paper](https://eprint.iacr.org/2024/1037.pdf) to strengthen the ZK property of the prover. See [these docs](https://dev.risczero.com/api/security-model#zero-knowledge-proving) for more information about zero knowledge and our proving system. This change results in a new set of control IDs. See the breaking changes section to learn more about this minor breaking change. https://github.com/risc0/risc0/pull/1970
* Fix template generation for `--nostd` mode. https://github.com/risc0/risc0/pull/2030
* Serializer: fix serialization of types such as `chronos::NaiveDate` that call into `collect_str`. https://github.com/risc0/risc0/pull/2035
* Fix build output. The build output from host and guest compilations were intermingled. A fix has been made to clean up the output.  https://github.com/risc0/risc0/pull/1826


### ⚡️ Features

* Add "light builds". A new faster way to build guest programs intended for development only. This will allow the user to build the guest without linking the emitted ELF bytes. https://github.com/risc0/risc0/pull/2166
* Add an optional embedded allocator to the zkVM guest. By default, the zkvm uses an allocator that does not deallocate heap memory. The embedded allocator deallocates and is useful for situations where the guest runs out of memory. If used, this allocator will result in an increased amount of cycles due to the extra operations necessary to deallocate memory. https://github.com/risc0/risc0/pull/2174
* Add experimental support for `sys_fork`. This syscall allows the zkVM to execute unconstrained code. The RISC-V code executed within this system call will not be encoded as a part of the trace execution. This can be used to implement hints and advice. For example, the square root of two can be computed using `sys_fork` and the solution can be verified in the guest by checking that the square of this solution is equal to two. https://github.com/risc0/risc0/pull/2084
* Use `stability::unstable` to mark new experimental APIs. https://github.com/risc0/risc0/pull/2182
* Add unstable `env::read_frame()` and `env::read_framed()` which improves cycle counts when reading the input from the guest. https://github.com/risc0/risc0/pull/2182
* Re-vamped rzup. The rzup utility is used to install toolchains and extensions. The first implementation was a simple bash script. This has been replaced by a more robust rust implementation. https://github.com/risc0/risc0/pull/1961
* Enable GPU proving by default on macOS. Previously, we have allowed the user to prove on CPU or GPU. This improves user experience by shipping a GPU-enabled r0vm server by default. https://github.com/risc0/risc0/pull/2092
* Added an example that showcases how the `c-kzg` crate can be run in the zkVM. https://github.com/risc0/risc0/pull/2045
* Added an example that uses C as the guest code. This demonstrates how a user can use C to write an entire guest program without rust. https://github.com/risc0/risc0/pull/1898
* Added a simple prover service example. This is a demonstration of how the public API can be used to build a simple proving service. https://github.com/risc0/risc0/pull/2113
* Added the ability to serialize Receipts using the borsh serialization crate. https://github.com/risc0/risc0/pull/2184

### 🚨 Breaking Changes

* Due to the zero-knowledge change above, receipts generated by zkVM 1.0.x cannot be verified with IDs from 1.1.x and verifiers using control IDs from 1.0.x are not compatible with 1.1.x. To avoid this control ID mismatch, users who are verifying proofs must ensure that the version of their verifier must match the version of their prover. For example, if a user is verifying proofs that come from `risc0-zvkvm` 1.1.x, they must ensure that the verifier they are using from `risc0-zkvm` version 1.1.x. If they are verifying proofs that come from `risc0-zkvm` version 1.0.x, they must ensure that the verifier is also from `risc0-zkvm` 1.1.x. Users of bonsai must ensure that their local verifier matches the version used by bonsai. For more information on why this change occurred, see the Fixes section.

## [v1.0.5 (2024-07-30)](https://github.com/risc0/risc0/releases/tag/v1.0.5)

### 🛠 Fixes

* Change the host to validate the guest buffer address if its length is non-zero. This fixes an issue that occurs when building the guest with Rust toolchain version 1.79.0.

## [v1.0.4 (2024-07-26)](https://github.com/risc0/risc0/releases/tag/v1.0.4)

### 🛠 Fixes

* Apply a workaround for LLVM compiler bug for rv32im to ensure that lower bits of addresses are preserved.
* Fix panic by remove page_size parameter from serialized MemoryImage

## [v1.0.3 (2024-07-16)](https://github.com/risc0/risc0/releases/tag/v1.0.3)

### 🛠 Fixes

* Fix client/server version compatibility.

## [v1.0.2 (2024-07-11)](https://github.com/risc0/risc0/releases/tag/v1.0.2)

### ⚡️ Features
* Improve executor performance by 2x.
* `bonsai-sdk`: enable execute-only mode. This will run the guest program but will not produce a receipt. This can be used to quickly measure the complexity of the guest program.
* `bonsai-sdk`: simplify the SDK by using the `maybe_async` crate.

### 🛠 Fixes

* Fix `no_std` starter template.
* Fix serialization of structs such as `NaiveDate` which calls into `collect_str`.

## [v1.0.1 (2024-06-04)](https://github.com/risc0/risc0/releases/tag/v1.0.1)

### 🛠 Fixes

* Fix issue with building CUDA kernels.

## [v1.0.0 (2024-06-04)](https://github.com/risc0/risc0/releases/tag/v1.0.0)

### 🔥 Prover Performance Improvements

* Witness generation has been parallelized by adding another preflight pass.
* Improved performance by minimizing data transfers when constructing merkle proofs.
* Parallelized `step_verify_bytes` function.
* Changed `eval_check` to use precomputed powers for poly_mix.

### 🛠 Fixes

* Fixed a bug with an unaligned short read.
* Commit globals in Fiat-Shamir transcript.
* Fixed an undefined behavior warning generated by rust 1.77.2 in guest.
* Addressed security vulnerabilities in the rv32im circuit.
* Fix clippy warnings in all published crates.
* Fix build issues arising from an undefined `_end` symbol.

### ⚡️ Features

* Generalized proof composition.
* Benchmarks have been improved.
* A new web app that can be used to display datasheets, prover benchmarks, application benchmarks and supported crates.
* Added the ability to compile Rust crates that bind to C code.
* Added a new `cargo risczero deploy` command to deploy ELF binaries to bonsai.
* `ProverOpts` now has a new `ReceiptKind` field. This is used to select the
minimum compression level of receipt to be generated by the `Prover` and
`ProverServer` traits. The kinds include composite (a receipt containing a
vector of segment receipts), succinct (a receipt where all segments have been
compressed into a single receipt via the lift and join recursion programs),
and compact (a snark receipt generated by compressing a succinct receipt using
a groth16 prover. This used for on-chain proving).
* A `compress` function has been added to the `Prover` trait. This allows the users to more easily change receipts to a different kind in the host.
* Rust's `alloc_zeroed` function has been optimized in the guest.
* Export `NullSegmentRef` for use by host code.
* Added a soundness error calculator.
* Bonsai SDK: added a method used to download receipts.
* Bonsai SDK: improved error messages.
* Bonsai SDK: added a new API to stop a proving session in Bonsai.

### 🚨 Breaking Changes

* Change sys_cycle_count to return a `u64` instead of u32.

* The `Prover` trait's `prove()` function now returns a `ProveInfo`. This `struct`
  contains the receipt as well as cycle and segment information gathered during
  the proof generation. The following is the definition of `ProveInfo` and
  `SessionStats` structs:

```rust
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
+   let receipt = prover.prove(env, BEVY_GUEST_ELF).unwrap().receipt;
```

## [v0.21.0 (2024-03-11)](https://github.com/risc0/risc0/releases/tag/v0.21.0)

### 🛠 Fixes

* Fix an issue where the temporary directory is not being removed when the
`Session` goes out of scope. This helps prevent the depletion of disk space.

* Verification of groth16 receipts in rust that are compatible with Bonsai

### ⚡️ Features

* Add an improved Poseidon2 hashing function that replaces Poseidon for recursive proofs.

### 🚨 Breaking Changes

* For recursive proofs, the Poseidon hash function is replaced by the Poseidon2 hash function. Users can still create receipts using the older Poseidon hash function but these receipts will not be usable by Bonsai or any proof composition or rollup use cases.

## [v0.20.1 (2024-02-01)](https://github.com/risc0/risc0/releases/tag/v0.20.1)

### 🛠 Fixes

* Revert change to `Prover::prove` to return a `SuccinctReceipt`. This prevents
  a performance regression for default use cases.

## [v0.20.0 (2024-01-29)](https://github.com/risc0/risc0/releases/tag/v0.20.0)

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
