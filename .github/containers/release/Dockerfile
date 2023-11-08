FROM nvidia/cuda:12.2.2-devel-ubuntu20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt -y install curl libssl-dev pkg-config
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

WORKDIR /src
