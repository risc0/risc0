<!-- cargo-rdme start -->

# Groth16

This library implements a verifier for the Groth16 protocol over the BN_254 elliptic curve.

## Example

```rust
use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};

const TEST_VERIFICATION_KEY: &str = test_data!("verification_key.json");
const TEST_PROOF: &str = test_data!("proof.json");
const TEST_PUBLIC_INPUTS: &str = test_data!("public.json");

fn verify() {
    let verifying_key: VerifyingKeyJson = serde_json::from_str(TEST_VERIFICATION_KEY).unwrap();
    let proof: ProofJson = serde_json::from_str(TEST_PROOF).unwrap();
    let public_inputs = PublicInputsJson {
        values: serde_json::from_str(TEST_PUBLIC_INPUTS).unwrap(),
    };
    let verifier = Verifier::from_json(proof, public_inputs, verifying_key).unwrap();
    verifier.verify().unwrap();
}
```

## Shrink Wrap (aka STARK to SNARK)

It also provides the [shrink_wrap][prove::shrink_wrap] function to run a prover Groth16
recursion prover via Docker. After generating a RISC Zero STARK proof, this function can be
used to transform it into a Groth16 proof. This function becomes available when the `prove`
feature flag is enabled.

> IMPORTANT: This feature requires an x86 architecture and Docker installed.
> Additionally, specific [installation steps](https://github.com/risc0/risc0/tree/main/groth16_proof) must be followed to use this functionality.

The recommended way to get a Groth16 proof is to use the `Prover` trait in the [risc0-zkvm]
crate. With `ProverOpts::groth16()` it will produce a Groth16 proof.

[risc0-zkvm]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/

# Publishing the rzup Component
The groth16 proving on GPU requires a special rzup component be installed. Publishing this
omponent can be done with the following commands

```bash
export VERSION=0.1.0
cargo xtask-groth16 -- ~/groth16-tmp
cargo run --bin rzup -- \
    publish create-artifact \
    --input ~/groth16-tmp/v$VERSION-risc0-groth16 \
    --output ~/groth16-component.tar.xz
aws-vault exec ci -- \
cargo run --bin rzup -- \
    publish upload \
    --target-agnostic \
    risc0-groth16 $VERSION \
    ~/groth16-component.tar.xz
```

<!-- cargo-rdme end -->
