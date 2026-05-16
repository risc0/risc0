# Metal Optimization Progress

This document tracks work toward the best local Apple Silicon proving setup.
The primary target is an untrusted local prover in the normal cryptographic
sense: the verifier does not trust the prover. When we say "no trusted setup"
below, we mean staying in the STARK receipt path and not depending on Groth16.

Current checkout: `upstream/main` at `35ed22a1ba1c0025b990befd0c9d7ec4f39f3840`.
Local machine used for validation: Apple M5 Max.
Current Apple toolchain used for Metal validation: Xcode 26.5 build `17F42`
with Metal Toolchain `17F42` installed via `xcodebuild -downloadComponent
MetalToolchain`; `xcrun --sdk macosx metal -v` reports Apple metal version
`32023.883`.
Only `/Applications/Xcode.app` is installed locally, so comparing against an
older Apple Metal Toolchain requires CI or a second machine.

## Current Recommendation

Use the M3 rv32im segment prover on Apple Silicon with Metal enabled by target
selection. On this branch, rv32im eval-check also uses Metal by default after
compiling generated `eval_check_*.metal` files with `-fno-inline`.

Use this env var only to force the old CPU eval-check safety fallback:

`RISC0_RV32IM_METAL_EVAL_CHECK=0`

The other rv32im Metal kernels keep the normal optimization pipeline. Set
`RISC0_RV32IM_METAL_INLINE_EVAL_CHECK=1` when comparing against or reproducing
the original fully optimized eval-check failure mode.

On the M5 Max this passes the current serial rv32im suite with eval-check CPU
verification, the non-serial rv32im harness, and 1M-row composite plus 64K-row
succinct datasheet runs. It is much faster than the CPU-eval-check safety
fallback on the filtered `fib prove/poseidon2` benchmark. This still needs
broader cross-machine and cross-toolchain validation before treating it as
upstream-production evidence.

For the best local proving throughput, start with `ProverOpts::fast()` or
`ProverOpts::composite()`. This produces a composite STARK receipt: fastest,
transparent, no trusted setup, but proof size grows with segment count.

For the best untrusted constant-size local receipt, use `ProverOpts::succinct()`.
This keeps the proof in the STARK/recursion path and avoids Groth16 trusted
setup, but it pays the recursion cost for `lift`, `join`, and `resolve`.

Do not use `ProverOpts::groth16()` for the primary "no trusted setup" goal.
Groth16 receipts are useful for very small proofs and on-chain verification, but
they depend on the STARK-to-SNARK trusted setup and are currently documented as
unsupported on Apple Silicon.

## Prover Selection Path

The public/default local prover path is:

1. `default_prover()` / `get_prover_server(opts)`.
2. If dev mode is disabled, `get_prover_server` constructs `ProverImpl`.
3. `ProverImpl::prove_with_ctx` executes the ELF into a `Session`.
4. `ProverImpl::prove_session` proves each segment with `prove_segment`.
5. `prove_segment` calls `segment_preflight`, then `prove_preflight`.
6. `prove_preflight` calls `risc0_circuit_rv32im::prove::segment_prover(po2)`.
7. On macOS/aarch64, `segment_prover` selects `ProverContext::new_metal(po2)`.

The M3 choice is also baked into execution. `ExecutorImpl::circuit_version()`
returns `RV32IM_M3_CIRCUIT_VERSION`, and the rv32im circuit defines that version
as `3`. So the "M3 engine" is not a separate receipt kind; it is the current
rv32im segment proving circuit used underneath composite/succinct/Groth16.

Receipt kind controls what happens after segment proofs:

- `Composite`: stop after segment receipts and assumption receipts are assembled.
- `Succinct`: run recursion programs (`lift`, `join`, `resolve`) to compress the
  composite receipt into a constant-size STARK receipt.
- `Groth16`: run `identity_p254`, then `risc0_groth16::prove::shrink_wrap`.

## Keccak Path

Keccak is a special accelerator circuit, not ordinary rv32im guest execution.
Guest code can request Keccak work through the Keccak syscall path. The host then
builds a `ProveKeccakRequest` and the prover resolves it as an assumption.

The local host path is:

1. `ProverImpl::prove_session` iterates over `session.pending_keccaks`.
2. Each request calls `prove_keccak`.
3. `prove_keccak` calls `risc0_circuit_keccak::prove::keccak_prover()`.
4. The Keccak seal is verified and then lifted with `prove_zkr` into a succinct
   receipt over an `Unknown` claim.
5. Keccak receipts are inserted into a union tree and later resolved against the
   main session receipt.

Current Metal status: Keccak has CUDA and CPU prover branches, but the Metal
branch is still commented out. On Apple Silicon, Keccak proving falls back to the
CPU circuit path today. This is a clear gap for workloads that use the Keccak
precompile heavily.

## Groth16 / Trusted Setup

Groth16 is the final STARK-to-SNARK wrapping stage. It produces the smallest
receipt and is the usual route for Ethereum-style verification, but it is not a
transparent proving path.

The project docs describe a trusted setup ceremony for the Groth16 prover and
verifier. The security model page also notes that the STARK-to-SNARK translator
uses Groth16 over BN254, so it depends on elliptic curve cryptography and the
setup ceremony assumptions.

For this optimization track, Groth16 is useful context but not the main target.
The main target is:

1. Fast local composite STARK proving on M3 + Metal.
2. Stable local succinct STARK proving on M3 + Metal recursion.
3. Optional Groth16 only after the transparent/STARK local path is solid.

## Zirgen Role

Zirgen is the circuit DSL/code generator. In the current codebase, it matters for
Metal because generated circuit kernels include Metal variants for recursion
work such as `eval_check`, `step_compute_accum`, and `step_verify_accum`.

The practical optimization boundary is:

- RISC Zero decides when a prover uses CPU, CUDA, or Metal.
- Zirgen decides what generated circuit code exists for those targets.
- `risc0-build-kernel` compiles Metal source into `.metallib` artifacts.

For M3 rv32im, main already has a hand-integrated Metal HAL and generated
per-`po2` kernels for `data_witgen`, `accum_witgen`, and `eval_check`.

The RISC0 checkout pins Bazel `@zirgen` to
`df6fb9dda1c20209058d6ee90a8912351b741081`, which is current
`risc0/zirgen` `main` as of this investigation. So the external Zirgen pin is
not stale. The recent Zirgen `main` commits checked here are out-of-tree build
support, V3/PoVW predicate work, and a CUDA `poly_mix` codegen change; they do
not change the generic Metal `eval_check` template. The checked-in rv32im M3
`eval_check` implementation is still from the M3 circuit integration lineage,
though: it entered with `cbcc6f79e` (`Initial commit for rv32im-m3 circuit`, PR
#3430), was moved into the merged rv32im crates by `ccc793fc9` (PR #3600), and
has not had a substantive `eval_check` code-shape change since. The generic
Zirgen Metal `eval_check.tmpl.metal` template dates back to the initial Zirgen
import and is not the exact code path used by the rv32im M3 C++/Metal HAL.

Historical RISC Zero issue #999 is relevant context: old Metal support was
deprecated because `eval_check` codegen could exceed Apple temporary-register
limits, and the issue explicitly pointed at needing more structured Zirgen
output. The current M5 Max failure is different in symptom (`Poly check failed`
rather than compile-time register exhaustion), but the successful `-O0`
experiment makes generated eval-check code shape and Metal optimizer pressure a
leading hypothesis.

## Validation Snapshot

Metal-focused validation on the M5 Max:

- After installing the Xcode 26.5 Metal Toolchain and forcing the rv32im Metal
  kernels to rebuild, serial rv32im Metal tests are not reliable:
  `cargo test -p risc0-circuit-rv32im --features prove prove::tests --release
  -- --nocapture --test-threads=1` failed with `Poly check failed`. The failing
  test moves between runs; observed failures include `addi`, `divu`, `rem`,
  `lh`, `lbu`, `lw`, `or`, and `sub`. Treat rv32im Metal as
  correctness-suspect on this machine/toolchain.
- The existing C++ `DualHal` CPU+Metal checker narrows the first divergent
  rv32im operation to `evalCheck`: with
  `RISC0_RV32IM_METAL_COMPARE_CPU=1 RISC0_RV32IM_METAL_EVAL_CHECK=1`, a serial
  suite run failed in `beq` with `DualHal matrix verify mismatch after
  evalCheck`. A later serial run failed in `sltiu` after `evalCheck` at row
  8288 col 0. Running only `prove::tests::sltiu` can also fail after
  `evalCheck`, but not every run; one observed loop failed after 19 repeats.
  Use this as the current compact repro shape:
  `for i in {1..20}; do RISC0_RV32IM_METAL_COMPARE_CPU=1
  RISC0_RV32IM_METAL_EVAL_CHECK=1 cargo test -p risc0-circuit-rv32im --features
  prove prove::tests::sltiu --release -- --nocapture --test-threads=1 || exit
  $?; done`.
- Bypassing only the Metal `eval_check_metal_*` kernels restores correctness.
  The branch now keeps the rest of the Metal HAL active but computes the rv32im
  validity polynomial on CPU by default:
  `cargo test -p risc0-circuit-rv32im --features prove prove::tests --release
  -- --nocapture --test-threads=1` passed 46 tests, and the default parallel
  run passed 46 tests. Set
  `RISC0_RV32IM_METAL_EVAL_CHECK=1` to force the full Metal eval-check kernel
  for diagnosis and benchmarking; the same serial suite failed in that mode
  with `jalr`, `mulhsu`, and `or` hitting `Poly check failed`.
- `cargo test -p risc0-zkp --features prove hal::metal --release -- --nocapture`
  passed: 19 tests, including after the Xcode 26.5 Metal Toolchain install.
- `cargo test -p risc0-circuit-recursion --features prove prove::hal::metal::tests::eval_check --release -- --ignored --nocapture`
  passed: 1 test, including after the Xcode 26.5 Metal Toolchain install.
- `examples/target/release/hello-world` with `RISC0_PROVER=local` completed a
  proof in about 0.5s warm with the default CPU eval-check safety path. A
  forced full-Metal eval-check run of the same binary was also about 0.5s, so
  this tiny example is not a useful performance discriminator.
- Eager `newComputePipelineState` over every function in the rv32im `.metallib`
  can stall badly with this toolchain when it compiles unused kernels such as
  higher-`po2` `eval_check` variants. Lazy pipeline creation avoids that startup
  problem, but it does not fix the `Poly check failed` correctness failure.
- Adding missing `device`-qualified compound assignment overloads for Metal
  `Fp` / `FpExt` was tested as a compiler-sensitivity hypothesis. It rebuilt and
  initially passed focused `sltiu`, but the 20-run loop still failed after
  `evalCheck`, so that change was not kept.
- Forcing `eval_check_metal_*` to dispatch one thread per threadgroup is also
  only a partial diagnostic. With that local experiment, the 20-run `sltiu`
  dual-HAL loop and full serial dual-HAL rv32im suite passed, which points at
  threadgroup/compiler scheduling pressure. But the non-dual full-Metal serial
  suite still failed with `Poly check failed` in `remu` and `srai`, so the
  one-threadgroup change is not a correctness fix and was not kept.
- Adding an immediate opt-in CPU readback of the eval-check output after the
  Metal dispatch also did not stabilize non-dual full Metal. The serial suite
  still failed with `Poly check failed` in `bltu`, so this is not just a missing
  post-dispatch readback.
- Forcing a command-buffer sync after every Metal dispatch also did not
  stabilize non-dual full Metal. The serial suite still failed with `Poly check
  failed` in `div`, `divu`, and `lh`, so command-buffer batching is unlikely to
  be the only root cause.
- The branch now has a narrower opt-in eval-check verifier:
  `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1`. It runs the Metal eval-check
  kernel, computes the same check buffer with `evalCheckCpu` from the same
  pinned inputs, and reports the first mismatch. With
  `RISC0_RV32IM_METAL_EVAL_CHECK=1`, the 20-run focused `sltiu` loop failed at
  row 5568 col 0 with `1869206222 vs 201529409`. This confirms the bug is in
  the Metal eval-check output itself, not only in later proof verification.
- Compiling the rv32im Metal kernels with `-O0` is a strong diagnostic. With a
  temporary hardcoded `-O0`, the focused direct verifier loop
  (`RISC0_RV32IM_METAL_EVAL_CHECK=1
  RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1 ... prove::tests::sltiu`) passed
  20/20, and the full serial rv32im prove suite passed 46/46 under forced Metal
  eval-check plus CPU verification. After wiring this as
  `RISC0_RV32IM_METAL_KERNEL_O0=1`, the same full serial rv32im suite passed
  46/46 with `RISC0_RV32IM_METAL_EVAL_CHECK=1` and
  `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1`. This strongly implicates
  optimized Metal compilation or optimization-sensitive generated eval-check
  code shape, but it is not a performance fix.
- `-fno-inline-functions` is a narrower and much better mitigation candidate
  than `-O0`. With full Metal eval-check forced and CPU verification enabled,
  the focused `sltiu` loop passed 20/20 and the full serial rv32im prove suite
  passed 46/46 when the flag was appended globally with
  `RISC0_RV32IM_METAL_APPEND_FLAGS`. The same filtered suite also passed 46/46
  without `--test-threads=1`. This points at inlining pressure in the generated
  `verifyCircuit` / eval-check path as the most actionable current hypothesis.
- The branch first applied `-fno-inline-functions` only to generated
  `eval_check_*.metal` files by default. With no global append flags, forced
  Metal eval-check plus CPU verification passed the focused `sltiu` loop 20/20
  and the full rv32im prove suite 46/46. This preserves the original repro path
  behind `RISC0_RV32IM_METAL_INLINE_EVAL_CHECK=1`: a focused inline `sltiu`
  loop passed 25/25, but the inline full rv32im prove suite failed in `sltiu`
  with a direct eval-check verifier mismatch at row 31840 col 0.
- The scoped default was then narrowed from `-fno-inline-functions` to
  `-fno-inline` on generated `eval_check_*.metal` files. Apple Metal accepts
  `-fno-inline`, but ignores narrower candidates such as
  `-fno-inline-functions-called-once` and `-fno-inline-small-functions`. With
  scoped `-fno-inline`, the focused `sltiu` eval-check verifier passed and the
  full rv32im prove suite with `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1`
  passed 46/46 with one ignored regression test.
- The narrowed `-fno-inline` default also passed a three-run full-suite stress
  loop with `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1`; each run passed 46/46
  with the ignored Metal regression test skipped.
- Full Metal eval-check is now the runtime default in this branch. The default
  full rv32im prove suite passed 46/46 with one ignored Metal regression test,
  and a default full-suite run with
  `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1` also passed 46/46. The old CPU
  eval-check fallback remains available with `RISC0_RV32IM_METAL_EVAL_CHECK=0`;
  a focused `sltiu` fallback sanity run passed with that env set.
- Higher-level zkVM validation also passes with the default full-Metal
  eval-check path:
  - `cargo test -p risc0-zkvm --features prove
    host::server::exec::tests::cpp_test -- --nocapture` passed.
  - `RISC0_PROVER=local cargo test --manifest-path examples/Cargo.toml -p
    hello-world --features prove test_hello_world -- --nocapture` passed and
    produced a local proof for the hello-world multiply example.
  - `cargo test -p risc0-zkvm --features prove
    host::server::prove::tests::basic -- --nocapture` passed, producing a
    succinct receipt for the `DoNothing` multi-test guest.
- Before flipping the runtime default, the scoped full-Metal path passed five
  consecutive non-serial full-suite verifier runs with
  `RISC0_RV32IM_METAL_EVAL_CHECK=1
  RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1`: each run passed 46/46, with the
  ignored Metal regression test skipped unless `--ignored` is provided.
- The branch also has an ignored focused regression test for the scoped
  eval-check mitigation:
  `RISC0_RV32IM_METAL_EVAL_CHECK=1
  RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1 cargo test -p
  risc0-circuit-rv32im --features prove
  prove::tests::metal_eval_check_sltiu_repeated --release -- --ignored
  --nocapture --test-threads=1`.
- The guest `risc0-zkvm-methods-cpp-crates` `blst_*` link failure was caused by
  the guest C compiler being set to the RISC-V GCC while `AR` was left unset on
  macOS. The `cc` crate fell back to `/usr/bin/ar`, producing a 96-byte empty
  `libblst.a`; the adjacent RISC-V object did contain the missing symbols.
  Setting the target-specific RISC-V archiver fixes the build. Validation:
  `cargo test -p risc0-zkvm --features prove --no-run` now succeeds, and
  `cargo test -p risc0-zkvm --features prove host::server::exec::tests::cpp_test
  -- --nocapture` passes. Docker guest-build validation also passes:
  `RISC0_USE_DOCKER=1 cargo test -p risc0-zkvm --features prove,docker
  host::server::exec::tests::cpp_test -- --nocapture` rebuilt the guest Docker
  artifacts and executed the `blst` guest successfully.
- The small Metal-enabled release datasheet matrix is now runnable with
  `--max-po2 16`:
  - `execute`: 28.8ms for 2.7M instructions.
  - `composite`: 897.8ms for 16K rows, 4.56s for 64K rows.
  - `lift`: 731.5ms for 256K recursion rows.
  - `join`: 923.6ms for 256K recursion rows.
  - `succinct`: 4.09s for 64K rows.
- `cargo bench -p risc0-zkvm --features prove,metal --bench fib execute` now
  runs; one filtered run averaged about 73MHz. The full `fib` benchmark suite is
  still not part of the default quick gate because each selected hotbench entry
  runs for roughly 10s plus setup.
- `cargo bench -p risc0-zkvm --features prove,metal --bench fib
  prove/poseidon2` now runs as a segment-only benchmark. On the current safety
  path it completed one timed iteration in 28.31s, about 18.1K rows/sec. This is
  intentionally recorded as the CPU-eval-check safety-path baseline, not a
  full-Metal result.
- Re-running the same benchmark after the runtime default flip with
  `RISC0_RV32IM_METAL_EVAL_CHECK=0` confirmed the old CPU eval-check fallback is
  still much slower than the default full-Metal path: 30.68s, about 16.7K
  rows/sec.
- The same filtered `fib prove/poseidon2` benchmark with
  `RISC0_RV32IM_METAL_KERNEL_O0=1 RISC0_RV32IM_METAL_EVAL_CHECK=1` completed in
  48.05s, about 10.7K rows/sec. This is slower than the CPU-eval-check safety
  path, so `-O0` should remain diagnostic only.
- With `RISC0_RV32IM_METAL_APPEND_FLAGS=-fno-inline-functions
  RISC0_RV32IM_METAL_EVAL_CHECK=1`, the filtered `fib prove/poseidon2`
  benchmark completed in 15.94s, about 32.1K rows/sec. This is faster than both
  the CPU-eval-check safety path and the `-O0` diagnostic path.
- With scoped default no-inline on only generated `eval_check_*.metal` files and
  `RISC0_RV32IM_METAL_EVAL_CHECK=1`, the same filtered `fib prove/poseidon2`
  benchmark completed in 4.89s to 6.16s, about 83.1K to 104.8K rows/sec. This
  is the best pre-default-flip segment-proving measurement.
- After flipping full Metal eval-check on by default, the same filtered
  benchmark without any rv32im eval-check env flags passed with a 4.73s to 4.84s
  range, about 105.8K to 108.3K rows/sec. This is the best current default
  segment-proving measurement.
- After narrowing the scoped eval-check flag to `-fno-inline`, the default
  no-env benchmark stayed in the same range: 4.77s to 4.93s, about 103.9K to
  107.4K rows/sec.
- A source-level Metal `__attribute__((noinline))` experiment on
  `computeRow<po2>` compiled and passed the focused default
  `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1 ... prove::tests::sltiu` sanity
  test, but the single proof took 63.38s. That is not a viable replacement for
  the scoped compiler-flag mitigation.
- Apple Metal accepts LLVM inline-threshold flags such as
  `-mllvm -inline-threshold=10`. With the scoped default noinline mitigation
  disabled, that threshold passed the same focused direct verifier test, but the
  single proof took 115.90s. That is also not a viable replacement for scoped
  `-fno-inline`.
- The same `-fno-inline-functions` full-Metal eval-check candidate passed
  `datasheet --max-po2 16 composite`: 658.9ms for 16K rows and 2.04s for 64K
  rows. This improves on the current safety-path baseline of 897.8ms and 4.56s,
  so the candidate is meaningful beyond the isolated `fib` segment benchmark.
- The candidate also passed `datasheet --max-po2 18 composite`: 658.7ms for 16K
  rows, 1.85s for 64K rows, 5.96s for 128K rows, and 9.04s for 256K rows. The
  larger 256K-row case reached about 28.3K rows/sec.
- The same candidate passed `datasheet --max-po2 18 succinct`: 2.57s for the
  64K-row succinct case, about 24.9K rows/sec, with about 930MB max RAM and a
  217.4KB seal.
- A larger `datasheet --max-po2 20 composite` run passed with forced full Metal
  eval-check: 767ms for 16K rows, 2.52s for 64K rows, 4.52s for 128K rows,
  8.57s for 256K rows, 16.88s for 512K rows, and 37.47s for 1M rows. The 1M-row
  case reached about 27.3K rows/sec. This was still using the global append flag
  and is now a historical lower bound.
- With the scoped eval-check-only no-inline default, the repeated
  `datasheet --max-po2 20 composite` run passed and reached 288.7ms for 16K
  rows, 783.8ms for 64K rows, 1.29s for 128K rows, 2.48s for 256K rows, 4.85s
  for 512K rows, and 9.68s for 1M rows. The 1M-row case reached about 105.7K
  rows/sec.
- After flipping full Metal eval-check on by default, the same
  `datasheet --max-po2 20 composite` run passed without any rv32im eval-check
  env flags and reached 286.9ms for 16K rows, 727.3ms for 64K rows, 1.36s for
  128K rows, 2.46s for 256K rows, 4.93s for 512K rows, and 9.84s for 1M rows.
  The 1M-row case reached about 104.1K rows/sec.
- With the scoped eval-check-only no-inline default, `datasheet --max-po2 18
  succinct` passed: 1.47s for the 64K-row succinct case, about 43.5K rows/sec,
  with about 930MB max RAM and a 217.4KB seal.
- After flipping full Metal eval-check on by default, the same
  `datasheet --max-po2 18 succinct` run passed without any rv32im eval-check env
  flags: 1.49s for the 64K-row succinct case, about 43K rows/sec, with about
  930MB max RAM and a 217.4KB seal.
- `cargo run --release -p risc0-circuit-keccak --features prove --example
  keccak -- --po2 14 --count 1` completed in 1.930s, about 41.975 keccak/sec.
  Keccak Metal is still disabled in `risc0-circuit-keccak`, so this is a CPU
  fallback baseline and not evidence of Metal Keccak coverage.
- Higher-level Keccak syscall/assumption proving also passes on the current
  default M3 + Metal rv32im path, while the Keccak accelerator proof itself
  still uses the CPU Keccak circuit path:
  - `cargo test -p risc0-zkvm --features prove
    host::server::prove::tests::keccak::basic -- --nocapture` passed both
    built-in `po2=16` and `po2=17` cases, including non-empty assumption
    receipts and receipt verification.
  - `cargo test --manifest-path examples/keccak/Cargo.toml --features prove
    hash_abc -- --nocapture` passed the public tiny-keccak accelerator example.
- The `datasheet composite` harness had a sparse-`po2` bug: it used `.take(...)`
  over a table that intentionally omits too-small powers of two, so `--max-po2
  16` could still run `po2=17` and panic. The harness now filters by the actual
  `po2` key.

## Metal Binding Status

There are two separate Metal binding stacks in the current tree:

- `rv32im-sys` uses C++ through Apple's `metal-cpp` headers. The pinned bundle is
  `metal-cpp_macOS13.3_iOS16.4.zip`.
- `risc0-zkp` and `risc0-circuit-recursion` use the Rust `metal` crate from the
  workspace dependency `metal = "0.29"`.

The Rust `metal` crate is deprecated upstream because it depends on the older
`objc` ecosystem. That is a real maintenance risk for the Rust ZKP and recursion
Metal HALs, but it is not the direct rv32im P0 correctness path. The rv32im
failure reproduces in the C++ Metal-cpp HAL.

Apple's Metal-cpp download page currently publishes `metal-cpp_26.4.zip` as the
latest observed bundle; a guessed `metal-cpp_26.5.zip` URL did not return a ZIP.
A trial local bump to `metal-cpp_26.4.zip` was not sufficient to make rv32im
Metal reliable, and reverting to the older pinned bundle did not restore serial
rv32im correctness after rebuilding kernels with the Xcode 26.5 Metal Toolchain.
This points more strongly at generated Metal kernel/compiler/runtime behavior
than at stale C++ header bindings alone.

## Work Plan

### P0: Make The Current M3 Metal Path Trustworthy

- Reproduce and isolate the serial rv32im `Poly check failed` failure with the
  Xcode 26.5 Metal Toolchain. This is now a correctness issue, not just a
  parallel-test flake. Current evidence points specifically at the generated
  `eval_check_metal_*` kernels or the Metal compiler/runtime handling of the
  generated `EvalCheckReg<po2>` access pattern.
- Keep the `RISC0_RV32IM_METAL_COMPARE_CPU=1` dual-HAL diagnostic available for
  CPU/Metal operation-level mismatch localization. Use it together with
  `RISC0_RV32IM_METAL_EVAL_CHECK=1` when specifically investigating the unsafe
  full-Metal eval-check path.
- Use `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1` for lower-overhead direct
  eval-check mismatch localization before falling back to full DualHal runs.
- Use `RISC0_RV32IM_METAL_KERNEL_O0=1` as the current strongest compiler/codegen
  diagnostic. It should not become the default without performance measurement,
  but it is the best available evidence that optimized Metal compilation is
  mishandling the generated rv32im eval-check shape. Initial measurement shows
  the `-O0` full-Metal path is slower than the CPU-eval-check safety path.
- Use `RISC0_RV32IM_METAL_APPEND_FLAGS` for targeted compiler-flag experiments.
  The first strong candidate was `-fno-inline-functions`, but the current
  narrower default is `-fno-inline` applied only to generated
  `eval_check_*.metal` files. Full Metal eval-check is now the runtime default
  in this branch. Keep stressing this scoped default with longer proof loops and
  larger real workloads before treating it as upstream-production evidence.
- Investigate a Zirgen/M3 code-shape fix for `eval_check` rather than treating
  Metal bindings alone as the root issue. Promising directions are reducing
  inlining/register pressure in `verifyCircuit`, avoiding the giant
  `EvalCheckReg<po2>` reinterpret-cast access pattern, or splitting the validity
  polynomial into smaller Metal functions/kernels.
- Keep benchmarking the default full-Metal eval-check path against the CPU
  eval-check safety fallback. The branch can force the fallback with
  `RISC0_RV32IM_METAL_EVAL_CHECK=0`.
- Keep the ignored `metal_eval_check_sltiu_repeated` test as the focused
  regression command for the scoped eval-check mitigation. Broaden it only if a
  smaller deterministic repro is found for the original inline failure.
- Keep the `risc0-zkvm-methods-cpp-crates` `blst_*` guest link fix covered in
  both native and Docker guest builds. The current fix sets
  `AR_riscv32im_risc0_zkvm_elf` beside the RISC-V guest compiler, and the
  focused Docker `cpp_test` path now passes.
- Check whether the pinned Metal-cpp header bundle is stale in a way that
  affects current Apple Silicon proving. `rv32im-sys` currently downloads
  `metal-cpp_macOS13.3_iOS16.4.zip`; Apple now publishes newer bundles such as
  `metal-cpp_26.4.zip`, whose README mentions bugfixing and other improvements.
  A first trial suggests this is not the root cause. Keep the check open only as
  a binding-health task, not as the leading correctness hypothesis.
- Do not treat the Rust `metal = "0.29"` dependency as a normal bump target.
  Upstream `metal-rs` is deprecated and recommends `objc2` / `objc2-metal` for
  new development. That dependency still matters for the Rust ZKP and recursion
  Metal HALs, but replacing it is a migration task rather than a quick P0
  correctness fix for rv32im's C++ Metal-cpp path.
- Compare `.metallib` output and runtime behavior across Apple Metal Toolchain
  versions if possible. A CI Apple Silicon runner passing with a different Xcode
  or Metal Toolchain would be a strong signal that this is toolchain-sensitive.
  This machine only has Xcode 26.5 build `17F42` installed, so this comparison
  is not locally actionable without installing another Xcode or using CI.
- Establish a stable benchmark matrix:
  - warm `hello-world` proof: present, but too small to distinguish safe
    CPU-eval-check and forced full-Metal eval-check.
  - small Metal-enabled `datasheet execute`, `composite`, `lift`, `join`, and
    `succinct`: present at `--max-po2 16`; the default full-Metal eval-check
    path also has `succinct` coverage at `--max-po2 18` and `composite`
    coverage at `--max-po2 20`.
  - filtered `fib execute`: present.
  - rv32im segment-only benchmark: present through filtered `fib
    prove/poseidon2`; the default full-Metal eval-check path is now the best
    measured segment-proving configuration on this branch.
  - Keccak-heavy workload: CPU fallback baseline and higher-level syscall proof
    coverage present; Metal Keccak remains disabled.

### P0 Exit Audit

Current status: not complete for upstream-production confidence, but the branch
has a usable local M5 Max default path.

Prompt-to-artifact checklist:

- Branch and commits: present. Work is on `metal-p0-m5-validation` with focused
  code and documentation commits.
- Living progress document: present in this file. It records prover selection,
  Keccak, Groth16/trusted setup, Zirgen, Metal bindings, validation results, and
  remaining work.
- M3 rv32im Metal eval-check default: present. `rv32im-sys` applies scoped
  `-fno-inline` only to generated `eval_check_*.metal` files, and the Metal HAL
  uses eval-check on Metal by default unless `RISC0_RV32IM_METAL_EVAL_CHECK=0`
  is set.
- Unsafe original repro path: present. `RISC0_RV32IM_METAL_INLINE_EVAL_CHECK=1`
  removes the scoped noinline mitigation, and prior inline full-suite testing
  reproduced a direct eval-check mismatch.
- Direct correctness diagnostic: present.
  `RISC0_RV32IM_METAL_VERIFY_EVAL_CHECK_CPU=1` compares Metal eval-check output
  against CPU eval-check output from the same inputs.
- Focused regression: present as ignored test
  `prove::tests::metal_eval_check_sltiu_repeated`.
- Native and Docker guest C/C++ archiver fix: present. Both native
  `cpp_test`/`--no-run` and Docker `RISC0_USE_DOCKER=1 ... cpp_test` passed.
- Benchmark matrix: present for default segment proving, CPU eval-check
  fallback, composite up to 1M rows, succinct at 64K rows, Keccak CPU fallback,
  and Keccak syscall/assumption proof coverage.
- M5 Max and modern Apple toolchain context: present. Validation records Xcode
  26.5 build `17F42`, Metal `32023.883`, and that no alternate Xcode is locally
  installed.
- Zirgen freshness check: present. The local RISC0 pin matches current
  `risc0/zirgen` `main`; recent Zirgen work does not contain a Metal eval-check
  fix for this path.
- Metal binding check: present. Newer Metal-cpp headers did not fix correctness,
  and the deprecated Rust `metal` crate is tracked as a separate maintenance
  risk rather than the rv32im P0 root cause.

Remaining gaps before marking P0 complete:

- Cross-machine or cross-toolchain validation is still missing. This machine has
  only Xcode 26.5, so the branch needs CI or another Apple Silicon host to
  separate an M5 Max/Metal Toolchain sensitivity from a general Metal issue.
- The mitigation is still a compiler-flag workaround, not a real Zirgen/M3
  code-shape fix. Source-level noinline on `computeRow<po2>` was rejected as too
  slow; a better split of `verifyCircuit`/validity-polynomial code is still open.
- The default path has strong local smoke, benchmark, short repeat-loop, and
  Keccak example coverage, but not a long-duration stress run or a broad
  real-application workload beyond the current datasheet/examples/zkVM tests.
- Keccak Metal remains disabled. This is outside rv32im eval-check correctness,
  but it is still a major gap for best local proving on Keccak-heavy workloads.

### P1: Optimize Transparent Local Proving

- Treat `ProverOpts::composite()` as the throughput baseline.
- Treat `ProverOpts::succinct()` as the constant-size STARK target.
- Profile M3 Metal segment proving for:
  - preflight time
  - GPU kernel time
  - command buffer and pipeline overhead
  - memory traffic and shared buffer behavior
- Profile recursion Metal separately; its witness generation currently still
  uses CPU witgen in the Metal circuit HAL.

### P2: Fill Metal Coverage Gaps

- Implement or restore Keccak Metal proving.
- Decide whether recursion CPU witgen is acceptable or should become a Metal
  target.
- Plan a Rust Metal HAL binding migration from the deprecated `metal` crate to
  `objc2-metal`, `objc2-foundation`, or a narrow local ObjC shim. This should be
  done behind an adapter layer and validated with the existing `risc0-zkp` and
  recursion Metal tests before touching rv32im.
- Keep Groth16 out of the primary path unless the product need is on-chain proof
  size rather than transparent local proving.

### P3: Evaluate Metal 4 Selectively

Metal 4 should be treated as a follow-up optimization, not the first milestone.
Likely useful areas are command submission, pipeline caching, compilation APIs,
and argument-table style binding. It is unlikely to make the field arithmetic
itself dramatically faster without deeper kernel/layout changes.

## Open Questions

- Is the rv32im parallel failure a Metal HAL command-buffer/resource lifetime
  issue, a generated-kernel/toolchain issue, a `gpu_guard` coverage issue, or a
  test harness artifact? The current serial failures make a pure parallelism
  explanation unlikely, and dual-HAL evidence currently points at `evalCheck`.
- Is the generated `EvalCheckReg<po2>` pointer/array pattern miscompiled by the
  Xcode 26.5 Metal Toolchain, or is the generated Metal eval-check code relying
  on undefined behavior that older toolchains happened to tolerate?
- Which Apple Metal Toolchain versions pass or fail rv32im Metal on Apple
  Silicon, and what does the CI runner use?
- Which real target workload should represent "best local prover" for M5 Max:
  single segment, multi-segment, Keccak-heavy, or recursion-heavy?
- Is `Succinct` required for the local workflow, or is `Composite` acceptable as
  the main artifact when proof size is not the bottleneck?
- Do we need Apple Silicon Groth16 at all, or is transparent STARK proving the
  actual target?
