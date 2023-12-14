// use hex::FromHex;
use halo2_core::VerifierComponents;
use methods::{COMPOSITION_ELF, COMPOSITION_ID, GROTH16_ELF, GROTH16_ID};
use methods::{VERIFIER_ELF, VERIFIER_ID};
use risc0_groth16::{
    raw::{RawProof, RawPublic, RawVKey},
    Groth16,
};
use risc0_zkvm::{default_prover, ExecutorEnv};
use rmp_serde;
use std::fs::File;
use std::io::Read;

const PATH: &str = "res/verification.components";
const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

fn main() {
    // verification_key, proof and public witness generated with snarkjs using Groth16 over BN254
    // (https://docs.circom.io/getting-started/proving-circuits/)
    let raw_vkey: RawVKey = serde_json::from_str(CIRCOM_VERIFICATION_KEY).unwrap();
    let raw_proof: RawProof = serde_json::from_str(CIRCOM_PROOF).unwrap();
    let raw_public = RawPublic {
        values: serde_json::from_str(CIRCOM_PUBLIC).unwrap(),
    };

    let groth16 = Groth16::from_raw(raw_vkey, raw_proof, raw_public).unwrap();
    groth16.verify().unwrap();

    let env = ExecutorEnv::builder()
        .write(&groth16)
        .unwrap()
        .build()
        .unwrap();

    let receipt = default_prover().prove_elf(env, GROTH16_ELF).unwrap();

    receipt.verify(GROTH16_ID).unwrap();

    // import the Halo2 verifier components
    let verifier_components = import_halo2_file(PATH);

    let params_len = verifier_components.v_params.len();
    let vk_len = verifier_components.vk.len();
    let proof_len = verifier_components.proof.len();

    // send the components to the guest
    let env = ExecutorEnv::builder()
        .write(&params_len)
        .unwrap()
        .write(&vk_len)
        .unwrap()
        .write(&proof_len)
        .unwrap()
        .write_slice(&verifier_components.v_params)
        .write_slice(&verifier_components.vk)
        .write_slice(&verifier_components.proof)
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt_halo2 = prover.prove_elf(env, VERIFIER_ELF).unwrap();

    let env = ExecutorEnv::builder()
        .write(&GROTH16_ID)
        .unwrap()
        .write(&receipt.journal.bytes)
        .unwrap()
        .write(&VERIFIER_ID)
        .unwrap()
        .write(&receipt_halo2.journal.bytes)
        .unwrap()
        .add_assumption(receipt.into())
        .add_assumption(receipt_halo2.into())
        .build()
        .unwrap();

    let receipt = default_prover().prove_elf(env, COMPOSITION_ELF).unwrap();
    receipt.verify(COMPOSITION_ID).unwrap();
}

fn import_halo2_file(path: &str) -> VerifierComponents {
    let mut f1 = File::open(path).expect("No file found");
    let mut verification_buffer = Vec::new();
    f1.read_to_end(&mut verification_buffer)
        .expect("unable to read data");
    let deserialized_struct: VerifierComponents =
        rmp_serde::from_slice(&verification_buffer).unwrap();
    deserialized_struct
}
