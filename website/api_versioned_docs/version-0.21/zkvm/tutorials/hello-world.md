# Building zkVM Hello World

This tutorial will walk you through building your first zkVM application. By
following the steps in this guide, you will learn how:

- to use the [cargo-risczero] tool to create a new project
- to send private data to the guest program
- the zkVM executes and generates a proof of a guest program
- the guest writes public output

## Step 1: Create a new project

Firstly, visit the [installation][install] page for how to install all the
necessary software. Next, using the `cargo-risczero` tool create a `hello-world`
project from the command line. The `cargo-risczero` tool provides a
`--guest-name` parameter which allows control over the name of the guest
program:

```bash
cargo risczero new hello-world --guest-name hello_guest
cd hello-world
```

In the project folder, `hello-world`, build and run the project using `cargo run --release`. Use this command any time you'd like to check your progress.

## Step 2 (Host): Share private data as input with the guest

zkVM or a [prover] runs on the **[host]**. The host code is in
`hello-world/host/src/main.rs`. The host creates an executor environment
`ExecutorEnv` before constructing a prover. The host makes the value `input`
available to the guest before execution. It does it by adding `input` to the
executor environment, which is responsible for managing guest-readable memory.
When the prover executes the program, it can access input:

```rust
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    let input: u32 = 7;
    let env = ExecutorEnv::builder().write(&input).unwrap().build().unwrap();
}
```

## Step 3 (Guest): Read input and commit output

Now, let's look at the guest code located in `methods/guest/src/main.rs`. This
is the portion of the code that will be proven. In the code snippet below, the
guest reads the `input` value from the host and then commits it to the [journal]
portion of the [receipt].

```rust ignore
use risc0_zkvm::guest::env;

fn main() {
    // read the input
    let input: u32 = env::read();

    // do something with the input
    // writing to the journal makes it public
    env::commit(&input);
}
```

The `env::commit` function commits public results to the [journal]. Once
committed to the journal, anyone with the [receipt] can read this value.

Notice, by committing any private information to the journal, we make this
private data public. We want to avoid committing sensitive data to public
journal.

## Step 4 (Host): Generate a receipt and read its journal contents

Let's look at how the host generates a receipt and extracts the [journal]'s
contents. We get a receipt, extract a journal from the receipt, and verify it.
In a real-world scenario, we'd want to hand the [receipt] to someone else for
verification, and the `prove` function does internal verification of the
receipt. After we extract the journal from the receipt, let's print `Hello
world` with the public output by adding this line to the host:

```rust ignore
println!("Hello, world! I generated a proof of guest execution! {} is a public output from journal", output);
```

```rust ignore
use methods::{HELLO_GUEST_ELF, HELLO_GUEST_ID};
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    let input: u32 = 15 * u32::pow(2, 27) + 1;
    let env = ExecutorEnv::builder().write(&input).unwrap().build().unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, HELLO_GUEST_ELF).unwrap();

    // Extract journal of receipt
    let output: u32 = receipt.journal.decode().unwrap();

    // Print, notice, after committing to a journal, the private input became public
    println!("Hello, world! I generated a proof of guest execution! {} is a public output from journal ", output);
}
```

You should now be able to see your proof with `cargo run --release`. If your
program printed the "Hello, world!" assertion and [receipt] verification was a
success, congratulations! If not, we hope that troubleshooting will get you
familiar with the system, and we'd love to chat with you on [Discord]. Or, if
you believe you've found a bug or other problem in our code, please open an
[issue] describing the problem.

If you're ready to start building more complex projects, we recommend taking a
look at the other [examples] for more project ideas that use zero-knowledge
proofs.

[cargo-risczero]: https://docs.rs/cargo-risczero
[Discord]: https://discord.gg/risczero
[examples]: ../examples.md
[guest]: /terminology#guest-program
[host]: /terminology#host-program
[install]: ../install.md
[issue]: https://github.com/risc0/risc0/issues/new/choose
[journal]: /terminology#journal
[prover]: /terminology#prover
[receipt]: /terminology#receipt
[seal]: /terminology#seal
