# syntax=docker/dockerfile:1
FROM rust:1.72.1 AS dependencies

WORKDIR /src/

# APT deps
RUN apt -qq update && \
    apt install -y -q clang apt-transport-https curl gnupg nodejs npm build-essential nlohmann-json3-dev nasm cmake libgmp-dev libsodium-dev

WORKDIR /src/

# Build and install circom
RUN git clone https://github.com/iden3/circom.git && \
  cd circom && \
  git checkout e60c4ab8a0b55672f0f42fbc68a74203bdb6a700 && \
  cargo install --path circom

# install snarkjs globally
RUN npm install -g snarkjs@latest

ENV CC=clang
ENV CXX=clang++

COPY groth16/risc0.circom ./groth16/risc0.circom
COPY groth16/stark_verify.circom ./groth16/stark_verify.circom
COPY scripts/build.sh ./

# Cache ahead of the larger build process
FROM dependencies AS build

WORKDIR /src/
RUN ./build.sh

FROM scratch AS outputs

COPY --from=build /src/groth16/stark_verify_cpp/stark_verify /
COPY --from=build /src/groth16/stark_verify_cpp/stark_verify.dat /
COPY --from=build /src/groth16/stark_verify.r1cs /
