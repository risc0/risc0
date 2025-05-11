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

use std::{error::Error as StdError, time::Duration};

use kameo::{error::RegistryError, prelude::*, remote::ActorSwarm};
use opentelemetry_otlp::WithExportConfig as _;
use opentelemetry_sdk::{propagation::TraceContextPropagator, trace::SdkTracerProvider, Resource};
use tokio::time::sleep;

use crate::Cli;

use self::{
    factory::FactoryActor,
    job::JobActor,
    manager::ManagerActor,
    protocol::{ProofRequest, TaskKind},
    worker::{GenericActorRef, Worker},
};

const LISTEN_ADDR: &str = "/ip4/0.0.0.0/udp/9000/quic-v1";

pub(crate) async fn main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    let is_manager = args.mode.manager;
    let task_kinds = args.mode.worker.clone();
    let mut app = App::new(is_manager, task_kinds).await?;

    if let Some(ref bin_path) = args.mode.elf {
        let binary = std::fs::read(bin_path)?;
        let input = if let Some(ref input_path) = args.initial_input {
            std::fs::read(input_path)?
        } else {
            vec![]
        };
        app.run_binary(binary, input).await;
    } else {
        println!("Use Ctrl-C to stop");
        tokio::signal::ctrl_c()
            .await
            .expect("failed to listen for ctrl-c");
    }

    app.stop().await;

    Ok(())
}

pub(crate) async fn client_main(args: &Cli) -> Result<(), Box<dyn StdError>> {
    ActorSwarm::bootstrap()?;

    let bin_path = args.mode.elf.as_ref().unwrap();
    let binary = std::fs::read(bin_path)?;
    let input = if let Some(ref input_path) = args.initial_input {
        std::fs::read(input_path)?
    } else {
        vec![]
    };

    let manager: RemoteActorRef<ManagerActor> = retry_lookup("manager").await?.unwrap();
    let reply = manager.ask(&ProofRequest { binary, input }).await?;
    reply.receipt.verify_integrity()?;

    Ok(())
}

pub(crate) struct App {
    provider: SdkTracerProvider,
    manager: Option<ActorRef<ManagerActor>>,
    factory: Option<GenericActorRef<FactoryActor>>,
    worker: Option<Worker>,
}

impl App {
    pub async fn new(
        is_manager: bool,
        task_kinds: Vec<TaskKind>,
    ) -> Result<Self, Box<dyn StdError>> {
        Self::new_inner(is_manager, false, task_kinds).await
    }

    #[cfg(test)]
    pub async fn new_test(
        is_manager: bool,
        task_kinds: Vec<TaskKind>,
    ) -> Result<Self, Box<dyn StdError>> {
        Self::new_inner(is_manager, true, task_kinds).await
    }

    async fn new_inner(
        is_manager: bool,
        is_test: bool,
        task_kinds: Vec<TaskKind>,
    ) -> Result<Self, Box<dyn StdError>> {
        let provider = init_tracer_provider();
        let mut manager = None;
        let mut factory = None;
        let mut worker = None;

        let swarm = ActorSwarm::bootstrap()?;

        if is_manager {
            if !is_test {
                swarm.listen_on(LISTEN_ADDR.parse()?).await?;
            }

            let factory_ref = kameo::spawn(FactoryActor::new());
            factory_ref.register("factory").await?;
            factory = Some(GenericActorRef::Local(factory_ref.clone()));

            let manager_ref = kameo::spawn(ManagerActor::new(factory_ref));
            manager_ref.register("manager").await?;
            manager = Some(manager_ref);
        }

        if !task_kinds.is_empty() {
            let factory_ref = match factory {
                Some(factory) => factory,
                None => {
                    let factory = retry_lookup("factory").await?.unwrap();
                    GenericActorRef::Remote(factory)
                }
            };

            tracing::info!("Starting worker: {task_kinds:?}");
            worker = Some(Worker::new(factory_ref.clone(), task_kinds));
            worker.as_mut().unwrap().start();

            factory = Some(factory_ref);
        }

        Ok(Self {
            provider,
            manager,
            factory,
            worker,
        })
    }

    pub async fn stop(mut self) {
        println!("stopping");

        if let Some(manager) = self.manager.take() {
            manager.stop_gracefully().await.unwrap();
            println!("waiting for manager");
            manager.wait_for_stop().await;
        }

        if let Some(worker) = self.worker.take() {
            println!("waiting for worker");
            worker.stop().await;
        }

        if let Some(GenericActorRef::Local(factory)) = self.factory {
            factory.stop_gracefully().await.unwrap();
            println!("waiting for factory");
            factory.wait_for_stop().await;
        }

        self.provider.shutdown().unwrap();
    }

    pub async fn run_binary(&mut self, binary: Vec<u8>, input: Vec<u8>) {
        let Some(GenericActorRef::Local(ref factory)) = self.factory else {
            unreachable!()
        };
        let job = kameo::spawn(JobActor::new(factory.clone()));
        job.tell(ProofRequest { binary, input }).await.unwrap();
        job.wait_for_stop().await;
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

async fn retry_lookup<A>(name: &str) -> Result<Option<RemoteActorRef<A>>, RegistryError>
where
    A: Actor + RemoteActor,
{
    for _ in 0..5 {
        if let Some(actor) = RemoteActorRef::lookup(name).await? {
            return Ok(Some(actor));
        }
        sleep(Duration::from_millis(100)).await;
    }
    Ok(None)
}
