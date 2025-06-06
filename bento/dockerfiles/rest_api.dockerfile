ARG S3_CACHE_PREFIX="public/rust-cache-docker-Linux-X64/sccache"

FROM rust:1.85.0-bookworm AS builder

RUN apt-get -qq update && apt-get install -y -q clang

FROM builder AS rust-builder

ARG S3_CACHE_PREFIX

WORKDIR /src/
COPY . .
RUN bento/dockerfiles/sccache-setup.sh "x86_64-unknown-linux-musl" "v0.8.2"
SHELL ["/bin/bash", "-c"]

# Prevent sccache collision in compose-builds
ENV SCCACHE_SERVER_PORT=4230

RUN --mount=type=secret,id=ci_cache_creds,target=/root/.aws/credentials \
    --mount=type=cache,target=/root/.cache/sccache/,id=bento_api_sccache \
    source bento/dockerfiles/sccache-config.sh ${S3_CACHE_PREFIX} && \
    cargo build --manifest-path bento/Cargo.toml --release -p api --bin rest_api && \
    cp bento/target/release/rest_api /src/rest_api && \
    sccache --show-stats

FROM rust:1.85.0-bookworm AS runtime

RUN mkdir /app/ && \
    apt -qq update && \
    apt install -y -q openssl

COPY --from=rust-builder /src/rest_api /app/rest_api
ENTRYPOINT ["/app/rest_api"]
