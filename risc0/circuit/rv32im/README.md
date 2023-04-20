
The RISC Zero zkVM circuit

# Crate Feature Flags

The following crate feature flags are available. They are configured in your `Cargo.toml`.

* cuda
  * Optional (default is CPU only)
  * Turns on CUDA GPU acceleration for the prover
* metal
  * Optional (default is CPU only)
  * Turns on Metal GPU acceleration for the prover
  * Only available for MacOS
* prove
  * Enabled by default
  * Disable this feature if you only need to use the verifier, or if you want to use the `guest` module in guest-side code
  * Must be set when `metal` or `cuda` is selected
* std
  * Optional support for stdlib in the guest, including `std::io` read and write in the guest
