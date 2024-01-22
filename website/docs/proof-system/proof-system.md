---
sidebar_position: 1
slug: ./
---

# Proof System Overview

<center> <img src="assets/receipt.png" width="600"> </center>
<br/>
When the RISC Zero [zkVM] executes, it produces a [Receipt] that serves as a proof of validity of a given [Session].

To confirm that a [Receipt] was honestly generated, use [Receipt::verify()].

The [Receipt] includes a [journal], which contains the public outputs of the [Session].
The contents of the [journal] are specified by calling [env::commit()] and [env::commit_slice()] in the [guest] code.

In addition to the journal, a receipt makes a number of claims about the program execution.
These claims are summarized in the [ReceiptClaim].

### Types of Receipts
A [Receipt] can take four main forms.

1. A **[flat receipt]** is a vector of [ZK-STARK]s, one for each [segment]. Segments & segment proofs are constructed by the [RISC-V Circuit].
2. A **[succinct receipt]** is a single [ZK-STARK] proving an entire [Session]. The SuccinctReceipt is formed by aggregating the proofs from the [FlatReceipt]. This is accomplished using the [Recursion Circuit]. Users can also aggregate multiple [SuccinctReceipt]s into a single [SuccinctReceipt] using [proof composition].
3. A **[Groth16 receipt]**  is a single [Groth16] proof for an entire [Session]. The Groth16Receipt is formed by verifying a SuccinctReceipt using RISC Zero's [Groth16 circuit].
4. A **[fake receipt]** doesn't contain any proof at all. This feature is offered to enable rapid prototyping. See [Dev Mode] for more information.

<center> <img src="assets/proof-system-layers.png"> </center>

The diagram above shows RISC Zero's full proving stack, including the [RISC-V Circuit], the [Recursion Circuit], and the [Groth16 Circuit]. In this diagram, the [flat receipt] is the collection of 6 stacked receipts, the [succinct receipt] is the single receipt after the last use of FRI, and the [Groth16 Receipt] is the tiny receipt that comes from the Groth16 Circuit.
For a video explanation of this architecture and the associated terminology, check out our [talk from zkSummit 10].

The details of the RISC Zero ZK-STARK protocol are described in our [ZKP Whitepaper] and in this [Sequence Diagram].
Documentation for our Groth16 circuit is TODO.

### Open-Source Proving
All three of these circuits are open-source and permissionless; anyone may generate proofs on their own hardware using the implementations available at our [GitHub].
Users may also choose to delegate the work of proof generation to [Bonsai].

Read more about our philosophy on open-source software [here](https://risczero.com/news/open-source).

## Learn More
In addition to the links in the sidebar, we recommend the following resources:
- [About the zkVM & Bonsai](/api/zkvm)
- [RISC Zero News](https://risczero.com/news)
- [Start Building](/api/zkvm/quickstart)
- [Study Club]

[zkVM]: https://docs.rs/risc0-zkvm
[Receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
[ReceiptClaim]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ReceiptClaim.html
[SegmentReceipts]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipts.html
[SegmentReceipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SegmentReceipt.html
[flat receipt]: https://docs.rs/risc0-zkvm/0.19.1/risc0_zkvm/struct.FlatReceipt.html
[succinct receipt]: https://docs.rs/risc0-zkvm/0.19.1/risc0_zkvm/struct.SuccinctReceipt.html
[Groth16 receipt]: test
[fake receipt]: https://dev.risczero.com/api/zkvm/dev-mode
[session]: https://dev.risczero.com/terminology#session
[Receipt::verify()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#method.verify
[ImageID]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SystemState.html
[journal]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#structfield.journal
[env::commit()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[env::commit_slice()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit_slice.html
[guest]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest
[ZK-STARK]: ../reference-docs/about-starks.md
[segment]: https://dev.risczero.com/terminology#segment
[ZKP Whitepaper]: https://www.risczero.com/proof-system-in-detail.pdf
[Sequence Diagram]: ./proof-system-sequence-diagram.md
[Study Club]: https://dev.risczero.com/studyclub

