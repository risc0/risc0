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

use std::collections::BTreeSet;

use anyhow::{Context, Result};
use enum_map::EnumMap;
use risc0_binfmt::{ByteAddr, MemoryImage, PovwNonce};
use risc0_zkp::core::digest::Digest;

use crate::{
    BlockType, Claim, EcallKind, EcallMetric, MAX_INSN_ROWS, MAX_INSN_ROWS_LOWER_PO2,
    TerminateState, execute::DEFAULT_SEGMENT_LIMIT_PO2, trace::TraceEvent,
};

use super::{
    pager::{PageTraceEvent, WorkingImage, compute_partial_image},
    segment::Segment,
};

/// Results from running the [Executor], including information about the initial and final memory
/// states as well metrics for the number of segments and rows used.
///
/// This struct has the information required to compute the [Claim] for the execution.
#[derive(Clone, Debug)]
#[non_exhaustive]
pub struct ExecutorResult {
    pub segments: u64,
    pub pre_image: MemoryImage,
    pub post_image: MemoryImage,
    pub row_count: u64,
    pub padding_row_count: u64,
    pub insn_count: u64,
    pub ecall_metrics: EnumMap<EcallKind, EcallMetric>,
    pub block_counts: Option<EnumMap<BlockType, u64>>,

    // Fields used to populate the [Claim].
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub po2: u32,
}

impl ExecutorResult {
    /// Construct the [Claim] for this execution.
    ///
    /// Calling this function will compute the digests of the pre and post image, if needed.
    pub fn claim(&mut self) -> Claim {
        Claim {
            po2: self.po2,
            pre_state: self.pre_image.image_id(),
            post_state: self.post_image.image_id(),
            output: self.output,
            terminate_state: self.terminate_state,
            povw_nonce: PovwNonce::default(),
        }
    }
}

#[derive(Default)]
pub(crate) struct RowInfo {
    pub count: u64,
    pub padding_count: u64,
    pub insn_count: u64,
    pub block_counts: Option<EnumMap<BlockType, u64>>,
    pub row_points: u64,
}

#[non_exhaustive]
pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
}

/// Limits on the execution, ensuring each segment can be proven and the session terminates.
#[derive(Copy, Clone, Debug)]
#[non_exhaustive]
pub struct ExecutionLimit {
    /// Maximum size of a segment, expressed as a power-of-two.
    pub segment_po2: usize,
    /// Maximum number of rows a single instruction is allowed to consume.
    ///
    /// Ecall instructions and paging can result in a single worst-case instruction taking
    /// thousands of rows. This is the limit on a number of rows a single instruction can take.
    /// If an instruction exceeds this limit, and falls at the end of segment, it may result in an
    /// execution failure.
    pub max_insn_rows: Option<usize>,
    /// Limit on the number of rows to execute in the session.
    pub session: RowLimit,
}

impl Default for ExecutionLimit {
    fn default() -> Self {
        Self::DEFAULT
    }
}

impl ExecutionLimit {
    pub const DEFAULT: Self = Self {
        segment_po2: DEFAULT_SEGMENT_LIMIT_PO2,
        max_insn_rows: None,
        session: RowLimit::None,
    };

    pub const fn with_segment_po2(self, segment_po2: usize) -> Self {
        Self {
            segment_po2,
            ..self
        }
    }

    pub const fn with_max_insn_rows(self, max_insn_rows: usize) -> Self {
        Self {
            max_insn_rows: Some(max_insn_rows),
            ..self
        }
    }

    pub const fn with_session_limit(self, session: RowLimit) -> Self {
        Self { session, ..self }
    }

    pub const fn with_soft_session_limit(self, rows: u64) -> Self {
        Self {
            session: RowLimit::Soft(rows),
            ..self
        }
    }

    pub const fn with_hard_session_limit(self, rows: u64) -> Self {
        Self {
            session: RowLimit::Hard(rows),
            ..self
        }
    }

    pub fn segment_limit(&self) -> u32 {
        1 << self.segment_po2 as u32
    }

    pub(crate) fn segment_threshold(&self) -> u32 {
        self.segment_limit() - self.max_insn_rows() as u32
    }

    pub fn max_insn_rows(&self) -> usize {
        self.max_insn_rows.unwrap_or(if self.segment_po2 >= 15 {
            MAX_INSN_ROWS
        } else {
            MAX_INSN_ROWS_LOWER_PO2
        })
    }
}

#[derive(Copy, Clone, Debug, Default)]
pub enum RowLimit {
    /// Hard limit on the number of rows, it is an error to exceed this limit.
    Hard(u64),
    /// Soft limit on the number of rows. Terminate, without error, if this limit is reached.
    Soft(u64),
    /// No limit on the number of rows.
    #[default]
    None,
}

#[derive(thiserror::Error, Debug)]
#[non_exhaustive]
pub enum ExecutionError {
    /// Error when when a hard [RowLimit] is exceeded.
    #[error("Session limit exceeded: {rows} >= {limit}")]
    RowLimitExceeded { limit: u64, rows: u64 },
    /// Error when the execution encounters an error. Optionally includes a [SegmentUpdate] with
    /// the results of execution up to the point of error in the final segment.
    #[error("Execution failed at program counter {pc:?}: {error}")]
    ExecutionFailed {
        #[source]
        error: anyhow::Error,
        pc: ByteAddr,
        update: Option<Box<SegmentUpdate>>,
    },
    #[error(transparent)]
    Other(#[from] anyhow::Error),
}

/// Update message sent to the segment callback on each split.
///
/// Contains the updated memory pages as well as the pages accessed during the associated segment.
/// Can be used to construct a [Segment] starting from an an initial memory state and processing
/// each segment update.
#[non_exhaustive]
#[derive(Clone, derive_more::Debug)]
pub struct SegmentUpdate {
    /// Partial image containing pages that were written to in the segment.
    pub(crate) update_partial_image: WorkingImage,
    /// Indices of all pages that were accessed in the segment.
    pub(crate) access_page_indexes: BTreeSet<u32>,

    /// Record of what is read by the guest across all syscalls.
    #[debug("{}", read_record.len())]
    pub(crate) read_record: Vec<Vec<u8>>,
    /// Record of writen to the host across all syscalls.
    #[debug("{}", write_record.len())]
    pub(crate) write_record: Vec<u32>,

    /// Input digest available to the guest via the input ecall.
    pub(crate) input_digest: Digest,
    /// Output digest set by the guest upon termination.
    ///
    /// Will only be `Some` if `terminate_state` is `Some`.
    pub(crate) output_digest: Option<Digest>,
    /// Value set upon termination of execution, indicating the termination type.
    pub(crate) terminate_state: Option<TerminateState>,

    pub used_rows: u32,
    pub insn_counter: u32,
    pub(crate) segment_threshold: u32,

    /// Power-of-two for the segment size required to prove this segment.
    pub po2: u32,
    /// Index of the segment in the session.
    pub(crate) index: u64,
    /// Gloablly unique nonce used within the proof of verifiable work system.
    pub(crate) povw_nonce: Option<PovwNonce>,

    /// Used to help debug the block tracking
    pub(crate) blocks: super::block_tracker::BlockCollection,
}

impl SegmentUpdate {
    /// Applies the update to the given [MemoryImage].
    ///
    /// Provided that the given memory image represents that state at the start of the segment, the
    /// memory image will be updated to the state after the segment.
    ///
    /// This function does not guarantee an update the node digests in the [MemoryImage] Merkle
    /// tree. To ensure that the digests are up to date, call [MemoryImage::update_digests].
    pub fn apply_to(&self, memory_image: &mut MemoryImage) -> Result<()> {
        for (idx, page) in self.update_partial_image.pages.iter() {
            memory_image.set_page(*idx, page.clone());
        }
        Ok(())
    }

    /// Compute a partially populated [MemoryImage] containing all pages from the given memory
    /// image that were accessed during this segment along with the Merkle tree uncles. The given
    /// memory image is updated to cache any hashes computed in the process.
    ///
    /// This function does not guarantee the digests are up to date on the returned [MemoryImage].
    /// Call [MemoryImage::update_digests] if needed to ensure the digests are up to date.
    pub fn compute_partial_image(&self, memory_image: &mut MemoryImage) -> Result<MemoryImage> {
        Ok(compute_partial_image(
            memory_image,
            &self.access_page_indexes,
        ))
    }

    /// Construct a [Segment] from this struct and the given initial memory image.
    ///
    /// The initial partial memory image can be calculated with [Self::compute_partial_image], as
    /// only accessed pages are required.
    pub fn into_segment(self, partial_image: MemoryImage) -> Segment {
        Segment {
            partial_image,
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            terminate_state: self.terminate_state,
            read_record: self.read_record,
            write_record: self.write_record,
            used_rows: self.used_rows,
            insn_counter: self.insn_counter,
            po2: self.po2,
            index: self.index,
            segment_threshold: self.segment_threshold,
            povw_nonce: self.povw_nonce,
            blocks: self.blocks,
        }
    }

    /// Produces a [Segment] with the partial memory image fore all accessed pages, then applies
    /// the update to the given [MemoryImage].
    pub fn apply_into_segment(self, memory_image: &mut MemoryImage) -> Result<Segment> {
        let partial_image = self
            .compute_partial_image(memory_image)
            .context("Failed to compute partial memory image")?;
        self.apply_to(memory_image)
            .context("Failed to apply update to memory image")?;
        Ok(self.into_segment(partial_image))
    }
}

impl From<PageTraceEvent> for TraceEvent {
    fn from(event: PageTraceEvent) -> Self {
        match event {
            PageTraceEvent::PageIn { cycles } => TraceEvent::PageIn { cycles },
            PageTraceEvent::PageOut { cycles } => TraceEvent::PageOut { cycles },
        }
    }
}
