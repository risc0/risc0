# Groth16

> WARNING: This software is still experimental, we do not recommend it for
> production use (see Security section).

This library implements a verifier for the Groth16 protocol over the BN_254 elliptic curve.

## Example

```rust
use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};

    const TEST_VERIFICATION_KEY: &str = include_str!("data/verification_key.json");
    const TEST_PROOF: &str = include_str!("data/proof.json");
    const TEST_PUBLIC_INPUTS: &str = include_str!("data/public.json");

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

## STARK to SNARK
It also provides a utility function to call a prover (via Docker).
After generating a RISC Zero STARK proof, it can be transformed into a SNARK using the `stark_to_snark` function.
This function becomes available when the `prove` feature flag is enabled.

> WARNING: This feature is in an experimental stage. It requires an x86 architecture and Docker installed.
> Additionally, specific [installation steps](https://github.com/risc0/risc0/tree/main/compact_proof) must be followed to use this functionality.

### Example

```rust
#[cfg(feature = "prove")]
fn stark2snark() {
    use risc0_groth16::docker::stark_to_snark;
    use risc0_zkvm::{
        get_prover_server, recursion::identity_p254, CompactReceipt, ExecutorEnv, ExecutorImpl,
        InnerReceipt, ProverOpts, Receipt, VerifierContext,
    };
    use risc0_zkvm_methods_core::multi_test::MultiTestSpec;
    use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID};

    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::BusyLoop { cycles: 0 })
        .unwrap()
        .build()
        .unwrap();

    tracing::info!("execute");

    let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = exec.run().unwrap();

    tracing::info!("prove");
    let opts = ProverOpts::default();
    let ctx = VerifierContext::default();
    let prover = get_prover_server(&opts).unwrap();
    let receipt = prover.prove_session(&ctx, &session).unwrap();
    let claim = receipt.get_claim().unwrap();
    let succinct_receipt = receipt.inner.succinct().unwrap();
    let journal = session.journal.unwrap().bytes;

    tracing::info!("identity_p254");
    let ident_receipt = identity_p254(&succinct_receipt).unwrap();
    let seal_bytes = ident_receipt.get_seal_bytes();

    tracing::info!("stark-to-snark");
    let seal = stark_to_snark(&seal_bytes).unwrap().to_vec();

    tracing::info!("Receipt");
    let receipt = Receipt::new(
        InnerReceipt::Compact(CompactReceipt { seal, claim }),
        journal,
    );

    receipt.verify(MULTI_TEST_ID).unwrap();
}
```
