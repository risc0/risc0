# syntax=docker/dockerfile:1
FROM rust:1.85.0-bookworm AS builder

RUN apt-get -qq update && apt-get install -y -q clang

WORKDIR /src/
COPY . ./bento/

WORKDIR /src/bento/

SHELL ["/bin/bash", "-c"]

# Consider using if building and running on the same CPU
# ENV RUSTFLAGS="-C target-cpu=native"

RUN cargo build --release -p workflow --bin agent && \
    cp /src/bento/target/release/agent /src/agent

# Use risczero/risc0-groth16-prover:v2025-01-31.1 as the basis for the prover and witness generator
FROM risczero/risc0-groth16-prover@sha256:2829419e1bee4b87a2ade42569d9dffb4a304bf593c531caa99c6a395e2558da AS binaries

FROM rust:1.85.0-bookworm AS runtime

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
