# BigInt2

BigInt2 provides precompiles for the RISC Zero zkVM that accelerate big integer algebra, including finite field arithmetic.

## Overview

This module includes:
- Pre-built precompiles for common big integer operations
- Syscall interfaces for calling both built-in and custom application-defined precompiles
- Optimized implementations for cryptographic operations

## Features

- **Big Integer Arithmetic**: Fast multiplication, addition, and modular operations
- **Finite Field Operations**: Efficient field arithmetic for cryptographic applications
- **Custom Precompiles**: Support for application-specific big integer operations
- **zkVM Integration**: Seamless integration with RISC Zero zkVM syscalls

## Usage

BigInt2 precompiles are automatically available in the RISC Zero zkVM environment. Applications can use the provided syscall interfaces to access both built-in operations and custom precompiles.

## Documentation

For detailed API documentation and examples, see the [RISC Zero documentation](https://dev.risczero.com).
