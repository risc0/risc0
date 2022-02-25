<img src="docs/assets/images/Risc0-Logo_Horizontal.svg" height="100">

# Risc0

Risc0 is a zero-knowledge verifiable general computing platform based on
zk-STARKs and the RISC-V microarchitecture.

## Building Risc0

We use [Bazel](https://bazel.build) for its strong multi-language multi-platform
features and performance.

We recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk) to make
bazel version management seamless.

You should be able to build and run all tests with:

```
bazelisk test //...
```

### macOS

Rust development on macOS **requires a full installation of Xcode**.

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
