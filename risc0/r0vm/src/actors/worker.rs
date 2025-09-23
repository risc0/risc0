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

use std::{rc::Rc, sync::Arc};

use anyhow::{Context as _, Result};
use kameo::{error::Infallible, prelude::*};
use risc0_zkvm::{
    CoprocessorCallback, DevModeDelay, DevModeProver, ExecutorEnv, ExecutorImpl, NullSegmentRef,
    PreflightResults, ProveKeccakRequest, ProverOpts, ProverServer, VerifierContext,
    get_prover_server,
};
use tokio::sync::mpsc::{Receiver, Sender, channel};

use super::{
    RemoteActor, RemoteWorkerRequest, RpcSender, WriteStream,
    allocator::{
        AllocateHardware, AllocatorRouterActor, CpuCores, CpuSpec, DeallocateHardware, GpuSpec,
        GpuTokens, GpuUuid, HardwareReservation, HardwareResource, RegisterWorker,
    },
    factory::FactoryRouterActor,
    protocol::{
        ExecuteTask, JoinTask, LiftTask, ProveKeccakTask, ProveSegmentTask, ResolveTask, Session,
        ShrinkWrapKind, ShrinkWrapTask, Task, TaskError, TaskHeader, TaskKind, UnionTask, WorkerId,
        factory::{
            GetTasks, JoinNode, ProveKeccakDone, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg,
            UnionDone,
        },
        worker::TaskMsg,
    },
    remote_actor_tell, routing_actor_impl,
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
    ShrinkWrap(Arc<ShrinkWrapTask>),
}

struct GpuTaskMsg {
    header: TaskHeader,
    task: GpuTask,
    hardware_reservations: Vec<HardwareReservation>,
}

enum CpuTask {
    Execute(Arc<ExecuteTask>),
    Preflight(Arc<ProveSegmentTask>),
}

struct CpuTaskMsg {
    header: TaskHeader,
    task: CpuTask,
    hardware_reservations: Vec<HardwareReservation>,
}

/// Number of tasks we queue up to do on CPU
const CPU_QUEUE_DEPTH: usize = 2;

/// Number of tasks we queue up to do on GPU
const GPU_QUEUE_DEPTH: usize = 2;

#[cfg(feature = "cuda")]
fn get_gpus_from_nvml() -> Result<Vec<GpuSpec>> {
    use nvml_wrapper::Nvml;

    let mut gpus = vec![];
    let nvml = Nvml::init()?;
    for idx in 0..nvml.device_count()? {
        let device = nvml.device_by_index(idx)?;
        gpus.push(GpuSpec {
            name: device.name()?,
            uuid: device.uuid()?.parse().unwrap(),
            tokens: GpuTokens::from(100),
        });
    }
    Ok(gpus)
}

#[cfg(not(feature = "cuda"))]
fn get_gpus_from_nvml() -> Result<Vec<GpuSpec>> {
    Ok(vec![])
}

fn fake_gpus() -> Vec<GpuSpec> {
    vec![GpuSpec {
        name: "Fake Test GPU".into(),
        uuid: GpuUuid::new_fake(),
        tokens: GpuTokens::from(100),
    }]
}

pub(crate) struct WorkerActor {
    processor: Processor,
    factory: ActorRef<FactoryRouterActor>,
    allocator: ActorRef<AllocatorRouterActor>,
    task_kinds: Vec<TaskKind>,
    id: WorkerId,
    gpus: Vec<GpuSpec>,
    cpu: CpuSpec,
}

impl WorkerActor {
    pub fn new(
        factory: ActorRef<FactoryRouterActor>,
        allocator: ActorRef<AllocatorRouterActor>,
        task_kinds: Vec<TaskKind>,
        delay: Option<DevModeDelay>,
    ) -> Result<ActorRef<Self>> {
        let gpus = if delay.is_some() {
            fake_gpus()
        } else {
            get_gpus_from_nvml().unwrap_or_else(|err| {
                tracing::error!("Got error when searching for GPUs: {err}");
                vec![]
            })
        };
        let cpu = CpuSpec {
            cores: CpuCores::from(usize::from(std::thread::available_parallelism()?) as u64),
        };
        let worker_id = WorkerId::new_v4();
        let s = Self {
            processor: Processor::new(factory.clone(), allocator.clone(), worker_id, delay),
            factory,
            allocator,
            task_kinds,
            id: worker_id,
            gpus,
            cpu,
        };

        Ok(kameo::spawn(s))
    }
}

impl Actor for WorkerActor {
    type Error = anyhow::Error;

    async fn on_start(&mut self, actor_ref: ActorRef<Self>) -> Result<()> {
        tracing::info!("Starting worker: {:?}", self.task_kinds);

        let mut hardware = self
            .gpus
            .iter()
            .map(|gpu| gpu.clone().into())
            .collect::<Vec<HardwareResource>>();
        hardware.push(self.cpu.clone().into());

        self.allocator
            .ask(RegisterWorker {
                remote_address: None,
                worker_id: self.id,
                hardware,
            })
            .await
            .unwrap();

        self.factory
            .tell(GetTasks {
                worker_id: self.id,
                worker: Some(WorkerRouterActor::new_local(actor_ref)),
                kinds: self.task_kinds.clone(),
            })
            .await
            .unwrap();

        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        _s_reason: ActorStopReason,
    ) -> Result<()> {
        Ok(())
    }
}

impl Message<TaskMsg> for WorkerActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskMsg, _ctx: &mut Context<Self, Self::Reply>) {
        let mut hardware_reservations = vec![HardwareReservation::Cpu { cores: msg.cores }];
        if msg.gpu_tokens > GpuTokens::ZERO {
            if self.gpus.is_empty() {
                panic!("worker received a GPU task, but has no access to a GPU");
            }
            hardware_reservations.push(HardwareReservation::Gpu {
                id: self.gpus[0].uuid.clone(),
                tokens: msg.gpu_tokens,
            });
        }

        self.allocator
            .ask(AllocateHardware {
                worker_id: self.id,
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        self.processor
            .process_task(msg, hardware_reservations)
            .await;
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
    fn new(
        factory: ActorRef<FactoryRouterActor>,
        allocator: ActorRef<AllocatorRouterActor>,
        worker_id: WorkerId,
        delay: Option<DevModeDelay>,
    ) -> Self {
        let (gpu_send, gpu_recv) = channel(GPU_QUEUE_DEPTH);
        let (cpu_send, cpu_recv) = channel(CPU_QUEUE_DEPTH);

        let gpu_processor = GpuProcessor::new(factory.clone(), allocator.clone(), worker_id, delay);
        tokio::task::spawn(async move {
            gpu_processor.process_tasks(gpu_recv).await;
        });

        let cpu_processor = CpuProcessor::new(
            factory.clone(),
            allocator.clone(),
            worker_id,
            delay,
            gpu_send.clone(),
        );
        tokio::task::spawn(async move {
            cpu_processor.process_tasks(cpu_recv).await;
        });

        Self {
            gpu_queue: gpu_send,
            cpu_queue: cpu_send,
        }
    }

    async fn process_task(&self, msg: TaskMsg, hardware_reservations: Vec<HardwareReservation>) {
        match msg.task {
            Task::Execute(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Execute(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::ProveSegment(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Preflight(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::Lift(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Lift(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::Join(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Join(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::ProveKeccak(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::ProveKeccak(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::Union(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Union(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::Resolve(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Resolve(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
            Task::ShrinkWrap(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::ShrinkWrap(task),
                        hardware_reservations,
                    })
                    .await
                    .unwrap();
            }
        }
    }
}

struct GpuProcessor {
    factory: ActorRef<FactoryRouterActor>,
    allocator: ActorRef<AllocatorRouterActor>,
    delay: Option<DevModeDelay>,
    worker_id: WorkerId,
}

impl GpuProcessor {
    fn new(
        factory: ActorRef<FactoryRouterActor>,
        allocator: ActorRef<AllocatorRouterActor>,
        worker_id: WorkerId,
        delay: Option<DevModeDelay>,
    ) -> Self {
        Self {
            factory,
            allocator,
            worker_id,
            delay,
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
        hardware_reservations: Vec<HardwareReservation>,
    ) -> anyhow::Result<()> {
        let global_id = header.global_id;
        self.factory.tell(TaskDoneMsg { header, payload }).await?;
        self.allocator
            .tell(DeallocateHardware {
                worker_id: self.worker_id,
                task_id: global_id,
                hardware_reservations,
            })
            .await?;
        Ok(())
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
            GpuTask::ShrinkWrap(task) => self.shrink_wrap(msg.header, task).await,
        };

        let result = self
            .send_done(header, result, msg.hardware_reservations)
            .await;
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
            let ctx = VerifierContext::default().with_dev_mode(prover.delay.is_some());
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

    async fn shrink_wrap(
        &self,
        header: TaskHeader,
        task: Arc<ShrinkWrapTask>,
    ) -> Result<TaskDone, TaskError> {
        tracing::info!(
            "ShrinkWrap({:?}): {:?}",
            task.kind,
            header.global_id.task_id
        );
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let task_kind = task.kind;
        let opts = match task_kind {
            ShrinkWrapKind::Groth16 => ProverOpts::groth16(),
        };
        let receipt =
            tokio::task::spawn_blocking(move || prover.get()?.compress(&opts, &task.receipt))
                .await
                .with_context(|| format!("JoinHandle error: shrink_wrap({task_kind:?}) task"))??;
        Ok(TaskDone::ShrinkWrap(Arc::new(receipt)))
    }
}

struct CpuProcessor {
    factory: ActorRef<FactoryRouterActor>,
    allocator: ActorRef<AllocatorRouterActor>,
    delay: Option<DevModeDelay>,
    worker_id: WorkerId,

    gpu_queue: Sender<GpuTaskMsg>,
}

impl CpuProcessor {
    fn new(
        factory: ActorRef<FactoryRouterActor>,
        allocator: ActorRef<AllocatorRouterActor>,
        worker_id: WorkerId,
        delay: Option<DevModeDelay>,
        gpu_queue: Sender<GpuTaskMsg>,
    ) -> Self {
        Self {
            factory,
            allocator,
            delay,
            worker_id,
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
        hardware_reservations: Vec<HardwareReservation>,
    ) -> anyhow::Result<()> {
        let global_id = header.global_id;
        self.factory.tell(TaskDoneMsg { header, payload }).await?;
        self.allocator
            .tell(DeallocateHardware {
                worker_id: self.worker_id,
                task_id: global_id,
                hardware_reservations,
            })
            .await?;
        Ok(())
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
                if let Err(error) = self
                    .preflight(msg.header, task, msg.hardware_reservations.clone())
                    .await
                    && let Err(err) = self
                        .send_done(header, Err(error), msg.hardware_reservations)
                        .await
                {
                    tracing::error!("Failed to send error: {err}");
                }
                return;
            }
        };

        let result = self
            .send_done(header, result, msg.hardware_reservations)
            .await;
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
        let session: anyhow::Result<Session> = tokio::task::spawn_blocking(move || {
            let coproc = Coprocessor {
                factory: factory.clone(),
                header,
            };

            let mut env = ExecutorEnv::builder();
            for assumption in task.request.assumptions.iter() {
                env.add_assumption(assumption.clone());
            }
            if let Some(po2) = task.request.segment_limit_po2 {
                env.segment_limit_po2(po2);
            }
            let env = env
                // .stdout(writer) // TODO
                .write_slice(&task.request.input)
                .coprocessor_callback(coproc)
                // .session_limit(limit) // TODO
                .build()?;

            // TODO(povw): Add PoVW here
            let mut exec = ExecutorImpl::from_elf(env, &task.request.binary)?;
            let mut segments = vec![];
            let session = exec.run_with_callback(|segment| {
                segments.push(segment.get_info());
                let msg = TaskUpdateMsg {
                    header: header_copy.clone(),
                    payload: TaskUpdate::Segment(segment),
                };
                factory.tell(msg).blocking_send()?;
                Ok(Box::new(NullSegmentRef))
            })?;

            let stats = session.stats();
            let receipt_claim = session.claim()?;
            let assumptions = session
                .assumptions
                .into_iter()
                .map(|(_, receipt)| Arc::new(receipt))
                .collect();

            let session = Session {
                stats,
                journal: session.journal,
                assumptions,
                segments,
                exit_code: session.exit_code,
                receipt_claim,
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
        hardware_reservations: Vec<HardwareReservation>,
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
                hardware_reservations,
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

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

pub(crate) enum WorkerRouterActor {
    Local(ActorRef<WorkerActor>),
    Remote(ActorRef<RemoteWorkerActor>),
}

impl Actor for WorkerRouterActor {
    type Error = Infallible;

    async fn on_start(&mut self, _actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        _reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        match self {
            Self::Local(_) => {}
            Self::Remote(r) => {
                let _ = r.stop_gracefully().await;
            }
        }
        Ok(())
    }
}

impl WorkerRouterActor {
    pub(crate) fn new_remote(rpc_sender: RpcSender<WriteStream>) -> ActorRef<Self> {
        let remote = kameo::spawn(RemoteWorkerActor::new_from_rpc_sender(rpc_sender));
        kameo::spawn(Self::Remote(remote))
    }

    pub(crate) fn new_local(local: ActorRef<WorkerActor>) -> ActorRef<Self> {
        kameo::spawn(Self::Local(local))
    }
}

type RemoteWorkerActor = RemoteActor<WorkerActor>;

routing_actor_impl!(WorkerRouterActor, TaskMsg, ());

remote_actor_tell!(RemoteActor<WorkerActor>, TaskMsg, RemoteWorkerRequest);
