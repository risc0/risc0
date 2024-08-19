# Bevy Game Engine Example

This code demonstrates a minimal example of how to use the [bevy] game engine inside the RISC Zero [zkVM].

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Use Cases

By using this demo as part of a [Bonsai application], you could build an app where on-chain payment depends on off-chain gameplay.
To learn more about this use case, check out our blog post about using Bonsai as a [zk coprocessor].

To link gameplay to a particular player, you may want to pair this demo with the [ECDSA] demo, which would allow a player to sign their moves.

## Project Organization

zkVM applications are organized into a [host program] and a [guest program].
The host program can be found in [`src/main.rs`] and the guest program can be found in [`methods/guest/src/main.rs`].

The [host] first [executes] the guest program and then [proves the execution] to construct a [receipt].
The receipt can be passed to a third party, who can examine the [journal] to check the program's outputs and can [verify] the [receipt] to ensure the integrity of the [guest program]'s execution.

## More Resources

For more information about building, running, and testing zkVM applications, see our [developer docs].

[`methods/guest/src/main.rs`]: methods/guest/src/main.rs
[`src/main.rs`]: src/main.rs
[bevy]: https://bevyengine.org/
[Bonsai application]: https://dev.bonsai.xyz
[developer docs]: https://dev.risczero.com/zkvm
[ECDSA]: https://github.com/risc0/risc0/tree/main/examples/ecdsa
[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[executes]: https://dev.risczero.com/terminology#execute
[guest program]: https://dev.risczero.com/terminology#guest-program
[host]: https://dev.risczero.com/terminology#host
[host program]: https://dev.risczero.com/terminology#host-program
[journal]: https://dev.risczero.com/terminology#journal
[proves the execution]: https://dev.risczero.com/terminology#prove
[receipt]: https://dev.risczero.com/terminology#receipt
[verify]: https://dev.risczero.com/terminology#verify
[zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[zkVM]: https://dev.risczero.com/zkvm
