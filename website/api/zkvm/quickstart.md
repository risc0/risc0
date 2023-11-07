---
sidebar_position: 3
slug: ./quickstart
---

# zkVM Quick Start

Welcome to the zkVM Quick Start page! Here are the steps to create your first proof:

1. Install the `risczero` toolchain
2. Create a new project using the `risczero` tool.
3. Familiarize yourself with the project's structure
4. Run your project locally

## Concept break

zkVM provides a zero-knowledge proof of the correct execution of any Rust code.
We want to run a piece of code and produce its proof of execution on zkVM. In the project code, we call zkVM a [prover]. The code we want to run on zkVM is a **[guest]** program. A proof of execution is a [receipt]; it contains a public part - a [journal] and an encryption part - a [seal].

zkVM runs on the **[host]**, which loads the guest program to the zkVM and provides input to the guest. zkVM, or a prover, proves the guest execution by producing a locally verified receipt.

## 1. Install the RISC Zero Toolchain

First, make sure you [install Rust], then install the RISC Zero toolchain by running the following:

```bash
cargo install cargo-binstall
cargo binstall cargo-risczero
cargo risczero install
```

## 2. Create a New Project

The `cargo-risczero` tool takes `--guest-name` parameter, a [guest] program that the zkVM runs, to generate a proof of its execution:

```bash
cargo risczero new my_project --guest-name guest_code_for_zk_proof
```

To run the zkVM on your own machine, we recommend at least 16 GB of RAM.

## 3. Project structure

The [Hello World tutorial] contains step-by-step instructions on how to:

- [Share private data] between the host & guest.
- [Share the guest's results] with the host publicly.
- [Generate a receipt] and read its journal contents.

## 4. Quick Development: Leveraging Dev Mode

During the development of your project, running your code can take a long time due to the proof generation process. To address this issue and allow for faster iterations of your code, we suggest utilizing [Dev Mode]. This mode bypasses the time-consuming proof generation process. To activate dev-mode, set the environment variable `RISC0_DEV_MODE=true` when executing your project:

```bash
RISC0_DEV_MODE=true cargo run --release
```

## 5. Real Proof Generation

Once you've reached a point where you're ready to generate real proofs, you can do so by setting the `RISC0_DEV_MODE=false`. We recommend that you specify the feature flag `disable-dev-mode`, which will ensure that dev-mode is not accidentally enabled. Generating proofs locally would be achieved by running the following:

```bash
RISC0_DEV_MODE=false cargo run --release --features disable-dev-mode
```

Note that since proofs are now being generated, the execution time of your project will be significantly longer than when running in dev mode. Consider using [Bonsai] to generate proofs remotely, as it will likely be significantly faster than running proofs locally. You can [request access] to Bonsai to set additional flags.

### Executor Statistics

To gain insights into your application's performance, you can obtain executor statistics by setting the `RUST_LOG` environment variable to `"executor=info"`.

Setting this filter will print statistics about the execution before proof generation, so you can understand how computationally expensive your application is. Since the statistics concern only the executor phase, it is recommended to run your application in dev mode to avoid the overhead of proof generation:

```bash
RISC0_DEV_MODE=true RUST_LOG="executor=info" cargo run --release
```

The statistics include:

- Total Cycles
- Session Cycle
- Segments Count
- Execution time

Knowing these statistics is helpful for estimating the cost of your application before submitting real workloads to Bonsai, as the cost of proof generation is proportional to the number of cycles and segments used.

### Other options

There is a list of options in the [feature flags].

> **Congratulations!**
>
> _That's all it takes to build and run a minimal RISC Zero application._

[Bonsai]: ../bonsai/quickstart
[Dev Mode]: ./dev-mode
[feature flags]: https://github.com/risc0/risc0#feature-flags
[Share private data]: ./tutorials/hello-world#step-2-host-share-private-data-as-input-with-the-guest
[Share the guest's results]: ./tutorials/hello-world#step-3-guest-read-input-and-commit-output
[Generate a receipt]: ./tutorials/hello-world#step-4-host-generate-a-receipt-and-read-its-journal-contents
[Hello World tutorial]: ./tutorials/hello-world
[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[host]: /terminology#host-program
[guest]: /terminology#guest-program
[receipt]: /terminology#receipt
[journal]: /terminology#journal
[seal]: /terminology#seal
[prover]: /terminology#prover
[request access]: https://bonsai.xyz/apply
