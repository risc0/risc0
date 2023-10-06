#!/bin/bash

set -euo pipefail

export CUDA_LIBRARY_PATH=/usr/lib/cuda
export RISC0_BUILD_LOCKED=1
export RISC0_EXECUTOR=ipc
export RISC0_PROVER=ipc
export RISC0_SERVER_PATH=$PWD/target/release/r0vm
export RUST_BACKTRACE=full
# export RUSTC_WRAPPER=sccache

cargo run --bin cargo-risczero -- risczero install
cargo build -p risc0-r0vm --release -F $FEATURE

cd examples

cargo test --locked
