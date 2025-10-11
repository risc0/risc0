# RISC Zero Build Kernel

Unified build system for compiling high-performance compute kernels across multiple platforms (C++, CUDA, Metal).

## Usage

```rust
use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    // C++ kernels
    KernelBuild::new(KernelType::Cpp)
        .files(["src/kernel.cpp"])
        .include("include")
        .compile("my_kernel");

    // CUDA kernels
    KernelBuild::new(KernelType::Cuda)
        .files(["src/kernel.cu"])
        .flag("-arch=native")
        .compile("my_cuda_kernel");

    // Metal kernels
    KernelBuild::new(KernelType::Metal)
        .files(["src/kernel.metal"])
        .include("include")
        .compile("my_metal_kernel");
}
```

## API

### KernelBuild Methods
- `new(kernel_type)` - Create build configuration
- `files(paths)` - Add source files
- `include(dir)` - Add include directory
- `flag(flag)` - Add compiler flag
- `deps(paths)` - Add dependency files
- `compile(output)` - Compile kernel

### KernelType
- `Cpp` - CPU kernels
- `Cuda` - NVIDIA GPU kernels
- `Metal` - Apple GPU kernels

## Environment Variables

- `RISC0_SKIP_BUILD_KERNELS` - Skip compilation
- `RUSTC_WRAPPER=sccache` - Faster rebuilds
- `NVCC_PREPEND_FLAGS` / `NVCC_APPEND_FLAGS` - CUDA flags
- `RISC0_CUDART_LINKAGE` - CUDA runtime linkage

## Features

- **Multi-platform**: C++, CUDA, Metal support
- **Caching**: SHA256-based build cache
- **Parallel**: Multi-threaded compilation
- **Integration**: Cargo build script support
