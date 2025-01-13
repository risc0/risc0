import React from "react";
import Mermaid from ".";

export default function RecursionMermaid() {
  return (
    <Mermaid
      height={580}
      definition={`
    %% no_run %%
flowchart TB

execute(".execute()")
--> Session

subgraph Session["<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Session.html'>Session</a>"]
direction TB
s1("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s2("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s3("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s4("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s5("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
s6("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Segment.html'>Segment</a>")
end

  s1-->ps1(".prove_segment()")
  s2-->ps2(".prove_segment()")
  s3-->ps3(".prove_segment()")
  s4-->ps4(".prove_segment()")
  s5-->ps5(".prove_segment()")
  s6-->ps6(".prove_segment()")

subgraph CompositeReceipt["<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.CompositeReceipt.html'>CompositeReceipt</a>"]
direction TB
c1("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c2("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c3("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c4("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c5("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
c6("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SegmentReceipt.html'>SegmentReceipt</a>")
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

l1-->suc1("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l2-->suc2("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l3-->suc3("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l4-->suc4("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l5-->suc5("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
l6-->suc6("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")


suc1-->j1(".join()")
suc2-->j1
suc3-->j2(".join()")
suc4-->j2
suc5-->j3(".join()")
suc6-->j3

j1-->suc11("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
j2-->suc12("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")
j3-->suc13("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc11-->j11(".join()")
suc12-->j11

j11-->suc21("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc21-->j21(".join()")
suc13-->j21

j21-->suc31("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc31-->id(".identity_p254()")

id-->suc41("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.SuccinctReceipt.html'>SuccinctReceipt</a>")

suc41-->compress(".compress()")

compress-->groth16("<a target="_blank" href='https://docs.rs/risc0-zkvm/latest/risc0_zkvm/struct.Groth16Receipt.html'>Groth16Receipt</a>")
  `}
    />
  );
}
