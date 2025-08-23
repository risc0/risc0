# C-KZG Crate Test

This code demonstrates that Ethereum's c-kzg-4844 crate runs on the zkVM guest. Since verification takes about 100 million segments, this only runs the executor.

Something like this crate would normally be implemented as a test case in the risc0 repo. However, this crate fails to build when placed in complex workspace or directory structure. The test is placed here until we find a way to use it inside the risc0/zkvm/methods/ directory.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

## Project Organization

zkVM applications are organized into a [host program] and a [guest program].
The host program can be found in [`src/main.rs`], and the guest program can be found in [`methods/guest/src/main.rs`].

The [host] [executes] the guest program. This example does not produce a receipt and is intended as a test to ensure that this guest code runs without panicking.

## More Resources

- For a video walk-through of this example, check out this [excerpt from our workshop at ZK HACK III].
- For more information about building, running, and testing zkVM applications, see our [developer docs].

[`methods/guest/src/main.rs`]: methods/guest/src/main.rs
[`src/main.rs`]: src/main.rs
[developer docs]: https://dev.risczero.com
[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples
[excerpt from our workshop at ZK HACK III]: https://www.youtube.com/watch?v=vxqxRiTXGBI&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=9
[executes]: https://dev.risczero.com/terminology#execute
[guest program]: https://dev.risczero.com/terminology#guest-program
[host]: https://dev.risczero.com/terminology#host
[host program]: https://dev.risczero.com/terminology#host-program
