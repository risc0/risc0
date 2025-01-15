# CHANGELOG

## Next (upcoming release)

## [v1.2.1 (2025-01-15)](https://github.com/risc0/risc0/releases/tag/v1.2.1)

### 🔥 Performance Improvements

* Implement `keccak` precompile. This offers performance improvements for any guest program that uses the `keccak` hash function, such as Ethereum block proving.
* Implement `secp256r1` (`p256`) precompile. This offers performance improvements for any guest program that performs arithmetic over the `secp256r1` curve, such as verifying TEE attestations.
* For more information about precompiles go to https://dev.risczero.com/api/zkvm/precompiles.

### ⚡️ Features

* Add `keccak` example.
* Add `p256` support to ECDSA example.
* Add `RISC0_INFO=1` to get profiling information.
* Add `used` and `free` methods to bump allocator to enable collecting memory metrics on the guest.

### Fixes

* Add `RUST_LIB_BACKTRACE` to `sys_getenv` allow-list to facilitate debugging guest code and allow the `anyhow!` macro to work without crashing the guest.
* Add `RISC0_FEATURE_bigint2` in the Docker build environment.

## [v1.2.0 (2024-12-04)](https://github.com/risc0/risc0/releases/tag/v1.2.0)

### 🔥 Performance Improvements

* Enable big integer acceleration in the rv32im circuit. The new `risc0-bigint2` crate contains code that facilitates acceleration.
* Accelerate RSA signature verification via bigint precompiles. Performance improvements vary by use case; as one example, our [JWT validator example](https://github.com/risc0/risc0/tree/main/examples/jwt-validator) went from ~15M cycles to ~166k cycles.

### ⚡️ Features

* Add support for deferred assumptions. This is used as a foundation for precompiles such as the up-coming keccak precompile.
* Add union recursion program use to aggregate receipts. API will be solidified in future revisions.
* Add experimental APIs used to accelerate keccak. This enables keccak hashes to be computed in an unconstrained environment but does not prove the soundness of the hashes themselves.
* Update guest code to use Rust toolchain version `1.81.0`.
* Change visibility of groth16 proof to facilitate development to enable writing on-chain verifiers themselves.
* Add `seal_size` method to receipt types.
* Make Bonsai Dependencies Optional under client feature flag.
* `bonsai-sdk`: added preflight journal fetching.
* Plumb `ReceiptClaim` through `SessionInfo` and client-server to facilitate local testing.
* Support wider range of client/server use cases including verification.
* `r0vm`: add `r0vm-ver-compat` feature flag to relax r0vm server version checks.
* `risc0-build`: allow guest methods binary targets to customize required-features and skip building such targets if not all required features were provided.
* Enable forwarding custom rustc flags to guest builds.
* Change `cargo risczero datasheet` to use guest code written in assembly to generate consistent cycle counts.
* `risc0-zkp`: Export `poseidon2` constants.
* `risc0-zkp`: add changes to support extended field element use by `zirgen` code generation.
* Use remark linter on website.

### Fixes

* Client/server: fix concurrent access to `TcpSocket`.
* Run `clippy` more widely on risc0 repository using all targets and address warnings and errors.
* Fix: gate `env::read_buffered()` behind the 'std' feature
* Fix missing cstdint include for cuda builds.

### 🚨 Breaking Changes

* Drop `risc0-circuit-bigint` in favor of `risc0-bigint2`.

## [v1.1.3 (2024-11-08)](https://github.com/risc0/risc0/releases/tag/v1.1.3)

### 🔥 Performance Improvements

* Add `poly_divide` kernel. This achieves proving speeds of 1.5 MHz on a 4090 GPU for proving rv32im programs.

### ⚡️ Features

* Enable environment variable to configure Bonsai poll time and reduce default.
* Client server: add an option to use redis.

### Fixes

* Fix cpp toolchain support for docker guest builds.
* Fix bugs in data sheet.

### 🚨 Breaking Changes

* Environment syscalls `sys_getenv`, `sys_argc` and `sys_argv` are disabled by
  default, with the option to enable them via a feature flag on the
  `risc0-zkvm-platform` crate. In host programs, environment variables and
  arguments are generally considered trusted. In contrast, the guest does not
  trust the host, which leads to risk that code designed for running on the
  host may result in insecure behavior when run in the guest. Disabling
  environment variables and args by default mitigates this risk.

## [v1.1.2 (2024-10-02)](https://github.com/risc0/risc0/releases/tag/v1.1.2)

### 🛠 Fixes

* Allow static mut references in specific places
* Update reqwest and downloader

## [v1.1.1 (2024-09-23)](https://github.com/risc0/risc0/releases/tag/v1.1.1)

Support wider range of client/server use cases.

## [v1.1.0 (2024-09-09)](https://github.com/risc0/risc0/releases/tag/v1.1.0)

### 🔥 Performance Improvements

* Improve GPU performance.
  For more information see https://reports.risczero.com/benchmarks.
* Speed up null builds of guest programs.

### 🛠 Fixes

* Released Rust toolchain `r0.1.79.0-1`. This toolchain fixes a crash in the
  guest that appears when enabling the heap allocator in combination with
  `thread_local!` in the zkVM guest.
* Enable support for running clippy on host-side code.
* Add linter to website
* Improve zero-knowledge property of the prover by increasing the amount of
  noise. We have used techniques described in this
  [paper](https://eprint.iacr.org/2024/1037.pdf) to strengthen the ZK property
  of the prover. See [these
  docs](https://dev.risczero.com/api/security-model#zero-knowledge-proving) for
  more information about zero knowledge and our proving system. This change
  results in a new set of control IDs. See the breaking changes section to learn
  more about this minor breaking change.
* Fix template generation for `--nostd` mode.

### ⚡️ Features

* Add the `risc0-circuit-bigint` crate, which is the basis for many upcoming
  cryptographic accelerators.
* Add examples and improve verbiage for datasheet.
* Add a `risc0_core::scope!` macro used to measure performance.
* Add blog link and use a cleaner mermaid theme for code examples on developer
  documentation website.
* Add "light builds". A new faster way to build guest programs intended for
  development only.
* Add an optional embedded allocator to the zkVM guest. By default, the zkvm
  uses an allocator that does not deallocate heap memory. The embedded allocator
  deallocates and is useful for long running guest programs.
* Add experimental support for `sys_fork`. This syscall allows the zkVM to
  execute unconstrained code. The RISC-V code executed within this system call
  will not be encoded as a part of the trace execution. This can be used to
  implement hints and advice.
* Use `stability::unstable` to mark new experimental APIs.
* Add unstable `env::read_frame()` and `env::read_framed()` which improves cycle
  counts when reading the input from the guest.
* Re-vamped rzup. The rzup utility is used to install toolchains and extensions.
  The first implementation was a simple bash script. This has been replaced by a
  more robust rust implementation.
* Enable GPU proving by default on macOS.
* Add an example that shows how the `c-kzg` crate can be run in the zkVM.
* Add an example that uses C as the guest code. This demonstrates how a user
  can use C to write an entire guest program without rust.
* Add a simple prover service example. This is a demonstration of how the
  public API can be used to build a simple proving service.
* Add the ability to serialize Receipts using the borsh serialization format.
* Add support for serialization of types such as `chronos::NaiveDate` that call
  into `collect_str`.

### 🚨 Breaking Changes

* Due to the zero-knowledge change above, receipts generated by zkVM 1.0.x
  cannot be verified with IDs from 1.1.x and verifiers using control IDs from
  1.0.x are not compatible with 1.1.x. To avoid this control ID mismatch, users
  who are verifying proofs must ensure that the version of their verifier must
  match the version of their prover. For example, if a user is verifying proofs
  that come from `risc0-zvkvm` 1.1.x, they must ensure that the verifier they
  are using from `risc0-zkvm` version 1.1.x. If they are verifying proofs that
  come from `risc0-zkvm` version 1.0.x, they must ensure that the verifier is
  also from `risc0-zkvm` 1.1.x. Users of bonsai must ensure that their local
  verifier matches the version used by bonsai. For more information on why this
  change occurred, see the Fixes section.

## [v1.0.5 (2024-07-30)](https://github.com/risc0/risc0/releases/tag/v1.0.5)

### 🛠 Fixes

* Change the host to validate the guest buffer address if its length is
  non-zero. This fixes an issue that occurs when building the guest with Rust
  toolchain version 1.79.0.

## [v1.0.4 (2024-07-26)](https://github.com/risc0/risc0/releases/tag/v1.0.4)

### 🛠 Fixes

* Apply a workaround for LLVM compiler bug for rv32im to ensure that lower bits
  of addresses are preserved.
* Fix panic by remove page_size parameter from serialized MemoryImage

## [v1.0.3 (2024-07-16)](https://github.com/risc0/risc0/releases/tag/v1.0.3)

### 🛠 Fixes

* Fix client/server version compatibility.

## [v1.0.2 (2024-07-11)](https://github.com/risc0/risc0/releases/tag/v1.0.2)

### ⚡️ Features
* Improve executor performance by 2x.
* `bonsai-sdk`: enable execute-only mode. This will run the guest program but
  will not produce a receipt. This can be used to quickly measure the complexity
  of the guest program.
* `bonsai-sdk`: simplify the SDK by using the `maybe_async` crate.

### 🛠 Fixes

* Fix `no_std` starter template.
* Fix serialization of structs such as `NaiveDate` which calls into
  `collect_str`.

## [v1.0.1 (2024-06-04)](https://github.com/risc0/risc0/releases/tag/v1.0.1)

### 🛠 Fixes

* Fix issue with building CUDA kernels.

## [v1.0.0 (2024-06-04)](https://github.com/risc0/risc0/releases/tag/v1.0.0)

### 🔥 Prover Performance Improvements

* Witness generation has been parallelized by adding another preflight pass.
* Improved performance by minimizing data transfers when constructing merkle
  proofs.
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
* A new web app that can be used to display datasheets, prover benchmarks,
  application benchmarks and supported crates.
* Added the ability to compile Rust crates that bind to C code.
* Added a new `cargo risczero deploy` command to deploy ELF binaries to bonsai.
* `ProverOpts` now has a new `ReceiptKind` field. This is used to select the
minimum compression level of receipt to be generated by the `Prover` and
`ProverServer` traits. The kinds include composite (a receipt containing a
vector of segment receipts), succinct (a receipt where all segments have been
compressed into a single receipt via the lift and join recursion programs),
and compact (a snark receipt generated by compressing a succinct receipt using
a groth16 prover. This used for on-chain proving).
* A `compress` function has been added to the `Prover` trait. This allows the
  users to more easily change receipts to a different kind in the host.
* Rust's `alloc_zeroed` function has been optimized in the guest.
* Export `NullSegmentRef` for use by host code.
* Added a soundness error calculator.
* Bonsai SDK: added a method used to download receipts.
* Bonsai SDK: improved error messages.
* Bonsai SDK: added a new API to stop a proving session in Bonsai.

### 🚨 Breaking Changes

* Change sys_cycle_count to return a `u64` instead of u32.

* The `Prover` trait's `prove()` function now returns a `ProveInfo`. This
  `struct` contains the receipt as well as cycle and segment information
  gathered during the proof generation. The following is the definition of
  `ProveInfo` and `SessionStats` structs:

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

For those upgrading from v0.21.0, the following code change is necessary on the
host side to retrieve the receipt.

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

* Add an improved Poseidon2 hashing function that replaces Poseidon for
  recursive proofs.

### 🚨 Breaking Changes

* For recursive proofs, the Poseidon hash function is replaced by the Poseidon2
  hash function. Users can still create receipts using the older Poseidon hash
  function but these receipts will not be usable by Bonsai or any proof
  composition or rollup use cases.

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
