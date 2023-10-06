#!/bin/bash

set -euo pipefail

cargo fmt --all --check
cargo fmt --all --check --manifest-path examples/Cargo.toml
cargo fmt --all --check --manifest-path bonsai/Cargo.toml
cargo fmt --all --check --manifest-path bonsai/examples/governance/Cargo.toml

cargo install cargo-sort
cargo sort --workspace --check
cargo sort --workspace --check examples
cargo sort --workspace --check bonsai
cargo sort --workspace --check bonsai/examples/governance

python license-check.py
