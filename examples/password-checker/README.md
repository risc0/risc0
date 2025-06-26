# `password_checker`

This simple password checker is implemented in Rust. The program is implemented in two parts: a policy checker (that runs in the zkVM) and a host driver (an ordinary command-line program that uses the zkVM to run the policy checker).

The policy checker accepts a password string and a salt from the host driver and checks the validity of the password. A password validity-checking function then examines the password and panics if criteria are not met. If the password meets validity criteria, execution proceeds and the zkVM appends a hash of the salted password to the journal. The journal is a readable record of all values committed by code in the zkVM; it is attached to the receipt (a record of correct execution).

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Why use zkVM to run this?

Our goal is to run our own password check locally without having to share our password directly with a recipient, preferring instead to share only a PBKDF2 SHA-256 password hash.
Because the validity-checking and hashing functionality runs on the zkVM, it generates a receipt that identifies which binary was executed (via the image ID), associates shared results with this particular execution (via the journal), and confirms its own integrity (via the cryptographic seal).

## Project organization

The main program that calls a method in the guest zkVM is in [src/main.rs](src/main.rs).
The code that runs inside the zkVM is in [`methods/guest/src/main.rs`](methods/guest/src/main.rs).
The rest of the project is build support.

For the main RISC Zero project, see [here](https://github.com/risc0/risc0).

## And now, some fine print

This is example code meant to illustrate the fundamentals of programming with the zkVM. The password policy (and broader protocol) implemented here is intended for educational purposes only.

## Video Tutorial

For a walk-through of the fundamentals of this example, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=Yg_BGqj_6lg\&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5\&index=5).

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
