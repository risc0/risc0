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

pub(crate) mod allocator;
pub(crate) mod config;
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
    net::{Ipv4Addr, SocketAddr, SocketAddrV4},
    os::{fd::AsFd as _, unix::net::UnixStream as StdUnixStream},
    path::{Path, PathBuf},
    sync::Arc,
    time::Duration,
};

use anyhow::Context as _;
use derive_more::From;
use kameo::prelude::*;
use nvml_wrapper::Nvml;
use opentelemetry_appender_tracing::layer::OpenTelemetryTracingBridge;
use opentelemetry_sdk::{
    Resource,
    logs::SdkLoggerProvider,
    metrics::{PeriodicReader, SdkMeterProvider},
    trace::SdkTracerProvider,
};
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
    allocator::{AllocatorActor, AllocatorRouterActor, RegisterManager},
    config::{
        AllocatorConfig, AppConfig, ExecutorConfig, ManagerConfig, ProverConfig, TelemetryConfig,
        VERSION, VersionConfig, default_api_listen_addr,
    },
    factory::{FactoryActor, FactoryRouterActor},
    manager::ManagerActor,
    protocol::{
        JobInfo, JobRequest, ProofRequest, ProofResult, ShrinkWrapRequest, ShrinkWrapResult,
        TaskKind,
        factory::{GetTask, TaskDoneMsg, TaskUpdateMsg},
    },
    rpc::{RpcMessageId, RpcSender, rpc_system},
    worker::Worker,
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
    if app.manager.is_some() {
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

    let addr = SocketAddrV4::new(Ipv4Addr::UNSPECIFIED, 0).into();
    let mut app = App::new(
        AppConfig {
            version: VERSION,
            api: None,
            manager: Some(ManagerConfig {
                listen: Some(addr),
                allocator: None,
            }),
            allocator: Some(AllocatorConfig {
                rpc_listen: Some(addr),
                proxy_listen: None,
            }),
            executor: Some(ExecutorConfig {
                manager: None,
                allocator: None,
                count: 1,
            }),
            prover: Some(vec![
                ProverConfig {
                    manager: None,
                    allocator: None,
                    count: num_gpus,
                    subscribe: large_tasks,
                    simulate: None,
                },
                ProverConfig {
                    manager: None,
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

struct TempConfig {
    file: NamedTempFile,
}

impl TempConfig {
    fn new(
        manager_addr: SocketAddr,
        allocator_addr: SocketAddr,
        subscribe: Vec<TaskKind>,
        enable_telemetry: bool,
    ) -> anyhow::Result<Self> {
        let config = AppConfig {
            version: VERSION,
            api: None,
            manager: None,
            allocator: None,
            executor: None,
            prover: Some(vec![ProverConfig {
                manager: Some(manager_addr),
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

pub(crate) struct App {
    provider: Option<OpenTelemetryProvider>,
    manager: Option<ActorRef<ManagerActor>>,
    allocator: Option<ActorRef<AllocatorActor>>,
    factory: Option<ActorRef<FactoryActor>>,
    workers: Vec<Worker>,
    factory_rpc_server: Option<FactoryRpcServer>,
    allocator_rpc_server: Option<AllocatorRpcServer>,
    children: Vec<ChildState>,
}

impl App {
    pub async fn new(cfg: AppConfig, enable_logging: bool) -> Result<Self, Box<dyn StdError>> {
        let mut manager = None;
        let mut allocator = None;
        let mut factory = None;
        let mut factory_rpc_server = None;
        let mut local_factory_rpc_addr = None;
        let mut allocator_rpc_server = None;
        let mut local_allocator_rpc_addr = None;

        let provider = if cfg.telemetry.is_some() {
            Some(OpenTelemetryProvider::new())
        } else {
            if enable_logging {
                init_logging();
            }
            None
        };

        if let Some(cfg_allocator) = &cfg.allocator {
            tracing::info!("Starting allocator");

            let alloc_ref = kameo::spawn(AllocatorActor::new());
            allocator = Some(alloc_ref.clone());

            if let Some(rpc_listen_addr) = cfg_allocator.rpc_listen {
                allocator_rpc_server =
                    Some(AllocatorRpcServer::new(rpc_listen_addr, alloc_ref.clone()));
                local_allocator_rpc_addr =
                    allocator_rpc_server.as_mut().unwrap().start(true).await?;
            }

            if let Some(proxy_listen_addr) = cfg_allocator.proxy_listen {
                tokio::spawn(allocator::run_proxy(proxy_listen_addr, alloc_ref));
            }
        }

        if let Some(cfg_manager) = &cfg.manager {
            let storage_root = if cfg.api.is_some() {
                Some(if let Some(cfg) = &cfg.storage {
                    cfg.path.clone()
                } else {
                    default_storage_root()
                })
            } else {
                None
            };

            let alloc_ref = AllocatorRouterActor::new(&cfg_manager.allocator, &allocator).await?;

            let factory_ref = kameo::spawn(FactoryActor::new(alloc_ref.clone()));
            factory = Some(factory_ref.clone());

            let manager_ref =
                kameo::spawn(ManagerActor::new(factory_ref.clone(), storage_root.clone()));
            manager = Some(manager_ref.clone());

            if let Some(listen_addr) = cfg_manager.listen {
                factory_rpc_server = Some(FactoryRpcServer::new(listen_addr, factory_ref));
                local_factory_rpc_addr = factory_rpc_server.as_mut().unwrap().start(false).await?;
            }

            if let Some(cfg_api) = &cfg.api {
                let api_addr = cfg_api.listen.unwrap_or_else(default_api_listen_addr);
                tokio::spawn(crate::api::run(
                    api_addr,
                    storage_root.unwrap(),
                    manager_ref,
                    cfg_api.po2,
                ));

                alloc_ref
                    .ask(RegisterManager {
                        zkvm_version: env!("CARGO_PKG_VERSION").parse().unwrap(),
                        port: api_addr.port(),
                        path: "/".into(),
                        remote_address: None,
                    })
                    .await?;
            }
        }

        let mut workers = vec![];
        let mut children = vec![];

        if let Some(cfg_executor) = cfg.executor {
            Self::create_executors(&cfg_executor, &factory, &allocator, &mut workers).await?;
        }

        if let Some(cfg_prover) = cfg.prover {
            Self::create_provers(
                &cfg_prover,
                local_factory_rpc_addr,
                local_allocator_rpc_addr,
                &factory,
                &allocator,
                &mut workers,
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
        })
    }

    async fn create_executors(
        executor: &ExecutorConfig,
        factory: &Option<ActorRef<FactoryActor>>,
        allocator: &Option<ActorRef<AllocatorActor>>,
        workers: &mut Vec<Worker>,
    ) -> Result<(), Box<dyn StdError>> {
        tracing::info!("Starting executor: {executor:?}");

        let alloc_ref = AllocatorRouterActor::new(&executor.allocator, allocator).await?;
        let factory_ref = FactoryRouterActor::new(&executor.manager, factory).await?;

        for _ in 0..executor.count {
            let mut worker = Worker::new(
                factory_ref.clone(),
                alloc_ref.clone(),
                vec![TaskKind::Execute],
                None,
            );
            worker.start()?;
            workers.push(worker);
        }

        Ok(())
    }

    #[allow(clippy::too_many_arguments)]
    async fn create_provers(
        cfg_prover: &[ProverConfig],
        local_factory_addr: Option<SocketAddr>,
        local_allocator_addr: Option<SocketAddr>,
        factory: &Option<ActorRef<FactoryActor>>,
        allocator: &Option<ActorRef<AllocatorActor>>,
        workers: &mut Vec<Worker>,
        children: &mut Vec<ChildState>,
        enable_telemetry: bool,
    ) -> Result<(), Box<dyn StdError>> {
        for prover in cfg_prover {
            tracing::info!("Starting prover: {prover:?}");

            let count = prover.count.unwrap_or_else(|| cuda_devices().unwrap_or(1));
            if (cfg_prover.len() == 1 && count == 1) || prover.simulate.is_some() {
                let alloc_ref = AllocatorRouterActor::new(&prover.allocator, allocator).await?;
                let factory_ref = FactoryRouterActor::new(&prover.manager, factory).await?;

                let mut worker = Worker::new(
                    factory_ref.clone(),
                    alloc_ref.clone(),
                    prover.subscribe.clone(),
                    prover.simulate,
                );
                worker.start()?;
                workers.push(worker);
            } else {
                let r0vm_path = std::env::current_exe()?;
                if prover.manager.is_none() && local_factory_addr.is_none() {
                    return Err(anyhow::anyhow!(
                        "Invalid configuration: \
                        either manager must run locally or prover.manager must be set"
                    )
                    .into());
                }
                let manager_addr = prover
                    .manager
                    .unwrap_or_else(|| local_factory_addr.unwrap());

                if prover.allocator.is_none() && local_allocator_addr.is_none() {
                    return Err(anyhow::anyhow!(
                        "Invalid configuration: \
                        either allocator must run locally or prover.allocator must be set"
                    )
                    .into());
                }
                let allocator_addr = prover
                    .allocator
                    .unwrap_or_else(|| local_allocator_addr.unwrap());

                let cfg_child = Arc::new(TempConfig::new(
                    manager_addr,
                    allocator_addr,
                    prover.subscribe.clone(),
                    enable_telemetry,
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
        for worker in &mut self.workers {
            if let Some(death_receiver) = worker.death_receiver.take() {
                let _ = death_receiver.await;
            }
        }
    }

    pub async fn stop(mut self) {
        tracing::info!("app: stop");

        if let Some(server) = self.factory_rpc_server.take() {
            tracing::info!("factory_rpc_server: stop");
            server.stop().await;
        }

        if let Some(server) = self.allocator_rpc_server.take() {
            tracing::info!("allocator_rpc_server: stop");
            server.stop().await;
        }

        if let Some(allocator) = self.allocator.take()
            && allocator.stop_gracefully().await.is_ok()
        {
            tracing::info!("allocator: wait for stop");
            allocator.wait_for_stop().await;
        }

        if let Some(manager) = self.manager.take()
            && manager.stop_gracefully().await.is_ok()
        {
            tracing::info!("manager: wait for stop");
            manager.wait_for_stop().await;
        }

        tracing::info!("worker: stop");
        for worker in self.workers {
            worker.stop().await;
        }

        if let Some(factory) = self.factory
            && factory.stop_gracefully().await.is_ok()
        {
            tracing::info!("factory: wait for stop");
            factory.wait_for_stop().await;
        }

        for mut child in self.children {
            let result = child.child.wait().await;
            if let Some(err) = result.err() {
                tracing::warn!("Failed to wait on child: {err}");
            }
        }

        if let Some(provider) = self.provider {
            provider.stop();
        }
    }

    pub async fn proof_request(
        &mut self,
        request: ProofRequest,
    ) -> anyhow::Result<JobInfo<ProofResult>> {
        let reply = self.manager.as_ref().unwrap().ask(request).await?;
        Ok(reply.status.try_into().unwrap())
    }

    pub async fn shrink_wrap_request(
        &mut self,
        request: ShrinkWrapRequest,
    ) -> anyhow::Result<JobInfo<ShrinkWrapResult>> {
        let reply = self.manager.as_ref().unwrap().ask(request).await?;
        Ok(reply.status.try_into().unwrap())
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
    join_handle: Option<JoinHandle<()>>,
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
            join_handle: None,
            _msg: PhantomData,
        }
    }

    pub async fn start(&mut self, forward_errors: bool) -> anyhow::Result<Option<SocketAddr>> {
        if self.join_handle.is_some() {
            return Ok(None);
        }

        let receiver = self.receiver.clone();
        let listener = TcpListener::bind(self.listen_addr).await?;
        let local_addr = listener.local_addr()?;

        self.join_handle = Some(tokio::spawn(async move {
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
                                rpc_sender,
                                message_id,
                                forward_errors,
                            };
                            req.dispatch(remote_address, receiver, ops)
                        })
                        .await;
                    receiver
                        .tell(RpcDisconnect { remote_address })
                        .await
                        .unwrap();
                });
            }
        }));

        Ok(Some(local_addr))
    }

    pub async fn stop(self) {
        if let Some(join_handle) = self.join_handle {
            join_handle.abort();
        }
    }
}

type WriteStream = metrics::OwnedWriteHalfWithMetrics<tcp::OwnedWriteHalf>;

struct RpcDispatchOps {
    rpc_sender: RpcSender<WriteStream>,
    message_id: Option<RpcMessageId>,
    forward_errors: bool,
}

impl RpcDispatchOps {
    async fn ask<ReceiverT, MessageT>(self, receiver: ActorRef<ReceiverT>, msg: MessageT)
    where
        ReceiverT: Message<MessageT>,
        MessageT: Send + 'static,
        <<ReceiverT as Message<MessageT>>::Reply as Reply>::Ok: serde::Serialize + Sync,
        <<ReceiverT as Message<MessageT>>::Reply as Reply>::Error: serde::Serialize + Sync,
    {
        let message_id = self.message_id.expect("request not expecting response");

        // The PendingReply isn't Send, so I have to do this :/
        let (tx, rx) = tokio::sync::oneshot::channel();
        tokio::task::spawn(async move {
            let pending_reply = receiver.ask(msg).enqueue().await.unwrap();
            tx.send(()).unwrap();

            if self.forward_errors {
                match pending_reply.await {
                    Ok(reply) => {
                        self.rpc_sender
                            .respond(&std::result::Result::<_, ()>::Ok(reply), message_id)
                            .await
                            .unwrap();
                    }
                    Err(SendError::HandlerError(error)) => {
                        self.rpc_sender
                            .respond(&std::result::Result::<(), _>::Err(error), message_id)
                            .await
                            .unwrap();
                    }
                    Err(other_error) => {
                        panic!("rpc actor send error: {other_error:?}")
                    }
                }
            } else if let Ok(reply) = pending_reply.await {
                self.rpc_sender.respond(&reply, message_id).await.unwrap();
            }
        });

        // wait until message has been enqueued in mailbox to preserve ordering.
        let _ = rx.await;
    }

    async fn tell<ReceiverT, MessageT>(self, receiver: ActorRef<ReceiverT>, msg: MessageT)
    where
        ReceiverT: Message<MessageT>,
        MessageT: Send + 'static,
    {
        assert!(self.message_id.is_none());
        receiver.tell(msg).await.unwrap();
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
    GetTask(GetTask),
    TaskUpdate(TaskUpdateMsg),
    TaskDone(TaskDoneMsg),
}

impl DispatchRpcMessage<FactoryActor> for RemoteFactoryRequest {
    async fn dispatch(
        self,
        _remote_address: SocketAddr,
        receiver: ActorRef<FactoryActor>,
        ops: RpcDispatchOps,
    ) {
        match self {
            RemoteFactoryRequest::GetTask(msg) => {
                ops.ask(receiver, msg).await;
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
    ChooseWorker(allocator::ChooseWorker),
    AllocateHardware(allocator::AllocateHardware),
    DeallocateHardware(allocator::DeallocateHardware),
    RegisterManager(allocator::RegisterManager),
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
            RemoteAllocatorRequest::ChooseWorker(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::AllocateHardware(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::DeallocateHardware(msg) => {
                ops.ask(receiver, msg).await;
            }
            RemoteAllocatorRequest::RegisterManager(mut msg) => {
                msg.remote_address = Some(remote_address);
                ops.ask(receiver, msg).await;
            }
        }
    }
}

macro_rules! routing_actor_impl {
    ($type:ty, $request:ty, $reply:ty) => {
        impl Message<$request> for $type {
            type Reply = ForwardedReply<$request, $reply>;

            async fn handle(
                &mut self,
                msg: $request,
                ctx: &mut Context<Self, Self::Reply>,
            ) -> Self::Reply {
                match self {
                    Self::Local(actor_ref) => ctx.forward(actor_ref, msg).await,
                    Self::Remote(actor_ref) => ctx.forward(actor_ref, msg).await,
                }
            }
        }
    };
}
pub(crate) use routing_actor_impl;

pub(crate) struct RemoteActor<ActorT> {
    rpc_sender: RpcSender<WriteStream>,
    rpc_receiver_handle: JoinHandle<()>,
    rpc_death_recv: Option<tokio::sync::oneshot::Receiver<()>>,
    remote_actor: std::marker::PhantomData<ActorT>,
}

impl<ActorT> RemoteActor<ActorT> {
    pub(crate) async fn new(addr: SocketAddr) -> anyhow::Result<Self> {
        let meter = opentelemetry::global::meter("r0vm");
        let stream =
            metrics::StreamWithMetrics::new(TcpStream::connect(addr).await?, meter.clone());
        let (rpc_sender, mut rpc_receiver) = rpc_system(stream, meter);

        let (rpc_death_send, rpc_death_recv) = tokio::sync::oneshot::channel();
        let rpc_receiver_handle = tokio::task::spawn(async move {
            rpc_receiver
                .receive_many(|_: (), _| async {
                    tracing::error!("received unexpected unsolicited RPC message");
                })
                .await;
            let _ = rpc_death_send.send(());
        });

        Ok(Self {
            rpc_sender,
            rpc_receiver_handle,
            rpc_death_recv: Some(rpc_death_recv),
            remote_actor: std::marker::PhantomData,
        })
    }
}

impl<ActorT: Send + 'static> Actor for RemoteActor<ActorT> {
    type Error = anyhow::Error;

    async fn on_start(&mut self, actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        let rpc_death_recv = self.rpc_death_recv.take().unwrap();
        tokio::task::spawn(async move {
            let _ = rpc_death_recv.await;
            actor_ref.kill();
        });
        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        _reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        self.rpc_sender.shutdown().await?;
        self.rpc_receiver_handle.abort();

        Ok(())
    }
}

macro_rules! remote_actor_ask {
    ($type:ty, $request:ty, $reply:ty, $msg_ty:ty) => {
        impl Message<$request> for $type {
            type Reply = DelegatedReply<$reply>;

            async fn handle(
                &mut self,
                msg: $request,
                ctx: &mut Context<Self, Self::Reply>,
            ) -> Self::Reply {
                let (delegated_reply, reply_sender) = ctx.reply_sender();

                let msg: $msg_ty = msg.into();
                self.rpc_sender
                    .ask(&msg, move |response: $reply| {
                        if let Some(reply_sender) = reply_sender {
                            reply_sender.send(response);
                        }
                    })
                    .await
                    .unwrap();
                delegated_reply
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
                _ctx: &mut Context<Self, Self::Reply>,
            ) -> Self::Reply {
                let msg: $msg_ty = msg.into();
                self.rpc_sender.tell(&msg).await.unwrap();
            }
        }
    };
}
pub(crate) use remote_actor_tell;

fn default_storage_root() -> PathBuf {
    dirs::home_dir().unwrap().join(".risc0").join("r0vm")
}

struct OpenTelemetryProvider {
    tracer_provider: SdkTracerProvider,
    meter_provider: SdkMeterProvider,
    logger_provider: SdkLoggerProvider,
}

impl OpenTelemetryProvider {
    pub(crate) fn new() -> Self {
        let resource = Resource::builder().with_service_name("r0vm").build();

        let log_exporter = opentelemetry_otlp::LogExporter::builder()
            .with_http()
            .build()
            .unwrap();

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
            .build()
            .unwrap();

        let tracer_provider = SdkTracerProvider::builder()
            .with_batch_exporter(span_exporter)
            .with_resource(resource.clone())
            .build();

        opentelemetry::global::set_tracer_provider(tracer_provider.clone());

        let metric_exporter = opentelemetry_otlp::MetricExporter::builder()
            .with_http()
            .build()
            .unwrap();

        let meter_provider = SdkMeterProvider::builder()
            .with_reader(
                PeriodicReader::builder(metric_exporter)
                    .with_interval(Duration::from_secs(1))
                    .build(),
            )
            .with_resource(resource.clone())
            .build();

        opentelemetry::global::set_meter_provider(meter_provider.clone());

        Self {
            tracer_provider,
            meter_provider,
            logger_provider,
        }
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
