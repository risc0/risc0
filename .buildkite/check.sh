#!/bin/bash

set -euo pipefail

cargo install cargo-sort

cargo fmt --all --check
cargo fmt --all --check --manifest-path examples/Cargo.toml
cargo fmt --all --check --manifest-path bonsai/Cargo.toml
cargo fmt --all --check --manifest-path bonsai/examples/governance/Cargo.toml
