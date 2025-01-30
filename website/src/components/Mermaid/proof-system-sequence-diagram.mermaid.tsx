import React from "react";
import Mermaid from ".";

export default function ProofSystemSequenceDiagramMermaid() {
  return (
    <Mermaid
      height={860}
      definition={`
    %% no_run %%
sequenceDiagram
  participant P as Prover
  participant V as Verifier
  Note over P,V: Circuit Setup Phase<br/>The Prover & Verifier agree on the public<br/>parameters for the zkVM circuit.
  Note over P,V: Image ID Setup Phase<br/>Anyone with access to the binary file and the<br/>public parameters can reconstruct the Image ID.
  Note over P: Execute the binary to<br/>construct the Main Execution Trace.
  Note over P: Compute Low Degree<br/>Extension to construct the<br/>Extended Main Execution Trace.
  Note over P: Merklize Extended Main Execution Trace
  P->>V: Send Merkle Root(s) for<br/>Extended Main Execution Trace
  V->>P: Return numerous random<br/>extension field elements.<br/>These are used for a<br/>permutation argument,<br/>a lookup argument, and<br/>a big integer accelerator.
  Note over P: Compute Extended Auxiliary Execution Trace.
  Note over P: Merklize Extended Auxiliary Execution Trace.
  P->>V: Send Merkle Root for<br/>Extended Auxiliary Execution Trace
  Note over P,V: Begin DEEP-ALI Protocol
  V->>P: Return random constraint<br/>mixing parameter, alpha
  Note over P: Use powers of alpha to mix (i.e. linearly combine)<br/>Constraint Polynomials into a Mixed Constraint Polynomial.
  Note over P: Divide by the Zeroes Polynomial<br/>to construct the High Degree Validity Polynomial<br/>Degree(HDVP) = MaxConstraintDegree * TraceDegree
  Note over P: Split High Degree Validity Polynomial<br/>into a few Low Degree Validity Polynomials,<br/>Degree(LDVP) = TraceDegree
  Note over P: Merklize Low Degree Validity Polynomials.
  P->>V: Send Merkle Root<br/>for Low Degree Validity Polynomials
  V->>P: Return a random extension<br/>field element, which serves<br/>as an out-of-domain<br/>evaluation point.
  P->>V: Send "necessary evaluations"<br/>required to evaluate constraints<br/>at out-of-domain evaluation point<br/>and coefficients of DEEP polynomials
  V->>P: Return random<br/>extension field element<br/>for FRI batching
  Note over P: Use FRI batching randomness to mix<br/> the DEEP polynomials, forming the FRI polynomial.
  P->>V: Send Merkle Root<br/>for the FRI polynomial
  Note over P,V: Begin FRI protocol.
  Note over P,V: Details of FRI are omitted for brevity.
`}
    />
  );
}
