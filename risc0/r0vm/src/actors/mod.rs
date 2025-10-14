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

pub(crate) mod actor;
pub(crate) mod allocator;
pub(crate) mod config;
pub(crate) mod error;
pub(crate) mod factory;
pub(crate) mod job;
pub(crate) mod manager;
pub(crate) mod metrics;
pub(crate) mod protocol;
pub(crate) mod rpc;
#[cfg(test)]
mod tests;
pub(crate) mod worker;

use std::{
    error::Error as StdError,
    io::{Write, stdin},
    marker::PhantomData,
    net::{IpAddr, Ipv4Addr, SocketAddr},
    os::{fd::AsFd as _, unix::net::UnixStream as StdUnixStream},
    path::{Path, PathBuf},
    sync::{Arc, Mutex},
    time::Duration,
};

use anyhow::Context as _;
use derive_more::From;
use nvml_wrapper::Nvml;
use opentelemetry_appender_tracing::layer::OpenTelemetryTracingBridge;
use opentelemetry_sdk::{
    Resource,
    logs::SdkLoggerProvider,
    metrics::{PeriodicReader, SdkMeterProvider},
    propagation::TraceContextPropagator,
    trace::SdkTracerProvider,
};
use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};
use tempfile::NamedTempFile;
use tokio::{
    io::{AsyncReadExt as _, AsyncWriteExt as _},
    net::{TcpListener, TcpStream, UnixStream, tcp},
    process::{Child, Command},
    task::JoinHandle,
};
use tracing_subscriber::{
    EnvFilter, Layer as _, layer::SubscriberExt as _, util::SubscriberInitExt as _,
};

use crate::init_logging;

use self::{
    actor::{Actor, ActorRef, Message},
    allocator::{
        AllocatorActor, DEFAULT_RELEASE_CHANNEL, DEFAULT_WORKER_TASK_LIMIT, DeploymentVersion,
        HardwareResource, RegisterManager, RegisterWorker, RemoteAllocatorActor,
    },
    config::{
        AllocatorConfig, AppConfig, ExecutorConfig, ManagerConfig, ProverConfig, TelemetryConfig,
        VERSION, VersionConfig, default_api_listen_addr,
    },
    factory::{FactoryActor, RemoteFactoryActor},
    manager::ManagerActor,
    protocol::{
        JobInfo, JobRequest, ProofRequest, ProofResult, ShrinkWrapRequest, ShrinkWrapResult,
        TaskKind, WorkerId,
        factory::{GetTasks, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
    },
    rpc::{RpcMessageId, RpcSender, rpc_system},
    worker::{RemoteWorkerActor, WorkerActor, worker_hardware},
};

#[tokio::main]
pub(crate) async fn async_main(config_path: Option<PathBuf>) -> Result<(), Box<dyn StdError>> {
    let config: AppConfig = if let Some(ref path) = config_path {
        let str = tokio::fs::read_to_string(path).await?;
        let version: VersionConfig = toml::from_str(&str)?;
        let version = version.version;
        if version != VERSION {
            return Err(anyhow::anyhow!("version {version} not supported").into());
        }
        toml::from_str(&str)?
    } else {
        AppConfig::default()
    };
    tracing::info!("{config:#?}");

    let mut app = App::new(config, /*enable_logging=*/ true).await?;
    if app.manager.is_some() || app.allocator.is_some() {
        wait_for_shutdown().await;
    } else {
        app.wait_for_workers().await;
    }

    app.stop().await;

    Ok(())
}

async fn wait_for_shutdown() {
    use tokio::signal::unix::{SignalKind, signal};

    let mut sigterm = signal(SignalKind::terminate()).expect("failed to bind SIGTERM");

    println!("Use Ctrl-C");

    tokio::select! {
        _ = tokio::signal::ctrl_c() => {
            eprintln!("Got SIGINT (Ctrl-C)");
        }
        _ = sigterm.recv() => {
            eprintln!("Got SIGTERM");
        }
    }

    println!();
}

async fn read_or_eof(socket: &mut UnixStream, buf: &mut [u8]) -> Result<bool, Box<dyn StdError>> {
    assert!(!buf.is_empty());

    let mut i = 0;
    while i < buf.len() {
        let num_read = socket
            .read(&mut buf[i..])
            .await
            .context("reading RPC header")?;
        if num_read == 0 {
            if i > 0 {
                Err(std::io::Error::from(std::io::ErrorKind::UnexpectedEof))
                    .context("reading RPC header")?
            }
            return Ok(false);
        }
        i += num_read;
    }
    Ok(true)
}

async fn relay_job_request(
    app: &mut App,
    socket: &mut UnixStream,
) -> Result<bool, Box<dyn StdError>> {
    let mut buf = vec![0u8; 4];
    if !read_or_eof(socket, &mut buf[..]).await? {
        return Ok(false);
    }

    let body_len: u32 = bincode::deserialize(&buf).context("received invalid RPC header")?;
    let mut buf = vec![0u8; body_len as usize];
    socket
        .read_exact(&mut buf)
        .await
        .context("error reading RPC body")?;
    let request: JobRequest =
        bincode::deserialize(&buf).context("error deserializing JobRequest")?;

    let mut response_buf = vec![0u8; 4];

    match request {
        JobRequest::Proof(request) => {
            let job_info = app
                .proof_request(request)
                .await
                .context("error running ProofRequest")?;
            bincode::serialize_into(&mut response_buf, &job_info)?;
        }
        JobRequest::ShrinkWrap(request) => {
            let job_info = app
                .shrink_wrap_request(request)
                .await
                .context("error running ShrinkWrapRequest")?;
            bincode::serialize_into(&mut response_buf, &job_info)?;
        }
    }

    let body_len = response_buf.len() as u32 - 4;
    bincode::serialize_into(&mut response_buf[0..4], &body_len)?;
    socket.write_all(&response_buf).await?;

    Ok(true)
}

#[tokio::main]
pub(crate) async fn rpc_main(num_gpus: Option<usize>) -> Result<(), Box<dyn StdError>> {
    let small_tasks = vec![
        TaskKind::Lift,
        TaskKind::Join,
        TaskKind::Union,
        TaskKind::Resolve,
        TaskKind::ShrinkWrap,
    ];

    let mut large_tasks = vec![TaskKind::ProveSegment, TaskKind::ProveKeccak];
    large_tasks.extend_from_slice(&small_tasks);

    let mut app = App::new(
        AppConfig {
            version: VERSION,
            release_channel: None,
            api: None,
            manager: Some(ManagerConfig {
                allocator: None,
                listen: None,
            }),
            allocator: Some(AllocatorConfig {
                listen: None,
                default_release_channel: None,
                worker_task_limit: None,
            }),
            executor: Some(ExecutorConfig {
                allocator: None,
                count: 1,
            }),
            prover: Some(vec![
                ProverConfig {
                    allocator: None,
                    count: num_gpus,
                    subscribe: large_tasks,
                    simulate: None,
                },
                ProverConfig {
                    allocator: None,
                    count: num_gpus,
                    subscribe: small_tasks,
                    simulate: None,
                },
            ]),
            storage: None,
            telemetry: None,
        },
        /*enable_logging=*/
        true,
    )
    .await?;

    let socket: StdUnixStream = stdin().as_fd().try_clone_to_owned()?.into();

    socket.set_nonblocking(true)?;
    let mut socket = UnixStream::from_std(socket)?;

    let result = loop {
        match relay_job_request(&mut app, &mut socket).await {
            Ok(true) => continue,
            Ok(false) => break Ok(()),
            Err(error) => break Err(error),
        }
    };

    app.stop().await;

    result
}

#[tokio::main]
pub(crate) async fn status_main(host: String) -> Result<(), Box<dyn StdError>> {
    use std::net::ToSocketAddrs as _;

    let addr = host
        .to_socket_addrs()?
        .next()
        .ok_or_else(|| format!("failed to resolve {host}"))?;

    let remote_allocator =
        actor::spawn(allocator::RemoteAllocatorActor::new(addr, "RemoteAllocatorActor").await?);

    let reply = remote_allocator.ask(allocator::GetStatus).await??;
    println!("{}", serde_json::to_string_pretty(&reply)?);

    Ok(())
}

struct TempConfig {
    file: NamedTempFile,
}

impl TempConfig {
    fn new(
        allocator_addr: SocketAddr,
        subscribe: Vec<TaskKind>,
        enable_telemetry: bool,
        release_channel: &Option<String>,
    ) -> anyhow::Result<Self> {
        let config = AppConfig {
            version: VERSION,
            release_channel: release_channel.clone(),
            api: None,
            manager: None,
            allocator: None,
            executor: None,
            prover: Some(vec![ProverConfig {
                allocator: Some(allocator_addr),
                count: Some(1),
                subscribe,
                simulate: None,
            }]),
            storage: None,
            telemetry: enable_telemetry.then_some(TelemetryConfig {}),
        };
        let toml = toml::to_string(&config)?;
        let mut file = tempfile::NamedTempFile::new()?;
        write!(file, "{toml}")?;
        Ok(Self { file })
    }
}

fn cuda_devices() -> anyhow::Result<usize> {
    let nvml = Nvml::init()?;
    for idx in 0..nvml.device_count()? {
        let device = nvml.device_by_index(idx)?;
        tracing::info!("Device {idx}:");
        tracing::info!("  name: {}", device.name()?);
        tracing::info!("  arch: {}", device.architecture()?);
        tracing::info!("  cores: {}", device.num_cores()?);
        tracing::info!("  {:#?}", device.memory_info()?);
        tracing::info!("  {:#?}", device.pci_info()?);
    }
    Ok(nvml.device_count()? as usize)
}

fn spawn_fail(path: &Path) -> String {
    format!("Could not launch \"{}\".", path.to_string_lossy())
}

struct ChildState {
    child: Child,
    // Pin the temporary file so that it stays alive for the lifetime of the child process.
    _config: Arc<TempConfig>,
}

fn default_storage_root() -> PathBuf {
    dirs::home_dir()
        .expect("should be able to find home_dir")
        .join(".risc0")
        .join("r0vm")
}

fn manager_listen_addr(config_ip: Option<IpAddr>) -> SocketAddr {
    let ip = config_ip.unwrap_or(IpAddr::V4(Ipv4Addr::LOCALHOST));
    SocketAddr::new(ip, 0)
}

fn allocator_listen_addr(config_addr: Option<SocketAddr>) -> SocketAddr {
    config_addr.unwrap_or(SocketAddr::new(IpAddr::V4(Ipv4Addr::LOCALHOST), 0))
}

fn missing_alloc_error(name: &str) -> String {
    format!(
        "Invalid configuration: \
        either allocator must run locally or {name}.allocator must be set"
    )
}

pub(crate) struct App {
    provider: Option<OpenTelemetryProvider>,
    manager: Option<ActorRef<ManagerActor>>,
    allocator: Option<ActorRef<AllocatorActor>>,
    factory: Option<ActorRef<FactoryActor>>,
    workers: Arc<Mutex<Vec<ActorRef<WorkerActor>>>>,
    factory_rpc_server: Option<FactoryRpcServer>,
    allocator_rpc_server: Option<AllocatorRpcServer>,
    children: Vec<ChildState>,
    allocator_rpc_addr: Option<SocketAddr>,
}

impl App {
    pub async fn new(cfg: AppConfig, enable_logging: bool) -> Result<Self, Box<dyn StdError>> {
        let mut manager = None;
        let mut allocator = None;
        let mut factory = None;
        let mut factory_rpc_server = None;
        let mut allocator_rpc_server = None;
        let mut local_allocator_rpc_addr = None;

        let provider = if cfg.telemetry.is_some() {
            Some(OpenTelemetryProvider::new().context("failed to create OpenTelemetryProvider")?)
        } else {
            if enable_logging {
                init_logging();
            }
            None
        };

        if let Some(cfg_allocator) = &cfg.allocator {
            tracing::info!("Starting allocator");

            let alloc_ref = actor::spawn(AllocatorActor::new(
                cfg_allocator
                    .default_release_channel
                    .as_deref()
                    .unwrap_or(DEFAULT_RELEASE_CHANNEL),
                cfg_allocator
                    .worker_task_limit
                    .unwrap_or(DEFAULT_WORKER_TASK_LIMIT),
            ));
            allocator = Some(alloc_ref.clone());

            let mut rpc_server = AllocatorRpcServer::new(
                allocator_listen_addr(cfg_allocator.listen),
                alloc_ref.clone(),
            );
            local_allocator_rpc_addr = Some(rpc_server.bind_and_listen().await?);
            allocator_rpc_server = Some(rpc_server);

            if let Some(cfg_api) = &cfg.api {
                let listen = cfg_api.listen.unwrap_or(default_api_listen_addr());
                tokio::spawn(allocator::run_proxy(listen, alloc_ref));
            }
        } else if cfg.api.is_some() {
            return Err("cannot run API without an allocator".into());
        }

        if let Some(cfg_manager) = &cfg.manager {
            let storage_root = if let Some(cfg) = &cfg.storage {
                cfg.path.clone()
            } else {
                default_storage_root()
            };

            let allocator_addr = cfg_manager
                .allocator
                .or(local_allocator_rpc_addr)
                .ok_or_else(|| missing_alloc_error("manager"))?;
            let alloc_ref = actor::spawn(
                RemoteAllocatorActor::new(allocator_addr, "RemoteAllocatorActor").await?,
            );

            #[cfg(feature = "cuda")]
            let require_gpu = true;

            #[cfg(not(feature = "cuda"))]
            let require_gpu = cfg
                .prover
                .as_ref()
                .map(|provers| provers.iter().any(|prover| prover.simulate.is_some()))
                .is_some_and(|a| a);

            let factory_ref = actor::spawn(FactoryActor::new(alloc_ref.clone(), require_gpu));
            factory = Some(factory_ref.clone());

            let remote_allocator = cfg_manager.allocator.is_some();
            let have_api = remote_allocator || cfg.api.is_some();

            let manager_ref = actor::spawn(ManagerActor::new(
                factory_ref.clone(),
                have_api.then(|| storage_root.clone()),
            ));
            manager = Some(manager_ref.clone());

            let mut rpc_server =
                FactoryRpcServer::new(manager_listen_addr(cfg_manager.listen), factory_ref);
            let local_factory_rpc_addr = rpc_server.bind_and_listen().await?;
            factory_rpc_server = Some(rpc_server);

            let mut api_addr = None;
            if have_api {
                api_addr = Some(
                    crate::api::run(
                        manager_listen_addr(cfg_manager.listen),
                        storage_root,
                        manager_ref,
                        cfg.api.and_then(|c| c.po2),
                    )
                    .await?,
                );
            }

            alloc_ref
                .ask(RegisterManager {
                    deployment_version: deployment_version(&cfg.release_channel),
                    api_port: api_addr.map(|a| a.port()),
                    rpc_port: Some(local_factory_rpc_addr.port()),
                    path: "/".into(),
                    remote_address: None,
                })
                .await??;
        }

        let workers = Arc::new(Mutex::new(vec![]));
        let mut children = vec![];

        if let Some(cfg_executor) = cfg.executor {
            Self::create_executors(
                &cfg_executor,
                &cfg.release_channel,
                local_allocator_rpc_addr,
                workers.clone(),
            )
            .await?;
        }

        if let Some(cfg_prover) = cfg.prover {
            Self::create_provers(
                &cfg_prover,
                &cfg.release_channel,
                local_allocator_rpc_addr,
                workers.clone(),
                &mut children,
                provider.is_some(),
            )
            .await?
        }

        Ok(Self {
            provider,
            manager,
            allocator,
            factory,
            workers,
            factory_rpc_server,
            allocator_rpc_server,
            children,
            allocator_rpc_addr: local_allocator_rpc_addr,
        })
    }

    #[allow(dead_code)]
    pub fn allocator_addr(&self) -> Option<SocketAddr> {
        self.allocator_rpc_addr
    }

    async fn create_executors(
        executor: &ExecutorConfig,
        release_channel: &Option<String>,
        local_allocator_addr: Option<SocketAddr>,
        workers: Arc<Mutex<Vec<ActorRef<WorkerActor>>>>,
    ) -> Result<(), Box<dyn StdError>> {
        tracing::info!("Starting executor: {executor:?}");

        let alloc_ip = executor
            .allocator
            .map(|a| a.ip())
            .unwrap_or(IpAddr::V4(Ipv4Addr::new(127, 0, 0, 1)));
        let alloc_addr = executor
            .allocator
            .or(local_allocator_addr)
            .ok_or_else(|| missing_alloc_error("executor"))?;
        let alloc_ref =
            actor::spawn(RemoteAllocatorActor::new(alloc_addr, "RemoteAllocatorActor").await?);

        for _ in 0..executor.count {
            start_worker(
                release_channel,
                alloc_ref.clone(),
                alloc_ip,
                workers.clone(),
                vec![TaskKind::Execute],
                None,
            )
            .await?;
        }

        Ok(())
    }

    #[allow(clippy::too_many_arguments)]
    async fn create_provers(
        cfg_prover: &[ProverConfig],
        release_channel: &Option<String>,
        local_allocator_addr: Option<SocketAddr>,
        workers: Arc<Mutex<Vec<ActorRef<WorkerActor>>>>,
        children: &mut Vec<ChildState>,
        enable_telemetry: bool,
    ) -> Result<(), Box<dyn StdError>> {
        for prover in cfg_prover {
            tracing::info!("Starting prover: {prover:?}");

            let count = prover.count.unwrap_or_else(|| cuda_devices().unwrap_or(1));
            if (cfg_prover.len() == 1 && count == 1) || prover.simulate.is_some() {
                let alloc_addr = prover
                    .allocator
                    .or(local_allocator_addr)
                    .ok_or_else(|| missing_alloc_error("prover"))?;
                let alloc_ref = actor::spawn(
                    RemoteAllocatorActor::new(alloc_addr, "RemoteAllocatorActor").await?,
                );

                start_worker(
                    release_channel,
                    alloc_ref,
                    alloc_addr.ip(),
                    workers.clone(),
                    prover.subscribe.clone(),
                    prover.simulate,
                )
                .await?;
            } else {
                let r0vm_path = std::env::current_exe()?;

                let allocator_addr = prover
                    .allocator
                    .or(local_allocator_addr)
                    .ok_or_else(|| missing_alloc_error("prover"))?;

                let cfg_child = Arc::new(TempConfig::new(
                    allocator_addr,
                    prover.subscribe.clone(),
                    enable_telemetry,
                    release_channel,
                )?);
                for device_idx in 0..count {
                    let child = Command::new(&r0vm_path)
                        .process_group(0)
                        .env("CUDA_VISIBLE_DEVICES", device_idx.to_string())
                        .arg("--config")
                        .arg(cfg_child.file.path())
                        .spawn()
                        .with_context(|| spawn_fail(&r0vm_path))?;
                    children.push(ChildState {
                        child,
                        _config: cfg_child.clone(),
                    });
                }
            }
        }

        Ok(())
    }

    pub async fn wait_for_workers(&mut self) {
        let workers = self.workers.lock().unwrap().clone();

        for worker in workers {
            worker.wait_for_stop().await;
        }
    }

    fn stop_actors(&mut self) {
        self.factory_rpc_server = None;
        self.allocator_rpc_server = None;

        if let Some(allocator) = &self.allocator {
            let _ = allocator.stop_gracefully("app shutdown");
        }

        if let Some(manager) = &self.manager {
            let _ = manager.stop_gracefully("app shutdown");
        }

        let workers = self.workers.lock().unwrap().clone();
        for worker in workers {
            let _ = worker.stop_gracefully("app shutdown");
        }

        if let Some(factory) = &self.factory {
            let _ = factory.stop_gracefully("app shutdown");
        }
    }

    async fn wait_for_actors(&mut self) {
        if let Some(allocator) = &self.allocator {
            tracing::info!("allocator: wait for stop");
            allocator.wait_for_stop().await;
        }

        if let Some(manager) = &self.manager {
            tracing::info!("manager: wait for stop");
            manager.wait_for_stop().await;
        }

        tracing::info!("worker: wait for stop");
        let workers = self.workers.lock().unwrap().clone();
        for worker in workers {
            worker.wait_for_stop().await;
        }

        if let Some(factory) = &self.factory {
            tracing::info!("factory: wait for stop");
            factory.wait_for_stop().await;
        }
    }

    async fn wait_for_children(&mut self) {
        tracing::info!(
            "waiting for children: {:?}",
            self.children
                .iter()
                .filter_map(|c| c.child.id())
                .collect::<Vec<_>>()
        );
        for child in &mut self.children {
            let result = child.child.wait().await;
            if let Some(err) = result.err() {
                tracing::warn!("Failed to wait on child: {err}");
            }
        }
    }

    pub async fn stop(mut self) {
        tracing::info!("app: stop");

        self.stop_actors();
        self.wait_for_actors().await;
        self.wait_for_children().await;
    }

    pub async fn proof_request(
        &mut self,
        request: ProofRequest,
    ) -> error::Result<JobInfo<ProofResult>> {
        let reply = self
            .manager
            .as_ref()
            .ok_or_else(|| error::Error::new("no manager configured"))?
            .ask(request)
            .await?;
        reply
            .status
            .try_into()
            .map_err(|e| error::Error::new(format!("unexpected ProofRequest reply {e}")))
    }

    pub async fn shrink_wrap_request(
        &mut self,
        request: ShrinkWrapRequest,
    ) -> error::Result<JobInfo<ShrinkWrapResult>> {
        let reply = self
            .manager
            .as_ref()
            .ok_or_else(|| error::Error::new("no manager configured"))?
            .ask(request)
            .await?;
        reply
            .status
            .try_into()
            .map_err(|e| error::Error::new(format!("unexpected ShrinkWrapRequest reply: {e}")))
    }
}

impl Drop for App {
    fn drop(&mut self) {
        self.stop_actors();

        if let Some(provider) = self.provider.take() {
            provider.stop();
        }
    }
}

async fn start_worker(
    release_channel: &Option<String>,
    alloc_ref: ActorRef<RemoteAllocatorActor>,
    alloc_ip: IpAddr,
    workers: Arc<Mutex<Vec<ActorRef<WorkerActor>>>>,
    subscribe: Vec<TaskKind>,
    simulate: Option<DevModeDelay>,
) -> Result<(), Box<dyn StdError>> {
    tracing::info!("Starting worker: {subscribe:?}");

    let worker_id = WorkerId::new_v4();
    let worker_hardware = worker_hardware(simulate)?;
    let reply = alloc_ref
        .ask(RegisterWorker {
            remote_address: None,
            worker_id,
            hardware: worker_hardware.clone(),
            deployment_version: deployment_version(release_channel),
        })
        .await??;

    let manager_addr = reply
        .manager_address
        .map(|addr| SocketAddr::new(addr.ip.unwrap_or(alloc_ip), addr.port))
        .ok_or("allocator gave us no manager to connect to")?;
    tracing::info!("Worker registered with allocator. Got manager = {manager_addr:?}",);

    let workers_clone = workers.clone();
    let worker_idx = workers.lock().unwrap().len();
    let factory_actor = actor::spawn(
        RemoteFactoryActor::new_with_remote_msg_callback(manager_addr, move |msg, msg_id, addr| {
            route_rpc_msg_to_worker(workers_clone.clone(), worker_idx, addr, msg, msg_id)
        })
        .await?,
    );

    let gpus = worker_hardware
        .iter()
        .filter_map(|h| match h {
            HardwareResource::Gpu(gpu) => Some(gpu.clone()),
            _ => None,
        })
        .collect();
    let mut workers = workers.lock().unwrap();
    let worker = WorkerActor::new(
        worker_id,
        factory_actor,
        alloc_ref.clone(),
        subscribe,
        simulate,
        gpus,
    )?;
    workers.push(worker);
    Ok(())
}

pub fn deployment_version(release_channel: &Option<String>) -> DeploymentVersion {
    DeploymentVersion {
        release_channel: release_channel
            .clone()
            .unwrap_or(DEFAULT_RELEASE_CHANNEL.into()),
        zkvm_version: env!("CARGO_PKG_VERSION")
            .parse()
            .expect("CARGO_PKG_VERSION should be a valid semver::Version"),
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

async fn route_rpc_msg_to_worker(
    workers: Arc<Mutex<Vec<ActorRef<WorkerActor>>>>,
    worker_idx: usize,
    remote_address: SocketAddr,
    msg: Option<RemoteWorkerRequest>,
    message_id: Option<RpcMessageId>,
) {
    let worker = workers.lock().unwrap()[worker_idx].clone();
    let ops = RpcDispatchOps {
        rpc_sender: None,
        message_id,
    };
    if let Some(msg) = msg {
        msg.dispatch(remote_address, worker, ops).await
    } else {
        let _ = worker.stop_gracefully("rpc end");
    }
}

type FactoryRpcServer = RpcServer<FactoryActor, RemoteFactoryRequest>;
type AllocatorRpcServer = RpcServer<AllocatorActor, RemoteAllocatorRequest>;

struct RpcDisconnect {
    remote_address: SocketAddr,
}

struct RpcServer<ReceiverT: Actor, MessageT> {
    listen_addr: SocketAddr,
    receiver: ActorRef<ReceiverT>,
    join_set: tokio::task::JoinSet<()>,
    _msg: PhantomData<MessageT>,
}

impl<ReceiverT, MessageT> RpcServer<ReceiverT, MessageT>
where
    ReceiverT: Actor + Message<RpcDisconnect>,
    MessageT: DispatchRpcMessage<ReceiverT> + serde::de::DeserializeOwned,
{
    pub fn new(listen_addr: SocketAddr, receiver: ActorRef<ReceiverT>) -> Self {
        Self {
            listen_addr,
            receiver,
            join_set: tokio::task::JoinSet::new(),
            _msg: PhantomData,
        }
    }

    pub async fn bind_and_listen(&mut self) -> anyhow::Result<SocketAddr> {
        assert!(
            self.join_set.is_empty(),
            "bind_and_listen called more than once"
        );

        let receiver = self.receiver.clone();
        let listener = TcpListener::bind(self.listen_addr).await?;
        let local_addr = listener.local_addr()?;

        self.join_set.spawn(async move {
            let mut join_set = tokio::task::JoinSet::new();
            loop {
                let (stream, remote_address) = match listener.accept().await {
                    Ok(result) => result,
                    Err(err) => {
                        tracing::error!("{err}");
                        break;
                    }
                };

                let meter = opentelemetry::global::meter("r0vm");
                let stream = metrics::StreamWithMetrics::new(stream, meter.clone());
                let receiver = receiver.clone();
                join_set.spawn(async move {
                    let (rpc_sender, mut rpc_receiver) = rpc_system(stream, meter);
                    let cloned_receiver = receiver.clone();
                    rpc_receiver
                        .receive_many::<MessageT, _>(move |req, message_id| {
                            let rpc_sender = rpc_sender.clone();
                            let receiver = cloned_receiver.clone();
                            let ops = RpcDispatchOps {
                                rpc_sender: Some(rpc_sender),
                                message_id,
                            };
                            req.dispatch(remote_address, receiver, ops)
                        })
                        .await;

                    // we don't worry about failing to deliver this message
                    let _ = receiver.tell(RpcDisconnect { remote_address }).await;
                });
            }
        });

        Ok(local_addr)
    }
}

type WriteStream = metrics::OwnedWriteHalfWithMetrics<tcp::OwnedWriteHalf>;

struct RpcDispatchOps {
    rpc_sender: Option<RpcSender<WriteStream>>,
    message_id: Option<RpcMessageId>,
}

impl RpcDispatchOps {
    async fn ask<ReceiverT, MessageT>(self, receiver: ActorRef<ReceiverT>, msg: MessageT)
    where
        ReceiverT: Message<MessageT>,
        MessageT: Send + 'static,
        <ReceiverT as Message<MessageT>>::Reply: serde::Serialize + Sync,
    {
        let message_id = self.message_id.expect("request should not have a response");
        let rpc_sender = self
            .rpc_sender
            .expect("ask should not be called on one-way RPC actor");

        let Ok(pending_reply) = receiver.ask_enqueue(msg).await else {
            rpc_sender
                .shutdown()
                .await
                .expect("we should be able to shutdown the socket");
            return;
        };

        tokio::task::spawn(async move {
            if let Ok(reply) = pending_reply.recv().await {
                // If we fail to send the reply, we don't worry. If the connection is closed we
                // should get a read error soon.
                let _ = rpc_sender.respond(&reply, message_id).await;
            } else {
                rpc_sender
                    .shutdown()
                    .await
                    .expect("we should be able to shutdown the socket");
            }
        });
    }

    async fn tell<ReceiverT, MessageT>(self, receiver: ActorRef<ReceiverT>, msg: MessageT)
    where
        ReceiverT: Message<MessageT>,
        MessageT: Send + 'static,
    {
        assert!(self.message_id.is_none());

        // If we fail to send the reply, we don't worry. If the connection is closed we
        // should get a read error soon.
        let _ = receiver.tell(msg).await;
    }
}

trait DispatchRpcMessage<ReceiverT: Actor> {
    fn dispatch(
        self,
        remote_address: SocketAddr,
        receiver: ActorRef<ReceiverT>,
        ops: RpcDispatchOps,
    ) -> impl Future<Output = ()> + Send + 'static;
}

#[allow(clippy::large_enum_variant)]
#[derive(Serialize, Deserialize, From)]
enum RemoteFactoryRequest {
    GetTasks(GetTasks),
    TaskUpdate(TaskUpdateMsg),
    TaskDone(TaskDoneMsg),
}

impl DispatchRpcMessage<FactoryActor> for RemoteFactoryRequest {
    async fn dispatch(
        self,
        remote_address: SocketAddr,
        receiver: ActorRef<FactoryActor>,
        ops: RpcDispatchOps,
    ) {
        match self {
            RemoteFactoryRequest::GetTasks(mut msg) => {
                msg.worker = Some(actor::spawn(RemoteWorkerActor::new_from_rpc_sender(
                    ops.rpc_sender
                        .clone()
                        .expect("ask should not be called on one-way RPC actor"),
                )));
                msg.remote_address = Some(remote_address);
                ops.tell(receiver, msg).await;
            }
            RemoteFactoryRequest::TaskUpdate(msg) => {
                ops.tell(receiver, msg).await;
            }
            RemoteFactoryRequest::TaskDone(msg) => {
                ops.tell(receiver, msg).await;
            }
        }
    }
}

#[allow(clippy::large_enum_variant)]
#[derive(Serialize, Deserialize, From)]
enum RemoteAllocatorRequest {
    RegisterWorker(allocator::RegisterWorker),
    ScheduleTask(allocator::ScheduleTask),
    AllocateHardware(allocator::AllocateHardware),
    DeallocateHardware(allocator::DeallocateHardware),
    EndTask(allocator::EndTask),
    RegisterManager(allocator::RegisterManager),
    GetStatus(allocator::GetStatus),
}

impl DispatchRpcMessage<AllocatorActor> for RemoteAllocatorRequest {
    async fn dispatch(
        self,
        remote_address: SocketAddr,
        receiver: ActorRef<AllocatorActor>,
        ops: RpcDispatchOps,
    ) {
        match self {
            RemoteAllocatorRequest::RegisterWorker(mut msg) => {
                msg.remote_address = Some(remote_address);
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::ScheduleTask(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::AllocateHardware(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::DeallocateHardware(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::EndTask(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::RegisterManager(mut msg) => {
                msg.remote_address = Some(remote_address);
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::GetStatus(msg) => ops.ask(receiver, msg).await,
        }
    }
}

#[derive(Serialize, Deserialize, From)]
enum RemoteWorkerRequest {
    TaskMsg(TaskMsg),
}

impl DispatchRpcMessage<WorkerActor> for RemoteWorkerRequest {
    async fn dispatch(
        self,
        _remote_address: SocketAddr,
        receiver: ActorRef<WorkerActor>,
        ops: RpcDispatchOps,
    ) {
        match self {
            RemoteWorkerRequest::TaskMsg(msg) => {
                ops.tell(receiver, msg).await;
            }
        }
    }
}

pub(crate) struct RemoteActor<ActorT> {
    rpc_sender: RpcSender<WriteStream>,
    rpc_receiver_handle: Option<JoinHandle<()>>,
    rpc_death_recv: Option<tokio::sync::oneshot::Receiver<()>>,
    remote_actor: std::marker::PhantomData<ActorT>,
}

impl<ActorT> RemoteActor<ActorT> {
    pub(crate) async fn new_with_remote_msg_callback<RemoteMsgT, FutT>(
        addr: SocketAddr,
        mut remote_msg_callback: impl FnMut(
            Option<RemoteMsgT>,
            Option<RpcMessageId>,
            SocketAddr,
        ) -> FutT
        + Send
        + 'static,
    ) -> anyhow::Result<Self>
    where
        RemoteMsgT: serde::de::DeserializeOwned,
        FutT: Future<Output = ()> + Send,
    {
        let meter = opentelemetry::global::meter("r0vm");
        let stream =
            metrics::StreamWithMetrics::new(TcpStream::connect(addr).await?, meter.clone());
        let (rpc_sender, mut rpc_receiver) = rpc_system(stream, meter);

        let (rpc_death_send, rpc_death_recv) = tokio::sync::oneshot::channel();
        let rpc_receiver_handle = tokio::task::spawn(async move {
            rpc_receiver
                .receive_many(|msg, id| remote_msg_callback(Some(msg), id, addr))
                .await;
            remote_msg_callback(None, None, addr).await;
            let _ = rpc_death_send.send(());
        });

        Ok(Self {
            rpc_sender,
            rpc_receiver_handle: Some(rpc_receiver_handle),
            rpc_death_recv: Some(rpc_death_recv),
            remote_actor: std::marker::PhantomData,
        })
    }

    pub(crate) fn new_from_rpc_sender(rpc_sender: RpcSender<WriteStream>) -> Self {
        Self {
            rpc_sender,
            rpc_receiver_handle: None,
            rpc_death_recv: None,
            remote_actor: std::marker::PhantomData,
        }
    }

    pub(crate) async fn new(addr: SocketAddr, name: &'static str) -> anyhow::Result<Self> {
        Self::new_with_remote_msg_callback(addr, move |msg: Option<()>, _, _| async move {
            if msg.is_some() {
                tracing::error!("{name}: received unexpected unsolicited RPC message");
            }
        })
        .await
    }
}

impl<ActorT: Send + 'static> Actor for RemoteActor<ActorT> {
    async fn on_start(&mut self, actor_ref: ActorRef<Self>) {
        if let Some(rpc_death_recv) = self.rpc_death_recv.take() {
            tokio::task::spawn(async move {
                let _ = rpc_death_recv.await;
                let _ = actor_ref.stop_gracefully("rpc connection closed");
            });
        }
    }

    async fn on_stop(&mut self) {
        let _ = self.rpc_sender.shutdown().await;
        if let Some(handle) = &self.rpc_receiver_handle {
            handle.abort();
        }
    }
}

macro_rules! remote_actor_ask {
    ($type:ty, $request:ty, $reply:ty, $msg_ty:ty) => {
        impl Message<$request> for $type {
            type Reply = $reply;

            async fn handle(&mut self, msg: $request, ctx: &mut Context<Self, Self::Reply>) {
                let reply_sender = ctx.reply_sender();

                let msg: $msg_ty = msg.into();
                let res = self
                    .rpc_sender
                    .ask(&msg, async move |response: $reply| {
                        if let Some(reply_sender) = reply_sender {
                            reply_sender.send(response).await;
                        }
                    })
                    .await;
                if let Err(error) = res {
                    tracing::error!("error communicating with remote actor: {error}");
                    let _ = ctx
                        .actor_ref()
                        .stop_gracefully(format!("rpc error: {error}"));
                }
            }
        }
    };
}
pub(crate) use remote_actor_ask;

macro_rules! remote_actor_tell {
    ($type:ty, $request:ty, $msg_ty:ty) => {
        impl Message<$request> for $type {
            type Reply = ();

            async fn handle(
                &mut self,
                msg: $request,
                ctx: &mut Context<Self, Self::Reply>,
            ) -> Self::Reply {
                let msg: $msg_ty = msg.into();
                let res = self.rpc_sender.tell(&msg).await;
                if let Err(error) = res {
                    tracing::error!("error communicating with remote actor: {error}");
                    let _ = ctx
                        .actor_ref()
                        .stop_gracefully(format!("rpc error: {error}"));
                }
            }
        }
    };
}
pub(crate) use remote_actor_tell;

//  _       _                     _
// | |_ ___| | ___ _ __ ___   ___| |_ _ __ _   _
// | __/ _ \ |/ _ \ '_ ` _ \ / _ \ __| '__| | | |
// | ||  __/ |  __/ | | | | |  __/ |_| |  | |_| |
//  \__\___|_|\___|_| |_| |_|\___|\__|_|   \__, |
//                                         |___/

struct OpenTelemetryProvider {
    tracer_provider: SdkTracerProvider,
    meter_provider: SdkMeterProvider,
    logger_provider: SdkLoggerProvider,
}

impl OpenTelemetryProvider {
    pub(crate) fn new() -> anyhow::Result<Self> {
        let resource = Resource::builder().with_service_name("r0vm").build();

        let log_exporter = opentelemetry_otlp::LogExporter::builder()
            .with_http()
            .build()?;

        let logger_provider = SdkLoggerProvider::builder()
            .with_resource(resource.clone())
            .with_batch_exporter(log_exporter)
            .build();

        tracing_subscriber::registry()
            .with(
                OpenTelemetryTracingBridge::new(&logger_provider)
                    .with_filter(EnvFilter::from_default_env()),
            )
            .with(
                tracing_subscriber::fmt::layer()
                    .with_ansi(false)
                    .without_time()
                    .with_filter(EnvFilter::from_default_env()),
            )
            .init();

        let span_exporter = opentelemetry_otlp::SpanExporter::builder()
            .with_http()
            .build()?;

        let tracer_provider = SdkTracerProvider::builder()
            .with_batch_exporter(span_exporter)
            .with_resource(resource.clone())
            .build();

        opentelemetry::global::set_tracer_provider(tracer_provider.clone());

        let metric_exporter = opentelemetry_otlp::MetricExporter::builder()
            .with_http()
            .build()?;

        let meter_provider = SdkMeterProvider::builder()
            .with_reader(
                PeriodicReader::builder(metric_exporter)
                    .with_interval(Duration::from_secs(1))
                    .build(),
            )
            .with_resource(resource.clone())
            .build();

        opentelemetry::global::set_meter_provider(meter_provider.clone());

        opentelemetry::global::set_text_map_propagator(TraceContextPropagator::new());

        Ok(Self {
            tracer_provider,
            meter_provider,
            logger_provider,
        })
    }

    pub(crate) fn stop(self) {
        tokio::task::spawn_blocking(move || {
            let _ = self.meter_provider.shutdown().inspect_err(|err| {
                tracing::warn!("{err:?}");
            });
            let _ = self.tracer_provider.shutdown().inspect_err(|err| {
                tracing::warn!("{err:?}");
            });
            let _ = self.logger_provider.shutdown().inspect_err(|err| {
                tracing::warn!("{err:?}");
            });
        });
    }
}
