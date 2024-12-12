# ZK Checkmate

This code demonstrates a minimal example of how to use the RISC Zero [zkVM] to make ZK proofs about chess.

The demo uses the [shakmaty] crate to prove that a chess position has a checkmate without revealing what that checkmate is.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

Congratulations! You just constructed a zero-knowledge proof that includes a mate-in-one.

## Use Cases

By using this demo as part of a [Bonsai application], you could build an app where on-chain payment depends on off-chain activity.
For example, you might issue an on-chain award for the first person who can find a mate-in-one.

To learn more about this use case, check out our blog about using Bonsai as a [zk coprocessor].

## Project Organization

zkVM applications are organized into a [host program] and a [guest program].
The host program can be found in [`src/main.rs`][host code], and the guest program can be found in [`methods/guest/src/main.rs`][guest code].

The [host] first [executes] the guest program and then [proves the execution] to construct a [receipt].
The receipt can be passed to a third party, who can examine the [journal] to check the program's outputs and can [verify] the [receipt] to ensure the integrity of the [guest program]'s execution.

## Approach

This is a simple zkVM application that demonstrates how to use a Rust crate inside the [zkVM].
Here, we use the [shakmaty] crate, which makes it possible to handle chess notation and chess logic.
To learn more about using Rust crates inside the zkVM, check out our [Rust Resources] page.

The [guest code] generates the `pos` that results from a given `move` on a given `board`, and then checks that `pos` is checkmate.
The [host code] supplies the `move` and the `board`.

The [host code] supplies a move that the [guest code] keeps private and an initial board state that the [guest code] publishes to the [journal]. There are default values for these, but you can also pass in an alternative move and/or board state as command line arguments. The move is in SAN format and the board state is in FEN format.

The [guest code] checks that applying the move to the initial board state is legal and results in a checkmate. If not, the [guest code] asserts and no [journal] is produced.

## More Resources

- For a video walk-through of this example, check out this [excerpt from our workshop at ZK HACK III].
- For more information about building, running, and testing zkVM applications, see our [developer docs].

[Bonsai application]: https://dev.bonsai.xyz
[developer docs]: https://dev.risczero.com
[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[excerpt from our workshop at ZK HACK III]: https://www.youtube.com/watch?v=vxqxRiTXGBI&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=9
[executes]: https://dev.risczero.com/terminology#execute
[guest code]: methods/guest/src/main.rs
[guest program]: https://dev.risczero.com/terminology#guest-program
[host]: https://dev.risczero.com/terminology#host
[host code]: src/main.rs
[host program]: https://dev.risczero.com/terminology#host-program
[journal]: https://dev.risczero.com/terminology#journal
[proves the execution]: https://dev.risczero.com/terminology#prove
[receipt]: https://dev.risczero.com/terminology#receipt
[Rust Resources]: https://dev.risczero.com/api/zkvm/rust-resources
[shakmaty]: https://docs.rs/shakmaty/latest/shakmaty/
[verify]: https://dev.risczero.com/terminology#verify
[zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[zkVM]: https://dev.risczero.com/zkvm
