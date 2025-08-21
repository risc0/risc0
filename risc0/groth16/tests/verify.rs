// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(test)]
mod tests {
    use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};

    const TEST_VERIFICATION_KEY: &str = include_str!("data/verification_key.json");
    const TEST_PROOF: &str = include_str!("data/proof.json");
    const TEST_PUBLIC_INPUTS: &str = include_str!("data/public.json");

    #[test]
    fn test_verify() {
        let verifying_key: VerifyingKeyJson = serde_json::from_str(TEST_VERIFICATION_KEY).unwrap();
        let proof: ProofJson = serde_json::from_str(TEST_PROOF).unwrap();
        let public_inputs = PublicInputsJson {
            values: serde_json::from_str(TEST_PUBLIC_INPUTS).unwrap(),
        };
        let verifier = Verifier::from_json(proof, public_inputs, verifying_key).unwrap();
        verifier.verify().unwrap();
    }
}
