# Building zkVM Hello World

This tutorial will walk you through building your first zkVM application.
By following the steps in this guide, you will learn how:

- to use the [cargo risczero] tool to create a new project
- to send private data to the guest program
- the zkVM executes and generates a proof of a guest program
- the guest writes public output

## Step 1: Create a new project

Firstly, visit the [installation] page for how to install all the necessary software.
Secondly, using the `cargo-risczero` tool create a `hello-world` project from the command line. The `cargo-risczero` tool allows for a `--guest-name` parameter, a guest program you want to run on zkVM to generate a proof of its execution:

```bash
## Create a project from our starter template
cargo risczero new hello-world --guest-name hello_guest
cd hello-world
```

In the project folder, `hello-world`, you can build and run the project via `cargo run --release`.
Use this command any time you'd like to check your progress.

You can also generate `rustdoc` pages for your project with `cargo doc`.

## Step 2 (Host): Share private data as input with the guest

zkVM or a [prover] runs on the **[host]**. The host code is in `hello-world/host/src/main.rs`.
The host creates an executor environment [`ExecutorEnv`] before constructing a prover.
The host makes the value `input` available to the guest before execution. It does so by adding `input` to the executor environment, which is responsible for managing guest-readable memory. The following piece of code demonstrates this:

```rust
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    let input: u32 = 7;
    let env = ExecutorEnv::builder().write(&input).unwrap().build().unwrap();
}
```

## Step 3 (Guest): Read input and commit output

Now, let's look at the guest code located in `methods/guest/src/main.rs`.
This is the portion of the code that will be proven.
In the code snippet below, the guest reads the `input` value from the host and then commits some `output` to the [journal] portion of the [receipt].
As this is just a template snippet, we commit some dummy `output`. In a real use case this should be the result of some calculations made over the `input` by the guest. 


```rust title="hello-world/methods/guest/src/main.rs"
use risc0_zkvm::guest::env;

// Define a main entrypoint to the guest program.
risc0_zkvm::guest::entry!(main);

pub fn main() {
    // TODO: Implement your guest code here

    // Read the input
    // NOTE: The input is basically the only thing kept in secret from verifiers.
    // It is not a good idea to make it public by outputting it to journal.
    let _input: u32 = env::read();

    // TODO: do something with the input
    let output = "Hello, World!";

    // Write public output to the journal.
    env::commit(&output);
}
```

The `env::commit` function commits public results to the [journal]. Once a value committed to the journal, anyone with the [receipt] can read it.

:::warning 
Notice, by committing any information to the journal, we make this data **public**. We want to avoid committing sensitive data to public journal. Guest program `input` is usually a **sensitive** kind data.
:::

## Step 4 (Host): Generate a receipt and read its journal contents

Let's look at how the host generates a receipt and extracts the [journal]'s contents.
We get a receipt, extract a journal from the receipt, and verify it.

After we extract the journal from the receipt, let's print the public output by adding `println!` to the host program.

Last but not the least, we verify the receipt by invoking the [`risc0_zkvm::Receipt::verify()`] method on it. In a real-world scenario, we'd want to hand the [receipt] to someone else who would verify it.

```rust title="hello-world/host/src/main.rs"
use methods::{
    HELLO_GUEST_ELF, HELLO_GUEST_ID,
};
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    let input: u32 = 15 * u32::pow(2, 27) + 1;
    let env = ExecutorEnv::builder().write(&input).unwrap().build().unwrap();
    // Obtain the default prover.
    let prover = default_prover();
    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove_elf(env, HELLO_GUEST_ELF).unwrap();

    // Extract the journal from the receipt
    let output: String = receipt.journal.decode().unwrap();

    // Print the extracted output
    println!("Yay, I generated a proof of guest execution! \"{}\" is the public output from the journal.", &output);

    // The receipt was verified at the end of proving. We give the below code is an
    // example of how someone else could verify this receipt.
    receipt.verify(HELLO_GUEST_ID).expect("Receipt verification failed!");
}
```

You should now be able to see your proof with running the command:

```bash
cargo run --release
```

If your program printed out the `"Hello, world!"` and the [receipt] verification was a success, **congratulations**!

You can try how a verification fails by adding the following line to the code above: 

```rust
receipt.verify([42u32; 8]).expect("Receipt verification failed!");
```

When you re-run the program, as *ImageID* provided to verifier is invalid, it should panic because of the failed verification. However, if you run the program with [dev-mode] turned on, that still would work as in this mode a [*fake*] receipt is generated which is always verified successfully:

```bash
RISC0_DEV_MODE=true cargo run --release
```

:::tip
If you met any issues during this tutorial, we hope that troubleshooting will get you familiar with the system, and we'd love to chat with you on [Discord].
Or, if you believe you've found a bug or other problem in our code, please feel free to open an [issue] describing the problem.

If you're ready to start building more complex projects, we recommend taking a look at the other examples in our [examples directory] for more project ideas that use zero-knowledge proofs.
:::

[Installation]: ../install
[cargo risczero]: https://docs.rs/cargo-risczero
[examples directory]: https://github.com/risc0/risc0/tree/main/examples
[host]: /terminology#host-program
[guest]: terminology#guest-program
[receipt]: /terminology#receipt
[journal]: /terminology#journal
[seal]: /terminology#seal
[Discord]: https://discord.gg/risczero
[issue]: https://github.com/risc0/risc0/issues
[prover]: /terminology#prover
[`ExecutorEnv`]: https://docs.rs/risc0-zkvm/0.19.0/risc0_zkvm/struct.ExecutorEnv.html
[`risc0_zkvm::Receipt::verify()`]: https://docs.rs/risc0-zkvm/0.19.0/risc0_zkvm/struct.Receipt.html#method.verify
[dev-mode]: /api/zkvm/dev-mode
[*fake*]: https://docs.rs/risc0-zkvm/0.19.0/risc0_zkvm/enum.InnerReceipt.html#variant.Fake