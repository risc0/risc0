#!/bin/bash

# Script: prover.sh
# Description: This script generates a witness and runs the Groth16 prover

# Exit immediately if a command exits with a non-zero status
# Print commands and their arguments as they are executed
# Treat unset variables as an error when substituting
set -euxo pipefail

# Define the path for the temporary witness file
WITNESS_FILE="/tmp/output.wtns"

# Increase stack size for witness generation
ulimit -s 16384

# Create a named pipe for the witness data
mkfifo "$WITNESS_FILE"

# Run witness generation in the background
(
    stark_verify /mnt/input.json "$WITNESS_FILE" ||
    echo "stark_verify failed" > "$WITNESS_FILE"
) &

# Run the Groth16 prover
prover stark_verify.cs stark_verify_final.pk.dmp "$WITNESS_FILE" /mnt/proof.json

# Clean up the named pipe once everything is done
wait && rm "$WITNESS_FILE"

