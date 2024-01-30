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

//! This module defines [Session] and [Segment] which provides a way to share
//! execution traces between the execution phase and the proving phase.

use std::{
    collections::BTreeSet,
    fs,
    path::{Path, PathBuf},
};

use anyhow::{ensure, Context, Result};
use risc0_binfmt::{MemoryImage, SystemState};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

use crate::{
    host::server::exec::executor::SyscallRecord, sha::Digest, Assumption, Assumptions, ExitCode,
    Journal, Output, ReceiptClaim, SegmentInfo, SessionInfo,
};

#[derive(Clone, Default, Serialize, Deserialize, Debug)]
pub struct PageFaults {
    pub(crate) reads: BTreeSet<u32>,
    pub(crate) writes: BTreeSet<u32>,
}

/// The execution trace of a program.
///
/// The record of memory transactions of an execution that starts from an
/// initial memory image (which includes the starting PC) and proceeds until
/// either a sys_halt or a sys_pause syscall is encountered. This record is
/// stored as a vector of [Segment]s.
#[derive(Serialize, Deserialize)]
pub struct Session {
    /// The constituent [Segment]s of the Session. The final [Segment] will have
    /// an [ExitCode] of [Halted](ExitCode::Halted), [Paused](ExitCode::Paused),
    /// or [SessionLimit](ExitCode::SessionLimit), and all other [Segment]s (if
    /// any) will have [ExitCode::SystemSplit].
    pub segments: Vec<Box<dyn SegmentRef>>,

    /// The data publicly committed by the guest program.
    pub journal: Option<Journal>,

    /// The data privately sent to the host.
    pub private_journal: Journal,

    /// The [ExitCode] of the session.
    pub exit_code: ExitCode,

    /// The final [MemoryImage] at the end of execution.
    pub post_image: MemoryImage,

    /// The list of assumptions made by the guest and resolved by the host.
    pub assumptions: Vec<Assumption>,

    /// The hooks to be called during the proving phase.
    #[serde(skip)]
    pub hooks: Vec<Box<dyn SessionEvents>>,

    /// The number of user cycles without any overhead for continuations or po2
    /// padding.
    pub user_cycles: u64,

    /// Total number of cycles that a prover experiences. This includes overhead
    /// associated with continuations and padding up to the nearest power of 2.
    pub total_cycles: u64,

    /// The system state of the initial [MemoryImage].
    pub pre_state: SystemState,

    /// The system state of the final [MemoryImage] at the end of execution.
    pub post_state: SystemState,
}

/// A reference to a [Segment].
///
/// This allows implementors to determine the best way to represent this in an
/// pluggable manner. See the [SimpleSegmentRef] for a very basic
/// implmentation.
#[typetag::serde(tag = "type")]
pub trait SegmentRef: Send {
    /// Resolve this reference into an actual [Segment].
    fn resolve(&self) -> Result<Segment>;
}

/// The execution trace of a portion of a program.
///
/// The record of memory transactions of an execution that starts from an
/// initial memory image, and proceeds until terminated by the system or user.
/// This represents a chunk of execution work that will be proven in a single
/// call to the ZKP system. It does not necessarily represent an entire program;
/// see [Session] for tracking memory transactions until a user-requested
/// termination.
#[derive(Clone, Serialize, Deserialize)]
pub struct Segment {
    pub(crate) pre_image: Box<MemoryImage>,
    // NOTE: segment.post_state is NOT EQUAL to segment.get_claim()?.post. This is because the
    // post SystemState on the ReceiptClaim struct has a PC that is shifted forward by 4.
    pub(crate) post_state: SystemState,
    pub(crate) output: Option<Output>,
    pub(crate) faults: PageFaults,
    pub(crate) syscalls: Vec<SyscallRecord>,
    pub(crate) split_insn: Option<u32>,
    pub(crate) exit_code: ExitCode,

    /// The number of cycles in powers of 2.
    pub po2: u32,

    /// The index of this [Segment] within the [Session]
    pub index: u32,

    /// The number of user cycles without any overhead for continuations or po2
    /// padding.
    pub cycles: u32,
}

/// The Events of [Session]
pub trait SessionEvents {
    /// Fired before the proving of a segment starts.
    #[allow(unused)]
    fn on_pre_prove_segment(&self, segment: &Segment) {}

    /// Fired after the proving of a segment ends.
    #[allow(unused)]
    fn on_post_prove_segment(&self, segment: &Segment) {}
}

impl Session {
    /// Construct a new [Session] from its constituent components.
    pub fn new(
        segments: Vec<Box<dyn SegmentRef>>,
        journal: Option<Vec<u8>>,
        private_journal: Vec<u8>,
        exit_code: ExitCode,
        post_image: MemoryImage,
        assumptions: Vec<Assumption>,
        user_cycles: u64,
        total_cycles: u64,
        pre_state: SystemState,
        post_state: SystemState,
    ) -> Self {
        Self {
            segments,
            journal: journal.map(|x| Journal::new(x)),
            private_journal: Journal::new(private_journal),
            exit_code,
            post_image,
            assumptions,
            hooks: Vec::new(),
            user_cycles,
            total_cycles,
            pre_state,
            post_state,
        }
    }

    /// Add a hook to be called during the proving phase.
    pub fn add_hook<E: SessionEvents + 'static>(&mut self, hook: E) {
        self.hooks.push(Box::new(hook));
    }

    /// Calculate for the [ReceiptClaim] associated with this [Session]. The
    /// [ReceiptClaim] is the claim that will be proven if this [Session]
    /// is passed to the [crate::Prover].
    pub fn get_claim(&self) -> Result<ReceiptClaim> {
        // Construct the Output struct for the session, checking internal consistency.
        // NOTE: The Session output if distinct from the final Segment output because in the
        // Session output any proven assumptions are not included.
        let output = if self.exit_code.expects_output() {
            self.journal
                .as_ref()
                .map(|journal| -> Result<_> {
                    Ok(Output {
                        journal: journal.bytes.clone().into(),
                        assumptions: Assumptions(
                            self.assumptions
                                .iter()
                                .filter_map(|a| match a {
                                    Assumption::Proven(_) => None,
                                    Assumption::Unresolved(r) => Some(r.clone()),
                                })
                                .collect::<Vec<_>>(),
                        )
                        .into(),
                    })
                })
                .transpose()?
        } else {
            ensure!(
                self.journal.is_none(),
                "Session with exit code {:?} has a journal",
                self.exit_code
            );
            ensure!(
                self.assumptions.is_empty(),
                "Session with exit code {:?} has encoded assumptions",
                self.exit_code
            );
            None
        };

        Ok(ReceiptClaim {
            pre: self.pre_state.clone().into(),
            post: self.post_state.clone().into(),
            exit_code: self.exit_code,
            input: Digest::ZERO,
            output: output.into(),
        })
    }

    /// TODO: write doc
    pub fn get_info(&self) -> SessionInfo {
        SessionInfo {
            segments: self
                .segments
                .iter()
                .map(|segment_ref| {
                    let segment = segment_ref.resolve().unwrap();
                    segment.get_info()
                })
                .collect(),
            public_journal: self.journal.clone().unwrap_or_default(),
            private_journal: self.private_journal.clone(),
            exit_code: self.exit_code,
        }
    }

    /// Log cycle information for this [Session].
    ///
    /// This logs the total and user cycles for this [Session] at the INFO level.
    pub fn log(&self) {
        let cycle_efficiency = self.user_cycles as f64 / self.total_cycles as f64 * 100.0;

        tracing::info!("number of segments: {}", self.segments.len());
        tracing::info!("total cycles: {}", self.total_cycles);
        tracing::info!("user cycles: {}", self.user_cycles);
        tracing::info!("cycle efficiency: {}%", cycle_efficiency as u32);
    }
}

impl Segment {
    /// Create a new [Segment] from its constituent components.
    #[allow(clippy::too_many_arguments)]
    pub(crate) fn new(
        pre_image: Box<MemoryImage>,
        post_state: SystemState,
        output: Option<Output>,
        faults: PageFaults,
        syscalls: Vec<SyscallRecord>,
        exit_code: ExitCode,
        split_insn: Option<u32>,
        po2: u32,
        index: u32,
        cycles: u32,
    ) -> Self {
        tracing::debug!("segment[{index}]> reads: {}, writes: {}, exit_code: {exit_code:?}, split_insn: {split_insn:?}, po2: {po2}, cycles: {cycles}",
            faults.reads.len(),
            faults.writes.len(),
        );
        Self {
            pre_image,
            post_state,
            output,
            faults,
            syscalls,
            exit_code,
            split_insn,
            po2,
            index,
            cycles,
        }
    }

    /// Calculate for the [ReceiptClaim] associated with this [Segment]. The
    /// [ReceiptClaim] is the claim that will be proven if this [Segment]
    /// is passed to the [crate::Prover].
    pub fn get_claim(&self) -> Result<ReceiptClaim> {
        // NOTE: When a segment ends in a Halted(_) state, it may not update the post state
        // digest. As a result, it will be the same as the pre_image. All other exit codes require
        // the post state digest to reflect the final memory state.
        // NOTE: The PC on the the post state is stored "+ 4". See ReceiptClaim for more detail.
        let post_state = SystemState {
            pc: self
                .post_state
                .pc
                .checked_add(WORD_SIZE as u32)
                .context("invalid pc in segment post state")?,
            merkle_root: match self.exit_code {
                ExitCode::Halted(_) => self.pre_image.compute_root_hash()?,
                _ => self.post_state.merkle_root.clone(),
            },
        };

        Ok(ReceiptClaim {
            pre: self.pre_image.get_system_state()?.into(),
            post: post_state.into(),
            exit_code: self.exit_code,
            input: Digest::ZERO,
            output: self.output.clone().into(),
        })
    }

    /// TODO: write doc
    pub fn get_info(&self) -> SegmentInfo {
        SegmentInfo {
            po2: self.po2,
            cycles: self.cycles,
        }
    }
}

/// A very basic implementation of a [SegmentRef].
///
/// The [Segment] itself is stored in this implementation.
#[derive(Clone, Serialize, Deserialize)]
pub struct SimpleSegmentRef {
    segment: Segment,
}

#[typetag::serde]
impl SegmentRef for SimpleSegmentRef {
    fn resolve(&self) -> Result<Segment> {
        Ok(self.segment.clone())
    }
}

impl SimpleSegmentRef {
    /// Construct a [SimpleSegmentRef] with the specified [Segment].
    pub fn new(segment: Segment) -> Self {
        Self { segment }
    }
}

/// A basic implementation of a [SegmentRef] that saves the segment to a file
///
/// The [Segment] is stored in a user-specified file in this implementation,
/// and the SegmentRef holds the filename.
///
/// There is an example of using [FileSegmentRef] in our [EVM example][1]
///
/// [1]: https://github.com/risc0/risc0/blob/main/examples/zkevm-demo/src/main.rs
#[derive(Clone, Serialize, Deserialize)]
pub struct FileSegmentRef {
    path: PathBuf,
}

#[typetag::serde]
impl SegmentRef for FileSegmentRef {
    fn resolve(&self) -> Result<Segment> {
        let contents = fs::read(&self.path)?;
        let segment = bincode::deserialize(&contents)?;
        Ok(segment)
    }
}

impl FileSegmentRef {
    /// Construct a [FileSegmentRef]
    ///
    /// This builds a FileSegmentRef that stores `segment` in a file at `path`.
    pub fn new(segment: &Segment, path: &Path) -> Result<Self> {
        let path = path.join(format!("{}.bincode", segment.index));
        fs::write(&path, bincode::serialize(&segment)?)?;
        Ok(Self { path })
    }
}
