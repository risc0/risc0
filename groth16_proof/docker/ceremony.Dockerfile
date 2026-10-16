# syntax=docker/dockerfile:1.7
FROM rust:1.84-bookworm AS dependencies

WORKDIR /src/

# APT deps
RUN apt -qq update && \
  apt install -y -q apt-transport-https build-essential clang cmake curl gnupg libgmp-dev libsodium-dev m4 nasm nlohmann-json3-dev npm

WORKDIR /src/

# Build and install circom
# Use the same circom version and flags as prover.Dockerfile so the r1cs matches
RUN git clone https://github.com/iden3/circom.git && \
  cd circom && \
  git checkout e410b0d5cd2948a15931df0bc50d79ce56fa8c32 && \
  cargo install --locked --path circom

ENV CC=clang
ENV CXX=clang++

# Cache ahead of the larger build process
FROM dependencies AS builder

WORKDIR /src/
COPY groth16/risc0.circom ./groth16/risc0.circom
COPY groth16/stark_verify.circom ./groth16/stark_verify.circom

# Build the r1cs
RUN (cd groth16; circom --r1cs --O2 stark_verify.circom)

# Create a final clean image with all the dependencies to run the ceremony
FROM node AS ceremony

WORKDIR /ceremony

# install snarkjs globally
RUN npm install -g snarkjs@0.7.5

COPY scripts/run_ceremony.sh .
COPY --from=builder /src/groth16/stark_verify.r1cs /ceremony/stark_verify.r1cs
RUN chmod +x run_ceremony.sh
RUN ulimit -s unlimited

ENTRYPOINT ["/ceremony/run_ceremony.sh", "/ceremony/stark_verify.r1cs", "/ceremony/groth16/pot23.ptau"]
