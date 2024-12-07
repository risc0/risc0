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

use alloc::vec;

use anyhow::Result;
use risc0_circuit_keccak::{KeccakState, KECCAK_CONTROL_ROOT, KECCAK_DEFAULT_PO2};
use risc0_zkp::core::hash::sha::SHA256_INIT;
use risc0_zkvm_platform::syscall::{
    sys_keccak_permute, sys_prove_keccak, sys_sha_compress, DIGEST_BYTES, DIGEST_WORDS,
};

use crate::sha::Digest;

const KECCAK_PERMUTE_CYCLES: usize = 200;
const MAX_KECCAK_CYCLES: usize = 1 << KECCAK_DEFAULT_PO2;
const MAX_KECCAK_INPUTS: usize = MAX_KECCAK_CYCLES / KECCAK_PERMUTE_CYCLES;

/// This struct implements the batching of calls to the keccak accelerator.
pub struct Keccak2Batcher {
    claim_state: Digest,
    inputs: Vec<KeccakState>,
}

impl Keccak2Batcher {
    pub const fn init() -> Self {
        Self {
            claim_state: SHA256_INIT,
            inputs: vec![],
        }
    }

    pub fn update(&mut self, in_state: &KeccakState) -> KeccakState {
        let mut out_state = KeccakState::default();
        unsafe { sys_keccak_permute(in_state, &mut out_state) };
        self.sha_single_keccak(in_state);
        self.inputs.push(*in_state);
        if self.inputs.len() == MAX_KECCAK_INPUTS {
            // we've reached the limit. Create a proof request.
            self.finalize();
        }
        out_state
    }

    pub fn finalize(&mut self) {
        if self.inputs.is_empty() {
            // no input so there's nothing to do
            self.reset();
            return;
        }

        let input: &[u32] = bytemuck::cast_slice(self.inputs.as_flattened());
        let claim_digest = self.claim_digest();

        unsafe {
            sys_prove_keccak(
                claim_digest.as_ref(),
                KECCAK_DEFAULT_PO2,
                KECCAK_CONTROL_ROOT.as_ref(),
                input.as_ptr(),
                input.len(),
            );
        }
        crate::guest::env::verify_assumption(claim_digest, KECCAK_CONTROL_ROOT).unwrap();

        self.reset();
    }

    fn claim_digest(&self) -> Digest {
        let mut claim_digest = self.claim_state;
        for word in claim_digest.as_mut_words().iter_mut() {
            *word = word.to_be();
        }
        claim_digest
    }

    fn reset(&mut self) {
        self.claim_state = SHA256_INIT;
        self.inputs = vec![];
    }

    fn sha_single_keccak(&mut self, keccak_in_state: &KeccakState) {
        let mut to_hash = [0u32; 64];
        to_hash[..50].clone_from_slice(bytemuck::cast_slice(keccak_in_state));

        let to_hash: &[Digest] = bytemuck::cast_slice(&to_hash);
        for i in 0..4 {
            let mut blk1: [u32; DIGEST_WORDS] = to_hash[i * 2].into();
            for word in blk1.iter_mut() {
                *word = word.to_be();
            }
            let mut blk2: [u32; DIGEST_WORDS] = to_hash[i * 2 + 1].into();
            for word in blk2.iter_mut() {
                *word = word.to_be();
            }

            unsafe {
                sys_sha_compress(
                    self.claim_state.as_mut(),
                    self.claim_state.as_ref(),
                    blk1.as_ptr() as *const [u32; DIGEST_WORDS],
                    blk2.as_ptr() as *const [u32; DIGEST_WORDS],
                )
            };
        }
    }
}
/// This struct implements the batching of calls to the keccak accelerator.
pub struct KeccakBatcher {
    input_transcript: [u8; Self::KECCAK_LIMIT],
    block_count_offset: usize,
    data_offset: usize,
}

impl Default for KeccakBatcher {
    /// create a new instance of a batcher with an input transcript region
    fn default() -> Self {
        Self {
            input_transcript: [0u8; Self::KECCAK_LIMIT],
            block_count_offset: 0,
            data_offset: Self::BLOCK_COUNT_BYTES,
        }
    }
}

impl KeccakBatcher {
    pub const fn init() -> Self {
        Self {
            input_transcript: [0u8; Self::KECCAK_LIMIT],
            block_count_offset: 0,
            data_offset: Self::BLOCK_COUNT_BYTES,
        }
    }

    pub const KECCAK_LIMIT: usize = 100_000;
    pub const BLOCK_COUNT_BYTES: usize = 8;
    pub const BLOCK_BYTES: usize = 136;
    pub const FINAL_PADDING_BYTES: usize = 8;

    /// write data to the input transcript.
    ///
    /// This is meant to be used by lower-level functions within keccak crates.
    /// Many keccak crates will write raw data and padding to a 1600 bit buffer
    /// often called the "state". All data and padding written to the state
    /// should be passed to this function.
    fn write_data(&mut self, input: &[u8]) -> Result<()> {
        self.input_transcript[self.data_offset..self.data_offset + input.len()]
            .copy_from_slice(input);
        self.data_offset += input.len();

        Ok(())
    }

    /// write padding to the input transcript.
    ///
    /// Pad the raw input with the delimitor, 0x00 bytes, and a 0x80 byte. This
    /// will pad the raw data upto the current block boundary.
    fn write_padding(&mut self) -> Result<()> {
        self.write_data(&[0x01])?;
        let data_length = self.current_data_length();
        let remaining_bytes = Self::BLOCK_BYTES - (data_length % Self::BLOCK_BYTES);

        let zeroes = vec![0u8; remaining_bytes - 1];

        self.write_data(&zeroes)?;
        self.write_data(&[0x80])?;

        Ok(())
    }

    /// write keccak hash to the transcript, updating the block count.
    ///
    /// the amount of raw data written to the
    pub fn write_keccak_entry(&mut self, input: &[u8], hash: &[u8; 32]) -> Result<()> {
        // if this entry does not fit in the remaining space, create a new claim and reset the batcher.
        let padding_bytes = Self::BLOCK_BYTES - (input.len() % Self::BLOCK_BYTES);
        if self.data_offset + input.len() + padding_bytes + DIGEST_BYTES + Self::FINAL_PADDING_BYTES
            > Self::KECCAK_LIMIT
        {
            let _digest = self.finalize_transcript();
        }

        self.write_data(input)?;
        self.write_padding()?;

        let data_length = self.current_data_length();
        let block_count = (data_length / Self::BLOCK_BYTES) as u8;

        self.write_data(hash)?;
        self.input_transcript[self.block_count_offset] = block_count;

        self.block_count_offset = self.data_offset;
        self.data_offset += Self::BLOCK_COUNT_BYTES;
        Ok(())
    }

    /// get the digest of the input transcript
    pub fn finalize_transcript(&mut self) -> Digest {
        use risc0_zkp::core::hash::sha::Sha256;

        self.input_transcript
            [self.block_count_offset..self.block_count_offset + Self::BLOCK_COUNT_BYTES]
            .copy_from_slice(&[0u8; Self::BLOCK_COUNT_BYTES]);
        let transcript_digest = crate::sha::Impl::hash_bytes(
            &self.input_transcript[0..self.block_count_offset + Self::BLOCK_COUNT_BYTES],
        );

        // TODO: add assumption, send transcript
        // crate::guest::env::verify_assumption(*transcript_digest, Digest::default()).unwrap();
        self.reset();
        *transcript_digest
    }

    fn reset(&mut self) {
        self.block_count_offset = 0;
        self.data_offset = Self::BLOCK_COUNT_BYTES;
    }

    fn current_data_length(&self) -> usize {
        self.data_offset - (self.block_count_offset + Self::BLOCK_COUNT_BYTES)
    }

    /// returns ture if the batcher has consumed data to hash. Used to determine
    /// whether if transcript hash should be generated.
    pub fn has_data(&self) -> bool {
        self.data_offset != Self::BLOCK_COUNT_BYTES
    }
}
