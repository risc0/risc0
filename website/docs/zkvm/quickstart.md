---
sidebar_position: 3
slug: ./quickstart
---

# zkVM Quick Start

Welcome to the [zkVM] Quick Start page! Here are the steps between you and your first proof:

1. Install the RISC Zero toolchain.
2. Initialize a new project using the [cargo risczero] tool.
3. Edit the boilerplate to build your first project.
4. Run your project locally or with [Bonsai].

## 1. Install the RISC Zero Toolchain

If you have already installed Rust via `rustup`, you can install our toolchain by running

```bash
cargo install cargo-risczero
cargo risczero install
```

If you need to install Rust or encounter problems, take a look at our [full installation instructions](install.md).

## 2. Initialize a New Project

Once you've installed the toolchain, you can initialize a new project using the [starter template] by running:
[starter template]: https://github.com/risc0/risc0/tree/main/templates/rust-starter

```bash
cargo risczero new my_project
```

See the [cargo risczero] docs for other options for initialization.

## 3. Edit the boilerplate to build your first project

In the codebase for your new project, you'll find a handful of places marked `TODO`, where you'll need to make some changes in order to build your first project.

Don't worry -- each `TODO` comes with instructions for what you need to do, and the [Hello World tutorial] contains step-by-step instructions.

## 4. Run your project, locally or remotely

The readme for your project includes instructions for how to run it, both locally or remotely. You can also get a better developer experience and smoother iteration on your code by using the developer mode.

### Running your project

To run your project locally, going through the full proof generation process, run:

```bash
cargo run --release
```

#### Tip: Leveraging Developer Mode

We recommend using [developer mode] while working on your project, as it will eliminate the time for verifying a receipt and consequently enabling faster iterations on the code. In order to enable developer mode, you need to set the environment variable `RISC0_DEV_MODE=1` when executing your project. (other possible values are `true` and `yes`). For more information about this mode, please see the FAQ on ['What is developer mode and how can I use it safely?'].

Example:

```bash
RISC0_DEV_MODE=1 cargo run --release
```

It's important to highlight that the developer mode is only meant to be used during development and testing. It should **never** be used in production.

## Local & Remote Proving

You can build and run your zkVM applications using your own hardware, or you can upload your [guest program] to [Bonsai] and make requests for proof generation as needed.

### Local Proving

To run the zkVM on your own machine, we recommend at least 16GB of RAM.
The readme files on the [zkVM demo applications] show `cargo` commands for local proof generation.

### Remote Proving

To run the zkVM remotely using [Bonsai], [request access] and set the environment variables `BONSAI_API_KEY=<YOUR_API_KEY>` and `BONSAI_API_URL=<BONSAI_URL>`.
Additional information is available in the [starter template](https://github.com/risc0/risc0/tree/main/templates/rust-starter#running-proofs-remotely-on-bonsai)

### Other options

Options such as GPU acceleration and skipping the proof generation are documented in the [feature flags].

> **Congratulations!**
>
> _That's all it takes to build and run a minimal RISC Zero application._

[zkVM]: ../zkvm/zkvm_overview.md
[guest program]: ../terminology.md#guest-program
[Bonsai]: ../bonsai/bonsai-overview.md
[install]: ./install.md
[feature flags]: https://github.com/risc0/risc0#feature-flags
[zkVM demo applications]: https://github.com/risc0/risc0/tree/v0.18.0/examples
[cargo risczero]: https://docs.rs/cargo-risczero/*/cargo_risczero
[Hello World tutorial]: https://github.com/risc0/risc0/tree/main/examples/hello-world/tutorial.md
[demo applications]: https://github.com/risc0/risc0/tree/v0.18.0/examples
[Bonsai Quick Start]: ../bonsai/quickstart.md
[request access]: https://bonsai.xyz/apply
['What is developer mode and how can I use it safely?']: ../faq.md#dev-mode
[developer mode]: ../faq.md#dev-mode
