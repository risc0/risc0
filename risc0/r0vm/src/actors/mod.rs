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
#[cfg(test)]
mod tests;
pub(crate) mod worker;

use std::{error::Error as StdError, net::SocketAddr, path::PathBuf};

use futures::{SinkExt as _, StreamExt};
use kameo::prelude::*;
use opentelemetry_otlp::WithExportConfig as _;
use opentelemetry_sdk::{propagation::TraceContextPropagator, trace::SdkTracerProvider, Resource};
use protocol::{JobInfo, ProofRequest};
use risc0_circuit_rv32im::execute::DEFAULT_SEGMENT_LIMIT_PO2;
use risc0_zkvm::DevModeDelay;
use serde::{Deserialize, Serialize};
use tokio::{
    net::{TcpListener, TcpStream},
    task::JoinHandle,
};
use tokio_util::{
    codec::{FramedRead, FramedWrite, LengthDelimitedCodec},
    sync::CancellationToken,
};

use crate::Cli;

use self::{
    factory::{FactoryActor, FactoryRouterActor, RemoteFactoryActor},
    manager::ManagerActor,
    protocol::{
        factory::{GetTask, TaskDoneMsg, TaskUpdateMsg},
        TaskKind,
    },
    worker::Worker,
};

#[derive(Serialize, Deserialize)]
pub(crate) struct SimulationConfig {
    pub pools: Vec<PoolConfig>,
}

#[derive(Serialize, Deserialize)]
pub(crate) struct PoolConfig {
    pub count: usize,
    pub profile: DevModeDelay,
    pub task_kinds: Vec<TaskKind>,
}

pub(crate) async fn main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let is_manager = args.mode.manager;
    let task_kinds = args.mode.worker.clone();

    let config = if let Some(ref path) = args.simulate {
        let json = std::fs::read_to_string(path)?;
        Some(serde_json::from_str(&json)?)
    } else {
        None
    };

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
        let binary = std::fs::read(bin_path)?;
        let input = if let Some(ref input_path) = args.initial_input {
            std::fs::read(input_path)?
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
    provider: SdkTracerProvider,
    manager: Option<ActorRef<ManagerActor>>,
    factory: Option<ActorRef<FactoryActor>>,
    workers: Vec<Worker>,
    server: Option<Server>,
}

impl App {
    pub async fn new(
        is_manager: bool,
        task_kinds: Vec<TaskKind>,
        addr: Option<SocketAddr>,
        api_addr: Option<SocketAddr>,
        storage_root: Option<PathBuf>,
        sim_config: Option<SimulationConfig>,
        po2: usize,
    ) -> Result<Self, Box<dyn StdError>> {
        let provider = init_tracer_provider();
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

            if let Some(addr) = addr {
                server = Some(Server::new(addr, factory_ref));
                server.as_mut().unwrap().start().await?;
            }

            if let Some(addr) = api_addr {
                tokio::spawn(crate::api::run(addr, storage_root, manager_ref));
            }
        }

        let factory_ref = match factory {
            Some(ref factory) => kameo::spawn(FactoryRouterActor::Local(factory.clone())),
            None => {
                let remote = kameo::spawn(RemoteFactoryActor::new(addr.unwrap()).await?);
                kameo::spawn(FactoryRouterActor::Remote(remote))
            }
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
            manager.stop_gracefully().await.unwrap();
            tracing::info!("manager: wait for stop");
            manager.wait_for_stop().await;
        }

        tracing::info!("worker: stop");
        for worker in self.workers {
            worker.stop().await;
        }

        if let Some(factory) = self.factory {
            factory.stop_gracefully().await.unwrap();
            tracing::info!("factory: wait for stop");
            factory.wait_for_stop().await;
        }

        self.provider.shutdown().unwrap();
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
    addr: SocketAddr,
    factory: ActorRef<FactoryActor>,
    token: CancellationToken,
    join_handle: Option<JoinHandle<()>>,
}

impl Server {
    pub fn new(addr: SocketAddr, factory: ActorRef<FactoryActor>) -> Self {
        Self {
            addr,
            factory,
            token: CancellationToken::new(),
            join_handle: None,
        }
    }

    pub async fn start(&mut self) -> anyhow::Result<()> {
        if self.join_handle.is_some() {
            return Ok(());
        }

        let factory = self.factory.clone();
        let token = self.token.clone();
        let listener = TcpListener::bind(self.addr).await?;

        self.join_handle = Some(tokio::spawn(async move {
            loop {
                let result = tokio::select! {
                    _ = token.cancelled() => {
                        tracing::info!("tcp listener: stop");
                        break;
                    }
                    result = listener.accept() => result
                };

                let (mut stream, _addr) = match result {
                    Ok(result) => result,
                    Err(err) => {
                        tracing::error!("{err}");
                        break;
                    }
                };

                let factory = factory.clone();
                let token = token.clone();
                tokio::spawn(async move {
                    loop {
                        let result = tokio::select! {
                            _ = token.cancelled() => {
                                tracing::info!("tcp session: stop");
                                break;
                            }
                            result = recv_request(&mut stream) => result
                        }
                        .unwrap();
                        match result {
                            Some(request) => {
                                handle_request(&mut stream, request, factory.clone()).await
                            }
                            None => break,
                        }
                    }
                });
            }
        }));

        Ok(())
    }

    pub async fn stop(self) {
        if let Some(join_handle) = self.join_handle {
            self.token.cancel();
            join_handle.await.unwrap();
        }
    }
}

async fn recv_request(stream: &mut TcpStream) -> anyhow::Result<Option<RemoteRequest>> {
    recv(stream).await
}

async fn handle_request(
    stream: &mut TcpStream,
    request: RemoteRequest,
    factory: ActorRef<FactoryActor>,
) {
    match request {
        RemoteRequest::GetTask(msg) => {
            let reply = factory.ask(msg).await.unwrap();
            send(stream, reply).await.unwrap();
        }
        RemoteRequest::TaskUpdate(msg) => {
            factory.tell(msg).await.unwrap();
        }
        RemoteRequest::TaskDone(msg) => {
            factory.tell(msg).await.unwrap();
        }
    }
}

fn default_storage_root() -> PathBuf {
    dirs::home_dir().unwrap().join(".risc0").join("r0vm")
}

fn init_tracer_provider() -> SdkTracerProvider {
    let otlp_exporter = opentelemetry_otlp::SpanExporter::builder()
        .with_http()
        .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
        .build()
        .unwrap();

    let provider = SdkTracerProvider::builder()
        .with_batch_exporter(otlp_exporter)
        .with_resource(Resource::builder().with_service_name("r0vm").build())
        .build();
    opentelemetry::global::set_text_map_propagator(TraceContextPropagator::new());
    opentelemetry::global::set_tracer_provider(provider.clone());

    provider
}

pub(crate) async fn send<T: serde::Serialize>(
    stream: &mut TcpStream,
    msg: T,
) -> anyhow::Result<()> {
    let encoder = LengthDelimitedCodec::builder()
        .max_frame_length(1024 * 1024 * 1024)
        .new_codec();
    let mut writer = FramedWrite::new(stream, encoder);

    let bytes = bincode::serialize(&msg)?;
    tracing::info!("tx {} bytes", bytes.len());
    writer.send(bytes.into()).await?;

    Ok(())
}

pub(crate) async fn recv<T: serde::de::DeserializeOwned>(
    stream: &mut TcpStream,
) -> anyhow::Result<Option<T>> {
    let decoder = LengthDelimitedCodec::builder()
        .max_frame_length(1024 * 1024 * 1024)
        .new_codec();

    let mut reader = FramedRead::new(stream, decoder);
    let frame = match reader.next().await {
        Some(result) => result?,
        None => return Ok(None),
    };

    tracing::info!("rx {} bytes", frame.len());
    Ok(Some(bincode::deserialize(&frame)?))
}
