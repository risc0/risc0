#!/bin/bash

set -euo pipefail

# TODO: move this to macos agent installer
# - name: Install gdb dependencies
#   run: brew install zstd gettext lz4 mpfr gmp
#   if: matrix.os == 'macOS'

# TODO: move this to agent plugin
# - name: Login to Docker Hub
#   if: >
#     matrix.os == 'Linux' &&
#     github.event.pull_request.head.repo.full_name == github.event.pull_request.base.repo.full_name
#   uses: docker/login-action@v3
#   with:
#     username: ${{ secrets.DOCKERHUB_CI_USER }}
#     password: ${{ secrets.DOCKERHUB_CI_PAT }}
# - uses: baptiste0928/cargo-install@v3
#   with:
#     crate: cargo-nextest
#     version: "0.9.96"

if [[ "${FEATURE}" == "cuda" ]]; then
  echo "--- nvidia-smi"
  nvidia-smi
fi

echo "--- cargo install cargo-nextest"
cargo install cargo-nextest@0.9.96

echo "--- install rust toolchain: $RISC0_RUST_TOOLCHAIN_VERSION"
cargo run --bin rzup -- --verbose install rust $RISC0_RUST_TOOLCHAIN_VERSION

echo "--- install cpp toolchain: $RISC0_CPP_TOOLCHAIN_VERSION"
cargo run --bin rzup -- --verbose install cpp $RISC0_CPP_TOOLCHAIN_VERSION

echo "--- install gdb component: $RISC0_CPP_TOOLCHAIN_VERSION"
cargo run --bin rzup -- --verbose install gdb $RISC0_CPP_TOOLCHAIN_VERSION

echo "--- install groth16 component: $RISC0_GROTH16_VERSION"
cargo run --bin rzup -- --verbose install risc0-groth16 $RISC0_GROTH16_VERSION

echo "--- test workspace"
$TEST_CMD \
  -F $FEATURE \
  -F prove \
  -F redis \
  -F unstable \
  --workspace \
  --timings \
  --exclude doc-test

echo "--- test risc0-r0vm (disable-dev-mode)"
cargo nextest run --release -p risc0-r0vm -F $FEATURE -F disable-dev-mode -- dev_mode

echo "--- sccache stats"
sccache --show-stats
