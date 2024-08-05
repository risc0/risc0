# Receipts 101

_A brief introduction to the RISC Zero [receipt]._

## What is a receipt?

A receipt gives the results of your program along with proof that they were
produced honestly.

![From Guest Code to Receipt](/diagrams/from-rust-to-receipt.png)

When you execute your [zkVM application][zkvm], the output of your application
is included in a [receipt]. The [receipt] serves as a succinct [validity proof]
for the [execution] of your application. Receipts can be passed to third parties
and [verified][verify] in order to cryptographically attest to the validity of
your application's output.

<!-- The following text is duplicated from the definition of "receipt" on the terminology page.-->

The receipt consists of a [journal] and a [seal]. The journal attests to the
public outputs of the program, and the seal is the opaque blob that
cryptographically attests to the validity of the receipt.

<!-- End receipt definition. -->

## How are receipts used?

Suppose Alice and Bob have agreed on some computation that needs to get done. In
particular, they've agreed on some zkVM [guest program], and they each have
access to the source code and the [Image ID] for that guest program. (In
practice, Bob may retrieve the Image ID either by constructing it himself or
retrieving it from a trusted channel.)

Alice runs the zkVM to generate a receipt, and then Alice sends the receipt to
Bob. After receiving the receipt, Bob can:

- inspect the receipt to extract the [journal]
- [verify] the receipt to ensure that:
  - the [execution] was valid
  - the [guest program] that executed was consistent with the expected [image
    ID].

## Extracting the Journal

The [journal] contains the public outputs of the computation. Users can extract
the journal from a receipt using [receipt.journal].

## Verifying a Receipt

[Verifying][verify] the receipt provides cryptographic assurance that the [journal] was
created honestly using the [guest program] with the expected [Image ID]. Users
can verify the receipt using [receipt.verify()].

## Serializing and Deserializing Receipts

For serializing and deserializing, you can use [serde] which supports many
encoding formats. There isn't a one-size-fits-all solution here, but one option
is:

`let bytes = bincode::serialize(&receipt);`

[execution]: /terminology#execution-trace
[guest program]: /terminology#guest-program
[Image ID]: /terminology#image-id
[journal]: /terminology#journal
[receipt]: /terminology#receipt
[receipt.verify()]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/struct.Receipt.html#method.verify
[receipt.journal]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/struct.Receipt.html#structfield.journal
[seal]: /terminology#seal
[serde]: https://crates.io/crates/serde
[validity proof]: /terminology#validity-proof
[verify]: /terminology#verify
[quickstart]: ./quickstart.md
[zkvm]: ./zkvm_overview.md
