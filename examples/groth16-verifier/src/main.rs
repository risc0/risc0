// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use anyhow::{Ok, Result};
use groth16_verifier_example::*;
use hello_world_methods::MULTIPLY_ID;
use risc0_zkvm::{
    groth16::{CircomProof, CircomPublic, CircomVKey, Groth16Proof},
    is_dev_mode, Receipt,
};

const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

fn main() -> Result<()> {
    // ----- Groth16 receipt verification from Bonsai --------
    //
    // Generate a groth16 receipt for the MULTIPLY ELF
    let groth16_receipt: Receipt = match is_dev_mode() {
        true => run_bonsai_mock(),
        false => run_bonsai(u64s_to_vec(17, 23))?,
    };

    // Groth16Receipt verification
    groth16_receipt
        .verify(MULTIPLY_ID)
        .expect("Faileed Groth16 receipt verification");
    println!("Verified the snark receipt from Bonsai");
    // -------------------------------------------------------------

    // ----- Groth16 proof verification from Circom/SnarkJS --------
    //
    // verification_key, proof and public witness generated with SnarkJS using Groth16 over BN254
    // (https://docs.circom.io/getting-started/proving-circuits/)
    let circom_vkey: CircomVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
    let circom_proof: CircomProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
    let circom_public = CircomPublic {
        values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
    };

    // we build a groth16 proof from the circom material collected from SnarkJS
    let proof = Groth16Proof::from_circom(circom_vkey, circom_proof, circom_public).unwrap();

    // groth16 proof verification
    proof.verify().unwrap();
    println!("Verified the Groth16 proof from Circom");
    Ok(())
    // -------------------------------------------------------------
}
