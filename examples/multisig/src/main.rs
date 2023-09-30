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

use risc0_zkvm::{
    default_prover,
    serde::{from_slice, to_vec},
    sha::Digest,
    ExecutorEnv, Receipt,
};
use multisig_methods::{ZK_MULTISIG_ID, ZK_MULTISIG_ELF};

fn is_multisig_quorum_satisfied(signature_one: &str, signature_two: &str, merkle_proof_one: &str, merkle_proof_two: &str, transaction_hash: &str, all_leaves: &str) -> (Digest, Receipt) { 
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(signature_one).unwrap())
        .add_input(&to_vec(signature_two).unwrap())
        .add_input(&to_vec(merkle_proof_one).unwrap())
        .add_input(&to_vec(merkle_proof_two).unwrap())
        .add_input(&to_vec(transaction_hash).unwrap())
        .add_input(&to_vec(all_leaves).unwrap())
        .build()
        .unwrap();

    let prover = default_prover();

    let receipt = prover.prove_elf(env, ZK_MULTISIG_ELF).unwrap();

    let digest = from_slice::<Vec<u8>, _>(&receipt.journal)
        .unwrap()
        .try_into()
        .unwrap();
    (digest, receipt)
}

const MAX_ARGS: usize = 7;

fn main() {
    let args: Vec<_> = std::env::args().collect();
    if args.len() == MAX_ARGS {
        let signature_one = &args[1]; // offset 1
        let signature_two = &args[2];
        let merkle_proof_one = &args[3];
        let merkle_proof_two = &args[4];
        let signed_message = &args[5];
        let all_leaves = &args[6];

        // Prove that the 'message' was signed by 2 unique signatories in the multisig scheme.
        let (digest, receipt) = is_multisig_quorum_satisfied(signature_one, signature_two, merkle_proof_one, merkle_proof_two, signed_message, all_leaves);
    
        // Verify the receipt, ensuring the prover supplied the correct arguments to satisfy the multisig.
        receipt
            .verify(ZK_MULTISIG_ID)
            .expect("receipt verification failed");
    
        println!("The data that Keccak256 hashes to {} was signed by 2 unique members of the multisig.", digest);
    } else {
        eprintln!("Wrong number of arguments provided. Please enter 6 arguments: <signature_one> <signature_two> <merkle_proof_one> <merkle_proof_two> <signed_message> <all_merkle_leaves>");
    }
}

#[cfg(test)]
mod tests {
    use multisig_methods::{ZK_MULTISIG_ID};

    #[test]
    fn verify_multisig() {
        let signature_one = "b3828c6eff4f8e90296b6ca2844534269c74643dd4b2dc3b628b5f3b8efab20f6e6542ba028d31a1a5cd55c8d1ebeda7efe010c1091f2034fee01327be94855a0";
        let signature_two = "55ee88d8a8d8b9263b429fedec257e65a29268e99e3d3cbf423db1e7c100779c5900dae93a0979c4172b2c262b553e8aa11908f744315ca3782bca86235a6fbc1";
        let merkle_proof_one = "e4083e5df4eef0b44a0e9d561ba9bd2ad76a2be3d021b7f2f3725e525352e988f6884e6b2078e95a3142df3d428978ecc0a4142facc5fb5e902933fe3a3b6e327f24885f6fad72d78165a75c88f961258d1b0f51910c1719dd8d6bac27a438cf0";
        let merkle_proof_two = "65be2cac622d5019dc04889aec418a2e9c724c456e91e43835b116350a72a42efa15a8b74d6795f59cf6fe1e3e2a1fc78c7ed024aae23976503aa4f2d4f7dc0d7f24885f6fad72d78165a75c88f961258d1b0f51910c1719dd8d6bac27a438cf3";
        let transaction_data = "{\"this\": \"would\", \"contain\": \"transaction\", \"data\": \"in\", \"practice\": \"maybe\", \"an\": \"erc4337\", \"user\": \"operation\"}";
        let all_leaves = "2ded6691f90f8ee99fd9bd72d39b35fd829d8c6654cda03ec709a02674aa334ae4083e5df4eef0b44a0e9d561ba9bd2ad76a2be3d021b7f2f3725e525352e98865be2cac622d5019dc04889aec418a2e9c724c456e91e43835b116350a72a42e1b5810aeb251583acc192df9638a3204798fb95126e91185a39c36728b83eb2cc5304c10ee245490ee283ebc082cbcfaad838858f4b2e24150c927ff475a2f0b4b53708aa80dacfc89b939d2944e42a2561515c58a995f255ba80844afb93fd8";
        let (digest, receipt) = super::is_multisig_quorum_satisfied(signature_one, signature_two, merkle_proof_one, merkle_proof_two, transaction_data, all_leaves);
        receipt.verify(ZK_MULTISIG_ID).unwrap();
        assert_eq!(
            hex::encode(digest.as_bytes()),
            "6f1237d5c028319a116a3f3cf774b9f64c6fee243432653132547c3c87e7c485",
            "The hash should match the Keccak256 hash of the transactions data to be approved."
        );
    }
}
