// Copyright 2026 RISC Zero, Inc.
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

use anyhow::{Context, Result};
use derive_more::Debug;
use risc0_binfmt::{MemoryImage, PovwNonce};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::{
    TerminateState,
    execute::{
        ExecutionLimit, Executor, ExecutorResult, RV32IM_M3_CIRCUIT_VERSION,
        executor::ExecutionError,
    },
};

use super::{Syscall, SyscallContext};

#[derive(Clone, Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct Segment {
    /// Initial sparse memory state for the segment
    ///
    /// It is not mandated that this have all digests up to date, as long as the dirty digests are
    /// marked. A process that receives a Segment must call [MemoryImage::update_digests] before
    /// any operation that accesses the digest values.
    pub partial_image: MemoryImage,

    /// Recorded host->guest IO, one entry per read
    #[debug("{}", read_record.len())]
    pub read_record: Vec<Vec<u8>>,
    /// Recorded rlen of guest->host IO, one entry per write
    #[debug("{}", write_record.len())]
    pub write_record: Vec<u32>,

    /// Digest written to the input slot of the globals and claim.
    pub input_digest: Digest,
    /// Digest written to the output slot of the globals and claim.
    pub output_digest: Option<Digest>,
    /// Value set upon termination of execution, indicating the termination type.
    pub terminate_state: Option<TerminateState>,

    pub segment_threshold: u32,

    pub used_rows: u32,

    /// Power-of-two for the segment size required to prove this segment.
    pub po2: u32,
    /// Index of the segment in the session.
    pub index: u64,
    /// Gloablly unique nonce used within the proof of verifiable work system.
    pub povw_nonce: Option<PovwNonce>,

    pub insn_counter: u32,

    /// Used to help debug the block tracking
    pub blocks: crate::execute::BlockCollection,
}

impl Segment {
    pub fn encode(&self) -> Result<Vec<u8>> {
        Ok(postcard::to_stdvec(self)?)
    }

    pub fn decode(bytes: &[u8]) -> Result<Self> {
        Ok(postcard::from_bytes(bytes)?)
    }

    /// Execute the [Segment], returning the execution result.
    ///
    /// This method can be used to compute the [crate::Rv32imV2Claim] from this segment.
    pub fn execute(&self) -> Result<ExecutorResult, ExecutionError> {
        let handler = SegmentSyscallHandler {
            segment: self,
            read_pos: Cell::new(0),
            write_pos: Cell::new(0),
        };
        let circuit_version = RV32IM_M3_CIRCUIT_VERSION;

        Executor::new(
            self.partial_image.clone(),
            handler,
            None,
            vec![],
            None,
            circuit_version,
        )
        .run(
            ExecutionLimit::default()
                .with_segment_po2(self.po2 as usize)
                .with_soft_session_limit(self.used_rows.into())
                // Set the max_insn_rows to 0 to prevent splits based on this. We know we need to
                // split on used_rows.
                .with_max_insn_rows(0),
            |_| Ok(()),
        )
    }
}

struct SegmentSyscallHandler<'a> {
    segment: &'a Segment,
    read_pos: Cell<usize>,
    write_pos: Cell<usize>,
}

impl Syscall for SegmentSyscallHandler<'_> {
    fn host_read(&self, _ctx: &mut impl SyscallContext, _fd: u32, buf: &mut [u8]) -> Result<u32> {
        let pos = self.read_pos.replace(self.read_pos.get() + 1);
        let read_record = &self.segment.read_record[pos];
        buf.copy_from_slice(read_record);
        Ok(read_record.len() as u32)
    }

    fn host_write(&self, _ctx: &mut impl SyscallContext, _fd: u32, _buf: &[u8]) -> Result<u32> {
        let pos = self.write_pos.replace(self.write_pos.get() + 1);
        Ok(*self
            .segment
            .write_record
            .get(pos)
            .context("malformed segment: write_pos is past the end of write_record")?)
    }
}
