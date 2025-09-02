# REVM Example

This example demonstrates how to execute EVM bytecode inside the RISC Zero zkVM using the [revm](https://github.com/bluealloy/revm) library.

## Overview

This example shows the simplest possible integration between RISC Zero and revm:

1. **Host**: Prepares simple EVM bytecode and sends it to the zkVM
2. **Guest**: Uses revm to process the bytecode inside the zkVM
3. **Verification**: The host verifies the proof that the bytecode was executed

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

[rust-toolchain]: ../../rust-toolchain.toml