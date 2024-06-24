---
slug: ./
---

# zkVM Overview

The RISC Zero zero-knowledge virtual machine [zkVM] (zkVM) lets you [prove]
correct execution of arbitrary Rust code. By allowing users to build
zero-knowledge applications that **leverage existing Rust packages**, the RISC
Zero zkVM makes it quick and easy to build powerful verifiable software
applications.

To learn more about what this enables, check out our [use cases] page.

If you're ready to start building, check out our [zkVM Quick Start][quickstart]
and our [zkVM example applications][examples].

## What are the components of a zkVM application?

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

## Next Steps

_Ready to start building zkVM applications?_ <br/>
Check out [zkVM Quickstart][quickstart] & [Guest Code 101][guest program].

_Want to browse some examples?_ <br/>
Check out the [zkVM example applications][examples].

_Curious about performance?_ <br/>
Check the [performance benchmarks][benchmarks] page.

_Looking for information about remote proving?_ <br/>
Check out [Bonsai].

_Looking for information about blockchain integration?_ <br/>
Check out our [Bonsai on Eth] page.

[alloy]: https://github.com/alloy-rs
[benchmarks]: ./benchmarks.md
[Bonsai]: ../generating-proofs/remote-proving.md
[Bonsai on Eth]: ../blockchain-integration/bonsai-on-eth.md
[cargo]: https://doc.rust-lang.org/cargo/index.html
[chess]: https://github.com/risc0/risc0/tree/main/examples/chess#zk-checkmate
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
[json]: https://github.com/risc0/risc0/tree/main/examples/json
[prove]: /terminology#validity-proof
[proofs]: /terminology#validity-proof
[prover]: /terminology#prover
[quickstart]: ./quickstart.md
[revm]: https://github.com/bluealloy/revm
[segments]: /terminology#segment
[session]: /terminology#session
[use cases]: ../use-cases.md
[verify]: /terminology#verify
[waldo]: https://www.risczero.com/news/waldo
[zeth]: https://risczero.com/news/zeth-release
[zkVM]: /terminology#zero-knowledge-virtual-machine-zkvm
