---
slug: ./
---

# zkVM Overview

> WARNING: This software is still experimental, we do not recommend it for
> production use.

_If you're ready to start building, check out our [zkVM Quick Start][quickstart]
and our [zkVM example applications][examples]._

The RISC Zero zero-knowledge virtual machine zkVM lets you [prove]
correct execution of arbitrary Rust code. By allowing users to build
zero-knowledge applications that **leverage existing Rust packages**, the RISC
Zero zkVM makes it quick and easy to build powerful verifiable software
applications. Our examples show how to:

- use chess crates to [prove mate-in-one][chess]
- use JSON crate to make [proofs about private data][json]
- use JPG crates to [prove you can find Waldo][waldo]
- use Rust-Ethereum crates like [revm], [ethers], and [alloy] to **[prove
  correct construction of Ethereum blocks][zeth]**.

On any other proving platform, building any of these projects requires starting
from the ground up. By letting developers use the primitives they need, the RISC
Zero zkVM makes verifiable software development a practical reality for projects
of all scales.

We're focused on delivering a first-class developer experience together with
first-class performance. We offer an open-source prover that can prove
computations of any size on standard consumer hardware, and we make it easy to
request/receive proofs remotely with [Bonsai].

The documentation on this site will teach you how to write software for the RISC
Zero zkVM, how to use the zkVM to generate proofs on your own machine, and how
to use Bonsai for remote proof generation.

## Building a zkVM Application

The core of a zkVM application is the [guest program].
The guest program is the part of the application that gets proven.

To prove correct execution of the [guest program]:

1. The [guest program] is compiled to an [ELF binary]. <br/>
2. The [executor] runs the [ELF binary] and records the [session].
3. The [prover] checks and proves the validity of the [session], outputting a
   [receipt].

> **Note:** You only need to worry about the details of step 2 & step 3 if
> you're running the zkVM on your own hardware. See [Host Code 101][host program] for more details on these steps. If you're using [Bonsai] for remote
> proving, you won't need to write host code.

![From Guest Code to Receipt](/diagrams/from-rust-to-receipt.png)

Anyone with a copy of the [receipt] can [verify] the [guest program]'s execution
and read its [publicly shared outputs][journal]. The verification algorithm
receives an [ImageID] as a parameter; the ImageID serves as a cryptographic
identifier for the expected ELF binary.

## Deploying a zkVM Application

Once you've built a zkVM application, you can generate proofs on your own
machine(s) or you can make requests to [Bonsai] to generate proofs as needed.

For local proof generation, we recommend a machine with at least 16GB of RAM.
Options for generating proofs using GPU acceleration and skipping proof
generation are documented in the [feature flags].

## Micro Architecture

The zkVM is a verifiable computer that works like a real embedded RISC-V
micro-processor. This enables developers to more easily develop zk powerful
applications.

### Continuations for limitless computations

Continuations allow the [zkVM] to do large computations by splitting the work
into small, independent [segments] of the same size. This enables proofs
generation on commodity hardware and makes zero knowledge computing widely
accessible. To learn more, read the article on [continuations].

## Next Steps

_Ready to start building zkVM applications?_ <br/>
Check out [zkVM Quickstart][quickstart] & [Guest Code 101][guest program].

_Want to browse some examples?_ <br/>
Check out the [zkVM example applications][examples].

_Curious about performance?_ <br/>
Check the [performance benchmarks][benchmarks] page.

_Looking for information about blockchain integration?_ <br/>
Check out [Bonsai].

_Curious about Zeth?_<br/>
Read the [article][zeth].

[alloy]: https://github.com/alloy-rs
[benchmarks]: ./benchmarks.md
[Bonsai]: ../bonsai/bonsai-overview.md
[cargo]: https://doc.rust-lang.org/cargo/index.html
[chess]: https://github.com/risc0/risc0/tree/release-0.20/examples/chess#zk-checkmate
[continuations]: https://www.risczero.com/news/continuations
[ethers]: https://github.com/ethers-io/ethers.js
[examples]: ./examples.md
[imageID]: /terminology#image-id
[receipt]: ./receipts.md
[ELF binary]: /terminology#elf-binary
[execution trace]: /terminology#execution-trace
[executor]: /terminology#executor
[feature flags]: https://github.com/risc0/risc0#feature-flags
[guest program]: ./guest-code-101.md
[host]: /terminology#host-program
[host program]: ./host-code-101.md
[journal]: /terminology#journal
[json]: https://github.com/risc0/risc0/tree/release-0.20/examples/json
[prove]: /terminology#validity-proof
[proofs]: /terminology#validity-proof
[prover]: /terminology#prover
[quickstart]: ./quickstart.md
[revm]: https://github.com/bluealloy/revm
[segments]: /terminology#segment
[session]: /terminology#session
[verify]: /terminology#verify
[waldo]: https://www.risczero.com/news/waldo
[zeth]: https://risczero.com/news/zeth-release
[zkVM]: /terminology#zero-knowledge-virtual-machine-zkvm
