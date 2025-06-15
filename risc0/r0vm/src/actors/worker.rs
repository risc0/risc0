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

use anyhow::{Context, Result};
use kameo::prelude::*;
use risc0_zkvm::{
    get_prover_server, CoprocessorCallback, DevModeDelay, DevModeProver, ExecutorEnv, ExecutorImpl,
    NullSegmentRef, PreflightResults, ProveKeccakRequest, ProveZkrRequest, ProverOpts,
    ProverServer, VerifierContext,
};
use tokio::sync::mpsc::{channel, Receiver, Sender};
use tokio::task::JoinHandle;

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

struct ProveSegmentCoreTask {
    preflight_results: Box<PreflightResults>,
}

enum GpuTask {
    ProveSegmentCore(ProveSegmentCoreTask),
    ProveKeccak(Arc<ProveKeccakTask>),
    Lift(Arc<LiftTask>),
    Join(Arc<JoinTask>),
    Union(Arc<UnionTask>),
    Resolve(Arc<ResolveTask>),
}

struct GpuTaskMsg {
    header: TaskHeader,
    task: GpuTask,
}

enum CpuTask {
    Execute(Arc<ExecuteTask>),
    Preflight(Arc<ProveSegmentTask>),
}

struct CpuTaskMsg {
    header: TaskHeader,
    task: CpuTask,
}

/// Number of tasks we pull off the network and queue up in memory before processing
const RECEIVE_QUEUE_DEPTH: usize = 1;

/// Number of tasks we queue up to do on CPU
const CPU_QUEUE_DEPTH: usize = 2;

/// Number of tasks we queue up to do on GPU
const GPU_QUEUE_DEPTH: usize = 2;

pub(crate) struct Worker {
    factory: ActorRef<FactoryRouterActor>,
    task_kinds: Vec<TaskKind>,
    join_handles: Vec<JoinHandle<()>>,
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
            factory,
            task_kinds,
            join_handles: vec![],
            delay,
            po2,
        }
    }

    pub fn start(&mut self) {
        if !self.join_handles.is_empty() {
            return;
        }

        let task_kinds = self.task_kinds.clone();
        let factory = self.factory.clone();
        let (send, mut recv) = channel(RECEIVE_QUEUE_DEPTH);
        self.join_handles.push(tokio::spawn(async move {
            while let Ok(permit) = send.reserve().await {
                let task = factory
                    .ask(GetTask {
                        worker_id: WorkerId::new_v4(),
                        kinds: task_kinds.clone(),
                    })
                    .await;
                permit.send(task);
            }
        }));

        let processor = Processor::new(self.factory.clone(), self.delay, self.po2);
        self.join_handles.push(tokio::spawn(async move {
            loop {
                let Some(msg) = recv.recv().await else { break };
                let msg = match msg {
                    Ok(msg) => msg,
                    Err(err) => {
                        tracing::error!("GetTask reply error: {err}");
                        break;
                    }
                };

                processor.process_task(msg).await;
            }
        }));
    }

    pub async fn stop(mut self) {
        for join_handle in std::mem::take(&mut self.join_handles) {
            join_handle.abort();
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

struct Processor {
    gpu_queue: Sender<GpuTaskMsg>,
    cpu_queue: Sender<CpuTaskMsg>,
}

impl Processor {
    fn new(factory: ActorRef<FactoryRouterActor>, delay: Option<DevModeDelay>, po2: usize) -> Self {
        let (gpu_send, gpu_recv) = channel(GPU_QUEUE_DEPTH);
        let (cpu_send, cpu_recv) = channel(CPU_QUEUE_DEPTH);

        let gpu_processor = GpuProcessor::new(factory.clone(), delay);
        tokio::task::spawn(async move {
            gpu_processor.process_tasks(gpu_recv).await;
        });

        let cpu_processor = CpuProcessor::new(factory.clone(), delay, po2, gpu_send.clone());
        tokio::task::spawn(async move {
            cpu_processor.process_tasks(cpu_recv).await;
        });

        Self {
            gpu_queue: gpu_send,
            cpu_queue: cpu_send,
        }
    }

    async fn process_task(&self, msg: TaskMsg) {
        match msg.task {
            Task::Execute(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Execute(task),
                    })
                    .await
                    .unwrap();
            }
            Task::ProveSegment(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Preflight(task),
                    })
                    .await
                    .unwrap();
            }
            Task::Lift(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Lift(task),
                    })
                    .await
                    .unwrap();
            }
            Task::Join(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Join(task),
                    })
                    .await
                    .unwrap();
            }
            Task::ProveKeccak(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::ProveKeccak(task),
                    })
                    .await
                    .unwrap();
            }
            Task::Union(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Union(task),
                    })
                    .await
                    .unwrap();
            }
            Task::Resolve(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Resolve(task),
                    })
                    .await
                    .unwrap();
            }
        }
    }
}

struct GpuProcessor {
    factory: ActorRef<FactoryRouterActor>,
    delay: Option<DevModeDelay>,
}

impl GpuProcessor {
    fn new(factory: ActorRef<FactoryRouterActor>, delay: Option<DevModeDelay>) -> Self {
        Self { factory, delay }
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

    async fn process_tasks(&self, mut recv: Receiver<GpuTaskMsg>) {
        while let Some(msg) = recv.recv().await {
            self.process_task(msg).await;
        }
    }

    async fn process_task(&self, msg: GpuTaskMsg) {
        let header = msg.header.clone();

        let result = match msg.task {
            GpuTask::ProveSegmentCore(task) => self.prove_segment_core(msg.header, task).await,
            GpuTask::ProveKeccak(task) => self.prove_keccak(msg.header, task).await,
            GpuTask::Lift(task) => self.lift(msg.header, task).await,
            GpuTask::Join(task) => self.join(msg.header, task).await,
            GpuTask::Union(task) => self.union(msg.header, task).await,
            GpuTask::Resolve(task) => self.resolve(msg.header, task).await,
        };

        let result = self.send_done(header, result).await;
        if let Err(err) = result {
            tracing::error!("Failed to send error: {err}");
        }
    }

    async fn prove_segment_core(
        &self,
        header: TaskHeader,
        task: ProveSegmentCoreTask,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!(
            "ProveSegmentCore: {}",
            task.preflight_results.segment_index()
        );
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            let ctx = VerifierContext::default();
            prover
                .get()?
                .prove_segment_core(&ctx, *task.preflight_results)
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

struct CpuProcessor {
    factory: ActorRef<FactoryRouterActor>,
    delay: Option<DevModeDelay>,
    po2: usize,

    gpu_queue: Sender<GpuTaskMsg>,
}

impl CpuProcessor {
    fn new(
        factory: ActorRef<FactoryRouterActor>,
        delay: Option<DevModeDelay>,
        po2: usize,
        gpu_queue: Sender<GpuTaskMsg>,
    ) -> Self {
        Self {
            factory,
            delay,
            po2,
            gpu_queue,
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

    async fn process_tasks(&self, mut recv: Receiver<CpuTaskMsg>) {
        while let Some(msg) = recv.recv().await {
            self.process_task(msg).await;
        }
    }

    async fn process_task(&self, msg: CpuTaskMsg) {
        let header = msg.header.clone();

        let result = match msg.task {
            CpuTask::Execute(task) => self.execute(msg.header, task).await,
            CpuTask::Preflight(task) => {
                if let Err(error) = self.preflight(msg.header, task).await {
                    if let Err(err) = self.send_done(header, Err(error)).await {
                        tracing::error!("Failed to send error: {err}");
                    }
                }
                return;
            }
        };

        let result = self.send_done(header, result).await;
        if let Err(err) = result {
            tracing::error!("Failed to send error: {err}");
        }
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

    async fn preflight(
        &self,
        header: TaskHeader,
        task: Arc<ProveSegmentTask>,
    ) -> Result<(), TaskError> {
        tracing::info!("Preflight: {}", task.segment.index);
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let preflight_results = tokio::task::spawn_blocking(move || -> Result<_> {
            Ok(Box::new(prover.get()?.segment_preflight(&task.segment)?))
        })
        .await
        .context("JoinHandle error: prove_segment task")??;
        self.gpu_queue
            .send(GpuTaskMsg {
                header,
                task: GpuTask::ProveSegmentCore(ProveSegmentCoreTask { preflight_results }),
            })
            .await
            .unwrap();

        Ok(())
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
