# Ethereum Examples

While all of the [zkVM examples][zkvm-examples] can be run on Bonsai by [configuring Bonsai][remote-proving] as your remote prover, those examples do not interact with or are intended to interact with Ethereum or any other blockchain. The references below are examples of how Bonsai and the zkVM can be integrated with Ethereum.

### Foundry Template

The [RISC Zero Foundry Template][foundry-template] provides a minimal application that can act as a template for developing your application.

### Zeth

[Zeth][zeth-repo] produces ZK validity proofs for Ethereum Virtual Machine blocks (EVM). This is accomplished by running [revm], a Rust implementation of the EVM in the zkVM. The end result is an open-source zkEVM with high code reuse and minute, not hour, proving times on Bonsai. For more info check out [Announcing Zeth: The first Type Zero zkEVM][zeth-article].

### DAO Governance Example

This [example app][governance-example] uses Bonsai as an Ethereum coprocessor. The protocol, based on the OpenZeppelin [Governor smart contract standard], batches signature verifications off-chain for a DAO governance vote. The end result is that in [~160 lines of Rust][signature-aggregation], a gas savings of 66% is achieved with significant room for optimizations.

[zkvm-examples]: /api/zkvm/examples
[remote-proving]: /api/generating-proofs/remote-proving
[zeth-repo]: https://github.com/risc0/zeth
[revm]: https://crates.io/crates/revm
[zeth-article]: https://www.risczero.com/news/zeth-release
[governance-example]: https://github.com/risc0/risc0/tree/release-0.20/bonsai/examples/governance
[Governor smart contract standard]: https://docs.openzeppelin.com/contracts/4.x/api/governance
[signature-aggregation]: https://github.com/risc0/risc0/blob/release-0.20/bonsai/examples/governance/methods/guest/src/bin/finalize_votes.rs
[foundry-template]: https://github.com/risc0/bonsai-foundry-template
