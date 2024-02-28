# RISC Zero on Ethereum

_Warning: The zkVM and Bonsai are still in development. Do not use in production._

Prove computation with the [RISC Zero zkVM](../zkvm) and verify the results in your Ethereum contract.

The zkVM and Bonsai together can act as a [coprocessor][coprocessor-article] to the smart contract application.
This unlocks powerful new applications on Ethereum that offload computationally intensive (i.e. gas expensive) and difficult to implement (e.g. ed25519 signature verification, or HTML parsing) functions to the zkVM.

## Getting Started

The [RISC Zero Foundry Template][foundry-template] provides a template and instructions for developing your application.
You can get started right away by cloning the template and following the instructions there.

## Overview

Below is a diagram and overview of a typical application with RISC Zero on Ethereum, utilizing Bonsai proving.

![RISC Zero on Ethereum interactions diagram](/img/risc0-ethereum-interaction.png)

1. Run your application logic in the zkVM. The off-chain component of your app (e.g. server or dApp client) sends a proof request to the Bonsai proving service.
2. Bonsai generates the program result, written to the [journal][term-journal], and a SNARK proof of its correctness.
3. The app submits this proof and journal on-chain to your app contract for validation.
4. Your app contract calls the [RISC Zero verifier contract][verifier-contract] to validate the proof. If the verification is successful, the journal is deemed trustworthy and can be safely used.

[coprocessor-article]: https://www.risczero.com/news/a-guide-to-zk-coprocessors-for-scalability
[foundry-template]: https://github.com/risc0/bonsai-foundry-template
[term-journal]: /terminology#journal
[verifier-contract]: /api/blockchain-integration/contracts/verifier.md
