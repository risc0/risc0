# zkVM Technical Specification

Like many other execution environments, the zkVM has unique characteristics
that developers may find helpful when programming. The following description of
zkVM characteristics assume familiarity with systems programming concepts. Those
who are not familiar may want to consult additional resources such as
[OsDevWiki] to understand the terminology.

## Introduction

The zkVM is a software emulator that implements a 32-bit RISC-V instruction set.
One thing to note about the zkVM is that it does not use features that one
typically finds in a traditional processor. This was done to enable the zkVM to
efficiently generate proofs on commodity hardware. While the emulator is more
simple than hardware processors, this is sufficient to run many useful
computations such as Ethereum block production and cryptographic signature
verification. The following section describes key characteristics of the zkVM
implementation.

## The zkVM Execution Model

The zkVM implements the `RV32IM` instruction set. This is the `RV32I` base
instruction along with the multiplication (`M`) feature. We do not implement
`CRS` instructions. This means that a program does not have what is typically
described as privileged and user modes. We do not implement loads or stores to
unaligned addresses. So all addresses must be multiples of `0x4` and all code
must be mapped to addresses divisible by `0x4`.

We extend the `RV32IM` ISA by using the `ECALL` instruction. We do this in order
to add instructions that are specific to zero knowledge computing.

The zkVM does not support interrupts and there is no built-in notion of a
scheduler. The zkVM runs programs using a single-thread environment without
preemption, so there is also no support for atomic instructions. If the
execution raises an exception such as an unaligned access, the execution
terminates without executing exception handlers.

## zkVM Memory Layout

The following table summarizes the layout of the zkVM memory

| Address Range             | Size   | Name          | Description                                                                                   |
| ------------------------- | ------ | ------------- | --------------------------------------------------------------------------------------------- |
| `0x00000000 - 0x000003ff` | 1 KB   | Invalid page  | This page of memory is invalid, so that dereferencing a NULL address will result in a failure |
| `0x00000400 - 0x0BFFFFFF` | 192 MB | User Memory   | Contains code, heap, and stack of the guest program                                           |
| `0x0C000000 - 0x0CFFFFFF` | 16 MB  | System Memory | Contains RISC-V registers and non-leaf Merkle tree nodes for the page table                   |
| `0x0D000000 - 0x0DFFFFFF` | 16 MB  | Page Table    | Contains the Page Table                                                                       |

## zkVM Memory Model

The zkVM executes instructions in order; in other
words, instructions are never reordered and the zkVM's memory model is
sequentially consistent. Unlike many processors, the zkVM has no notion of
traditional memory caches and cache-coherency protocols implemented in the zkVM.

[OsDevWiki]: https://wiki.osdev.org/Main_Page
