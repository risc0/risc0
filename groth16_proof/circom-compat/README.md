# circom-compat

Gnark bindings to Circom's R1CS, WTNS, and ZKEY for Groth16 proof generation in Go. This library enables seamless integration of Circom circuits within the gnark ecosystem.

### Requirements

- Go 1.22 or newer
- Circom circuit files:
   - [stark_verify.r1cs](https://risc0-artifacts.s3.us-west-2.amazonaws.com/tsc/2024-04-04/stark_verify.r1cs)
   - [stark_verify_final.zkey](https://risc0-artifacts.s3.us-west-2.amazonaws.com/tsc/2024-04-04/stark_verify_final.zkey)
- Witness file
- (Small examples provided under [test/data](test/data))

### Creating a Groth16 Proof

Use the `cmd/prover` tool to create a Groth16 proof:

```sh
go run cmd/prover/main.go test/data/multiplier2.r1cs test/data/multiplier2_final.zkey test/data/multiplier2.wtns proof.json
```

This command is similar to [rapidsnark](https://github.com/iden3/rapidsnark) but also requires the constraint system as input.

### Converting Circom Files to Gnark Format

For improved efficiency, convert Circom files to Gnark format:

```sh
go run cmd/converter/main.go test/data/multiplier2.r1cs test/data/multiplier2_final.zkey
```

This creates `multiplier2.cs` and `multiplier2_final.pk`, which can be used instead of their Circom counterparts when running the prover.
