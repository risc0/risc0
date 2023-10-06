#!/bin/bash

set -euo pipefail

cargo run --bin cargo-risczero -- risczero install

cargo test -p risc0-build -F docker
RISC0_USE_DOCKER=1 cargo test -p risc0-zkvm -F docker -- "docker::"
