#!/bin/bash

set -euo pipefail
# Enable trace when DEBUG=1
[[ "${DEBUG:-}" != "" ]] && set -x

docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
