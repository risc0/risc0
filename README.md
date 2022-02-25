<img src="docs/assets/images/Risc0-Logo_Horizontal.svg" height="100">

# Risc0

Risc0 is a zero-knowledge verifiable general computing platform based on
zk-STARKs and the RISC-V microarchitecture.
## Building Risc0

We use [Bazel](https://bazel.build) for its strong multi-language multi-platform
features and performance.

We recommend using [Bazelisk](https://github.com/bazelbuild/bazelisk) to make
bazel version management seamless.

In order to build Risc0 executables you'll need a RISC-V toolchain. See the
platform specific instructions below.

**Note**: to configure the location of the RISC-V toolchain on your system, add a
`.bazelrc.local` file to the root of the project with this line:
```
build --riscv_root=/<path>/<to>/<riscv>/<toolchain>
```

### macOS

Rust development on macOS **requires a full install of Xcode**.

Using Brew:
 * Follow instructions here https://github.com/riscv-software-src/homebrew-riscv
 * You may need to `brew install gettext`

Your `.bazelrc.local` file should contain a line _like_ this
(check your exact path):
```
build --riscv_root=/usr/local/Cellar/riscv-gnu-toolchain/main
```

Once the prerequisites are installed you should be able to build and run all of
the tests:
```
bazelisk test ...
```

## Running the 'Battleship' Examples

'Battleship' is a 2-player hidden information game implemented in C++ & Rust.

Players produce proofs of game-state and the result of their actions to enable
two players play fairly with no intermediaries.

The best way to understand how the game works currently is to read the code
and run the tests with logging on:

### CPP
```
RISC0_LOG=1 bazelisk run //examples/cpp/battleship:test --test_output=streamed
```

### Rust
```
RISC0_LOG=1 bazelisk run //examples/rust/battleship:test --test_output=streamed
```


##
