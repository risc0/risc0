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

extern crate alloc;

use alloc::vec::Vec;

use anyhow::Result;
use serde::{Deserialize, Serialize};

/// An event traced from the running VM.
#[derive(Clone, Eq, Ord, PartialEq, PartialOrd, Serialize, Deserialize)]
pub enum TraceEvent {
    /// An instruction has started at the given program counter
    InstructionStart {
        /// Cycle number since startup
        cycle: u64,
        /// Program counter of the instruction being executed
        pc: u32,
        /// Encoded instruction being executed.
        insn: u32,
    },

    /// A register has been set
    RegisterSet {
        /// Register ID (0-16)
        idx: usize,
        /// New value in the register
        value: u32,
    },

    /// A memory location has been written
    MemorySet {
        /// Address of memory that's been written
        addr: u32,
        /// Data that's been written
        region: Vec<u8>,
    },
}

/// A callback used to collect [TraceEvent]s.
pub trait TraceCallback {
    fn trace_callback(&mut self, event: TraceEvent) -> Result<()>;
}

impl<F: FnMut(TraceEvent) -> Result<()>> TraceCallback for F {
    fn trace_callback(&mut self, event: TraceEvent) -> Result<()> {
        self(event)
    }
}

impl core::fmt::Debug for TraceEvent {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            Self::InstructionStart { cycle, pc, insn } => {
                write!(f, "InstructionStart({cycle}, 0x{pc:08X}, 0x{insn:08X})")
            }
            Self::RegisterSet { idx, value } => write!(f, "RegisterSet({idx}, 0x{value:08X})"),
            Self::MemorySet { addr, region } => {
                write!(f, "MemorySet(0x{addr:08X}, {region:#04X?})")
            }
        }
    }
}
