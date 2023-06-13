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

use risc0_zkp::core::digest::Digest;
#[cfg(not(target_os = "zkvm"))]
use risc0_zkp::core::hash::sha::Sha256;
#[cfg(not(target_os = "zkvm"))]
use risc0_zkp::{adapter::CircuitInfo, verify::VerificationError};
use serde::{Deserialize, Serialize};

#[cfg(not(target_os = "zkvm"))]
use crate::receipt::compute_image_id;
#[cfg(not(target_os = "zkvm"))]
use crate::recursion::circuit_impl::CIRCUIT_CORE;
#[cfg(not(target_os = "zkvm"))]
use crate::sha::{self};
use crate::{receipt::SessionReceipt, ControlId};

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

/// SystemState describes the system's memory during program execution
///
/// An instance of this struct provides a program counter and an image ID that
/// represents all values in memory at that moment.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct SystemState {
    /// the program counter
    pub pc: u32,
    /// the image ID represents a snapshot of all memory regions
    pub image_id: Digest,
}

/// The receipt metadata describes the system information about each receipt.
///
/// This information is used to verify the integrity of the receipt as well as
/// joining two receipts together using recursion.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ReceiptMeta {
    /// hash of the input to this segment before execution
    pub input: Digest,
    /// System State before the segment execution
    pub pre: SystemState,
    /// System State after the segment execution
    pub post: SystemState,
    /// The system's exit state at the end of this segment
    pub sys_exit: u8,
    /// The system's exit status derived from a sys_pause instruction at the end
    /// of this segment
    pub user_exit: u8,
    /// hash of the output
    pub output: Digest,
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
            image_id: read_sha_halfs(flat),
        }
    }

    fn encode(&self, flat: &mut Vec<u32>) {
        write_u32_bytes(flat, self.pc);
        write_sha_halfs(flat, &self.image_id);
    }

    #[cfg(not(target_os = "zkvm"))]
    fn digest(&self) -> Digest {
        tagged_struct("risc0.SystemState", &[self.image_id], &[self.pc])
    }
}

impl ReceiptMeta {
    /// decode a [ReceiptMeta] from a list of [u32]'s
    pub fn decode(flat: &mut VecDeque<u32>) -> Self {
        Self {
            input: read_sha_halfs(flat),
            pre: SystemState::decode(flat),
            post: SystemState::decode(flat),
            sys_exit: flat.pop_front().unwrap() as u8,
            user_exit: flat.pop_front().unwrap() as u8,
            output: read_sha_halfs(flat),
        }
    }
    /// encode a [ReceiptMeta] to a list of [u32]'s
    pub fn encode(&self, flat: &mut Vec<u32>) {
        write_sha_halfs(flat, &self.input);
        self.pre.encode(flat);
        self.post.encode(flat);
        flat.push(self.sys_exit as u32);
        flat.push(self.user_exit as u32);
        write_sha_halfs(flat, &self.output);
    }

    #[cfg(not(target_os = "zkvm"))]
    fn digest(&self) -> Digest {
        tagged_struct(
            "risc0.ReceiptMeta",
            &[
                self.input,
                self.pre.digest(),
                self.post.digest(),
                self.output,
            ],
            &[self.sys_exit.into(), self.user_exit.into()],
        )
    }
}

/// This struct represents a receipt for one or more [crate::SegmentReceipt]s
/// joined through recursion.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct SegmentRecursionReceipt {
    /// the cryptographic seal of this receipt
    pub seal: Vec<u32>,
    /// the control ID of this receipt
    pub control_id: Digest,
    /// the receipt metadata containing states of the system during the segment
    /// executions
    pub meta: ReceiptMeta,
}

impl SegmentRecursionReceipt {
    /// verify the integrity of this receipt
    #[cfg(not(target_os = "zkvm"))]
    pub fn verify(&self) -> Result<(), VerificationError> {
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
        if output_hash != self.meta.digest() {
            return Err(VerificationError::JournalDigestMismatch);
        }
        // Everything passed
        Ok(())
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

impl SessionReceipt for SessionRollupReceipt {
    /// Verify the integrity of the receipt by using the segment receipt and the
    /// journal
    #[cfg(not(target_os = "zkvm"))]
    fn verify(&self, image_id: Digest) -> Result<(), VerificationError> {
        self.receipt.verify()?;
        let journal_digest = sha::Impl::hash_bytes(&self.journal);
        let pre_img = &self.receipt.meta.pre;
        if image_id != compute_image_id(&pre_img.image_id, pre_img.pc) {
            return Err(VerificationError::ImageVerificationError);
        }

        if *journal_digest.as_ref() != self.receipt.meta.output {
            return Err(VerificationError::JournalDigestMismatch);
        }

        Ok(())
    }

    fn get_journal(&self) -> &Vec<u8> {
        &self.journal
    }

    fn encode(&self) -> Vec<u8> {
        bytemuck::cast_slice(crate::serde::to_vec(&self).unwrap().as_slice()).into()
    }

    fn get_seal_len(&self) -> usize {
        bytemuck::cast_slice::<u32, u8>(self.receipt.seal.as_slice()).len()
    }

    #[cfg(test)]
    fn as_any(&self) -> &dyn core::any::Any {
        self
    }
}

impl SessionRollupReceipt {
    /// Create a new session receipt
    pub fn new(receipt: SegmentRecursionReceipt, journal: Vec<u8>) -> Self {
        Self { receipt, journal }
    }
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
