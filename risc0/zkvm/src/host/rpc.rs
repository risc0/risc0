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

use std::{sync::Arc, time::Duration};

use derive_more::From;
use serde::{Deserialize, Serialize};

use crate::{
    AssumptionReceipt, ExitCode, Journal, Receipt, ReceiptClaim, SegmentInfo, SessionInfo,
    SessionStats,
};

/// Request to start a proof job.
#[derive(Serialize, Deserialize)]
pub struct ProofRequest {
    /// Program binary to be proved.
    pub binary: Vec<u8>,

    /// Serialized input for the guest program.
    pub input: Vec<u8>,

    /// Assumption receipts required by the proof.
    pub assumptions: Vec<AssumptionReceipt>,

    /// Optional segment size limit as log2 (po2).
    pub segment_limit_po2: Option<u32>,

    /// If true, execute without generating a receipt.
    pub execute_only: bool,
}

/// Supported shrink-wrap proof kinds.
#[derive(Copy, Clone, Debug, Serialize, Deserialize)]
pub enum ShrinkWrapKind {
    /// Groth16 proof format.
    Groth16,
}

/// Request to shrink-wrap a receipt.
#[derive(Serialize, Deserialize)]
pub struct ShrinkWrapRequest {
    /// Desired shrink-wrap kind.
    pub kind: ShrinkWrapKind,
    /// Receipt to shrink-wrap.
    pub receipt: Receipt,
}

/// Union of supported job requests.
#[allow(clippy::large_enum_variant)]
#[derive(Serialize, Deserialize, From)]
pub enum JobRequest {
    /// Start a proof job.
    Proof(ProofRequest),
    /// Perform receipt shrink-wrapping.
    ShrinkWrap(ShrinkWrapRequest),
}

/// Status metadata for a submitted job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct JobInfo<JobResultT> {
    /// Current status of the job.
    pub status: JobStatus<JobResultT>,

    /// Time elapsed since the job started.
    pub elapsed_time: Duration,
}

/// Execution status of a job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum JobStatus<JobResultT> {
    /// In progress with a status message.
    Running(String),

    /// Completed successfully with a result.
    Succeeded(JobResultT),

    /// Failed with an error.
    Failed(TaskError),

    /// Job exceeded its time limit.
    TimedOut,

    /// Aborted before completion.
    Aborted,
}

/// Result payload for a proof job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ProofResult {
    /// Execution session details.
    pub session: Arc<Session>,

    /// Proof receipt if generated.
    pub receipt: Option<Arc<Receipt>>,
}

/// Result payload for a shrink-wrap job.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ShrinkWrapResult {
    /// Shrink-wrapped receipt.
    pub receipt: Arc<Receipt>,
}

/// Summary of an execution session.
#[derive(Debug, Serialize, Deserialize)]
pub struct Session {
    /// Aggregated execution statistics.
    pub stats: SessionStats,

    /// Program journal, if any.
    pub journal: Option<Journal>,

    /// Assumption receipts referenced by this session.
    pub assumptions: Vec<Arc<AssumptionReceipt>>,

    /// Execution segments.
    pub segments: Vec<SegmentInfo>,

    /// Guest exit code.
    pub exit_code: ExitCode,

    /// Receipt claim produced by the session.
    pub receipt_claim: ReceiptClaim,
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

/// Error type for job execution.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum TaskError {
    /// Generic error message.
    Generic(String),
}

impl<JobResultT> JobStatus<JobResultT> {
    /// Returns a Bonsai-compatible status string.
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

