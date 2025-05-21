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

use std::{ops::Range, sync::Arc, time::Duration};

use clap::ValueEnum;
use derive_more::Debug;
use kameo::{actor::ActorRef, Reply};
use risc0_zkvm::{
    AssumptionReceipt, Journal, ProveKeccakRequest, Receipt, ReceiptClaim, Segment, SegmentReceipt,
    SuccinctReceipt, UnionClaim, Unknown,
};
use serde::{Deserialize, Serialize};

use super::job::JobActor;

pub(crate) type JobId = uuid::Uuid;
pub(crate) type TaskId = u64;
pub(crate) type WorkerId = uuid::Uuid;

#[derive(Serialize, Deserialize)]
pub(crate) struct CreateJobRequest {
    pub request: ProofRequest,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct CreateJobReply {
    pub job_id: JobId,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct JobStatusRequest {
    pub job_id: JobId,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct JobStatusReply {
    pub info: Option<JobInfo>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) enum JobStatus {
    Running(String),
    Succeeded(ProofResult),
    Failed(TaskError),
    TimedOut,
    Aborted,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct JobInfo {
    pub status: JobStatus,
    pub elapsed_time: Duration,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct ProofResult {
    pub session: Arc<Session>,
    pub receipt: Arc<Receipt>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ProofRequest {
    pub binary: Vec<u8>,
    pub input: Vec<u8>,
    pub assumptions: Vec<Receipt>,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct Session {
    pub(crate) segment_count: usize,
    pub(crate) user_cycles: u64,
    pub(crate) total_cycles: u64,
    pub(crate) journal: Option<Journal>,
    pub(crate) assumptions: Vec<Arc<AssumptionReceipt>>,
}

#[derive(Clone, Copy, Debug, Hash, PartialEq, Eq, Serialize, Deserialize, ValueEnum)]
pub(crate) enum TaskKind {
    Execute,
    ProveSegment,
    ProveKeccak,
    Lift,
    Join,
    Union,
    Resolve,
}

#[derive(Clone, Copy, Hash, PartialEq, Eq, Serialize, Deserialize)]
pub(crate) struct GlobalId {
    pub job_id: JobId,
    pub task_id: TaskId,
}

#[derive(Clone, Serialize, Deserialize)]
pub(crate) struct TaskHeader {
    pub global_id: GlobalId,
    pub task_kind: TaskKind,
}

#[derive(Clone, Serialize, Deserialize)]
pub(crate) enum Task {
    Execute(Arc<ExecuteTask>),
    ProveSegment(Arc<ProveSegmentTask>),
    ProveKeccak(Arc<ProveKeccakTask>),
    Lift(Arc<LiftTask>),
    Join(Arc<JoinTask>),
    Union(Arc<UnionTask>),
    Resolve(Arc<ResolveTask>),
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ExecuteTask {
    pub request: ProofRequest,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ProveSegmentTask {
    pub segment: Segment,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ProveKeccakTask {
    pub index: usize,
    pub request: ProveKeccakRequest,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Serialize, Deserialize)]
pub(crate) struct SegmentRange {
    pub start: usize,
    pub end: usize,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct LiftTask {
    pub receipt: SegmentReceipt,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct JoinTask {
    pub range: SegmentRange,
    pub receipts: Vec<SuccinctReceipt<ReceiptClaim>>,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct UnionTask {
    pub height: usize,
    pub pos: usize,
    pub receipts: Vec<Arc<SuccinctReceipt<Unknown>>>,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ResolveTask {
    pub conditional: Arc<SuccinctReceipt<ReceiptClaim>>,
    pub assumption: Arc<SuccinctReceipt<Unknown>>,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) enum TaskError {
    Generic(String),
}

pub mod factory {
    use super::*;

    #[derive(Clone, Serialize, Deserialize)]
    pub(crate) struct GetTask {
        pub worker_id: WorkerId,
        pub kinds: Vec<TaskKind>,
    }

    #[derive(Clone, Reply)]
    pub(crate) struct SubmitTaskMsg {
        pub job: ActorRef<JobActor>,
        pub header: TaskHeader,
        pub task: Task,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct TaskUpdateMsg {
        pub header: TaskHeader,
        pub payload: TaskUpdate,
    }

    #[derive(Reply, Serialize, Deserialize)]
    pub(crate) struct TaskDoneMsg {
        pub header: TaskHeader,
        pub payload: Result<TaskDone, TaskError>,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct DropJob {
        pub job_id: JobId,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) enum TaskUpdate {
        Start,
        Segment(Segment),
        Keccak(ProveKeccakRequest),
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) enum TaskDone {
        Session(Arc<Session>),
        ProveSegment(Box<SegmentReceipt>),
        ProveKeccak(Arc<ProveKeccakDone>),
        Lift(Box<JoinNode>),
        Join(Box<JoinNode>),
        Union(Arc<UnionDone>),
        Resolve(Arc<SuccinctReceipt<ReceiptClaim>>),
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct ProveKeccakDone {
        pub index: usize,
        pub receipt: SuccinctReceipt<Unknown>,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct JoinNode {
        pub range: SegmentRange,
        pub receipt: SuccinctReceipt<ReceiptClaim>,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct UnionDone {
        pub height: usize,
        pub pos: usize,
        pub receipt: SuccinctReceipt<UnionClaim>,
    }
}

pub mod worker {
    use super::*;

    #[derive(Clone, Reply, Serialize, Deserialize)]
    pub(crate) struct TaskMsg {
        pub header: TaskHeader,
        pub task: Task,
    }
}

impl From<Range<usize>> for SegmentRange {
    fn from(value: Range<usize>) -> Self {
        Self {
            start: value.start,
            end: value.end,
        }
    }
}

impl From<Range<u32>> for SegmentRange {
    fn from(value: Range<u32>) -> Self {
        Self {
            start: value.start as usize,
            end: value.end as usize,
        }
    }
}

impl Task {
    pub fn kind(&self) -> TaskKind {
        match self {
            Task::Execute(_) => TaskKind::Execute,
            Task::ProveSegment(_) => TaskKind::ProveSegment,
            Task::ProveKeccak(_) => TaskKind::ProveKeccak,
            Task::Lift(_) => TaskKind::Lift,
            Task::Join(_) => TaskKind::Join,
            Task::Union(_) => TaskKind::Union,
            Task::Resolve(_) => TaskKind::Resolve,
        }
    }

    pub fn name(&self) -> &'static str {
        match self {
            Task::Execute(_) => "execute",
            Task::ProveSegment(_) => "prove",
            Task::ProveKeccak(_) => "keccak",
            Task::Lift(_) => "lift",
            Task::Join(_) => "join",
            Task::Union(_) => "union",
            Task::Resolve(_) => "resolve",
        }
    }
}

impl JobStatus {
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
