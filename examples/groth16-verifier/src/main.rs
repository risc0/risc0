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

use methods::{GROTH16_VERIFIER_ELF, GROTH16_VERIFIER_ID};
use risc0_groth16::{
    circom::{CircomProof, CircomPublic, CircomVKey},
    Groth16,
};
use risc0_zkvm::{default_prover, ExecutorEnv};

const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

fn main() {
    // verification_key, proof and public witness generated with circom and snarkjs using Groth16 over BN254
    // (https://docs.circom.io/getting-started/proving-circuits/)
    let circom_vkey: CircomVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
    let circom_proof: CircomProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
    let circom_public = CircomPublic {
        values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
    };

    // we parse a groth16 proof from the circom material collected from SnarkJS
    let groth16_proof = Groth16::from_circom(circom_vkey, circom_proof, circom_public).unwrap();

    // groth16 proof verification
    groth16_proof.verify().unwrap();

    // we configure an Executor with the groth16 proof
    let env = ExecutorEnv::builder()
        .write(&groth16_proof)
        .unwrap()
        .build()
        .unwrap();

    // we run the prover to generate a receipt of correct verification
    let receipt = default_prover().prove(env, GROTH16_VERIFIER_ELF).unwrap();

    // we verify the final receipt
    receipt.verify(GROTH16_VERIFIER_ID).unwrap();

    // we compare the committed hash to the original proof
    let output_digest: [u8; 32] = receipt.journal.decode().unwrap();
    assert_eq!(output_digest, groth16_proof.digest());

    println!("Verification: OK!");
}
