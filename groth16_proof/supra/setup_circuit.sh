#!/bin/bash

set -e
set -x

IN_PATH="input-files"
CIRCOM_FILE="modified-circuit/stark_verify.circom"
OUT_PATH="output-files"

if [ ! -f "${CIRCOM_FILE}" ]; then
    cp ../groth16/stark_verify.circom $CIRCOM_FILE
fi

if [ ! -d "${OUT_PATH}" ]; then
    mkdir $OUT_PATH
fi

if [ ! -f "${IN_PATH}/stark_verify_final.zkey" ]; then
    cd $IN_PATH
    wget -O- https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-05-17.1/stark_verify_final.zkey.gz | gunzip -c > stark_verify_final.zkey
    cd ..
fi

# Clone and compile the optimized witness generator
if [ ! -d "circom-witnesscalc" ]; then
    git clone git@github.com:supranational/circom-witnesscalc.git
fi

if [ ! -d "circom-witnesscalc/target/release" ]; then
    cd circom-witnesscalc
    cargo build --release
    cd ..
fi

# Generate the circuit graph with the optimized witness generator
if [ ! -f "${OUT_PATH}/stark_verify_graph.bin" ]; then
    ./circom-witnesscalc/target/release/build-circuit $CIRCOM_FILE $OUT_PATH/stark_verify_graph.bin
fi

./circom-witnesscalc/target/release/calc-parallel-graph-bn254 $OUT_PATH/stark_verify_graph.bin $OUT_PATH/parallel-graph 32

cd cuda
./build.sh
cd ..

# Preprocess and precompute some data to accelerate the proving process
# and store them for fast initialization for proving
./cuda/setup_prover $OUT_PATH $IN_PATH/stark_verify_final.zkey
