---
sidebar_position: 1
slug: ./
---

# Proof System Overview

When the RISC Zero [zkVM] executes, it produces a [Receipt] that serves as a proof of validity of a given [Session].

To confirm that a [Receipt] was honestly generated, use [Receipt::verify] and supply the [ImageID] of the code that should have been executed as a parameter.

The [Receipt] includes a [journal], which contains the public outputs of the [Session].
The contents of the [journal] are specified by calling [env::commit()] and [env::commit_slice()] in the [guest] code.

In addition to the journal, a receipt makes a number of claims about the program execution.
These claims are summarized in the [ReceiptMetadata].

A [Receipt] can take two main forms:

- It can be represented by a collection of [SegmentReceipts], each of which proves a single [Segment].
  Collectively, the [SegmentReceipts] prove the validity of the full [Session].
- It can also be represented by a single [SuccinctReceipt], proving the validity of the entire session.
  Using recursive proving, any number of [SegmentReceipts] can be compressed into a single [SuccinctReceipt].

Cryptographically each [SegmentReceipt] or [SuccinctReceipt] is a [ZK-STARK].
The details of the RISC Zero ZK-STARK are described in our [ZKP Whitepaper] and in this [Sequence Diagram].

## Learn More

### About the zkVM

- [Video Explainer from zkHack](https://www.youtube.com/watch?v=8hwY88xJoyM&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=8)
- [Written Explainer][1]

### About STARKs

- [STARKs reference doc][2]
- STARK by Hand Tutorial
  - [Website version][3]
  - [Google Sheet version](https://docs.google.com/spreadsheets/d/1Onr41OozD62y-B0jIL7bHAH5kf771-o4xvmnHUFpOyo/edit?usp=sharing)
  - [Printable Version][5]

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
[ReceiptMetadata]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ReceiptMetadata.html
[SegmentReceipts]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipts.html
[SegmentReceipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipt.html
[SuccinctReceipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/recursion/struct.SuccinctReceipt.html
[Session]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Session.html
[Receipt::verify]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#method.verify
[ImageID]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SystemState.html
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#structfield.journal
[env::commit()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[env::commit_slice()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit_slice.html
[guest]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest
[ZK-STARK]: ../reference-docs/about-starks.md
[Segment]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Segment.html
[ZKP Whitepaper]: https://www.risczero.com/proof-system-in-detail.pdf
[Sequence Diagram]: ./proof-system-sequence-diagram.md
[RISC Zero Study Club]: https://dev.risczero.com/studyclub
[YouTube channel]: https://www.youtube.com/@risczero
[0]: https://www.youtube.com/watch?v=8hwY88xJoyM&list=PLcPzhUaCxlCgig7ofeARMPwQ8vbuD6hC5&index=8
[1]: /api/zkvm
[2]: ../reference-docs/about-starks.md
[3]: ./stark-by-hand.md
[4]: https://docs.google.com/spreadsheets/d/1Onr41OozD62y-B0jIL7bHAH5kf771-o4xvmnHUFpOyo/edit?usp=sharing
[5]: assets/fibonacci-stark.pdf
[6]: https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=5
[7]: https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=2
[8]: https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=3
[9]: https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=4
[10]: https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=1
[11]: https://www.youtube.com/watch?v=hUl8ZB6hpUM&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=6
