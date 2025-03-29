# Ethereum Examples

:::tip
The [risc0-ethereum][risc0-ethereum] repo is where you can find [blockchain examples][blockchain-examples], [verifier contracts][verifier-contracts] and [Steel][steel-src].
:::

While all of the [zkVM examples][zkvm-examples] can be run on Bonsai by [configuring Bonsai][remote-proving] as your remote prover, those examples do not interact with or are intended to interact with Ethereum or any other blockchain. The references below are examples of how Bonsai and the zkVM can be integrated with Ethereum.

### Foundry Template

The [RISC Zero Foundry Template][foundry-template] provides a minimal application that can act as a template for developing your application.

### Steel

[Steel][steel-repo] is a library for [view call proofs][steel-blog], which enables users to easily integrate claims about Ethereum state into zkVM applications.

### Zeth

[Zeth][zeth-repo] produces ZK validity proofs for Ethereum Virtual Machine blocks (EVM). This is accomplished by running [revm], a Rust implementation of the EVM in the zkVM. The end result is an open-source zkEVM with high code reuse and minute, not hour, proving times on Bonsai. For more info check out [Announcing Zeth: The first Type Zero zkEVM][zeth-article].

### DAO Governance Example

This [example app][governance-example] uses Bonsai as an Ethereum coprocessor. The protocol, based on the OpenZeppelin [Governor smart contract standard][governor-standard], batches signature verifications off-chain for a DAO governance vote. The end result is that in [\~160 lines of Rust][signature-aggregation], a gas savings of \~77% is achieved with significant room for optimizations.

[blockchain-examples]: https://github.com/risc0/risc0-ethereum/tree/release-2.0/examples
[foundry-template]: https://github.com/risc0/risc0-foundry-template
[governance-example]: https://github.com/risc0/risc0-ethereum/tree/release-2.0/examples/governance
[governor-standard]: https://docs.openzeppelin.com/contracts/5.x/api/governance
[remote-proving]: ../generating-proofs/remote-proving.md
[revm]: https://crates.io/crates/revm
[risc0-ethereum]: https://github.com/risc0/risc0-ethereum
[signature-aggregation]: https://github.com/risc0/risc0-ethereum/blob/release-2.0/examples/governance/methods/guest/src/bin/finalize_votes.rs
[steel-blog]: https://www.risczero.com/blog/introducing-steel-1.0
[steel-repo]: https://crates.io/crates/risc0-steel
[steel-src]: https://github.com/risc0/risc0-ethereum/tree/release-2.0/steel
[verifier-contracts]: https://github.com/risc0/risc0-ethereum/tree/release-2.0/contracts
[zeth-article]: https://www.risczero.com/news/zeth-release
[zeth-repo]: https://github.com/risc0/zeth
[zkvm-examples]: ../zkvm/examples.md
