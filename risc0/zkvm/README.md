<!-- cargo-rdme start -->

The RISC Zero zkVM is a RISC-V virtual machine that produces [zero-knowledge
proofs] of code it executes. By using the zkVM, a cryptographic [receipt] is
produced which anyone can [verify][receipt-verify] was produced by the
zkVM's guest code. No additional information about the code execution (such
as, for example, the inputs provided) is revealed by publishing the
[receipt].

Additional (non-reference) resources for using our zkVM that you may also
find helpful, especially if you're new to the RISC Zero zkVM. These include:

* Our [zkVM Tutorial], which walks you through writing your first zkVM
  project.
* The [`cargo risczero` tool]. It includes a `new` command which generates
  code for building and launching a zkVM guest and guidance on where
  projects most commonly modify host and guest code.
* The [examples], which contains various examples using our zkVM.
* [This clip][zkHack] from our presentation at ZK Hack III gives an overview
  of the RISC Zero zkVM. [Our YouTube channel][YouTube] has many more videos
  as well.
* We track zkVM issues with known workarounds using the [rust guest
  workarounds] GitHub tag. If you're having problems running your code in
  the zkVM, you can see if there's a workaround, and if you're using a
  workaround, you can track when it gets resolved to a permanent solution.
* And more on [the RISC Zero developer website][dev-docs]!

# Crate Feature Flags

The following feature flags are supported.

Note that in order to use `risc0-zkvm` in the guest, you must disable the
default features by setting `default-features = false`.

| Feature          | Target(s)         | Implies    | Description                                                                                                                                                  |
| ---------------- | ----------------- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| client           | all except rv32im | std        | Enables the client API.                                                                                                                                      |
| cuda             |                   | prove, std | Enables CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed.                                                                         |
| disable-dev-mode | all except rv32im |            | Disables dev mode so that proving and verifying may not be faked. Used to prevent a misplaced `RISC0_DEV_MODE` from breaking security in production systems. |
| metal            | macos             | prove, std | Enables Metal GPU acceleration for the prover.                                                                                                               |
| prove            | all except rv32im | std        | Enables the prover, incompatible within the zkvm guest.                                                                                                      |
| std              | all               |            | Support for the Rust stdlib.                                                                                                                                 |

[`cargo risczero` tool]: https://crates.io/crates/cargo-risczero
[dev-docs]: https://dev.risczero.com
[examples]: https://dev.risczero.com/api/zkvm/examples
[receipt]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/receipt/struct.Receipt.html
[receipt-verify]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/receipt/struct.Receipt.html#method.verify
[rust guest workarounds]: https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22
[YouTube]: https://www.youtube.com/@risczero
[zero-knowledge proofs]: https://en.wikipedia.org/wiki/Zero-knowledge_proof
[zkHack]: https://youtu.be/cLqFvhmXiD0
[zkVM Tutorial]: https://dev.risczero.com/api/zkvm/tutorials/hello-world

<!-- cargo-rdme end -->
