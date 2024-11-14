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

use crate::sha::Digest;
use alloc::vec;
use anyhow::Result;
use risc0_zkvm_platform::syscall::DIGEST_BYTES;

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
