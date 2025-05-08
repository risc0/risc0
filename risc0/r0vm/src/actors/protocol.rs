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

use std::sync::Arc;

use kameo::{
    actor::{ActorID, ActorRef},
    Reply,
};
use risc0_zkvm::{
    Journal, ProveKeccakRequest, ReceiptClaim, Segment, SegmentReceipt, SuccinctReceipt,
    UnionClaim, Unknown,
};
use serde::{Deserialize, Serialize};

use crate::actors::manager::TaskManagerActor;

pub(crate) type TaskId = u64;

#[derive(Serialize, Deserialize)]
pub(crate) struct ProofRequest {
    pub binary: Vec<u8>,
    pub input: Vec<u8>,
}

#[derive(Clone, Copy, Debug, Hash, PartialEq, Eq, Serialize, Deserialize)]
pub(crate) enum TaskKind {
    Execute,
    ProveSegment,
    ProveKeccak,
    Lift,
    Join,
    Union,
    Resolve,
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
    pub binary: Vec<u8>,
    pub input: Vec<u8>,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ProveSegmentTask {
    pub segment: Segment,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ProveKeccakTask {
    pub request: ProveKeccakRequest,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct LiftTask {
    pub receipt: SegmentReceipt,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct JoinTask {
    pub receipts: Vec<SuccinctReceipt<ReceiptClaim>>,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct UnionTask {
    pub receipts: Vec<SuccinctReceipt<Unknown>>,
}

#[derive(Reply, Serialize, Deserialize)]
pub(crate) struct ResolveTask {
    pub conditional: SuccinctReceipt<ReceiptClaim>,
    pub assumption: SuccinctReceipt<Unknown>,
}

pub mod factory {
    use super::*;

    #[derive(Serialize, Deserialize)]
    pub(crate) struct GetTask {
        pub kinds: Vec<TaskKind>,
    }

    #[derive(Clone, Reply)]
    pub(crate) struct SubmitTaskMsg {
        pub task_mgr: ActorRef<TaskManagerActor>,
        pub task_id: TaskId,
        pub task_kind: TaskKind,
        pub task: Task,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct TaskStatusMsg {
        pub job_id: ActorID,
        pub task_id: TaskId,
        pub body: TaskStatus,
    }

    #[derive(Reply, Serialize, Deserialize)]
    pub(crate) struct TaskDoneMsg {
        pub job_id: ActorID,
        pub task_id: TaskId,
        pub body: TaskDone,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) enum TaskStatus {
        Segment(Segment),
        Keccak(ProveKeccakRequest),
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) enum TaskDone {
        Session(Arc<Session>),
        ProveSegment(Arc<SegmentReceipt>),
        ProveKeccak(Arc<SuccinctReceipt<Unknown>>),
        Lift(Arc<SuccinctReceipt<ReceiptClaim>>),
        Join(Arc<SuccinctReceipt<ReceiptClaim>>),
        Union(Arc<SuccinctReceipt<UnionClaim>>),
        Resolve(Arc<SuccinctReceipt<ReceiptClaim>>),
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct SegmentReady {
        pub segment: Segment,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct SessionDone {
        pub session: Session,
    }

    #[derive(Serialize, Deserialize)]
    pub(crate) struct Session {
        pub(crate) segment_count: usize,
        pub(crate) user_cycles: u64,
        pub(crate) total_cycles: u64,
        pub(crate) journal: Option<Journal>,
    }
}

pub mod worker {
    use super::*;

    #[derive(Clone, Reply, Serialize, Deserialize)]
    pub(crate) struct TaskMsg {
        pub job_id: ActorID,
        pub task_id: TaskId,
        pub task_kind: TaskKind,
        pub task: Task,
    }
}
