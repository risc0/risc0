# sppark

sppark (pronounced 'spark') is **S**upranational's **p**erformance **p**rimitives for **ar**guments of **k**nowledge such as SNARKs and STARKs. The library focuses on accelerating the most computationally expensive pieces of zero-knowledge proofs generation such as multi-scalar multiplication (MSM), number theoretic transform (NTT), arithmetic hashes, and more. The library is a collection of CUDA/C++ templates that can be instantiated for a range of finite fields and elliptic curves.

## Table of Contents

  * [Status](#status)
  * [General notes on implementation](#general-notes-on-implementation)
  * [Platform and Language Compatibility](#platform-and-language-compatibility)
  * [Introductory Integration Tutorial](#introductory-integration-tutorial)
    + [Multi-scalar Multiplication (MSM)](#multi-scalar-multiplication-msm)
  * [Repository Structure](#repository-structure)
  * [Performance](#performance)
  * [License](#license)

## Status

**This library is under active development [with a list of planned significant improvements]**

## General notes on implementation

The goal of the sppark library is to provide foundational components for applications and other libraries that require high-performance operations for zero-knowledge proofs generation.

## Platform and Language Compatibility

This library primarily supports x86_64 with Nvidia's Volta+ GPU hardware platforms on Linux and Windows operating systems. A limited support for AMD's RDNA and CDNA GPUs is provided. Non-GPU portions can be utilized even on ARM64, and additionally on Mac.

We show how to interface with Rust and Go. Caveat lector. Achieving highest possible GPU performance requires interfacing with target language memory management, possibly its async facilities, and might even require changes to object's data layout. These are hard to generalize and consequently are also a matter of discussion, likely on a case-by-case basis.

## Introductory Integration Tutorial

[TBD]

### Multi-scalar Multiplication (MSM)

[TBD]

## Repository Structure

**Root** - Contains various configuration files, documentation, licensing.
* **conversion** -
* **ec** - Contains templates for elliptic curve operations such as addition and doubling for different point representations.
* **ff** - Contains CUDA template[s] for finite field operations and instantiations of a variety of fields.
* **hash** -
* **memory** -
* **merkle** -
* **msm** - Contains multi-scalar multiplication template[s] that can be instantiated for a variety of elliptic curves such as BLS12-381 and the Pasta curves
* **ntt** - Contains NTT CUDA kernels.
* **poc** - Proof-of-concept implementations, including benchmarking.
* **rust** - Houses Rust crate definition.
* **util** - General-purpose helper classes.

## Performance

Simplified benchmark results can be collected by end users by exercising proof-of-concept applications. "Simplified" refers to the fact that there is always room for application-specific tuning. Intention is to give a general "taste." Just in case, benchmarks are likely to require high-end GPUs and one can't expect that they will execute on a laptop unmodified.

Caveat lector. As you compile PoC applications you might get warnings about not FFI-safe types. Alarming as they are, the fact that tests pass means that it works out nevertheless. However, this is **not** to say that they should be ignored and that one can proceed to build production code upon it. We intend to work with external software maintainers to resolve these warnings.

## License

The sppark library is licensed under the [Apache License Version 2.0](LICENSE) software license.
