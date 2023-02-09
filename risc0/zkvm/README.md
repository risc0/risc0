The RISC Zero zkVM is a RISC-V virtual machine that produces
[zero-knowledge proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof)
of code it executes. By using the zkVM, a cryptographic
[receipt](receipt::Receipt) is produced which anyone can [verify](Receipt::verify)
was produced by the zkVM's guest code. No additional information about the
code execution (such as, for example, the inputs provided) is revealed by
publishing the [receipt](receipt::Receipt).

In addition to [our reference documentation on docs.rs](https://docs.rs/risc0-zkvm), we have
additional (non-reference) resources for using our zkVM that you may also
find helpful, especially if you're new to the RISC Zero zkVM. These include:

* Our [Hello Multiply!](https://www.risczero.com/docs/examples/hello_multiply)
tutorial, which walks you through writing your first zkVM project.
* A [zkVM Rust starter template](https://github.com/risc0/risc0-rust-starter),
a template for starting zkVM projects. It includes code for building and
launching a zkVM guest and guidance on where projects most commonly modify
host and guest code.
* The [zkVM Rust examples repository](https://github.com/risc0/risc0-rust-examples),
which contains various examples using our zkVM.
* [This clip](https://youtu.be/cLqFvhmXiD0) from our presentation at ZK Hack
III gives an overview of the RISC Zero zkVM.
[Our YouTube channel](https://www.youtube.com/@risczero) has many more
videos as well.
* And more on [the RISC Zero website](https://www.risczero.com/)!