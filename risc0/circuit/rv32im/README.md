
The RISC Zero zkVM circuit

# Crate Feature Flags

The following [crate feature flags](https://doc.rust-lang.org/cargo/reference/features.html) are available.

| Feature | Target(s)  | Implies | Description |
| --- | --- | --- | ---- |
| cuda || prove, std | Turns on CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed. |
metal |macos|prove|Turns on Metal GPU acceleration for the prover
prove|all except rv32im|std| Disable this feature if you want to use the `guest` module in guest-side code
std|all|--|Support for stdlib in the guest

* cuda
  * Optional (default is CPU only)
  * Turns on CUDA GPU acceleration for the prover
* metal
  * Optional (default is CPU only)
  * Turns on Metal GPU acceleration for the prover
  * Only available for MacOS
* prove
  * Enabled by default
  * Disable this feature if you want to use the `guest` module in guest-side code (or if you only need the verifier, for the sake of excluding unnecessary code)
  * Must be set when `metal` or `cuda` is selected
* std
  * Optional support for stdlib in the guest
