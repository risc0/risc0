# Groth16 Prover

> WARNING: This software is still experimental, we do not recommend it for
> production use (see Security section).

This directory contains utilities for performing a "stark2snark" workflow. This
is useful for transforming a RISC Zero STARK proof into a Groth16 SNARK proof
which is suitable for publishing on-chain.

## Quickstart

To install the necessary dependencies, run:
```bash
./scripts/install_prover.sh
```

## Manual installation

All the following commands must be run from the `compact_proof` directory.

1. Build circom files and binaries:
```bash
docker build -f docker/build.Dockerfile . -t snark-build --output=groth16 --target outputs
```

2. Copy the `stark_verify_final.zkey` from a ceremony into the `groth16` directory.
Alternatively, run the ceremony (optional):
```bash
wget -O groth16/pot23.ptau https://hermez.s3-eu-west-1.amazonaws.com/powersOfTau28_hez_final_23.ptau
docker build -f docker/ceremony.Dockerfile . -t snark-ceremony
docker run --rm -v $(pwd)/groth16:/ceremony/groth16 snark-ceremony
```

3. Build the prover image:
```bash
docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
```

## Proof Generation

The `input.json` file needs to be generated using the `seal-to-json` utility.
Place this file into the directory of your choice, then add this as a volume and
run the docker container:

```bash
docker run --rm -v $WORK_DIR:/mnt risc0-groth16-prover
```

The resulting `output.json` file will be in the chosen `$WORK_DIR`.
This file can be parsed and decoded into a `Groth16Seal`.
Finally, this seal can be embedded within a `InnerReceipt::Groth16`.

See [`seal_to_json/src/tests.rs`](./seal_to_json/src/tests.rs) for an end-to-end
example.
