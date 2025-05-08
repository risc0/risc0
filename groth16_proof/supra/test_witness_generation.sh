#!/bin/bash

set -e
set -x

IN_PATH="input-files"
OUT_PATH="output-files"
SCRIPTS_PATH="../scripts"

# Follow risc0's original steps to compile the witness generator for their stark_verify circuit
if [ ! -f "${OUT_PATH}/stark_verify_cpp/stark_verify" ]; then
    circom --r1cs --c --O2 --no_asm ../groth16/stark_verify.circom -o $OUT_PATH

    python3 $SCRIPTS_PATH/chunk.py $OUT_PATH/stark_verify_cpp/stark_verify.cpp
    rm $OUT_PATH/stark_verify_cpp/stark_verify.cpp
    BIG_FILE=$(du -h $OUT_PATH/stark_verify_cpp/*.cpp | sort -rh | head -1 | awk '{ print $2 }')
    python3 $SCRIPTS_PATH/outline.py "$BIG_FILE"
    rm "$BIG_FILE"

    ### COMPILE THE NEW CHUNKS ###
    rm $OUT_PATH/stark_verify_cpp/Makefile
    cp $SCRIPTS_PATH/replacement-Makefile $OUT_PATH/stark_verify_cpp/Makefile
    cd $OUT_PATH/stark_verify_cpp/
    make -j`nproc`
    cd ../..
fi

# Generate the witness for the original circuit with circom
./$OUT_PATH/stark_verify_cpp/stark_verify $IN_PATH/fib-seal.json $OUT_PATH/fib-seal.wtns
./$OUT_PATH/stark_verify_cpp/stark_verify $IN_PATH/loop-seal.json $OUT_PATH/loop-seal.wtns

# Generate the witness for the modified circuit with the optimized witness generator
./circom-witnesscalc/target/release/calc-witness-bn254 $OUT_PATH/parallel-graph $IN_PATH/fib-seal.json $OUT_PATH/fib-seal-rust.wtns
./circom-witnesscalc/target/release/calc-witness-bn254 $OUT_PATH/parallel-graph $IN_PATH/loop-seal.json $OUT_PATH/loop-seal-rust.wtns

# Ensure that the witnesses match each other
diff $OUT_PATH/fib-seal.wtns $OUT_PATH/fib-seal-rust.wtns
diff $OUT_PATH/loop-seal.wtns $OUT_PATH/loop-seal-rust.wtns
