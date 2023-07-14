# Bonsai Governance Showcase

### Background

Billions of dollars worth of assets are managed by DAO treasuries, to be put to use towards the DAO's mission.
Governance, in one form or another, is widely deployed to help decide what actions will be aligned with the mission.

Voting is core to most Governance systems, and one of the major challenges is the high gas costs associated with voting on-chain.
DAO's a tradeoff between using fully on-chain systems like [Tally] and pay the high associated gas costs, or use an off-chain system with lower security guarantees.

### Summary

In this showcase, we implement the Bonsai Governor to reduce gas costs of fully-verifiable on-chain voting by processing ballots in the zkVM, with proving in Bonsai.
We start from the [OpenZeppelin Governor] standard, which is used by DAOs such as Uniswap, ENS, Aave and many others.

Key to this design is offloading compute that is expensive on-chain to the [RISC Zero] zkVM guest, with execution and proving being handled by Bonsai.
In particular, this design optimizes voting operations, especially when casting a signed vote, by deferring signature verification and ensuring that voters can only vote once to the zkVM.
Instead of the verifying the signature, or adding the ballot to EVM state, both the `Governor.vote` and `Governor.voteBySig` methods simply log an `event` and add the ballot to a running hash accumulator.
With this, we are able to reduce gas costs for voting, while maintaining the full security guarantees of voting on L1.

As a result, the Bonsai Governor uses about 66% less gas per vote[^1] compared with the baseline [OpenZeppelin Governor] implementation.
This translates to significant savings for voters and DAOs.

At gas prices of July 2023, the baseline is about $6-9 per vote.
With the Bonsai Governor, the gas cost is $2-3 per vote.
On a proposal with 1000 active voters, this saves voters and the DAO $4000-6000 per proposal. [^2]

Features currently in development can further decrease gas costs to make it possible to execute governance with full L1 security, with only a fixed cost of ~300-400k gas per proposal, no matter how many votes. [^3]

[^1]: When dicussing gas-per-vote we only count the gas spent executing Governor logic, and not e.g. intrisic gas for a transaction. We count it this way since both in the baseline and Bonsai Governor these costs can be amortized by batching transactions.
[^2]: Prover costs are not mentioned here because proving computation off-chain with RISC Zero costs less than 1\100th the cost of on-chain compute as of July 2023.
[^3]: In particular, we are working on methods for verified L1 data access in the zkVM guest, which will allow lookup up voter weights inside the guest.

## Codebase

This showcase is based on the [Bonsai Foundry Template]

### Dependencies

1. [Rust and Cargo](https://rustup.rs)

    ```bash
    curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
    ```

2. [Foundry](https://getfoundry.sh/)

    ```bash
    curl -L https://foundry.paradigm.xyz | bash
    ```

***Hint:*** *If you're installing Foundry for the first time, be sure to quit your terminal before reopening it and running the `foundryup` command.*

### Testing

Run the tests using. These tests run both the smart contracts, and the zkVM guest, providing a local implementation of Bonsai relay functionality.

```bash
forge test
```

For faster testing of the smart contracts without running tests against the smart contracts alone, without running the zkVM guest, use:

```bash
TEST_USE_ZKVM=false forge test
```

Additionally there are tests for the guest alone that can be run with.

```bash
cargo test
```

### Prove on Bonsai

By default, the tests above run without producing a zkVM receipt.
Running `forge test` with the following environment variables will cause the system to prove the vote finalization step using Bonsai.
The Bonsai proving service will produce a single STARK proof for the full computation, then compress the proof into a SNARK.
The Bonsai relay service, run locally for the test, uploads this SNARK to authorize the callback to the Governance contract.

```bash
export BONSAI_API_KEY="YOUR_API_KEY" # see form linked above
export BONSAI_API_URL="BONSAI_URL" # provided with your api key
BONSAI_PROVING=bonsai forge test --match-contract BasicBonsaiGovernorTest
```

[Tally]: https://www.tally.xyz
[RISC Zero]: https://www.risczero.com/
[OpenZeppelin Governor]: https://docs.openzeppelin.com/contracts/4.x/api/governance
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
