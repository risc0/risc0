# Groth16 Prover

> WARNING: This software is still experimental, we do not recommend it for
> production use (see Security section).
>
> Currently, due to the Circom native C++ witness generator that depends on x86 assembly for field operations, only x86 architecture is supported.

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
run the docker container:

```bash
docker run --rm -v $WORK_DIR:/mnt risc0-groth16-prover
```

The resulting `proof.json` file will be in the chosen `$WORK_DIR`.
This file can be parsed and decoded into a `risc0_groth16::Seal`.
Finally, this seal can be embedded within a `InnerReceipt::Compact`.

See [`risc0-zkvm/src/host/server/prove/tests.rs`](../risc0/zkvm/src/host/server/prove/tests.rs) for an end-to-end
example.
