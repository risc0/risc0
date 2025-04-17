# syntax=docker/dockerfile:1
ARG CUDA_IMG=nvidia/cuda:12.2.0-devel-ubuntu22.04
ARG CUDA_RUNTIME_IMG=nvidia/cuda:12.2.0-runtime-ubuntu22.04
ARG S3_CACHE_PREFIX="public/rust-cache-docker-Linux-X64/sccache"

FROM ${CUDA_IMG} AS rust-builder

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Los_Angeles"

RUN apt-get -qq update && apt-get install -y -q \
    openssl libssl-dev pkg-config curl clang git \
    build-essential openssh-client

ENV RUSTUP_HOME=/usr/local/rustup \
    CARGO_HOME=/usr/local/cargo \
    PATH=/usr/local/cargo/bin:$PATH

# Install rust and a target rust version (should match rust-toolchain.toml for best speed)
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
RUN chmod -R a+w $RUSTUP_HOME $CARGO_HOME
RUN rustup install 1.81

FROM rust-builder AS builder

ARG NVCC_APPEND_FLAGS=""
ARG CUDA_OPT_LEVEL=1
ARG S3_CACHE_PREFIX
ENV NVCC_APPEND_FLAGS=${NVCC_APPEND_FLAGS}
ENV RISC0_CUDA_OPT=${CUDA_OPT_LEVEL}
ENV SCCACHE_SERVER_PORT=4227
# ENV SCCACHE_LOG=trace

WORKDIR /src/
COPY . .
RUN bento/dockerfiles/sccache-setup.sh "x86_64-unknown-linux-musl" "v0.8.2"
SHELL ["/bin/bash", "-c"]

# Consider using if building and running on the same CPU
# ENV RUSTFLAGS="-C target-cpu=native"

RUN --mount=type=secret,id=ci_cache_creds,target=/root/.aws/credentials \
    --mount=type=cache,target=/root/.cache/sccache/,id=bento_agent_sc \
    source bento/dockerfiles/sccache-config.sh ${S3_CACHE_PREFIX} && \
    cargo build --manifest-path bento/Cargo.toml --release -p workflow -F cuda --bin agent && \
    cp bento/target/release/agent /src/agent && \
    sccache --show-stats

# Use risczero/risc0-groth16-prover:v2025-01-31.1 as the basis for the prover and witness generator
FROM risczero/risc0-groth16-prover@sha256:2829419e1bee4b87a2ade42569d9dffb4a304bf593c531caa99c6a395e2558da AS binaries

FROM ${CUDA_RUNTIME_IMG} AS runtime

RUN apt-get update -q -y && apt-get install -q -y ca-certificates libssl3 && rm -rf /var/lib/apt/lists/*

# Copy the witness generator and data files from the binary stage
COPY --from=binaries /usr/local/bin/stark_verify /app/stark_verify
COPY --from=binaries /app/stark_verify.dat /app/stark_verify.dat

# Copy the prover binary and related files from previous stages
COPY --from=binaries /usr/local/bin/prover /app/prover
COPY --from=binaries /app/stark_verify.cs /app/stark_verify.cs
COPY --from=binaries /app/stark_verify_final.pk.dmp /app/stark_verify_final.pk.dmp

# Main prover
COPY --from=builder /src/agent /app/agent

ENTRYPOINT ["/app/agent"]
