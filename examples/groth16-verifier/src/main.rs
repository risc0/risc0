use bonsai_groth16::{
    raw::{RawProof, RawPublic, RawVKey},
    Digest, Groth16,
};
use bonsai_sdk::alpha::responses::SnarkReceipt;
use methods::{GROTH16_VERIFIER_ELF, GROTH16_VERIFIER_ID};
use risc0_zkvm::{default_prover, ExecutorEnv};

const CIRCOM_VERIFICATION_KEY: &str = include_str!("data/circom/verification_key.json");
const CIRCOM_PROOF: &str = include_str!("data/circom/proof.json");
const CIRCOM_PUBLIC: &str = include_str!("data/circom/public.json");

fn main() {
    // ----- Snark receipt verification from Bonsai --------
    //
    // SnarkReceipt as received from Bonsai
    let snark_receipt_json = r#"
    {
        "snark":{
            "a":[[26,63,155,211,133,192,185,234,51,172,152,49,113,248,13,45,155,140,75,98,171,225,72,44,133,246,88,199,37,103,28,56],
                [22,46,102,79,175,35,89,153,55,78,200,143,26,196,209,62,247,200,136,247,101,65,101,157,59,33,20,91,191,43,246,84]],
            "b":[[[20,0,192,47,211,1,254,55,118,229,52,232,89,161,51,100,224,242,246,5,106,190,188,113,187,230,100,7,255,70,192,153],
                [9,206,194,232,36,249,103,125,57,1,189,209,245,133,230,79,219,98,176,253,221,160,20,78,189,142,46,52,171,1,162,203]],
                [[32,70,252,38,183,118,240,156,230,16,28,10,122,111,184,65,239,158,193,102,94,156,5,56,24,236,174,103,160,172,89,109],
                [4,151,70,37,225,160,65,7,230,206,172,247,41,192,58,149,244,201,31,171,7,137,232,107,29,143,227,49,96,29,198,35]]],
            "c":[[20,112,216,216,113,186,224,139,117,16,31,102,238,29,76,150,58,216,254,75,147,172,89,147,216,138,41,130,172,106,148,8],
                [23,250,144,90,188,98,158,62,214,76,108,236,158,31,125,183,20,200,101,254,212,15,32,174,120,230,219,15,71,206,189,55]],
            "public":[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,104,228,45,139,61,220,73,159,78,23,153,167,103,5,42,179],
                [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,56,2,104,79,22,69,224,160,40,88,91,4,69,211,146,49],
                [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,207,29,214,20,178,62,196,218,167,244,197,95,239,64,43,255],
                [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,86,246,102,224,24,131,128,68,162,253,108,219,190,247,101,102]]
        },
        "receipt_meta_digest":[255,43,64,239,95,197,244,167,218,196,62,178,20,214,29,207,102,101,247,190,219,108,253,162,68,128,131,24,224,102,246,86],
        "journal":[1,0,0,0]
    }
    "#;
    let snark_receipt: SnarkReceipt = serde_json::from_str(snark_receipt_json).unwrap();

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
    // Note: this step produces around 160 segments, thus proving without
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
    assert_eq!(journal_output, groth16.digest())
    // -------------------------------------------------------------
}
