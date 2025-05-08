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

#![allow(unused)]

use std::{collections::VecDeque, error::Error as StdError, path::Path, sync::Arc};

use kameo::prelude::*;
use risc0_zkvm::{ProveKeccakRequest, Segment, SegmentReceipt};

use crate::{
    actors::{
        factory::FactoryActor,
        protocol::{
            factory::{
                SegmentReady, SessionDone, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskStatus,
                TaskStatusMsg,
            },
            ExecuteTask, LiftTask, ProofRequest, ProveKeccakTask, ProveSegmentTask, Task, TaskKind,
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
        .await;

    task_mgr.wait_for_stop().await;

    factory.wait_for_stop().await;

    Ok(())
}

#[derive(Actor, RemoteActor)]
pub(crate) struct TaskManagerActor {
    factory: ActorRef<FactoryActor>,
    segments: VecDeque<Segment>,
    next_task_id: u64,
}

impl TaskManagerActor {
    pub fn new(factory: ActorRef<FactoryActor>) -> Self {
        Self {
            factory,
            segments: VecDeque::new(),
            next_task_id: 0,
        }
    }

    fn next_task_id(&mut self) -> u64 {
        self.next_task_id += 1;
        self.next_task_id
    }

    async fn prove_segment(&mut self, task_mgr: ActorRef<Self>, segment: Segment) {
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::ProveSegment,
            task: Task::ProveSegment(Arc::new(ProveSegmentTask { segment })),
        };
        self.factory.tell(task).await;
    }

    async fn prove_segment_done(&mut self, task_mgr: ActorRef<Self>, receipt: SegmentReceipt) {
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::Lift,
            task: Task::Lift(Arc::new(LiftTask { receipt })),
        };
        self.factory.tell(task).await;
    }

    async fn prove_keccak(&mut self, task_mgr: ActorRef<Self>, request: ProveKeccakRequest) {
        let task = SubmitTaskMsg {
            task_mgr,
            task_id: self.next_task_id(),
            task_kind: TaskKind::ProveKeccak,
            task: Task::ProveKeccak(Arc::new(ProveKeccakTask { request })),
        };
        self.factory.tell(task).await;
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
        self.factory.tell(task).await;
    }
}

impl Message<TaskStatusMsg> for TaskManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskStatusMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("TaskStatusMsg");
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
        tracing::info!("TaskDoneMsg");
        match msg.body {
            TaskDone::Session(session) => todo!(),
            TaskDone::ProveSegment(receipt) => {
                self.prove_segment_done(ctx.actor_ref(), receipt.as_ref().clone())
                    .await
            }
            TaskDone::ProveKeccak(receipt) => todo!(),
            TaskDone::Lift(receipt) => todo!(),
            TaskDone::Join(receipt) => todo!(),
            TaskDone::Union(receipt) => todo!(),
            TaskDone::Resolve(receipt) => todo!(),
        }
    }
}
