FROM nvidia/cuda:11.4.3-devel-ubuntu20.04

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Los_Angeles"

RUN apt-get -qq update && \
  apt-get install -y -q \
  build-essential \
  clang \
  curl \
  git \
  libssl-dev \
  pkg-config

ENV \
  RUSTUP_HOME=/usr/local/rustup \
  CARGO_HOME=/usr/local/cargo \
  PATH=/usr/local/cargo/bin:$PATH \
  RUST_VERSION=1.73.0

RUN curl https://sh.rustup.rs -sSf | bash -s -- -y

ENV CC=clang
ENV CXX=clang++

COPY . .
