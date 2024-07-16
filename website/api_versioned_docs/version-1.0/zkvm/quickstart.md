# zkVM Quick Start

Welcome to the zkVM Quick Start page! Here are the steps to create your first proof:

1. Install the RISC Zero toolchain with `rzup`.
2. Create a new project using the `cargo-risczero` tool.
3. Familiarize yourself with the project's structure.
4. Run your project in dev-mode.
5. Run your project locally to generate a zk-proof.

## Concept break

The zkVM provides a zero-knowledge proof of the correct execution of Rust-based
program. The **[host]** is responsible for launching the zkVM (or a
**[prover]**), and then the **[guest]** is the program that runs inside the
zkVM. A proof of execution is a **[receipt]**; it contains a public part - a
**[journal]** and an encryption part - a **[seal]**.

## 1. Install the RISC Zero Toolchain

Install `rzup` by running the following command:

```bash
curl -L https://risczero.com/install | bash
```

Run `rzup` to install the RISC Zero toolchain and `cargo-risczero`.

```bash
rzup
```

> Note: To install a specific version instead of using the latest stable version, use `rzup --version <version>`, where the `<version>` is a [release tag](https://github.com/risc0/risc0/releases).
>
> The version used must match the `risc0-zkvm` version from your guest and host.

## 2. Create a New Project

The `cargo-risczero` tool takes `--guest-name` parameter, a [guest] program that
the zkVM runs, to generate a proof of its execution:

```bash
cargo risczero new my_project --guest-name guest_code_for_zk_proof
```

There is a list of options in the [feature flags].

## 3. Project structure

The [Hello World tutorial][hello-world] contains step-by-step instructions on
how to:

- [Share private data][tutorial-step-2] between the host & guest.
- [Share the guest's results][tutorial-step-3] with the host publicly.
- [Generate a receipt][tutorial-step-4] and read its journal contents.

## 4. Quick Development: Leveraging dev-mode

During the development of your project, running your code can take a long time
due to the proof generation process. To address this issue and allow for faster
iterations of your code, we suggest utilizing [dev-mode]. This mode bypasses the
time-consuming proof generation process. To activate dev-mode, set the
environment variable `RISC0_DEV_MODE=1` when executing your project:

```bash
RISC0_DEV_MODE=1 cargo run --release
```

## 5. Real Proof Generation

Once you've reached a point where you're ready to generate real proofs, you can
do so by setting `RISC0_DEV_MODE=0`. Generating proofs locally would be achieved
by running the following:

```bash
RISC0_DEV_MODE=0 cargo run --release
```

Note that since proofs are now being generated, the execution time will be
significantly longer than when running in dev-mode. To create a proof with the
zkVM on your own machine, we recommend at least 16 GB of RAM. To avoid these
hardware requirements, consider using [Bonsai] to generate proofs remotely, as
it will be significantly faster than running proofs locally. You can \[request
access] to Bonsai to set additional flags.

### Executor Statistics

To gain insights into your application's performance, you can obtain executor
statistics by setting the `RUST_LOG` environment variable to
`"[executor]=info"`.

Setting this filter will print statistics about the execution before proof
generation, so you can understand how computationally expensive your application
is. Since the statistics concern only the executor phase, it is recommended to
run your application in dev-mode to avoid the overhead of proof generation:

```bash
RISC0_DEV_MODE=1 RUST_LOG="[executor]=info" cargo run --release
```

The statistics include:

- Total Cycles
- Session Cycle
- Segments Count
- Execution time

Knowing these statistics is useful for estimating the cost of your application
before submitting real workloads to Bonsai, as the cost of proof generation is
proportional to the number of cycles and segments used.

> **Congratulations!**
>
> _That's all it takes to build and run a minimal RISC Zero application._

[Bonsai]: ../generating-proofs/remote-proving.md
[dev-mode]: ../generating-proofs/dev-mode.md
[feature flags]: https://github.com/risc0/risc0#feature-flags
[guest]: /terminology#guest-program
[hello-world]: ./tutorials/hello-world.md
[host]: /terminology#host-program
[install Rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[journal]: /terminology#journal
[prover]: /terminology#prover
[receipt]: /terminology#receipt
[seal]: /terminology#seal
[tutorial-step-2]: tutorials/hello-world.md#step-2-host-share-private-data-as-input-with-the-guest
[tutorial-step-3]: tutorials/hello-world.md#step-3-guest-read-input-and-commit-output
[tutorial-step-4]: tutorials/hello-world.md#step-4-host-generate-a-receipt-and-read-its-journal-contents
