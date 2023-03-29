# ZK Checkmate

Proves that a chess position has a checkmate without revealing what that checkmate is.

Takes a move that is kept private and an initial board state that is published to the [journal](https://www.risczero.com/docs/explainers/zkvm/). There are default values for these, but you can also pass in an alternative move and/or board state as command line arguments. The move is in SAN format and the board state is in FEN format.

## Quick Start

First, make sure [rustup](https://rustup.rs) is installed. This project uses a [nightly](https://doc.rust-lang.org/book/appendix-07-nightly-rust.html) version of [Rust](https://doc.rust-lang.org/book/ch01-01-installation.html). The [`rust-toolchain`](rust-toolchain) file will be used by `cargo` to automatically install the correct version.

To build all methods and create a zero-knowledge proof that the position defined [here](https://github.com/risc0/risc0/blob/main/examples/chess/src/main.rs#L28) includes a mate-in-one, run the following command from this directory:

```
cargo run -r
```

## About the code
The [guest code](https://github.com/risc0/risc0-rust-examples/blob/main/chess/methods/guest/src/bin/checkmate.rs) generates the `pos` that results from a given `move` on a given `board`, and then checks that `pos` is checkmate.
The [host code](https://github.com/risc0/risc0/blob/main/examples/chess/methods/guest/src/main.rs) supplies the `move` and the `board`.

## Video Tutorial

For a walk-through of this example, check out this [excerpt from our workshop at ZK HACK III](https://www.youtube.com/watch?v=vxqxRiTXGBI&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=9).
