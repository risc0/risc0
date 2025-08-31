# FAQ

---

## Contents

- [ZK Basics](#zk-basics)
- [Building on the zkVM](#building-on-the-zkvm)
  - [Code Troubleshooting](#code-troubleshooting)
  - [zkVM Application Design](#zkvm-application-design)
  - [Features, Performance, and Limitations](#features-performance-and-limitations)
- [The RISC Zero Circuits](#the-risc-zero-circuits)
- [Security](#security)

---

## ZK Basics

<a class="anchor" id="zkp" />

<details closed>
  <summary>
    Q: What is a zero-knowledge proof?
  </summary>

  A zero-knowledge proof (or ZKP) is <a href="https://en.wikipedia.org/wiki/Zero-knowledge_proof">"a method by which one party (the prover) can prove to another party (the verifier) that a given statement is true \[without] conveying any additional information"</a>.
  RISC Zero's zkVM makes it easy to produce ZKPs to prove the correct execution of arbitrary code. <br />

  <br />

  When Alice executes code inside the zkVM, Alice gets back a <a href="https://dev.risczero.com/terminology#receipt">receipt</a>.
  Alice can pass the receipt to Bob, who can then <a href="https://dev.risczero.com/terminology#verify">verify</a> the receipt.

  <br />

  <br />

  By verifying the receipt, Bob can confirm that the expected code executed and produced the asserted results.
  Any inputs Alice passes to the program during execution will be private unless Alice chooses to share them.
</details>

<br />

## Building on the zkVM

### Code Troubleshooting

<a class="anchor" id="build-errors" />

<details closed>
  <summary>
    Q: I'm running into build errors. Where should I look for help?
  </summary>

  A: Some known issues and workarounds are tracked on GitHub under the <a href="https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22">"rust guest workarounds"</a> tag.
  If you can't find your problem here you can open a <a href="https://github.com/risc0/risc0/issues">new issue</a> or reach out to us on <a href="https://discord.gg/risczero">Discord</a>.
</details>

<br />

### zkVM Application Design

<a class="anchor" id="using-receipts" />

<details closed>
  <summary>
    Q:
    What do I do with the receipt once I've created it?
  </summary>

  A:
  After Alice creates a <a href="https://dev.risczero.com/terminology#receipt">receipt</a>, she'll typically pass it to Bob who will want to <a href="https://dev.risczero.com/terminology#verify">verify</a> its authenticity.
  At a minimum, Bob will need access to the <a href="https://dev.risczero.com/terminology#image-id">ImageID</a> of the expected program.
  For most cases, Bob will want to know what code was run, and will therefore also want the <a href="https://dev.risczero.com/terminology#elf-binary">ELF file</a> or the source code that generated it.
  Bob can verify the receipt was created by this code by constructing the <a href="https://dev.risczero.com/terminology#image-id">ImageID</a> from the given ELF file and using it for verification. <br />

  <br />

  In our <a href="https://github.com/risc0/risc0/tree/v0.18.0/examples">examples</a>, the receipt is generated and verified within the same program, but typically the receipt will be passed to a third party for verification.
</details>

<a class="anchor" id="io-buffer-overflows" />

<details closed>
  <summary>
    Q:  When can information be shared with the guest zkVM? How do you prevent buffer overflows?
  </summary>

  A:
  Data can be sent during program execution from the host to the guest via a memory map.
  The host-writeable memory is write-once, meaning that adjacent memory regions cannot be overwritten and executed.
</details>

<a class="anchor" id="what-should-guest-do" />

<details closed>
  <summary>
    Q:
    How do I know which computations should be performed in the guest zkVM, and which can be offloaded to the host?
  </summary>

  A: If you don't need to perform a computation securely, if others don't rely on it, and if it doesn't produce outputs that others rely on, it can probably be performed outside of the zkVM. <br />

  <br />

  However, consider that code run in the RISC Zero zkVM can be shown to behave as expected even on a host that is entirely untrusted.
  To get the most value out of this guarantee, we recommend dividing the computational labor with an untrusted host in mind.
  That is, other parties should not need to trust the host's output or operations in order to benefit from the work done in the zkVM.
</details>

<details closed>
  <a class="anchor" id="image-id" />

  <summary>
    Q:
    What exactly is the ImageID of a zkVM application?
  </summary>

  A: The ImageID is a unique identifier given to a zkVM application. It cryptographically relates the application binary (ELF) to its produced receipts. This bound is a critical security property that ensures applications run unaltered.

  Specifically, the ImageID is a Merklization of the initial zkVM memory state, or MemoryImage, produced when the zkVM loads the application binary. The memory state is hashed to produce a single deterministic value via a pure function resembling:

  ```rust ignore
  fn compute_image_id(used_elf_pages, page_size, page_table_addr, pc) -> ImageID
  ```

  Note: Only the loaded parts of the application binary, `used_elf_pages,` are utilized to calculate the ImageID. Consequently, the hashing does not include elements of a compiled binary that do not affect program meaning, e.g., debug information and timestamps.

  As a consequence, _functionally equivalent_ binaries, from the zkVM perspective, will result in identical ImageIDs. However, the compiled binaries (ELFs) may be bitwise different if hashed directly from disk. _This does not affect the zkVM security model._
</details>

<br />

### Features, Performance, and Limitations

<a class="anchor" id="benchmarks" />

<details closed>
  <summary>
    Q: Are performance benchmarks available?
  </summary>

  A: Yes. We have a <a href="https://reports.risczero.com/">benchmarks website</a>, and you can also generate your own benchmarks. More details are available on the <a href="https://dev.risczero.com/zkvm/benchmarks">benchmarks page</a>.
</details>

<a class="anchor" id="language-support" />

<details closed>
  <summary>
    Q: What languages can I use to develop zkVM applications?
  </summary>

  A: We recommend Rust for writing zkVM applications.
  Although technically the zkVM can execute any RISC-V code, we only have documentation and API support for Rust development.
  Development in C++ is also possible, but proceed at your own risk.
  You can reference the <a href="https://github.com/risc0/risc0/tree/v0.11.0/examples/cpp">examples in C++</a> that were included in the 0.11 release, although we've made substantial changes since that release, and we're available to answer questions on <a href="https://discord.gg/risczero"> Discord</a> as needed.
</details>

<a class="anchor" id="max-length" />

<details closed>
  <summary>
    Q: What is the maximum execution length for a program running on the zkVM?
  </summary>

  A: Since we added support for <a href="https://www.risczero.com/news/continuations"> continuations</a>, the execution length can be very large.
  So far, we've made proofs for executions that exceed 4 billion cycles, and there's plenty of room to expand that further.
</details>

<a class="anchor" id="rust-crate" />

<details closed>
  <summary>
    Q: I have a specific Rust crate I'd like to use. Will it work inside the zkVM?
  </summary>

  A: Each night, we check the top 1000 Rust crates for zkVM compatibility.
  You can see the results <a href="https://reports.risczero.com/crates-validation"> here</a>.
  As of this writing, 71% of the top 1000 Rust crates work inside the zkVM. <br />

  <br />

  If the crate you'd like to use isn't working, there may be a workaround <a href="https://github.com/risc0/risc0/issues?q=is%3Aissue+is%3Aopen+label%3A%22rust+guest+workarounds%22">here</a>.
  If there's not already a workaround, please <a href="https://github.com/risc0/risc0/issues/new">open an issue</a> or reach out on <a href="https://discord.gg/risczero">Discord.</a>
</details>

<a class="anchor" id="large-data" />

<details closed>
  <summary>
    Q:
    If I want the guest to process large volumes of data during execution, I might be constrained by space limitations. What are my options?
  </summary>

  A:
  If data is loaded from the host to restrict guest program size, the most significant limitation on zkVM data processing is a constraint on instruction cycles.
  Loading data into the guest costs instruction cycles, as does data processing.

  There are workarounds for data limitations if the data is only included to ensure that its integrity becomes part of the proof of computation.
  If the data can be processed externally and simply needs to be verifiably unchanged, consider processing data externally and sending the guest a Merkle proof or (if no processing is needed) generating a SHA of a large dataset.

  In the future, we plan to lift these processing limitations using continuations and recursion.
</details>

<a class="anchor" id="acceleration" />

<details closed>
  <summary>
    Q:
    I'd like to speed up the processing done inside the zkVM. What are my options?
  </summary>

  A:
  For cryptographic operations, it is possible to build 'accelerator' circuits such as our implementation of SHA256.
  Fast cryptography is sufficient to support many 'DeFi' applications.
  For many other applications, it is possible to perform most computation on the host (outside the zkVM) and then verify the results in the zkVM.
</details>

## The RISC Zero Circuits

<a class="anchor" id="dont-write-circuits" />

<details closed>
  <summary>
    Q: Do I need to write a ZK circuit to build on RISC Zero?
  </summary>

  A: No!
  We take care of the circuit building so that you can focus on building applications.
  Everything you'll need to build is outlined in the <a href="https://dev.risczero.com/zkvm">zkVM docs</a> and the <a href="https://dev.risczero.com/bonsai">Bonsai docs</a>.
</details>

<a class="anchor" id="circuits" />

<details closed>
  <summary>
    Q: What do RISC Zero's circuits do?
  </summary>

  RISC Zero has three circuits: one that executes RISC-V code, one that's used for recursion, and one that is used for a STARK-to-SNARK conversion.

  - The RISC-V circuit receives an ELF binary file as a public input and private inputs from the host; the output of the RISC-V circuit is a receipt.
  - The recursion circuit is specialized to prove the verification of RISC Zero receipts; this circuit is used in order to compress many RISC Zero receipts into a single receipt.
  - The STARK-to-SNARK circuit is used to translate a STARK proof into a SNARK proof, which enables on-chain verification.
</details>

<br />

## Security

<a class="anchor" id="image-id-security" />

<details closed>
  <summary>
    Q:
    How can we use the ImageID to determine if an application is altered before execution?
  </summary>

  A: The ImageID is determined from an application's compiled binary (ELF), explained in detail <a href="https://dev.risczero.com/faq#image-id">above.</a>

  Someone wishing to confirm that a receipt corresponds to specific Rust source code can locally reproduce a binary targeting the RISC Zero zkVM using our reproducible build tool and verify that the resulting ImageID matches the ImageID in the receipt.

  For example, building our [builtin zkVM test functions](https://github.com/risc0/risc0/tree/main/risc0/zkvm/methods/guest):

  ```bash
  cargo risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml
  ```

  will produce similar output to:

  ```bash
  ELFs ready at:
  ImageID: 417778745b43c82a20db33a55c2b1d6e0805e0fa7eec80c9654e7321121e97af - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/multi_test"
  ImageID: c7c399c25ecf26b79e987ed060efce1f0836a594ad1059b138b6ed2f123dad38 - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/hello_commit"
  ImageID: a51a4b747f18b7e5f36a016bdd6f885e8293dbfca2759d6667a6df8edd5f2489 - "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker/risc0_zkvm_methods_guest/slice_io"
  ```

  These ImageIDs will stay consistent across all builds due to a containerized process working together with Cargo working norms. You can find more about our reproducible builds and how we test them in this [pull request.](https://github.com/risc0/risc0/pull/799)
</details>

<a class="anchor" id="tampering-with-code" />

<details closed>
  <summary>
    Q: If the guest zkVM lives on the host machine, can't the host still tamper with the application?
  </summary>

  A: Like other zk-STARKs, RISC Zero's implementation makes it cryptographically infeasible to generate an invalid receipt:

  - If the binary is modified, then the receipt's seal will not match the ImageID of the expected binary.
  - If the execution is modified, then the execution trace will be invalid.
  - If the output is modified, then the journal's hash will not match the hash recorded in the receipt.
</details>
