#!/bin/bash

set -eoux

docker build -f docker/build.Dockerfile . -t snark-build --output=groth16 --target outputs

wget -O groth16/stark_verify_final.zkey.tar.gz https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-01-15/stark_verify_final.zkey
(cd groth16; tar xvf stark_verify_final.zkey.tar.gz)

docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
