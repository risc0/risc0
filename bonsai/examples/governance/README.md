# Bonsai Governance Showcase

### Background

Billions of dollars worth of assets are managed by DAO treasuries, to be put to use towards each DAO's mission.
Governance, in one form or another, is widely deployed to help decide what actions will be aligned with the mission.

Voting is core to most Governance systems, and one of the major challenges is the high gas costs associated with voting on-chain.
High gas costs make voting more expensive, and therefore less inclusive, making this a serious concern.
There's a trade-off between using fully on-chain systems like [Tally] with high associated gas costs, or using an off-chain system with lower security guarantees.

### Summary

In this showcase, we implement the Bonsai Governor to reduce gas costs of fully-verifiable on-chain voting by processing ballots in the zkVM.
We start from the [OpenZeppelin Governor] standard, which is used by DAOs such as Uniswap, ENS, Aave and many others.

Key to this design is offloading compute that is expensive on-chain to the [RISC Zero] zkVM guest, with execution and proving being handled by Bonsai.
In particular, this design optimizes voting operations, especially when casting a signed vote, by deferring signature verification and double-voting checks to the zkVM.
Instead of verifying the signature or adding the ballot to EVM state, both the `Governor.vote` and `Governor.voteBySig` methods simply log an `event` and add the ballot to a running hash accumulator.
These event logs are collected later, by anybody in the world, and passed to the zkVM for vote finalization with the results sent to the Bonsai Governor smart contract through the Bonsai relay.
With this, we are able to reduce gas costs for voting, while maintaining the security guarantees of voting on L1.

As a result, the Bonsai Governor uses about 66% less gas per vote[^1] compared with the baseline [OpenZeppelin Governor] implementation.
This translates to significant savings for voters and DAOs, and more inclusive voting as a result.

At gas prices of July 2023, the baseline is about $6-9 per vote.
With the Bonsai Governor, the gas cost is $2-3 per vote.
On a proposal with 1000 active voters, this saves voters and the DAO $4000-6000 per proposal. [^2]

One of the major advantages of RISC Zero is the simplicity of defining the zkVM program.
Instead of complicated arithmetic circuits, which only experts in zero-knowledge cryptography can write and maintain, the zkVM program definition is 150 lines of Rust code.
Check out `methods/guest/src/bin/finalize_votes.rs` to see the full definition of the zkVM program.

Features currently in development can further decrease gas costs to make it possible to execute governance with L1 security, with only a fixed cost of ~300-400k gas per proposal, no matter how many votes. [^3]

[^1]: When discussing gas-per-vote we only count the gas spent executing Governor logic, and not e.g. intrinsic gas for a transaction. We count it this way since both in the baseline and Bonsai Governor these costs can be amortized by batching transactions.
[^2]: Prover costs are not mentioned here because proving computation off-chain with RISC Zero costs less than 1/100th the cost of on-chain compute as of July 2023.
[^3]: In particular, we are working on methods for verified L1 data access in the zkVM guest, which will allow lookup up voter weights inside the guest.

### Security Considerations

Any voting system needs to achieve two very important properties:

1. It must not be possible for any actor to commit *fraud* by casting more votes than authorized.
2. Every voter must be able to ensure their voter is counted, i.e. that their vote *cannot be censored*.

OpenZeppelin's Governor standard provides prevents fraud as long as the L1 execution is sound, a property ensured by the robust Ethereum full-node community.
It is also censorship resistant as long as Ethereum is censorship-resistant, which is provided by the [mechanisms of Ethereum consensus].

[mechanisms of Ethereum consensus]: https://notes.ethereum.org/@vbuterin/pbs_censorship_resistance

The Bonsai Governance design implemented here provides the same security properties as OpenZeppelin's Governor standard.
In order to achieve the same properties, the Bonsai Governor requires an additional dependency on the soundness of the RISC Zero proof system.
If there is a break in the soundness of the RISC Zero proof system, it may be possible for a malicious actor to produce fraudulent votes.

In this showcase, we are using Groth16 with a locally produced trusted setup.
In the near future we will transition to proof system based on well-established secure setup ceremonies.

The Bonsai Governor's current design accepts ballots exclusively on-chain, and requires every ballot provided on-chain to be included in the vote tally.
By doing so, it achieves the same censorship resistance as the OpenZeppelin Governor.
In any future design where off-chain voting is allowed, on-chain voting will always be available to ensure every vote is counted.

We look forward to open-sourcing the recursive prover, however in the meantime, such proofs are exclusive to our Bonsai proving service.
This presents known censorship and liveness concerns which we plan to mitigate through various means and eventually decentralization.

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

***Note:*** *The Bonsai proving service is still in early Alpha. To request an API key [complete the form here](https://bonsai.xyz/apply).*

```bash
export BONSAI_API_KEY="YOUR_API_KEY" # see form linked above
export BONSAI_API_URL="BONSAI_URL" # provided with your api key
RISC0_DEV_MODE=false forge test --match-contract BasicBonsaiGovernorTest
```

[Tally]: https://www.tally.xyz
[RISC Zero]: https://www.risczero.com/
[OpenZeppelin Governor]: https://docs.openzeppelin.com/contracts/4.x/api/governance
[Bonsai Foundry Template]: https://github.com/risc0/bonsai-foundry-template
