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

// Something is going on with the axum code triggering this
#![allow(clippy::diverging_sub_expression)]

//! This module contains a piece of the actor system known as the "allocator"
//!
//! The allocator exists to provide coordination between different versions of r0vm actor clusters.
//! To support fulfilling proof requests across different r0vm versions, multiple clusters of r0vm
//! must be run on the same hardware. To handle this scenario the allocator takes care of the
//! following responsibilities:
//!
//! - Routing proof requests to the appropriate versioned r0vm cluster.
//! - Ensuring that workers which share hardware resources (such as GPUSs) do not schedule tasks
//!   using said resources simultaneously.
//!
//! To accomplish this, the allocator must communicate with managers and workers.
//!
//! Workers advertise to the allocator what hardware resources they are using. Workers also
//! allocate and decallocate hardware time from the allocator. Managers receive proof requests from
//! the allocator, and they also talk to the allocator to make scheduling decisions.
//!

use std::collections::{BTreeMap, HashMap, HashSet, VecDeque, btree_map, hash_map};
use std::fmt;
use std::net::SocketAddr;
use std::net::{IpAddr, Ipv4Addr};
use std::str::FromStr;
use std::sync::Arc;

use super::{
    RemoteActor, RemoteAllocatorRequest, RpcDisconnect,
    actor::{Actor, ActorRef, Context, Message, ReplySender},
    error::{Error, Result},
    protocol::{GlobalId, WorkerId, WorkerIdFmt},
    remote_actor_ask,
};
use derive_more::{Add, AddAssign, From, Sub, SubAssign};
use http_body_util::BodyExt as _;
use indexmap::IndexMap;
use serde::{Deserialize, Serialize};
use tokio::net::TcpListener;
use url::Url;
use uuid::Uuid;

/// This is the URL path where requests are proxied to a manager of a specified version.
pub const PROXY_URL_PATH: &str = "/r0vm";

/// This value is the globally unique immutable alphanumeric identifier of the GPU. It does not
/// correspond to any physical label on the board.
#[derive(Clone, Debug, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct GpuUuid(Uuid);

impl GpuUuid {
    pub fn new_fake() -> Self {
        Self(Uuid::new_v4())
    }
}

impl FromStr for GpuUuid {
    type Err = Error;

    fn from_str(s: &str) -> Result<Self> {
        let rest = s
            .strip_prefix("GPU-")
            .ok_or_else(|| Error::new("UUID doesn't start with GPU-"))?;
        Ok(Self(Uuid::from_str(rest)?))
    }
}

impl fmt::Display for GpuUuid {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        if f.alternate() {
            let gpu_id = self.0.to_string();
            let gpu_short = &gpu_id[gpu_id.len() - 5..];
            write!(f, "GPU-{gpu_short}")
        } else {
            write!(f, "GPU-{}", &self.0)
        }
    }
}

/// Represents the ability schedule something to run on the GPU.
#[derive(
    Add,
    AddAssign,
    Sub,
    SubAssign,
    Copy,
    Clone,
    Default,
    Debug,
    PartialEq,
    Eq,
    PartialOrd,
    Ord,
    Serialize,
    Deserialize,
    From,
)]
pub struct GpuTokens(u64);

impl GpuTokens {
    pub const ZERO: Self = Self(0);

    fn checked_sub(self, other: Self) -> Option<Self> {
        self.0.checked_sub(other.0).map(Self)
    }
}

/// Represents a GPU on some machine.
#[derive(Clone, Serialize, Deserialize)]
pub struct GpuSpec {
    /// The name of the GPU for logging purposes
    pub name: String,
    /// A globally unique ID representing the GPU.
    pub uuid: GpuUuid,
    /// Number of GPU tokens
    pub tokens: GpuTokens,
}

/// Represents a count of CPU cores.
#[derive(
    Add,
    AddAssign,
    Sub,
    SubAssign,
    Copy,
    Clone,
    Debug,
    PartialEq,
    Eq,
    PartialOrd,
    Ord,
    Serialize,
    Deserialize,
    From,
)]
pub struct CpuCores(u64);

impl CpuCores {
    pub const ZERO: Self = Self(0);

    fn checked_sub(self, other: Self) -> Option<Self> {
        self.0.checked_sub(other.0).map(Self)
    }
}

/// Represents a CPU on some machine.
#[derive(Clone, Serialize, Deserialize)]
pub struct CpuSpec {
    /// The number of cores this CPU has.
    pub cores: CpuCores,
}

#[derive(Clone, Serialize, Deserialize, From)]
pub enum HardwareResource {
    Gpu(GpuSpec),
    Cpu(CpuSpec),
}

#[derive(Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct MachineId {
    ip: IpAddr,
}

impl MachineId {
    fn new_localhost() -> Self {
        Self {
            ip: IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)),
        }
    }
}

/// Description of a hardware resource to reserve while a worker is allocated.
#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum HardwareReservation {
    /// A portion of a GPU is reserved.
    Gpu { id: GpuUuid, tokens: GpuTokens },
    /// A portion of a CPU is reserved.
    Cpu { cores: CpuCores },
}

/// The allocator's representation of a task.
struct Task {
    /// A description of the task for display purposes
    description: String,

    /// GPU tokens being used the task
    used_gpu_tokens: HashMap<GpuUuid, GpuTokens>,

    /// CPU cores being used the task
    used_cores: CpuCores,
}

impl Task {
    fn cpu_allocated(&self) -> bool {
        self.used_cores > CpuCores::ZERO
    }

    fn gpu_allocated(&self) -> bool {
        self.used_gpu_tokens.values().any(|t| *t > GpuTokens::ZERO)
    }
    fn hw_allocated(&self) -> bool {
        self.cpu_allocated() || self.gpu_allocated()
    }
}

impl fmt::Display for Task {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut hw = String::new();

        if self.hw_allocated() {
            hw += ":";
        }

        if self.cpu_allocated() {
            hw += " CPU in-use";
        }
        if self.gpu_allocated() {
            hw += " GPU in-use";
        }

        write!(f, "{}{hw}", &self.description,)
    }
}

/// The allocator's representation of a worker.
struct Worker {
    /// If the worker is on a remote machine, this is the socket address of the RPC connection
    remote_address: Option<SocketAddr>,
    /// What machine is this worker running on
    machine: MachineId,
    /// What hardware does this worker have access to
    hardware: Vec<HardwareResource>,
    /// What tasks (tasks) are currently running on this worker.
    tasks: IndexMap<GlobalId, Task>,
    /// From what version of the software is this worker and what release channel
    deployment_version: DeploymentVersion,
}

impl Worker {
    fn new(
        remote_address: Option<SocketAddr>,
        machine: MachineId,
        hardware: Vec<HardwareResource>,
        deployment_version: DeploymentVersion,
    ) -> Self {
        Self {
            remote_address,
            tasks: IndexMap::new(),
            machine,
            hardware,
            deployment_version,
        }
    }

    fn to_get_status(&self, id: WorkerId) -> GetStatusWorker {
        let host = self
            .remote_address
            .map(|a| a.ip().to_string())
            .unwrap_or("localhost".into());
        let port = self.remote_address.map(|a| a.port());

        let hardware = self
            .hardware
            .iter()
            .filter_map(|h| match h {
                HardwareResource::Gpu(gpu) => Some(format!("{:#}", &gpu.uuid)),
                _ => None,
            })
            .collect::<Vec<_>>();

        let tasks = self.tasks.values().map(|t| t.to_string()).collect();
        GetStatusWorker {
            id: format!("{:#}", WorkerIdFmt(id)),
            hardware,
            host,
            port,
            version: self.deployment_version.clone(),
            tasks,
        }
    }
}

struct Manager {
    endpoint: Option<Url>,
    remote_address: Option<SocketAddr>,
    rpc_port: Option<u16>,
}

struct Cpu {
    total_cores: CpuCores,
    free_cores: CpuCores,
}

struct Gpu {
    max_tokens: GpuTokens,
    free_tokens: GpuTokens,
}

struct PendingAllocation {
    request: AllocateHardware,
    reply_sender: Option<ReplySender<Result<()>>>,
}

#[derive(Copy, Clone, PartialEq, Eq)]
enum HardwareFilter {
    Cpu,
    Gpu,
}

#[derive(Default)]
struct ManagerMap(HashMap<String, BTreeMap<semver::Version, Manager>>);

impl ManagerMap {
    fn get(&self, key: &DeploymentVersion) -> Option<&Manager> {
        self.0.get(&key.release_channel)?.get(&key.zkvm_version)
    }

    fn entry(&mut self, key: DeploymentVersion) -> btree_map::Entry<'_, semver::Version, Manager> {
        self.0
            .entry(key.release_channel)
            .or_default()
            .entry(key.zkvm_version)
    }

    fn retain(&mut self, mut f: impl FnMut(&DeploymentVersion, &mut Manager) -> bool) {
        for (release_channel, managers) in &mut self.0 {
            managers.retain(|version, manager| {
                let sw_version = DeploymentVersion {
                    release_channel: release_channel.clone(),
                    zkvm_version: version.clone(),
                };
                f(&sw_version, manager)
            });
        }
        self.0.retain(|_, managers| !managers.is_empty());
    }

    fn iter_channel(
        &self,
        release_channel: &str,
    ) -> Option<btree_map::Iter<'_, semver::Version, Manager>> {
        self.0.get(release_channel).map(|managers| managers.iter())
    }
}

pub struct AllocatorActor {
    default_release_channel: String,
    workers: HashMap<WorkerId, Worker>,
    managers: ManagerMap,
    gpus: HashMap<GpuUuid, Gpu>,
    cpus: HashMap<MachineId, Cpu>,
    http_client: Arc<reqwest::Client>,

    pending: VecDeque<PendingAllocation>,
}

impl Actor for AllocatorActor {}

impl AllocatorActor {
    pub fn new(default_release_channel: impl Into<String>) -> Self {
        Self {
            default_release_channel: default_release_channel.into(),
            workers: HashMap::new(),
            managers: Default::default(),
            gpus: HashMap::new(),
            cpus: HashMap::new(),
            http_client: Arc::new(reqwest::Client::new()),
            pending: VecDeque::new(),
        }
    }

    fn get_workers_using_gpu(&self, matching_uuid: &GpuUuid) -> HashSet<WorkerId> {
        self.workers
            .iter()
            .filter(|(_, w)| {
                w.hardware.iter().any(|h| {
                    matches!(
                        h,
                        HardwareResource::Gpu(GpuSpec { uuid, .. }) if uuid == matching_uuid
                    )
                })
            })
            .map(|(w, _)| *w)
            .collect()
    }

    fn get_workers_using_machine(&self, machine_id: &MachineId) -> HashSet<WorkerId> {
        self.workers
            .iter()
            .filter(|(_, w)| &w.machine == machine_id)
            .map(|(w, _)| *w)
            .collect()
    }

    /// The number of tasks the hardware this worker is using is currently running.
    fn get_worker_num_hardware_tasks(
        &self,
        worker_id: &WorkerId,
        hardware_filter: HardwareFilter,
    ) -> Result<usize> {
        let worker = self
            .workers
            .get(worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {worker_id}")))?;

        let mut associated_workers = HashSet::new();
        for hardware in &worker.hardware {
            match hardware {
                HardwareResource::Gpu(gpu) => {
                    if hardware_filter == HardwareFilter::Gpu {
                        associated_workers.extend(self.get_workers_using_gpu(&gpu.uuid));
                    }
                }
                HardwareResource::Cpu(_) => {
                    if hardware_filter == HardwareFilter::Cpu {
                        associated_workers.extend(self.get_workers_using_machine(&worker.machine));
                    }
                }
            }
        }

        Ok(associated_workers
            .iter()
            .map(|w| {
                self.workers
                    .get(w)
                    .expect("worker should still exist")
                    .tasks
                    .len()
            })
            .sum())
    }

    /// The number of tasks this worker is using is currently running.
    fn get_worker_num_tasks(&self, worker_id: &WorkerId) -> Result<usize> {
        let worker = self
            .workers
            .get(worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {worker_id}")))?;

        Ok(worker.tasks.len())
    }

    /// Add to the tasks we are tracking for this worker
    fn add_worker_task(
        &mut self,
        worker_id: &WorkerId,
        task_id: GlobalId,
        description: String,
    ) -> Result<()> {
        let worker = self
            .workers
            .get_mut(worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {worker_id}")))?;
        if let indexmap::map::Entry::Vacant(e) = worker.tasks.entry(task_id) {
            e.insert(Task {
                description,
                used_gpu_tokens: HashMap::new(),
                used_cores: CpuCores::ZERO,
            });
        } else {
            return Err(Error::new("duplicate task_id"));
        }
        Ok(())
    }

    /// Learn about a new GPU.
    fn add_gpu(&mut self, gpu: GpuSpec) {
        if let hash_map::Entry::Vacant(e) = self.gpus.entry(gpu.uuid) {
            e.insert(Gpu {
                max_tokens: gpu.tokens,
                free_tokens: gpu.tokens,
            });
        }
    }

    /// Learn about a new CPU.
    fn add_cpu(&mut self, machine_id: MachineId, cpu: CpuSpec) {
        if let hash_map::Entry::Vacant(e) = self.cpus.entry(machine_id) {
            e.insert(Cpu {
                total_cores: cpu.cores,
                free_cores: cpu.cores,
            });
        }
    }

    /// Learn about new hardware.
    fn add_hardware(&mut self, machine: &MachineId, hardware: Vec<HardwareResource>) {
        for h in hardware {
            match h {
                HardwareResource::Gpu(gpu) => self.add_gpu(gpu),
                HardwareResource::Cpu(cpu) => self.add_cpu(machine.clone(), cpu),
            }
        }
    }

    fn maybe_allocate(&mut self, request: &AllocateHardware) -> Result<bool> {
        let worker = self
            .workers
            .get_mut(&request.worker_id)
            .expect("all pending requests should be for workers that are still connected");

        let task = worker
            .tasks
            .get_mut(&request.task_id)
            .expect("all pending requests should be for tasks which are still scheduled");

        for res in &request.hardware_reservations {
            match res {
                HardwareReservation::Gpu { id, tokens } => {
                    let gpu = self
                        .gpus
                        .get(id)
                        .ok_or_else(|| Error::new(format!("unknown GPU {id}")))?;
                    if &gpu.free_tokens < tokens {
                        return Ok(false);
                    }
                }
                HardwareReservation::Cpu { cores } => {
                    let cpu = self
                        .cpus
                        .get(&worker.machine)
                        .expect("all worker CPUs should exist");
                    if &cpu.free_cores < cores {
                        return Ok(false);
                    }
                }
            }
        }

        for res in &request.hardware_reservations {
            match res {
                HardwareReservation::Gpu { id, tokens } => {
                    let gpu = self
                        .gpus
                        .get_mut(id)
                        .ok_or_else(|| Error::new(format!("unknown GPU {id}")))?;
                    gpu.free_tokens -= *tokens;
                    *task.used_gpu_tokens.entry(id.clone()).or_default() += *tokens;
                }
                HardwareReservation::Cpu { cores } => {
                    let cpu = self
                        .cpus
                        .get_mut(&worker.machine)
                        .expect("all worker CPUs should exist");
                    cpu.free_cores -= *cores;
                    task.used_cores += *cores;
                }
            }
        }

        Ok(true)
    }

    fn maybe_allocate_many(&mut self) {
        for p in std::mem::take(&mut self.pending) {
            match self.maybe_allocate(&p.request) {
                Ok(true) => {
                    if let Some(reply_sender) = p.reply_sender {
                        reply_sender.send(Ok(()));
                    }
                }
                Err(error) => {
                    if let Some(reply_sender) = p.reply_sender {
                        reply_sender.send(Err(error));
                    }
                }
                Ok(false) => self.pending.push_back(p),
            }
        }
    }

    fn get_gpu_tasks(&self, id: &GpuUuid) -> impl Iterator<Item = &Task> {
        self.workers.values().flat_map(|worker| {
            worker
                .tasks
                .values()
                .filter(|t| t.used_gpu_tokens.contains_key(id))
        })
    }
}

/// Request to register a worker with the allocator.
#[derive(Serialize, Deserialize)]
pub struct RegisterWorker {
    pub remote_address: Option<SocketAddr>,
    pub worker_id: WorkerId,
    pub hardware: Vec<HardwareResource>,
    pub deployment_version: DeploymentVersion,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct ManagerAddress {
    pub ip: Option<IpAddr>,
    pub port: u16,
}

#[derive(Serialize, Deserialize)]
pub struct RegisterWorkerReply {
    pub manager_address: Option<ManagerAddress>,
}

impl Message<RegisterWorker> for AllocatorActor {
    type Reply = Result<RegisterWorkerReply>;

    async fn handle(&mut self, msg: RegisterWorker, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.register_worker(msg))
    }
}

impl AllocatorActor {
    fn register_worker(&mut self, msg: RegisterWorker) -> Result<RegisterWorkerReply> {
        let machine = match &msg.remote_address {
            Some(addr) => MachineId { ip: addr.ip() },
            None => MachineId::new_localhost(),
        };

        if let hash_map::Entry::Vacant(e) = self.workers.entry(msg.worker_id) {
            e.insert(Worker::new(
                msg.remote_address,
                machine.clone(),
                msg.hardware.clone(),
                msg.deployment_version.clone(),
            ));
            let num_cpus = msg
                .hardware
                .iter()
                .filter(|h| matches!(h, HardwareResource::Cpu(_)))
                .count();
            if num_cpus > 1 {
                return Err(Error::new("cannot register worker with two CPUs"));
            }
            self.add_hardware(&machine, msg.hardware);
        } else {
            return Err(Error::new(format!(
                "duplicate registration from worker {} at {}",
                msg.worker_id, machine.ip
            )));
        }

        let mut manager_address = None;
        if let Some(manager) = self.managers.get(&msg.deployment_version)
            && let Some(rpc_port) = manager.rpc_port
        {
            manager_address = Some(ManagerAddress {
                ip: manager.remote_address.map(|a| a.ip()),
                port: rpc_port,
            });
        }

        Ok(RegisterWorkerReply { manager_address })
    }
}

/// Choose a worker to send work to from the given candidate pool.
///
/// The idea is for the allocator to choose which worker is the least busy. The allocator reserves
/// the right to not reply immediately. It could be that all the workers already have deep queues
/// and the best move is to wait until one becomes less busy.
#[derive(Serialize, Deserialize, PartialEq, Eq, Debug)]
pub struct ScheduleTask {
    pub candidates: Vec<WorkerId>,
    pub task_id: GlobalId,
    pub description: String,
}

/// Reply when a worker is successfully chosen.
#[derive(Serialize, Deserialize, Debug)]
pub struct ScheduleTaskReply {
    pub worker_id: WorkerId,
}

impl Message<ScheduleTask> for AllocatorActor {
    type Reply = Result<ScheduleTaskReply>;

    async fn handle(&mut self, msg: ScheduleTask, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.schedule_task(msg))
    }
}

impl AllocatorActor {
    fn schedule_task(&mut self, msg: ScheduleTask) -> Result<ScheduleTaskReply> {
        // Choose a worker which is least busy. We prefer a quiet GPU over a quiet CPU in this
        // selection.
        #[derive(PartialEq, Eq, PartialOrd, Ord, Debug)]
        struct CandidateWorker {
            gpu_tasks: usize,
            machine_tasks: usize,
            worker_tasks: usize,
            id: WorkerId,
        }

        let mut workers = msg
            .candidates
            .into_iter()
            .map(|c| -> Result<_> {
                Ok(CandidateWorker {
                    id: c,
                    gpu_tasks: self.get_worker_num_hardware_tasks(&c, HardwareFilter::Gpu)?,
                    machine_tasks: self.get_worker_num_hardware_tasks(&c, HardwareFilter::Cpu)?,
                    worker_tasks: self.get_worker_num_tasks(&c)?,
                })
            })
            .filter_map(|res| match res {
                Ok(w) => Some(w),
                Err(error) => {
                    tracing::error!("Not selecting worker due to error: {error}");
                    None
                }
            })
            .collect::<Vec<_>>();

        if workers.is_empty() {
            return Err(Error::new("no eligible candidate workers"));
        }

        workers.sort();
        let chosen_worker = workers[0].id;

        // Count that this worker has a new task now.
        self.add_worker_task(&chosen_worker, msg.task_id, msg.description)?;

        Ok(ScheduleTaskReply {
            worker_id: chosen_worker,
        })
    }
}

/// Mark the given hardware resources as being used. If the given hardware resources are already
/// allocated, this message is only replied to once they are free.
#[derive(Serialize, Deserialize)]
pub struct AllocateHardware {
    pub worker_id: WorkerId,
    pub task_id: GlobalId,
    pub hardware_reservations: Vec<HardwareReservation>,
}

impl Message<AllocateHardware> for AllocatorActor {
    type Reply = Result<()>;

    async fn handle(&mut self, request: AllocateHardware, ctx: &mut Context<Self, Self::Reply>) {
        match self.validate_allocation_request(&request) {
            Ok(()) => {
                let reply_sender = ctx.reply_sender();
                self.pending.push_back(PendingAllocation {
                    request,
                    reply_sender,
                });
                self.maybe_allocate_many();
            }
            Err(error) => ctx.reply(Err(error)),
        }
    }
}

impl AllocatorActor {
    fn validate_allocation_request(&mut self, request: &AllocateHardware) -> Result<()> {
        let worker = self
            .workers
            .get_mut(&request.worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {}", request.worker_id)))?;
        if !worker.tasks.contains_key(&request.task_id) {
            return Err(Error::new(
                "allocation request associated with task not running on worker",
            ));
        }

        Ok(())
    }
}

/// The given hardware resources are free and can be used again in allocate.
#[derive(Serialize, Deserialize)]
pub struct DeallocateHardware {
    pub worker_id: WorkerId,
    pub task_id: GlobalId,
    pub hardware_reservations: Vec<HardwareReservation>,
}

impl Message<DeallocateHardware> for AllocatorActor {
    type Reply = Result<()>;

    async fn handle(&mut self, msg: DeallocateHardware, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.deallocate_hardware(msg))
    }
}

impl AllocatorActor {
    fn deallocate_hardware(&mut self, msg: DeallocateHardware) -> Result<()> {
        let worker_id = msg.worker_id;
        let worker = self
            .workers
            .get_mut(&worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {worker_id}")))?;

        let task = worker
            .tasks
            .get_mut(&msg.task_id)
            .ok_or_else(|| Error::new(format!("worker not running task: {}", msg.task_id)))?;

        for res in msg.hardware_reservations {
            match res {
                HardwareReservation::Gpu { id, tokens } => {
                    let gpu = self
                        .gpus
                        .get_mut(&id)
                        .ok_or_else(|| Error::new(format!("unknown GPU {id}")))?;

                    let worker_tokens = task
                        .used_gpu_tokens
                        .get_mut(&id)
                        .ok_or_else(|| Error::new("worker returning GPU tokens it doesn't have"))?;
                    *worker_tokens = worker_tokens
                        .checked_sub(tokens)
                        .ok_or_else(|| Error::new("worker returning GPU tokens it doesn't have"))?;
                    if *worker_tokens == GpuTokens::ZERO {
                        task.used_gpu_tokens.remove(&id);
                    }

                    gpu.free_tokens += tokens;
                    assert!(gpu.free_tokens <= gpu.max_tokens);
                }
                HardwareReservation::Cpu { cores } => {
                    let cpu = self
                        .cpus
                        .get_mut(&worker.machine)
                        .expect("all worker CPUs should exist");

                    task.used_cores = task
                        .used_cores
                        .checked_sub(cores)
                        .ok_or_else(|| Error::new("worker returning CPU cores it doesn't have"))?;

                    cpu.free_cores += cores;
                    assert!(cpu.free_cores <= cpu.total_cores);
                }
            }
        }

        self.maybe_allocate_many();

        Ok(())
    }
}

/// The given task has completed
#[derive(Serialize, Deserialize)]
pub struct EndTask {
    pub worker_id: WorkerId,
    pub task_id: GlobalId,
}

impl Message<EndTask> for AllocatorActor {
    type Reply = Result<()>;

    async fn handle(&mut self, msg: EndTask, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.end_task(msg))
    }
}

impl AllocatorActor {
    fn end_task(&mut self, msg: EndTask) -> Result<()> {
        let worker_id = msg.worker_id;
        let worker = self
            .workers
            .get_mut(&worker_id)
            .ok_or_else(|| Error::new(format!("unknown worker {worker_id}")))?;

        if self
            .pending
            .iter()
            .any(|req| req.request.task_id == msg.task_id)
        {
            return Err(Error::new(
                "attempting to end task which has a pending allocation",
            ));
        }

        let Some(task) = worker.tasks.get(&msg.task_id) else {
            return Err(Error::new(format!(
                "worker not running task: {}",
                msg.task_id
            )));
        };

        if task.hw_allocated() {
            return Err(Error::new(
                "attempting to end task which still has hardware allocated",
            ));
        }

        let removed = worker.tasks.shift_remove(&msg.task_id).is_some();
        assert!(removed);

        Ok(())
    }
}

/// A particular deployed version of r0vm
#[derive(Clone, Debug, Hash, PartialEq, Eq, PartialOrd, Ord, Serialize, Deserialize)]
pub struct DeploymentVersion {
    pub release_channel: String,
    pub zkvm_version: semver::Version,
}

impl DeploymentVersion {
    #[cfg(test)]
    pub fn new(release_channel: impl Into<String>, zkvm_version: semver::Version) -> Self {
        Self {
            release_channel: release_channel.into(),
            zkvm_version,
        }
    }
}

impl fmt::Display for DeploymentVersion {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}:{}", &self.release_channel, &self.zkvm_version)
    }
}

impl FromStr for DeploymentVersion {
    type Err = Error;

    fn from_str(s: &str) -> Result<Self> {
        let (release_channel, version) = s
            .rsplit_once(":")
            .ok_or_else(|| Error::new("missing ':'"))?;
        Ok(Self {
            release_channel: release_channel.into(),
            zkvm_version: version
                .parse()
                .map_err(|err| Error::new(format!("failed to parse version: {err}")))?,
        })
    }
}

#[test]
fn deployment_version_parse() {
    assert_eq!(
        DeploymentVersion::from_str("foo:1.2.3").unwrap(),
        DeploymentVersion::new("foo", semver::Version::new(1, 2, 3))
    );
    assert_eq!(
        DeploymentVersion::from_str("foo:bar:1.2.3").unwrap(),
        DeploymentVersion::new("foo:bar", semver::Version::new(1, 2, 3))
    );
    assert_eq!(
        DeploymentVersion::from_str("1.2.3")
            .unwrap_err()
            .to_string(),
        "missing ':'"
    );
    assert_eq!(
        DeploymentVersion::from_str("foo:").unwrap_err().to_string(),
        "failed to parse version: empty string, expected a semver version"
    );
}

#[derive(Serialize, Deserialize)]
pub struct RegisterManager {
    pub deployment_version: DeploymentVersion,
    pub path: String,
    pub api_port: Option<u16>,
    pub rpc_port: Option<u16>,
    pub remote_address: Option<SocketAddr>,
}

impl Message<RegisterManager> for AllocatorActor {
    type Reply = Result<()>;

    async fn handle(&mut self, msg: RegisterManager, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.register_manager(msg))
    }
}

impl AllocatorActor {
    fn register_manager(&mut self, msg: RegisterManager) -> Result<()> {
        if let btree_map::Entry::Vacant(e) = self.managers.entry(msg.deployment_version.clone()) {
            let host = msg
                .remote_address
                .map(|a| a.ip())
                .unwrap_or(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)));
            e.insert(Manager {
                endpoint: msg.api_port.map(|api_port| {
                    format!(
                        "http://{host}:{api_port}/{}",
                        msg.path.trim_start_matches('/')
                    )
                    .parse()
                    .expect("the formatted URL should always be valid")
                }),
                remote_address: msg.remote_address,
                rpc_port: msg.rpc_port,
            });
            tracing::info!(
                "Registered manager with version {} at addr={host} api_port={:?}, rpc_port={:?}",
                &msg.deployment_version,
                &msg.api_port,
                &msg.rpc_port
            );
        } else {
            return Err(Error::new(format!(
                "duplicate registration for manager with deployment version {}",
                msg.deployment_version
            )));
        }
        Ok(())
    }
}

impl Message<RpcDisconnect> for AllocatorActor {
    type Reply = ();

    async fn handle(&mut self, msg: RpcDisconnect, _ctx: &mut Context<Self, Self::Reply>) {
        self.maybe_remove_workers(&msg);
        self.maybe_remove_managers(&msg);
    }
}

impl AllocatorActor {
    fn maybe_remove_workers(&mut self, msg: &RpcDisconnect) {
        // Take out any workers with the given remote_address
        let mut workers_to_remove = vec![];
        for (worker_id, worker) in std::mem::take(&mut self.workers) {
            if worker.remote_address == Some(msg.remote_address) {
                workers_to_remove.push((worker_id, worker));
            } else {
                self.workers.insert(worker_id, worker);
            }
        }

        for (worker_id, worker) in workers_to_remove {
            // Remove any pending requests from this worker
            self.pending.retain(|r| r.request.worker_id != worker_id);

            // Return all tokens for any pending tasks
            for (_, task) in worker.tasks {
                for (uuid, tokens) in task.used_gpu_tokens {
                    let gpu = self.gpus.get_mut(&uuid).expect("all worker GPUs exist");
                    gpu.free_tokens += tokens;
                    assert!(gpu.free_tokens <= gpu.max_tokens);
                }
                if task.used_cores > CpuCores::ZERO {
                    let cpu = self
                        .cpus
                        .get_mut(&worker.machine)
                        .expect("all worker CPUs exist");

                    cpu.free_cores += task.used_cores;
                    assert!(cpu.free_cores <= cpu.total_cores);
                }
            }
        }

        // Now that potentially some tokens are returned, might be able to schedule some tasks
        self.maybe_allocate_many();
    }

    fn maybe_remove_managers(&mut self, msg: &RpcDisconnect) {
        self.managers
            .retain(|_, m| m.remote_address != Some(msg.remote_address));
    }
}

#[derive(Serialize, Deserialize)]
pub struct GetStatus;

#[derive(Serialize, Deserialize)]
pub struct GetStatusWorker {
    id: String,
    hardware: Vec<String>,
    host: String,
    port: Option<u16>,
    version: DeploymentVersion,
    tasks: Vec<String>,
}

#[derive(Serialize, Deserialize)]
pub struct GetStatusGpu {
    id: String,
    tasks: Vec<String>,
}

#[derive(Serialize, Deserialize)]
pub struct GetStatusReply {
    pub workers: Vec<GetStatusWorker>,
    pub gpus: Vec<GetStatusGpu>,
}

impl Message<GetStatus> for AllocatorActor {
    type Reply = Result<GetStatusReply>;

    async fn handle(&mut self, _msg: GetStatus, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(self.get_status())
    }
}

impl AllocatorActor {
    fn get_status(&mut self) -> Result<GetStatusReply> {
        let mut workers: Vec<_> = self
            .workers
            .iter()
            .map(|(worker_id, worker)| worker.to_get_status(*worker_id))
            .collect();
        workers.sort_by_key(|worker| worker.id.clone());

        let mut gpus: Vec<_> = self
            .gpus
            .keys()
            .map(|id| GetStatusGpu {
                id: format!("{id:#}"),
                tasks: self
                    .get_gpu_tasks(id)
                    .map(|t| t.description.clone())
                    .collect(),
            })
            .collect();
        gpus.sort_by_key(|gpu| gpu.id.clone());

        Ok(GetStatusReply { workers, gpus })
    }
}

#[cfg(test)]
mod allocation_tests {
    use super::*;
    use crate::actors::actor::{self, ActorRunner};

    fn test_gpu_id(n: u32) -> GpuUuid {
        assert!(n < 10);
        format!("GPU-deadbeef-0000-0000-0000-00000000000{n}")
            .parse()
            .unwrap()
    }

    fn test_worker_id(n: u32) -> WorkerId {
        assert!(n < 10);
        format!("00000000-0000-0000-0000-00000000000{n}")
            .parse()
            .unwrap()
    }

    fn test_task_id(i: u64, j: u64) -> GlobalId {
        GlobalId {
            job_id: format!("00000000-0000-0000-0000-00000000000{i}")
                .parse()
                .unwrap(),
            task_id: j,
        }
    }

    struct Fixture {
        workers: Vec<WorkerId>,
        worker_addresses: HashMap<WorkerId, SocketAddr>,
        alloc_ref: ActorRef<AllocatorActor>,
        alloc_runner: ActorRunner<AllocatorActor>,
    }

    impl Fixture {
        async fn new(worker_count: u32) -> Self {
            let (alloc_ref, mut alloc_runner) =
                actor::run(AllocatorActor::new("default-channel")).await;

            let workers: Vec<WorkerId> = (0..worker_count).map(test_worker_id).collect();
            let mut worker_addresses = HashMap::new();
            for (i, worker_id) in workers.iter().enumerate() {
                let worker_addr: SocketAddr =
                    format!("1.2.3.{}:100{}", i / 4, i % 4).parse().unwrap();
                alloc_ref
                    .ask_with_runner(
                        RegisterWorker {
                            worker_id: *worker_id,
                            remote_address: Some(worker_addr),
                            hardware: vec![
                                HardwareResource::Gpu(GpuSpec {
                                    name: "test GPU".into(),
                                    uuid: test_gpu_id(i as u32 / 2),
                                    tokens: GpuTokens(100),
                                }),
                                HardwareResource::Cpu(CpuSpec { cores: CpuCores(4) }),
                            ],
                            deployment_version: DeploymentVersion::new(
                                "test",
                                semver::Version::new(1, 2, 3),
                            ),
                        },
                        &mut alloc_runner,
                    )
                    .await
                    .unwrap()
                    .unwrap();
                worker_addresses.insert(*worker_id, worker_addr);
            }

            Self {
                workers,
                worker_addresses,
                alloc_ref,
                alloc_runner,
            }
        }

        async fn schedule_task(&mut self, i: u64, j: u64) -> ScheduleTaskReply {
            self.alloc_ref
                .ask_with_runner(
                    ScheduleTask {
                        candidates: self.workers.clone(),
                        task_id: test_task_id(i, j),
                        description: "test task".into(),
                    },
                    &mut self.alloc_runner,
                )
                .await
                .unwrap()
                .unwrap()
        }

        async fn end_task(&mut self, i: u64, j: u64, worker_id: WorkerId) -> Result<()> {
            self.alloc_ref
                .ask_with_runner(
                    EndTask {
                        worker_id,
                        task_id: test_task_id(i, j),
                    },
                    &mut self.alloc_runner,
                )
                .await
                .unwrap()
        }

        async fn disconnect_worker(&mut self, worker_id: WorkerId) {
            let remote_address = *self.worker_addresses.get(&worker_id).unwrap();
            self.alloc_ref
                .tell_with_runner(RpcDisconnect { remote_address }, &mut self.alloc_runner)
                .await
                .unwrap();
        }

        async fn allocate_hardware(&mut self, alloc: AllocateHardware) -> Result<()> {
            self.alloc_ref
                .ask_with_runner(alloc, &mut self.alloc_runner)
                .await
                .unwrap()
        }

        async fn deallocate_hardware(&mut self, dealloc: DeallocateHardware) -> Result<()> {
            self.alloc_ref
                .ask_with_runner(dealloc, &mut self.alloc_runner)
                .await
                .unwrap()
        }
    }

    #[tokio::test]
    async fn alloc_dealloc_realloc() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let response = fixture.schedule_task(1, 2).await;
        assert_eq!(response.worker_id, worker_id);

        let second_allocation = fixture
            .alloc_ref
            .ask_enqueue(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 2),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        fixture.alloc_runner.handle_one().await;

        assert!(!second_allocation.has_reply());

        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        second_allocation.recv().await.unwrap().unwrap();

        fixture.end_task(1, 1, worker_id).await.unwrap();

        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 2),
                hardware_reservations,
            })
            .await
            .unwrap();
        fixture.end_task(1, 2, worker_id).await.unwrap();
    }

    async fn double_dealloc(hardware_reservations: Vec<HardwareReservation>, expected_err: &str) {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        // deallocate again should be an error
        let err = fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations,
            })
            .await
            .unwrap_err();

        assert_eq!(err.to_string(), expected_err);
    }

    #[tokio::test]
    async fn end_task_before_dealloc() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        // trying to end before deallocating hardware is an error
        let err = fixture.end_task(1, 1, worker_id).await.unwrap_err();
        assert_eq!(
            err.to_string(),
            "attempting to end task which still has hardware allocated"
        );
    }

    #[tokio::test]
    async fn end_task_before_full_dealloc() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(50),
        }];
        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations,
            })
            .await
            .unwrap();

        // trying to end before deallocating hardware is an error
        let err = fixture.end_task(1, 1, worker_id).await.unwrap_err();
        assert_eq!(
            err.to_string(),
            "attempting to end task which still has hardware allocated"
        );
    }

    #[tokio::test]
    async fn piecemeal_dealloc() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(50),
        }];
        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations,
            })
            .await
            .unwrap();

        fixture.end_task(1, 1, worker_id).await.unwrap();
    }

    #[tokio::test]
    async fn double_dealloc_gpu() {
        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];
        double_dealloc(
            hardware_reservations,
            "worker returning GPU tokens it doesn't have",
        )
        .await;
    }

    #[tokio::test]
    async fn double_dealloc_cpu() {
        let hardware_reservations = vec![HardwareReservation::Cpu { cores: CpuCores(2) }];
        double_dealloc(
            hardware_reservations,
            "worker returning CPU cores it doesn't have",
        )
        .await;
    }

    #[tokio::test]
    async fn alloc_unknown_gpu() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(1),
            tokens: GpuTokens(100),
        }];

        let err = fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap_err();

        assert_eq!(err.to_string(), format!("unknown GPU {}", test_gpu_id(1)));
    }

    #[tokio::test]
    async fn dealloc_unknown_gpu() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(1),
            tokens: GpuTokens(100),
        }];
        let err = fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations,
            })
            .await
            .unwrap_err();

        assert_eq!(err.to_string(), format!("unknown GPU {}", test_gpu_id(1)));
    }

    #[tokio::test]
    async fn end_task_pending() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let response = fixture.schedule_task(1, 2).await;
        assert_eq!(response.worker_id, worker_id);

        let second_allocation = fixture
            .alloc_ref
            .ask_enqueue(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 2),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        fixture.alloc_runner.handle_one().await;

        assert!(!second_allocation.has_reply());

        let err = fixture.end_task(1, 2, worker_id).await.unwrap_err();
        assert_eq!(
            err.to_string(),
            "attempting to end task which has a pending allocation"
        );

        // Even after the error we can continue, the task is still running
        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        fixture.end_task(1, 1, worker_id).await.unwrap();

        second_allocation.recv().await.unwrap().unwrap();

        fixture
            .deallocate_hardware(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1, 2),
                hardware_reservations,
            })
            .await
            .unwrap();
        fixture.end_task(1, 2, worker_id).await.unwrap();
    }

    #[tokio::test]
    async fn alloc_disconnect_realloc() {
        // 2 workers on the same machine sharing a GPU
        let mut fixture = Fixture::new(2).await;
        let worker1 = fixture.workers[0];
        let worker2 = fixture.workers[1];

        // worker1 reserves the GPU
        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, worker1);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .allocate_hardware(AllocateHardware {
                worker_id: worker1,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        // worker2 tries to reserve the same GPU
        let response = fixture.schedule_task(1, 2).await;
        assert_eq!(response.worker_id, worker2);

        let second_allocation = fixture
            .alloc_ref
            .ask_enqueue(AllocateHardware {
                worker_id: worker2,
                task_id: test_task_id(1, 2),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();
        fixture.alloc_runner.handle_one().await;

        // worker2 has to wait
        assert!(!second_allocation.has_reply());

        // worker1 disconnects
        fixture.disconnect_worker(worker1).await;

        // worker2 should be able to get the hardware now
        second_allocation.recv().await.unwrap().unwrap();
    }

    #[tokio::test]
    async fn alloc_for_task_not_running() {
        let mut fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        let error = fixture
            .allocate_hardware(AllocateHardware {
                worker_id,
                task_id: test_task_id(1, 1),
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap_err();

        assert_eq!(
            error.to_string(),
            "allocation request associated with task not running on worker"
        );
    }

    #[tokio::test]
    async fn chooses_least_busy_worker() {
        // create 8 workers, adjacent pairs are on same GPU, adjacent 4 are on same machine.
        // | (0, 1), (2, 3) | (4, 5), (6, 7) |
        let mut fixture = Fixture::new(8).await;

        // first GPU on first machine
        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, fixture.workers[0]);

        // first GPU on second machine
        let response = fixture.schedule_task(1, 2).await;
        assert_eq!(response.worker_id, fixture.workers[4]);

        // second GPU on first machine
        let response = fixture.schedule_task(1, 3).await;
        assert_eq!(response.worker_id, fixture.workers[2]);

        // The first task ends
        fixture.end_task(1, 1, fixture.workers[0]).await.unwrap();

        // first GPU on first machine is available again
        let response = fixture.schedule_task(1, 4).await;
        assert_eq!(response.worker_id, fixture.workers[0]);
    }

    #[tokio::test]
    async fn worker_disconnect() {
        // create 8 workers, adjacent pairs are on same GPU, adjacent 4 are on same machine.
        // | (0, 1), (2, 3) | (4, 5), (6, 7) |
        let mut fixture = Fixture::new(8).await;

        // first GPU on first machine
        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, fixture.workers[0]);

        // disconnect worker 4
        fixture.disconnect_worker(fixture.workers[4]).await;

        // second GPU on second machine
        let response = fixture.schedule_task(1, 2).await;
        assert_eq!(response.worker_id, fixture.workers[5]);
    }

    #[tokio::test]
    async fn end_task_disconnected_worker() {
        // create 8 workers, adjacent pairs are on same GPU, adjacent 4 are on same machine.
        // | (0, 1), (2, 3) | (4, 5), (6, 7) |
        let mut fixture = Fixture::new(8).await;

        // first GPU on first machine
        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, fixture.workers[0]);

        // disconnect worker 1
        fixture.disconnect_worker(fixture.workers[0]).await;

        // ending the task at this point should be an error
        assert_eq!(
            fixture
                .end_task(1, 1, fixture.workers[0])
                .await
                .unwrap_err()
                .to_string(),
            format!("unknown worker {}", fixture.workers[0])
        );
    }

    #[tokio::test]
    async fn end_task_twice() {
        // create 8 workers, adjacent pairs are on same GPU, adjacent 4 are on same machine.
        // | (0, 1), (2, 3) | (4, 5), (6, 7) |
        let mut fixture = Fixture::new(8).await;

        // first GPU on first machine
        let response = fixture.schedule_task(1, 1).await;
        assert_eq!(response.worker_id, fixture.workers[0]);

        fixture.end_task(1, 1, fixture.workers[0]).await.unwrap();

        // ending the task at this point should be an error
        assert_eq!(
            fixture
                .end_task(1, 1, fixture.workers[0])
                .await
                .unwrap_err()
                .to_string(),
            format!("worker not running task: {}", test_task_id(1, 1))
        );
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

pub type RemoteAllocatorActor = RemoteActor<AllocatorActor>;

remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    RegisterWorker,
    Result<RegisterWorkerReply>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    ScheduleTask,
    Result<ScheduleTaskReply>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    AllocateHardware,
    Result<()>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    DeallocateHardware,
    Result<()>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    EndTask,
    Result<()>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    RegisterManager,
    Result<()>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    GetStatus,
    Result<GetStatusReply>,
    RemoteAllocatorRequest
);

//  _ __  _ __ _____  ___   _
// | '_ \| '__/ _ \ \/ / | | |
// | |_) | | | (_) >  <| |_| |
// | .__/|_|  \___/_/\_\\__, |
// |_|                  |___/

#[derive(Debug)]
struct HttpError {
    status_code: http::StatusCode,
    message: String,
}

impl HttpError {
    fn new(status_code: http::StatusCode, message: impl Into<String>) -> Self {
        Self {
            status_code,
            message: message.into(),
        }
    }
}

impl std::error::Error for HttpError {}

impl std::fmt::Display for HttpError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        self.message.fmt(f)
    }
}

/// If no release channel is configured, this is what we use by default.
pub const DEFAULT_RELEASE_CHANNEL: &str = "unknown-alpha";

pub struct ApiRequest {
    pub request: http::Request<axum::body::Body>,
}

impl ApiRequest {
    fn risc0_version(&self) -> anyhow::Result<semver::VersionReq> {
        let version_value = self
            .request
            .headers()
            .get("x-risc0-version")
            .ok_or_else(|| {
                HttpError::new(
                    http::StatusCode::BAD_REQUEST,
                    "request missing `x-risc0-version` header",
                )
            })?;
        Ok(version_value.to_str()?.parse()?)
    }

    fn risc0_release_channel(&self, default_release_channel: &str) -> anyhow::Result<String> {
        Ok(self
            .request
            .headers()
            .get("x-risc0-release-channel")
            .map(|v| v.to_str().map(|v| v.to_string()))
            .unwrap_or(Ok(default_release_channel.into()))?)
    }
}

pub struct ApiResponse {
    pub response: http::Response<axum::body::Body>,
}

async fn proxy_api_request(
    http_client: Arc<reqwest::Client>,
    endpoint: Url,
    req: ApiRequest,
) -> anyhow::Result<ApiResponse> {
    use anyhow::Context as _;

    // Convert request into reqwest::Request
    let (mut parts, body) = req.request.into_parts();

    tracing::trace!("RECEIVED REQUEST TO PROXY: {parts:?}");

    let request_path = parts
        .uri
        .path()
        .strip_prefix(PROXY_URL_PATH)
        .ok_or_else(|| anyhow::anyhow!("url {} doesn't begin with {PROXY_URL_PATH}", parts.uri))?;

    // Join the URLs together
    let joined_uri = endpoint.join(request_path).context("failed to join URLs")?;
    parts.uri = joined_uri
        .to_string()
        .parse()
        .with_context(|| format!("failed to convert {joined_uri} to reqwest::Uri"))?;

    let request =
        http::Request::from_parts(parts, reqwest::Body::wrap_stream(body.into_data_stream()));
    let req: reqwest::Request = request
        .try_into()
        .context("failed to convert to reqwest::Request")?;

    let req_url = req.url().clone();
    let response: http::Response<reqwest::Body> = http_client
        .execute(req)
        .await
        .with_context(|| format!("failed to contact remote manager at {req_url}"))?
        .into();
    let (parts, body) = response.into_parts();

    Ok(ApiResponse {
        response: http::Response::from_parts(
            parts,
            axum::body::Body::from_stream(body.into_data_stream()),
        ),
    })
}

impl AllocatorActor {
    fn handle_api_request(
        &mut self,
        request: ApiRequest,
        reply_sender: &mut Option<ReplySender<anyhow::Result<ApiResponse>>>,
    ) -> anyhow::Result<()> {
        let release_channel = request.risc0_release_channel(&self.default_release_channel)?;
        let version_req = request.risc0_version()?;

        // Find a registered manager which satisfies the given request version.
        // We prefer versions which are higher.
        if let Some(iter) = self.managers.iter_channel(&release_channel) {
            for (manager_version, manager) in iter.rev() {
                if version_req.matches(manager_version) {
                    let http_client = self.http_client.clone();
                    let Some(endpoint) = manager.endpoint.clone() else {
                        continue;
                    };
                    let reply_sender = reply_sender.take();
                    tokio::task::spawn(async move {
                        if let Some(reply_sender) = reply_sender {
                            reply_sender
                                .send(proxy_api_request(http_client, endpoint, request).await)
                        }
                    });
                    return Ok(());
                }
            }
        }

        Err(HttpError::new(
            http::StatusCode::BAD_REQUEST,
            format!(
                "no manager found to satisfy request with requirement {version_req} \
                in software channel {release_channel}"
            ),
        )
        .into())
    }
}

impl Message<ApiRequest> for AllocatorActor {
    type Reply = anyhow::Result<ApiResponse>;

    async fn handle(&mut self, request: ApiRequest, ctx: &mut Context<Self, Self::Reply>) {
        let mut reply_sender = ctx.reply_sender();
        if let Err(error) = self.handle_api_request(request, &mut reply_sender)
            && let Some(reply_sender) = reply_sender
        {
            reply_sender.send(Err(error));
        }
    }
}

fn http_error_response(error: anyhow::Error) -> http::Response<axum::body::Body> {
    let status_code = error
        .downcast_ref::<HttpError>()
        .map(|e| e.status_code)
        .unwrap_or(http::StatusCode::INTERNAL_SERVER_ERROR);
    tracing::error!("Allocator proxy REST API response error: code={status_code} msg={error}");
    http::Response::builder()
        .status(status_code)
        .body(axum::body::Body::new(error.to_string()))
        .unwrap()
}

#[axum::debug_handler]
async fn proxy_handler(
    axum::extract::State(allocator): axum::extract::State<ActorRef<AllocatorActor>>,
    request: http::Request<axum::body::Body>,
) -> http::Response<axum::body::Body> {
    match allocator.ask(ApiRequest { request }).await {
        Ok(Ok(resp)) => resp.response,
        Ok(Err(error)) => http_error_response(error),
        Err(error) => http_error_response(error.into()),
    }
}

fn proxy_app(allocator: ActorRef<AllocatorActor>) -> axum::Router {
    use axum::routing::*;

    // This attempts to be a complete list of HTTP methods we would ever support.
    axum::Router::new()
        .route(
            &format!("{PROXY_URL_PATH}/{{*wildcard}}"),
            delete(proxy_handler)
                .get(proxy_handler)
                .head(proxy_handler)
                .options(proxy_handler)
                .patch(proxy_handler)
                .post(proxy_handler)
                .put(proxy_handler)
                .trace(proxy_handler),
        )
        .with_state(allocator)
}

/// Runs HTTP proxy that forwards to all registered managers. The particular manager is selected
/// via the `x-risc0-version` header.
pub async fn run_proxy(
    addr: SocketAddr,
    allocator: ActorRef<AllocatorActor>,
) -> anyhow::Result<()> {
    use anyhow::Context as _;

    let listener = TcpListener::bind(addr).await?;
    tracing::info!(
        "Allocator proxy REST API listening on: {}",
        listener.local_addr()?
    );

    axum::serve(listener, proxy_app(allocator))
        .with_graceful_shutdown(crate::api::shutdown_signal())
        .await
        .context("Allocator API service failed")?;

    Ok(())
}

#[cfg(test)]
mod proxy_tests {
    use super::*;
    use crate::actors::actor;
    use axum_test::TestServer;
    use httpmock::MockServer;
    use rstest::rstest;

    struct TestManager {
        server: MockServer,
    }

    impl TestManager {
        fn new() -> Self {
            let server = MockServer::start();
            Self { server }
        }
    }

    fn method_req_has_body(method: &http::Method) -> bool {
        use http::Method;

        method == Method::PUT || method == Method::PATCH || method == Method::POST
    }

    fn method_resp_has_body(method: &http::Method) -> bool {
        use http::Method;
        method == Method::DELETE
            || method == Method::GET
            || method == Method::PATCH
            || method == Method::POST
            || method == Method::PUT
            || method == Method::TRACE
    }

    async fn manager_proxy_test(
        manager_versions: Vec<DeploymentVersion>,
        expected_replied_manager_version: Option<DeploymentVersion>,
        method: http::Method,
        request_release_channel: Option<&str>,
        request_version: &str,
    ) -> axum_test::TestResponse {
        let managers: HashMap<_, _> = manager_versions
            .iter()
            .map(|v| (v.clone(), TestManager::new()))
            .collect();

        let alloc_ref = actor::spawn(AllocatorActor::new("default-channel"));

        for (version, manager) in &managers {
            alloc_ref
                .ask(RegisterManager {
                    deployment_version: version.clone(),
                    api_port: Some(
                        manager
                            .server
                            .url("/")
                            .parse::<Url>()
                            .unwrap()
                            .port()
                            .unwrap(),
                    ),
                    rpc_port: None,
                    path: "?".into(),
                    remote_address: None,
                })
                .await
                .unwrap()
                .unwrap();
        }

        let proxy = TestServer::new(proxy_app(alloc_ref)).unwrap();

        let hello_mock = expected_replied_manager_version.map(|v| {
            let method = method.clone();
            managers[&v].server.mock(move |mut when, mut then| {
                when = when.path("/ping").method(method.as_str());
                if method_req_has_body(&method) {
                    when.body("ping");
                }
                then = then.status(200);
                if method_resp_has_body(&method) {
                    then.body("pong");
                }
            })
        });
        let req_url = format!("{PROXY_URL_PATH}/ping");
        let mut test_req = proxy.method(method.clone(), &req_url);

        if method_req_has_body(&method) {
            test_req = test_req.text("ping");
        }
        if let Some(request_release_channel) = request_release_channel {
            test_req = test_req.add_header("x-risc0-release-channel", request_release_channel);
        }
        let response = test_req
            .add_header("x-risc0-version", request_version)
            .await;

        if let Some(hello_mock) = hello_mock {
            hello_mock.assert();
        }

        response
    }

    fn dver(
        release_channel: impl Into<String>,
        major: u64,
        minor: u64,
        patch: u64,
    ) -> DeploymentVersion {
        DeploymentVersion::new(release_channel, semver::Version::new(major, minor, patch))
    }

    #[rstest]
    #[case::delete("DELETE")]
    #[case::get("GET")]
    #[case::head("HEAD")]
    #[case::options("OPTIONS")]
    #[case::patch("PATCH")]
    #[case::post("POST")]
    #[case::put("PUT")]
    #[case::trace("TRACE")]
    #[tokio::test]
    async fn proxy_manager_not_found(#[case] method: &str) {
        let method = http::Method::from_bytes(method.as_bytes()).unwrap();
        let response = manager_proxy_test(
            vec![dver("test", 1, 2, 3)],
            None,
            method.clone(),
            Some("test"),
            "1.2.4",
        )
        .await;
        response.assert_status(http::StatusCode::BAD_REQUEST);
        if method_resp_has_body(&method) {
            assert_eq!(
                response.text(),
                "no manager found to satisfy request with requirement ^1.2.4 in software channel test"
            );
        }
    }

    #[rstest]
    #[case::delete("DELETE")]
    #[case::get("GET")]
    #[case::head("HEAD")]
    #[case::options("OPTIONS")]
    #[case::patch("PATCH")]
    #[case::post("POST")]
    #[case::put("PUT")]
    #[case::trace("TRACE")]
    #[tokio::test]
    async fn proxy_manager_exact_match(#[case] method: &str) {
        let method = http::Method::from_bytes(method.as_bytes()).unwrap();
        let response = manager_proxy_test(
            vec![dver("test", 1, 2, 3), dver("test", 1, 2, 4)],
            Some(dver("test", 1, 2, 3)),
            method.clone(),
            Some("test"),
            "=1.2.3",
        )
        .await;
        response.assert_status_success();
        if method_resp_has_body(&method) {
            response.assert_text("pong");
        }
    }

    #[tokio::test]
    async fn proxy_manager_multiple_match_chooses_latest() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                dver("test", 1, 2, 3),
                dver("test", 1, 2, 4),
                dver("test", 3, 0, 0),
            ],
            Some(dver("test", 1, 2, 4)),
            method,
            Some("test"),
            "1.2.3",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn proxy_manager_multiple_match_doesnt_choose_rc() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                dver("test", 1, 2, 3),
                dver("test", 1, 2, 4),
                dver("test", 3, 0, 0),
                "test:3.0.0-rc.1".parse().unwrap(),
            ],
            Some(dver("test", 3, 0, 0)),
            method,
            Some("test"),
            "3.0.0",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn proxy_manager_different_channel() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                dver("test", 1, 2, 3),
                dver("test2", 1, 2, 4),
                dver("test", 3, 0, 0),
            ],
            Some(dver("test", 1, 2, 3)),
            method,
            Some("test"),
            "1.2.3",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn proxy_manager_default_channel() {
        let method = http::Method::PUT;
        let response = manager_proxy_test(
            vec![
                dver("default-channel", 1, 2, 3),
                dver("test2", 1, 2, 4),
                dver("test", 3, 0, 0),
            ],
            Some(dver("default-channel", 1, 2, 3)),
            method,
            None,
            "1.2.3",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn multiple_managers_registered_error() {
        let alloc_ref = actor::spawn(AllocatorActor::new("default-channel"));

        alloc_ref
            .ask(RegisterManager {
                deployment_version: dver("test", 1, 2, 3),
                api_port: Some(8080),
                rpc_port: None,
                path: "/".into(),
                remote_address: None,
            })
            .await
            .unwrap()
            .unwrap();

        let error = alloc_ref
            .ask(RegisterManager {
                deployment_version: dver("test", 1, 2, 3),
                api_port: Some(8080),
                rpc_port: None,
                path: "/".into(),
                remote_address: None,
            })
            .await
            .unwrap()
            .unwrap_err();
        assert_eq!(
            error.to_string(),
            "duplicate registration for manager with deployment version test:1.2.3"
        );
    }
}
