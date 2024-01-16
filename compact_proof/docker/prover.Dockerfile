# syntax=docker/dockerfile:1
FROM ubuntu:jammy-20231211.1@sha256:bbf3d1baa208b7649d1d0264ef7d522e1dc0deeeaaf6085bf8e4618867f03494 AS builder

# APT deps
RUN apt -qq update && \
  apt install -y -q build-essential clang cmake libsodium-dev libgmp-dev nodejs npm nasm m4

ENV CC=clang
ENV CXX=clang++

WORKDIR /src

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

# Create a final clean image with all the dependencies to perform stark->snark
FROM ubuntu:jammy-20231211.1@sha256:bbf3d1baa208b7649d1d0264ef7d522e1dc0deeeaaf6085bf8e4618867f03494 AS prover

# install snarkjs for the `soliditycalldata` subcommand
RUN apt update -qq && \
  apt install -y libsodium23 nodejs npm && \
  npm install -g snarkjs@latest

COPY --from=builder /usr/local/sbin/rapidsnark /usr/local/sbin/rapidsnark
COPY groth16/stark_verify_final.zkey /app/stark_verify_final.zkey
COPY groth16/stark_verify /app/stark_verify
COPY groth16/stark_verify.dat /app/stark_verify.dat
COPY scripts/prover.sh /app/prover.sh

WORKDIR /app
RUN chmod +x prover.sh
RUN ulimit -s unlimited

ENTRYPOINT ["/app/prover.sh"]
