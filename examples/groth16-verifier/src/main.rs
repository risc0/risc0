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

use crate::bonsai_sdk::responses::SnarkReceipt;
use anyhow::Result;
use bonsai_groth16_verifier::{
    raw::{RawProof, RawPublic, RawVKey},
    Digest, Groth16,
};
use bonsai_sdk::alpha as bonsai_sdk;
use groth16_verifier_example::*;
use methods::{GROTH16_VERIFIER_ELF, GROTH16_VERIFIER_ID};
use risc0_zkvm::{default_prover, ExecutorEnv};

const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

fn main() -> Result<()> {
    // ----- Snark receipt verification from Bonsai --------
    //
    // Generate a snark receipt for the hello-world example
    let snark_receipt: SnarkReceipt = match dev_mode()? {
        true => run_bonsai_mock(),
        false => run_bonsai(u64s_to_vec(17, 23))?,
    };

    // SnarkReceipt verification
    snark_receipt
        .verify()
        .expect("Failed snark receipt verification");
    println!("Verified the snark receipt from Bonsai");
    // -------------------------------------------------------------

    // ----- Groth16 proof verification from Circom/SnarkJS --------
    //
    // verification_key, proof and public witness generated with SnarkJS using Groth16 over BN254
    // (https://docs.circom.io/getting-started/proving-circuits/)
    let raw_vkey: RawVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
    let raw_proof: RawProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
    let raw_public = RawPublic {
        values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
    };

    // we build a groth16 instance from the raw material collected from SnarkJS
    let groth16 = Groth16::from_raw(raw_vkey, raw_proof, raw_public).unwrap();

    // groth16 proof verification
    groth16.verify().unwrap();
    println!("Verified the Groth16 proof from Circom");
    // -------------------------------------------------------------

    // ----- zkVM Groth16 proof verification from Circom/SnarkJS --------
    //
    // we build an ExecutorEnv using as input the previous groth16 instance
    let env = ExecutorEnv::builder()
        .write(&groth16)
        .unwrap()
        .build()
        .unwrap();

    // we run the prover to obtain a receipt of the zkVM groth16 verifier
    //
    // Note: this step requires around 150 milion cycles, thus proving without
    // using Bonsai or CUDA acceleration can slow. We recommend enabling
    // dev mode by setting the env variable `RISC0_DEV_MODE=true`
    println!(
        "Proving the Groth16 proof verification (input digest: {})",
        hex::encode(groth16.digest())
    );
    let receipt = default_prover()
        .prove_elf(env, GROTH16_VERIFIER_ELF)
        .unwrap();

    // We verify the receipt and make sure the output of the journal is
    // equal to the digest of our input
    receipt.verify(GROTH16_VERIFIER_ID).unwrap();
    let journal_output: Digest = receipt.journal.decode().unwrap();
    println!(
        "Verified the Groth16 zkVM verification (output digest: {})",
        hex::encode(journal_output)
    );
    assert_eq!(journal_output, groth16.digest());
    Ok(())
    // -------------------------------------------------------------
}
