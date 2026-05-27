The RISC Zero Proving System

These are the core algorithms that prove and verify the execution of zk-STARK circuits.

# Crate Feature Flags

The following [crate feature flags](https://doc.rust-lang.org/cargo/reference/features.html) are available.

| Feature | Target(s)         | Implies    | Description                                                                                |
| ------- | ----------------- | ---------- | ------------------------------------------------------------------------------------------ |
| cuda    |                   | prove, std | Turns on CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed.      |
| metal   | macos             | prove, std | Deprecated - release-3.0 does not enable Metal GPU acceleration by default on Apple Silicon; local proving falls back to CPU in this release line.      |
| prove   | all except rv32im | std        | Enables the prover, incompatible within the zkvm guest.                                    |
| std     | all               |            | Support for the Rust stdlib.                                                               |
