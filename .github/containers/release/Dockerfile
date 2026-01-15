FROM nvidia/cuda:12.2.2-devel-ubuntu20.04 as base

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt -y install curl libssl-dev pkg-config libtbb-dev
RUN curl -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

WORKDIR /src

FROM base AS builder
COPY . .
RUN --mount=type=cache,id=release,target=/root/.cache \
  --mount=type=cache,id=release,target=/root/.cargo,from=base,source=/root/.cargo \
  cargo build -p cargo-risczero --release

FROM scratch AS export
COPY --from=builder /src/target/release/cargo-risczero /
COPY --from=builder /src/target/release/r0vm /
