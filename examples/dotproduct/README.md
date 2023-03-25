# Risc-0 Dotproduct example
An example, computing the dotproduct of two 2-dimensional vectors with Risc0. To run the code, you'll need a working
rust installation, then just `cargo run`.

Main tips:
- Unless your inputs are simple, write a wrapper `Inputs` or `Args` struct in a separate `core` library, and use the library from your `methods` and `dotproduct` (or whatever your binary crate is called) to serialize and deserialize the argument. This sidesteps some issues with the Risc-0 glue code, which tends to produce difficult to read errors.
- Build times tend to be long. If you're just testing your `core` or `methods` directory, build and test from those
  directories to shorten your iteration loop.

