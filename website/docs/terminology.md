# Key Terminology

### Assumption

An assumption is [receipt claim] upon which a [receipt] is [conditional].
When the [guest] uses [composition] to verify a receipt in the [zkVM], an assumption is added to the [receipt].
This assumption can be proven and resolved later, either through [recursion] or by providing proof of the assumption to the verifier.

### Circuit

A mathematical construct that acts as the "CPU" of the [zkVM] in a manner that enables creating [proofs]. <br/>
See also: [Arithmetic Circuits]

### Clock cycles

The smallest unit of compute in the zkVM [circuit], analogous to a clock cycle on a physical CPU.
The complexity of a [guest program]'s [execution] is measured in clock cycles as they directly affect the memory, proof size, and time performance of the [zkVM].

Generally, a single cycle corresponds to a single [RISC-V] operation. However, some operations require two cycles.

See the [Optimization Guide](/api/zkvm/optimization) for more information about the zkVM cycles and performance.

### Commit

Append data to the [journal]. <br/>
See also: [env::commit()]

### Composition

As of our 0.20 release, the [zkVM] supports verification of RISC Zero receipts inside the RISC Zero [guest] through a feature known as composition.
With this, multiple zkVM programs can be _composed_ and produce a single receipt that verifies all computation done to reach the final result.

Some use cases for composition include:

- Splitting a program into multiple parts, proven by different parties, to preserve privacy and data ownership of each party.
  - E.g. Produce a proof that a ciphertext is a correct encryption of some value to a valid public key.
  - E.g. Produce a proof for a database query by joining receipts from the query over each privately held shard.
- Aggregating many proofs into one for efficient batch verification.
  - E.g. Produce a proof for a block of transactions, where each transaction is itself verified by a receipt.
- Creating a single receipt for a workflow that might be split into many different operations.
  - E.g. Produce a single receipt for the result of an image processing pipeline, where different filters are in their own guests.

### Conditional

A [receipt] can be described as "conditional" if it is only true when one or more unproven [assumptions] are also true.
When the [assumptions] are not proven to be true, a conditional receipt does not provide any guarantees, and so verifiers will reject conditional receipts.
A conditional receipt can be made unconditional by providing receipts proving all [assumptions].
Conditional receipts are a part of the [composition] feature.

### Continuations

As of our 0.15 release, the [zkVM] uses continuations to enable proof generation for very large programs without blowing up memory requirements.
Large proof generation is made possible by splitting the execution trace for a single [session] into a number of [segments], and proving those segments independently. <br/>
See also: [Continuations study club], [Continuations blog]

### Control ID

The control ID is the Merkle hash of the contents of the control columns, which are assumed to be known to the verifier as part of the circuit definition.

The control ID is the first entry in the [seal] and plays a key role in defining the operations of the circuit. Verifying a [receipt] involves:

- Checking the control ID on the receipt against the control ID for the expected version of the zkVM.
- Verifying the validity of the Merkle branches for various entries of the Control columns.

For a closer look at how the control columns are used to manage constraint enforcement, check out our [STARK by Hand] explainer.

### Control Root

The control root is the Merkle hash of a set of [control ID]s.

The control root plays a key role in enforcing zkVM version control. Each [control ID] identifies one [recursion program]; the control root identifies the list of allowed recursion programs. When the RISC-V circuit or recursion programs change, the control root is updated to reflect the new set of allowed functions.

This design allows for updates to the [RISC-V circuit] without necessitating a new trusted setup for the [Groth16 circuit]. <br/>
See also: [Code reference for control root]

### Deterministic Builds

A compilation process is called "deterministic" (or "reproducible") if it reliably produces the same binary file, on a byte-by-byte level.

In the context of RISC Zero application development, deterministic builds are necessary to ensure a clear linkage between the source code for the [guest program] and the resulting [Image ID][ImageID].

To access deterministic builds for your zkVM application, use [`cargo risczero build`]. Deterministic builds are made possible by running the `rustc` compiler inside a Docker container.

### ELF Binary

The executable format for the [RISC-V] instruction set.
Each [method] in a [guest program] is written in Rust and compiled into an ELF binary before execution begins. Then, the ELF binary is [executed] and [proven].

### Execute

Run a [method] inside the [zkVM] and produce an [execution trace] which can be used by the [prover] to create a [proof] of correct execution.

### Executor

The portion of the [zkVM] responsible for generating the [execution trace]. <br/>
See also: [Executor documentation], [Prover]

### Execution Trace

A complete record of a computation.
The execution trace is organized as a rectangular array, where each row describes a complete snapshot of the state of the [zkVM] at a given moment in time.
The width of the execution trace relates to the number of registers/components in the machine, and the length of the execution trace relates to the number of [clock cycles] of the program's execution.

The execution trace is generated by the [executor] and checked for validity by the [prover].
A valid trace means that the [ELF binary] was faithfully executed according to the rules of the [RISC-V] instruction set architecture.

### Groth16

A proof system that offers a very small proof size, suitable for on-chain verification.

### Groth16 Circuit

RISC Zero's Groth16 Circuit is used to generate [receipts] that are small enough to support on-chain verification.
The Groth16 Circuit is a circom implementation of the verifier for the [Recursion Circuit].

### Groth16 Receipt

A Groth16 Receipt is a very small [validity proof], used primarily for on-chain verification.
The Groth16 Receipt is constructed using the [Groth16 Circuit].

### Guest

The system running inside the [zkVM]. <br/>
See also: [Rust crate for zkVM guest]

### Guest Program

The portion of a [zkVM] application that gets proven.
The guest program receives inputs from an (untrusted) [host].
Depending on the application, the guest program can [commit] results to the [journal] and/or send them to the host. <br/>
See also: [Rust crate for zkVM guest]

### Host

The system the [zkVM] runs on.

### Host program

The [host]-native, untrusted portion of a [zkVM] application.
The host program loads the [guest program] and provides inputs to the guest program as necessary.

### Image ID

A small cryptographic identifier that indicates the [method] or boot image for zkVM [execution]. <br/>
See also: [ImageID documentation], [ImageID excerpt from Study Club], [segment]

### Journal

The portion of the [receipt] that contains the public outputs of a [zkVM] application. <br/>
See also: [commit]

### Method

A single 'main' entry point for code that runs inside the [zkVM].

### Prove

Generate a [receipt] that serves as [proof] of correct execution of a [guest program].

### Prover

The portion of the [zkVM] that [executes] and [proves] a [guest program], thereby constructing a [receipt]. <br/>
See also: [Prover documentation], [Executor]

### Receipt

A receipt attests to valid [execution] of a [guest program].
[Verifying] the receipt provides cryptographic assurance that the [journal] was indeed constructed using the expected [circuit] and the expected [imageID].
The receipt consists of the [receipt claim] and the [seal].
The [receipt claim] contains the [journal] along with other important details, and constitutes to the public outputs of the program.
The [seal] is the opaque blob that cryptographically attests to the validity of the [receipt claim].

### Receipt Claim

Every receipt has an associated "receipt claim" or "claim", also known as the "public output".
The claim is the statement that the receipt provides proof of.
It contains the [journal], and it additionally includes information about the [imageID], exit status (e.g. if the program exits successfully or encountered an error), and the memory state at the end of execution.
A simple example of a claim is "I ran the Fibonacci sequence calculator with input "21" and got output "10946".
RISC Zero provides a formal system for defining and proving claims.

### Recursion

When a zero-knowledge proof is verified within a zero-knowledge proof, this is referred to as "recursion".
RISC Zero uses recursion to underpin features such as [continuations] and [composition].
Through recursion, RISC Zero can take two or more [receipts] and compress them into one receipt.
By repeating this compression, an arbitrary number of related [receipts] (e.g. all the [Segments] of a [Session]) can be compressed into a single receipt.

### Recursion Circuit

The recursion circuit is used to aggregate and compose [proofs].

### Recursion Program

The [recursion circuit] is capable of efficiently evaluating polynomial constraints, and was specifically designed to verify STARK proofs. Programs written for this circuit are loaded into the \[control columns]. Each recursion program is identified by a [Control ID].

For a list of all supported recursion programs, see the documentation for the [zkVM API Client].

### RISC-V

The 5th edition of UC Berkeley's reduced instruction set computer architecture.
RISC Zero uses RISC-V, specifically the [rv32im instruction set](https://riscv.org/wp-content/uploads/2019/12/riscv-spec-20191213.pdf), as the basis for the RISC Zero zkVM.

### RISC-V Circuit

The RISC-V circuit is the core of the [zkVM].

### Seal

The portion of the [receipt] that cryptographically attests to the [receipt claim] and the correct execution of the [guest program].
Concretely, the seal is a [zk-STARK] and is generated by the [prover]. <br/>
See also: [validity proof]

### Segment

The [execution trace] of a portion of a [guest program].
The execution of a segment begins at some initial memory image (identified by the [ImageID]) and proceeds until terminated by the system or user.
This represents a chunk of execution work that will be proven in a single call to the zero-knowledge proof system. <br/>
See also: [Session]

### Session

The [execution trace] of a [guest program].
The session's execution starts from an initial memory image (which includes the starting program counter) and proceeds until either a sys\_halt or a sys\_pause syscall is encountered.
This record is stored as a vector of [Segments].

### STARK

A STARK (scalable, transparent argument of knowledge) serves as proof of validity for a [zkVM] program. <br/>
See also: [About STARKs], [Sequence Diagram for RISC Zero's STARK], [RISC Zero's ZKP Whitepaper]

### SNARK

A SNARK (succinct non-interactive argument of knowledge) serves as proof of validity for Blockchain applications due to their small size compared to [STARK] proofs. <br/>
See also: [About SNARKs]

### Validity Proof

A validity proof is a cryptographic argument that attests to the validity of an [execution trace].
The [seal] on the [receipt] serves as a validity proof for the RISC-V instruction set.
A validity proof is often referred to as a "zero-knowledge proof", or simply a "proof".

### Verifier

A program on the [host] that [verifies] a [receipt].

### Verify

Check that the [receipt] is valid.
Verifying [segment] receipts requires checking that the [seal] is valid and was generated by the expected [ImageID].
Verifying [session] receipts requires checking the validity of each [segment] and checking that the initial/final memory snapshots for each segment align appropriately.

### Zero-Knowledge Virtual Machine (zkVM)

A virtual machine that runs trusted code and generates proofs.
RISC Zero's zkVM implements the RISC-V instruction set architecture and uses a [STARK]-based proof system.

[About STARKs]: ./reference-docs/about-starks.md
[About SNARKs]: https://ethereum.org/en/developers/docs/scaling/zk-rollups/#validity-proofs
[Arithmetic Circuits]: /reference-docs/about-arithmetic-circuits
[assumptions]: #assumption
[`cargo risczero build`]: https://docs.rs/crate/cargo-risczero/latest
[circuit]: #circuit
[clock cycles]: #clock-cycles
[Code reference for control root]: https://github.com/risc0/risc0/blob/v0.21.0/risc0/circuit/recursion/src/control_id.rs#L16
[commit]: #commit
[composition]: #composition
[conditional]: #conditional
[continuations]: #continuations
[Continuations study club]: https://www.youtube.com/watch?v=v4HIwaqmIxk&list=PLcPzhUaCxlCirUkJY0ltpjdtzWcz5U_6y&index=1
[Continuations blog]: https://www.risczero.com/news/continuations
[control ID]: #control-id
[ELF binary]: #elf-binary
[env::commit()]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest/env/fn.commit.html
[executes]: #execute
[execution]: #execute
[executed]: #executor
[executor]: #executor
[Executor documentation]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/trait.Executor.html
[execution trace]: #execution-trace
[Groth16 Circuit]: #groth16-circuit
[guest]: #guest-program
[guest program]: #guest-program
[host]: #host
[imageID]: #image-id
[ImageID documentation]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.SystemState.html
[ImageID excerpt from Study Club]: https://www.youtube.com/watch?v=QwzrBHHkzFE&list=PLcPzhUaCxlCirUkJY0ltpjdtzWcz5U_6y&index=4
[journal]: #journal
[method]: #method
[proves]: #prove
[proven]: #prover
[prover]: #prover
[Prover documentation]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/trait.Prover.html
[receipt]: #receipt
[receipts]: #receipt
[receipt claim]: #receipt-claim
[recursion]: #recursion
[Recursion Circuit]: #recursion-circuit
[recursion program]: #recursion-program
[RISC-V]: #risc-v
[RISC-V Circuit]: #risc-v-circuit
[RISC Zero's ZKP Whitepaper]: https://risczero.com/proof-system-in-detail.pdf
[Rust crate for zkVM guest]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/guest
[seal]: #seal
[Segment]: #segment
[Segments]: #segment
[session]: #session
[Sequence Diagram for RISC Zero's STARK]: ./proof-system/proof-system-sequence-diagram.md
[STARK]: #stark
[STARK by Hand]: ./proof-system/stark-by-hand.md
[zk-stark]: #stark
[proof]: #validity-proof
[proofs]: #validity-proof
[validity proof]: #validity-proof
[verifying]: #verify
[verifies]: #verify
[zkVM]: #zero-knowledge-virtual-machine-zkvm
[zkVM API Client]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.ApiClient.html#
