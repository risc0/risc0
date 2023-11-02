# A Blockchain Developer's Guide to the zkVM

_(To start building on [Bonsai], check out the [Bonsai Quick Start] page.)_

In order to prove code using Bonsai, you need to write the code you want proven. That is, you'll need to write a [guest program] for the [zkVM](/terminology#zero-knowledge-virtual-machine-zkvm). This guide will focus on the core techniques a blockchain developer will need to write zkVM code to prove in Bonsai. We have [a number of guides](../zkvm) for developing for the zkVM more generally if you want to dive deeper!

## The role of the zkVM in Bonsai

![Bonsai ETH Relay overview](/img/eth-relay-diagram.jpg)

<!-- TODO: Modify the diagram to highlight the right zkVM portion. -->

The zkVM is used as an internal component of Bonsai. It is what runs your program off-chain using inputs from your smart contract call, and it is what [proves] your code was [executed] in a way anyone can [verify]. Bonsai runs most of the zkVM for you: all you need to provide is the code you want proven, which we call the zkVM [guest program].

## Writing Rust code

[Guest programs] are written in [Rust]. If you're new to [Rust], we recommend their [official learning resources](https://www.rust-lang.org/learn).

When creating your [guest program], you can write [Rust] code in the usual way, including importing packages others have written. We do provide some additional zkVM-specific functionality, most notably `env::read_slice` for reading the input data sent from your smart contract and `env::commit_slice` for [committing] public results to the [journal] (see below).

This is, in principle, everything you need to know to use the zkVM with Bonsai: write [Rust] code that does whatever it is you want proven, and use the `env` functions to read inputs from, and commit results to, your smart contract. But if you continue reading we'll provide further orientation to the role of the zkVM and some useful tips and tricks for writing zkVM code.

## Retrieving and handling zkVM receipts

Once Bonsai proves your code, it will give you access to this proof with a [receipt]. Much like a paper receipt, the zkVM [receipt] can be handed to someone else to demonstrate that a program was executed with integrity. The [receipt] also contains any computational results we've chosen to share in its [journal], so we know our results came from the faithfully executed program.

## I/O between the EVM blockchain and the zkVM

The zkVM doesn't natively speak EVM bytecode, so you'll want to decode and encode your smart contract inputs and outputs inside of your provable zkVM guest program. This will allow you to store off-chain program inputs in regular Rust variables and use them during computation. Because your shared outputs will be encoded back into EVM bytecode, you'll be able to read results back into app contracts.

Because the zkVM supports general-purpose instructions, you can use standard Rust libraries including [ethabi](https://github.com/rust-ethereum/ethabi), a Rust library for decoding and encoding EVM bytecode.

## Why am I seeing errors?

We have an [FAQ](/faq) that discusses some frequently encountered problems. You can also ask us questions on [Discord].

## Diving deeper

We have [extensive resources](../zkvm) on writing zkVM code. Many of these resources assume you are developing without the aid of Bonsai. Here are some differences you might encounter when reading these docs:

- zkVM docs frequently refer to the [guest] and [host]. With Bonsai, you only write code for the [guest]; Bonsai itself runs the [host]. A partial exception is providing inputs and receiving the [receipt], which is handled by the [host] without Bonsai, whereas with the Bonsai ETH Relay your smart contract must handle these duties.
- You might see our zkVM documentation refer to executors, sessions, and segments. These code-level concepts are related to [continuations](https://www.risczero.com/news/continuations), a feature that lets us design our zkVM program proof work to be parallelizable and not limited by the size of the program to be proven. Bonsai takes advantage of this feature to parallelize proofs about off-chain computation. If you're reading about these in zkVM documentation, you're almost certainly looking at host-side details that you don't need in order to write provable code.

[Bonsai]: ../bonsai/
[Rust]: https://www.rust-lang.org/
[Bonsai Quick Start]: quickstart.md
[Discord]: https://discord.gg/risczero
[guest program]: /terminology#guest-program
[Guest programs]: /terminology#guest-program
[proves]: /terminology#validity-proof
[executed]: /terminology#execute
[verify]: /terminology#verify
[guest]: /terminology#guest
[host]: /terminology#host
[receipt]: /terminology#receipt
[committing]: /terminology#commit
[journal]: /terminology#journal
