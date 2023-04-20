RISC Zero's core Zero Knowledge Proof components.

These are the core algorithms that prove and verify the execution of zk-STARK circuits.

# Crate Feature Flags

The following crate feature flags are available. They are configured in your `Cargo.toml`.

* cuda
  * Optional (default is CPU only)
  * Turns on GPU acceleration for guest code with CUDA
* metal
  * Optional (default is CPU only)
  * Turns on GPU acceleration for guest code with Metal
* prove
  * Enabled by default
  * Disable this feature if you only need to use the verifier
* std
  * Optional support for stdlib in the guest, including `std::io` read and write in the guest
