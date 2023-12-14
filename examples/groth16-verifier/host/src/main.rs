use methods::{GROTH16_VERIFIER_ELF, GROTH16_VERIFIER_ID};
use risc0_groth16::{
    raw::{RawProof, RawPublic, RawVKey},
    Groth16,
};
use risc0_zkvm::{default_prover, ExecutorEnv};

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

    let receipt = default_prover()
        .prove_elf(env, GROTH16_VERIFIER_ELF)
        .unwrap();
    receipt.verify(GROTH16_VERIFIER_ID).unwrap();
}
