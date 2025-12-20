#!/bin/bash

set -euo pipefail

echo "--- root: cargo clippy"
cargo clippy -F $FEATURE -F unstable --all-targets

echo "--- benchmarks: cargo clippy"
pushd benchmarks
cargo clippy -F $FEATURE --all-targets
popd

echo "--- examples: cargo clippy"
pushd examples
cargo clippy -F $FEATURE --all-targets
popd
