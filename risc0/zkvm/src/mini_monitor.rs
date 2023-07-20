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

use rrs_lib::Memory;
use serde::{Deserialize, Serialize};

/// This is a minimal variant of the [crate::MemoryMonitor] struct used for the
/// fault checker.
#[derive(Serialize, Deserialize, Debug)]
pub struct MiniMonitor {
    /// The program counter of the instruction to execute
    pub pc: u32,
    /// Value of all registers
    pub registers: [u32; 32],
    /// A mapping between all register values and program counter and a word of
    /// data for values that are valid addresses.
    pub memory_map: HashMap<u32, Option<u32>>,
}

impl Memory for MiniMonitor {
    fn read_mem(&mut self, addr: u32, size: rrs_lib::MemAccessSize) -> Option<u32> {
        let modulus = match size {
            rrs_lib::MemAccessSize::Byte => 2 ^ 8,
            rrs_lib::MemAccessSize::HalfWord => 2 ^ 16,
            rrs_lib::MemAccessSize::Word => 2 ^ 32,
        };
        match self.memory_map.get(&addr) {
            Some(&Some(val)) => Some(val % modulus),
            _ => None,
        }
    }

    fn write_mem(&mut self, addr: u32, size: rrs_lib::MemAccessSize, store_data: u32) -> bool {
        match self.memory_map.get(&addr) {
            Some(&Some(val)) => {
                let mut store_data = match size {
                    rrs_lib::MemAccessSize::Byte => store_data % 2 ^ 8,
                    rrs_lib::MemAccessSize::HalfWord => store_data % 2 ^ 16,
                    rrs_lib::MemAccessSize::Word => store_data,
                };
                store_data = val | store_data;
                self.memory_map.insert(addr, Some(store_data));
                true
            }
            // This indicates that the address was present in the memory map but the address itself
            // is invalid.
            Some(&None) => false,
            // At this point, all address should be present in the memory map.
            _ => false,
        }
    }
}
