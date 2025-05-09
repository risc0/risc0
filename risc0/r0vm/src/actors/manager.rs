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

use std::{collections::BTreeMap, error::Error as StdError, path::Path, sync::Arc};

use kameo::prelude::*;
use risc0_zkvm::{
    ProveKeccakRequest, ReceiptClaim, Segment, SegmentReceipt, SuccinctReceipt, UnionClaim, Unknown,
};

use crate::{
    actors::{
        factory::FactoryActor,
        protocol::{
            factory::{
                JoinNode, Session, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskStatus, TaskStatusMsg,
            },
            ExecuteTask, JoinTask, LiftTask, ProofRequest, ProveKeccakTask, ProveSegmentTask,
            SegmentRange, Task, TaskKind,
        },
    },
    Cli,
};

pub(crate) async fn main(_args: &Cli, path: &Path) -> Result<(), Box<dyn StdError>> {
    let addr = "/ip4/0.0.0.0/udp/9000/quic-v1".parse()?;
    println!("addr: {addr}");

    ActorSwarm::bootstrap()?.listen_on(addr).await?;

    let factory = kameo::spawn(FactoryActor::new());
    factory.register("factory").await?;

    let task_mgr = kameo::spawn(TaskManagerActor::new(factory.clone()));

    let binary = std::fs::read(path)?;
    task_mgr
        .tell(ProofRequest {
            binary,
            input: vec![],
        })
        .await
        .unwrap();
    task_mgr.wait_for_stop().await;

    factory.wait_for_stop().await;

    Ok(())
}

#[derive(Actor, RemoteActor)]
pub(crate) struct TaskManagerActor {
    factory: ActorRef<FactoryActor>,
    joins: BTreeMap<SegmentRange, Arc<SuccinctReceipt<ReceiptClaim>>>,
    next_task_id: u64,
    session: Option<Arc<Session>>,
}

impl TaskManagerActor {
    pub fn new(factory: ActorRef<FactoryActor>) -> Self {
        Self {
            factory,
            joins: BTreeMap::new(),
            next_task_id: 0,
            session: None,
        }
    }

    fn next_task_id(&mut self) -> u64 {
        self.next_task_id += 1;
        self.next_task_id
    }

    async fn prove_segment(&mut self, task_mgr: ActorRef<Self>, segment: Segment) {
        tracing::info!("ProveSegment: {:?}", segment.index);
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::ProveSegment,
            task: Task::ProveSegment(Arc::new(ProveSegmentTask { segment })),
        };
        self.factory.tell(task).await.unwrap();
    }

    async fn prove_keccak(&mut self, task_mgr: ActorRef<Self>, request: ProveKeccakRequest) {
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::ProveKeccak,
            task: Task::ProveKeccak(Arc::new(ProveKeccakTask { request })),
        };
        self.factory.tell(task).await.unwrap();
    }

    async fn session_done(&mut self, task_mgr: ActorRef<Self>, session: Arc<Session>) {
        tracing::info!("SessionDone");
        self.session = Some(session);
        self.maybe_finish(task_mgr).await;
    }

    async fn prove_segment_done(&mut self, task_mgr: ActorRef<Self>, receipt: Arc<SegmentReceipt>) {
        tracing::info!("ProveSegmentDone: {:?}", receipt.index);
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::Lift,
            task: Task::Lift(Arc::new(LiftTask {
                receipt: Arc::into_inner(receipt).unwrap(),
            })),
        };
        self.factory.tell(task).await.unwrap();
    }

    async fn prove_keccak_done(
        &mut self,
        _task_mgr: ActorRef<Self>,
        _receipt: Arc<SuccinctReceipt<Unknown>>,
    ) {
        // Union MMR
        todo!()
    }

    async fn lift_done(&mut self, task_mgr: ActorRef<Self>, node: Arc<JoinNode>) {
        tracing::info!("LiftDone: {:?}", node.range);
        let node = Arc::into_inner(node).unwrap();
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join(task_mgr.clone()).await;
        self.maybe_finish(task_mgr).await;
    }

    async fn join_done(&mut self, task_mgr: ActorRef<Self>, node: Arc<JoinNode>) {
        tracing::info!("JoinDone: {:?}", node.range);
        let node = Arc::into_inner(node).unwrap();
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join(task_mgr.clone()).await;
        self.maybe_finish(task_mgr).await;
    }

    async fn union_done(
        &mut self,
        _task_mgr: ActorRef<Self>,
        _receipt: Arc<SuccinctReceipt<UnionClaim>>,
    ) {
        todo!()
    }

    async fn resolve_done(
        &mut self,
        _task_mgr: ActorRef<Self>,
        _receipt: Arc<SuccinctReceipt<ReceiptClaim>>,
    ) {
        todo!()
    }

    async fn maybe_join(&mut self, task_mgr: ActorRef<Self>) {
        if let Some(((a_range, a_receipt), (b_range, b_receipt))) = self
            .joins
            .iter()
            .zip(self.joins.iter().skip(1))
            .filter(|((a, _), (b, _))| a.end == b.start)
            .map(|((a_range, a_receipt), (b_range, b_receipt))| {
                ((*a_range, a_receipt.clone()), (*b_range, b_receipt.clone()))
            })
            .take(1)
            .next()
        {
            self.joins.remove(&a_range);
            self.joins.remove(&b_range);
            let range = (a_range.start..b_range.end).into();
            self.join(
                task_mgr,
                range,
                vec![(*a_receipt).clone(), (*b_receipt).clone()],
            )
            .await;
        }
    }

    async fn join(
        &mut self,
        task_mgr: ActorRef<Self>,
        range: SegmentRange,
        receipts: Vec<SuccinctReceipt<ReceiptClaim>>,
    ) {
        tracing::info!("join: {range:?}");
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::Join,
            task: Task::Join(Arc::new(JoinTask { range, receipts })),
        };
        self.factory.tell(task).await.unwrap();
    }

    async fn maybe_finish(&mut self, task_mgr: ActorRef<Self>) {
        if let Some(ref session) = self.session {
            tracing::info!("maybe_finish: session done");
            if let Some((range, _receipt)) = self.joins.first_key_value() {
                if range.start == 0 && range.end == session.segment_count {
                    tracing::info!("maybe_finish: complete range");
                    task_mgr.stop_gracefully().await.unwrap();
                }
            }
        }
    }
}

impl Message<ProofRequest> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("ProofRequest");
        let task = SubmitTaskMsg {
            task_mgr: ctx.actor_ref(),
            task_id: self.next_task_id(),
            task_kind: TaskKind::Execute,
            task: Task::Execute(Arc::new(ExecuteTask {
                binary: msg.binary,
                input: msg.input,
            })),
        };
        self.factory.tell(task).await.unwrap();
    }
}

impl Message<TaskStatusMsg> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskStatusMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("TaskStatusMsg: {:?}", msg.task_id);
        let task_mgr = ctx.actor_ref();
        match msg.body {
            TaskStatus::Segment(segment) => self.prove_segment(task_mgr, segment).await,
            TaskStatus::Keccak(request) => self.prove_keccak(task_mgr, request).await,
        }
    }
}

impl Message<TaskDoneMsg> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("TaskDoneMsg: {:?}", msg.task_id);
        let task_mgr = ctx.actor_ref();
        match msg.body {
            TaskDone::Session(session) => self.session_done(task_mgr, session).await,
            TaskDone::ProveSegment(receipt) => self.prove_segment_done(task_mgr, receipt).await,
            TaskDone::ProveKeccak(receipt) => self.prove_keccak_done(task_mgr, receipt).await,
            TaskDone::Lift(node) => self.lift_done(task_mgr, node).await,
            TaskDone::Join(node) => self.join_done(task_mgr, node).await,
            TaskDone::Union(receipt) => self.union_done(task_mgr, receipt).await,
            TaskDone::Resolve(receipt) => self.resolve_done(task_mgr, receipt).await,
        }
    }
}
