<!-- cargo-rdme start -->

# Bento

The bento crate is a more feature-complete implementation of the prover example.

## How To Run

1. Build the docker images:

```
docker compose --file compose.yml --env-file sample.env up --build
```

2. Invoke the `bento` CLI:

```
RUST_LOG=info cargo run --bin bento_cli -- -e -c 32
```

<!-- cargo-rdme end -->
