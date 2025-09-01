# REVM Example

This example demonstrates how to execute EVM bytecode inside the RISC Zero zkVM using the [revm](https://github.com/bluealloy/revm) library.

## Overview

This example shows the simplest possible integration between RISC Zero and revm:

1. **Host**: Prepares simple EVM bytecode and sends it to the zkVM
2. **Guest**: Uses revm to process the bytecode inside the zkVM
3. **Verification**: The host verifies the proof that the bytecode was executed

The example uses a simple bytecode sequence that stores a value in memory and returns it:
```
PUSH1 0x42    // Push value 0x42 onto stack
PUSH1 0x00    // Push memory offset 0x00 onto stack  
MSTORE        // Store 0x42 at memory offset 0x00
PUSH1 0x20    // Push return data size (32 bytes)
PUSH1 0x00    // Push return data offset (0x00)
RETURN        // Return 32 bytes from memory offset 0x00
```

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