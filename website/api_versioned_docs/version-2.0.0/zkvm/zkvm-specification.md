# zkVM Technical Specification

Like many other execution environments, the zkVM has unique characteristics that
developers may find helpful when programming. The following description of zkVM
characteristics assume familiarity with systems programming concepts. Those who
are not familiar may want to consult additional resources such as [OsDevWiki] to
understand the terminology.

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

## The User/Kernel Split

The RISC Zero zkVM implements user and machine modes. The guest code running
on the zkVM is divided into two components: the kernel and user-space programs,
both executing the rv32im instruction set. The kernel functions as an operating
system kernel, while user programs run in a separate user mode. This separation
ensures that the kernel's resources remain protected from user-space
code.

While running, a user program may invoke an ECALL to perform I/O, call
accelerators, or run custom system call handlers. When an ECALL is run in the
user code, the zkVM traps the call and transfers control to the kernel.
The kernel processes the request by dispatching it to the appropriate system
call handler, which may involve delegating computation to the host. The dispatch
is implemented in the kernel. Once the host returns the results, the kernel
processes the response, delivers the result back to the user program, and
resumes execution in user space.

## zkVM Memory Layout

The following table summarizes the layout of the zkVM guest memory

| Address Range             | Size   | Name          | Description                                                                                   |
| ------------------------- | ------ | ------------- | --------------------------------------------------------------------------------------------- |
| `0x00000000 - 0x0000FFFF` | 64 KiB | Invalid page  | This page of memory is invalid, so that dereferencing a NULL address will result in a failure |
| `0x00010000 - 0xBFFFFFFF` | ~3 GB  | User Memory   | Contains code, heap, and stack of the guest program                                           |
| `0xC0000000 - 0xFF000000` | ~1 GB  | Kernel Memory | Contains kernel code and data such as ecall/trap dispatch, register contents                  |

## zkVM Memory Model

The zkVM executes instructions in order; in other words, instructions are never
reordered and the zkVM's memory model is sequentially consistent. Unlike many
processors, the zkVM has no notion of traditional memory caches and
cache-coherency protocols.

[OsDevWiki]: https://wiki.osdev.org/Main_Page
