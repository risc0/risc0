#!/bin/bash

set -euo pipefail

cargo doc --workspace --no-deps --exclude=risc0-zkvm-methods
