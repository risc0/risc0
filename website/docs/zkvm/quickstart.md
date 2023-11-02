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
cargo install cargo-binstall
cargo binstall cargo-risczero
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

## 4. Quick Development: Leveraging Dev Mode

During the development of your project, you might find that running your code can take a long time due to the proof generation process. To address this issue and allow for faster iterations of your code, we suggest utilizing [dev-mode]. This mode bypasses the time-consuming proof generation process. To activate dev-mode, simply set the environment variable `RISC0_DEV_MODE=true` when executing your project (other acceptable values include `1` and `yes`).

Example:

```bash
RISC0_DEV_MODE=true cargo run --release
```

For a deeper understanding of dev-mode and its safe usage, please refer to our page explaining [what is dev-mode]. Please note that dev-mode is only meant to be used during development and testing. It should **never** be used in production.

## 5. Real Proof Generation

Once you've reached a point where you're ready to generate real proofs, you can do so by unseting the `RISC0_DEV_MODE` environment variable (or setting it to `RISC0_DEV_MODE=false`). We recommend that you additionally specify the feature flag `disable-dev-mode`, which will ensure that dev-mode is not accidentally enabled. Please consult more information about `disable-dev-mode` in the [feature flags] table, and the [dev-mode] page for more information.

Proceeding with the example above, generating proofs locally would be achieved by running:

```bash
RISC0_DEV_MODE=false cargo run --release --features disable-dev-mode
```

Note that `RISC0_DEV_MODE=false` is the default behavior, so you can also simply run:

```bash
cargo run --release --features disable-dev-mode
```

We would always recommend using `disable-dev-mode` in production, as it ensures that dev-mode is not accidentally enabled.

Also, note that since now proofs are being generated, the execution time of your project will be significantly longer than when running in dev-mode. You might want to consider using [Bonsai] to generate proofs remotely, as it will likely be faster than running proofs locally.

## 6. Local & Remote Proving

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
[dev-mode]: ./dev-mode.md
[what is dev-mode]: ./dev-mode.md
