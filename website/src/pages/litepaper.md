---
id: litepaper
title: Bonsai Network Blockchain Litepaper
---

# Bonsai: One Chain to Prove Them All

## Problem

Even with multiple teams and significant funding, zkEVM technology is in its infancy and full EVM compatibility is at least a year away. Building a custom zero-knowledge circuit for a blockchain currently takes years of development and hundreds of millions of dollars. At present, potential zero-knowledge proof development on non-EVM blockchains is cost and resource prohibitive. Outside of Ethereum, most L1 blockchains, L2 rollups, app chains, and dApps are effectively blocked from utilizing zero knowledge for scaling and privacy.

Existing implementations of zkEVM, optimistic rollup L2s, and zero-knowledge L1s also introduce limitations across use cases which would otherwise be solved by pervasive access to developer-friendly zero knowledge. There are compromises in the following areas: scalability, functionality, network control, interoperability, and development flexibility. These compromises and inefficiencies create a pressing need for a new approach to zero-knowledge proof technology in the current blockchain ecosystem.

## Solution

### Overview

Bonsai is a general purpose zero-knowledge proof network that allows any chain, any protocol, and any application to take advantage of zero-knowledge proofs for scaling, privacy, and interoperability. With Bonsai, zero-knowledge proof integration into Ethereum, L1 blockchains, Cosmos app chains, L2 rollups, and dApps is possible in a matter of days with minimal development effort.

Built on the open RISC-V instruction set, our zkVM allows for widespread language compatibility with the potential for code to be written in Rust, C++, Solidity, Go, and other languages. With a combination of recursive proofs, a bespoke circuit compiler, state continuations, and continuous improvements to the proving algorithm, Bonsai enables anyone to generate highly performant zero-knowledge proofs for a variety of applications.

Bonsai combines three key ingredients to produce a unique network that will enable new classes of applications to be developed across the blockchain ecosystem:

- A general purpose zkVM capable of running any virtual machine in a zero-knowledge/verifiable context
- A proving system that directly integrates into any smart contract or chain
- A universal rollup that distributes any computations proven on Bonsai to every chain

### Zero-Knowledge Proofs For Every Chain And Application

Bonsai allows for zero-knowledge proofs to be built into the entire web3 ecosystem by acting as an independent zero-knowledge proving network that chains and dApps can call from smart contracts or validators to generate zero-knowledge proofs. The proofs are then posted onto blockchains such as Ethereum, zero-knowledge L2s, app chains, and L1s. This enables verifiable off-chain compute; applications can rely on Bonsai for the majority of their smart contract logic and state change calculations without the use of a blockchain VM (EVM). The state changes and smart contract execution are fully verified by Bonsai’s ZK proofs which are posted on-chain. The resulting smart contract is more compact, functional, and gas efficient.

```solidity
// Without Bonsai
contract simulation_normal {
 function some_really_hard_work() {
   // A large amount of gas heavy code
       // code ...
       // code ...
       // code ...
       // code ...
       // code ...
       //
 }
}
```

```solidity
// With Bonsai
contract simulation_bonsai {
 function some_really_hard_work() {
   bonsai_proving_network.call(“some_really_hard_work”);
 }
}
```

**Bonsai simplifies non-trivial smart contracts and chains.**

Bonsai reduces any smart contract into a single ZK Bonsai network call and moves all the gas-heavy code execution off chain. Smart contracts are no longer bounded by the limitations of EVM and others; instead, they will have full support in Rust and any other programming language that the zkVM will support. This means that a Solidity contract on ETH will be able to write its main logic in Rust on Bonsai and take advantage of non-EVM primitives, Rust crates, and the breadth of functionality of off-chain code execution.

This direct integration into smart contracts enables us to bring ZK to any Layer 1, Layer 2, app chain, and dApp. Ethereum L1 dApps can now utilize Bonsai’s ZK off-chain execution to reduce gas fees and increase TPS on the Ethereum base layer. The Uniswap swap function, for example, can calculate swap rates and pool fees off chain on Bonsai, greatly reducing the amount of gas required to conduct a swap on ETH L1.

By integrating directly into the smart contract, we maintain full composability with the native chain of any ZK app built on Bonsai. Additionally, ZK dApps can now utilize native ETH, liquidity, NFTs, and Aave/Uniswap LPs. Bonsai effectively allows any application, blockchain, and app chain to easily integrate ZK proofs into their protocol without custom ZK circuit development.

### Native Interoperability

As a central proving network across multiple chains, Bonsai enables composable interoperability between different smart contracts, regardless of their origin chain. Bonsai is also a universal rollup in that zero-knowledge proofs originating from Ethereum and other chains are all rolled up into a single proof that is posted across any chain. This means that Bonsai is a shared execution layer accessible by any blockchain.

A swap call on an Ethereum DEX will therefore be able to directly utilize a liquidity pool on Solana. Smart contracts will also be able to call each other across chains within the confines of the Bonsai shared execution layer. Existing liquidity and shielded assets can be easily bridged natively between chains through Bonsai. The possibilities are endless, as Bonsai is not limited to L1s: Bonsai will also work on and enable interoperability between Layer 2 ORUs and zkEVMs, Cosmos app chains (with the potential for IBC integration), oracles, and web2.

## Bonsai Architecture

Bonsai is a massively parallel, chain-agnostic, and general purpose network designed to enable developers to build a completely new class of zero-knowledge applications. In order to enable this, the architecture is composed of multiple modular parts that together will allow the network to interact across any chain and protocol. Bonsai was also built from the ground up with a decentralization-first approach to its architecture. All components of the network are being developed to enable distributed execution and proving.

![Bonsai architecture diagram, showing stages for: request, proving market, universal rollup, multi-chain post, and Merkle lookup](/img/bonsai-at-a-glance.png)

### Major Components

**Prover Network:** A network of node operators running our zkVM prover in order to execute and prove any requests sent from the Bonsai API. Bonsai’s infrastructure will ensure high Node availability as well as tracking incentives for Node operators. Over time this network will expand and decentralize enabling anyone to run provers.

**Request Pool:** A database of requests for proofs as well as metadata about those proofs (for instance, age and rollup-depth). This pool will also act as a sequencer and construct blocks for node operators. Many proofs will be split into multiple portions in order to enable time-efficient proving, the request pool manages the splitting and recombining of single function requests.

**Rollup Engine:** The rollup engine takes proofs generated by the prover network and rolls them up into a singular root proof. It then publishes this root proof onto chains such as Ethereum and Solana which subsequently can verify the proof’s validity.

**Image Hub:** The image hub will allow developers to store functions and program images that can be executed by blockchain smart contracts through the Bonsai API. Program images in this case can vary in complexity from basic DeFi swap functions to complex light clients and even Geth. All execution of these images will be ZK provable through Bonsai and our zkVM. The image hub provides extremely powerful programming primitives to developers and will enable the creation of complex stateful workflows that span multiple blockchains. It will enable Bonsai to act as a shared execution layer between any chain and increase the functionality of smart contracts by many magnitudes.

### Future components

**State Store:** The Bonsai State Store will enable developers to store state on Bonsai instead of needing to maintain state on the settlement layer (Layer 1 Ethereum etc). This will increase gas savings and reduce contract complexity for the application while enhancing the functionality of code executed on Bonsai. Variables within the state store are represented by Key/Value pairs which store the state on Bonsai for easy accessibility within Bonsai functions/program images.

**Proving Marketplace:** As demand for Bonsai proofs exceeds the in-house supply we can provide, we will move towards developing a decentralized proving network. We can base the design of such a market around Bitcoin and Ethereum where anyone can generate proofs. The proof marketplace will match proof asks with bids allowing for permissionless participation in the proving network and increasing Bonsai’s overall efficiency and reliability.

## Blockchain Use Cases

### Scaling - Off-Chain Smart Contract Execution

Bonsai allows smart contracts to execute an arbitrary amount of code off-chain and generates a proof attesting to the validity of the code execution and state change. This leads to large gains in the **scalability, functionality, and interoperability of blockchains.**

**Scalability** - By simply moving code execution away from a blockchain VM, smart contracts will require orders of magnitude less gas as fewer lines of code need to be executed on chain. This will help reduce the gas costs of any smart contract and lead to significantly lower fees across DEXs, lending protocols, NFT marketplaces, and more. It is plausible that with Bonsai there will be an upper limit of gas fees per smart contract regardless of contract complexity. With Bonsai, smart contracts can converge roughly to the following:

```solidity
contract simulation_bonsai {
  function some_really_hard_work() {
    // Amount of ETH to swap, liquidation prices, LP balances, Etc.
    inputVals = Query chain for input values and data

    // Ask Bonsai to calculate state transitions
    newState = bonsai_proving_network.call(“some_really_hard_work”, inputVals)

    // Update blockchain values
    state = newState
  }
}
```

**Functionality** - Off-chain execution also allows functions to take advantage of Rust/C++/etc. libraries and crates. This is because off-chain execution is not bounded by the limitations of existing L1 execution layers. Instead, smart contract code on Bonsai can be executed like a traditional executable on the RISC Zero zkVM, which allows for more performant and complex smart contracts. This also enables libraries and crates that open up functionality within contracts, especially those built on traditional monolithic L1s .

**Example:** **Ethereum On Chain Order Book**

A two-sided maker taker order book is currently unobtainable on ETH due to high gas fees and the need for complex order matching algorithms. Through Bonsai the entire order matching process can be conducted off-chain on the network. The only on-chain actions would consist of submitting the order itself and locking up the payment asset. Further optimizations can be introduced if the order book state is stored off-chain. From the ETH block explorer perspective, the order book would look like a simple transfer of assets between two parties with all of the hidden matching and bids/asks conducted on Bonsai.

**Interoperability -** As mentioned in the previous sections, Bonsai is a shared off-chain execution layer which enables any chain and smart contracts to interact together. The Bonsai zkVM will act as a center of all off-chain smart contracts regardless of their origin or language, as everything in Bonsai compiles down to RISC-V. As an execution layer, Bonsai will enable the level of composability and interoperability traditionally found within a Layer 1 across any chain.

**The goal of Bonsai is to provide every chain with the capacity for boundless computation.**
