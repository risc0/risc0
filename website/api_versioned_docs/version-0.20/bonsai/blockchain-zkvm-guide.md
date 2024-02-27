# A Blockchain Developer's Guide to the zkVM

<!-- TODO(scratch#231): Update this document and "RISC Zero on Ethereum" to improve and consolidate -->

In order to prove code using RISC Zero, you need to write the code you want proven.
That is, you'll need to write a [guest program][term-guest-program] for the [zkVM][term-zkvm].

**This guide will focus on the core techniques a blockchain developer will need to write zkVM code to prove in [Bonsai].**

## Getting Started

The [RISC Zero Foundry Template][foundry-template] provides a template and instructions for developing your application.
You can get started right away by cloning the template and following the instructions there.

## Writing Rust code

[Guest programs][term-guest-program] are written in [Rust]. If you're new to [Rust], we recommend their [official learning resources][rust-learn].

When creating your [guest program][term-guest-program], you can write [Rust] code in the usual way, including using `std` and importing packages others have written.
We provide some additional zkVM-specific functionality, most notably `env::read_slice` for reading the input data and `env::commit_slice` for [committing] public results to the [journal] (see below).

This is, in principle, everything you need to know to use the zkVM with Bonsai: write [Rust] code that does whatever it is you want proven, and use the `env` functions to read inputs from, and commit results to, your smart contract. But if you continue reading we'll provide further orientation to the role of the zkVM and some useful tips and tricks for writing zkVM code.

## Retrieving and handling zkVM receipts

Once Bonsai proves your code, it will give you access to this proof with a [receipt]. Much like a paper receipt, the zkVM [receipt] can be handed to someone else to demonstrate that a program was executed with integrity. The [receipt] also contains any computational results we've chosen to share in its [journal], so we know our results came from the faithfully executed program.

## I/O between the EVM blockchain and the zkVM

The zkVM doesn't natively speak EVM bytecode, so you'll want to decode and encode your smart contract inputs and outputs inside of your provable zkVM guest program. This will allow you to store off-chain program inputs in regular Rust variables and use them during computation. Because your shared outputs will be encoded back into EVM bytecode, you'll be able to read results back into app contracts.

Because the zkVM supports general-purpose instructions, you can use standard Rust libraries including [alloy], a Rust library for interacting with Ethereum.

## Why am I seeing errors?

We have an [FAQ](/faq) that discusses some frequently encountered problems. You can also ask us questions on [Discord].

## Diving deeper

We have [extensive resources](../zkvm/zkvm_overview.md) on writing zkVM code.

Many of these resources assume you are developing without the aid of Bonsai. Here are some differences you might encounter when reading these docs:

- zkVM docs frequently refer to the [guest] and [host]. With Bonsai, you only write code for the [guest]; Bonsai itself runs the [host]. A partial exception is providing inputs and receiving the [receipt], which is handled by the [host] without Bonsai, and by the off-chain component of your app (e.g. a dApp client or server) when using Bonsai.
- You might see our zkVM documentation refer to sessions, and segments. These code-level concepts are related to [continuations](https://www.risczero.com/news/continuations), a feature that lets us design our zkVM program proof work to be parallelizable and not limited by the size of the program to be proven. Bonsai takes advantage of this feature to parallelize proofs about off-chain computation. If you're reading about these in zkVM documentation, you're almost certainly looking at host-side details that you don't need in order to write provable code.

[Bonsai]: bonsai-overview.md
[Discord]: https://discord.gg/risczero
[Rust]: https://www.rust-lang.org/
[alloy]: https://github.com/alloy-rs
[committing]: /terminology#commit
[foundry-template]: https://github.com/risc0/bonsai-foundry-template
[guest]: /terminology#guest
[host]: /terminology#host
[journal]: /terminology#journal
[receipt]: /terminology#receipt
[rust-learn]: https://www.rust-lang.org/learn
[term-guest-program]: /terminology#guest-program
[term-zkvm]: /terminology#zero-knowledge-virtual-machine-zkvm
