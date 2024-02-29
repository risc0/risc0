#!/bin/bash

set -eoux

# docker build -f docker/build.Dockerfile . -t snark-build --output=groth16 --target outputs

# wget https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-02-07/stark_verify_final.zkey.gz -O groth16/stark_verify_final.zkey.gz
# (cd groth16; gzip -df stark_verify_final.zkey.gz)

docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
