# syntax=docker/dockerfile:1.7
FROM rust:1.74.0 AS dependencies

WORKDIR /src/

# APT deps
RUN apt -qq update && \
  apt install -y -q apt-transport-https build-essential clang cmake curl gnupg libgmp-dev libsodium-dev m4 nasm nlohmann-json3-dev npm

WORKDIR /src/

# Build and install circom
RUN git clone https://github.com/iden3/circom.git && \
  cd circom && \
  git checkout e60c4ab8a0b55672f0f42fbc68a74203bdb6a700 && \
  cargo install --path circom

ENV CC=clang
ENV CXX=clang++

# Build rapidsnark
RUN git clone https://github.com/iden3/rapidsnark.git && \
  cd rapidsnark && \
  git checkout 547bbda73bea739639578855b3ca35845e0e55bf

WORKDIR /src/rapidsnark/
# Copied from: https://github.com/iden3/rapidsnark/blob/main/tasksfile.js
# to bypass the taskfile dep in NPM being dropped
RUN git submodule init && \
  git submodule update && \
  mkdir -p build && \
  (cd depends/ffiasm && npm install) && \
  cd build/ && \
  node ../depends/ffiasm/src/buildzqfield.js -q 21888242871839275222246405745257275088696311157297823662689037894645226208583 -n Fq && \
  node ../depends/ffiasm/src/buildzqfield.js -q 21888242871839275222246405745257275088548364400416034343698204186575808495617 -n Fr && \
  nasm -felf64 fq.asm && \
  nasm -felf64 fr.asm && \
  g++ -I. -I../src -I../depends/ffiasm/c -I../depends/json/single_include ../src/main_prover.cpp ../src/binfile_utils.cpp ../src/zkey_utils.cpp ../src/wtns_utils.cpp ../src/logger.cpp ../depends/ffiasm/c/misc.cpp ../depends/ffiasm/c/naf.cpp ../depends/ffiasm/c/splitparstr.cpp ../depends/ffiasm/c/alt_bn128.cpp fq.cpp fq.o fr.cpp fr.o -o prover -fmax-errors=5 -std=c++17 -pthread -lgmp -lsodium -O3 -fopenmp &&\
  cp ./prover /usr/local/sbin/rapidsnark

# Cache ahead of the larger build process
FROM dependencies AS builder

WORKDIR /src/
COPY groth16/risc0.circom ./groth16/risc0.circom
COPY groth16/stark_verify.circom ./groth16/stark_verify.circom

# Build the witness generation
RUN (cd groth16; circom --c stark_verify.circom) && \
  sed -i 's/g++/clang++/' groth16/stark_verify_cpp/Makefile && \
  sed -i 's/O3/O0/' groth16/stark_verify_cpp/Makefile && \
  (cd groth16/stark_verify_cpp; make)

# Download the proving key
RUN wget https://risc0-artifacts.s3.us-west-2.amazonaws.com/zkey/2024-05-17.1/stark_verify_final.zkey.gz -O groth16/stark_verify_final.zkey.gz && \
  (cd groth16; gzip -df stark_verify_final.zkey.gz)

# Create a final clean image with all the dependencies to perform stark->snark
FROM ubuntu:jammy-20231211.1@sha256:bbf3d1baa208b7649d1d0264ef7d522e1dc0deeeaaf6085bf8e4618867f03494 AS prover

RUN apt update -qq && \
  apt install -y libsodium23 nodejs npm && \
  npm install -g snarkjs@0.7.3

COPY scripts/prover.sh /app/prover.sh
COPY --from=builder /usr/local/sbin/rapidsnark /usr/local/sbin/rapidsnark
COPY --from=builder /src/groth16/stark_verify_cpp/stark_verify /app/stark_verify
COPY --from=builder /src/groth16/stark_verify_cpp/stark_verify.dat /app/stark_verify.dat
COPY --from=builder /src/groth16/stark_verify_final.zkey /app/stark_verify_final.zkey

WORKDIR /app
RUN chmod +x prover.sh
RUN ulimit -s unlimited

ENTRYPOINT ["/app/prover.sh"]
