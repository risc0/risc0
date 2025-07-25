# Building zkVM Hello World

This tutorial will walk you through building your first zkVM application. By
following the steps in this guide, you will learn how:

- to use the [cargo-risczero] tool to create a new project
- to send private data to the guest program
- the zkVM executes and generates a proof of a guest program
- the guest writes public output

## Step 1: Create a New Project

Firstly, visit the [installation][install] page for how to install the
necessary software.

Once installed, clone the `risc0` monorepo and change into the `hello-world` example directory:

```sh
git clone https://github.com/risc0/risc0
cd risc0/examples/hello-world
```

Next, check the version of `cargo risczero` installed:

```sh
cargo risczero --version
cargo-risczero $MAJOR.$MINOR.$PATCH # e.g. release-1.2
```

To match the example release version with your local installation, check out the corresponding branch of the example:

```sh
git checkout release-$MAJOR.$MINOR # e.g. release-1.2
```

For example, if your local version is `cargo-risczero 1.2.0`, run:

```sh
git checkout release-1.2
```

Once on the correct release branch, run the example:

```sh
cargo run --release
```

Use this command any time you'd like to check your progress.

## Step 2 (Host): Share Private Data as Input with the Guest

The zkVM (or a [prover]) runs on the [host]. The host code is located in `hello-world/src/main.rs` and `hello-world/src/lib.rs`.

The host creates an executor environment `ExecutorEnv` before constructing a prover. This executor environment is responsible for managing guest-readable memory. The host makes the value `input` available to the guest program before execution by adding `input` to the executor environment.

When the prover executes the program, it can access input via the `.write()` method on `ExecutorEnv::builder()`:

```rust ignore
// hello-world/src/lib.rs
use risc0_zkvm::{default_prover, ExecutorEnv, Receipt};

pub fn multiply(a: u64, b: u64) -> (Receipt, u64) {
    let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .write(&a)
        .unwrap()
        .write(&b)
        .unwrap()
        .build()
        .unwrap();
}
```

## Step 3 (Guest): Read Input and Commit Output

The guest code is located in `methods/guest/src/main.rs`. This
is the portion of the code that will be proven. In the code snippet below, the
guest reads the two `a` and `b` values from the host and commits them to the [journal]
portion of the [receipt].

```rust ignore
// hello-world/methods/guest/src/main.rs
use risc0_zkvm::guest::env;
risc0_zkvm::guest::entry!(main);

fn main() {
    // Load the first number from the host
    let a: u64 = env::read();
    // Load the second number from the host
    let b: u64 = env::read();
    // Verify that neither of them are 1 (i.e. nontrivial factors)
    if a == 1 || b == 1 {
        panic!("Trivial factors")
    }
    // Compute the product while being careful with integer overflow
    let product = a.checked_mul(b).expect("Integer overflow");
    env::commit(&product);
}
```

The `env::commit` function commits public results to the [journal]. Once
committed to the journal, anyone with the [receipt] can read this value. Notice, by committing any private information to the journal, we make this **private data public**. For this reason, be sure to avoid committing sensitive data to the public journal.

## Step 4 (Host): Generate a Receipt and Read Its Journal Contents

Let's look at how the host generates a receipt and extracts the contents of the [journal].

First, the [receipt] is generated, and afterwards the journal can be extracted:

```rust ignore
// hello-world/src/main.rs
use hello_world::multiply;
use hello_world_methods::MULTIPLY_ID;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    // Pick two numbers
    let (receipt, _) = multiply(17, 23);

    // Verify receipt, panic if it's wrong
    receipt.verify(MULTIPLY_ID).expect(
        "Code you have proven should successfully verify; did you specify the correct image ID?",
    );
}
```

where the full `multiply` function is:

```rust ignore
// hello-world/src/lib.rs
// Compute the product a*b inside the zkVM
pub fn multiply(a: u64, b: u64) -> (Receipt, u64) {
    let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .write(&a)
        .unwrap()
        .write(&b)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, MULTIPLY_ELF).unwrap().receipt;

    // Extract journal of receipt (i.e. output c, where c = a * b)
    let c: u64 = receipt.journal.decode().expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    // Report the product
    println!("I know the factors of {}, and I can prove it!", c);

    (receipt, c)
}
```

The contents of the journal are stored in the variable `c`. `prover.prove()` carries out proving of the guest program, and it also completes internal verification of the receipt.

## Step 5: Run the Hello World Example

To run this example locally, and see if proving completed successfully, run:

```sh
cargo run --release
```

If proving is successful, the line `"I know the factors of 391, and I can prove it!"` is printed.

To change the number that is factorized, head to `hello-world/src/main.rs` and change this line:

```rust ignore
let (receipt, _) = multiply(17, 23); // where 17 * 23 = 391
```

If something went wrong, we hope that troubleshooting will get you
familiar with the system, and we'd love to chat with you on [Discord]. Or, if
you believe you've found a bug or other problem in our code, please open an
[issue] describing the problem.

If you're ready to start building more complex projects, we recommend taking a
look at the other [examples] for more project ideas that use zero-knowledge
proofs.

[cargo-risczero]: https://docs.rs/cargo-risczero
[Discord]: https://discord.gg/risczero
[examples]: ../examples.md
[host]: /terminology#host-program
[install]: ../install.md
[issue]: https://github.com/risc0/risc0/issues/new/choose
[journal]: /terminology#journal
[prover]: /terminology#prover
[receipt]: /terminology#receipt
