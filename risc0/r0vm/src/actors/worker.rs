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

use std::{borrow::Cow, rc::Rc, sync::Arc};

use opentelemetry::{
    global::BoxedSpan,
    trace::{Span as _, Tracer as _},
};
use risc0_zkvm::{
    CoprocessorCallback, DevModeDelay, DevModeProver, ExecutorEnv, ExecutorImpl, NullSegmentRef,
    PreflightResults, ProveKeccakRequest, ProverOpts, ProverServer, VerifierContext,
    get_prover_server,
};
use tokio::sync::mpsc::{Receiver, Sender, channel};

use super::{
    RemoteActor, RemoteWorkerRequest,
    actor::{self, Actor, ActorRef, Context, Message},
    allocator::{
        AllocateHardware, CpuCores, CpuSpec, DeallocateHardware, EndTask, GpuSpec, GpuTokens,
        GpuUuid, HardwareReservation, HardwareResource, RemoteAllocatorActor,
    },
    error::{Error, Result},
    factory::RemoteFactoryActor,
    job,
    protocol::{
        ExecuteTask, JoinTask, LiftTask, ProveKeccakTask, ProveSegmentTask, ResolveTask, Session,
        ShrinkWrapKind, ShrinkWrapTask, Task, TaskError, TaskHeader, TaskKind, UnionTask, WorkerId,
        factory::{
            GetTasks, JoinNode, ProveKeccakDone, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg,
            UnionDone,
        },
        worker::TaskMsg,
    },
    remote_actor_tell,
};

type TaskResult<T> = std::result::Result<T, TaskError>;

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
    to_reserve: Vec<HardwareReservation>,
    reserved: Vec<HardwareReservation>,
    tracing: job::tracer::SavedContext,
}

enum CpuTask {
    Execute(Arc<ExecuteTask>),
    Preflight(Arc<ProveSegmentTask>),
}

struct CpuTaskMsg {
    header: TaskHeader,
    task: CpuTask,
    to_reserve: Vec<HardwareReservation>,
    reserved: Vec<HardwareReservation>,
    tracing: job::tracer::SavedContext,
}

/// Number of tasks we queue up to do on CPU
const CPU_QUEUE_DEPTH: usize = 50;

/// Number of tasks we queue up to do on GPU
const GPU_QUEUE_DEPTH: usize = 50;

#[cfg(feature = "cuda")]
fn get_gpus_from_nvml() -> anyhow::Result<Vec<GpuSpec>> {
    use nvml_wrapper::Nvml;
    use std::collections::HashSet;

    let visible_devices = std::env::var("CUDA_VISIBLE_DEVICES")
        .ok()
        .map(|v| {
            v.split(",")
                .map(|v| v.trim().parse())
                .collect::<std::result::Result<HashSet<u32>, _>>()
                .map_err(|e| anyhow::anyhow!("failed to parse CUDA_VISIBLE_DEVICES: {e}"))
        })
        .transpose()?;

    let mut gpus = vec![];
    let nvml = Nvml::init()?;
    for idx in 0..nvml.device_count()? {
        if let Some(visible_devices) = &visible_devices
            && !visible_devices.contains(&idx)
        {
            continue;
        }

        let device = nvml.device_by_index(idx)?;
        gpus.push(GpuSpec {
            name: device.name()?,
            uuid: device
                .uuid()?
                .parse()
                .expect("nvml device should have valid UUID"),
            tokens: GpuTokens::from(100),
        });
    }
    Ok(gpus)
}

#[cfg(not(feature = "cuda"))]
fn get_gpus_from_nvml() -> anyhow::Result<Vec<GpuSpec>> {
    Ok(vec![])
}

fn fake_gpus() -> Vec<GpuSpec> {
    vec![GpuSpec {
        name: "Fake Test GPU".into(),
        uuid: GpuUuid::new_fake(),
        tokens: GpuTokens::from(100),
    }]
}

pub(crate) fn worker_hardware(
    delay: Option<DevModeDelay>,
) -> anyhow::Result<Vec<HardwareResource>> {
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

    let mut hardware = gpus
        .iter()
        .map(|gpu| gpu.clone().into())
        .collect::<Vec<HardwareResource>>();
    hardware.push(cpu.clone().into());
    Ok(hardware)
}

pub(crate) struct WorkerActor {
    processor: Processor,
    factory: ActorRef<RemoteFactoryActor>,
    task_kinds: Vec<TaskKind>,
    id: WorkerId,
    gpus: Vec<GpuSpec>,
}

impl WorkerActor {
    pub fn new(
        worker_id: WorkerId,
        factory: ActorRef<RemoteFactoryActor>,
        allocator: ActorRef<RemoteAllocatorActor>,
        task_kinds: Vec<TaskKind>,
        delay: Option<DevModeDelay>,
        gpus: Vec<GpuSpec>,
    ) -> anyhow::Result<ActorRef<Self>> {
        let s = Self {
            processor: Processor::new(factory.clone(), allocator, worker_id, delay),
            factory,
            task_kinds,
            id: worker_id,
            gpus,
        };

        Ok(actor::spawn(s))
    }
}

impl Actor for WorkerActor {
    async fn on_start(&mut self, actor_ref: ActorRef<Self>) {
        let res = self
            .factory
            .tell(GetTasks {
                worker_id: self.id,
                worker: None,
                remote_address: None,
                kinds: self.task_kinds.clone(),
            })
            .await;
        if let Err(error) = res {
            tracing::error!("worker dead: failed to talk to factory: {error}");
            let _ = actor_ref.stop_gracefully(format!("failed to talk to factory: {error}"));
        }
    }
}

impl Message<TaskMsg> for WorkerActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskMsg, ctx: &mut Context<Self, Self::Reply>) {
        let res = self.handle_task(msg).await;
        if let Err(error) = res {
            tracing::error!("worker has died: {error}");
            let _ = ctx.actor_ref().stop_gracefully(error.to_string());
        }
    }
}

impl WorkerActor {
    async fn handle_task(&mut self, msg: TaskMsg) -> Result<()> {
        let mut to_reserve = vec![HardwareReservation::Cpu { cores: msg.cores }];
        if msg.gpu_tokens > GpuTokens::ZERO {
            if self.gpus.is_empty() {
                self.fail_task(
                    msg,
                    "worker received a GPU task, but has no access to a GPU",
                )
                .await?;

                return Ok(());
            }
            to_reserve.push(HardwareReservation::Gpu {
                id: self.gpus[0].uuid.clone(),
                tokens: msg.gpu_tokens,
            });
        }

        self.processor.process_task(msg, to_reserve).await?;

        Ok(())
    }

    async fn fail_task(&mut self, msg: TaskMsg, message: &str) -> Result<()> {
        self.factory
            .tell(TaskDoneMsg {
                header: msg.header,
                payload: Err(TaskError::Generic(message.into())),
            })
            .await?;

        Ok(())
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
        factory: ActorRef<RemoteFactoryActor>,
        allocator: ActorRef<RemoteAllocatorActor>,
        worker_id: WorkerId,
        delay: Option<DevModeDelay>,
    ) -> Self {
        let (gpu_send, gpu_recv) = channel(GPU_QUEUE_DEPTH);
        let (cpu_send, cpu_recv) = channel(CPU_QUEUE_DEPTH);

        let gpu_processor = GpuProcessor::new(factory.clone(), allocator.clone(), worker_id, delay);
        tokio::task::spawn(async move {
            let res = gpu_processor.process_tasks(gpu_recv).await;
            if let Err(error) = res {
                tracing::error!("GPU processor failed: {error}");
            }
        });

        let cpu_processor = CpuProcessor::new(
            factory.clone(),
            allocator.clone(),
            worker_id,
            delay,
            gpu_send.clone(),
        );
        tokio::task::spawn(async move {
            let res = cpu_processor.process_tasks(cpu_recv).await;
            if let Err(error) = res {
                tracing::error!("CPU processor failed: {error}");
            }
        });

        Self {
            gpu_queue: gpu_send,
            cpu_queue: cpu_send,
        }
    }

    async fn process_task(&self, msg: TaskMsg, to_reserve: Vec<HardwareReservation>) -> Result<()> {
        match msg.task {
            Task::Execute(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Execute(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("CPU processor dead: {e}")))?;
            }
            Task::ProveSegment(task) => {
                self.cpu_queue
                    .send(CpuTaskMsg {
                        header: msg.header,
                        task: CpuTask::Preflight(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("CPU processor dead: {e}")))?;
            }
            Task::Lift(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Lift(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
            Task::Join(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Join(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
            Task::ProveKeccak(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::ProveKeccak(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
            Task::Union(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Union(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
            Task::Resolve(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::Resolve(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
            Task::ShrinkWrap(task) => {
                self.gpu_queue
                    .send(GpuTaskMsg {
                        header: msg.header,
                        task: GpuTask::ShrinkWrap(task),
                        to_reserve,
                        reserved: vec![],
                        tracing: msg.tracing,
                    })
                    .await
                    .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;
            }
        }
        Ok(())
    }
}

struct TaskTracer {
    span: BoxedSpan,
}

impl TaskTracer {
    fn new(tracing: &job::tracer::SavedContext, name: impl Into<Cow<'static, str>>) -> Self {
        let ctx = tracing.to_context();
        let tracer = opentelemetry::global::tracer("worker");

        let span = tracer.start_with_context(name, &ctx);
        Self { span }
    }
}

impl Drop for TaskTracer {
    fn drop(&mut self) {
        self.span.end();
    }
}

struct GpuProcessor {
    factory: ActorRef<RemoteFactoryActor>,
    allocator: ActorRef<RemoteAllocatorActor>,
    delay: Option<DevModeDelay>,
    worker_id: WorkerId,
}

impl GpuProcessor {
    fn new(
        factory: ActorRef<RemoteFactoryActor>,
        allocator: ActorRef<RemoteAllocatorActor>,
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
        payload: TaskResult<TaskDone>,
        hardware_reservations: Vec<HardwareReservation>,
    ) -> Result<()> {
        let global_id = header.global_id;
        self.factory.tell(TaskDoneMsg { header, payload }).await?;
        self.allocator
            .tell(DeallocateHardware {
                worker_id: self.worker_id,
                task_id: global_id,
                hardware_reservations,
            })
            .await?;
        self.allocator
            .tell(EndTask {
                worker_id: self.worker_id,
                task_id: global_id,
            })
            .await?;
        Ok(())
    }

    async fn process_tasks(&self, mut recv: Receiver<GpuTaskMsg>) -> Result<()> {
        while let Some(msg) = recv.recv().await {
            self.process_task(msg).await?;
        }
        Ok(())
    }

    async fn process_task(&self, mut msg: GpuTaskMsg) -> Result<()> {
        let allocate_tracer = TaskTracer::new(&msg.tracing, "allocate GPU");
        tracing::info!(
            "ALLOCATE: {} wait for {:?}",
            &self.worker_id,
            &msg.to_reserve
        );
        self.allocator
            .ask(AllocateHardware {
                worker_id: self.worker_id,
                task_id: msg.header.global_id,
                hardware_reservations: msg.to_reserve.clone(),
            })
            .await??;
        drop(allocate_tracer);

        let _tracer = TaskTracer::new(
            &msg.tracing,
            format!("WorkerGPU({:?})", msg.header.task_kind),
        );

        msg.reserved.extend(std::mem::take(&mut msg.to_reserve));

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

        self.send_done(header, result, msg.reserved).await?;

        Ok(())
    }

    async fn prove_segment_core(
        &self,
        header: TaskHeader,
        task: ProveSegmentCoreTask,
    ) -> TaskResult<TaskDone> {
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
        .map_err(|e| Error::new(format!("JoinHandle error: prove_segment task: {e}")))??;
        Ok(TaskDone::ProveSegment(Box::new(receipt)))
    }

    async fn prove_keccak(
        &self,
        header: TaskHeader,
        task: Arc<ProveKeccakTask>,
    ) -> TaskResult<TaskDone> {
        let index = task.index;
        tracing::info!("ProveKeccak: {index}");
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt =
            tokio::task::spawn_blocking(move || prover.get()?.prove_keccak(&task.request))
                .await
                .map_err(|e| Error::new(format!("JoinHandle error: prove_keccak task: {e}")))??;
        Ok(TaskDone::ProveKeccak(Arc::new(ProveKeccakDone {
            index,
            receipt,
        })))
    }

    async fn lift(&self, header: TaskHeader, task: Arc<LiftTask>) -> TaskResult<TaskDone> {
        tracing::info!("Lift: {}", task.receipt.index);
        self.task_start(header.clone()).await?;
        let segment_idx = task.receipt.index;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || prover.get()?.lift(&task.receipt))
            .await
            .map_err(|e| Error::new(format!("JoinHandle error: lift task: {e}")))??;
        Ok(TaskDone::Lift(Box::new(JoinNode {
            range: (segment_idx..segment_idx + 1).into(),
            receipt,
        })))
    }

    async fn join(&self, header: TaskHeader, task: Arc<JoinTask>) -> TaskResult<TaskDone> {
        let range = task.range;
        tracing::info!("Join: {range:?}");
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.join(&task.receipts[0], &task.receipts[1])
        })
        .await
        .map_err(|e| Error::new(format!("JoinHandle error: join task: {e}")))??;
        Ok(TaskDone::Join(Box::new(JoinNode { range, receipt })))
    }

    async fn union(&self, header: TaskHeader, task: Arc<UnionTask>) -> TaskResult<TaskDone> {
        let height = task.height;
        let pos = task.pos;
        tracing::info!("Union: {height}/{pos}");
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.union(&task.receipts[0], &task.receipts[1])
        })
        .await
        .map_err(|e| Error::new(format!("JoinHandle error: union task: {e}")))??;
        Ok(TaskDone::Union(Arc::new(UnionDone {
            height,
            pos,
            receipt,
        })))
    }

    async fn resolve(&self, header: TaskHeader, task: Arc<ResolveTask>) -> TaskResult<TaskDone> {
        tracing::info!("Resolve: {:?}", header.global_id.task_id);
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let receipt = tokio::task::spawn_blocking(move || {
            prover.get()?.resolve(&task.conditional, &task.assumption)
        })
        .await
        .map_err(|e| Error::new(format!("JoinHandle error: resolve task: {e}")))??;
        Ok(TaskDone::Resolve(Arc::new(receipt)))
    }

    async fn shrink_wrap(
        &self,
        header: TaskHeader,
        task: Arc<ShrinkWrapTask>,
    ) -> TaskResult<TaskDone> {
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
                .map_err(|_| {
                    Error::new(format!("JoinHandle error: shrink_wrap({task_kind:?}) task"))
                })??;
        Ok(TaskDone::ShrinkWrap(Arc::new(receipt)))
    }
}

#[derive(Clone)]
struct CpuProcessor {
    factory: ActorRef<RemoteFactoryActor>,
    allocator: ActorRef<RemoteAllocatorActor>,
    delay: Option<DevModeDelay>,
    worker_id: WorkerId,

    gpu_queue: Sender<GpuTaskMsg>,
}

impl CpuProcessor {
    fn new(
        factory: ActorRef<RemoteFactoryActor>,
        allocator: ActorRef<RemoteAllocatorActor>,
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

    async fn task_start(&self, header: TaskHeader) -> Result<()> {
        self.send_update(header, TaskUpdate::Start).await
    }

    async fn send_update(&self, header: TaskHeader, payload: TaskUpdate) -> Result<()> {
        Ok(self.factory.tell(TaskUpdateMsg { header, payload }).await?)
    }

    async fn send_done(
        &self,
        header: TaskHeader,
        payload: TaskResult<TaskDone>,
        hardware_reservations: Vec<HardwareReservation>,
    ) -> Result<()> {
        let global_id = header.global_id;
        self.factory.tell(TaskDoneMsg { header, payload }).await?;
        self.allocator
            .tell(DeallocateHardware {
                worker_id: self.worker_id,
                task_id: global_id,
                hardware_reservations,
            })
            .await?;
        self.allocator
            .tell(EndTask {
                worker_id: self.worker_id,
                task_id: global_id,
            })
            .await?;

        Ok(())
    }

    async fn process_tasks(&self, mut recv: Receiver<CpuTaskMsg>) -> Result<()> {
        while let Some(msg) = recv.recv().await {
            self.process_task(msg).await?;
        }
        Ok(())
    }

    async fn process_task(&self, mut msg: CpuTaskMsg) -> Result<()> {
        let mut to_reserve = vec![];

        for r in std::mem::take(&mut msg.to_reserve) {
            if matches!(r, HardwareReservation::Cpu { .. }) {
                to_reserve.push(r);
            } else {
                msg.to_reserve.push(r);
            }
        }

        let allocate_tracer = TaskTracer::new(&msg.tracing, "allocate CPU");
        tracing::info!("ALLOCATE: {} wait for {to_reserve:?}", &self.worker_id);
        self.allocator
            .ask(AllocateHardware {
                worker_id: self.worker_id,
                task_id: msg.header.global_id,
                hardware_reservations: to_reserve.clone(),
            })
            .await??;
        drop(allocate_tracer);

        msg.reserved.extend(to_reserve);

        let header = msg.header.clone();

        let processor = self.clone();

        let tracer = TaskTracer::new(
            &msg.tracing,
            format!("WorkerCPU({:?})", msg.header.task_kind),
        );
        tokio::task::spawn(async move {
            let res = processor.run_task(msg, header).await;
            if let Err(error) = res {
                tracing::error!("CPU task runner failed: {error}");
            }

            drop(tracer);
        });

        Ok(())
    }

    async fn run_task(&self, msg: CpuTaskMsg, header: TaskHeader) -> Result<()> {
        let result = match msg.task {
            CpuTask::Execute(task) => self.execute(msg.header, task).await,
            CpuTask::Preflight(task) => {
                if let Err(error) = self
                    .preflight(
                        msg.header,
                        task,
                        msg.to_reserve.clone(),
                        msg.reserved.clone(),
                        msg.tracing.clone(),
                    )
                    .await
                {
                    self.send_done(header, Err(error), msg.reserved).await?;
                }
                return Ok(());
            }
        };
        self.send_done(header, result, msg.reserved).await?;

        Ok(())
    }

    async fn execute(&self, header: TaskHeader, task: Arc<ExecuteTask>) -> TaskResult<TaskDone> {
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
                factory.tell_blocking(msg)?;
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
        .map_err(|e| Error::new(format!("JoinHandle error: execute task: {e}")))?;
        Ok(TaskDone::Session(Arc::new(session?)))
    }

    async fn preflight(
        &self,
        header: TaskHeader,
        task: Arc<ProveSegmentTask>,
        to_reserve: Vec<HardwareReservation>,
        reserved: Vec<HardwareReservation>,
        tracing: job::tracer::SavedContext,
    ) -> TaskResult<()> {
        tracing::info!("Preflight: {}", task.segment.index);
        self.task_start(header.clone()).await?;
        let prover = Prover { delay: self.delay };
        let preflight_results = tokio::task::spawn_blocking(move || -> Result<_> {
            Ok(Box::new(prover.get()?.segment_preflight(&task.segment)?))
        })
        .await
        .map_err(|e| Error::new(format!("JoinHandle error: preflight task: {e}")))??;
        self.gpu_queue
            .send(GpuTaskMsg {
                header,
                task: GpuTask::ProveSegmentCore(ProveSegmentCoreTask { preflight_results }),
                to_reserve,
                reserved,
                tracing,
            })
            .await
            .map_err(|e| Error::new(format!("GPU processor dead: {e}")))?;

        Ok(())
    }
}

struct Coprocessor {
    factory: ActorRef<RemoteFactoryActor>,
    header: TaskHeader,
}

impl CoprocessorCallback for Coprocessor {
    fn prove_keccak(&mut self, request: ProveKeccakRequest) -> anyhow::Result<()> {
        use anyhow::Context as _;

        self.factory
            .tell_blocking(TaskUpdateMsg {
                header: self.header.clone(),
                payload: TaskUpdate::Keccak(request),
            })
            .context("Failed to send ProveKeccakRequest")
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

pub type RemoteWorkerActor = RemoteActor<WorkerActor>;

remote_actor_tell!(RemoteActor<WorkerActor>, TaskMsg, RemoteWorkerRequest);
