# Factors

The _factors_ example is a minimalistic RISC Zero zkVM proof. The prover demonstrates that they know two nontrivial factors (i.e. both greater than 1) of a number, without revealing what those factors are. Thus, the prover demonstrates that a number is composite — and that they know the factors — without revealing any further information about the number.

To see this example in action, [install Rust] and use `cargo run` in this directory to run it:
```
cargo run
```

# Tutorial
## How to Recreate _Factors_

This example is a good introduction for beginners new to RISC Zero; if you're looking to get started creating RISC Zero zkVM projects, you're in the right place! We'll spend the rest of this README walking you through how to recreate the factors example for yourself, assuming no prior knowledge of RISC Zero.

## Step 1: Create a new project

First, [install Rust] if you don't already have it. Next you can create a RISC Zero zkVM project with boilerplate already filled out using our [`cargo risczero` tool]:
```
## Install from crates.io
cargo install cargo-risczero

## Navigate to where you want to create your project
cd wherever/you/want

## Create a project from our starter template
cargo risczero new factors
```
This will create a project named `factors` in the directory where you ran the `cargo risczero new` command. Now we can enter our new project's directory and start working on it!
```
cd factors
```

## Step 2: Give the guest program a name

This project will call a program that executes on the guest zkVM whose source is found in `factors/methods/guest/src/main.rs`.
Edit `methods/guest/Cargo.toml`, changing the line `name = "method_name"` to instead read
```
name = "multiply"
```

In order to access this guest code from the host driver program, the host program `factors/host/src/main.rs` includes two guest methods:

```rust
use methods::{METHOD_NAME_ELF, METHOD_NAME_ID};
```

Both of these must be changed to reflect the new guest program name:
```rust
use methods::{MULTIPLY_ELF, MULTIPLY_ID};
```
(As an aside, if you add more than one callable guest program to your next RISC Zero zkVM project, you'll need to include these `ELF` and `ID` references once for each guest file.)

While we're at it, let's change the rest of the references in `factors/host/src/main.rs`.
Don't worry about why these lines are included yet; for now, we're just being diligent not to leave dead references behind.
Here are what the other two lines with `METHOD_NAME_ELF` and `METHOD_NAME_ID` should look like after updating:

```rust
fn main() {
    // Here we make an executor, loading the (renamed) ELF binary.
    let mut exec = Executor::from_elf(env, METHOD_NAME_ELF).unwrap();
...
    // Optional: Verify receipt to confirm that recipients will also be able to
    // verify your receipt
    receipt.verify(METHOD_NAME_ID).unwrap();
}
```

### Intermission: Build and run the project!

In the main project folder, build and run the project using `cargo run --release`.
Nothing exciting will happen yet, but it should give you an error if you made one of the above changes incorrectly.
Use this command any time you'd like to check your progress.

## Step 3 (Host): Share two values with the guest

In this step, we'll be continuing to modify `factors/src/main.rs`.
Let's start by picking some aesthetically pleasing primes:
```
fn main() {
    let a: u64 = 17;
    let b: u64 = 23;
```

Currently, our host driver program creates an executor environment before constructing an executor. The `Executor::run()` command will produce a session. The `Session::prove()` command will cause our guest program to execute, producing a receipt:

```rust
    // First, we construct an executor environment
    let env = ExecutorEnv::default();

    // TODO: add guest input to the executor environment using
    // ExecutorEnvBuilder::add_input()

    // Next, we make an executor, loading the (renamed) ELF binary.
    let mut exec = Executor::from_elf(env, METHOD_NAME_ELF).unwrap();

    // Run the executor to produce a session.
    let session = exec.run().unwrap();

    // Prove the session to produce a receipt.
    let receipt = session.prove().unwrap();
```
 We'd like the host to make the values of `a` and `b` available to the guest prior to execution.
 Because the executor environment is responsible for managing guest-readable memory, we need to add these values as inputs after the environment is created. We do this in between making the executor environment and constructing the executor (in place of the "`TODO`" in the previous code snippet).

 As a preliminary step, let's first move away from the default construction `ExecutorEnv::default()` and instead use `ExecutorEnv::builder()`, which supports adding guest input:

 ```rust
    // First, we construct an executor environment
      let env = ExecutorEnv::builder().build();

          // TODO: add guest input to the executor environment using
    // ExecutorEnvBuilder::add_input()
  ```

 Now we're ready to add inputs `a` and `b` to the executor environment before it gets built:

 ```rust
    // First, we construct an executor environment
      let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .add_input(&to_vec(&a).unwrap())
        .add_input(&to_vec(&b).unwrap())
        .build();
```

You can confirm your work with `cargo run --release` — the program still won't do anything, but it should compile and run successfully.
You will get a warning about `from_slice` being unused; this function is needed when reading the [journal], but the guest hasn't written to it yet, so the host can't read from it yet.

## Step 4 (Guest): Multiply two values and commit their result

Now it's time to start writing guest code, located in `methods/guest/src/main.rs`.
This is the portion of the code that will be proven.

For this project, we'll tell the guest to read the values of `a` and `b` from the host and multiply them together.
We'll then publicly commit their product to the [journal] portion of the [receipt].

Here is the complete guest program.
We'll break this down step by step below:
```rust
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

```rust
    let a: u64 = env::read();
    let b: u64 = env::read();
```
### Confirm that factors are non-trivial

Next, we'll add a line that panics if either chosen value is 1. This will leave us with a guest program that only completes if the product of `a` and `b` is genuinely composite.
```rust
    // Verify that neither of them are 1 (i.e. nontrivial factors)
    if a == 1 || b == 1 {
        panic!("Trivial factors")
    }
```

## Compute and publish the product

Now we can compute their product and `commit` it.
```rust
    let product = a.checked_mul(b).expect("Integer overflow");
    env::commit(&product);
```
The `env::commit` function is used to commit public results to the [journal].
Once committed to the journal, anyone with the [receipt] can read this value.

Now you should be able to confirm your work again with `cargo run --release`.
Once more, the program won't do anything, but it should run successfully and build with a single warning about `from_slice` being unused.

## Step 5 (Host): Generate a receipt and read its journal contents

For this step, we return to the main file for the host driver program at `factors/host/src/main.rs`, which currently has a placeholder comment asking to fill in with code for handling the [receipt]:

```rust
    // TODO: Implement code for transmitting or serializing the receipt for
    // other parties to verify here
```

In a real-world scenario, we'd want to hand the [receipt] to someone else, but reading it ourselves will be a nice way to check our project is working as expected.
So, let's extract the [journal]'s contents by replacing the "`TODO`" in the above code snippet with the following lines.

```rust
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

[install Rust]: https://www.rust-lang.org/tools/install
[`cargo risczero` tool]: https://crates.io/crates/cargo-risczero
[examples directory]: https://github.com/risc0/risc0/tree/main/examples
[Getting Started resources]: https://www.risczero.com/docs/
[Discord]: https://discord.com/invite/risczero
[issue]: https://github.com/risc0/risc0/issues
[receipt]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/receipt/struct.Receipt.html
[journal]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/receipt/struct.Receipt.html#structfield.journal
