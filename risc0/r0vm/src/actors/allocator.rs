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
use std::error::Error as StdError;
use std::fmt;
use std::net::SocketAddr;
use std::net::{IpAddr, Ipv4Addr};
use std::sync::Arc;

use super::{
    RemoteActor, RemoteAllocatorRequest, RpcDisconnect,
    protocol::{GlobalId, WorkerId},
    remote_actor_ask, routing_actor_impl,
};
use derive_more::{Add, AddAssign, From, Sub, SubAssign};
use http_body_util::BodyExt as _;
use kameo::{Reply, prelude::*};
use serde::{Deserialize, Serialize};
use tokio::net::TcpListener;
use url::Url;
use uuid::Uuid;

/// This is the URL path where requests are proxied to a manager of a specified version.
const PROXY_URL_PATH: &str = "/r0vm";

#[derive(Debug, Serialize, Deserialize)]
pub struct Error(String);

impl Error {
    fn new(msg: impl Into<String>) -> Self {
        Self(msg.into())
    }
}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", &self.0)
    }
}

type Result<T> = std::result::Result<T, Error>;

impl From<uuid::Error> for Error {
    fn from(e: uuid::Error) -> Self {
        Self(e.to_string())
    }
}

/// This value is the globally unique immutable alphanumeric identifier of the GPU. It does not
/// correspond to any physical label on the board.
#[derive(Clone, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub struct GpuUuid(Uuid);

impl GpuUuid {
    pub fn new_fake() -> Self {
        Self(Uuid::new_v4())
    }
}

impl std::str::FromStr for GpuUuid {
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
        write!(f, "GPU-{}", &self.0)
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
#[derive(Clone, Serialize, Deserialize)]
pub enum HardwareReservation {
    /// A portion of a GPU is reserved.
    Gpu { id: GpuUuid, tokens: GpuTokens },
    /// A portion of a CPU is reserved.
    Cpu { cores: CpuCores },
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
    tasks: HashMap<GlobalId, String>,
    /// GPU tokens being used the running tasks
    used_gpu_tokens: HashMap<GpuUuid, GpuTokens>,
    /// CPU cores being used the running tasks
    used_cores: CpuCores,
}

impl Worker {
    fn new(
        remote_address: Option<SocketAddr>,
        machine: MachineId,
        hardware: Vec<HardwareResource>,
    ) -> Self {
        Self {
            remote_address,
            tasks: HashMap::new(),
            machine,
            hardware,
            used_gpu_tokens: HashMap::new(),
            used_cores: CpuCores(0),
        }
    }
}

struct Manager {
    endpoint: Url,
    remote_address: Option<SocketAddr>,
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

#[derive(Actor)]
pub struct AllocatorActor {
    workers: HashMap<WorkerId, Worker>,
    managers: BTreeMap<semver::Version, Manager>,
    gpus: HashMap<GpuUuid, Gpu>,
    cpus: HashMap<MachineId, Cpu>,
    http_client: Arc<reqwest::Client>,

    pending: VecDeque<PendingAllocation>,
}

impl AllocatorActor {
    pub fn new() -> Self {
        Self {
            workers: HashMap::new(),
            managers: BTreeMap::new(),
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

    /// The number of tasks the GPU this worker is using is currently running.
    fn get_worker_num_tasks(
        &self,
        worker_id: &WorkerId,
        hardware_filter: HardwareFilter,
    ) -> Result<usize> {
        let worker = self
            .workers
            .get(worker_id)
            .ok_or_else(|| Error::new("unknown worker"))?;

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
            .map(|w| self.workers.get(w).unwrap().tasks.len())
            .sum())
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
            .ok_or_else(|| Error::new("unknown worker"))?;
        if let hash_map::Entry::Vacant(e) = worker.tasks.entry(task_id) {
            e.insert(description);
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

        for res in &request.hardware_reservations {
            match res {
                HardwareReservation::Gpu { id, tokens } => {
                    let gpu = self
                        .gpus
                        .get(id)
                        .ok_or_else(|| Error::new("unknown GPU {id}"))?;
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
                        .ok_or_else(|| Error::new("unknown GPU {id}"))?;
                    gpu.free_tokens -= *tokens;
                    *worker.used_gpu_tokens.entry(id.clone()).or_default() += *tokens;
                }
                HardwareReservation::Cpu { cores } => {
                    let cpu = self
                        .cpus
                        .get_mut(&worker.machine)
                        .expect("all worker CPUs should exist");
                    cpu.free_cores -= *cores;
                    worker.used_cores += *cores;
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
}

/// Request to register a worker with the allocator.
#[derive(Serialize, Deserialize)]
pub struct RegisterWorker {
    pub remote_address: Option<SocketAddr>,
    pub worker_id: WorkerId,
    pub hardware: Vec<HardwareResource>,
}

impl Message<RegisterWorker> for AllocatorActor {
    type Reply = DelegatedReply<Result<()>>;

    async fn handle(
        &mut self,
        msg: RegisterWorker,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ctx.reply(self.register_worker(msg))
    }
}

impl AllocatorActor {
    fn register_worker(&mut self, msg: RegisterWorker) -> Result<()> {
        let machine = match &msg.remote_address {
            Some(addr) => MachineId { ip: addr.ip() },
            None => MachineId::new_localhost(),
        };

        if let hash_map::Entry::Vacant(e) = self.workers.entry(msg.worker_id) {
            e.insert(Worker::new(
                msg.remote_address,
                machine.clone(),
                msg.hardware.clone(),
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

        Ok(())
    }
}

/// Choose a worker to send work to from the given candidate pool.
///
/// The idea is for the allocator to choose which worker is the least busy. The allocator reserves
/// the right to not reply immediately. It could be that all the workers already have deep queues
/// and the best move is to wait until one becomes less busy.
#[derive(Serialize, Deserialize)]
pub struct ChooseWorker {
    pub candidates: Vec<WorkerId>,
    pub task_id: GlobalId,
    pub description: String,
}

/// Reply when a worker is successfully chosen.
#[derive(Serialize, Deserialize, Reply)]
pub struct ChooseWorkerReply {
    pub worker_id: WorkerId,
}

impl Message<ChooseWorker> for AllocatorActor {
    type Reply = DelegatedReply<Result<ChooseWorkerReply>>;

    async fn handle(
        &mut self,
        msg: ChooseWorker,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ctx.reply(self.choose_worker(msg))
    }
}

impl AllocatorActor {
    fn choose_worker(&mut self, msg: ChooseWorker) -> Result<ChooseWorkerReply> {
        if msg.candidates.is_empty() {
            return Err(Error::new("no candidates provided"));
        }

        // Choose a worker which is least busy. We prefer a quiet GPU over a quiet CPU in this
        // selection.
        #[derive(PartialEq, Eq, PartialOrd, Ord, Debug)]
        struct CandidateWorker {
            gpu_tasks: usize,
            machine_tasks: usize,
            id: WorkerId,
        }

        let mut workers = msg
            .candidates
            .into_iter()
            .map(|c| {
                Ok(CandidateWorker {
                    id: c,
                    gpu_tasks: self.get_worker_num_tasks(&c, HardwareFilter::Gpu)?,
                    machine_tasks: self.get_worker_num_tasks(&c, HardwareFilter::Cpu)?,
                })
            })
            .collect::<Result<Vec<_>>>()?;
        workers.sort();
        let chosen_worker = workers[0].id;

        // Count that this worker has a new task now.
        self.add_worker_task(&chosen_worker, msg.task_id, msg.description)?;

        Ok(ChooseWorkerReply {
            worker_id: chosen_worker,
        })
    }
}

/// Mark the given hardware resources as being used. If the given hardware resources are already
/// allocated, this message is only replied to once they are free.
#[derive(Serialize, Deserialize)]
pub struct AllocateHardware {
    pub worker_id: WorkerId,
    pub hardware_reservations: Vec<HardwareReservation>,
}

impl Message<AllocateHardware> for AllocatorActor {
    type Reply = DelegatedReply<Result<()>>;

    async fn handle(
        &mut self,
        request: AllocateHardware,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();

        self.pending.push_back(PendingAllocation {
            request,
            reply_sender,
        });

        self.maybe_allocate_many();

        delegated_reply
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
    type Reply = DelegatedReply<Result<()>>;

    async fn handle(
        &mut self,
        msg: DeallocateHardware,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ctx.reply(self.deallocate_hardware(msg))
    }
}

impl AllocatorActor {
    fn deallocate_hardware(&mut self, msg: DeallocateHardware) -> Result<()> {
        let worker_id = msg.worker_id;
        let worker = self
            .workers
            .get_mut(&worker_id)
            .ok_or_else(|| Error::new("unknown worker {worker_id}"))?;
        if worker.tasks.remove(&msg.task_id).is_none() {
            return Err(Error::new(format!(
                "worker not running task: {:?}",
                msg.task_id
            )));
        }

        for res in msg.hardware_reservations {
            match res {
                HardwareReservation::Gpu { id, tokens } => {
                    let gpu = self
                        .gpus
                        .get_mut(&id)
                        .ok_or_else(|| Error::new("unknown GPU {id}"))?;

                    let worker_tokens = worker
                        .used_gpu_tokens
                        .get_mut(&id)
                        .ok_or_else(|| Error::new("worker returning GPU tokens it doesn't have"))?;
                    *worker_tokens = worker_tokens
                        .checked_sub(tokens)
                        .ok_or_else(|| Error::new("worker returning GPU tokens it doens't have"))?;
                    if *worker_tokens == GpuTokens::ZERO {
                        worker.used_gpu_tokens.remove(&id);
                    }

                    gpu.free_tokens += tokens;
                    assert!(gpu.free_tokens <= gpu.max_tokens);
                }
                HardwareReservation::Cpu { cores } => {
                    let cpu = self
                        .cpus
                        .get_mut(&worker.machine)
                        .expect("all worker CPUs should exist");

                    worker.used_cores = worker
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

#[derive(Serialize, Deserialize)]
pub struct RegisterManager {
    pub zkvm_version: semver::Version,
    pub path: String,
    pub port: u16,
    pub remote_address: Option<SocketAddr>,
}

impl Message<RegisterManager> for AllocatorActor {
    type Reply = DelegatedReply<Result<()>>;

    async fn handle(
        &mut self,
        msg: RegisterManager,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ctx.reply(self.register_manager(msg))
    }
}

impl AllocatorActor {
    fn register_manager(&mut self, msg: RegisterManager) -> Result<()> {
        if let btree_map::Entry::Vacant(e) = self.managers.entry(msg.zkvm_version.clone()) {
            let host = msg
                .remote_address
                .map(|a| a.ip())
                .unwrap_or(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)));
            e.insert(Manager {
                endpoint: format!(
                    "http://{}:{}/{}",
                    host,
                    msg.port,
                    msg.path.trim_start_matches('/')
                )
                .parse()
                .unwrap(),
                remote_address: msg.remote_address,
            });
        } else {
            return Err(Error::new(format!(
                "duplicate registration for manager with version {}",
                msg.zkvm_version
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
            for (uuid, tokens) in worker.used_gpu_tokens {
                let gpu = self.gpus.get_mut(&uuid).expect("all worker GPUs exist");
                gpu.free_tokens += tokens;
                assert!(gpu.free_tokens <= gpu.max_tokens);
            }
            if worker.used_cores > CpuCores::ZERO {
                let cpu = self
                    .cpus
                    .get_mut(&worker.machine)
                    .expect("all worker CPUs exist");

                cpu.free_cores += worker.used_cores;
                assert!(cpu.free_cores <= cpu.total_cores);
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
pub struct GetStatusReply {
    pub workers: BTreeMap<String, Vec<String>>,
}

impl Message<GetStatus> for AllocatorActor {
    type Reply = DelegatedReply<Result<GetStatusReply>>;

    async fn handle(
        &mut self,
        _msg: GetStatus,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        ctx.reply(self.get_status())
    }
}

impl AllocatorActor {
    fn get_status(&mut self) -> Result<GetStatusReply> {
        Ok(GetStatusReply {
            workers: self
                .workers
                .iter()
                .map(|(worker_id, worker)| {
                    let key = format!(
                        "{}{worker_id}",
                        worker
                            .remote_address
                            .map(|a| format!("{a}:"))
                            .unwrap_or_default(),
                    );
                    let value = worker.tasks.values().cloned().collect();
                    (key, value)
                })
                .collect(),
        })
    }
}

#[cfg(test)]
mod allocation_tests {
    use super::*;
    use crate::actors::protocol::JobId;

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

    fn test_task_id(n: u64) -> GlobalId {
        GlobalId {
            job_id: JobId::new_v4(),
            task_id: n,
        }
    }

    struct Fixture {
        workers: Vec<WorkerId>,
        alloc_ref: ActorRef<AllocatorActor>,
    }

    impl Fixture {
        async fn new(worker_count: u32) -> Self {
            let alloc_ref = kameo::spawn(AllocatorActor::new());

            let workers: Vec<WorkerId> = (0..worker_count).map(test_worker_id).collect();
            for (i, worker_id) in workers.iter().enumerate() {
                alloc_ref
                    .ask(RegisterWorker {
                        worker_id: *worker_id,
                        remote_address: Some(
                            format!("1.2.3.{}:100{}", i / 4, i % 4).parse().unwrap(),
                        ),
                        hardware: vec![
                            HardwareResource::Gpu(GpuSpec {
                                name: "test GPU".into(),
                                uuid: test_gpu_id(i as u32 / 2),
                                tokens: GpuTokens(100),
                            }),
                            HardwareResource::Cpu(CpuSpec { cores: CpuCores(4) }),
                        ],
                    })
                    .await
                    .unwrap();
            }

            Self { workers, alloc_ref }
        }

        async fn choose_worker(&self) -> ChooseWorkerReply {
            self.alloc_ref
                .ask(ChooseWorker {
                    candidates: self.workers.clone(),
                    task_id: test_task_id(1),
                    description: "test task".into(),
                })
                .await
                .unwrap()
        }
    }

    #[tokio::test]
    async fn alloc_dealloc_realloc() {
        let fixture = Fixture::new(1).await;
        let worker_id = fixture.workers[0];

        let response = fixture.choose_worker().await;
        assert_eq!(response.worker_id, worker_id);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .alloc_ref
            .ask(AllocateHardware {
                worker_id,
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        let other_alloc_ref = fixture.alloc_ref.clone();
        let other_hardware_reservations = hardware_reservations.clone();
        let second_allocation = tokio::task::spawn(async move {
            other_alloc_ref
                .ask(AllocateHardware {
                    worker_id,
                    hardware_reservations: other_hardware_reservations,
                })
                .await
                .unwrap();
        });

        tokio::task::yield_now().await;
        assert!(!second_allocation.is_finished());

        fixture
            .alloc_ref
            .ask(DeallocateHardware {
                worker_id,
                task_id: test_task_id(1),
                hardware_reservations,
            })
            .await
            .unwrap();

        second_allocation.await.unwrap();
    }

    #[tokio::test]
    async fn alloc_disconnect_realloc() {
        // 2 workers on the same machine sharing a GPU
        let fixture = Fixture::new(2).await;
        let worker1 = fixture.workers[0];
        let worker2 = fixture.workers[1];

        // worker1 reserves the GPU
        let response = fixture.choose_worker().await;
        assert_eq!(response.worker_id, worker1);

        let hardware_reservations = vec![HardwareReservation::Gpu {
            id: test_gpu_id(0),
            tokens: GpuTokens(100),
        }];

        fixture
            .alloc_ref
            .ask(AllocateHardware {
                worker_id: worker1,
                hardware_reservations: hardware_reservations.clone(),
            })
            .await
            .unwrap();

        // worker2 tries to reserve the same GPU
        let other_alloc_ref = fixture.alloc_ref.clone();
        let other_hardware_reservations = hardware_reservations.clone();
        let second_allocation = tokio::task::spawn(async move {
            other_alloc_ref
                .ask(AllocateHardware {
                    worker_id: worker2,
                    hardware_reservations: other_hardware_reservations,
                })
                .await
                .unwrap();
        });

        // worker2 has to wait
        tokio::task::yield_now().await;
        assert!(!second_allocation.is_finished());

        // worker1 disconnects
        fixture
            .alloc_ref
            .ask(RpcDisconnect {
                remote_address: "1.2.3.0:1000".parse().unwrap(),
            })
            .await
            .unwrap();

        // worker2 should be able to get the hardware now
        second_allocation.await.unwrap();
    }

    #[tokio::test]
    async fn chooses_least_busy_worker() {
        // create 8 workers, adjacent pairs are on same GPU, adjacent 4 are on same machine.
        // | (0, 1), (2, 3) | (4, 5), (6, 7) |
        let fixture = Fixture::new(8).await;

        // first GPU on first machine
        let response = fixture.choose_worker().await;
        assert_eq!(response.worker_id, fixture.workers[0]);

        // first GPU on second machine
        let response = fixture.choose_worker().await;
        assert_eq!(response.worker_id, fixture.workers[4]);

        // second GPU on first machine
        let response = fixture.choose_worker().await;
        assert_eq!(response.worker_id, fixture.workers[2]);
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

#[derive(Actor)]
pub(crate) enum AllocatorRouterActor {
    Local(ActorRef<AllocatorActor>),
    Remote(ActorRef<RemoteAllocatorActor>),
}

impl AllocatorRouterActor {
    pub async fn new(
        addr: &Option<SocketAddr>,
        local: &Option<ActorRef<AllocatorActor>>,
    ) -> std::result::Result<ActorRef<Self>, Box<dyn StdError>> {
        if let Some(addr) = addr {
            let remote =
                kameo::spawn(RemoteAllocatorActor::new(*addr, "RemoteAllocatorActor").await?);
            Ok(kameo::spawn(Self::Remote(remote)))
        } else {
            Ok(kameo::spawn(Self::Local(
                local.as_ref().ok_or("no allocator configured")?.clone(),
            )))
        }
    }
}

routing_actor_impl!(
    AllocatorRouterActor,
    RegisterWorker,
    DelegatedReply<Result<()>>
);

routing_actor_impl!(
    AllocatorRouterActor,
    ChooseWorker,
    DelegatedReply<Result<ChooseWorkerReply>>
);

routing_actor_impl!(
    AllocatorRouterActor,
    AllocateHardware,
    DelegatedReply<Result<()>>
);

routing_actor_impl!(
    AllocatorRouterActor,
    DeallocateHardware,
    DelegatedReply<Result<()>>
);

routing_actor_impl!(
    AllocatorRouterActor,
    RegisterManager,
    DelegatedReply<Result<()>>
);

pub type RemoteAllocatorActor = RemoteActor<AllocatorActor>;

remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    RegisterWorker,
    Result<()>,
    RemoteAllocatorRequest
);
remote_actor_ask!(
    RemoteActor<AllocatorActor>,
    ChooseWorker,
    Result<ChooseWorkerReply>,
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

pub struct ApiRequest {
    pub request: http::Request<axum::body::Body>,
}

impl ApiRequest {
    fn risc0_version(&self) -> anyhow::Result<semver::VersionReq> {
        let version_value = self
            .request
            .headers()
            .get("x-risc0-version")
            .ok_or_else(|| anyhow::anyhow!("request missing `x-risc0-version` header"))?;
        Ok(version_value.to_str()?.parse()?)
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
    // Convert request into reqwest::Request
    let (parts, body) = req.request.into_parts();
    let request =
        http::Request::from_parts(parts, reqwest::Body::wrap_stream(body.into_data_stream()));
    let mut req: reqwest::Request = request.try_into()?;

    // Join the URLs together
    *req.url_mut() = endpoint.join(
        req.url()
            .path()
            .strip_prefix(PROXY_URL_PATH)
            .ok_or_else(|| anyhow::anyhow!("url doesn't begin with {PROXY_URL_PATH}"))?,
    )?;

    let response: http::Response<reqwest::Body> = http_client.execute(req).await?.into();
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
        let version_req = request.risc0_version()?;

        // Find a registered manager which satisfies the given request version.
        // We prefer versions which are higher.
        for (manager_version, manager) in self.managers.iter().rev() {
            if version_req.matches(manager_version) {
                let http_client = self.http_client.clone();
                let endpoint = manager.endpoint.clone();
                let reply_sender = reply_sender.take();
                tokio::task::spawn(async move {
                    if let Some(reply_sender) = reply_sender {
                        reply_sender.send(proxy_api_request(http_client, endpoint, request).await)
                    }
                });
                return Ok(());
            }
        }

        Err(HttpError::new(
            http::StatusCode::BAD_REQUEST,
            format!("no manager found to satisfy request with requirement {version_req}"),
        )
        .into())
    }
}

impl Message<ApiRequest> for AllocatorActor {
    type Reply = DelegatedReply<anyhow::Result<ApiResponse>>;

    async fn handle(
        &mut self,
        request: ApiRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, mut reply_sender) = ctx.reply_sender();
        if let Err(error) = self.handle_api_request(request, &mut reply_sender)
            && let Some(reply_sender) = reply_sender
        {
            reply_sender.send(Err(error));
        }
        delegated_reply
    }
}

fn send_error_err<M, E>(error: &SendError<M, E>) -> Option<&E> {
    if let SendError::HandlerError(e) = error {
        Some(e)
    } else {
        None
    }
}

#[axum::debug_handler]
async fn proxy_handler(
    axum::extract::State(allocator): axum::extract::State<ActorRef<AllocatorActor>>,
    request: http::Request<axum::body::Body>,
) -> http::Response<axum::body::Body> {
    match allocator.ask(ApiRequest { request }).await {
        Ok(resp) => resp.response,
        Err(error) => {
            let status_code = send_error_err(&error)
                .and_then(|e| e.downcast_ref::<HttpError>())
                .map(|e| e.status_code)
                .unwrap_or(http::StatusCode::INTERNAL_SERVER_ERROR);
            http::Response::builder()
                .status(status_code)
                .body(axum::body::Body::new(error.to_string()))
                .unwrap()
        }
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
    tracing::info!("Allocator API listening on: {}", listener.local_addr()?);

    axum::serve(listener, proxy_app(allocator))
        .with_graceful_shutdown(crate::api::shutdown_signal())
        .await
        .context("Allocator API service failed")?;

    Ok(())
}

#[cfg(test)]
mod proxy_tests {
    use super::*;
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
        manager_versions: Vec<semver::Version>,
        expected_replied_manager_version: Option<semver::Version>,
        method: http::Method,
        request_version: &str,
    ) -> axum_test::TestResponse {
        let managers: HashMap<_, _> = manager_versions
            .iter()
            .map(|v| (v.clone(), TestManager::new()))
            .collect();

        let alloc_ref = kameo::spawn(AllocatorActor::new());

        for (version, manager) in &managers {
            alloc_ref
                .ask(RegisterManager {
                    zkvm_version: version.clone(),
                    port: manager
                        .server
                        .url("/")
                        .parse::<Url>()
                        .unwrap()
                        .port()
                        .unwrap(),
                    path: "?".into(),
                    remote_address: None,
                })
                .await
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
        let response = test_req
            .add_header("x-risc0-version", request_version)
            .await;

        if let Some(hello_mock) = hello_mock {
            hello_mock.assert();
        }

        response
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
            vec![semver::Version::new(1, 2, 3)],
            None,
            method.clone(),
            "1.2.4",
        )
        .await;
        response.assert_status(http::StatusCode::BAD_REQUEST);
        if method_resp_has_body(&method) {
            assert_eq!(
                response.text(),
                "no manager found to satisfy request with requirement ^1.2.4"
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
            vec![semver::Version::new(1, 2, 3), semver::Version::new(1, 2, 4)],
            Some(semver::Version::new(1, 2, 3)),
            method.clone(),
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
                semver::Version::new(1, 2, 3),
                semver::Version::new(1, 2, 4),
                semver::Version::new(3, 0, 0),
            ],
            Some(semver::Version::new(1, 2, 4)),
            method,
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
                semver::Version::new(1, 2, 3),
                semver::Version::new(1, 2, 4),
                semver::Version::new(3, 0, 0),
                "3.0.0-rc.1".parse().unwrap(),
            ],
            Some(semver::Version::new(3, 0, 0)),
            method,
            "3.0.0",
        )
        .await;
        response.assert_status_success();
        response.assert_text("pong");
    }

    #[tokio::test]
    async fn multiple_managers_registered_error() {
        let alloc_ref = kameo::spawn(AllocatorActor::new());

        alloc_ref
            .ask(RegisterManager {
                zkvm_version: semver::Version::new(1, 2, 3),
                port: 8080,
                path: "/".into(),
                remote_address: None,
            })
            .await
            .unwrap();

        let error = alloc_ref
            .ask(RegisterManager {
                zkvm_version: semver::Version::new(1, 2, 3),
                port: 8080,
                path: "/".into(),
                remote_address: None,
            })
            .await
            .unwrap_err();
        assert_eq!(
            error.to_string(),
            "duplicate registration for manager with version 1.2.3"
        );
    }
}
