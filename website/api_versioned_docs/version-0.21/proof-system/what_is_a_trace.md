# What is an Execution Trace?

When a piece of code runs on a machine, the **execution trace** is a complete
record of the computation: a snapshot of the full state of the machine at each
clock cycle of the computation.

It's typical to write an execution trace as a rectangular array, where each row
shows the complete state of the machine at a given moment in time, and each
column shows a temporal record of some particular aspect of the computation
(say, the value stored in a particular RISC-V register) at each clock cycle. A
line-by-line analysis of the trace allows for a computational audit with respect
to the program instructions and the underlying computer architecture.

`RISC Zero's computational receipts use cutting-edge technology to audit an
execution trace while preserving computational privacy.`

_The core of a RISC Zero receipt is a
[zk-STARK](../reference-docs/about-starks.md); for a more technical description
of how we turn an execution trace into a zk-STARK, see the [proof system
sequence diagram](./proof-system-sequence-diagram) and our [STARK by
Hand](./stark-by-hand) explainer._
