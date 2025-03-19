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
#sed -i 's/g++/clang++/' groth16/stark_verify_cpp/Makefile
#sed -i 's/O3/O0/' groth16/stark_verify_cpp/Makefile
cp scripts/replacement-Makefile groth16/stark_verify_cpp/Makefile

# Break the generated program into more manageable pieces.
python scripts/chunk.py groth16/stark_verify_cpp/stark_verify.cpp
rm groth16/stark_verify_cpp/stark_verify.cpp

# Generate a header and insert includes so the chunks can call each other.
(cd groth16/stark_verify_cpp;
  # Extract the declarations from the first chunk to use as a common header.
  grep stark_verify-1.cpp -e "^#include" > stark_verify.h
  grep stark_verify-1.cpp -e "^void" >> stark_verify.h
  grep stark_verify-1.cpp -e "^Circom_TemplateFunction" | sed -e 's/ = {/;/g' -e 's/^/extern /' >> stark_verify.h
  # Add one missing declaration
  echo "void release_memory_component(Circom_CalcWit* ctx, uint pos);" >> stark_verify.h

  # Rewrite the first chunk, omitting the declarations we just extracted.
  grep stark_verify-1.cpp -v -e "^#include" | grep -v -e "^void" > \
    stark_verify-0.cpp
  mv stark_verify-0.cpp stark_verify-1.cpp

  # Insert an include declaration into each implementation chunk.
  find -name "stark_verify-*.cpp" -exec sed -i '1 i #include "stark_verify.h"' {} \;
)

# One of the pieces will be much larger than the others; we expect it to be
# the top-level Verify_*_run function. Break it down further.
BIG_FILE=$(du -h groth16/stark_verify_cpp/*.cpp | sort -rh | head -1 | awk '{ print $2 }')
python scripts/outline.py "$BIG_FILE"
rm "$BIG_FILE"

# Build the witness generation
(cd groth16/stark_verify_cpp; make -j`nproc`)
