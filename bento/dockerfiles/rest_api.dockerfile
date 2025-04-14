FROM rust:1.85.0-bookworm AS builder

RUN apt-get -qq update && apt-get install -y -q clang

FROM builder AS rust-builder

WORKDIR /src/
COPY . ./bento/

WORKDIR /src/bento/
SHELL ["/bin/bash", "-c"]

RUN cargo build --release -p api --bin rest_api && \
    cp /src/bento/target/release/rest_api /src/rest_api

FROM rust:1.85.0-bookworm AS runtime

RUN mkdir /app/ && \
    apt -qq update && \
    apt install -y -q openssl

COPY --from=rust-builder /src/rest_api /app/rest_api
ENTRYPOINT ["/app/rest_api"]
