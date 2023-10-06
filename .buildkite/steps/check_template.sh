#!/bin/bash

set -euo pipefail

export TMP_DIR=$PWD/tmp

cargo run --bin cargo-risczero -- risczero install
cargo build --release -p risc0-r0vm

cargo run --bin cargo-risczero risczero new \
  --template templates/rust-starter \
  --templ-subdir="" \
  --path $PWD \
  --dest $TMP_DIR \
  template-test

cargo build --release --manifest-path $TMP_DIR/template-test/Cargo.toml
$TMP_DIR/template-test/target/release/host
