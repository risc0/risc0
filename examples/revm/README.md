# REVM Example

This example demonstrates how to execute EVM bytecode inside the RISC Zero zkVM using the [revm](https://github.com/bluealloy/revm) library.

## Overview

This example shows a possible integration between RISC Zero and revm:

1. **Host**: Prepares simple EVM bytecode and sends it to the zkVM
2. **Guest**: Uses revm to process the bytecode inside the zkVM
3. **Verification**: The host verifies the proof that the bytecode was executed

The original motivation for this example is a Zero Knowledge Bug Bounty Program, in which a whitehat can prove they know how to construct an attack to extract funds from a contract without revealing the transaction information, minimizing trust issues with protocols and revealing the information only after a payout.

## Quick Start

First, make sure [rustup](https://rustup.rs) is installed. The
[`rust-toolchain.toml`][rust-toolchain] file will be used by `cargo` to
automatically install the correct version.

To build all methods and execute the method within the zkVM, run the following
command:

```bash
cargo run
```

## Use Cases

This demonstrates the foundation for more complex EVM-based applications in zkVM:

- **Private smart contract execution**: Execute smart contracts privately while proving correctness
- **EVM compatibility layers**: Build EVM-compatible rollups or sidechains
- **Cross-chain verification**: Prove execution of Ethereum transactions on other chains
- **Auditing tools**: Verify contract behavior without revealing sensitive inputs

## Acknowledgments

This project was built as part of the [EF Core Program Brazil 2025](https://github.com/erc55/core-program-2025).

[rust-toolchain]: ../../rust-toolchain.toml