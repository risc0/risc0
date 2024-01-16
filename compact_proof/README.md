# Groth16 Prover

## Quickstart

To install the necessary dependencies, run:
```bash
./scripts/install_prover.sh
```

## Manual installation

All the following commands must be run from the `compact_proof` folder.

1. Build circom files and binaries
```bash
docker build -f docker/build.Dockerfile . -t snark-build --output=groth16 --target outputs
```

2. Copy the `stark_verify_final.zkey` from a ceremony into the `groth16` folder. Alternatively, run the ceremony (optional)
```bash
wget -O groth16/pot23.ptau https://hermez.s3-eu-west-1.amazonaws.com/powersOfTau28_hez_final_23.ptau
docker build -f docker/ceremony.Dockerfile . -t snark-ceremony
docker run --rm -v $(pwd)/groth16:/ceremony/groth16 snark-ceremony
```

3. Build the prover image
```bash
docker build -f docker/prover.Dockerfile . -t risc0-groth16-prover
```

## Proof Genration
```bash
docker run --rm -v seal.json:/app/input.json:ro risc0-groth16-prover
```
