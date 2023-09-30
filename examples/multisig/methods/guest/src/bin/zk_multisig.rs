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

#![no_main]

use hex::FromHex;
use k256::ecdsa::{RecoveryId, Signature, VerifyingKey};
use risc0_zkvm::{
    guest::env
};
use rs_merkle::{algorithms::Sha256, Hasher, MerkleProof, MerkleTree};
use sha3::{Keccak256, Digest};

risc0_zkvm::guest::entry!(main);

const TRUSTED_MERKLE_ROOT: &str =
    "1962fbc17a4440d383f544724e9a943773c0cc6eade89b66b724c31cf33d3f62";

pub fn main() {
    let signature_one_input: String = env::read(); // <ecdsa_sig_address_one + recovery_id>
    let signature_two_input: String = env::read(); // <ecdsa_sig_address_two + recovery_id>
    let merkle_proof_one_input: String = env::read(); // <proof_hashes + index_of_leaf>
    let merkle_proof_two_input: String = env::read(); // <proof_hashes + index_of_leaf>
    let signed_message_input: String = env::read(); // <signed_message>
    let all_leaves_input: String = env::read(); // <merkle_leaves>

    let all_leaves_bytes = Vec::<u8>::from_hex(all_leaves_input.trim()).expect("Failed to decode hex string");

    let leaves: Vec<[u8; 32]> = all_leaves_bytes.chunks_exact(32)
    .map(|chunk| {
        let array: [u8; 32] = chunk.try_into().expect("Failed to convert chunk to array");
        array
    })
    .collect();

    let merkle_tree = MerkleTree::<Sha256>::from_leaves(&leaves);
    let new_root_hex = merkle_tree
        .root_hex()
        .ok_or("couldn't get the merkle root")
        .unwrap();
    let new_root = merkle_tree.root().ok_or("couldn't get the merkle root");
    let root_hash = match new_root {
        Ok(hash) => hash,
        Err(err) => {
            println!("Error: {:?}", err);
            return;
        }
    };
    let merkle_root_log_message = "Merkle Root: ".to_owned() + &new_root_hex;
    env::log(&merkle_root_log_message);

    if !new_root_hex.eq(TRUSTED_MERKLE_ROOT) {
        let error_message =
            "Error, merkle root hash is incorrect. Expected".to_owned() + &TRUSTED_MERKLE_ROOT;
        env::log(&error_message);
        return;
    }

    if merkle_proof_one_input.eq(&merkle_proof_two_input) {
        let error_message = "Error, merkle proofs cannot be the same!";
        env::log(&error_message);
        return;
    }

    /*
     * Checking that the first merkle proof is valid
     */
    let merkle_proof_one_index = merkle_proof_one_input.chars().last().unwrap();
    let merkle_proof_one_index_str = merkle_proof_one_index.to_string();
    let merkle_proof_one_index_value = merkle_proof_one_index_str.parse::<u32>().unwrap() as usize;

    let sanitized_merke_proof_one = &merkle_proof_one_input[..merkle_proof_one_input.len() - 1];
    let merkle_proof_one_index_log_message =
        "Merkle Proof One Index: ".to_owned() + &merkle_proof_one_index_str;
    env::log(&merkle_proof_one_index_log_message);


    let indices_to_prove = vec![merkle_proof_one_index_value];
    let start_range = merkle_proof_one_index_value as usize;
    let end_range = (merkle_proof_one_index_value + 1) as usize;
    let leaves_to_prove = leaves
        .get(start_range..end_range)
        .ok_or("can't get leaves to prove");
    let leaves_to_prove_result = match leaves_to_prove {
        Ok(leaves) => leaves,
        Err(err) => {
            println!("Error: {:?}", err);
            return;
        }
    };

    let merkle_proof_one_result = match hex::decode(sanitized_merke_proof_one) {
        Ok(bytes) => {
            let test_proof_slice: &[u8] = bytes.as_slice();

            let test_proof = MerkleProof::<Sha256>::try_from(test_proof_slice);
            match test_proof {
                Ok(proof) => {
                    let res = proof.verify(
                        root_hash,
                        &indices_to_prove,
                        leaves_to_prove_result,
                        leaves.len(),
                    );
                    let res_str = res.to_string();
                    let mp_one_log_msg = "Verify Merkle Proof One Result: ".to_owned() + &res_str;
                    env::log(&mp_one_log_msg);
                    res
                }
                Err(err) => {
                    println!("Failed to verify proof: {}", err);
                    false
                }
            }
        }
        Err(err) => {
            println!("Failed to decode hex: {}", err);
            false
        }
    };

    /*
     * Checking that the second merkle proof is valid
     */
    let merkle_proof_two_index = merkle_proof_two_input.chars().last().unwrap();
    let merkle_proof_two_index_str = merkle_proof_two_index.to_string();
    let merkle_proof_two_index_value = merkle_proof_two_index_str.parse::<u32>().unwrap() as usize;

    let sanitized_merke_proof_two = &merkle_proof_two_input[..merkle_proof_two_input.len() - 1];
    let merkle_proof_two_index_log_message =
        "Merkle Proof Two Index: ".to_owned() + &merkle_proof_two_index_str;
    env::log(&merkle_proof_two_index_log_message);

    let indices_to_prove_mp_two = vec![merkle_proof_two_index_value];
    let start_range_mp_two = merkle_proof_two_index_value as usize;
    let end_range_mp_two = (merkle_proof_two_index_value + 1) as usize;
    let leaves_to_prove_mp_two = leaves
        .get(start_range_mp_two..end_range_mp_two)
        .ok_or("can't get leaves to prove");
    let leaves_to_prove_result_mp_two = match leaves_to_prove_mp_two {
        Ok(leaves) => leaves,
        Err(err) => {
            println!("Error: {:?}", err);
            return;
        }
    };

    let merkle_proof_two_result = match hex::decode(sanitized_merke_proof_two) {
        Ok(bytes) => {
            let test_proof_slice: &[u8] = bytes.as_slice();

            let test_proof = MerkleProof::<Sha256>::try_from(test_proof_slice);
            match test_proof {
                Ok(proof) => {
                    let res = proof.verify(
                        root_hash,
                        &indices_to_prove_mp_two,
                        leaves_to_prove_result_mp_two,
                        leaves.len(),
                    );
                    let res_str = res.to_string();
                    let mp_two_log_msg = "Verify Merkle Proof Two Result: ".to_owned() + &res_str;
                    env::log(&mp_two_log_msg);
                    res
                }
                Err(err) => {
                    println!("Failed to verify proof: {}", err);
                    false
                }
            }
        }
        Err(err) => {
            println!("Failed to decode hex: {}", err);
            false
        }
    };

    /*
     * Ensure both merkle proofs passed before progressing
     */
    if !merkle_proof_one_result {
        let log_msg = "❌ Merkle Proof One Failed: ".to_owned() + &merkle_proof_one_input;
        env::log(&log_msg);
        return;
    }

    if !merkle_proof_two_result {
        let log_msg = "❌ Merkle Proof Two Failed: ".to_owned() + &merkle_proof_two_input;
        env::log(&log_msg);
        return;
    }

    let signed_message = Keccak256::new_with_prefix(signed_message_input);

    /*
     * Recover address of first signature hash it and check if it's in the tree - use the index from the merkle proof to do this
     */
    let sig_one_rec_id_input = signature_one_input.chars().last().unwrap();
    let sig_one_rec_id_str = sig_one_rec_id_input.to_string();
    let sig_one_rec_id = sig_one_rec_id_str.parse::<u32>().unwrap() as u8;
    let sanitized_signature_one_input = &signature_one_input[..signature_one_input.len() - 1];

    let signature_one_bytes = hex::decode(sanitized_signature_one_input).expect("Invalid hex string");
    let signature = Signature::try_from(signature_one_bytes.as_slice());

    let signature_res = match signature {
        Ok(value) => value,
        Err(e) => {
            println!("❌ Failed to get signature: {:?}", e);
            return;
        }
    };

    let recid = RecoveryId::try_from(sig_one_rec_id);
    let recid_res = match recid {
        Ok(value) => value,
        Err(e) => {
            println!("❌ Failed to get RecoveryId: {:?}", e);
            return;
        }
    };

    
    let recovered_key = VerifyingKey::recover_from_digest(
        signed_message.clone(),
        &signature_res,
        recid_res,
    );


    let recovered_key_res = match recovered_key {
        Ok(value) => value,
        Err(e) => {
            println!("❌ Failed to get RecoveredKey: {:?}", e);
            return;
        }
    };


    let encoded_point_pub_key_one = recovered_key_res.to_encoded_point(false);
    let encoded_point_pub_key_one_hex = encoded_point_pub_key_one.to_string().to_lowercase();
    // let log_public_key_one = "Recovered Public Key One: ".to_owned() + &encoded_point_pub_key_one_hex;
    // env::log(&log_public_key_one);

    let pubic_key_one_hash = Sha256::hash(encoded_point_pub_key_one_hex.as_bytes());
    let pubic_key_one_hash_hex = hex::encode(pubic_key_one_hash);
    let log_public_key_hash_one = "Recovered Public Key Hash One: ".to_owned() + &pubic_key_one_hash_hex;
    env::log(&log_public_key_hash_one);

    let actual_leaf_one = hex::encode(leaves[merkle_proof_one_index_value]);
    if  actual_leaf_one != pubic_key_one_hash_hex {
        let log_msg = "❌ Recovered public key from signature_one is not a signatory: ".to_owned() + &encoded_point_pub_key_one_hex;
        env::log(&log_msg);
        return;
    } else {
        let log_msg = "🎉 Recovered public key is a signatory: ".to_owned() + &encoded_point_pub_key_one_hex;
        env::log(&log_msg);
    }

    /*
     * Recover address of second signature hash it and check if it's in the tree - use the index from the merkle proof to do this
     */
     let sig_two_rec_id_input = signature_two_input.chars().last().unwrap();
     let sig_two_rec_id_str = sig_two_rec_id_input.to_string();
     let sig_two_rec_id = sig_two_rec_id_str.parse::<u32>().unwrap() as u8;
     let sanitized_signature_two_input = &signature_two_input[..signature_two_input.len() - 1];
 
     let signature_two_bytes = hex::decode(sanitized_signature_two_input).expect("Invalid hex string");
     let signature = Signature::try_from(signature_two_bytes.as_slice());
 
     let signature_res = match signature {
         Ok(value) => value,
         Err(e) => {
             println!("❌ Failed to get signature: {:?}", e);
             return;
         }
     };
 
     let recid = RecoveryId::try_from(sig_two_rec_id);
     let recid_res = match recid {
         Ok(value) => value,
         Err(e) => {
             println!("❌ Failed to get RecoveryId: {:?}", e);
             return;
         }
     };
     
     let recovered_key = VerifyingKey::recover_from_digest(
         signed_message.clone(),
         &signature_res,
         recid_res,
     );
 
 
     let recovered_key_res = match recovered_key {
         Ok(value) => value,
         Err(e) => {
             println!("❌ Failed to get RecoveredKey: {:?}", e);
             return;
         }
     };
 
     let encoded_point_pub_key_two = recovered_key_res.to_encoded_point(false);
     let encoded_point_pub_key_two_hex = encoded_point_pub_key_two.to_string().to_lowercase();
 
     let pubic_key_two_hash = Sha256::hash(encoded_point_pub_key_two_hex.as_bytes());
     let pubic_key_two_hash_hex = hex::encode(pubic_key_two_hash);
     let log_public_key_hash_two = "Recovered Public Key Hash Two: ".to_owned() + &pubic_key_two_hash_hex;
     env::log(&log_public_key_hash_two);

     let actual_leaf_two = hex::encode(leaves[merkle_proof_two_index_value]);
     if  actual_leaf_two != pubic_key_two_hash_hex {
         let log_msg = "❌ Recovered public key from signature_two is not a signatory: ".to_owned() + &encoded_point_pub_key_two_hex;
         env::log(&log_msg);
         return;
     } else {
        let log_msg = "🎉 Recovered public key is a signatory: ".to_owned() + &encoded_point_pub_key_one_hex;
        env::log(&log_msg);
    }

    /*
     * Check that both recovered keys are not the same
     */
     if pubic_key_one_hash_hex == pubic_key_two_hash_hex {
        let log_msg = "Cannot provide two signatures from the same signatory: ".to_owned() + &pubic_key_one_hash_hex;
        env::log(&log_msg);
        return;
     } else {
        let log_msg = "\n\n🎉 Congratulations, you've satisfied the multisig quorum. Now generating proof... 🎉\n ".to_owned();
        env::log(&log_msg);
     }


    let final_hash = signed_message.finalize();
    let final_hash_bytes = final_hash.as_slice();
    let message_bytes = hex::encode(final_hash_bytes); 
    let commit_log_msg = "\n\nCommiting to hash: ".to_owned() + &message_bytes;
    env::log(&commit_log_msg);
    env::commit(&final_hash_bytes);
}
