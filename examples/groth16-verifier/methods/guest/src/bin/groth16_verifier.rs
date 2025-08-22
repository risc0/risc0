// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_groth16::{ProofJson, PublicInputsJson, Verifier, VerifyingKeyJson};
use risc0_zkvm::{guest::env, sha::Digestible};

pub fn main() {
    let (proof_json, public_inputs_json, verifying_key_json): (
        ProofJson,
        PublicInputsJson,
        VerifyingKeyJson,
    ) = env::read();

    Verifier::from_json(
        proof_json,
        public_inputs_json.clone(),
        verifying_key_json.clone(),
    )
    .unwrap()
    .verify()
    .unwrap();

    let verifying_key_digest = verifying_key_json.verifying_key().unwrap().digest();
    let public_inputs_digest = public_inputs_json.to_scalar().unwrap().digest();
    env::commit(&(verifying_key_digest, public_inputs_digest));
}
