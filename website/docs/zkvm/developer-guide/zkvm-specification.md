# zkVM Technical Fact Sheet

Like many other execution environments, the zkVM it has unique characteristics
that developers may find helpful when programming the zkVM. The following
details assume familiarity with systems programming concepts. Those who are not
familiar may want to consult additional resources such as [OsDevWiki] to
understand the terminology.

## Introduction

The zkVM is a software emulator that implements a 32-bit RISC-V instruction set.
One thing to note about this implementation is that not all features that one
typically finds in a traditional processor are implemented. This was done to
enable the zkVM to efficiently generate proofs on commodity hardware. While the
emulator does not implement everything, we find that this sufficient to run many
useful computations such as Ethereum block production and cryptographic
signature verification. The following section describes key characteristics of
the zkVM implementation.

## The zkVM Execution Model

The zkVM implements the `RV32IM` instruction set. This is the `RV32I` base
instruction along with the multiplication (`M`) feature. We do not implement
`CRS` instructions. This means that a program does not have what is
traditionally described as privileged and user modes. We do not implement loads
or stores to unaligned addresses. So all addresses must be multiples of `0x4`
and all code must be mapped to addresses divisible by `0x4`.

We extend the `RV32IM` ISA by using the `ECALL` instruction. We do this in order
to add instructions that are specific to zero knowledge computing.

The zkVM does not support interrupts or exceptions and there is no built-in
notion of a scheduler. The zkVM runs programs using a single-thread environment
without preemption, so there is also no need for atomic instructions.

## zkVM Memory Model

The zkVM executes instruction in the order they appear in the ELF. In other words,
instructions are never reordered and the zkVM's memory model is sequentially
consistent. Unlike many processors, the zkVM has no notion of memory caches
and cache-coherency protocols implemented in the zkVM.

## zkVM Memory Layout


## zkVM ECALLS


[OsDevWiki]: https://wiki.osdev.org/Main_Page
