# Host Code 101

In a [zkVM application][zkVM], the [host] is the machine that is running the
zkVM. The host is an untrusted agent that sets up the zkVM environment and
handles inputs/outputs during execution.

> **Note:** _If you're building for [Bonsai], you don't need to write host
> code._

This page serves as an introduction to writing RISC Zero host code, to help you
get started building applications for the [zkVM].

- For a step-by-step tutorial for writing your own host code, check out our
  [Hello World Tutorial][tutorial].
- All of the host functionality is described in the [`risc0-zkvm` Rust
  crate][risc0-zkvm].

## The Executor & the Prover

In a zkVM application, the host is responsible for constructing and running the
[Executor] and the [Prover].

![From Guest Code to Receipt][from-rust-to-receipt]

In more detail, the host will:

1. Construct an [execution environment][executor-env] where it will run the
   [Executor] for a [guest program].
   - This environment is where the host will provide settings and communicate
     with the [guest].
2. Run the [Prover] to [execute] and [prove] the [guest program] and generate a
   [receipt].

The [receipt] can now be passed to a third-party for verification.

## A Very Simple Host

The code shown below is the `main()` function for a very simple host program.
Aside from the absence of any I/O during execution, the host performs exactly
the actions described above.

```rust
use risc0_zkvm::{default_prover, ExecutorEnv};
# use risc0_zkvm_methods::HELLO_COMMIT_ELF as METHOD_NAME_ELF;

let env = ExecutorEnv::builder().build().unwrap();
let prover = default_prover();
let receipt = prover.prove(env, METHOD_NAME_ELF).unwrap().receipt;
```

Here, the zkVM uses `METHOD_NAME_ELF` binary to execute guest code. The `METHOD_NAME_ELF` is computed during compilation. The user needs to import it (`use methods::{METHOD_NAME_ELF};`) and then pass it as an input parameter to the `prover.prove` function.

To see more complex examples, check out the [examples].

## Verifying Receipts

The functionality for [verifying receipts][receipt-verify] is also included in
the [`risc0-zkvm` Rust crate][risc0-zkvm].

The standard workflow is for one party to generate a receipt and pass it to
another party for verification, along these lines:

```rust
# use risc0_zkvm::{default_prover, ExecutorEnv};
# use risc0_zkvm_methods::HELLO_COMMIT_ELF as METHOD_NAME_ELF;
# use risc0_zkvm_methods::HELLO_COMMIT_ID as METHOD_NAME_ID;
# let env = ExecutorEnv::builder().build().unwrap();
# let prover = default_prover();
# let receipt = prover.prove(env, METHOD_NAME_ELF).unwrap().receipt;
receipt.verify(METHOD_NAME_ID).unwrap();
```

During compilation, we compute the `METHOD_NAME_ID`, and the user needs to import it (`use methods::{METHOD_NAME_ID};`) before passing it to `receipt.verify` function for verification.

For more information on passing and verifying receipts, check out our page on
[Receipts]. For practical demos, check out the [examples].

## Happy Building!

Hopefully, this guide and the [zkVM Quick Start][quickstart] page will be
sufficient for you to build your first [zkVM application][zkVM]!

If you run into problems, don't be a stranger! You can file an issue on \[these
docs] or the [examples], and we're happy to answer questions on [Discord].

[Bonsai]: ../generating-proofs/remote-proving.md
[Discord]: https://discord.gg/risczero
[examples]: ./examples.md
[execute]: /terminology#execute
[executor]: /terminology#executor
[executor-env]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ExecutorEnv.html
[from-rust-to-receipt]: /diagrams/from-rust-to-receipt.png
[guest]: /terminology#guest
[guest program]: /terminology#guest-program
[host]: /terminology#host
[journal]: /terminology#journal
[JSON]: https://github.com/risc0/risc0/blob/main/examples/json/src/main.rs
[method]: /terminology#method
[prove]: /terminology#prove
[Prover]: /terminology#prover
[quickstart]: ./quickstart.md
[receipt]: /terminology#receipt
[Receipts]: ./receipts.md
[receipt-verify]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#method.verify
[risc0-zkvm]: https://docs.rs/risc0-zkvm
[tutorial]: ./tutorials/hello-world.md
[verifies]: /terminology#verify
[zkVM]: ./zkvm_overview.md
