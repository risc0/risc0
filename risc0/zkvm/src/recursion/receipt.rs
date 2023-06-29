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

use alloc::{collections::VecDeque, vec::Vec};

use dyn_partial_eq::DynPartialEq;
#[cfg(not(target_os = "zkvm"))]
use risc0_zkp::{adapter::CircuitInfo, core::hash::sha::Sha256};
use risc0_zkp::{core::digest::Digest, verify::VerificationError};
use serde::{Deserialize, Serialize};

use crate::{
    receipt::{ReceiptMetadata, SegmentReceipt, SystemState},
    ControlId,
};
#[cfg(not(target_os = "zkvm"))]
use crate::{
    recursion::circuit_impl::CIRCUIT_CORE,
    sha::{self},
};

/// This function gets valid control ID's from the posidon and recursion
/// circuits
pub fn valid_control_ids() -> Vec<Digest> {
    use hex::FromHex;
    use risc0_zkp::core::hash::poseidon::PoseidonHashFn;
    let mut all_ids = Vec::<Digest>::new();
    for digest_str in PoseidonHashFn::CONTROL_ID {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    for digest_str in crate::recursion::control_id::RECURSION_CONTROL_IDS {
        all_ids.push(Digest::from_hex(digest_str).unwrap());
    }
    all_ids
}

#[cfg(not(target_os = "zkvm"))]
fn tagged_struct(tag: &str, down: &[Digest], data: &[u32]) -> Digest {
    let tag_digest: Digest = *sha::Impl::hash_bytes(tag.as_bytes());
    let mut all = Vec::<u8>::new();
    all.extend_from_slice(tag_digest.as_bytes());
    for digest in down {
        all.extend_from_slice((*digest).as_bytes());
    }
    for word in data {
        all.extend_from_slice(&(*word).to_le_bytes());
    }
    let down_count: u16 = down.len().try_into().unwrap();
    all.extend_from_slice(&down_count.to_le_bytes());
    *sha::Impl::hash_bytes(&all)
}

fn read_sha_halfs(flat: &mut VecDeque<u32>) -> Digest {
    let mut bytes = Vec::<u8>::new();
    for half in flat.drain(0..16) {
        bytes.push((half & 0xff).try_into().unwrap());
        bytes.push((half >> 8).try_into().unwrap());
    }
    bytes.try_into().unwrap()
}

fn read_u32_bytes(flat: &mut VecDeque<u32>) -> u32 {
    u32::from_le_bytes(
        flat.drain(0..4)
            .map(|x| x as u8)
            .collect::<Vec<u8>>()
            .try_into()
            .unwrap(),
    )
}

fn write_sha_halfs(flat: &mut Vec<u32>, digest: &Digest) {
    for x in digest.as_words() {
        flat.push(*x & 0xffff);
        flat.push(*x >> 16);
    }
}

fn write_u32_bytes(flat: &mut Vec<u32>, word: u32) {
    for x in word.to_le_bytes() {
        flat.push(x as u32);
    }
}

impl SystemState {
    fn decode(flat: &mut VecDeque<u32>) -> Self {
        Self {
            pc: read_u32_bytes(flat),
            merkle_root: read_sha_halfs(flat),
        }
    }

    fn encode(&self, flat: &mut Vec<u32>) {
        write_u32_bytes(flat, self.pc);
        write_sha_halfs(flat, &self.merkle_root);
    }

    #[cfg(not(target_os = "zkvm"))]
    fn digest(&self) -> Digest {
        tagged_struct("risc0.SystemState", &[self.merkle_root], &[self.pc])
    }
}

impl ReceiptMetadata {
    /// decode a [crate::ReceiptMetadata] from a list of [u32]'s
    pub fn decode(flat: &mut VecDeque<u32>) -> Result<Self, VerificationError> {
        let input = read_sha_halfs(flat);
        let pre = SystemState::decode(flat);
        let post = SystemState::decode(flat);
        let sys_exit = flat.pop_front().unwrap() as u32;
        let user_exit = flat.pop_front().unwrap() as u32;
        let exit_code = ReceiptMetadata::make_exit_code(sys_exit, user_exit)?;
        let output = read_sha_halfs(flat);

        Ok(Self {
            input,
            pre,
            post,
            exit_code,
            output,
        })
    }
    /// encode a [crate::ReceiptMetadata] to a list of [u32]'s
    pub fn encode(&self, flat: &mut Vec<u32>) -> Result<(), VerificationError> {
        write_sha_halfs(flat, &self.input);
        self.pre.encode(flat);
        self.post.encode(flat);
        let (sys_exit, user_exit) = self.get_exit_code_pairs()?.clone();
        flat.push(sys_exit);
        flat.push(user_exit);
        write_sha_halfs(flat, &self.output);
        Ok(())
    }

    #[cfg(not(target_os = "zkvm"))]
    fn digest(&self) -> Result<Digest, VerificationError> {
        let (sys_exit, user_exit) = self.get_exit_code_pairs()?.clone();
        Ok(tagged_struct(
            "risc0.ReceiptMeta",
            &[
                self.input,
                self.pre.digest(),
                self.post.digest(),
                self.output,
            ],
            &[sys_exit, user_exit],
        ))
    }
}

/// This struct represents a receipt for one or more
/// [crate::SegmentBaseReceipt]s joined through recursion.
#[derive(Clone, Debug, Serialize, Deserialize, DynPartialEq, PartialEq)]
pub struct SegmentRecursionReceipt {
    /// the cryptographic seal of this receipt
    pub seal: Vec<u32>,
    /// the control ID of this receipt
    pub control_id: Digest,
    /// the receipt metadata containing states of the system during the segment
    /// executions
    pub meta: ReceiptMetadata,
}

#[typetag::serde]
impl SegmentReceipt for SegmentRecursionReceipt {
    /// verify the integrity of this receipt
    #[cfg(not(target_os = "zkvm"))]
    fn verify(&self, _hashfn_name: &String) -> Result<(), VerificationError> {
        use risc0_core::field::baby_bear::BabyBearElem;
        use risc0_zkp::core::hash::poseidon::PoseidonHashSuite;

        use super::CircuitImpl;

        // Make the hal
        let hal = risc0_zkp::verify::CpuVerifyHal::<_, PoseidonHashSuite, _>::new(&CIRCUIT_CORE);
        let valid_ids = valid_control_ids();
        let check_code = |_po2: u32, control_id: &Digest| -> Result<(), VerificationError> {
            let Some(_) = valid_ids.iter().position(|elem| elem == control_id) else {
                return Err(VerificationError::JournalDigestMismatch);
            };
            Ok(())
        };
        // Verify the receipt itself is correct
        risc0_zkp::verify::verify(&hal, &CIRCUIT_CORE, &self.seal, check_code)?;
        // Extract the globals from the seal
        let output_elems: &[BabyBearElem] =
            bytemuck::cast_slice(&self.seal[..CircuitImpl::OUTPUT_SIZE]);
        let mut seal_meta = VecDeque::<u32>::new();
        for elem in output_elems {
            seal_meta.push_back(elem.as_u32())
        }
        // TODO: Read root hash
        seal_meta.drain(0..16);
        // Verify the output hash matches that data
        let output_hash = read_sha_halfs(&mut seal_meta);
        if output_hash != self.meta.digest()? {
            return Err(VerificationError::JournalDigestMismatch);
        }
        // Everything passed
        Ok(())
    }

    fn get_metadata(&self) -> anyhow::Result<ReceiptMetadata, VerificationError> {
        Ok(self.meta.clone())
    }

    fn get_seal_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(self.seal.as_slice())
    }
}

/// A SessionRollupReceipt represents computational integrity for an entire
/// [crate::Session].
///
/// This represents the receipt for an entire session where each segment proof
/// has been rolled up using recursion.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct SessionRollupReceipt {
    /// receipt that represents all sessions joined via recursion
    pub receipt: SegmentRecursionReceipt,
    /// the journal of the entire session
    pub journal: Vec<u8>,
}

#[cfg(test)]
mod tests {
    use crate::recursion::receipt::tagged_struct;
    #[test]
    fn test_tagged_struct() {
        let digest1 = tagged_struct("foo", &[], &[1, 2013265920, 3]);
        let digest2 = tagged_struct("bar", &[digest1, digest1], &[2013265920, 5]);
        let digest3 = tagged_struct(
            "baz",
            &[digest1, digest2, digest1],
            &[6, 7, 2013265920, 9, 10],
        );

        println!("digest = {:?}", digest3);
    }
}
