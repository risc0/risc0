# Groth16 Prover

This directory contains utilities for performing a "stark2snark" workflow. This
is useful for transforming a RISC Zero STARK proof into a Groth16 SNARK proof
which is suitable for publishing on-chain.

> Recommended way to produce Groth16 receipts is to use the `Prover` trait in the `risc0-zkvm` crate.
> See the crate documentation for more information.

## Quickstart

To install the necessary dependencies, run:

```bash
./scripts/install_prover.sh
```

## Manual Installation

All the following commands must be run from the `groth16_proof` directory.

1. Run the ceremony (optional):
   ```bash
   wget -O groth16/pot23.ptau https://hermez.s3-eu-west-1.amazonaws.com/powersOfTau28_hez_final_23.ptau
   docker build -f docker/ceremony.Dockerfile . -t snark-ceremony
   docker run --rm -v $(pwd)/groth16:/ceremony/groth16 snark-ceremony
   ```
2. Build the prover image:
   ```bash
   docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
   ```
   > Note that the `prover.Dockerfile` downloads a proving key from an existing ceremony.
   > If a new ceremony is required, replace it with the new proving key generated in step 1.

## Proof Generation

The `input.json` file needs to be generated using the `seal-to-json` utility.
Place this file into the directory of your choice, then add this as a volume and
run the Docker container:

```bash
docker run --rm -v $WORK_DIR:/mnt risc0-groth16-prover
```

The resulting `proof.json` file will be in the chosen `$WORK_DIR`.
This file can be parsed and decoded into a `risc0_groth16::Seal`.
Finally, this seal can be embedded within a `InnerReceipt::Groth16`.

See [`risc0-zkvm/src/host/server/prove/tests.rs`](../risc0/zkvm/src/host/server/prove/tests.rs) for an end-to-end
example.
