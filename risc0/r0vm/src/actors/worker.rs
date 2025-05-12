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

use kameo::prelude::*;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, NullSegmentRef, ProverOpts, VerifierContext,
};
use tokio::task::JoinHandle;
use tokio_util::sync::CancellationToken;

use super::{
    factory::FactoryRouterActor,
    protocol::{
        factory::{GetTask, JoinNode, Session, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg},
        worker::TaskMsg,
        ExecuteTask, JoinTask, LiftTask, ProveKeccakTask, ProveSegmentTask, ResolveTask, Task,
        TaskHeader, TaskKind, UnionTask,
    },
};

struct Processor {
    factory: ActorRef<FactoryRouterActor>,
}

pub(crate) struct Worker {
    factory: ActorRef<FactoryRouterActor>,
    task_kinds: Vec<TaskKind>,
    token: CancellationToken,
    join_handle: Option<JoinHandle<()>>,
}

impl Worker {
    pub fn new(factory: ActorRef<FactoryRouterActor>, task_kinds: Vec<TaskKind>) -> Self {
        Self {
            factory,
            task_kinds,
            token: CancellationToken::new(),
            join_handle: None,
        }
    }

    pub fn start(&mut self) {
        if self.join_handle.is_some() {
            return;
        }

        let request = GetTask {
            kinds: self.task_kinds.clone(),
        };
        let factory = self.factory.clone();
        let processor = Processor {
            factory: factory.clone(),
        };
        let token = self.token.clone();
        self.join_handle = Some(tokio::spawn(async move {
            loop {
                let request = request.clone();
                tokio::select! {
                    _ = token.cancelled() => {
                        tracing::info!("stopping");
                        break;
                    }
                    reply = factory.ask(request) => {
                        processor.process_task(reply.unwrap()).await.unwrap();
                    }
                }
            }
        }));
    }

    pub async fn stop(self) {
        if let Some(join_handle) = self.join_handle {
            self.token.cancel();
            join_handle.await.unwrap();
        }
    }
}

impl Processor {
    async fn process_task(&self, msg: TaskMsg) -> anyhow::Result<()> {
        match msg.task {
            Task::Execute(task) => self.execute(msg.header, task).await,
            Task::ProveSegment(task) => self.prove_segment(msg.header, task).await,
            Task::Lift(task) => self.lift(msg.header, task).await,
            Task::Join(task) => self.join(msg.header, task).await,
            Task::ProveKeccak(task) => self.prove_keccak(msg.header, task).await,
            Task::Union(task) => self.union(msg.header, task).await,
            Task::Resolve(task) => self.resolve(msg.header, task).await,
        }
    }

    async fn task_start(&self, header: TaskHeader) -> anyhow::Result<()> {
        self.send_update(header, TaskUpdate::Start).await
    }

    async fn send_update(&self, header: TaskHeader, body: TaskUpdate) -> anyhow::Result<()> {
        Ok(self.factory.tell(TaskUpdateMsg { header, body }).await?)
    }

    async fn send_done(&self, header: TaskHeader, body: TaskDone) -> anyhow::Result<()> {
        Ok(self.factory.tell(TaskDoneMsg { header, body }).await?)
    }

    async fn execute(&self, header: TaskHeader, task: Arc<ExecuteTask>) -> anyhow::Result<()> {
        tracing::info!("ELF: {} bytes", task.binary.len());
        self.task_start(header.clone()).await?;

        let relay = RelayActor::spawn(self.factory.clone());
        let executor = ExecutorActor::spawn_in_thread(relay.clone());

        let msg = ExecuteTaskMsg {
            header: header.clone(),
            task,
        };
        let session = executor.ask(msg).await?;

        relay.stop_gracefully().await?;
        relay.wait_for_stop().await;

        self.send_done(header, TaskDone::Session(Box::new(session)))
            .await?;

        Ok(())
    }

    async fn prove_segment(
        &self,
        header: TaskHeader,
        task: Arc<ProveSegmentTask>,
    ) -> anyhow::Result<()> {
        tracing::info!("ProveSegment: {}", task.segment.index);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let ctx = VerifierContext::default();
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.prove_segment(&ctx, &task.segment)
        })
        .await??;
        self.send_done(header, TaskDone::ProveSegment(Box::new(receipt)))
            .await?;
        Ok(())
    }

    async fn prove_keccak(
        &self,
        header: TaskHeader,
        task: Arc<ProveKeccakTask>,
    ) -> anyhow::Result<()> {
        tracing::info!("ProveKeccak: {}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.prove_keccak(&task.request)
        })
        .await??;
        self.send_done(header, TaskDone::ProveKeccak(Box::new(receipt)))
            .await?;
        Ok(())
    }

    async fn lift(&self, header: TaskHeader, task: Arc<LiftTask>) -> anyhow::Result<()> {
        tracing::info!("Lift: {}", task.receipt.index);
        self.task_start(header.clone()).await?;
        let segment_idx = task.receipt.index;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.lift(&task.receipt)
        })
        .await??;
        self.send_done(
            header,
            TaskDone::Lift(Box::new(JoinNode {
                range: (segment_idx..segment_idx + 1).into(),
                receipt,
            })),
        )
        .await?;
        Ok(())
    }

    async fn join(&self, header: TaskHeader, task: Arc<JoinTask>) -> anyhow::Result<()> {
        let range = task.range;
        tracing::info!("Join: {range:?}");
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.join(&task.receipts[0], &task.receipts[1])
        })
        .await??;
        self.send_done(
            header,
            TaskDone::Join(Box::new(JoinNode { range, receipt })),
        )
        .await?;
        Ok(())
    }

    async fn union(&self, header: TaskHeader, task: Arc<UnionTask>) -> anyhow::Result<()> {
        tracing::info!("Union: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.union(&task.receipts[0], &task.receipts[1])
        })
        .await??;
        self.send_done(header, TaskDone::Union(Box::new(receipt)))
            .await?;
        Ok(())
    }

    async fn resolve(&self, header: TaskHeader, task: Arc<ResolveTask>) -> anyhow::Result<()> {
        tracing::info!("Resolve: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.resolve(&task.conditional, &task.assumption)
        })
        .await??;
        self.send_done(header, TaskDone::Resolve(Box::new(receipt)))
            .await?;
        Ok(())
    }
}

struct ExecuteTaskMsg {
    pub header: TaskHeader,
    pub task: Arc<ExecuteTask>,
}

#[derive(Actor)]
struct ExecutorActor {
    relay: ActorRef<RelayActor>,
}

impl ExecutorActor {
    pub fn spawn_in_thread(relay: ActorRef<RelayActor>) -> ActorRef<Self> {
        spawn_in_thread(Self { relay })
    }
}

impl Message<ExecuteTaskMsg> for ExecutorActor {
    type Reply = anyhow::Result<Session>;

    async fn handle(
        &mut self,
        msg: ExecuteTaskMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let env = ExecutorEnv::builder()
            .write_slice(&msg.task.input)
            .build()?;
        let mut exec = ExecutorImpl::from_elf(env, &msg.task.binary)?;
        let session = exec.run_with_callback(|segment| {
            let msg = TaskUpdateMsg {
                header: msg.header.clone(),
                body: TaskUpdate::Segment(segment),
            };
            self.relay.tell(msg).blocking_send()?;
            Ok(Box::new(NullSegmentRef))
        })?;

        let session = Session {
            segment_count: session.segments.len(),
            user_cycles: session.user_cycles,
            total_cycles: session.total_cycles,
            journal: session.journal,
        };

        Ok(session)
    }
}

#[derive(Actor)]
struct RelayActor {
    factory: ActorRef<FactoryRouterActor>,
}

impl RelayActor {
    pub fn spawn(factory: ActorRef<FactoryRouterActor>) -> ActorRef<Self> {
        spawn(Self { factory })
    }
}

impl Message<TaskUpdateMsg> for RelayActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.factory.tell(msg).await.unwrap();
    }
}

impl Message<TaskDoneMsg> for RelayActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.factory.tell(msg).await.unwrap();
    }
}
