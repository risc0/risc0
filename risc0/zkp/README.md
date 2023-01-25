RISC Zero's core Zero Knowledge Proof components for Rust.

These are the core algorithms that prove and verify the execution of RISC Zero's
RISC-V circuit. This includes utilities such as [core::sha] (which allows faster
SHA-256 hashing than a naive RISC-V implementation). It is these latter
utilities that are more commonly used directly from this crate: Developers
looking to construct (or verify) a zero-knowledge proof with RISC Zero are
advised to use the [risc0_zkvm] crate instead.

[risc0_zkvm]: https://docs.rs/risc0-zkvm
