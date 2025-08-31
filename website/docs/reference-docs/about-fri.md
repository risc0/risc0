# About the FRI Protocol

The FRI ([**F**ast](about-ntts-and-fourier.md), [**R**eed-Solomon](about-rs-codes.md) [**I**nteractive](https://en.wikipedia.org/wiki/Interactive_proof_system) [Oracle](https://en.wikipedia.org/wiki/Oracle_machine) [Proof of Proximity](https://privacytools.seas.harvard.edu/sites/g/files/omnuum6656/files/privacytools/files/stoc283fp-rothblum.pdf)) protocol is the final component of RISC Zero's argument of computational integrity.

RISC Zero's [STARK](about-starks.md) converts an assertion of computational integrity to an assertion about polynomial division.
In the language of Reed-Solomon codes, this assertion about polynomial division can be re-framed as an assertion about [block proximity](https://en.wikipedia.org/wiki/Hamming_distance).
The FRI protocol finishes the argument by proving the assertion about block proximity.

## Basic Function

Given a Merkle root, the _FRI protocol_ is a recursive technique for proving that the associated Merkle leaves correspond to a low-degree polynomial.

## Background

### Inside the Algorithm

The FRI protocol consists of a number of `commit` rounds followed by a number of `query` rounds.

- In each `commit` round, the Prover commits a new (smaller) Merkle tree corresponding to evaluations of a lower-degree polynomial; the round-by-round commitments depend on a random mixing parameter that allows for an audit-trail in the upcoming query round.
  - In each `commit` round, the degree of the FRI polynomial and the size of the associated Merkle tree is reduced by a factor of 16, in the RISC Zero implementation.
  - RISC Zero runs `commit` rounds until the degree of the FRI polynomial is less than or equal to 255.
- In each `query` round, the Prover reveals Merkle branches (and leaves) from each of the FRI commitments. The branches revealed in the query rounds are selected using the [Fiat-Shamir Heuristic](https://en.wikipedia.org/wiki/Fiat%E2%80%93Shamir_heuristic).
  - Varying the number of `query` rounds offers a tradeoff between security level and computational efficiency.
- RISC Zero's implementation for FRI can be found [here](https://github.com/risc0/risc0/blob/main/risc0/zkp/src/prove/fri.rs)

### About DEEP-FRI

Shortly after the FRI protocol was released, an alternative protocol called DEEP-FRI was released.
Although DEEP-FRI was initially thought to have improved soundness relative to FRI, the Proximity Gaps for Reed-Solomon Codes paper shows that the original FRI protocol offers the same soundness results as DEEP-FRI at less computational complexity.
The RISC Zero ZKP system uses the original FRI protocol.

## Suggested Reading

### Academic Papers

- [Proximity Gaps for Reed-Solomon Codes (Ben-Sasson et. al, 2020)](https://eprint.iacr.org/2020/654.pdf) (PDF)
- [Fast Reed Solomon Interactive Oracle Proofs of Proximity (Ben-Sasson et. al, 2017)](https://drops.dagstuhl.de/opus/volltexte/2018/9018/pdf/LIPIcs-ICALP-2018-14.pdf) (PDF)
- [Interactive Proofs of Proximity (Rothblum, Vadhan, and Widgerson, 2013)](https://guyrothblum.files.wordpress.com/2014/11/rvw13.pdf) (PDF)

### Explanatory References

- RISC Zero Study Club [Slides](https://drive.google.com/file/d/1TuufbM8py2mGDkjMUg5FWZzw8VqNri4O/view?usp=share_link) & [Video Recording](https://www.youtube.com/watch?v=j35yz22OVGE)
- [FRI Sequence Diagram](https://twitter.com/EllipticHector/status/1641842245337743367)
- [A summary on the FRI low degree test (Ulrich Haböck, Orbis Labs, 2022)](https://eprint.iacr.org/2022/1216.pdf) (PDF)
- [Low Degree Testing](https://medium.com/starkware/low-degree-testing-f7614f5172db), part 3 of the STARK Math series
- [Vitalik's FRI article](https://vitalik.eth.limo/general/2017/11/22/starks_part_2.html)
- [Anatomy of a STARK, Part 3: FRI](https://aszepieniec.github.io/stark-anatomy/fri)
