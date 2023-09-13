# Tutorial: Building your first zkVM application
Welcome!

This tutorial will walk you through building your first [zkVM application].
By following the steps in this guide, you will:
- Use the [cargo risczero] tool to create a blank [starter template]
- Make the handful of changes necessary to create a functional zkVM application
- Finish the tutorial with an exact copy of the [host] and [guest] programs from the [hello-world] example.

For more resources for building zkVM applications, check out our [developer docs].

[zkVM application]: https://dev.risczero.com/zkvm
[cargo risczero]: https://docs.rs/cargo-risczero/latest/cargo_risczero/
[starter template]: https://github.com/risc0/risc0/tree/v0.16.0/templates/rust-starter
[hello-world]: https://github.com/risc0/risc0/tree/v0.16.0/examples/hello-world
[developer docs]: https://dev.risczero.com/zkvm
[host]: https://dev.risczero.com/terminology#host-program
[guest]: https://dev.risczero.com/terminology#guest-program

## Step 1: Create a new project

First, [install Rust] if you don't already have it.
Now, you can create a RISC Zero zkVM project from the command line:

```bash
## Install from crates.io
cargo install cargo-risczero
cargo risczero install

# Navigate to where you want to create your project
cd wherever/you/want

## Create a project from our starter template
cargo risczero new hello-world
```
This will create a project named `hello-world` in the directory where you ran the [`cargo risczero new`] command. Now we can enter our new project's directory and start working on it!
```bash
cd hello-world
```

[`cargo risczero new`]: https://docs.rs/cargo-risczero/latest/cargo_risczero/#new
[install Rust]: https://www.rust-lang.org/tools/install

## Step 2: Give the methods package a name

The methods package contains the program that executes on the guest zkVM as well as a few supporting libraries. Before we proceed, let's change its name in `methods/Cargo.toml` to match the name of our project, renaming `name = methods` to `name = hello-world-methods`.
Also in `host/Cargo.toml`, rename `methods = { path = "../methods" }` to `hello-world-methods = { path = "../methods" }` in order to locate the renamed guest code.

Parts of this package are included in the driver program `src/main.rs`, so change the line

```no_compile
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
```

to

```no_compile
use hello_world_methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
```

## Step 3: Give the guest program and its packages a name

Take a moment to look inside the methods package directory. The `hello-world` project will call a program that executes on the guest zkVM whose source is found in `methods/guest/src/main.rs`. Our next step will be to name this guest program.


Edit `methods/guest/Cargo.toml`, changing the line `name = "method_name"` to instead read `name = "multiply"`.


In order to access guest code from the host driver program, the host program `host/src/main.rs` includes two guest methods: `METHOD_NAME_ELF` and `METHOD_NAME_ID`.

```no_compile
use hello_world_methods::{METHOD_NAME_ELF, METHOD_NAME_ID};

```

Both of these must be changed to reflect the new guest program name:

```
use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_ID};
```
(As an aside, if you add more than one callable guest program to your next RISC Zero zkVM project, you'll need to include `ELF` and `ID` references once for each guest file.)

While we're at it, let's update the references to `METHOD_NAME_ELF` and `METHOD_NAME_ID` in `hello-world/host/src/main.rs` to reflect our new program name. Don't worry about why these lines are included yet; for now, we're just being diligent not to leave dead references behind.

Here are what the other two lines with `METHOD_NAME_ELF` and `METHOD_NAME_ID` should look like after updating:

```no_compile
    // Rename METHOD_NAME_ELF
    let receipt = prover.prove_elf(env, MULTIPLY_ELF).unwrap();

    // Rename METHOD_NAME_ID
    // receipt.verify(MULTIPLY_ID).unwrap();
```

### Step 4: Build and run the project!

In the main project folder, build and run the project using `cargo run --release`.
Nothing exciting will happen yet, but it should give you an error if you made one of the above changes incorrectly.
Use this command any time you'd like to check your progress.

## Concept break: How do we run and prove the guest program?


Our next objective is to provide the guest program with input. Before we implement this, let's take a closer look at how we run and prove the guest program in `hello-world/src/main.rs`.

In the starter template project, our host driver program creates an executor environment before constructing a prover.  When `Prover::prove_elf()` is called, it will produce a receipt:

```rust
    use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_ID};
    use risc0_zkvm::{
      default_prover,
      serde::{from_slice, to_vec},
      ExecutorEnv,
    };

    // First, we construct an executor environment
    let env = ExecutorEnv::builder().build().unwrap();

    // We're not quite ready to run these steps yet

    // Obtain the default prover.
    // let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    // let receipt = prover.prove_elf(env, MULTIPLY_ELF).unwrap();

    // receipt.verify(MULTIPLY_ID).unwrap();
```



## Step 5 (Host): Share two values with the guest

In this step, we'll be continuing to modify `hello-world/src/main.rs`.
Let's start by picking some aesthetically pleasing primes:
```
fn main() {
    let a: u64 = 17;
    let b: u64 = 23;
}
```

We'd like the host to make the values of `a` and `b` available to the guest prior to execution. We can do this by adding them to the the executor environment, which is responsible for managing guest-readable memory. When the prover executes the program, it will have access to these guest inputs.

 We need to add these values as inputs before the executor environment is built:

 ```rust
    use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_ID};
    use risc0_zkvm::{serde::to_vec, ExecutorEnv};

    let a: u64 = 17;
    let b: u64 = 23;

    // First, we construct an executor environment
    let env = ExecutorEnv::builder()
      // Send a & b to the guest
      .add_input(&to_vec(&a).unwrap())
      .add_input(&to_vec(&b).unwrap())
      .build()
      .unwrap();
```

You can confirm your work with `cargo run --release` — the program still won't do anything, but it should compile and run successfully.
You will get a warning about `from_slice` being unused; this function is needed when reading the [journal], but the guest hasn't written to it yet, so the host can't read from it yet.

## Step 6 (Guest): Multiply two values and commit their result

Now it's time to start writing guest code, located in `methods/guest/src/main.rs`.
This is the portion of the code that will be proven.

For this project, we'll tell the guest to read the values of `a` and `b` from the host and multiply them together.
We'll then publicly commit their product to the [journal] portion of the [receipt].

Here is the complete guest program.
We'll break this down step by step below:
```no_compile
pub fn main() {
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
### Load values from the host

Use `env::read()` to load both numbers that the host provided:

```no_compile
    let a: u64 = env::read();
    let b: u64 = env::read();
```
### Confirm that factors are non-trivial

Next, we'll add a line that panics if either chosen value is 1. This will leave us with a guest program that only completes if the product of `a` and `b` is genuinely composite.
```no_compile
    // Verify that neither of them are 1 (i.e. nontrivial factors)
    if a == 1 || b == 1 {
        panic!("Trivial factors")
    }
```

## Compute and publish the product

Now we can compute their product and `commit` it.
```no_compile
    let product = a.checked_mul(b).expect("Integer overflow");
    env::commit(&product);
```
The `env::commit` function is used to commit public results to the [journal].
Once committed to the journal, anyone with the [receipt] can read this value.

Now you should be able to confirm your work again with `cargo run --release`.
Once more, the program won't do anything, but it should run successfully and build with a single warning about `from_slice` being unused.

## Step 7 (Host): Generate a receipt and read its journal contents

For this step, we return to the main file for the host driver program at `hello-world/host/src/main.rs`, which currently has a placeholder comment asking to fill in with code for handling the [receipt]:

```no_compile
    // Run the prover to produce a receipt.
    let receipt = prover.prove_elf(env, METHOD_NAME_ELF).unwrap();
```

In a real-world scenario, we'd want to hand the [receipt] to someone else, but reading it ourselves will be a nice way to check our project is working as expected.
So, let's extract the [journal]'s contents by replacing the "`TODO`" in the above code snippet with the following lines.

```rust
    use hello_world_methods::{MULTIPLY_ELF, MULTIPLY_ID};
    use risc0_zkvm::{
      default_prover,
      ExecutorEnv,
      serde::{from_slice, to_vec},
    };

    let a: u64 = 17;
    let b: u64 = 23;

    let env = ExecutorEnv::builder()
      // Send a & b to the guest
      .add_input(&to_vec(&a).unwrap())
      .add_input(&to_vec(&b).unwrap())
      .build()
      .unwrap();

    let prover = default_prover();
    let receipt = prover.prove_elf(env, MULTIPLY_ELF).unwrap();
    receipt.verify(MULTIPLY_ID).unwrap();

    // Extract journal of receipt (i.e. output c, where c = a * b)
    let c: u64 = from_slice(&receipt.journal).unwrap();

    // Print an assertion
    println!("Hello, world! I know the factors of {}, and I can prove it!", c);
```

You should now be able to see your proof of factorization with `cargo run --release`.
If your program printed the "Hello, world!" assertion and [receipt] verification was a success, congratulations!
If not, we hope that troubleshooting will get you familiar with the system, and we'd love to chat with you on [Discord].
Or, if you believe you've found a bug or other problem in our code, please open an [issue] describing the problem.

If you're ready to start building more complex projects, we recommend taking a look at the other examples in our [examples directory] and looking through our further [Getting Started resources] for more project ideas that use zero-knowledge proofs.

[examples directory]: https://github.com/risc0/risc0/tree/v0.16.3/examples
[Getting Started resources]: https://dev.risczero.com/zkvm
[Discord]: https://discord.gg/risczero
[issue]: https://github.com/risc0/risc0/issues
[receipt]: https:/dev.risczero.com/terminology#receipt
[journal]: https:/dev.risczero.com/terminology#journal
