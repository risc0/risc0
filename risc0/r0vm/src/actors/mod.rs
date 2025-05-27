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
pub(crate) mod protocol;
pub(crate) mod rpc;
#[cfg(test)]
mod tests;
pub(crate) mod worker;

use std::{error::Error as StdError, net::SocketAddr, path::PathBuf, time::Duration};

use futures::{SinkExt as _, StreamExt as _};
use kameo::prelude::*;
use opentelemetry::metrics::Counter;
use opentelemetry_otlp::WithExportConfig as _;
use opentelemetry_sdk::{
    logs::SdkLoggerProvider,
    metrics::{PeriodicReader, SdkMeterProvider},
    propagation::TraceContextPropagator,
    trace::SdkTracerProvider,
    Resource,
};
use protocol::{JobInfo, ProofRequest};
use risc0_circuit_rv32im::execute::DEFAULT_SEGMENT_LIMIT_PO2;
use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};
use tokio::{
    net::{TcpListener, TcpStream},
    task::JoinHandle,
};
use tokio_util::codec::{FramedRead, FramedWrite, LengthDelimitedCodec};
use tracing_subscriber::{layer::SubscriberExt, util::SubscriberInitExt, EnvFilter, Layer};

use crate::Cli;

use self::{
    factory::{FactoryActor, FactoryRouterActor, RemoteFactoryActor},
    manager::ManagerActor,
    protocol::{
        factory::{GetTask, TaskDoneMsg, TaskUpdateMsg},
        TaskKind,
    },
    rpc::{rpc_system, RpcMessageId, RpcSender},
    worker::Worker,
};

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct SimulationConfig {
    pub pools: Vec<PoolConfig>,
}

#[derive(Debug, Serialize, Deserialize)]
pub(crate) struct PoolConfig {
    pub count: usize,
    pub profile: DevModeDelay,
    pub task_kinds: Vec<TaskKind>,
}

#[tokio::main]
pub(crate) async fn async_main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let is_manager = args.mode.manager;
    let task_kinds = args.mode.worker.clone();

    let config = if let Some(ref path) = args.simulate {
        let str = tokio::fs::read_to_string(path).await?;
        Some(toml::from_str(&str)?)
    } else {
        None
    };
    tracing::info!("{config:#?}");

    let mut app = App::new(
        is_manager,
        task_kinds,
        args.addr,
        args.api,
        args.storage.clone(),
        config,
        args.po2.unwrap_or(DEFAULT_SEGMENT_LIMIT_PO2),
    )
    .await?;

    if let Some(ref bin_path) = args.mode.elf {
        let binary = tokio::fs::read(bin_path).await?;
        let input = if let Some(ref input_path) = args.initial_input {
            tokio::fs::read(input_path).await?
        } else {
            vec![]
        };
        app.run_binary(binary, input).await.unwrap();
    } else {
        println!("Use Ctrl-C to stop");
        tokio::signal::ctrl_c()
            .await
            .expect("failed to listen for ctrl-c");
        println!();
    }

    app.stop().await;

    Ok(())
}

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
}

impl App {
    pub async fn new(
        is_manager: bool,
        task_kinds: Vec<TaskKind>,
        mut addr: Option<SocketAddr>,
        api_addr: Option<SocketAddr>,
        storage_root: Option<PathBuf>,
        sim_config: Option<SimulationConfig>,
        po2: usize,
    ) -> Result<Self, Box<dyn StdError>> {
        // let provider = if sim_config.is_none() {
        //     Some(init_tracer_provider())
        // } else {
        //     None
        // };
        let provider = Some(OpenTelemetryProvider::new());

        let mut manager = None;
        let mut factory = None;
        let mut workers = vec![];
        let mut server = None;

        if is_manager {
            let storage_root = storage_root.unwrap_or_else(default_storage_root);

            let factory_ref = kameo::spawn(FactoryActor::new());
            factory = Some(factory_ref.clone());

            let manager_ref =
                kameo::spawn(ManagerActor::new(factory_ref.clone(), storage_root.clone()));
            manager = Some(manager_ref.clone());

            if let Some(listen_addr) = addr {
                server = Some(Server::new(listen_addr, factory_ref));
                addr = Some(server.as_mut().unwrap().start().await?.unwrap());
            }

            if let Some(addr) = api_addr {
                tokio::spawn(crate::api::run(addr, storage_root, manager_ref));
            }
        }

        let factory_ref = match addr {
            Some(addr) => {
                let remote = kameo::spawn(RemoteFactoryActor::new(addr).await?);
                kameo::spawn(FactoryRouterActor::Remote(remote))
            }
            None => kameo::spawn(FactoryRouterActor::Local(factory.as_ref().unwrap().clone())),
        };

        if let Some(config) = sim_config {
            for pool in config.pools {
                tracing::info!(
                    "Starting simulated worker pool: {}, task_kinds: {:?}",
                    pool.count,
                    pool.task_kinds
                );
                for _ in 0..pool.count {
                    let mut worker = Worker::new(
                        factory_ref.clone(),
                        pool.task_kinds.clone(),
                        Some(pool.profile),
                        po2,
                    );
                    worker.start();
                    workers.push(worker);
                }
            }
        } else if !task_kinds.is_empty() {
            tracing::info!("Starting worker: {task_kinds:?}");
            let mut worker = Worker::new(factory_ref.clone(), task_kinds.clone(), None, po2);
            worker.start();
            workers.push(worker);
        }

        Ok(Self {
            provider,
            manager,
            factory,
            workers,
            server,
        })
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

    pub async fn run_binary(&mut self, binary: Vec<u8>, input: Vec<u8>) -> anyhow::Result<JobInfo> {
        let request = ProofRequest {
            binary,
            input,
            assumptions: vec![],
        };
        let reply = self.manager.as_ref().unwrap().ask(request).await?;
        Ok(reply.info.unwrap())
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
            loop {
                let (stream, _addr) = match listener.accept().await {
                    Ok(result) => result,
                    Err(err) => {
                        tracing::error!("{err}");
                        break;
                    }
                };

                let factory = factory.clone();
                tokio::spawn(async move {
                    let (rpc_sender, mut rpc_receiver) = rpc_system(stream);
                    rpc_receiver
                        .receive_many(move |req, message_id| {
                            let rpc_sender = rpc_sender.clone();
                            let factory = factory.clone();
                            tokio::task::spawn(async move {
                                handle_request(rpc_sender, req, message_id, factory).await
                            });
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

async fn handle_request(
    rpc_sender: RpcSender,
    request: RemoteRequest,
    message_id: Option<RpcMessageId>,
    factory: ActorRef<FactoryActor>,
) {
    match request {
        RemoteRequest::GetTask(msg) => {
            let message_id = message_id.expect("request not expecting response");
            let reply = factory.ask(msg).await.unwrap();
            rpc_sender.respond(&reply, message_id).await.unwrap();
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

struct TcpSession {
    pub(crate) stream: TcpStream,
    codec: LengthDelimitedCodec,
    tx_messages: Counter<u64>,
    tx_bytes: Counter<u64>,
    rx_messages: Counter<u64>,
    rx_bytes: Counter<u64>,
}

impl TcpSession {
    #[expect(dead_code)]
    pub(crate) fn new(stream: TcpStream) -> Self {
        let codec = LengthDelimitedCodec::builder()
            .max_frame_length(1024 * 1024 * 1024)
            .new_codec();
        let meter = opentelemetry::global::meter("r0vm");
        let tx_messages = meter.u64_counter("tx_messages").build();
        let tx_bytes = meter.u64_counter("tx_bytes").with_unit("bytes").build();
        let rx_messages = meter.u64_counter("rx_messages").build();
        let rx_bytes = meter.u64_counter("rx_bytes").with_unit("bytes").build();
        Self {
            stream,
            codec,
            tx_messages,
            tx_bytes,
            rx_messages,
            rx_bytes,
        }
    }

    #[expect(dead_code)]
    pub(crate) async fn send<T: serde::Serialize>(&mut self, msg: T) -> anyhow::Result<()> {
        let mut writer = FramedWrite::new(&mut self.stream, self.codec.clone());

        let frame = bincode::serialize(&msg)?;
        self.tx_bytes.add(frame.len() as u64, &[]);
        self.tx_messages.add(1, &[]);
        tracing::info!("tx {} bytes", frame.len());

        writer.send(frame.into()).await?;

        Ok(())
    }

    #[expect(dead_code)]
    pub(crate) async fn recv<T: serde::de::DeserializeOwned>(
        &mut self,
    ) -> anyhow::Result<Option<T>> {
        let mut reader = FramedRead::new(&mut self.stream, self.codec.clone());
        let frame = match reader.next().await {
            Some(result) => result?,
            None => return Ok(None),
        };

        self.rx_bytes.add(frame.len() as u64, &[]);
        self.rx_messages.add(1, &[]);
        tracing::info!("rx {} bytes", frame.len());

        Ok(Some(bincode::deserialize(&frame)?))
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
