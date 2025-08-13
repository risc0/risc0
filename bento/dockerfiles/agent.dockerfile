# syntax=docker/dockerfile:1
ARG CUDA_IMG=nvidia/cuda:12.8.0-devel-ubuntu24.04
ARG CUDA_RUNTIME_IMG=nvidia/cuda:12.8.0-runtime-ubuntu24.04
ARG S3_CACHE_PREFIX="public/rust-cache-docker-Linux-X64/sccache"

FROM ${CUDA_IMG} AS rust-builder

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Los_Angeles"

RUN apt-get -qq update && apt-get install -y -q \
    openssl libssl-dev pkg-config curl clang git \
    build-essential openssh-client unzip

ENV RUSTUP_HOME=/usr/local/rustup \
    CARGO_HOME=/usr/local/cargo \
    PATH=/usr/local/cargo/bin:$PATH

# Install rust and a target rust version (should match rust-toolchain.toml for best speed)
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
RUN chmod -R a+w $RUSTUP_HOME $CARGO_HOME
RUN rustup install 1.81

# Install protoc
RUN curl -o protoc.zip -L https://github.com/protocolbuffers/protobuf/releases/download/v31.1/protoc-31.1-linux-x86_64.zip
RUN unzip protoc.zip -d /usr/local

FROM rust-builder AS builder

ARG NVCC_APPEND_FLAGS="\
  --generate-code arch=compute_75,code=sm_75 \
  --generate-code arch=compute_80,code=sm_80 \
  --generate-code arch=compute_86,code=sm_86 \
  --generate-code arch=compute_89,code=sm_89 \
  --generate-code arch=compute_90,code=sm_90 \
  --generate-code arch=compute_120,code=compute_120"
ARG CUDA_OPT_LEVEL=1
ARG S3_CACHE_PREFIX
ENV NVCC_APPEND_FLAGS=${NVCC_APPEND_FLAGS}
ENV RISC0_CUDA_OPT=${CUDA_OPT_LEVEL}
ENV SCCACHE_SERVER_PORT=4227
# ENV SCCACHE_LOG=trace

WORKDIR /src/
COPY . .

# Install groth16 component
ENV RISC0_HOME=/usr/local/risc0
RUN cargo run --package rzup -- --verbose install risc0-groth16

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

FROM ${CUDA_RUNTIME_IMG} AS runtime

RUN apt-get update -q -y && apt-get install -q -y ca-certificates libssl3 && rm -rf /var/lib/apt/lists/*

# Main prover
COPY --from=builder /src/agent /app/agent

# copy rzup directory
COPY --from=builder /usr/local/risc0 /usr/local/risc0

ENTRYPOINT ["/app/agent"]
