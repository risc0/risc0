# syntax=docker/dockerfile:1.7
FROM rust:1.74.0 AS dependencies

WORKDIR /src/

# APT deps
RUN apt -qq update && \
  apt install -y -q apt-transport-https build-essential clang cmake curl gnupg libgmp-dev libsodium-dev m4 nasm nlohmann-json3-dev npm

# Build and install circom
RUN git clone https://github.com/iden3/circom.git && \
  cd circom && \
  git checkout e60c4ab8a0b55672f0f42fbc68a74203bdb6a700 && \
  cargo install --path circom

ENV CC=clang
ENV CXX=clang++

# Cache ahead of the larger build process
FROM dependencies AS builder

COPY groth16/risc0.circom ./groth16/risc0.circom
COPY groth16/stark_verify.circom ./groth16/stark_verify.circom

# Build the r1cs
RUN (cd groth16; circom --r1cs stark_verify.circom)

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
