# About RISC-V

[RISC-V](https://en.wikipedia.org/wiki/RISC-V) is a minimal, modular [Von Neumann architecture][0].

## Relevance in RISC Zero

The simplicity of RISC-V as well as the maturity of the RISC-V ecosystem makes it ideal for a zero-knowledge virtual machine.
RISC Zero's [zkVM][1] implements the RISC-V rv32im specification, which consists of the rv32i base with the multiplication extension.
This means that developers can write code in languages such as Rust, Go, and C, compile the code to RISC-V assembly code, and execute it on the zkVM.

## Documentation

The specification of rv32im is defined in [The RISC-V Instruction Set Manual, Volume I: User-Level ISA][2].
A succinct summary of the architecture is available [here][3]

## Suggested Reading and Videos

For more on how these ideas fit into RISC Zero's system, we recommend:

- RISC Zero's talk from zk Summit 7: [Encoding Von-Neumann Architectures in Zero-Knowledge Proof Systems](https://www.youtube.com/watch?v=od033ugtlYQ&list=PLcPzhUaCxlCgCvzkkaBWzVuHdBRsTNxj1&index=7)
- RISC Zero Study Club: What is RISC-V and what does it have to do with RISC Zero's zkVM -- [video](https://www.youtube.com/watch?v=11DIflEwx50&list=PLcPzhUaCxlCjdhONxEYZ1dgKjZh3ZvPtl&index=5&t=1s) and [slides][5]

[0]: https://en.wikipedia.org/wiki/Von_Neumann_architecture
[1]: /api/zkvm
[2]: https://riscv.org/wp-content/uploads/2019/12/riscv-spec-20191213.pdf
[3]: https://github.com/jameslzhu/riscv-card/blob/master/riscv-card.pdf
[4]: https://www.youtube.com/watch?v=od033ugtlYQ&list=PLcPzhUaCxlCgCvzkkaBWzVuHdBRsTNxj1&index=7
[5]: https://drive.google.com/file/d/1p7E5Sgi__5_CevGKHpTwrlb0KWjSaYPU/view
