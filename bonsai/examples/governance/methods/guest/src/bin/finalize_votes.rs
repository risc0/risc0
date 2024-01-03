// Copyright 2024 RISC Zero, Inc.
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

use std::{collections::BTreeMap, io::Read};

use k256::{
    ecdsa::{RecoveryId, Signature, VerifyingKey},
    elliptic_curve::sec1::ToEncodedPoint,
    PublicKey,
};
use risc0_zkvm::{
    guest::env,
    sha::rust_crypto::{Digest as _, Sha256},
};
use tiny_keccak::{Hasher, Keccak};

const ENCODED_INPUT_CHUNK_SIZE: usize = 100;

fn keccak256(bytes: &[u8]) -> [u8; 32] {
    let mut digest = [0u8; 32];
    let mut hasher = Keccak::v256();
    hasher.update(bytes);
    hasher.finalize(&mut digest);
    digest
}

/// Assert that the given bytes are zeroes.
/// `offset` is used only for inclusion in an error message on panic.
fn assert_zero(bytes: &[u8], offset: usize) {
    for (i, byte) in bytes.iter().copied().enumerate() {
        assert_eq!(
            byte,
            0u8,
            "expected byte to be zero at offset {}",
            offset + i
        );
    }
}

/// Converts an Ethereum-convention recovery ID to the k256 RecoveryId type.
fn into_recovery_id(v: u8) -> Option<RecoveryId> {
    match v {
        0 => Some(0),
        1 => Some(1),
        27 => Some(0),
        28 => Some(1),
        v if v >= 35 => Some((v - 1) % 2),
        _ => None,
    }
    .and_then(RecoveryId::from_byte)
}

/// Signer address recovery from the (v, r, s) signature components.
///
/// This methods exists to replicate the behavior of `ecrecover` within the EVM.
/// It can only be considered a signature validation is digest is verified to be
/// the hash of a known message.
fn ecrecover(v: u8, rs: [u8; 64], digest: [u8; 32]) -> [u8; 20] {
    let recovery_id = into_recovery_id(v).expect("value for v is invalid");
    let signature = Signature::from_slice(&rs[..]).expect("signature encoding is invalid");
    let recovered_pk: PublicKey =
        VerifyingKey::recover_from_prehash(&digest[..], &signature, recovery_id)
            .expect("signature is invalid")
            .into();

    // Calculate the Ethereum address from the k256 public key.
    let encoded_pk = recovered_pk.to_encoded_point(/* compress = */ false);
    keccak256(&encoded_pk.as_bytes()[1..])[12..]
        .try_into()
        .unwrap()
}

fn main() {
    // Read data sent from the application contract.
    let mut input_bytes = Vec::<u8>::new();
    env::stdin().read_to_end(&mut input_bytes).unwrap();

    // Input starts with a 32-byte proposal ID is then a packed encoding of 100-byte
    // chunks of the form:
    // When signed == true:
    //  u16(support) u8(signed) u8(v) [u8; 32](r) [u8; 32](s) [u8; 32](digest)
    // When signed == false:
    //  u16(support) u8(signed) u8(v) [u8; 20](voter) [u8; 76](0)
    let proposal_id: [u8; 32] = input_bytes[..32].try_into().unwrap();
    let chunks = input_bytes[32..].chunks_exact(ENCODED_INPUT_CHUNK_SIZE);
    assert_eq!(
        chunks.remainder().len(),
        0,
        "input bytes must be a multiple of 100 bytes: {}",
        input_bytes.len()
    );

    // Iterate through the 100-byte chunks, decoding each and reconstructing the
    // ballot box hash accumulator value, and adding the votes to a map of votes.
    let mut ballot_box_accum = proposal_id;
    let mut hasher = Sha256::new();
    let mut votes = BTreeMap::<[u8; 20], u8>::new();
    for (offset, chunk) in chunks
        .enumerate()
        .map(|(i, chunk)| (i * ENCODED_INPUT_CHUNK_SIZE, chunk))
    {
        assert_zero(&chunk[0..1], offset);
        let signed: u8 = chunk[1];
        let support: u8 = chunk[2];
        let voter: [u8; 20] = match signed {
            0 => {
                assert_zero(&chunk[3..4], offset);
                assert_zero(&chunk[24..], offset + 24);

                hasher.update(&ballot_box_accum[..]);
                hasher.update(&chunk[..24]);
                hasher.finalize_into_reset((&mut ballot_box_accum).into());

                chunk[4..24].try_into().unwrap()
            }
            1 => {
                let v: u8 = chunk[3];
                let rs: [u8; 64] = chunk[4..68].try_into().unwrap();
                let sig_digest: [u8; 32] = chunk[68..100].try_into().unwrap();

                hasher.update(&ballot_box_accum[..]);
                hasher.update(chunk);
                hasher.finalize_into_reset((&mut ballot_box_accum).into());

                ecrecover(v, rs, sig_digest)
            }
            _ => panic!("value of signed is invalid: {}", signed),
        };
        // Add the vote to the map of votes, possibly replacing an existing vote.
        votes.insert(voter, support);
    }

    // Commit the proposal ID, ballot box hash, and 24-byte encoded ballots to the
    // journal.
    // NOTE: Padding bytes are inserted to maintain u32 word alignment. It is not
    // well-established that this actually results in a more efficient program,
    // so this needs to be tested.
    env::commit_slice(&proposal_id[..]);
    env::commit_slice(&ballot_box_accum[..]);
    for (voter, support) in votes.iter() {
        env::commit_slice(&u32::from(*support).to_be_bytes()[..]);
        env::commit_slice(&voter[..]);
    }
}
