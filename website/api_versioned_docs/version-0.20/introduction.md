---
slug: /
---

# Introduction

Welcome to the [RISC Zero] documentation! This site contains documentation for:

- **[Bonsai]**: A software development stack that allows on-chain and off-chain
  applications to request and receive proofs from our zkVM.

- **[The RISC Zero zkVM][zkVM]**: A high-performance tool for proving correct
  execution of arbitrary code.

- **[The RISC Zero Proof System][proof-system]**: The cryptographic techniques
  underlying the zkVM.

We also have reference documentation for our Rust code, which can be found at
[https://docs.rs/risc0-zkvm/][risc0-zkvm] for the `risc0-zkvm` crate. For our
other Rust crates, links to their reference docs can be found in [this
list][rust-libraries].

---

## What is RISC Zero?

[RISC Zero] is a [startup] creating the infrastructure & tooling necessary for
developers around the globe to build software that leverages ZK technology.

ZK technology is staged to re-shape the way we interact digitally. Historically,
the only method for confirming the correct execution of a software application
was through redundant computation. ZK introduces a new option: **verifiable
computation**.

It's now possible to pair a program's output with a self-certifying _receipt_,
allowing a skeptical third party to verify correct execution — and the verifier
doesn't need to repeat the original computation or even see the inputs to the
program!

Verifiable computation is a game changer for the resilience and economics of
operating the computing infrastructure we all rely on. It creates a number of
emergent use cases which we are excited to enable. Key among these use cases
are:

- [zk coprocessors], which enable on-chain applications to reduce gas costs by
  moving the complex part of their application logic off-chain
- blockchain infrastructure, including [our work with Optimism][optimism]

To enable ZK builders to thrive, we're working on two core products: the [zkVM]
and [Bonsai].

## Bonsai

[Bonsai] is a proving service that allows on-chain and off-chain applications to
request and receive [zkVM] proofs.

Bonsai is a general purpose zero-knowledge proving service that allows for any
chain, any protocol, and any application to take advantage of ZK proofs. It is
massively parallel, programmable, and performant.

Bonsai lets you integrate zero-knowledge proofs directly into any smart
contracts without the need for custom circuits. This allows for ZK to be
integrated directly into dApps on any EVM chain, with the potential to support
any other ecosystem.

Our zkVM is the foundation of Bonsai and enables widespread language
compatibility with support for provable Rust code and the potential for
zero-knowledge provable code in any language that compiles to RISC-V like C++,
Rust, Go, and more. With a combination of recursive proofs, a bespoke circuit
compiler, state continuations, and continuous improvements to the proving
algorithm, Bonsai enables anyone to generate highly performant ZK proofs for a
variety of applications.

Read more on Bonsai [here][Bonsai].

## The RISC Zero zkVM

The RISC Zero [zkVM] can prove the correct execution of arbitrary code, allowing
developers to build ZK applications in mature languages like Rust and C++. This
release marked a major breakthrough in enabling ZK software development: the
zkVM made it possible to build a ZK application _without having to build a
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

Given the ease of development and the performance, the zkVM is the clear choice
for your ZK needs.

## Connect with us

If you want to report a bug or contribute to our code, you can do so on
[GitHub][risc0-repo].

You're welcome to join [our Discord community][discord] to discuss RISC Zero,
ask questions, and see how other people use RISC Zero!

Follow us on [Twitter] and [YouTube], and [sign up for our mailing
list][mailing-list] to get our latest announcements.

[Bonsai]: ./bonsai/bonsai-overview.md
[chess]: https://github.com/risc0/risc0/tree/release-0.20/examples/chess
[continuations]: https://risczero.com/news/continuations
[crate-validation]: https://reports.risczero.com/crates-validation
[discord]: https://discord.gg/risczero
[ecdsa]: https://github.com/risc0/risc0/tree/release-0.20/examples/ecdsa
[JSON]: https://github.com/risc0/risc0/tree/release-0.20/examples/json
[mailing-list]: https://fmree464va4.typeform.com/to/X3KJB85v
[optimism]: https://www.theblock.co/post/240929/optimism-zk-proof-proposals
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
[zk coprocessors]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[zkpoex]: https://risczero.com/news/zkpoex
[zkVM]: ./zkvm/zkvm_overview.md
