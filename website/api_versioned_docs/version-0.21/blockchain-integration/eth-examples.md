# Ethereum Examples

While all of the [zkVM examples][zkvm-examples] can be run on Bonsai by [configuring Bonsai][remote-proving] as your remote prover, those examples do not interact with or are intended to interact with Ethereum or any other blockchain. The references below are examples of how Bonsai and the zkVM can be integrated with Ethereum.

### Foundry Template

The [RISC Zero Foundry Template][foundry-template] provides a minimal application that can act as a template for developing your application.

### Zeth

[Zeth][zeth-repo] produces ZK validity proofs for Ethereum Virtual Machine blocks (EVM). This is accomplished by running [revm], a Rust implementation of the EVM in the zkVM. The end result is an open-source zkEVM with high code reuse and minute, not hour, proving times on Bonsai. For more info check out [Announcing Zeth: The first Type Zero zkEVM][zeth-article].

### DAO Governance Example

This [example app][governance-example] uses Bonsai as an Ethereum coprocessor. The protocol, based on the OpenZeppelin [Governor smart contract standard], batches signature verifications off-chain for a DAO governance vote. The end result is that in [\~160 lines of Rust][signature-aggregation], a gas savings of 66% is achieved with significant room for optimizations.

[foundry-template]: https://github.com/risc0/bonsai-foundry-template
[governance-example]: https://github.com/risc0/risc0/tree/release-0.21/bonsai/examples/governance
[Governor smart contract standard]: https://docs.openzeppelin.com/contracts/4.x/api/governance
[remote-proving]: ../generating-proofs/remote-proving.md
[revm]: https://crates.io/crates/revm
[signature-aggregation]: https://github.com/risc0/risc0/blob/release-0.21/bonsai/examples/governance/methods/guest/src/bin/finalize_votes.rs
[zeth-article]: https://www.risczero.com/news/zeth-release
[zeth-repo]: https://github.com/boundless-xyz/zeth
[zkvm-examples]: /api/zkvm/examples
