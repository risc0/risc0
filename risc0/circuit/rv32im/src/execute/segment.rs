// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::cell::Cell;

use anyhow::Result;
use derive_more::Debug;
use risc0_binfmt::{MemoryImage, PovwNonce};
use serde::{Deserialize, Serialize};

use crate::{
    MAX_INSN_CYCLES, MAX_INSN_CYCLES_LOWER_PO2, Rv32imV2Claim,
    execute::{CycleLimit, Executor, RV32IM_V2_CIRCUIT_VERSION},
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

    pub povw_nonce: Option<PovwNonce>,

    pub insn_counter: u32,
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
        Executor::new(
            self.partial_image.clone(),
            &handler,
            None,
            vec![],
            None,
            RV32IM_V2_CIRCUIT_VERSION,
        )
        .run(
            self.po2 as usize,
            max_insn_cycles,
            CycleLimit::Soft(self.suspend_cycle.into()),
            |_| Ok(()),
        )?;
        Ok(())
    }
}

struct SegmentSyscallHandler<'a> {
    segment: &'a Segment,
    read_pos: Cell<usize>,
    #[expect(dead_code)]
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
        unimplemented!()
    }
}
