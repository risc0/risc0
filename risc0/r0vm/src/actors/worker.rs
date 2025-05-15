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

use anyhow::Context;
use kameo::prelude::*;
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, NullSegmentRef, ProverOpts, VerifierContext,
};
use tokio::task::JoinHandle;
use tokio_util::sync::CancellationToken;

use super::{
    factory::FactoryRouterActor,
    protocol::{
        factory::{GetTask, JoinNode, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg},
        worker::TaskMsg,
        ExecuteTask, JoinTask, LiftTask, ProveKeccakTask, ProveSegmentTask, ResolveTask, Session,
        Task, TaskError, TaskHeader, TaskKind, UnionTask,
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
                        processor.process_task(reply).await;
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

impl From<anyhow::Error> for TaskError {
    fn from(value: anyhow::Error) -> Self {
        Self::Generic(value.to_string())
    }
}

impl Processor {
    async fn process_task(&self, msg: Result<TaskMsg, SendError<GetTask, SendError<GetTask>>>) {
        let msg = match msg {
            Ok(msg) => msg,
            Err(err) => {
                tracing::error!("GetTask reply error: {err}");
                return;
            }
        };
        let header = msg.header.clone();
        let result = match msg.task {
            Task::Execute(task) => self.execute(msg.header, task).await,
            Task::ProveSegment(task) => self.prove_segment(msg.header, task).await,
            Task::Lift(task) => self.lift(msg.header, task).await,
            Task::Join(task) => self.join(msg.header, task).await,
            Task::ProveKeccak(task) => self.prove_keccak(msg.header, task).await,
            Task::Union(task) => self.union(msg.header, task).await,
            Task::Resolve(task) => self.resolve(msg.header, task).await,
        };
        let result = self.send_done(header, result).await;
        if let Err(err) = result {
            tracing::error!("Failed to send error: {err}");
        }
    }

    async fn task_start(&self, header: TaskHeader) -> anyhow::Result<()> {
        self.send_update(header, TaskUpdate::Start).await
    }

    async fn send_update(&self, header: TaskHeader, payload: TaskUpdate) -> anyhow::Result<()> {
        Ok(self.factory.tell(TaskUpdateMsg { header, payload }).await?)
    }

    async fn send_done(
        &self,
        header: TaskHeader,
        payload: Result<TaskDone, TaskError>,
    ) -> anyhow::Result<()> {
        Ok(self.factory.tell(TaskDoneMsg { header, payload }).await?)
    }

    async fn execute(
        &self,
        header: TaskHeader,
        task: Arc<ExecuteTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!("ELF: {} bytes", task.binary.len());
        self.task_start(header.clone()).await?;
        let factory = self.factory.clone();
        let header_copy = header.clone();
        let session: anyhow::Result<Session> = tokio::task::spawn_blocking(move || {
            let env = ExecutorEnv::builder().write_slice(&task.input).build()?;
            let mut exec = ExecutorImpl::from_elf(env, &task.binary)?;
            let session = exec.run_with_callback(|segment| {
                let msg = TaskUpdateMsg {
                    header: header_copy.clone(),
                    payload: TaskUpdate::Segment(segment),
                };
                factory.tell(msg).blocking_send()?;
                Ok(Box::new(NullSegmentRef))
            })?;

            let session = Session {
                segment_count: session.segments.len(),
                user_cycles: session.user_cycles,
                total_cycles: session.total_cycles,
                journal: session.journal,
            };

            Ok(session)
        })
        .await
        .context("JoinHandle error: execute task")?;
        Ok(TaskDone::Session(Arc::new(session?)))
    }

    async fn prove_segment(
        &self,
        header: TaskHeader,
        task: Arc<ProveSegmentTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!("ProveSegment: {}", task.segment.index);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let ctx = VerifierContext::default();
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.prove_segment(&ctx, &task.segment)
        })
        .await
        .context("JoinHandle error: prove_segment task")??;
        Ok(TaskDone::ProveSegment(Box::new(receipt)))
    }

    async fn prove_keccak(
        &self,
        header: TaskHeader,
        task: Arc<ProveKeccakTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!("ProveKeccak: {}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.prove_keccak(&task.request)
        })
        .await
        .context("JoinHandle error: prove_keccak task")??;
        Ok(TaskDone::ProveKeccak(Box::new(receipt)))
    }

    async fn lift(&self, header: TaskHeader, task: Arc<LiftTask>) -> Result<TaskDone, TaskError> {
        tracing::info!("Lift: {}", task.receipt.index);
        self.task_start(header.clone()).await?;
        let segment_idx = task.receipt.index;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.lift(&task.receipt)
        })
        .await
        .context("JoinHandle error: lift task")??;
        Ok(TaskDone::Lift(Box::new(JoinNode {
            range: (segment_idx..segment_idx + 1).into(),
            receipt,
        })))
    }

    async fn join(&self, header: TaskHeader, task: Arc<JoinTask>) -> Result<TaskDone, TaskError> {
        let range = task.range;
        tracing::info!("Join: {range:?}");
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.join(&task.receipts[0], &task.receipts[1])
        })
        .await
        .context("JoinHandle error: join task")??;
        Ok(TaskDone::Join(Box::new(JoinNode { range, receipt })))
    }

    async fn union(&self, header: TaskHeader, task: Arc<UnionTask>) -> Result<TaskDone, TaskError> {
        tracing::info!("Union: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.union(&task.receipts[0], &task.receipts[1])
        })
        .await
        .context("JoinHandle error: union task")??;
        Ok(TaskDone::Union(Box::new(receipt)))
    }

    async fn resolve(
        &self,
        header: TaskHeader,
        task: Arc<ResolveTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!("Resolve: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.resolve(&task.conditional, &task.assumption)
        })
        .await
        .context("JoinHandle error: resolve task")??;
        Ok(TaskDone::Resolve(Box::new(receipt)))
    }
}
