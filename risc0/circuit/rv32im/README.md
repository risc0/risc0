The RISC Zero zkVM circuit

# Crate Feature Flags

The following [crate feature flags](https://doc.rust-lang.org/cargo/reference/features.html) are available.

| Feature | Target(s)         | Implies    | Description                                                                           |
| ------- | ----------------- | ---------- | ------------------------------------------------------------------------------------- |
| cuda    |                   | prove, std | Turns on CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed. |
| metal   | macos             | prove, std | Turns on Metal GPU acceleration for the prover.                                       |
| prove   | all except rv32im | std        | Enables the prover, incompatible within the zkvm guest.                               |
| std     | all               |            | Support for the Rust stdlib.                                                          |
