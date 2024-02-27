# Use Cases

Verifiable computation is a game changer for the resilience and economics of
operating the computing infrastructure we all rely on. It creates a number of
emergent use cases which we are excited to enable. Key among these use cases
are:

- [zk coprocessors], which enable on-chain applications to reduce gas costs by
  moving the complex part of their application logic off-chain
- blockchain infrastructure, including [our work with Optimism][optimism]

The RISC Zero [zkVM] can prove the correct execution of arbitrary code, allowing
developers to build ZK applications in mature languages like Rust and C++. The release
of the RISC Zero zkVM marked a major breakthrough in enabling ZK software development:
the zkVM made it possible to build a ZK application _without having to build a
circuit_ and _without writing in a custom language_.

By allowing developers to build in Rust and leverage the maturity of the Rust
ecosystem, the zkVM has made it possible for developers to quickly build
meaningful ZK applications, with no background in advanced mathematics or
cryptography.

These applications include:

- **[JSON]**: prove the contents of some entry in a JSON file, while keeping the
  rest of the data private
- **[Where's Waldo][waldo]**: prove that Waldo appears in a JPG file, while
  keeping the rest of the image private
- **[ZK Checkmate][chess]**: prove that you see a mate-in-one, without revealing
  the winning move
- **[ZK Proof of Exploit][zkpoex]**: prove that you _could_ exploit an Ethereum
  account, without revealing the exploit
- **[ECDSA signature verification][ecdsa]**: prove the validity of an ECDSA
  signature

These examples are all made possible by **leveraging a mature software
ecosystem**: over 70% of the [top 1000 Rust crates][crate-validation] work
out-of-the-box in the zkVM. Being able to import Rust crates is a game changer
for the ZK software world: projects that would take months or years to build on
other platforms can be solved trivially on our platform.

In addition to being far easier to build on, we're also delivering on
[performance]. The zkVM has GPU acceleration for CUDA and Metal, and with
[continuations] we've enabled parallel proving of large programs.

## Getting Started

To harness the power of ZK, you'll need to:

1. [Write an application for the RISC Zero zkVM][zkvm-quickstart].
2. [Generate proofs for your zkVM application][bonsai-quickstart].
3. [Integrate your proofs into on-chain applications][bonsai-on-eth].

[zkvm-quickstart]: ./zkvm/quickstart.md
[bonsai-quickstart]: ./generating-proofs/remote-proving.md
[bonsai-on-eth]: ./blockchain-integration/bonsai-on-eth.md
[Bonsai]: ./generating-proofs/remote-proving.md
[chess]: https://github.com/risc0/risc0/tree/main/examples/chess
[continuations]: https://risczero.com/news/continuations
[crate-validation]: https://risc0.github.io/ghpages/dev/crate-validation/index.html
[discord]: https://discord.gg/risczero
[ecdsa]: https://github.com/risc0/risc0/tree/main/examples/ecdsa
[JSON]: https://github.com/risc0/risc0/tree/main/examples/json
[mailing-list]: https://fmree464va4.typeform.com/to/X3KJB85v
[optimism]: https://www.theblock.co/post/240929/optimism-zk-proof-proposals?utm_source=twitter&utm_medium=social
[performance]: ./zkvm/benchmarks.md
[proof-system]: /proof-system
[RISC Zero]: https://risczero.com
[risc0-repo]: https://github.com/risc0/risc0
[risc0-zkvm]: https://docs.rs/risc0-zkvm
[rust-libraries]: https://github.com/risc0/risc0#rust-libraries
[startup]: https://risczero.com/news/series-a
[twitter]: https://twitter.com/risczero
[waldo]: https://risczero.com/news/waldo
[YouTube]: https://www.youtube.com/@risczero
[zk coprocessors]: https://twitter.com/RiscZero/status/1677316664772132864
[zkpoex]: https://risczero.com/news/zkpoex
[zkVM]: ./zkvm/zkvm_overview.md
