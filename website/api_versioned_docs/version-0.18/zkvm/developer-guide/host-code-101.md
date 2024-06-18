# Host Code 101

In a [zkVM application], the [host] is the machine that is running the zkVM.
The host is an untrusted agent that sets up the zkVM environment and handles inputs/outputs during execution.

> **Note:** _If you're building for [Bonsai], you don't need to write host code._

This page serves as an introduction to writing RISC Zero host code, to help you get started building applications for the [zkVM].

- For a simple example, check out the [Hello World demo], where the [guest] receives two inputs from the [host] and commits their product to the [journal]. For a slightly more complex example, see the [JSON demo].
- For a step-by-step tutorial for writing your own host code, check out our [Hello World Tutorial].
- All of the host functionality is described in the [`risc0-zkvm` Rust crate].

## The Executor & the Prover

In a zkVM application, the host is responsible for constructing and running the [Executor] and the [Prover].

![From Guest Code to Receipt](/diagrams/from-rust-to-receipt.png)

In more detail, the host will:

1. Construct an [execution environment] where it will run the [Executor] for a [guest program].
   - This environment is where the host will provide settings and communicate with the [guest].
2. Run the [Prover] to [execute] and [prove] the [guest program] and generate a [receipt].

The [receipt] can now be passed to a third-party for verification.

## A Very Simple Host

The code shown below is the `main()` function for a very simple host program.
Aside from the absence of any I/O during execution, the host performs exactly the actions described above.

```rust
use risc0_zkvm::{default_prover, ExecutorEnv};
# use risc0_zkvm_methods::HELLO_COMMIT_ELF as METHOD_NAME_ELF;

let env = ExecutorEnv::builder().build().unwrap();
let prover = default_prover();
let receipt = prover.prove_elf(env, METHOD_NAME_ELF).unwrap();
```

To see more complex examples, check out our [examples] folder on GitHub.

## Verifying Receipts

The functionality for [verifying receipts] is also included in the [`risc0-zkvm` Rust crate].

The standard workflow is for one party to generate a receipt and pass it to another party for verification, along these lines:

```rust
# use risc0_zkvm::{default_prover, ExecutorEnv};
# use risc0_zkvm_methods::HELLO_COMMIT_ELF as METHOD_NAME_ELF;
# use risc0_zkvm_methods::HELLO_COMMIT_ID as METHOD_NAME_ID;
# let env = ExecutorEnv::builder().build().unwrap();
# let prover = default_prover();
# let receipt = prover.prove_elf(env, METHOD_NAME_ELF).unwrap();
receipt.verify(METHOD_NAME_ID).unwrap();
```

For more information on passing and verifying receipts, check out our page on [Receipts].
For practical demos, check out the [examples] on GitHub.

## Happy Building!

Hopefully, this guide and the [zkVM Quick Start] page will be sufficient for you to build your first [zkVM application]!

If you run into problems, don't be a stranger!
You can file an issue on [these docs] or the [examples], and we're happy to answer questions on [Discord].

[Bonsai]: ../../bonsai/
[Discord]: https://discord.gg/risczero
[examples]: https://github.com/risc0/risc0/tree/release-0.18/examples/
[execute]: /terminology#execute
[execution environment]: https://docs.rs/risc0-zkvm/0.18/risc0_zkvm/struct.ExecutorEnv.html
[executor]: /terminology#executor
[guest]: /terminology#guest
[`guest` module]: https://docs.rs/risc0-zkvm/0.18/risc0_zkvm/guest
[guest program]: /terminology#guest-program
[Hello World demo]: https://github.com/risc0/risc0/tree/release-0.18/examples/hello-world
[Hello World Tutorial]: https://github.com/risc0/risc0/blob/release-0.18/examples/hello-world/tutorial.md
[host]: /terminology#host
[journal]: /terminology#journal
[JSON demo]: https://github.com/risc0/risc0/blob/release-0.18/examples/json/src/main.rs
[method]: /terminology#method
[prove]: /terminology#prove
[Prover]: /terminology#prover
[proves]: /terminology#validity-proof
[receipt]: /terminology#receipt
[Receipts]: receipts.md
[`risc0-zkvm` Rust crate]: https://docs.rs/risc0-zkvm
[these docs]: https://github.com/risc0/risc0/issues/new/choose
[verifies]: /terminology#verify
[verifying receipts]: https://docs.rs/risc0-zkvm/0.18/risc0_zkvm/struct.Receipt.html#method.verify
[zkVM Quick Start]: ../quickstart.md
[zkVM Overview]: ../zkvm_overview.md
[zkVM Application]: ../
[zkVM]: ../
