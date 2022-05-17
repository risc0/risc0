#!/bin/bash

cargo release --no-push
cargo release --no-push --manifest-path risc0/zkvm/sdk/rust/guest/Cargo.toml
