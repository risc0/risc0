# RISC Zero Fuzzing Targets

This crate defines fuzzing

Based on the
https://github.com/AFLplusplus/LibAFL/tree/main/fuzzers/fuzz_anything/cargo_fuzz


```sh
rustup +nightly component add llvm-tools
```

```sh
CARGO_PROFILE_RELEASE_LTO=off cargo +nightly-2025-06-20 fuzz run --release receipt_seal --fuzz-dir risc0/fuzz
```
