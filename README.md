<img src="docs/assets/images/Risc0-Logo_Horizontal.svg" height="100">

# RISC Zero

Risc0 is a zero-knowledge verifiable general computing platform based on
zk-STARKs and the RISC-V microarchitecture.

## Building RISC Zero

We use [Bazel](https://bazel.build) for its strong multi-language multi-platform
features and performance.

We recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk) to make
bazel version management seamless.

In order to build Risc0 executables you'll need a RISC-V toolchain.
Bazel will automatically fetch and manage the toolchain for the following platforms:

* Linux - Ubuntu 18+ (x86_64)
* macOS (x86_64)
* macOS (arm64)
* Windows (x86_64)

Other platforms will be supported in the future.

You should be able to build and run all tests with:

```
bazelisk test //...
```

### macOS

Risc0 development on macOS **requires a full installation of Xcode (not just command line tools)**.

### Windows

Our usage of Bazel requires [symlink support to be enabled](https://bazel.build/docs/windows#symlink).
This is possible on Windows by enabling [Developer Mode](https://docs.microsoft.com/en-us/windows/apps/get-started/enable-your-device-for-development),
or by running Bazel as an administrator.

## Running the 'Battleship' Examples

'Battleship' is a 2-player hidden information game implemented in C++ & Rust.

Players produce proofs of game-state and the result of their actions to enable
two players to play fairly with no intermediaries.

The best way to understand how the game works currently is to read the code
and run the tests with debug logging enabled:

### C++

```
RISC0_LOG=1 bazelisk run //examples/cpp/battleship:test
```

### Rust

```
RISC0_LOG=1 bazelisk run //examples/rust/battleship:test
```

