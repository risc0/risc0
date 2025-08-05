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

//! This module defines [Session] and [Segment] which provides a way to share
//! execution traces between the execution phase and the proving phase.

use std::{collections::BTreeSet, fs, path::PathBuf};

use anyhow::{ensure, Context, Result};
use enum_map::EnumMap;
use risc0_binfmt::{PovwJobId, SystemState};
use risc0_circuit_keccak::{compute_keccak_digest, KECCAK_CONTROL_ROOT};
use risc0_circuit_rv32im::{execute::EcallMetric, TerminateState};
use serde::{Deserialize, Serialize};

use crate::{
    host::{
        client::env::{ProveKeccakRequest, SegmentPath},
        prove_info::SessionStats,
    },
    mmr::{GuestPeak, MerkleMountainAccumulator},
    sha::Digest,
    Assumption, AssumptionReceipt, Assumptions, ExitCode, Journal, MaybePruned, Output,
    ReceiptClaim, Work,
};

use super::exec::syscall::{SyscallKind, SyscallMetric};

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

    /// The list of assumptions made by the guest and resolved by the host.
    pub assumptions: Vec<(Assumption, AssumptionReceipt)>,

    /// The list of assumptions made by the guest and resolved by the host in an mmr.
    pub mmr_assumptions: Vec<AssumptionReceipt>,

    /// The hooks to be called during the proving phase.
    pub hooks: Vec<Box<dyn SessionEvents>>,

    /// The number of user cycles without any overhead for continuations or po2
    /// padding.
    pub user_cycles: u64,

    /// The number of cycles needed for paging operations.
    pub paging_cycles: u64,

    /// The number of cycles needed for the proof system which includes padding
    /// up to the nearest power of 2.
    pub reserved_cycles: u64,

    /// Total number of cycles that a prover experiences. This includes overhead
    /// associated with continuations and padding up to the nearest power of 2.
    pub total_cycles: u64,

    /// The system state of the initial MemoryImage.
    pub pre_state: SystemState,

    /// The system state of the final MemoryImage at the end of execution.
    pub post_state: SystemState,

    /// A list of pending keccak proof requests.
    // TODO: make this scalable so we don't OOM
    pub(crate) pending_keccaks: Vec<ProveKeccakRequest>,

    /// ecall metrics grouped by name.
    pub(crate) ecall_metrics: Vec<(String, EcallMetric)>,

    /// syscall metrics grouped by kind.
    pub(crate) syscall_metrics: EnumMap<SyscallKind, SyscallMetric>,

    /// Optional PoVW job identifier for tracking verifiable work.
    pub(crate) povw_job_id: Option<PovwJobId>,
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

    pub(crate) inner: risc0_circuit_rv32im::execute::Segment,

    pub(crate) output: Option<Output>,
}

impl Segment {
    /// Give the power of two length of this [Segment]
    ///
    /// If the [Segment]'s execution trace had 2^20 rows, this would return 20.
    pub fn po2(&self) -> usize {
        self.inner.po2 as usize
    }

    pub(crate) fn user_cycles(&self) -> u32 {
        self.inner.suspend_cycle
    }
}

/// The results of running preflight on a [Segment].
pub struct PreflightResults {
    pub(crate) inner: risc0_circuit_rv32im::prove::PreflightResults,

    pub(crate) terminate_state: Option<TerminateState>,
    pub(crate) output: Option<Output>,
    pub(crate) segment_index: u32,
}

impl PreflightResults {
    /// The index of the [Segment] this [PreflightResults] came from.
    pub fn segment_index(&self) -> u32 {
        self.segment_index
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
        let output = if self.exit_code.expects_output() {
            self.journal
                .as_ref()
                .map(|journal| -> Result<_> {
                    Ok(Output {
                        journal: journal.bytes.clone().into(),
                        assumptions: self
                            .unresolved_assumptions()
                            .context("failed to compute unresolved_assumptions")?
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

    fn keccak_root_assumption(&self) -> Result<Option<Assumption>> {
        let mut keccak_receipts = MerkleMountainAccumulator::<GuestPeak>::new();
        for proof_request in self.pending_keccaks.iter() {
            let claim = compute_keccak_digest(bytemuck::cast_slice(proof_request.input.as_slice()));
            tracing::debug!("adding keccak assumption: {}", claim);
            keccak_receipts.insert(Assumption {
                claim,
                control_root: KECCAK_CONTROL_ROOT,
            })?;
        }

        if !keccak_receipts.is_empty() {
            let root_assumption = keccak_receipts.root()?;
            tracing::debug!("keccak root assumption for session: {:?}", root_assumption);
            return Ok(Some(root_assumption));
        }
        Ok(None)
    }

    fn unresolved_assumptions(&self) -> Result<Assumptions> {
        let keccak_root_assumption = self
            .keccak_root_assumption()
            .context("failed to compute keccak root assumption")?;
        Ok(self
            .assumptions
            .iter()
            .filter_map(|(_, receipt)| match receipt {
                AssumptionReceipt::Proven(_) => None,
                AssumptionReceipt::Unresolved(assumption) => {
                    if let Some(ref keccak) = keccak_root_assumption {
                        if keccak == assumption {
                            return None;
                        }
                    }
                    Some(assumption.clone())
                }
            })
            .collect::<Vec<_>>()
            .into())
    }

    /// Returns the work value for this session if PoVW tracking is enabled.
    pub fn work(&self) -> Option<Work> {
        self.povw_job_id.map(|povw_job_id| Work {
            nonce_min: povw_job_id.nonce(0),
            nonce_max: povw_job_id.nonce(self.segments.len() as u32),
            value: self.total_cycles,
        })
    }

    /// Log cycle information for this [Session].
    ///
    /// This logs the total and user cycles for this [Session] at the INFO level.
    pub fn log(&self) {
        if std::env::var_os("RISC0_INFO").is_none() {
            return;
        }

        let pct = |cycles: u64| cycles as f64 / self.total_cycles as f64 * 100.0;

        tracing::info!("number of segments: {}", self.segments.len());
        tracing::info!("{} total cycles", self.total_cycles);
        tracing::info!(
            "{} user cycles ({:.2}%)",
            self.user_cycles,
            pct(self.user_cycles)
        );
        tracing::info!(
            "{} paging cycles ({:.2}%)",
            self.paging_cycles,
            pct(self.paging_cycles)
        );
        tracing::info!(
            "{} reserved cycles ({:.2}%)",
            self.reserved_cycles,
            pct(self.reserved_cycles)
        );

        tracing::info!("ecalls");
        let mut ecall_metrics = self.ecall_metrics.clone();
        ecall_metrics.sort_by(|a, b| a.1.cycles.cmp(&b.1.cycles));
        for (name, metric) in ecall_metrics.iter().rev() {
            tracing::info!(
                "\t{} {name} calls, {} cycles, ({:.2}%)",
                metric.count,
                metric.cycles,
                pct(metric.cycles)
            );
        }

        tracing::info!("syscalls");
        let mut syscall_metrics: Vec<_> = self.syscall_metrics.iter().collect();
        syscall_metrics.sort_by(|a, b| a.1.count.cmp(&b.1.count));
        for (name, metric) in syscall_metrics.iter().rev() {
            tracing::info!("\t{} {name:?} calls", metric.count);
        }
    }

    /// Returns stats for the session
    ///
    /// This contains cycle and segment information about the session useful for debugging and measuring performance.
    pub fn stats(&self) -> SessionStats {
        SessionStats {
            segments: self.segments.len(),
            total_cycles: self.total_cycles,
            user_cycles: self.user_cycles,
            paging_cycles: self.paging_cycles,
            reserved_cycles: self.reserved_cycles,
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
