# RISC0 Circuit Keccak System

This package contains the generated HAL code for the keccak circuit.

## CUDA Compilation

The CUDA compilation for this circuit can be time-consuming and may take hours on certain systems. By default, the keccak circuit is enabled through the `keccak` feature flag. If you don't need the keccak circuit when using CUDA, you can use the `no-keccak` feature in the zkvm crate to disable it and skip the lengthy CUDA compilation.

### Usage

When building with CUDA support, you can add the `no-keccak` feature to your zkvm dependency:

```toml
[dependencies]
risc0-zkvm = { version = "3.0.0", features = ["cuda", "no-keccak"] }
```

Or directly when using cargo:

```
cargo build --release --features cuda,no-keccak
```

This will create a stub library to satisfy dependencies while skipping the lengthy CUDA compilation process for the keccak circuit.

### When to use

Use the `no-keccak` feature when:
- You are developing and don't need the keccak circuit specifically
- You're experiencing extremely long build times with CUDA enabled
- Your application doesn't use cryptographic operations that depend on keccak

Note that disabling the keccak circuit will prevent you from using certain cryptographic features that rely on it.

### Feature Precedence

If both `keccak` and `no-keccak` features are enabled, `keccak` takes precedence and the keccak circuit will be built.
