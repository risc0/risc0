---
sidebar_position: 1
slug: ./
---

# Proof System Overview

### Introduction
When the RISC Zero [zkVM] executes, it produces a [Receipt] that serves as a proof of validity of a given [Session].

To confirm that a [Receipt] was honestly generated, use [Receipt::verify] and supply the [ImageID] of the code that should have been executed as a parameter.

The [Receipt] includes a [journal], which contains the public outputs of the [Session].
The contents of the [journal] are specified by calling [env::commit()] and [env::commit_slice()] in the [guest] code.

In addition to the journal, a receipt makes a number of claims about the program execution.
These claims are summarized in the [ReceiptClaim].

### Types of Receipts
A [Receipt] can take three main forms, each of which constitutes a proof of validity of a [Session]:

1. A [FlatReceipt] is a vector of [ZK-STARK]s, one for each [segment]. Segments & segment proofs are constructed by the [RISC-V zkVM].
2. A [SuccinctReceipt] is a single [ZK-STARK] proving an entire [Session]. The SuccinctReceipt is formed by aggregating the proofs from the [FlatReceipt]. This is accomplished using the [Recursion Circuit]. Users can also aggregate multiple [SuccinctReceipt]s into a single [SuccinctReceipt] using [proof composition].
3. A [Groth16Receipt] is a single [Groth16] proof for an entire [Session]. The Groth16Receipt is formed by verifying a SuccinctReceipt using RISC Zero's [Groth16 circuit].

The details of the RISC Zero ZK-STARK protocol are described in our [ZKP Whitepaper] and in this [Sequence Diagram].

## Learn More

### About the zkVM

- [Video Explainer from zkHack](https://www.youtube.com/watch?v=8hwY88xJoyM&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=8)
- [Written Explainer](/api/zkvm)

### About STARKs

- [STARKs reference doc](../reference-docs/about-starks.md)
- STARK by Hand Tutorial
  - [Website version](./stark-by-hand.md)
  - [Google Sheet version](https://docs.google.com/spreadsheets/d/1Onr41OozD62y-B0jIL7bHAH5kf771-o4xvmnHUFpOyo/edit?usp=sharing)
  - [Printable Version](assets/fibonacci-stark.pdf)

### About RISC Zero

- All our public talks and podcasts are available on our [YouTube channel].
- [RISC Zero Study Club] is intended to help make the technology underpinning RISC Zero more accessible. Past sessions include:
  - [What is RISC-V and how does it relate to RISC Zero?](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=5)
  - [Intro to Finite Fields](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=2)
  - [Intro to Reed-Solomon Codes](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=3)
  - [Intro to Number Theoretic Transforms](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=4)
  - [Intro to the FRI Protocol](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=1)
  - [Finite Field Implementation Options: Barrett & Montgomery Multiplication](https://www.youtube.com/watch?v=hUl8ZB6hpUM&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=6)

[zkVM]: https://docs.rs/risc0-zkvm
[Receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
[ReceiptClaim]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ReceiptClaim.html
[SegmentReceipts]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipts.html
[SegmentReceipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipt.html
[SuccinctReceipt]: https://docs.rs/risc0-zkvm/0.19.1/risc0_zkvm/struct.SuccinctReceipt.html
[session]: https://dev.risczero.com/terminology#session
[Receipt::verify]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#method.verify
[ImageID]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SystemState.html
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#structfield.journal
[env::commit()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[env::commit_slice()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit_slice.html
[guest]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest
[ZK-STARK]: ../reference-docs/about-starks.md
[segment]: https://dev.risczero.com/terminology#segment
[ZKP Whitepaper]: https://www.risczero.com/proof-system-in-detail.pdf
[Sequence Diagram]: ./proof-system-sequence-diagram.md
[RISC Zero Study Club]: https://dev.risczero.com/studyclub
[YouTube channel]: https://www.youtube.com/@risczero
