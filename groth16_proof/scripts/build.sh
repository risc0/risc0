#!/bin/bash

set -eoux

# We presume the following are installed system wide:
# circom
# make and standard dev stuff
# clang
# nasm
# nlohmann/json
#
# This script is meant to be run via
# scripts/build.sh from the `groth16_proof` folder

# Run circom
(cd groth16; circom --c --r1cs stark_verify.circom)

# Edit the make file
sed -i 's/g++/clang++/' groth16/stark_verify_cpp/Makefile
sed -i 's/O3/O0/' groth16/stark_verify_cpp/Makefile

# Build the witness generation (only works on x86 machines)
(cd groth16/stark_verify_cpp; make)
