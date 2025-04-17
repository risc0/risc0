// Copyright 2025 RISC Zero, Inc.
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

use std::cell::Cell;

use anyhow::Result;
use derive_more::Debug;
use risc0_binfmt::MemoryImage;
use serde::{Deserialize, Serialize};

use crate::{
    execute::{testutil, Executor},
    Rv32imV2Claim, MAX_INSN_CYCLES, MAX_INSN_CYCLES_LOWER_PO2,
};

use super::{Syscall, SyscallContext};

#[derive(Clone, Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct Segment {
    /// Initial sparse memory state for the segment
    pub partial_image: MemoryImage,

    pub claim: Rv32imV2Claim,

    /// Recorded host->guest IO, one entry per read
    #[debug("{}", read_record.len())]
    pub read_record: Vec<Vec<u8>>,

    /// Recorded rlen of guest->host IO, one entry per write
    #[debug("{}", write_record.len())]
    pub write_record: Vec<u32>,

    /// Cycle at which we suspend
    pub suspend_cycle: u32,

    /// Total paging cycles
    pub paging_cycles: u32,

    pub segment_threshold: u32,

    pub po2: u32,

    pub index: u64,
}

impl Segment {
    pub fn encode(&self) -> Result<Vec<u8>> {
        Ok(postcard::to_stdvec(self)?)
    }

    pub fn decode(bytes: &[u8]) -> Result<Self> {
        Ok(postcard::from_bytes(bytes)?)
    }

    pub fn execute(&self) -> Result<()> {
        let handler = SegmentSyscallHandler {
            segment: self,
            read_pos: Cell::new(0),
            write_pos: Cell::new(0),
        };

        let max_insn_cycles = if self.po2 >= 15 {
            MAX_INSN_CYCLES
        } else {
            MAX_INSN_CYCLES_LOWER_PO2
        };
        Executor::new(self.partial_image.clone(), &handler, None, vec![]).run(
            self.po2 as usize,
            max_insn_cycles,
            testutil::DEFAULT_SESSION_LIMIT,
            |_| Ok(()),
        )?;
        Ok(())
    }
}

struct SegmentSyscallHandler<'a> {
    segment: &'a Segment,
    read_pos: Cell<usize>,
    write_pos: Cell<usize>,
}

impl Syscall for SegmentSyscallHandler<'_> {
    fn host_read(&self, _ctx: &mut dyn SyscallContext, _fd: u32, buf: &mut [u8]) -> Result<u32> {
        let pos = self.read_pos.replace(self.read_pos.get() + 1);
        let read_record = &self.segment.read_record[pos];
        buf.copy_from_slice(read_record);
        Ok(read_record.len() as u32)
    }

    fn host_write(&self, _ctx: &mut dyn SyscallContext, _fd: u32, _buf: &[u8]) -> Result<u32> {
        let pos = self.write_pos.replace(self.read_pos.get() + 1);
        Ok(self.segment.write_record[pos])
    }
}
