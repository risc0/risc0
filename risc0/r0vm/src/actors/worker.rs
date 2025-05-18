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

use std::{rc::Rc, sync::Arc};

use anyhow::Context;
use kameo::prelude::*;
use risc0_zkvm::{
    get_prover_server, CoprocessorCallback, DevModeDelay, DevModeProver, ExecutorEnv, ExecutorImpl,
    NullSegmentRef, ProveKeccakRequest, ProveZkrRequest, ProverOpts, ProverServer, VerifierContext,
};
use tokio::task::JoinHandle;
use tokio_util::sync::CancellationToken;

use super::{
    factory::FactoryRouterActor,
    protocol::{
        factory::{
            GetTask, JoinNode, ProveKeccakDone, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg,
            UnionDone,
        },
        worker::TaskMsg,
        ExecuteTask, JoinTask, LiftTask, ProveKeccakTask, ProveSegmentTask, ResolveTask, Session,
        Task, TaskError, TaskHeader, TaskKind, UnionTask, WorkerId,
    },
};

struct Processor {
    factory: ActorRef<FactoryRouterActor>,
    delay: Option<DevModeDelay>,
    po2: usize,
}

pub(crate) struct Worker {
    worker_id: WorkerId,
    factory: ActorRef<FactoryRouterActor>,
    task_kinds: Vec<TaskKind>,
    token: CancellationToken,
    join_handle: Option<JoinHandle<()>>,
    delay: Option<DevModeDelay>,
    po2: usize,
}

impl Worker {
    pub fn new(
        factory: ActorRef<FactoryRouterActor>,
        task_kinds: Vec<TaskKind>,
        delay: Option<DevModeDelay>,
        po2: usize,
    ) -> Self {
        Self {
            worker_id: WorkerId::new_v4(),
            factory,
            task_kinds,
            token: CancellationToken::new(),
            join_handle: None,
            delay,
            po2,
        }
    }

    pub fn start(&mut self) {
        if self.join_handle.is_some() {
            return;
        }

        let request = GetTask {
            worker_id: self.worker_id,
            kinds: self.task_kinds.clone(),
        };
        let factory = self.factory.clone();
        let processor = Processor {
            factory: factory.clone(),
            delay: self.delay,
            po2: self.po2,
        };
        let token = self.token.clone();
        self.join_handle = Some(tokio::spawn(async move {
            loop {
                let request = request.clone();
                tokio::select! {
                    _ = token.cancelled() => {
                        // tracing::info!("stopping");
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

struct Prover {
    delay: Option<DevModeDelay>,
}

impl Prover {
    fn get(&self) -> anyhow::Result<Rc<dyn ProverServer>> {
        if let Some(delay) = self.delay {
            Ok(Rc::new(DevModeProver::with_delay(delay)))
        } else {
            get_prover_server(&ProverOpts::default())
        }
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
        tracing::info!("ELF: {} bytes", task.request.binary.len());
        self.task_start(header.clone()).await?;
        let factory = self.factory.clone();
        let header_copy = header.clone();
        let po2 = self.po2 as u32;
        let session: anyhow::Result<Session> = tokio::task::spawn_blocking(move || {
            let coproc = Coprocessor {
                factory: factory.clone(),
                header,
            };

            let mut env = ExecutorEnv::builder();
            for assumption in task.request.assumptions.iter() {
                env.add_assumption(assumption.clone());
            }
            let env = env
                // .stdout(writer) // TODO
                .write_slice(&task.request.input)
                .coprocessor_callback(coproc)
                // .session_limit(limit) // TODO
                .segment_limit_po2(po2)
                .build()?;

            let mut exec = ExecutorImpl::from_elf(env, &task.request.binary)?;
            let session = exec.run_with_callback(|segment| {
                let msg = TaskUpdateMsg {
                    header: header_copy.clone(),
                    payload: TaskUpdate::Segment(segment),
                };
                factory.tell(msg).blocking_send()?;
                Ok(Box::new(NullSegmentRef))
            })?;

            let assumptions = session
                .assumptions
                .into_iter()
                .map(|(_, receipt)| Arc::new(receipt))
                .collect();

            let session = Session {
                segment_count: session.segments.len(),
                user_cycles: session.user_cycles,
                total_cycles: session.total_cycles,
                journal: session.journal,
                assumptions,
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
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            let ctx = VerifierContext::default();
            prover.get()?.prove_segment(&ctx, &task.segment)
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
        let index = task.index;
        tracing::info!("ProveKeccak: {index}");
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt =
            tokio::task::spawn_blocking(move || prover.get()?.prove_keccak(&task.request))
                .await
                .context("JoinHandle error: prove_keccak task")??;
        Ok(TaskDone::ProveKeccak(Arc::new(ProveKeccakDone {
            index,
            receipt,
        })))
    }

    async fn lift(&self, header: TaskHeader, task: Arc<LiftTask>) -> Result<TaskDone, TaskError> {
        tracing::info!("Lift: {}", task.receipt.index);
        self.task_start(header.clone()).await?;
        let segment_idx = task.receipt.index;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || prover.get()?.lift(&task.receipt))
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
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.join(&task.receipts[0], &task.receipts[1])
        })
        .await
        .context("JoinHandle error: join task")??;
        Ok(TaskDone::Join(Box::new(JoinNode { range, receipt })))
    }

    async fn union(&self, header: TaskHeader, task: Arc<UnionTask>) -> Result<TaskDone, TaskError> {
        let height = task.height;
        let pos = task.pos;
        tracing::info!("Union: {height}/{pos}");
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.union(&task.receipts[0], &task.receipts[1])
        })
        .await
        .context("JoinHandle error: union task")??;
        Ok(TaskDone::Union(Arc::new(UnionDone {
            height,
            pos,
            receipt,
        })))
    }

    async fn resolve(
        &self,
        header: TaskHeader,
        task: Arc<ResolveTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!("Resolve: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.resolve(&task.conditional, &task.assumption)
        })
        .await
        .context("JoinHandle error: resolve task")??;
        Ok(TaskDone::Resolve(Arc::new(receipt)))
    }
}

struct Coprocessor {
    factory: ActorRef<FactoryRouterActor>,
    header: TaskHeader,
}

impl CoprocessorCallback for Coprocessor {
    fn prove_zkr(&mut self, _request: ProveZkrRequest) -> anyhow::Result<()> {
        unimplemented!()
    }

    fn prove_keccak(&mut self, request: ProveKeccakRequest) -> anyhow::Result<()> {
        self.factory
            .tell(TaskUpdateMsg {
                header: self.header.clone(),
                payload: TaskUpdate::Keccak(request),
            })
            .blocking_send()
            .context("Failed to send ProveKeccakRequest")
    }
}
