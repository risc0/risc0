# Bevy Game Engine Example
This code demonstrates a minimal example of how to use the [bevy] game engine inside the RISC Zero [zkVM].

## Quick Start
First, [install Rust] if you don't already have it.
Then, run the example with:
```
  cargo run --release
```

## Use Cases
By using this demo as part of a [Bonsai application], you could build an app where on-chain payment depends on off-chain gameplay.
To learn more about this use case, check out our Twitter thread about using Bonsai as a [zk coprocessor].

To link gameplay to a particular player, you may want to pair this demo with the [ECDSA] demo, which would allow a player to sign their moves.

## Project Organization
zkVM applications are organized into a [host program] and a [guest program].
The host program can be found in [`src/main.rs`](src/main.rs) and the guest program can be found in [`methods/guest/src/main.rs`](methods/guest/src/main.rs).

The [host] first [executes] the guest program and then [proves the execution] to construct a [receipt].
The receipt can be passed to a third party, who can examine the [journal] to check the program's outputs and can [verify] the [receipt] to ensure the integrity of the [guest program]'s execution.

## More Resources
For more information about building, running, and testing zkVM applications, see our [developer docs].

[bevy]: https://bevyengine.org/
[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[zkVM]: https://dev.risczero.com/terminology#zero-knowledge-virtual-machine-zkvm
[host]: https://dev.risczero.com/terminology#host
[executes]: https://dev.risczero.com/terminology#execute
[guest program]: https://dev.risczero.com/terminology#guest-program
[host program]: https://dev.risczero.com/terminology#host-program
[proves the execution]: https://dev.risczero.com/terminology#prove
[receipt]: https://dev.risczero.com/terminology#receipt
[verify]: https://dev.risczero.com/terminology#verify
[journal]: https://dev.risczero.com/terminology#journal
[developer docs]: https://dev.risczero.com/zkvm
[Bonsai application]: https://dev.bonsai.xyz
[zk coprocessor]: https://twitter.com/RiscZero/status/1677316664772132864
[src/main.rs]: /src/main.rs
[ECDSA]: https://github.com/risc0/risc0/tree/main/examples/ecdsa
