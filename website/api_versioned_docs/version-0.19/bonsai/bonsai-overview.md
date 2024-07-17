---
slug: ./
---

# Bonsai Overview

Bonsai enables boundless computation on any blockchain.
With Bonsai, instead of generating proofs on your own hardware, you can upload the program you need proven and request that Bonsai generates proofs for you as needed.

Bonsai is highly parallelized, highly performant and can horizontally scale. To get a taste of what you can do with Bonsai, check out [Zeth], our [Governance Showcase], [Bonsai Pay], and our twitter thread about using [Bonsai as a zk coprocessor].

Whether you're looking to take heavy computations off-chain or need to generate proofs for your trustless, verifiable software, Bonsai can help.
Check out our [Bonsai Quick Start] page, and start building!

**Please note that Bonsai is still in early development. <br/>
[Request access here], and do not use Bonsai in production.**

![Bonsai overview](/img/bonsai_architecture.png)

The diagram above shows a simplified overview of Bonsai.
As a developer using Bonsai you'll write your [guest program] that can be used as part of:

- A trustless, verifiable software
- Some business logic of a smart contract

As a result, you'll get back a [receipt] proving the execution of your [guest program] as well as its public result in a [journal].

_Note that there are various ways to interact with Bonsai, outlined on the [Bonsai Quick Start] page._

## How do I interact with Bonsai directly?

![Bonsai Ethereum](/img/bonsai_zkvm.png)

If you build a project with the [`cargo risczero`] tool, you can set environment variables to enable remote proving using Bonsai. Namely, when running your project, set `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>`.

Alternatively, you can use the [Bonsai SDK] or the [Bonsai REST API].

## How do I interact with Bonsai from Ethereum?

![Bonsai Ethereum](/img/bonsai_ethereum.png)

The picture above shows a simplified overview of how users can integrate Bonsai into their Ethereum smart contracts:

1. You can send proof requests to Bonsai via an _off-chain_ REST API interface or _on-chain_ via a smart contract.
2. The `Bonsai Relayer` will forward your proof request to the Bonsai proving service.
3. Bonsai will use the RISC Zero zkVM to generate a proof, and send the proof back to your contract via the `Bonsai Relay Contract`.

## How do I interact with Bonsai from other chains?

Stay tuned!

## Bonsai Building Blocks

### 1. The RISC Zero zkVM: the proof engine behind Bonsai

_Status: [Available and open source](https://github.com/risc0/risc0)_

Under the hood, Bonsai uses the RISC Zero zkVM to prove your programs. With the zkVM, you have access to recursive proofs, proofs composition, a general-purpose circuit (with a bespoke circuit compiler), state continuations, and continuous improvements to the proving algorithm.

### 2. The Bonsai proving service, powered by the zkVM

_Status: Pre-Alpha_

The Bonsai proving service can be used standalone or directly integrated with smart contracts and blockchains. If you're interested in Bonsai, learn more in our [litepaper] and [talks](https://youtu.be/nVAs2i-_Iyo?t=3044).

### 3. Bonsai Relayer and Relay Contract: Connecting off-chain proofs and on-chain applications

_Status: Pre-Alpha, [documentation](./bonsai-on-eth.md) and [Bonsai Foundry template](https://github.com/risc0/bonsai-foundry-template) available_

The `Bonsai Relayer` and the `Bonsay Relay Contract` let your Ethereum dApps connect to Bonsai. Smart contract developers can call our proving service off-chain via a REST API or through an on-chain relay contract connected to the Bonsai proving service.

## Where we're headed

We're building technology that allows anyone to generate highly performant zero-knowledge proofs for a variety of applications. We want to make zero-knowledge proof integration into Ethereum, L1 blockchains, Cosmos app chains, L2 rollups, and dApps possible with minimal development effort. To learn more, read our [litepaper].

[litepaper]: /litepaper
[Request access here]: https://bonsai.xyz/apply
[`cargo risczero`]: https://crates.io/crates/cargo-risczero
[Bonsai SDK]: https://crates.io/crates/bonsai-sdk
[Bonsai REST API]: https://api.bonsai.xyz/swagger-ui/
[Bonsai Quick Start]: quickstart.md
[Bonsai as a zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[Governance Showcase]: https://github.com/risc0/risc0/tree/release-0.19/bonsai/examples/governance#readme
[Zeth]: https://www.risczero.com/news/zeth-release
[guest program]: /terminology#guest-program
[receipt]: /terminology#receipt
[journal]: /terminology#journal
[Bonsai Pay]: https://www.risczero.com/news/bonsai-pay
