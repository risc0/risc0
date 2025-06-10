# Cryptographic Security Model

RISC Zero is proud to offer an end-to-end solution for verifiable computation.
Users can generate proofs for correct execution of software code using the [RISC Zero zkVM],
and they can verify those proofs on-chain using our permissionless [verifier contract] on Ethereum networks such as Sepolia.

The rest of this document offers an overview of the security model for applications that rely on RISC Zero's tooling.

RISC Zero offers the following components, each of which is ready for use on testnet.

## Overview of Components

The RISC Zero zkVM and its on-chain dependencies necessary for verifying proofs on chain, can be described as the following five high-level components.

| Component Name                  | Latest Audit  | Description                                                                                                                                                                                                                                                                                                                                                                                                                    |
| ------------------------------- | ------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| **cargo risczero** tool         | [10/31/2023↗] | Compiles user-written Rust code into RISC-V ELF binaries [deterministically]                                                                                                                                                                                                                                                                                                                                                   |
| **RISC-V Prover**               | [10/31/2023↗] | Executes and proves execution of ELF binaries produced by the `cargo risczero` tool                                                                                                                                                                                                                                                                                                                                            |
| **Recursion Prover**            | [10/31/2023↗] | Aggregates proofs from the RISC-V Prover; supports a small number of programs like [lift], [join], [resolve]. Each program is identified by a [control ID] and the full list of allowed programs is identified in [control root].                                                                                                                                                                                              |
| **STARK-to-SNARK Prover**       | [05/20/2024↗] | Verifies STARK proofs from the RISC Zero Recursion Prover, compressing them into a Groth16 SNARK for efficient on-chain verification. The [control root] is passed to as a public input, allowing for updates to our RISC-V Prover without requiring a new trusted setup ceremony.                                                                                                                                             |
| **On-chain verifier contracts** | [06/05/2024↗] | Verifies Groth16 proofs from the RISC Zero STARK-to-SNARK Prover. The control root is hard-coded into the on-chain verifier contract. Addresses for the on-chain verifier contracts we have deployed are available in our [verifier contract] documentation, and a detailed description of the options for governance, upgrades, and deprecation are available in our [Version Management Design][VersionManagement@main] doc. |

Together, these components allow developers to integrate proofs of arbitrary Rust code into their on-chain applications.
In order to use these components, developers provide:

- the Rust code for their zkVM guest program.
- a smart contract on-chain whose behavior will depend on the output of the Verifier Contract

**RISC Zero technology cannot prevent many types of security issues in user guest programs (e.g. applications) or contracts. It is necessary for zkVM adopters to validate the security of guest programs and contracts. This includes secure development life-cycles and external security auditing by qualified providers.**

![Security Model Diagram](/diagrams/security-model-diagram.svg)

## Zero-Knowledge Proving

The RISC Zero zkVM hides all program inputs and all witness data, and targets perfect zero-knowledge.

Nevertheless, we have not written a mathematical argument to prove that our system is zero-knowledge. We are working on some minor engineering changes in order to make it easier to prove that our proof system has perfect zero-knowledge.

We urge those with critical privacy requirements to take caution until the necessary changes have been implemented.

We also point out the following caveats with respect to privacy:

:::warning
Whoever is generating the proofs can see the secret data. Users may choose to use any of these provers locally to ensure their data stays private.
:::

:::warning
Proofs generated by the **RISC-V Prover** that haven't been passed through the **Recursion Prover** leak information about the length of execution.
Passing proofs through the Recursion Prover resolves this warning: recursion proofs leak no information about execution length.
:::

## Cryptographic Security

In analyzing the cryptographic security of our system, we consider two primary questions:

1. Can a malicious user who doesn't know a valid [execution trace] for the given [receipt claim] create a fake proof that will trick the verifier?
2. Can a malicious user extract secret information from a proof posted on-chain?

The first question is about the **soundness** of the protocol, and the second question is whether the protocol is **zero-knowledge**.

Soundness is often quantified in terms of "[bits]" — our [on-chain verifier contracts][Verifier Contract] target 96 bits of security.

| Prover                | Cryptographic Assumptions                                                                                                                       | Bits of Security | Quantum Safe? |
| --------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- | ---------------- | ------------- |
| RISC-V Prover         | - Random Oracle Model <br /> - Toy Problem Conjecture                                                                                           | 96               | Yes           |
| Recursion Prover      | - Random Oracle Model <br /> - Toy Problem Conjecture                                                                                           | 99               | Yes           |
| STARK-to-SNARK Prover | - Security of elliptic curve pairing over BN254. <br /> - Knowledge of Exponent assumption <br /> - Integrity of Groth16 Trusted Setup Ceremony | 99+              | No            |

The Toy Problem conjecture, specified in detail in the [ethSTARK documentation], says that the best known attack on STARK proof systems is the best possible attack.

## The STARK Provers

The RISC-V Prover and the Recursion Prover both use STARK-based protocols, which are not known to be vulnerable to attacks via quantum computers.

### How secure are the STARK Provers?

We estimate that it would take approximately 100,000 years to brute force a collision against our STARK protocol using GPUs in a parallel attack, using 1 million high-end GPUs.

- Currently, we look to the RTX 4090 as a high-end reference GPU.
- RTX 4090 [benchmarks] provide a reference SHA2-256 hashrate at less than 25,000 million hashes per second.
- We have seen several [examples] of large purchases of GPUs on the order of 350,000 so we conservatively suggest that a distributed attacker may be able to operate 1 million RTX 4090s in parallel.

At $2^{96}$ [bits] of security required to force a collision, we can estimate the time to brute force a collision as follows:

`2^96 / (25,000,000,000 Hashes/s * 1,000,000 GPUs) / 60seconds / 60 minutes / 24 hours / 365 days = 100492 years`

The analysis for bits of security for the RISC-V and Recursion Prover can be found in the [security calculator].
For a detailed cryptographic description of our STARK system, we refer readers to [RISC Zero zkVM: Scalable, Transparent Arguments of RISC-V Integrity][proof-system].

## The STARK to SNARK Translator

The STARK to SNARK translator uses a Groth16 prover over the BN254 pairing-friendly curve. The security of this part of the protocol depends on elliptic curve cryptography, and is therefore vulnerable to attacks from quantum computers.

### How secure is the STARK to SNARK Prover?

The best known attack vector against our STARK to SNARK Prover is to attack the underlying elliptic curve pairing used with BN254.
This primitive has been heavily battle-tested; it has been included as a precompile on Ethereum since the introduction of EIP-197.

For a detailed discussion of the security of BN254, we refer readers to the discussion on this [GitHub issue from Zcash].

[05/20/2024↗]: https://github.com/risc0/rz-security/blob/main/audits/circuits/hexens_v1c_stark2snark_20240520.pdf
[06/05/2024↗]: https://github.com/risc0/rz-security/blob/main/audits/contracts/hexens_verifiercontract_20240605.pdf
[10/31/2023↗]: https://github.com/risc0/rz-security/blob/main/audits/zkVM/hexens_zkVM_20231031.pdf
[benchmarks]: https://gist.github.com/Chick3nman/32e662a5bb63bc4f51b847bb422222fd
[bits]: https://a16zcrypto.com/posts/article/snark-security-and-performance
[control ID]: /terminology#control-id
[control root]: /terminology#control-root
[deterministically]: /terminology#deterministic-builds
[ethSTARK documentation]: https://eprint.iacr.org/2021/582
[examples]: https://www.pcmag.com/news/zuckerbergs-meta-is-spending-billions-to-buy-350000-nvidia-h100-gpus
[execution trace]: /terminology#execution-trace
[GitHub issue from Zcash]: https://github.com/zcash/zcash/issues/714
[join]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ApiClient.html#method.join
[lift]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ApiClient.html#method.lift
[proof-system]: pathname:///proof-system-in-detail.pdf
[receipt claim]: /terminology#receipt-claim
[resolve]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.ApiClient.html#method.resolve
[RISC Zero zkVM]: ./zkvm
[security calculator]: https://github.com/risc0/risc0/blob/main/risc0/zkp/src/prove/soundness.rs
[Verifier Contract]: ./blockchain-integration/contracts/verifier.md
[VersionManagement@main]: https://github.com/risc0/risc0-ethereum/blob/main/contracts/version-management-design.md
