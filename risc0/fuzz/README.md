# RISC Zero Fuzzing Targets

This crate provides fuzzing for RISC Zero library functions.

## Receipt verification

Fuzzer for the receipt seal verification function, looking for panic issues.

The following command, relative to the repo root, will run the fuzzer.

```sh
cargo +nightly fuzz run receipt_seal --fuzz-dir risc0/fuzz --sanitizer none -- -max_len=1048576
```

Note that `cargo fuzz` requires the nightly toolchain to build.
The flag `--sanitizer none` is provided since the goal is to find panics, and to avoid build issues encountered during development.
The `-max_len` flag raises the default maximum input length from 4k bytes to 1 MB.
Adding `-jX` before the `--` enables parallelism across cores, e.g. `-j$(nproc)`.

### Coverage

After running the fuzzer using the command above, it's possible to view a coverage report for the corpus.
This will tell you which lines are reached by an example in the corpus, and which are not.

#### Dependencies

```sh
# Ensure you have the required LLVM tools.
rustup +nightly component add llvm-tools-preview
# Install rustfilt so that you can have demangled symbols in the report.
cargo install rustfilt
```

#### Commands

1. Run the corpus under coverage instrumentation to get a coverage profile

```sh
cargo +nightly fuzz coverage --fuzz-dir ./risc0/fuzz receipt_seal --sanitizer=none
```

2. Create a coverage report

The following command will create a text report in the terminal, showing the regions with at least one covered line.

```sh
rust-cov show ./target/x86_64-unknown-linux-gnu/coverage/x86_64-unknown-linux-gnu/release/receipt_seal \
    -Xdemangler=rustfilt \
    -instr-profile=./risc0/fuzz/coverage/receipt_seal/coverage.profdata \
    -show-line-counts-or-regions \
    -show-instantiations \
    -region-coverage-gt=0
```

The following command will produce an `lcov.info` file. This can be used to display coverage information in your editor.

```sh
rust-cov export --Xdemangler=rustfilt ./target/x86_64-unknown-linux-gnu/coverage/x86_64-unknown-linux-gnu/release/receipt_seal \
    -instr-profile=./risc0/fuzz/coverage/receipt_seal/coverage.profdata \
    -region-coverage-gt=0  \
    -format=lcov > lcov.info
```
