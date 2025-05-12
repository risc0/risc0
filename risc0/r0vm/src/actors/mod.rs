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

use std::{error::Error as StdError, net::SocketAddr};

use futures::{SinkExt as _, StreamExt};
use kameo::prelude::*;
use opentelemetry_otlp::WithExportConfig as _;
use opentelemetry_sdk::{propagation::TraceContextPropagator, trace::SdkTracerProvider, Resource};
use serde::{Deserialize, Serialize};
use tokio::{
    net::{TcpListener, TcpStream},
    task::{JoinHandle, JoinSet},
};
use tokio_util::{
    codec::{FramedRead, FramedWrite, LengthDelimitedCodec},
    sync::CancellationToken,
};

use crate::Cli;

use self::{
    factory::{FactoryActor, FactoryRouterActor, RemoteFactoryActor},
    job::JobActor,
    manager::ManagerActor,
    protocol::{
        factory::{GetTask, TaskDoneMsg, TaskUpdateMsg},
        ProofReply, ProofRequest, TaskKind,
    },
    worker::Worker,
};

pub(crate) async fn main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let is_manager = args.mode.manager;
    let task_kinds = args.mode.worker.clone();
    let mut app = App::new(is_manager, task_kinds, args.addr, false).await?;

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

pub(crate) async fn client_main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let bin_path = args.mode.elf.as_ref().unwrap();
    let binary = std::fs::read(bin_path)?;
    let input = if let Some(ref input_path) = args.initial_input {
        std::fs::read(input_path)?
    } else {
        vec![]
    };

    tracing::info!("Sending request");
    let mut tcp = TcpStream::connect(args.addr.unwrap()).await?;
    let msg = RemoteRequest::ProofRequest(ProofRequest { binary, input });
    send(&mut tcp, msg).await?;
    let reply: ProofReply = recv(&mut tcp).await?.unwrap();
    reply.receipt.verify_integrity()?;
    tracing::info!("Receipt verified");

    Ok(())
}

#[derive(Serialize, Deserialize)]
enum RemoteRequest {
    ProofRequest(ProofRequest),
    GetTask(GetTask),
    TaskUpdate(TaskUpdateMsg),
    TaskDone(TaskDoneMsg),
}

pub(crate) struct App {
    provider: SdkTracerProvider,
    manager: Option<ActorRef<ManagerActor>>,
    factory: Option<ActorRef<FactoryActor>>,
    worker: Option<Worker>,
    server: Option<Server>,
}

impl App {
    pub async fn new(
        is_manager: bool,
        task_kinds: Vec<TaskKind>,
        addr: Option<SocketAddr>,
        is_test: bool,
    ) -> Result<Self, Box<dyn StdError>> {
        let provider = init_tracer_provider();
        let mut manager = None;
        let mut factory = None;
        let mut worker = None;
        let mut server = None;

        if is_manager {
            let factory_ref = kameo::spawn(FactoryActor::new());
            factory = Some(factory_ref.clone());

            let manager_ref = kameo::spawn(ManagerActor::new(factory_ref.clone()));
            manager = Some(manager_ref.clone());

            if !is_test {
                server = Some(Server::new(addr, manager_ref, factory_ref));
                server.as_mut().unwrap().start().await?;
            }
        }

        if !task_kinds.is_empty() {
            let factory_ref = match factory {
                Some(ref factory) => kameo::spawn(FactoryRouterActor::Local(factory.clone())),
                None => {
                    let remote = kameo::spawn(RemoteFactoryActor::new(addr.unwrap()).await?);
                    kameo::spawn(FactoryRouterActor::Remote(remote))
                }
            };

            tracing::info!("Starting worker: {task_kinds:?}");
            worker = Some(Worker::new(factory_ref, task_kinds));
            worker.as_mut().unwrap().start();
        }

        Ok(Self {
            provider,
            manager,
            factory,
            worker,
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

        if let Some(worker) = self.worker.take() {
            tracing::info!("worker: stop");
            worker.stop().await;
        }

        if let Some(factory) = self.factory {
            factory.stop_gracefully().await.unwrap();
            tracing::info!("factory: wait for stop");
            factory.wait_for_stop().await;
        }

        self.provider.shutdown().unwrap();
    }

    pub async fn run_binary(
        &mut self,
        binary: Vec<u8>,
        input: Vec<u8>,
    ) -> anyhow::Result<ProofReply> {
        let job = kameo::spawn(JobActor::new(self.factory.as_ref().unwrap().clone()));
        let reply = job.ask(ProofRequest { binary, input }).await?;
        job.wait_for_stop().await;
        Ok(reply)
    }
}

struct Server {
    addr: Option<SocketAddr>,
    manager: ActorRef<ManagerActor>,
    factory: ActorRef<FactoryActor>,
    token: CancellationToken,
    join_handle: Option<JoinHandle<()>>,
}

impl Server {
    pub fn new(
        addr: Option<SocketAddr>,
        manager: ActorRef<ManagerActor>,
        factory: ActorRef<FactoryActor>,
    ) -> Self {
        Self {
            addr,
            manager,
            factory,
            token: CancellationToken::new(),
            join_handle: None,
        }
    }

    pub async fn start(&mut self) -> anyhow::Result<()> {
        if self.join_handle.is_some() {
            return Ok(());
        }

        let addr = self.addr.unwrap();
        let manager = self.manager.clone();
        let factory = self.factory.clone();
        let token = self.token.clone();
        let listener = TcpListener::bind(addr).await?;

        self.join_handle = Some(tokio::spawn(async move {
            let mut join_set = JoinSet::new();
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

                let manager = manager.clone();
                let factory = factory.clone();
                let token = token.clone();
                join_set.spawn(async move {
                    let mut session = RemoteSession { manager, factory };
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
                            Some(request) => session.handle_request(&mut stream, request).await,
                            None => break,
                        }
                    }
                });
            }
            join_set.join_all().await;
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

struct RemoteSession {
    manager: ActorRef<ManagerActor>,
    factory: ActorRef<FactoryActor>,
}

impl RemoteSession {
    pub async fn handle_request(&mut self, stream: &mut TcpStream, request: RemoteRequest) {
        match request {
            RemoteRequest::ProofRequest(msg) => {
                let reply = self.manager.ask(msg).await.unwrap();
                send(stream, reply).await.unwrap();
            }
            RemoteRequest::GetTask(msg) => {
                let reply = self.factory.ask(msg).await.unwrap();
                send(stream, reply).await.unwrap();
            }
            RemoteRequest::TaskUpdate(msg) => {
                self.factory.tell(msg).await.unwrap();
            }
            RemoteRequest::TaskDone(msg) => {
                self.factory.tell(msg).await.unwrap();
            }
        }
    }
}

fn init_tracer_provider() -> SdkTracerProvider {
    let otlp_exporter = opentelemetry_otlp::SpanExporter::builder()
        .with_http()
        .with_protocol(opentelemetry_otlp::Protocol::HttpBinary)
        .build()
        .unwrap();

    let provider = SdkTracerProvider::builder()
        // .with_simple_exporter(opentelemetry_stdout::SpanExporter::default())
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
    let encoder = LengthDelimitedCodec::new();
    let mut writer = FramedWrite::new(stream, encoder);

    let bytes = bincode::serialize(&msg)?;
    writer.send(bytes.into()).await?;

    Ok(())
}

pub(crate) async fn recv<T: serde::de::DeserializeOwned>(
    stream: &mut TcpStream,
) -> anyhow::Result<Option<T>> {
    let decoder = LengthDelimitedCodec::new();

    let mut reader = FramedRead::new(stream, decoder);
    let frame = match reader.next().await {
        Some(result) => result?,
        None => return Ok(None),
    };

    Ok(Some(bincode::deserialize(&frame)?))
}
