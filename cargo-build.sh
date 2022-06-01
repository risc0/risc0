#!/bin/bash

cargo run --bin risc0-build-methods
cargo test --release
