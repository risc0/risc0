> [!IMPORTANT]
> `main` is the development branch.
> When building applications or running examples, use the [latest release](https://github.com/risc0/risc0/releases) instead.

<p align="center">
  <a href="https://risczero.com" target="_blank">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://risczero.com/companies/risczero_dark.svg">
      <img src="https://risczero.com/companies/risczero.svg" alt="RISC Zero Company Logo" width="142" height="126">
    </picture>
  </a>
</p>

[![Crates.io][crates-badge]][crates-url]
[![Apache 2.0 licensed][licence-badge]][licence-url]
[![Build Status][actions-badge]][actions-url]
[![Discord chat][discord-badge]][discord-url]
[![Twitter][twitter-badge]][twitter-url]
[![GitHub][github-badge]][github-url]

# RISC Zero: Zero-Knowledge Verifiable Computing Platform

RISC Zero is a zero-knowledge verifiable general computing platform based on
[zk-STARKs][zk-proof] and the [RISC-V] microarchitecture. Current version: v1.2.

## Table of Contents
- [Overview](#overview)
- [System Requirements and Compatibility](#system-requirements-and-compatibility)
- [Protocol Overview and Terminology](#protocol-overview-and-terminology)
- [Use Cases and Applications](#use-cases-and-applications)
- [Security](#security)
- [Getting Started](#getting-started)
- [Quick Examples](#quick-examples)
- [Documentation](#documentation)
- [Building from Source](#building-from-source)
- [Packages and Libraries](#packages-and-libraries)
  - [Rust Binaries](#rust-binaries)
  - [Rust Libraries](#rust-libraries)
- [Feature Flags](#feature-flags)
- [Contributing](#contributing)
- [Frequently Asked Questions (FAQ)](#frequently-asked-questions-faq)
- [License](#license)

## Overview

A [zero knowledge proof][zk-proof] allows one party (the prover) to convince
another party (the verifier) that something is true without revealing all the
details. In the case of RISC Zero, the prover can show they correctly executed
some code (known to both parties), while only revealing to the verifier the
output of the code, not any of its inputs or any state during execution.

The code runs in a special virtual machine, called a _zkVM_. The RISC Zero zkVM
emulates a small [RISC-V] computer, allowing it to run arbitrary code in any
language, so long as a compiler toolchain exists that targets RISC-V. Currently,
SDK support exists for Rust, C, and C⁠+⁠+.

## System Requirements and Compatibility

RISC Zero supports running on the following platforms:

- **Operating Systems**:
  - Linux (Ubuntu 20.04+, other distributions should work but may require additional setup)
  - macOS (10.15 Catalina or later)
  - Windows (via WSL2 - Windows Subsystem for Linux)

- **Hardware Requirements**:
  - Minimum: 4 CPU cores, 8GB RAM
  - Recommended: 8+ CPU cores, 16GB+ RAM
  - GPU acceleration (optional):
    - CUDA for NVIDIA GPUs (requires CUDA toolkit 11.7+)
    - Metal for Apple Silicon (built-in support)

- **Language Support**:
  - Primary SDK: Rust (stable toolchain)
  - Guest code can be written in: Rust, C, C++
  - Experimental support for other languages via RISC-V compilation

- **Dependencies**:
  - Rust toolchain (installation instructions in the Getting Started section)
  - For development: additional tools listed in [CONTRIBUTING.md](./CONTRIBUTING.md)

## Protocol Overview and Terminology

First, the code to be proven must be compiled from its implementation language
into a _method_. A method is represented by a RISC-V ELF file with a special
entry point that runs the code of the method. Additionally, one can compute for
a given method its _image ID_ which is a special type of cryptographic hash of
the ELF file, and is required for verification.

Next, the host program runs and proves the method inside the zkVM. The logical
RISC-V machine running inside the zkVM is called the _guest_ and the prover
running the zkVM is called the _host_. The guest and the host can communicate
with each other during the execution of the method, but the host cannot modify
the execution of the guest in any way, or the proof being generated will be
invalid. During execution, the guest code can write to a special append-only log
called the _journal_ which represents the official output of the computation.

Presuming the method terminated correctly, a _receipt_ is produced, which
provides the proof of correct execution. This receipt consists of 2 parts: the
journal written during execution and a blob of opaque cryptographic data called
the _seal_.

The verifier can then verify the receipt and examine the log. If any tampering
was done to the journal or the seal, the receipt will fail to verify.
Additionally, it is cryptographically infeasible to generate a valid receipt
unless the output of the journal is the exactly correct output for some valid
execution of the method whose image ID matches the receipt. In summary, the
receipt acts as a zero-knowledge proof of correct execution.

Because the protocol is zero-knowledge, the verifier cannot infer anything about
the details of the execution or any data passed between the host and the guest
(aside from what is implied by the data written to the journal and the correct
execution of the code).

## Use Cases and Applications

RISC Zero can be used in various scenarios where computation needs to be verified without revealing sensitive data:

- **Blockchain and DeFi**: Create verifiable financial transactions and smart contracts with privacy
- **Identity verification**: Prove certain attributes about identity without exposing personal data
- **Gaming**: Verify game state transitions without revealing player strategy
- **Machine Learning**: Prove ML model performance without sharing sensitive training data
- **Healthcare**: Analyze medical data while preserving patient privacy
- **Supply chain**: Verify compliance with regulations without exposing trade secrets

For real-world examples, check out our [showcase of projects][showcase] built with RISC Zero.

## Security

This code implements a [three-layer recursive proof system][zksummit10-talk],
based on the well-studied zk-STARK protocol and Groth16 protocol. An overview of
the underlying cryptographic assumptions can be found on our [Security
Model][security-model] page. With default parameters, this system achieves
perfect zero-knowledgeness and 98 bits of conjectured security. Our STARK
protocol is described in [Scalable, Transparent Arguments of RISC-V
Integrity][proof-system-in-detail], and a soundness/security calculator is
included in the `soundness.rs` file.

To run the calculator, use `RUST_LOG=risc0_zkp=debug` when running a proof.

## Getting Started

To start your own project, you can use our `cargo risczero` tool to write the
initial boilerplate and set up a standard directory structure.

First, [install Rust][install-rust] if you don't already have it, then install
the RISC Zero toolchain installer, `rzup`. We'll use `rzup` to install
`cargo-risczero`.

To install `rzup` run the following command and follow the instructions:

```bash
curl -L https://risczero.com/install | bash
```

Next we can install the RISC Zero toolchain by running `rzup install`:

```bash
rzup install
```

You can verify the installation was successful by running:

```bash
cargo risczero --version
```

After installation, you can create a new project (named `my_project` in this example):

```bash
cargo risczero new my_project
```

More details and options for `cargo risczero` are given in
[its README][cargo-risczero-readme].

For more guidance on how to use RISC Zero, how RISC Zero projects are typically
structured, and other resources useful to developers new to RISC Zero, see our
[Getting Started page][quickstart].

## Quick Examples

Here are some basic examples to show you what working with RISC Zero looks like.

### Example 1: A Simple ZK Proof

This example shows how to create a basic zero-knowledge proof that a number is prime:

```rust
// In methods/guest/src/main.rs (guest code)
#![no_std]
#![no_main]

use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // Read the input number
    let number: u64 = env::read();
    
    // Check if the number is prime
    let is_prime = is_prime(number);
    
    // Commit the result to the journal
    env::commit(&is_prime);
}

fn is_prime(n: u64) -> bool {
    if n <= 1 {
        return false;
    }
    if n <= 3 {
        return true;
    }
    if n % 2 == 0 || n % 3 == 0 {
        return false;
    }
    
    let mut i = 5;
    while i * i <= n {
        if n % i == 0 || n % (i + 2) == 0 {
            return false;
        }
        i += 6;
    }
    true
}
```

```rust
// In host/src/main.rs (host code)
use methods::{IS_PRIME_ID, IS_PRIME_PATH};
use risc0_zkvm::{Prover, Receipt};

fn main() {
    // The secret number we want to check (this will not be revealed)
    let secret_number: u64 = 37;
    
    // Initialize the prover
    let mut prover = Prover::new(IS_PRIME_PATH, IS_PRIME_ID).unwrap();
    
    // Add our private input
    prover.add_input_u64_slice(&[secret_number]).unwrap();
    
    // Run the prover
    let receipt = prover.run().unwrap();
    
    // The receipt can be verified by a third party
    let result: bool = receipt.journal.decode().unwrap();
    
    println!("Proved that the secret number is {}prime!", if result { "" } else { "not " });
}
```

### Example 2: Private Voting System

This example shows a minimal implementation of a private voting system:

```rust
// In methods/guest/src/main.rs
#![no_std]
#![no_main]

use risc0_zkvm::guest::env;
use serde::{Deserialize, Serialize};

risc0_zkvm::guest::entry!(main);

#[derive(Serialize, Deserialize)]
struct Vote {
    voter_id: u64,
    candidate_id: u32,
}

pub fn main() {
    // Read the private vote data
    let vote: Vote = env::read();
    
    // Verify the voter is in the allowed list (could be more complex)
    let allowed_voters: Vec<u64> = env::read();
    assert!(allowed_voters.contains(&vote.voter_id), "Voter not allowed");
    
    // Only reveal the candidate that was voted for, not who voted
    env::commit(&vote.candidate_id);
}
```

For more examples, check out the [examples directory](https://github.com/risc0/risc0/tree/main/examples) in our GitHub repository.

## Documentation

Documentation for the zkVM SDK and other Rust crates can be found at [docs.rs/risc0-zkvm](https://docs.rs/risc0-zkvm).
All other documentation can be found at [dev.risczero.com](https://dev.risczero.com).

You can build and view the Rust documentation locally by using `cargo doc`.
See [CONTRIBUTING.md](./CONTRIBUTING.md) for dependencies.
Source code for the documentation website can be found in the [website directory](./website).

## Building from Source

Building from source requires some additional tools and steps.
Please refer to [CONTRIBUTING.md](./CONTRIBUTING.md) for the full instructions.

## Packages and Libraries

### Rust Binaries

| Binary         | Description | [crates.io] |
| -------------- | ----------- | ----------- |
| cargo-risczero | CLI tool for creating and managing RISC Zero projects | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/cargo-risczero) |
| risc0-r0vm     | The RISC Zero zkVM runtime | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-r0vm) |
| risc0-tools    | Miscellaneous tools for working with RISC Zero | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-tools) |

### Rust Libraries

| Library                     | Description | [crates.io] | [docs.rs](https://docs.rs) |
| --------------------------- | ----------- | ----------- | -------------------------- |
| bonsai-sdk                  | SDK for interacting with the Bonsai proving service | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/bonsai-sdk) | [![](https://img.shields.io/docsrs/bonsai-sdk)](https://docs.rs/bonsai-sdk) |
| risc0-binfmt                | Binary format utilities for RISC Zero | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-binfmt) | [![](https://img.shields.io/docsrs/risc0-binfmt)](https://docs.rs/risc0-binfmt) |
| risc0-build                 | Build system for RISC Zero projects | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-build) | [![](https://img.shields.io/docsrs/risc0-build)](https://docs.rs/risc0-build) |
| risc0-build-kernel          | Kernel building utilities | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-build-kernel) | [![](https://img.shields.io/docsrs/risc0-build-kernel)](https://docs.rs/risc0-build-kernel) |
| risc0-circuit-recursion     | Recursive proving circuit | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-circuit-recursion) | [![](https://img.shields.io/docsrs/risc0-circuit-recursion)](https://docs.rs/risc0-circuit-recursion) |
| risc0-circuit-recursion-sys | Low-level recursion circuit bindings | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-circuit-recursion-sys) | [![](https://img.shields.io/docsrs/risc0-circuit-recursion-sys)](https://docs.rs/risc0-circuit-recursion-sys) |
| risc0-circuit-rv32im        | RISC-V instruction circuit | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-circuit-rv32im) | [![](https://img.shields.io/docsrs/risc0-circuit-rv32im)](https://docs.rs/risc0-circuit-rv32im) |
| risc0-circuit-rv32im-sys    | Low-level RISC-V circuit bindings | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-circuit-rv32im-sys) | [![](https://img.shields.io/docsrs/risc0-circuit-rv32im-sys)](https://docs.rs/risc0-circuit-rv32im-sys) |
| risc0-core                  | Core RISC Zero types and traits | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-core) | [![](https://img.shields.io/docsrs/risc0-core)](https://docs.rs/risc0-core) |
| risc0-groth16               | Groth16 proving scheme | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-groth16) | [![](https://img.shields.io/docsrs/risc0-groth16)](https://docs.rs/risc0-groth16) |
| risc0-sys                   | Low-level system bindings | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-sys) | [![](https://img.shields.io/docsrs/risc0-sys)](https://docs.rs/risc0-sys) |
| risc0-zkp                   | Zero-knowledge proof system | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-zkp) | [![](https://img.shields.io/docsrs/risc0-zkp)](https://docs.rs/risc0-zkp) |
| risc0-zkvm                  | Zero-knowledge virtual machine | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-zkvm) | [![](https://img.shields.io/docsrs/risc0-zkvm)](https://docs.rs/risc0-zkvm) |
| risc0-zkvm-platform         | Platform abstraction for the zkVM | [![x](https://img.shields.io/badge/crates.io-v1.2-orange)](https://crates.io/crates/risc0-zkvm-platform) | [![](https://img.shields.io/docsrs/risc0-zkvm-platform)](https://docs.rs/risc0-zkvm-platform) |

## Feature Flags

The following feature flags are present in one or more of the crates listed above:

| Feature          | Target(s)         | Implies    | Description                                                                                                                                                  | Crates                                                               |
| ---------------- | ----------------- | ---------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | -------------------------------------------------------------------- |
| client           | all except rv32im | std        | Enables the client API.                                                                                                                                      | risc0-zkvm                                                           |
| cuda             |                   | prove, std | Enables CUDA GPU acceleration for the prover. Requires CUDA toolkit to be installed.                                                                         | risc0-circuit-recursion, risc0-circuit-rv32im, risc0-zkp, risc0-zkvm |
| disable-dev-mode | all except rv32im |            | Disables dev mode so that proving and verifying may not be faked. Used to prevent a misplaced `RISC0_DEV_MODE` from breaking security in production systems. | risc0-zkvm                                                           |
| metal            | macos             | prove, std | Deprecated - Metal GPU acceleration is enabled by default on Apple Silicon.                                                                                  | risc0-circuit-recursion, risc0-circuit-rv32im, risc0-zkp, risc0-zkvm |
| prove            | all except rv32im | std        | Enables the prover, incompatible within the zkvm guest.                                                                                                      | risc0-circuit-recursion, risc0-circuit-rv32im, risc0-zkp, risc0-zkvm |
| std              | all               |            | Support for the Rust stdlib.                                                                                                                                 | risc0-circuit-recursion, risc0-circuit-rv32im, risc0-zkp, risc0-zkvm |

## Contributing

We welcome contributions to RISC Zero! Please see [CONTRIBUTING.md](./CONTRIBUTING.md) for details on how to get started.

Potential contribution areas:
- Bug fixes and improvements
- Documentation enhancements
- New examples and tutorials
- Performance optimizations
- Feature implementation
- Integration with other systems

Join our [Discord server][discord-url] to connect with other contributors and maintainers.

## Frequently Asked Questions (FAQ)

### What makes RISC Zero different from other ZK systems?
RISC Zero is a general-purpose zero-knowledge VM based on the RISC-V architecture, allowing execution of arbitrary programs with proofs of correct execution. Unlike many other ZK systems that are designed for specific applications, RISC Zero can run any computation that compiles to RISC-V instructions.

### Is RISC Zero production-ready?
RISC Zero is being actively used in production systems, but as with any cryptographic software, careful consideration should be given to security requirements. We recommend reviewing our [Security Model][security-model] and conducting appropriate security reviews for your specific use case.

### What's the performance like?
Performance depends heavily on the complexity of the computation being proven. Simple programs can be proven in seconds, while more complex programs may take minutes or hours. GPU acceleration can significantly improve proving times. The verification process is typically much faster than proving.

### Can I use RISC Zero with languages other than Rust?
Yes, the guest code can be written in any language that compiles to RISC-V, including C and C++. However, the host side SDK is currently only available for Rust. Support for other host languages is on our roadmap.

### Do I need specialized hardware to use RISC Zero?
No, RISC Zero works on standard CPUs. For improved performance, you can utilize GPU acceleration using CUDA (NVIDIA) or Metal (Apple Silicon), but this is optional.

### Where can I get help if I'm stuck?
Join our [Discord community][discord-url] where you can get help from the team and other community members. You can also check out our [documentation](https://dev.risczero.com) or open an issue on GitHub.

### How can I cite RISC Zero in academic work?
If you're using RISC Zero in academic work, you can cite it as:

```
RISC Zero Team. "RISC Zero: A Zero-Knowledge Verifiable General Computing Platform." 
GitHub repository, https://github.com/risc0/risc0
```

## License

This project is licensed under the Apache 2.0 license. See [LICENSE](LICENSE).

[actions-badge]: https://img.shields.io/github/actions/workflow/status/risc0/risc0/main.yml?branch=main
[actions-url]: https://github.com/risc0/risc0/actions?query=workflow%3ACI+branch%3Amain
[cargo-risczero-readme]: https://github.com/risc0/risc0/blob/main/risc0/cargo-risczero/README.md
[crates-badge]: https://img.shields.io/badge/crates.io-v1.2-orange
[crates-url]: https://crates.io/crates/risc0-zkvm
[crates.io]: https://crates.io
[discord-badge]: https://img.shields.io/discord/953703904086994974.svg?logo=discord&style=flat-square
[discord-url]: https://discord.gg/risczero
[github-badge]: https://img.shields.io/github/stars/risc0/risc0?style=flat-square&logo=github
[github-url]: https://github.com/risc0/risc0
[install-rust]: https://doc.rust-lang.org/cargo/getting-started/installation.html
[licence-badge]: https://img.shields.io/github/license/risc0/risc0?color=blue
[licence-url]: https://github.com/risc0/risc0/blob/main/LICENSE
[proof-system-in-detail]: https://dev.risczero.com/proof-system-in-detail.pdf
[quickstart]: https://dev.risczero.com/api/zkvm/quickstart
[risc-v]: https://en.wikipedia.org/wiki/RISC-V
[security-model]: https://dev.risczero.com/api/security-model
[twitter-badge]: https://img.shields.io/twitter/follow/risczero
[twitter-url]: https://twitter.com/risczero
[zk-proof]: https://en.wikipedia.org/wiki/Non-interactive_zero-knowledge_proof
[zksummit10-talk]: https://www.youtube.com/watch?v=wkIBN2CGJdc
[showcase]: https://www.risczero.com/news/projects
