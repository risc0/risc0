# Examples

- **[Hello World]**: a recommended place to start. Prove a number is composite, and you know its factors without revealing them
- **[JSON]**: prove the contents of some entry in a JSON file, while keeping the rest of the data private
- **[Where's Waldo]**: prove that Waldo appears in a JPG file, while keeping the rest of the image private, additionally, there is [Where's Waldo blog]
- **[ZK Checkmate]**: prove that you see a mate-in-one, without revealing the winning move
- **[ZK Proof of Exploit]**: prove that you _could_ exploit an Ethereum account, without revealing the exploit
- **[ECDSA signature verification]**: prove the validity of an ECDSA signature
- **[zkEVM]**: demo of running EVM engine on the Risc Zero zkVM

## Running the examples

The examples listed above and others can be found in RISC Zero's repository under [/examples].
Unless otherwise noted in their own READMEs, the examples can be run following the instructions below.

### Install dependencies

First, ensure that you have all RISC Zero tools installed. See [installation instructions] for more information.

### Check out the correct version of the example

The compilation of the examples is tied to the version installed, so it is important to check out the correct version that corresponds to the local one. To do so, first get the available version in your system:

```bash
cargo risczero --version
```

Then check out the corresponding branch of the example:

```bash
git checkout <version> # e.g. v0.19.1
```

### Run the example

Finally, run the example with:

```bash
cargo run --release
```

[Hello World]: https://github.com/risc0/risc0/tree/main/examples/hello-world
[JSON]: https://github.com/risc0/risc0/tree/main/examples/json
[Where's Waldo]: https://github.com/risc0/risc0/tree/main/examples/waldo
[Where's Waldo blog]: https://risczero.com/news/waldo
[ZK Checkmate]: https://github.com/risc0/risc0/tree/main/examples/chess
[ZK Proof of Exploit]: https://risczero.com/news/zkpoex
[ECDSA signature verification]: https://github.com/risc0/risc0/tree/main/examples/ecdsa
[zkEVM]: https://github.com/risc0/risc0/tree/main/examples/zkevm-demo
[/examples]: https://github.com/risc0/risc0/tree/main/examples
[installation instructions]: install.md
