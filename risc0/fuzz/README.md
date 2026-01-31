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
