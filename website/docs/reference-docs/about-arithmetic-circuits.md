# About Arithmetic Circuits

[Arithmetic circuits][3] consist of a collection of wires and gates, where the wires hold [elements of a finite field][0] and each gate computes either finite field addition or finite field multiplication.
In contrast, in an [electronic circuit][1], the wires either contain electrical signal or they don't, and each gate may compute a variety of logical operations.

Arithmetic circuits are central to zero-knowledge proof techniques: SNARKs and STARKs prove integrity of an execution of an arithmetic circuit.

## Arithmetic Circuits as Polynomials

Because arithmetic circuits consist only of addition and multiplication, the circuit can be translated into a polynomial. In other words, the output(s) of the circuit can be expressed as a multi-variate polynomial, $C(x_1,\ldots,x_n)$ where

- $n$ is the number of inputs to the polynomial, and
- the degree of $C$ is bounded by the number of multiplications in the circuit.

![][2]

The circuit pictured above can be written as $C(x_1, x_2) = (x_1+x_2)\cdot x_2 \cdot (x_2+1)$. This simple example is drawn from [Wikipedia][3].

## Two Approaches to Building with ZK

- Option 1: Build app-specific arithmetic circuits
- Option 2: Build on top of a zero-knowledge virtual machine, which receives a binary file as an input and outputs a proof of execution.

At RISC Zero, we adopt the latter approach: we've written a [RISC-V circuit][4], which emulates rv32im.
The rv32im circuit receives a RISC-V binary and some user specified input, and generates an [execution trace][5].

If the execution trace is valid, the [Prover](https://docs.rs/risc0-zkvm/*/risc0_zkvm/trait.Prover.html) generates a [receipt] that can be [verified] by a skeptical third party.

## RISC Zero's Circuits

In addition to the rv32im circuit, we have built:

- an accelerator circuit for SHA-256
- a recursion circuit, which receives two receipts and produces a single recursion receipt.

## Additional Resources

- Wikipedia page on [arithmetic circuit complexity][3]
- [From programs to arithmetic circuits](https://www.youtube.com/watch?v=0M0pAubEjz8&list=PLBJMt6zV1c7Gh9Utg-Vng2V6EYVidTFCC&index=4): YouTube video from David Wong

[verified]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html#method.verify
[receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
[0]: about-finite-fields.md
[1]: https://en.wikipedia.org/wiki/Electronic_circuit
[2]: assets/arithmeticcircuit.png
[3]: https://en.wikipedia.org/wiki/Arithmetic_circuit_complexity
[4]: https://docs.rs/risc0-circuit-rv32im
[5]: ../proof-system/what_is_a_trace.md
[6]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/trait.Prover.html
[7]: https://en.wikipedia.org/wiki/Arithmetic_circuit_complexity
[8]: https://www.youtube.com/watch?v=0M0pAubEjz8&list=PLBJMt6zV1c7Gh9Utg-Vng2V6EYVidTFCC&index=4
