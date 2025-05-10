# RISC0 Circuit Keccak System

This package contains the generated HAL code for the keccak circuit.

## CUDA Compilation

The CUDA compilation for this circuit can be time-consuming and may take hours on certain systems. If you don't need the keccak circuit when using CUDA, you can use the `skip-cuda-keccak` feature to skip compiling the CUDA kernels for this circuit.

### Usage

When building with CUDA support, you can add the `skip-cuda-components` feature to your zkvm dependency:

```toml
[dependencies]
risc0-zkvm = { version = "3.0.0", features = ["cuda", "skip-cuda-components"] }
```

Or directly when using cargo:

```
cargo build --release --features cuda,skip-cuda-components
```

This will create a stub library to satisfy dependencies while skipping the lengthy CUDA compilation process for the keccak circuit.

### When to use

Use this feature when:
- You are developing and don't need the keccak circuit specifically
- You're experiencing extremely long build times with CUDA enabled
- Your application doesn't use cryptographic operations that depend on keccak

Note that skipping the keccak circuit will prevent you from using certain cryptographic features that rely on it.
