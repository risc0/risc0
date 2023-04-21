The RISC Zero zkVM is a RISC-V virtual machine that produces [zero-knowledge
proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof) of code it executes.
By using the zkVM, a cryptographic [receipt](SessionReceipt) is produced which
anyone can [verify](SessionReceipt::verify) was produced by the zkVM's guest
code. No additional information about the code execution (such as, for example,
the inputs provided) is revealed by publishing the [receipt](SessionReceipt).

In addition to [our reference documentation on
docs.rs](https://docs.rs/risc0-zkvm), we have additional (non-reference)
resources for using our zkVM that you may also find helpful, especially if
you're new to the RISC Zero zkVM. These include:

* Our [Factors](https://github.com/risc0/risc0/tree/main/examples/factors#tutorial)
tutorial, which walks you through writing your first zkVM project.
* The [`cargo risczero` tool](https://crates.io/crates/cargo-risczero). It
includes a `new` command which generates code for building and launching a zkVM
guest and guidance on where projects most commonly modify host and guest code.
* The [zkVM Rust examples
directory](https://github.com/risc0/risc0/tree/main/examples), which contains
various examples using our zkVM.
* [This clip](https://youtu.be/cLqFvhmXiD0) from our presentation at ZK Hack III
gives an overview of the RISC Zero zkVM. [Our YouTube
channel](https://www.youtube.com/@risczero) has many more videos as well.
* We track zkVM issues with known workarounds using the [rust guest
  workarounds](https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22)
  GitHub tag. If you're having problems running your code in the zkVM, you can
  see if there's a workaround, and if you're using a workaround, you can track
  when it gets resolved to a permanent solution.
* And more on [the RISC Zero website](https://www.risczero.com/)!
