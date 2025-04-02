# syntax=docker/dockerfile:1.7

# Stage 1: Build and install Circom
FROM rust:1.84-bookworm AS circom

# Set the working directory
WORKDIR /usr/src/

# Clone and build Circom version 2.2.2 from a specific commit
ADD https://github.com/iden3/circom.git#e410b0d5cd2948a15931df0bc50d79ce56fa8c32 circom
RUN (cd circom; cargo install --path circom)

# Add the required circuit files
COPY groth16/risc0.circom groth16/risc0.circom
COPY groth16/stark_verify.circom groth16/stark_verify.circom

# Compile the circuit using Circom
RUN (cd groth16; circom --r1cs --c --O2 --no_asm stark_verify.circom)

# Stage 2: Compile the witness generator from scratch
FROM debian:bookworm AS witgen

WORKDIR /usr/src/

# Install necessary build dependencies
RUN apt-get update -q -y && apt-get install -q -y build-essential clang libgmp-dev nasm nlohmann-json3-dev

COPY --from=circom /usr/src/groth16/stark_verify_cpp/ stark_verify_cpp/

# Install python and slice up the witness generator
RUN apt-get install -q -y python3-dev
COPY scripts/split.py scripts/split.py
RUN python3 scripts/split.py stark_verify_cpp/stark_verify.cpp \
    stark_verify_cpp/stark_verify.x
RUN mv stark_verify_cpp/stark_verify.x \
    stark_verify_cpp/stark_verify.cpp

COPY scripts/replacement-Makefile stark_verify_cpp/Makefile

RUN (cd stark_verify_cpp; make)

# Stage 3: Build the Gnark prover
FROM golang:1.23-bookworm AS gnark

WORKDIR /usr/src/gnark

# Download the proving key and copy the generated constraint system
ADD --checksum=sha256:69c6056451ea814b37e30ccbc44639dbaafef73540cbfbff6ec7e68e2d325735 \
  https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-05-17.1/stark_verify_final.zkey.gz groth16/stark_verify_final.zkey.gz
COPY --from=circom /usr/src/groth16/stark_verify.r1cs groth16/stark_verify.r1cs

# Pre-download Go modules for cache efficiency
COPY circom-compat/go.mod circom-compat/go.sum ./
RUN go mod download && go mod verify

# Copy all Go source code
COPY circom-compat/. ./

# Build the Gnark prover with CGO disabled for static linking
ENV CGO_ENABLED=0
RUN go build ./cmd/prover

# Convert files to Gnark format using a custom converter tool
RUN go run ./cmd/converter --dump groth16/stark_verify.r1cs groth16/stark_verify_final.zkey.gz

# Final Stage: Create a minimal image to run the prover and witness generator
FROM debian:bookworm-slim

# Copy the prover binary and related files from previous stages
COPY --from=gnark /usr/src/gnark/prover /usr/local/bin/prover
COPY --from=gnark /usr/src/gnark/groth16/stark_verify.cs /app/stark_verify.cs
COPY --from=gnark /usr/src/gnark/groth16/stark_verify_final.pk.dmp /app/stark_verify_final.pk.dmp

# Copy the witness generator and data files from the witgen stage
COPY --from=witgen /usr/src/stark_verify_cpp/stark_verify /usr/local/bin/stark_verify
COPY --from=witgen /usr/src/stark_verify_cpp/stark_verify.dat /app/stark_verify.dat

# Install entrypoint script and set executable permissions
COPY scripts/prover.sh /app/prover.sh
RUN chmod +x /app/prover.sh

WORKDIR /app

ENTRYPOINT ["/app/prover.sh"]
