# About STARKs

The seal on a RISC Zero receipt is generated using a **zk-STARK**: a _zero knowledge, scalable, transparent argument of knowledge._

STARKs are a highly technical process - an innovation in the world of zero-knowledge cryptography introduced by Eli Ben-Sasson et. al in 2018.
In order to prove the integrity of a computation with a STARK, the prover arithmetizes the entire question.
By encoding the [execution trace](../proof-system/what_is_a_trace.md) into [polynomials](about-finite-fields.md), the statement of computational integrity is reduced to a statement about polynomial division.

## Documentation

In the context of the RISC Zero zkVM, the term **seal** refers to the zk-STARK that attests to the integrity of the trace.
The following documentation describes the RISC Zero zk-STARK in more detail:

- [Proof system sequence diagram](../proof-system/proof-system.md) <br/> This document includes a sequence diagram and step-by-step specification of the RISC Zero zk-STARK.
- [STARK by Hand](../proof-system/stark-by-hand.md) <br/> This document shows a simplified, concrete example of the construction of a RISC Zero seal.

## References

We recommend the following external references on STARKs:

### Less Technical

- [Extreme Integrity in Decentralized World](https://medium.com/@eli_1210/extreme-integrity-in-decentralized-world-a56da4c730ea)
- [Cambrian Explosion of Crypto Proofs](https://medium.com/starkware/the-cambrian-explosion-of-crypto-proofs-7ac080ac9aed)
- [STARKs vs. SNARKS (Consensys, 2021)](https://consensys.net/blog/blockchain-explained/zero-knowledge-proofs-starks-vs-snarks/)

### More Technical

- [Anatomy of a Stark](https://aszepieniec.github.io/stark-anatomy/) (developer focused)
- [The Starkmath series](https://medium.com/tag/stark-math)
- [STARK 101](https://starkware.co/stark-101/) (developer focused)
- [Vitalik's STARK series](https://vitalik.eth.limo/general/2017/11/09/starks_part_1.html)

### Most Technical

- [The STARK paper (Ben-Sasson et al, 2018)](https://eprint.iacr.org/2018/046.pdf)
