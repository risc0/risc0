#!/bin/bash

set -euo pipefail

echo "--- cargo install cargo-sort"
cargo install cargo-sort@2.0.2

echo "--- cargo install cargo-rdme"
cargo install cargo-rdme@1.4.3

echo "--- cargo fmt"
cargo fmt --all --check
cargo fmt --all --check --manifest-path benchmarks/Cargo.toml
cargo fmt --all --check --manifest-path examples/Cargo.toml
cargo fmt --all --check --manifest-path tools/crates-validator/Cargo.toml

echo "--- cargo sort"
cargo sort --workspace --grouped --check
cargo sort --workspace --grouped --check benchmarks
cargo sort --workspace --grouped --check examples
cargo sort --workspace --grouped --check tools/crates-validator

echo "--- cargo rdme (bonsai/sdk)"
pushd bonsai/sdk
cargo rdme -c
popd

echo "--- cargo rdme (risc0/groth16)"
pushd risc0/groth16
cargo rdme -c
popd

echo "--- cargo rdme (risc0/zkvm)"
pushd risc0/zkvm
cargo rdme -c
popd

echo "--- license check"
python3 license-check.py

echo "-- check for "D0 NOT MERGE" comments"
[ "$(grep -re 'DO[_ ]\?NOT[_ ]\?MERGE' $(git ls-tree --full-tree --name-only -r HEAD) | tee /dev/fd/2 | wc -l)" -eq "0" ]

echo "--- Compare circom hashes to golden values"
bash .buildkite/scripts/circom_stable.sh
