#!/bin/bash

set -euo pipefail

echo "--- root: cargo clippy"
cargo clippy -F $FEATURE -F unstable --all-targets

echo "--- benchmarks: cargo clippy"
cd benchmarks && cargo clippy -F $FEATURE --all-targets

echo "--- examples: cargo clippy"
cd examples && cargo clippy -F $FEATURE --all-targets
