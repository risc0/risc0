# syntax=docker/dockerfile:1
FROM rust:1.72.1 AS dependencies

WORKDIR /src/

# APT deps
RUN apt -qq update && \
  apt install -y -q clang apt-transport-https curl gnupg nodejs npm build-essential nlohmann-json3-dev nasm cmake libgmp-dev libsodium-dev

WORKDIR /src/

# Build and install circom
RUN git clone https://github.com/iden3/circom.git && \
  cd circom && \
  git checkout e60c4ab8a0b55672f0f42fbc68a74203bdb6a700 && \
  cargo install --path circom

# install snarkjs globally
RUN npm install -g snarkjs@0.7.3

ENV CC=clang
ENV CXX=clang++

COPY groth16/risc0.circom ./groth16/risc0.circom
COPY groth16/stark_verify.circom ./groth16/stark_verify.circom
COPY scripts/build.sh ./


# Set up sccache
ENV  SCCACHE_URL=https://github.com/mozilla/sccache/releases/download
ENV  SCCACHE_VERSION=v0.7.1

# Install sccache
RUN SCCACHE_FILE=sccache-$SCCACHE_VERSION && \
  curl -L "$SCCACHE_URL/$SCCACHE_VERSION/$SCCACHE_FILE.tar.gz" | tar xz && \
  mv -f $SCCACHE_FILE/sccache /usr/local/bin/sccache && \
  chmod +x /usr/local/bin/sccache


ENV AWS_ACCESS_KEY_ID=changeme
ENV AWS_SECRET_ACCESS_KEY=changeme
ENV RUSTC_WRAPPER=/usr/local/bin/sccache
ENV SCCACHE_REGION=us-west-2
ENV SCCACHE_BUCKET=risc0-ci-cache
ENV SCCACHE_S3_KEY_PREFIX=public/groth16/sccache
#ENV SCCACHE_ENDPOINT=cdn.example.org
#ENV SCCACHE_S3_USE_SSL=true

# Cache ahead of the larger build process
FROM dependencies AS build

WORKDIR /src/
RUN ./build.sh

FROM scratch AS outputs

COPY --from=build /src/groth16/stark_verify_cpp/stark_verify /
COPY --from=build /src/groth16/stark_verify_cpp/stark_verify.dat /
COPY --from=build /src/groth16/stark_verify.r1cs /
