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

use std::{collections::BTreeSet, fs, path::PathBuf};

use anyhow::{ensure, Result};
use risc0_binfmt::{MemoryImage, SystemState};
use risc0_circuit_rv32im::prove::segment::Segment as CircuitSegment;
use serde::{Deserialize, Serialize};

use crate::{
    host::{
        client::env::{ProveZkrRequest, SegmentPath},
        prove_info::SessionStats,
    },
    sha::Digest,
    Assumption, AssumptionReceipt, Assumptions, ExitCode, Journal, MaybePruned, Output,
    ReceiptClaim,
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
#[non_exhaustive]
pub struct Session {
    /// The constituent [Segment]s of the Session. The final [Segment] will have
    /// an [ExitCode] of [Halted](ExitCode::Halted), [Paused](ExitCode::Paused),
    /// or [SessionLimit](ExitCode::SessionLimit), and all other [Segment]s (if
    /// any) will have [ExitCode::SystemSplit].
    pub segments: Vec<Box<dyn SegmentRef>>,

    /// The input digest.
    pub input: Digest,

    /// The data publicly committed by the guest program.
    pub journal: Option<Journal>,

    /// The [ExitCode] of the session.
    pub exit_code: ExitCode,

    /// The final [MemoryImage] at the end of execution.
    pub post_image: MemoryImage,

    /// The list of assumptions made by the guest and resolved by the host.
    pub assumptions: Vec<(Assumption, AssumptionReceipt)>,

    /// The hooks to be called during the proving phase.
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

    /// A list of pending ZKR proof requests.
    // TODO: make this scalable so we don't OOM
    pub(crate) pending_zkrs: Vec<ProveZkrRequest>,
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
    /// The index of this [Segment] within the [Session]
    pub index: u32,

    pub(crate) inner: CircuitSegment,
    pub(crate) output: Option<Output>,
}

impl Segment {
    /// Give the power of two length of this [Segment]
    ///
    /// If the [Segment]'s execution trace had 2^20 rows, this would return 20.
    pub fn po2(&self) -> usize {
        self.inner.po2
    }
}

/// A reference to a [Segment].
///
/// This allows implementers to determine the best way to represent this in an
/// pluggable manner. See the [SimpleSegmentRef] for a very basic
/// implementation.
pub trait SegmentRef: Send {
    /// Resolve this reference into an actual [Segment].
    fn resolve(&self) -> Result<Segment>;
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
    #[allow(clippy::too_many_arguments)]
    pub(crate) fn new(
        segments: Vec<Box<dyn SegmentRef>>,
        input: Digest,
        journal: Option<Vec<u8>>,
        exit_code: ExitCode,
        post_image: MemoryImage,
        assumptions: Vec<(Assumption, AssumptionReceipt)>,
        user_cycles: u64,
        total_cycles: u64,
        pre_state: SystemState,
        post_state: SystemState,
        pending_zkrs: Vec<ProveZkrRequest>,
    ) -> Self {
        Self {
            segments,
            input,
            journal: journal.map(Journal::new),
            exit_code,
            post_image,
            assumptions,
            hooks: Vec::new(),
            user_cycles,
            total_cycles,
            pre_state,
            post_state,
            pending_zkrs,
        }
    }

    /// Add a hook to be called during the proving phase.
    pub fn add_hook<E: SessionEvents + 'static>(&mut self, hook: E) {
        self.hooks.push(Box::new(hook));
    }

    /// Calculate for the [ReceiptClaim] associated with this [Session]. The
    /// [ReceiptClaim] is the claim that will be proven if this [Session]
    /// is passed to the [crate::Prover].
    pub fn claim(&self) -> Result<ReceiptClaim> {
        // Construct the Output struct for the session, checking internal consistency.
        // NOTE: The Session output is distinct from the final Segment output because in the
        // Session output any proven assumptions are not included.
        self.claim_with_assumptions(self.assumptions.iter().map(|(_, x)| x))
    }

    pub(crate) fn claim_with_assumptions<'a>(
        &self,
        assumptions: impl Iterator<Item = &'a AssumptionReceipt>,
    ) -> Result<ReceiptClaim> {
        let output = if self.exit_code.expects_output() {
            self.journal
                .as_ref()
                .map(|journal| -> Result<_> {
                    Ok(Output {
                        journal: journal.bytes.clone().into(),
                        assumptions: Assumptions(
                            assumptions
                                .filter_map(|x| match x {
                                    AssumptionReceipt::Proven(_) => None,
                                    AssumptionReceipt::Unresolved(a) => Some(a.clone().into()),
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
            input: MaybePruned::Pruned(self.input),
            output: output.into(),
        })
    }

    /// Log cycle information for this [Session].
    ///
    /// This logs the total and user cycles for this [Session] at the INFO level.
    pub fn log(&self) {
        let cycle_efficiency = self.user_cycles as f64 / self.total_cycles as f64 * 100.0;

        tracing::info!("number of segments: {}", self.segments.len());
        tracing::info!("total cycles: {}", self.total_cycles);
        tracing::info!("user cycles: {}", self.user_cycles);
        tracing::debug!("cycle efficiency: {}%", cycle_efficiency as u32);
    }

    /// Returns stats for the session
    ///
    /// This contains cycle and segment information about the session useful for debugging and measuring performance.
    pub fn stats(&self) -> SessionStats {
        SessionStats {
            segments: self.segments.len(),
            total_cycles: self.total_cycles,
            user_cycles: self.user_cycles,
        }
    }
}

/// Implementation of a [SegmentRef] that does not save the segment.
///
/// This is useful for DevMode where the segments aren't needed.
#[derive(Serialize, Deserialize)]
pub struct NullSegmentRef;

impl SegmentRef for NullSegmentRef {
    fn resolve(&self) -> anyhow::Result<Segment> {
        unimplemented!()
    }
}

pub fn null_callback(_: Segment) -> Result<Box<dyn SegmentRef>> {
    Ok(Box::new(NullSegmentRef))
}

/// A very basic implementation of a [SegmentRef].
///
/// The [Segment] itself is stored in this implementation.
#[derive(Clone, Serialize, Deserialize)]
pub struct SimpleSegmentRef {
    segment: Segment,
}

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
pub struct FileSegmentRef {
    path: PathBuf,
    _dir: SegmentPath,
}

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
    pub fn new(segment: &Segment, dir: &SegmentPath) -> Result<Self> {
        let path = dir.path().join(format!("{}.bincode", segment.index));
        fs::write(&path, bincode::serialize(&segment)?)?;
        Ok(Self {
            path,
            _dir: dir.clone(),
        })
    }
}
