# Examples

- **[Hello World][example-hello]**: a recommended place to start. Prove a number
  is composite, and you know its factors without revealing them
- **[JSON][example-json]**: prove the contents of some entry in a JSON file,
  while keeping the rest of the data private
- **[Where's Waldo][example-waldo]**: prove that Waldo appears in a JPG file,
  while keeping the rest of the image private, additionally, there is [Where's
  Waldo blog][waldo-blog]
- **[ZK Checkmate][example-chess]**: prove that you see a mate-in-one, without
  revealing the winning move
- **[ZK Proof of Exploit][zkpoex]∑**: prove that you _could_ exploit an Ethereum
  account, without revealing the exploit
- **[ECDSA signature verification][example-ecdsa]**: prove the validity of an
  ECDSA signature
- **[zkEVM][example-zkevm]**: demo of running EVM engine on the Risc Zero zkVM

## Running the examples

The examples listed above and others can be found in RISC Zero's repository
under [/examples][examples-dir]. Unless otherwise noted in their own READMEs,
the examples can be run following the instructions below.

### Install dependencies

First, ensure that you have all RISC Zero tools installed. See [installation
instructions][install] for more information.

### Check out the correct version of the example

The compilation of the examples is tied to the version installed, so it is
important to check out the correct version that corresponds to the local one. To
do so, first get the available version in your system:

```bash
cargo risczero --version
```

Then check out the corresponding branch of the example:

```bash
git checkout release-$VERSION # e.g. release-0.19
```

### Run the example

Finally, run the example with:

```bash
cargo run --release
```

[example-chess]: https://github.com/risc0/risc0/tree/release-0.20/examples/chess
[example-ecdsa]: https://github.com/risc0/risc0/tree/release-0.20/examples/ecdsa
[example-hello]: https://github.com/risc0/risc0/tree/release-0.20/examples/hello-world
[example-json]: https://github.com/risc0/risc0/tree/release-0.20/examples/json
[example-waldo]: https://github.com/risc0/risc0/tree/release-0.20/examples/waldo
[example-zkevm]: https://github.com/risc0/risc0/tree/release-0.20/examples/zkevm-demo
[examples-dir]: https://github.com/risc0/risc0/tree/release-0.20/examples
[install]: ./install.md
[waldo-blog]: https://risczero.com/news/waldo
[zkpoex]: https://risczero.com/news/zkpoex
