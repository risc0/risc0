# Recursive Proving

RISC Zero's zkVM uses recursive proving in order to achieve unbounded computation size, constant proof size, proof aggregation, and proof composition.

:::tip

[prove_with_opts] allows users to choose between [composite, succinct or groth16 receipts].

:::

The rest of this page describes low-level details that are not necessary for users.

## Recursive Proving Process

The end-to-end process for proof generation is shown in the following diagram.

```mermaid
flowchart LR

execute(".execute()")
--> Session

subgraph Session["<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Session.html'>Session</a>"]
direction TB
s1("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s2("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s3("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s4("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s5("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s6("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
end

  s1-->ps1(".prove_segment()")
  s2-->ps2(".prove_segment()")
  s3-->ps3(".prove_segment()")
  s4-->ps4(".prove_segment()")
  s5-->ps5(".prove_segment()")
  s6-->ps6(".prove_segment()")

subgraph CompositeReceipt["<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.CompositeReceipt.html'>CompositeReceipt</a>"]
direction TB
c1("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c2("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c3("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c4("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c5("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c6("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
end

ps1-->c1
ps2-->c2
ps3-->c3
ps4-->c4
ps5-->c5
ps6-->c6


c1-->l1(".lift()")
c2-->l2(".lift()")
c3-->l3(".lift()")
c4-->l4(".lift()")
c5-->l5(".lift()")
c6-->l6(".lift()")

l1-->suc1("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l2-->suc2("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l3-->suc3("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l4-->suc4("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l5-->suc5("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l6-->suc6("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")


suc1-->j1(".join()")
suc2-->j1
suc3-->j2(".join()")
suc4-->j2
suc5-->j3(".join()")
suc6-->j3

j1-->suc11("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
j2-->suc12("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
j3-->suc13("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc11-->j11(".join()")
suc12-->j11

j11-->suc21("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc21-->j21(".join()")
suc13-->j21

j21-->suc31("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc31-->id(".identity_p254()")

id-->suc41("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc41-->compress(".compress()")

compress-->groth16("<a href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Groth16Receipt.html'>Groth16Receipt</a>")
```

To summarize the diagram:

1. The program is _executed_, resulting in a collection of _Segments_.
1. Each _Segment_ is proven, resulting in a _SegmentReceipt_.
1. Each _SegmentReceipt_ is _lifted_, resulting in a _SuccinctReceipt_.
1. Pairs of _SuccinctReceipts_ are _joined_, resulting in another _SuccinctReceipt_. This continues until a single _SuccinctReceipt_ remains.
1. The final _SuccinctReceipt_ is passed through _identity_p254_, which prepares for Groth16 proving.
1. The _SuccinctReceipt_ is _compressed_, generating a _Groth16Receipt_.

The _Groth16Receipt_ can now be posted on-chain and verified by the [RISC Zero Verifier Contract].

## Recursive Circuit Architecture

RISC Zero's zkVM consists of three circuits.

1. The RISC-V Circuit is a STARK circuit that proves correct execution of RISC-V programs.
1. The Recursion Circuit is a separate STARK circuit, that's designed to efficiently generate proofs for the verification of STARK proofs and to support the integration of custom accelerator circuits into the zkVM.
   This circuit has a similar architecture to the RISC-V Circuit, but with fewer columns and a much simpler instruction set.
   The same [proof system] is used for both the RISC-V Circuit and the Recursion Circuit.
1. The STARK-to-SNARK Circuit is an R1CS circuit that proves verification of proofs from the Recursion Circuit.

## Recursion Programs
The Recursion Circuit supports a number of programs, including `lift()`, `join()`, `resolve()`, and `identity_p254()`.
Instead, users should access recursion via the [Prover].

To aid in conceptual understanding, we offer the following explanations of the recursion programs:

1. The `lift()` program verifies a STARK proof from the RISC-V Prover, using the Recursion Prover. This recursion proof has a single constant-time verification procedure, with respect to the original segment length, and is then used as the input to all other recursion programs (e.g. join, resolve, and identity_p254).

1. The `join()` program verifies two proofs from the Recursion Prover, using the Recursion Prover. By repeated application of `join()`, any number of receipts for execution spans within the same session can be compressed into a single receipt for the entire session.

1. The `identity_p254()` program verifies a proof from the Recursion Prover using the Poseidon254 hash function. The identity_p254 program is used as the last step in the prover pipeline before running the Groth16 prover.

## STARK-to-SNARK Wrapping
All of the recursion programs in the previous section output a [SuccinctReceipt], which is a STARK proof (~200kB)

The final step in the recursion process is `compress()`, which outputs a [Groth16Receipt], which can be verified on-chain using the [RISC Zero Verifier Contract].

[composite, succinct or groth16 receipts]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/enum.ReceiptKind.html
[Groth16Receipt]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Groth16Receipt.html
[proof system]: ../docs/proof-system/proof-system-sequence-diagram.md
[prove_with_opts]: https://docs.rs/risc0-zkvm/1.0/risc0_zkvm/trait.Prover.html#method.prove_with_opts
[Prover]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/trait.Prover.html#method.prove_with_opts
[Receipt]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Receipt.html
[RISC Zero Verifier Contract]: blockchain-integration/contracts/verifier.md
[SuccinctReceipt]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html