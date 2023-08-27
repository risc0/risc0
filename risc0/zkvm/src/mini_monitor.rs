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

use std::collections::HashMap;

use anyhow::{bail, Result};
use risc0_binfmt::compute_image_id;
use risc0_zkp::core::{
    digest::Digest,
    hash::sha::{BLOCK_BYTES, SHA256_INIT},
};
use risc0_zkvm_platform::{
    memory::{SYSTEM, TEXT_START},
    syscall::{reg_abi::REG_MAX, DIGEST_BYTES},
    WORD_SIZE,
};
use rrs_lib::Memory;
use serde::{Deserialize, Serialize};

use crate::sha::{Impl, Sha256};

// each element of the merkle path has the following:
// 1) a page entry address index. None indicates root index.
// 2) a reference count
// 3) the page bytes
pub type MerklePathElement = (Option<u32>, u32, Vec<u8>);

/// This is a small implementation of a memory monitor used for the fault
/// checker. It records all memory regions needed for a signle RISC-V
/// instruction execution.
#[derive(Serialize, Deserialize, Debug)]
pub struct MiniMonitor {
    /// The program counter of the instruction to execute
    pub pc: u32,
    /// A mapping between all register values and program counter and a word of
    /// data for values that are valid addresses.
    pub memory_map: HashMap<u32, MerklePathElement>,
    /// size of each page within each entry of the [MerklePathElement]
    pub page_size: u32,
}

impl MiniMonitor {
    const LOWEST: u32 = TEXT_START;
    const HIGHEST: u32 = SYSTEM.start() as u32;
    /// Given an address, return true if the address is within the zkVM's
    /// accessible memory regions
    pub fn address_is_within_range(&self, addr: u32) -> bool {
        Self::LOWEST <= addr && addr < Self::HIGHEST
    }

    /// get the 32-bit value value referenced by the program counter.
    pub fn get_pc_value(&self) -> Result<u32> {
        let offset = self.get_offset(self.pc) as usize;
        let idx = self.get_page_index(self.pc);

        let page = match self.memory_map.get(&idx) {
            Some((_, _, data)) => data,
            None => bail!("page index {idx} does not exist in the memory map"),
        };

        if offset + WORD_SIZE > page.len() {
            bail!("Not enough data in page");
        }
        Ok(*bytemuck::from_bytes::<u32>(
            &page[offset..offset + WORD_SIZE],
        ))
    }

    /// get all register contents from the memory map.
    pub fn get_registers(&self) -> Result<[u32; REG_MAX]> {
        const REGISTER_LENGTH: usize = WORD_SIZE * REG_MAX;
        let offset = self.get_offset(SYSTEM.start() as u32) as usize;
        let idx = self.get_page_index(SYSTEM.start() as u32);

        let page = match self.memory_map.get(&idx) {
            Some((_, _, data)) => data,
            None => bail!("page index {idx} does not exist in the memory map"),
        };

        if offset + REGISTER_LENGTH > page.len() {
            bail!("Not enough data in SYSTEM region");
        }

        let mm_regs: &[u32] = bytemuck::cast_slice(&page[offset..offset + REGISTER_LENGTH]);
        let mut registers = [0u32; REG_MAX];

        for idx in 0..REG_MAX {
            registers[idx] = mm_regs[idx];
        }
        Ok(registers)
    }

    fn hash_page_bytes(page: &[u8]) -> Digest {
        let mut state = SHA256_INIT;
        assert!(page.len() % BLOCK_BYTES == 0);
        for block in page.chunks_exact(BLOCK_BYTES) {
            let block1 = Digest::try_from(&block[0..DIGEST_BYTES]).unwrap();
            let block2 = Digest::try_from(&block[DIGEST_BYTES..BLOCK_BYTES]).unwrap();
            state = *Impl::compress(&state, &block1, &block2);
        }
        state
    }

    fn get_root_digest(&self, memory_map: &mut HashMap<u32, MerklePathElement>) -> Result<Digest> {
        // we need to start at the two leaf pages and merklize
        let mut addr = self.pc;

        loop {
            let page_idx = self.get_page_index(addr);
            let (entry, _, data) = memory_map.get_mut(&page_idx).unwrap();

            // get the entry page
            addr = match entry {
                Some(val) => *val,
                None => {
                    // we're at the root page. Compute the digest.
                    return Ok(Self::hash_page_bytes(&data));
                }
            };
        }
    }

    fn traverse_merkle_path(&self, memory_map: &mut HashMap<u32, MerklePathElement>, addr: u32) {
        // we need to start at the two leaf pages and merklize
        let mut page_idx = self.get_page_index(addr);

        loop {
            let (entry, ref_count, data) = memory_map.get_mut(&page_idx).unwrap();
            *ref_count -= 1;

            if *ref_count > 0 || entry.is_none() {
                break;
            }

            // get the digest
            let digest = &Self::hash_page_bytes(&data);
            let digest_bytes = digest.as_bytes();

            // get the entry page
            let entry_idx = self.get_page_index(entry.unwrap());
            let entry_offset = self.get_offset(entry.unwrap()) as usize;
            let (_, _, entry_page) = memory_map.get_mut(&entry_idx).unwrap();

            // write the digest to the entry page
            for idx in 0..DIGEST_BYTES {
                entry_page[idx + entry_offset] = digest_bytes[idx];
            }
            page_idx = entry_idx;
        }
    }

    /// get the root hash of the memory map.
    pub fn compute_root_hash(&self) -> Result<Digest> {
        let mut memory_map = self.memory_map.clone();

        self.traverse_merkle_path(&mut memory_map, self.pc);
        self.traverse_merkle_path(&mut memory_map, SYSTEM.start() as u32);
        let digest = self.get_root_digest(&mut memory_map)?;
        Ok(compute_image_id(&digest, self.get_pc_value()?))
    }

    /// get the page index. The page index is the key for the hash map used in
    /// the memory map.
    pub fn get_page_index(&self, addr: u32) -> u32 {
        addr >> self.page_size.ilog2()
    }

    /// get the page index. The page index is the key for the hash map used in
    /// the memory map.
    pub fn get_offset(&self, addr: u32) -> u32 {
        addr % self.page_size
    }
}

/// This implements a way for the rrs crate to read and write memory regions. If
/// the execution gets to this point, the address has been checked to ensure
/// that it's aligned. The only thing the fault checker needs to do is to ensure
/// that the read and write addresses are within range. The reads and writes do
/// not need to fetch/write to the memory map.
impl Memory for MiniMonitor {
    fn read_mem(&mut self, addr: u32, _size: rrs_lib::MemAccessSize) -> Option<u32> {
        // Since we don't actually need to read. Return `Some(0)` on a successful read.
        self.address_is_within_range(addr).then_some(0)
    }

    fn write_mem(&mut self, addr: u32, _size: rrs_lib::MemAccessSize, _store_data: u32) -> bool {
        // Since we don't actually need to write, return the result of the range check.
        self.address_is_within_range(addr)
    }
}
