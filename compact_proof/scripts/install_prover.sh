#!/bin/bash

set -eoux

docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
