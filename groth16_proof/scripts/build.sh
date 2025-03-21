#!/bin/bash

set -eoux

# We presume the following are installed system wide:
# circom 2.2.2 or later
# make and standard dev stuff
# clang
# nasm
# nlohmann/json
#
# This script is meant to be run via
# scripts/build.sh from the `groth16_proof` folder

# Run circom
(cd groth16; circom --c --no_asm --r1cs --O2 stark_verify.circom)

# Replace the makefile, since we are about to break the main file down into
# pieces for individual compilation, and we want to use clang anyway.
cp scripts/replacement-Makefile groth16/stark_verify_cpp/Makefile

# Break the generated program into more manageable pieces.
python3 scripts/chunk.py groth16/stark_verify_cpp/stark_verify.cpp
rm groth16/stark_verify_cpp/stark_verify.cpp

# One of the pieces will be much larger than the others; we expect it to be
# the top-level Verify_*_run function. Break it down further.
BIG_FILE=$(du -h groth16/stark_verify_cpp/*.cpp | sort -rh | head -1 | awk '{ print $2 }')
python3 scripts/outline.py "$BIG_FILE"
rm "$BIG_FILE"

# Build the witness generation
(cd groth16/stark_verify_cpp; make -j`nproc`)
