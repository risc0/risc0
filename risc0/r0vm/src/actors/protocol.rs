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

use std::{fmt, ops::Range, sync::Arc};

use clap::ValueEnum;
use derive_more::{Debug, From, TryInto};
use risc0_zkvm::{
    ProveKeccakRequest, Receipt, ReceiptClaim, Segment, SegmentReceipt, SuccinctReceipt,
    UnionClaim, Unknown,
};
use serde::{Deserialize, Serialize};

use super::{RemoteWorkerActor, actor::ActorRef};

pub use risc0_zkvm::rpc::{
    JobInfo, JobRequest, JobStatus, ProofRequest, ProofResult, Session, ShrinkWrapKind,
    ShrinkWrapRequest, ShrinkWrapResult, TaskError,
};

pub(crate) type JobId = uuid::Uuid;
pub(crate) type TaskId = u64;
pub(crate) type WorkerId = uuid::Uuid;

pub struct WorkerIdFmt(pub WorkerId);

impl fmt::Display for WorkerIdFmt {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        if f.alternate() {
            let worker_id = self.0.to_string();
            let short_id = &worker_id[worker_id.len() - 5..];
            write!(f, "WID-{short_id}")
        } else {
            write!(f, "WID-{}", &self.0)
        }
    }
}

/// This is an async message that should return immediately to the API.
///
/// The API is designed to have users poll for status, but the initial request
/// must return immediately.
#[derive(Serialize, Deserialize)]
pub(crate) struct CreateJobRequest {
    pub request: JobRequest,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct CreateJobReply {
    pub job_id: JobId,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct JobStatusRequest {
    pub job_id: JobId,
}

#[derive(Serialize, Deserialize, Debug, Clone)]
pub(crate) struct JobRequestReply {
    pub job_id: JobId,
    pub status: JobStatusReply,
}

#[derive(Serialize, Deserialize, TryInto, Debug, Clone, From)]
pub(crate) enum JobStatusReply {
    Proof(JobInfo<ProofResult>),
    ShrinkWrap(JobInfo<ShrinkWrapResult>),
    #[try_into(ignore)]
    #[from(ignore)]
    NotFound,
}

#[derive(Clone, Copy, Debug, Hash, PartialEq, Eq, Serialize, Deserialize, ValueEnum)]
#[serde(rename_all = "kebab-case")]
pub(crate) enum TaskKind {
    Execute,
    ProveSegment,
    ProveKeccak,
    Lift,
    Join,
    Union,
    Resolve,
    ShrinkWrap,
}

#[derive(Clone, Copy, Debug, Hash, PartialEq, Eq, Serialize, Deserialize)]
pub(crate) struct GlobalId {
    pub job_id: JobId,
    pub task_id: TaskId,
}

impl fmt::Display for GlobalId {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "TASK-{}:{}", &self.job_id, &self.task_id)
    }
}

#[derive(Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
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
    ShrinkWrap(Arc<ShrinkWrapTask>),
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ExecuteTask {
    pub request: ProofRequest,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ProveSegmentTask {
    pub segment: Segment,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ProveKeccakTask {
    pub index: usize,
    pub request: ProveKeccakRequest,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord, Serialize, Deserialize)]
pub(crate) struct SegmentRange {
    pub start: usize,
    pub end: usize,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct LiftTask {
    pub receipt: SegmentReceipt,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct JoinTask {
    pub range: SegmentRange,
    pub receipts: Vec<SuccinctReceipt<ReceiptClaim>>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct UnionTask {
    pub height: usize,
    pub pos: usize,
    pub receipts: Vec<Arc<SuccinctReceipt<Unknown>>>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ResolveTask {
    pub conditional: Arc<SuccinctReceipt<ReceiptClaim>>,
    pub assumption: Arc<SuccinctReceipt<Unknown>>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct ShrinkWrapTask {
    pub kind: ShrinkWrapKind,
    pub receipt: Arc<Receipt>,
}

pub mod factory {
    use super::*;
    use crate::actors::actor::Actor;

    #[derive(Clone, Serialize, Deserialize)]
    #[serde(bound = "")]
    pub(crate) struct GetTasks<WorkerT: Actor = RemoteWorkerActor> {
        pub worker_id: WorkerId,
        #[serde(skip)]
        pub worker: Option<ActorRef<WorkerT>>,
        pub kinds: Vec<TaskKind>,
    }

    #[derive(Clone)]
    pub(crate) struct SubmitTaskMsg<JobT: Actor> {
        pub job: ActorRef<JobT>,
        pub header: TaskHeader,
        pub task: Task,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct TaskUpdateMsg {
        pub header: TaskHeader,
        pub payload: TaskUpdate,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct TaskDoneMsg {
        pub header: TaskHeader,
        pub payload: Result<TaskDone, TaskError>,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct DropJob {
        pub job_id: JobId,
    }

    #[allow(clippy::large_enum_variant)]
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
        ShrinkWrap(Arc<Receipt>),
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
    use super::{Task, TaskHeader};
    use crate::actors::allocator::{CpuCores, GpuTokens};
    use serde::{Deserialize, Serialize};

    #[derive(Clone, Serialize, Deserialize)]
    pub(crate) struct TaskMsg {
        pub header: TaskHeader,
        pub task: Task,
        pub gpu_tokens: GpuTokens,
        pub cores: CpuCores,
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
            Task::ShrinkWrap(_) => TaskKind::ShrinkWrap,
        }
    }
}
