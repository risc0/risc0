#!/bin/bash

set -e
set -x

IN_PATH="input-files"
OUT_PATH="output-files"

if [ ! -f "${OUT_PATH}/verification_key.json" ]; then
    snarkjs zkey export verificationkey $IN_PATH/stark_verify_final.zkey $OUT_PATH/verification_key.json
fi

time ./cuda/run_prover $OUT_PATH $IN_PATH/stark_verify_final.zkey $IN_PATH/fib-seal.json
snarkjs groth16 verify $OUT_PATH/verification_key.json public.json proof.json

time ./cuda/run_prover $OUT_PATH $IN_PATH/stark_verify_final.zkey $IN_PATH/loop-seal.json
snarkjs groth16 verify $OUT_PATH/verification_key.json public.json proof.json
