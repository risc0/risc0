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
    io::{stdin, Write},
    net::{Ipv4Addr, SocketAddr, SocketAddrV4},
    os::{fd::AsFd as _, unix::net::UnixStream as StdUnixStream},
    path::{Path, PathBuf},
    time::Duration,
};

use anyhow::Context;
use kameo::prelude::*;
use nvml_wrapper::Nvml;
use opentelemetry_otlp::WithExportConfig as _;
use opentelemetry_sdk::{
    logs::SdkLoggerProvider,
    metrics::{PeriodicReader, SdkMeterProvider},
    propagation::TraceContextPropagator,
    trace::SdkTracerProvider,
    Resource,
};
use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};
use tempfile::NamedTempFile;
use tokio::{
    io::{AsyncReadExt as _, AsyncWriteExt as _},
    net::{tcp, TcpListener, UnixStream},
    process::Command,
    task::JoinHandle,
};
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt, EnvFilter, Layer};

use crate::Cli;

use self::{
    factory::{FactoryActor, FactoryRouterActor, RemoteFactoryActor},
    manager::ManagerActor,
    protocol::{
        factory::{GetTask, TaskDoneMsg, TaskUpdateMsg},
        JobInfo, ProofRequest, ProofResult, ShrinkWrapRequest, ShrinkWrapResult, TaskKind,
    },
    rpc::{rpc_system, RpcMessageId, RpcSender},
    worker::Worker,
};

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct WorkerConfig {
    pub pools: Vec<PoolConfig>,
}

impl From<Vec<TaskKind>> for WorkerConfig {
    fn from(task_kinds: Vec<TaskKind>) -> Self {
        WorkerConfig {
            pools: vec![PoolConfig {
                count: 1,
                profile: None,
                task_kinds,
            }],
        }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub(crate) struct PoolConfig {
    pub count: usize,
    pub profile: Option<DevModeDelay>,
    pub task_kinds: Vec<TaskKind>,
}

#[tokio::main]
pub(crate) async fn async_main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let is_manager = args.mode.manager;

    let config = if let Some(ref path) = args.mode.config {
        let str = tokio::fs::read_to_string(path).await?;
        Some(toml::from_str(&str)?)
    } else {
        Some(args.mode.worker.clone().into())
    };
    tracing::info!("{config:#?}");

    let mut app = App::new(
        is_manager,
        args.addr,
        args.api,
        args.storage.clone(),
        config,
        args.po2,
        /* enable_telemetry */ true,
    )
    .await?;

    if let Some(ref bin_path) = args.mode.elf {
        let binary = tokio::fs::read(bin_path).await?;
        let input = if let Some(ref input_path) = args.initial_input {
            tokio::fs::read(input_path).await?
        } else {
            vec![]
        };
        let request = ProofRequest {
            binary,
            input,
            assumptions: vec![],
            segment_limit_po2: None,
        };
        app.proof_request(request).await.unwrap();
    } else if is_manager {
        println!("Use Ctrl-C to stop");
        tokio::signal::ctrl_c()
            .await
            .expect("failed to listen for ctrl-c");
        println!();
    } else {
        app.wait_for_workers().await;
    }

    app.stop().await;

    Ok(())
}

async fn relay_proof_request(app: &mut App) -> Result<(), Box<dyn StdError>> {
    let socket: StdUnixStream = stdin().as_fd().try_clone_to_owned()?.into();

    socket.set_nonblocking(true)?;
    let mut socket = UnixStream::from_std(socket)?;

    let mut buf = vec![0u8; 4];
    socket
        .read_exact(&mut buf)
        .await
        .context("error reading RPC header")?;
    let body_len: u32 = bincode::deserialize(&buf).context("received invalid RPC header")?;
    let mut buf = vec![0u8; body_len as usize];
    socket
        .read_exact(&mut buf)
        .await
        .context("error reading RPC body")?;
    let request: ProofRequest =
        bincode::deserialize(&buf).context("error deserializing ProofRequest")?;

    let job_info = app
        .proof_request(request)
        .await
        .context("error running ProofRequest")?;

    let mut buf = vec![0u8; 4];
    bincode::serialize_into(&mut buf, &job_info)?;
    let body_len = buf.len() as u32 - 4;
    bincode::serialize_into(&mut buf[0..4], &body_len)?;
    socket.write_all(&buf).await?;

    Ok(())
}

#[tokio::main]
pub(crate) async fn rpc_main(num_gpus: Option<usize>) -> Result<(), Box<dyn StdError>> {
    let workers = num_gpus.unwrap_or_else(|| cuda_devices().unwrap_or(1));

    let execute_pool = PoolConfig {
        count: 1,
        profile: None,
        task_kinds: vec![TaskKind::Execute],
    };

    let primary_pool = PoolConfig {
        count: 1,
        profile: None,
        task_kinds: vec![TaskKind::ProveSegment, TaskKind::ProveKeccak],
    };

    let secondary_pool = PoolConfig {
        count: 1,
        profile: None,
        task_kinds: vec![
            TaskKind::Lift,
            TaskKind::Join,
            TaskKind::Union,
            TaskKind::Resolve,
        ],
    };

    let addr = SocketAddrV4::new(Ipv4Addr::UNSPECIFIED, 0).into();
    let mut app = App::new(
        /* is_manager */ true,
        Some(addr),
        /* api_addr */ None,
        /* storage_root */ None,
        Some(WorkerConfig {
            pools: vec![execute_pool],
        }),
        /* po2 */ None,
        /* enable_telemetry */ false,
    )
    .await?;

    let local_addr = app.local_addr.unwrap();
    let r0vm_path = std::env::current_exe()?;
    let primary_config = TempConfig::new(WorkerConfig {
        pools: vec![primary_pool],
    })?;
    let secondary_config = TempConfig::new(WorkerConfig {
        pools: vec![secondary_pool],
    })?;

    let mut children = vec![];
    for device_idx in 0..workers {
        let child = Command::new(&r0vm_path)
            .process_group(0)
            .env("CUDA_VISIBLE_DEVICES", device_idx.to_string())
            .arg("--config")
            .arg(primary_config.file.path())
            .arg("--addr")
            .arg(local_addr.to_string())
            .spawn()
            .with_context(|| spawn_fail(&r0vm_path))?;
        children.push(child);

        let child = Command::new(&r0vm_path)
            .process_group(0)
            .env("CUDA_VISIBLE_DEVICES", device_idx.to_string())
            .arg("--config")
            .arg(secondary_config.file.path())
            .arg("--addr")
            .arg(local_addr.to_string())
            .spawn()
            .with_context(|| spawn_fail(&r0vm_path))?;
        children.push(child);
    }

    let result = relay_proof_request(&mut app).await;

    app.stop().await;

    for mut child in children {
        child.wait().await?;
    }

    result
}

struct TempConfig {
    file: NamedTempFile,
}

impl TempConfig {
    fn new(config: WorkerConfig) -> anyhow::Result<Self> {
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

#[allow(clippy::large_enum_variant)]
#[derive(Serialize, Deserialize)]
enum RemoteRequest {
    GetTask(GetTask),
    TaskUpdate(TaskUpdateMsg),
    TaskDone(TaskDoneMsg),
}

pub(crate) struct App {
    provider: Option<OpenTelemetryProvider>,
    manager: Option<ActorRef<ManagerActor>>,
    factory: Option<ActorRef<FactoryActor>>,
    workers: Vec<Worker>,
    server: Option<Server>,
    local_addr: Option<SocketAddr>,
}

impl App {
    #[allow(clippy::too_many_arguments)]
    pub async fn new(
        is_manager: bool,
        mut addr: Option<SocketAddr>,
        api_addr: Option<SocketAddr>,
        storage_root: Option<PathBuf>,
        worker_config: Option<WorkerConfig>,
        po2: Option<u32>,
        enable_telemetry: bool,
    ) -> Result<Self, Box<dyn StdError>> {
        let provider = enable_telemetry.then(OpenTelemetryProvider::new);

        let mut manager = None;
        let mut factory = None;
        let mut workers = vec![];
        let mut server = None;
        let mut local_addr = None;

        if is_manager {
            let storage_root = if api_addr.is_some() {
                Some(storage_root.unwrap_or_else(default_storage_root))
            } else {
                storage_root
            };

            let factory_ref = kameo::spawn(FactoryActor::new());
            factory = Some(factory_ref.clone());

            let manager_ref =
                kameo::spawn(ManagerActor::new(factory_ref.clone(), storage_root.clone()));
            manager = Some(manager_ref.clone());

            if let Some(listen_addr) = addr {
                server = Some(Server::new(listen_addr, factory_ref));
                addr = server.as_mut().unwrap().start().await?;
                local_addr = addr;
            }

            if let Some(addr) = api_addr {
                tokio::spawn(crate::api::run(
                    addr,
                    storage_root.unwrap(),
                    manager_ref,
                    po2,
                ));
            }
        }

        let factory_ref = match addr {
            Some(addr) => {
                let remote = kameo::spawn(RemoteFactoryActor::new(addr).await?);
                kameo::spawn(FactoryRouterActor::Remote(remote))
            }
            None => kameo::spawn(FactoryRouterActor::Local(factory.as_ref().unwrap().clone())),
        };

        if let Some(config) = worker_config {
            for pool in config.pools {
                tracing::info!(
                    "Starting worker pool: {}, task_kinds: {:?}",
                    pool.count,
                    pool.task_kinds
                );
                for _ in 0..pool.count {
                    let mut worker =
                        Worker::new(factory_ref.clone(), pool.task_kinds.clone(), pool.profile);
                    worker.start();
                    workers.push(worker);
                }
            }
        }

        Ok(Self {
            provider,
            manager,
            factory,
            workers,
            server,
            local_addr,
        })
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

        if let Some(server) = self.server.take() {
            tracing::info!("server: stop");
            server.stop().await;
        }

        if let Some(manager) = self.manager.take() {
            if manager.stop_gracefully().await.is_ok() {
                tracing::info!("manager: wait for stop");
                manager.wait_for_stop().await;
            }
        }

        tracing::info!("worker: stop");
        for worker in self.workers {
            worker.stop().await;
        }

        if let Some(factory) = self.factory {
            if factory.stop_gracefully().await.is_ok() {
                tracing::info!("factory: wait for stop");
                factory.wait_for_stop().await;
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

    #[allow(dead_code)]
    pub async fn shrink_wrap_request(
        &mut self,
        request: ShrinkWrapRequest,
    ) -> anyhow::Result<JobInfo<ShrinkWrapResult>> {
        let reply = self.manager.as_ref().unwrap().ask(request).await?;
        Ok(reply.status.try_into().unwrap())
    }
}

struct Server {
    listen_addr: SocketAddr,
    factory: ActorRef<FactoryActor>,
    join_handle: Option<JoinHandle<()>>,
}

impl Server {
    pub fn new(listen_addr: SocketAddr, factory: ActorRef<FactoryActor>) -> Self {
        Self {
            listen_addr,
            factory,
            join_handle: None,
        }
    }

    pub async fn start(&mut self) -> anyhow::Result<Option<SocketAddr>> {
        if self.join_handle.is_some() {
            return Ok(None);
        }

        let factory = self.factory.clone();
        let listener = TcpListener::bind(self.listen_addr).await?;
        let local_addr = listener.local_addr()?;

        self.join_handle = Some(tokio::spawn(async move {
            let mut join_set = tokio::task::JoinSet::new();
            loop {
                let (stream, _addr) = match listener.accept().await {
                    Ok(result) => result,
                    Err(err) => {
                        tracing::error!("{err}");
                        break;
                    }
                };

                let meter = opentelemetry::global::meter("r0vm");
                let stream = metrics::StreamWithMetrics::new(stream, meter.clone());
                let factory = factory.clone();
                join_set.spawn(async move {
                    let (rpc_sender, mut rpc_receiver) = rpc_system(stream, meter);
                    rpc_receiver
                        .receive_many(move |req, message_id| {
                            let rpc_sender = rpc_sender.clone();
                            let factory = factory.clone();
                            handle_request(rpc_sender, req, message_id, factory)
                        })
                        .await;
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

async fn handle_request(
    rpc_sender: RpcSender<WriteStream>,
    request: RemoteRequest,
    message_id: Option<RpcMessageId>,
    factory: ActorRef<FactoryActor>,
) {
    match request {
        RemoteRequest::GetTask(msg) => {
            let message_id = message_id.expect("request not expecting response");

            // The PendingReply isn't Send, so I have to do this :/
            let (tx, rx) = tokio::sync::oneshot::channel();
            tokio::task::spawn(async move {
                let pending_reply = factory.ask(msg).enqueue().await.unwrap();
                tx.send(()).unwrap();
                if let Ok(reply) = pending_reply.await {
                    rpc_sender.respond(&reply, message_id).await.unwrap();
                }
            });

            // wait until message has been enqueued in mailbox to preserve ordering.
            let _ = rx.await;
        }
        RemoteRequest::TaskUpdate(msg) => {
            assert!(message_id.is_none());
            factory.tell(msg).await.unwrap();
        }
        RemoteRequest::TaskDone(msg) => {
            assert!(message_id.is_none());
            factory.tell(msg).await.unwrap();
        }
    }
}

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

        let logger_provider = SdkLoggerProvider::builder()
            .with_resource(resource.clone())
            .with_batch_exporter(
                opentelemetry_otlp::LogExporter::builder()
                    .with_http()
                    .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
                    .build()
                    .unwrap(),
            )
            .build();

        tracing_subscriber::registry()
            // .with(OpenTelemetryTracingBridge::new(&logger_provider))
            .with(tracing_subscriber::fmt::layer().with_filter(EnvFilter::from_default_env()))
            .init();

        let tracer_provider = SdkTracerProvider::builder()
            .with_batch_exporter(
                opentelemetry_otlp::SpanExporter::builder()
                    .with_http()
                    .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
                    .build()
                    .unwrap(),
            )
            .with_resource(resource.clone())
            .build();

        opentelemetry::global::set_text_map_propagator(TraceContextPropagator::new());
        opentelemetry::global::set_tracer_provider(tracer_provider.clone());

        let meter_provider = SdkMeterProvider::builder()
            .with_reader(
                PeriodicReader::builder(
                    opentelemetry_otlp::MetricExporter::builder()
                        .with_http()
                        .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
                        .build()
                        .unwrap(),
                )
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
