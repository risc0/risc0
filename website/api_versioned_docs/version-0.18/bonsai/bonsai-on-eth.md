# Bonsai on Ethereum

_Warning: Bonsai is still in early development. Do not use in production._

Bonsai can be used as a [zk coprocessor] for Ethereum, allowing you to request and receive [verified proofs] directly from your smart contract.

At a high level, here's how it works:

![Bonsai ETH Relay overview](/img/eth-relay-diagram.jpg)

<!-- TODO: Highlight the relay sections of this diagram -->

Our Bonsai-ETH Relay acts as a middle-man between your app contract and the Bonsai proving service. In order to use the Bonsai ETH Relay, dApp developers must have completed the following steps:

1. Deployed a [smart contract] on chain that calls the relay contract
2. Uploaded a compiled [program] for the zkVM to the Bonsai proving service

## Getting Started

The [Bonsai Foundry Template] is the best place to get started building Bonsai applications for Ethereum.
You may also want to check out our [Bonsai Quick Start](quickstart.md) page.

[verified proofs]: https://risczero.com/news/on-chain-verification
[zk coprocessor]: https://www.risczero.com/blog/a-guide-to-zk-coprocessors-for-scalability
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
[smart contract]: https://github.com/risc0/bonsai-foundry-template/tree/main/contracts
[program]: https://github.com/risc0/bonsai-foundry-template/tree/main/methods/guest/src/bin
