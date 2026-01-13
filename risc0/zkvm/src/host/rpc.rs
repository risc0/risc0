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

use std::{sync::Arc, time::Duration};

use derive_more::From;
use serde::{Deserialize, Serialize};

use crate::{
    AssumptionReceipt, ExitCode, Journal, Receipt, ReceiptClaim, SegmentInfo, SessionInfo,
    SessionStats,
};

/// Request to execute/prove a guest ELF via the zkVM RPC interface.
///
/// This is primarily used by host-side clients that delegate execution/proving to a prover service
/// (e.g. the `r0vm` cluster used by `DefaultProver`).
#[derive(Serialize, Deserialize)]
pub struct ProofRequest {
    /// Guest program ELF bytes.
    pub binary: Vec<u8>,

    /// Serialized executor input.
    pub input: Vec<u8>,

    /// Assumption receipts that the proof may rely on.
    pub assumptions: Vec<AssumptionReceipt>,

    /// Optional segment limit (log2) to use for execution/proving.
    pub segment_limit_po2: Option<u32>,

    /// If `true`, execute without producing a proof/receipt (only session info).
    pub execute_only: bool,

    /// If `true`, allow dev-mode behavior in the prover service.
    pub dev_mode: bool,
}

/// Kind of shrink-wrapping requested for a receipt.
#[derive(Copy, Clone, Debug, Serialize, Deserialize)]
pub enum ShrinkWrapKind {
    /// Convert the receipt to a Groth16-based succinct receipt.
    Groth16,
}

/// Request to convert an existing receipt into a shrink-wrapped form.
#[derive(Serialize, Deserialize)]
pub struct ShrinkWrapRequest {
    /// The shrink-wrapping mode to apply.
    pub kind: ShrinkWrapKind,
    /// The receipt to shrink-wrap.
    pub receipt: Receipt,
    /// If `true`, allow dev-mode behavior in the prover service.
    pub dev_mode: bool,
}

/// A top-level request accepted by the zkVM prover RPC service.
#[allow(clippy::large_enum_variant)]
#[derive(Serialize, Deserialize, From)]
pub enum JobRequest {
    /// Run a proof (or execute-only) job.
    Proof(ProofRequest),
    /// Shrink-wrap an existing receipt.
    ShrinkWrap(ShrinkWrapRequest),
}

/// Metadata about an RPC job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct JobInfo<JobResultT> {
    /// Current job status (running/succeeded/failed/etc).
    pub status: JobStatus<JobResultT>,

    /// Total elapsed time for the job, as measured by the prover service.
    pub elapsed_time: Duration,
}

/// Status of an RPC job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum JobStatus<JobResultT> {
    /// The job is still running; includes an optional progress message.
    Running(String),

    /// The job completed successfully and produced a result.
    Succeeded(JobResultT),

    /// The job failed with an error returned by the prover service.
    Failed(TaskError),

    /// The job exceeded its allowed time budget.
    TimedOut,

    /// The job was aborted (e.g. by cancellation/shutdown).
    Aborted,
}

/// Result of executing/proving a guest program via RPC.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ProofResult {
    /// Session information (stats, journal, etc) produced by execution.
    pub session: Arc<Session>,

    /// Optional receipt produced by proving.
    ///
    /// When `ProofRequest::execute_only` is `true`, this will typically be `None`.
    pub receipt: Option<Arc<Receipt>>,
}

/// Result of shrinking-wrapping a receipt via RPC.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ShrinkWrapResult {
    /// The shrink-wrapped receipt.
    pub receipt: Arc<Receipt>,
}

/// Session data returned by the prover service for an execution/proving job.
#[derive(Debug, Serialize, Deserialize)]
pub struct Session {
    /// Execution statistics.
    pub stats: SessionStats,

    /// Optional journal output.
    pub journal: Option<Journal>,

    /// Receipts assumed during execution/proving.
    pub assumptions: Vec<Arc<AssumptionReceipt>>,

    /// Segment information for the session.
    pub segments: Vec<SegmentInfo>,

    /// Guest exit code.
    pub exit_code: ExitCode,

    /// Receipt claim produced by execution.
    pub receipt_claim: ReceiptClaim,

    /// Captured guest stdout bytes.
    pub stdout: Vec<u8>,
}

impl From<Session> for SessionInfo {
    fn from(s: Session) -> Self {
        Self {
            segments: s.segments,
            journal: s.journal.unwrap_or_default(),
            exit_code: s.exit_code,
            receipt_claim: Some(s.receipt_claim),
        }
    }
}

/// Error returned by a task executed in the prover service.
#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum TaskError {
    /// A generic error message.
    Generic(String),
}

impl<JobResultT> JobStatus<JobResultT> {
    /// Returns a status string compatible with Bonsai-style job statuses.
    pub fn bonsai_status(&self) -> &str {
        match self {
            JobStatus::Running(_) => "RUNNING",
            JobStatus::Succeeded(_) => "SUCCEEDED",
            JobStatus::Failed(_) => "FAILED",
            JobStatus::TimedOut => "TIMED_OUT",
            JobStatus::Aborted => "ABORTED",
        }
    }
}

impl From<anyhow::Error> for TaskError {
    fn from(value: anyhow::Error) -> Self {
        Self::Generic(value.to_string())
    }
}
