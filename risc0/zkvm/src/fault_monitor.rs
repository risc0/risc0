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

use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::{
    memory::{SYSTEM, TEXT_START},
    syscall::reg_abi::REG_MAX,
};
use rrs_lib::{MemAccessSize, Memory};
use serde::{Deserialize, Serialize};

/// This is a small implementation of a memory monitor used for the fault
/// checker. It contains 2 pages: a page containing the pc and the page
/// containing all register values. These two pages hold enough information to
/// run a single instruction.
#[derive(Serialize, Deserialize, Debug, Clone)]
pub struct FaultCheckMonitor {
    /// The program counter of the instruction to execute
    pub pc: u32,
    /// The next instruction (aka, the value referenced by the pc)
    pub insn: u32,
    /// Data of all registers
    pub regs: [u32; REG_MAX],
    /// Post ID digest. TODO: this needs to be computed from the memory state
    pub post_id: Digest,
}

impl FaultCheckMonitor {
    const LOWEST: u32 = TEXT_START;
    const HIGHEST: u32 = SYSTEM.start() as u32;
    /// Given an address, return true if the address is within the zkVM's
    /// accessible memory regions
    pub fn address_is_within_range(&self, addr: u32) -> bool {
        Self::LOWEST <= addr && addr < Self::HIGHEST
    }
}

/// This implements a way for the rrs crate to read and write memory regions. If
/// the execution gets to this point, the address has been checked to ensure
/// that it's aligned. The only thing the fault checker needs to do is to ensure
/// that the read and write addresses are within range. The reads and writes do
/// not need to fetch/write to the memory map. One exception is the next
/// instruction. The instruction at pc needs to be fetched from memory. For this
/// implementation, a special case has been implemented to fetch the
/// instruction.
impl Memory for FaultCheckMonitor {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        let val: u32 = if addr == self.pc {
            match size {
                // if we get here, the caller requested to fetch the entire instruction.
                MemAccessSize::Word => self.insn,
                _ => 0,
            }
        } else {
            0 // Since we don't actually need to read. Return `Some(0)` on
              // anything else
        };
        self.address_is_within_range(addr).then_some(val)
    }

    fn write_mem(&mut self, addr: u32, _size: rrs_lib::MemAccessSize, _store_data: u32) -> bool {
        // Since we don't actually need to write, return the result of the range check.
        self.address_is_within_range(addr)
    }
}
