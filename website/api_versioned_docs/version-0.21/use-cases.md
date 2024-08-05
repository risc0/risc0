# Use Cases

Verifiable computation is a game changer for the resilience and economics of
operating the computing infrastructure we all rely on. It creates a number of
emergent use cases which we are excited to enable. Key among these are:

- [ZK Coprocessors][zk-coprocessors], which enable blockchain applications to reduce gas costs by
  moving the expensive part of their application logic off-chain
- Optimistic rollups with ZK fraud proofs, including [our work with Optimism][optimism]

The RISC Zero [zkVM] can prove the correct execution of arbitrary code, allowing
developers to build ZK applications in mature languages like Rust and C++. The release
of the RISC Zero zkVM marked a major breakthrough in enabling ZK software development:
the zkVM made it possible to build a ZK application _without having to build a
circuit_ and _without writing in a custom language_.

By allowing developers to build in Rust and leverage the maturity of the Rust
ecosystem, the zkVM has made it possible for developers to quickly build
meaningful ZK applications, with no background in advanced mathematics or
cryptography.

We've built a number of applications and primitives showcasing these capabilies, including:

- **[Zeth]**: prove the correct construction of an entire Ethereum block or an entire Optimism block
- **[Bonsai Pay]**: send Ethereum to someone's gmail address
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

**Ready to start building?** <br/>
Check out our [Getting Started] page.

[Bonsai Pay]: https://risczero.com/news/bonsai-pay
[chess]: https://github.com/risc0/risc0/tree/release-0.21/examples/chess
[continuations]: https://risczero.com/news/continuations
[crate-validation]: https://reports.risczero.com/crates-validation
[ecdsa]: https://github.com/risc0/risc0/tree/release-0.21/examples/ecdsa
[Getting Started]: ./getting-started.md
[JSON]: https://github.com/risc0/risc0/tree/release-0.21/examples/json
[optimism]: https://www.theblock.co/post/240929/optimism-zk-proof-proposals
[performance]: ./zkvm/benchmarks.md
[waldo]: https://risczero.com/news/waldo
[Zeth]: https://risczero.com/news/zeth-release
[zk-coprocessors]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[zkpoex]: https://risczero.com/news/zkpoex
[zkVM]: ./zkvm/zkvm_overview.md
