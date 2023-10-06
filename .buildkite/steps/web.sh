#!/bin/bash

set -euo pipefail

export RISC0_BUILD_LOCKED=1
# export RUSTC_WRAPPER=sccache

cargo run --bin cargo-risczero -- risczero install

cargo xtask install
cargo xtask gen-receipt

cd examples/browser-verify

npm install
npm test -- --firefox
