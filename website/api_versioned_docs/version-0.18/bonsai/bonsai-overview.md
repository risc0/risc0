---
slug: ./
---

# Bonsai Overview

Bonsai enables boundless computation on any blockchain.
With Bonsai, instead of generating proofs on your own hardware, you can upload the program you need proven and request that Bonsai generates proofs for you as needed.

Bonsai is highly parallelized and highly performant. To get a taste of what you can do with Bonsai, check out our [Governance Showcase], the [Bonfire Wallet] demo from the Hash Cloak team, and our twitter thread about using [Bonsai as a zk coprocessor].

Whether you're looking to take heavy computations off-chain or need to generate proofs for your trustless, verifiable software, Bonsai can help.
Check out our [Bonsai Quick Start] page, and start building!

**Please note that Bonsai is still in early development. <br/>
[Request access here], and do not use Bonsai in production.**

![Bonsai ETH Relay overview](/img/eth-relay-diagram.jpg)

<!-- revise diagram with "you create"/"bonsai creates" colors -->

The diagram above shows how to use Bonsai via an Ethereum smart contract.
In this diagram, all you are responsible for as a developer using Bonsai are:

- The smart contract invoking Bonsai
- The smart contract handling Bonsai's results via callback
- The program you want Bonsai to prove

_Note that aside from the architecture shown above, there are various ways to interact with Bonsai, outlined on the [Bonsai Quick Start] page. This includes the option to use Bonsai outside of blockchain applications altogether._

## How do I interact with Bonsai directly?

If you build a project with the [`cargo risczero`] tool, you can set environment variables to enable remote proving using Bonsai. Namely, when running your project, set `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>`.

Alternatively, you can use the [Bonsai SDK] or the [Bonsai REST API].

## How do I interact with Bonsai from Ethereum?

The architecture pictured above shows how to call Bonsai via an Ethereum smart contract. This architecture involves three core components, the zkVM, the proving service, and the ETH relay.

1. You'll call the ETH relay via a smart contract.
2. The ETH relay will send a proof request to the proving service.
3. The proving service will use the zkVM to generate a proof, and send the proof back via the ETH Relay.

These three components are described in more detail below.

## How do I interact with Bonsai from other chains?

Stay tuned!

## Bonsai Building Blocks

### 1. The RISC Zero zkVM: the proof engine behind Bonsai

_Status: [Available and open source](https://github.com/risc0/risc0)_

Under the hood, Bonsai uses the RISC Zero zkVM to prove your programs. With the zkVM, you have access to recursive proofs, a general-purpose circuit (with a bespoke circuit compiler), state continuations, and continuous improvements to the proving algorithm.

### 2. The Bonsai proving service, powered by the zkVM

_Status: Pre-Alpha_

The Bonsai proving service can be used standalone or directly integrated with smart contracts and blockchains. If you're interested in Bonsai, learn more in our [litepaper] and [talks](https://youtu.be/nVAs2i-_Iyo?t=3044).

### 3. Bonsai ETH Relay: Connecting off-chain proofs and on-chain applications

_Status: Pre-Alpha, [documentation](bonsai-on-eth.md) and [Bonsai Foundry template](https://github.com/risc0/bonsai-foundry-template) available_

The Bonsai ETH Relay connects your Ethereum dApps to Bonsai. Smart contract developers can call our proving service through an on-chain relay contract connected to the Bonsai proving service. If you'd prefer to engage with Bonsai proving service directly, we'll be rolling out the means to do so in the near future.

## Where we're headed

We're building technology that allows anyone to generate highly performant zero-knowledge proofs for a variety of applications. We want to make zero-knowledge proof integration into Ethereum, L1 blockchains, Cosmos app chains, L2 rollups, and dApps possible with minimal development effort. To learn more, read our [litepaper].

[waitlist]: https://bonsai.xyz/apply
[litepaper]: /litepaper
[zkVM]: ../zkvm/
[Request access here]: https://bonsai.xyz/apply
[`cargo risczero`]: https://crates.io/crates/cargo-risczero
[Bonsai SDK]: https://crates.io/crates/bonsai-sdk
[Bonsai REST API]: https://api.bonsai.xyz/swagger-ui/
[Bonsai Quick Start]: ../bonsai/quickstart.md
[Bonsai as a zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[Bonfire Wallet]: https://ethglobal.com/showcase/bonfire-wallet-n1dzp
[Governance Showcase]: https://github.com/risc0/risc0/tree/release-0.18/bonsai/examples/governance#readme
