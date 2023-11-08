# Ethereum Examples

While all of the [zkVM examples] can be run on Bonsai by [configuring Bonsai] as your remote prover, those examples do not interact with or are intended to interact with Ethereum or any other blockchain. The references below are examples of how Bonsai and the zkVM can be integrated with Ethereum.

### Zeth

[Zeth] produces ZK validity proofs for Ethereum Virtual Machine blocks (EVM). This is accomplished by running [revm], a Rust implementation of the EVM in the zkVM. The end result is an open-source zkEVM with high code reuse and minute, not hour, proving times on Bonsai. For more info check out [Announcing Zeth: The first Type Zero zkEVM].

### DAO Governance Example

This [example app] uses Bonsai as an Ethereum coprocessor. The protocol, based on the OpenZeppelin [Governor smart contract standard], batches signature verifications off-chain for a DAO governance vote. The end result is that in [~160 lines of Rust], a gas savings of 66% is achieved with significant room for optimizations.

### BonsaiStarter.sol

This [test contract] in the [Bonsai Foundry Template] provides an example of two different ways Bonsai can be integrated with Ethereum smart contracts using the [Bonsai Ethereum Relay].

[zkVM examples]: /api/zkvm/examples
[configuring Bonsai]: /api/zkvm/quickstart#remote-proving
[Zeth]: https://github.com/risc0/zeth
[revm]: https://crates.io/crates/revm
[Announcing Zeth: The first Type Zero zkEVM]: https://www.risczero.com/news/zeth-release
[example app]: https://github.com/risc0/risc0/tree/main/bonsai/examples/governance
[Governor smart contract standard]: https://docs.openzeppelin.com/contracts/4.x/api/governance
[~160 lines of Rust]: https://github.com/risc0/risc0/blob/main/bonsai/examples/governance/methods/guest/src/bin/finalize_votes.rs
[test contract]: https://github.com/risc0/bonsai-foundry-template/blob/main/contracts/BonsaiStarter.sol
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
[Bonsai Ethereum Relay]: https://github.com/risc0/risc0/tree/main/bonsai/ethereum-relay
