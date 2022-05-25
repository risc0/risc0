#!/bin/bash

cargo run --bin risc0-build-methods
cargo test --release
cargo build --release --manifest-path examples/rust/battleship/contract/Cargo.toml
