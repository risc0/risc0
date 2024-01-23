# ZKVM Crates.io Validation tools

This tool allows for spot or bulk testing of different crates.io crates within the zkvm. Using crates.io database export data, combined with manual additions it allows for bulk testing of build/run compatibility of crates with the risc0 zkvm.

## Running

### Build a profile

```bash
RUST_LOG=info cargo run --bin gen-profiles -- -r ~/src/risc0/ -d /tmp/db-dump.tar.gz -o /tmp/profile.json
# Optionally you can select a single crate, useful for testing profile customizations:
RUST_LOG=info cargo run --bin gen-profiles -- -r ~/src/risc0/ -d /tmp/db-dump.tar.gz -o /tmp/profile.json -n lazy_static
```

### Run the profile

```bash
RUST_LOG=info cargo run -- -p /tmp/profile.json
```
