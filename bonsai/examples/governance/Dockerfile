# Start from rust template
FROM rust

# Install Foundry
RUN cargo install --git https://github.com/foundry-rs/foundry --profile local --force foundry-cli anvil chisel

# Install rust toolchain
COPY rust-toolchain.toml .
RUN rustup toolchain install .

# Copy source code
COPY . .

# Update github host
RUN mkdir -p /root/.ssh && ssh-keyscan github.com > ~/.ssh/known_hosts

# Build solidity code
RUN forge build

# Build rust code
RUN --mount=type=ssh  \
    cargo build

ENTRYPOINT ["forge"]
