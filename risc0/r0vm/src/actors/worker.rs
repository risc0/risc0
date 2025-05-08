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

#![allow(unused)]

use std::{error::Error as StdError, sync::Arc, time::Duration};

use kameo::{error::RegistryError, prelude::*, remote::dial_opts::DialOpts};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, NullSegmentRef, ProverOpts, VerifierContext,
};
use tokio::{task::JoinSet, time::sleep};

use crate::{
    actors::{
        factory::FactoryActor,
        manager::TaskManagerActor,
        protocol::{
            factory::{
                GetTask, SegmentReady, Session, TaskDone, TaskDoneMsg, TaskStatus, TaskStatusMsg,
            },
            ExecuteTask, Task, TaskId, TaskKind,
        },
    },
    Cli,
};

use super::protocol::ProveSegmentTask;

pub(crate) async fn main(_args: Cli) -> Result<(), Box<dyn StdError>> {
    ActorSwarm::bootstrap()?
        .dial(
            DialOpts::unknown_peer_id()
                .address("/ip4/127.0.0.1/udp/9000/quic-v1".parse()?)
                .build(),
        )
        .await?;

    let factory = retry_lookup().await?.unwrap();
    let worker = Worker::new(factory);
    Ok(worker.run().await?)
}

struct Worker {
    factory: RemoteActorRef<FactoryActor>,
}

impl Worker {
    pub fn new(factory: RemoteActorRef<FactoryActor>) -> Self {
        Self { factory }
    }

    pub async fn run(&self) -> anyhow::Result<()> {
        loop {
            let msg = self
                .factory
                .ask(&GetTask {
                    kinds: vec![TaskKind::Execute, TaskKind::ProveSegment, TaskKind::Lift],
                })
                .await?;

            match msg.task {
                Task::Execute(inner) => {
                    self.execute(msg.job_id, msg.task_id, Arc::into_inner(inner).unwrap())
                        .await?
                }
                Task::ProveSegment(inner) => {
                    self.prove_segment(msg.job_id, msg.task_id, Arc::into_inner(inner).unwrap())
                        .await?
                }
                Task::Lift(task) => todo!(),
                _ => unimplemented!(),
            }
        }
    }

    async fn execute(
        &self,
        job_id: ActorID,
        task_id: TaskId,
        task: ExecuteTask,
    ) -> anyhow::Result<()> {
        tracing::info!("ELF: {} bytes", task.binary.len());

        let relay = RelayActor::spawn(self.factory.clone());
        let executor = ExecutorActor::spawn_in_thread(relay.clone());

        let msg = ExecuteTaskMsg {
            job_id,
            task_id,
            task_kind: TaskKind::Execute,
            task,
        };
        let session = executor.ask(msg).await?;

        relay.stop_gracefully().await?;
        relay.wait_for_stop().await;

        self.factory
            .tell(&TaskDoneMsg {
                job_id,
                task_id,
                body: TaskDone::Session(Arc::new(session)),
            })
            .await?;

        Ok(())
    }

    async fn prove_segment(
        &self,
        job_id: ActorID,
        task_id: TaskId,
        task: ProveSegmentTask,
    ) -> anyhow::Result<()> {
        let prover = get_prover_server(&ProverOpts::default())?;
        let ctx = VerifierContext::default();
        let receipt = prover.prove_segment(&ctx, &task.segment)?;
        Ok(())
    }
}

async fn retry_lookup() -> Result<Option<RemoteActorRef<FactoryActor>>, RegistryError> {
    for _ in 0..5 {
        if let Some(actor) = RemoteActorRef::<FactoryActor>::lookup("factory").await? {
            return Ok(Some(actor));
        }
        sleep(Duration::from_millis(100)).await;
    }
    Ok(None)
}

pub(crate) struct ExecuteTaskMsg {
    pub job_id: ActorID,
    pub task_id: TaskId,
    pub task_kind: TaskKind,
    pub task: ExecuteTask,
}

#[derive(Actor)]
struct ExecutorActor {
    relay: ActorRef<RelayActor>,
}

impl ExecutorActor {
    pub fn spawn_in_thread(relay: ActorRef<RelayActor>) -> ActorRef<Self> {
        spawn_in_thread(Self { relay })
    }
}

impl Message<ExecuteTaskMsg> for ExecutorActor {
    type Reply = anyhow::Result<Session>;

    async fn handle(
        &mut self,
        msg: ExecuteTaskMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let env = ExecutorEnv::builder()
            .write_slice(&msg.task.input)
            .build()?;
        let mut exec = ExecutorImpl::from_elf(env, &msg.task.binary)?;
        let session = exec.run_with_callback(|segment| {
            let msg = TaskStatusMsg {
                job_id: msg.job_id,
                task_id: msg.task_id,
                body: TaskStatus::Segment(segment),
            };
            self.relay.tell(msg).blocking_send()?;
            Ok(Box::new(NullSegmentRef))
        })?;

        let session = Session {
            segment_count: session.segments.len(),
            user_cycles: session.user_cycles,
            total_cycles: session.total_cycles,
            journal: session.journal,
        };

        Ok(session)
    }
}

#[derive(Actor)]
struct RelayActor {
    factory: RemoteActorRef<FactoryActor>,
}

impl RelayActor {
    pub fn spawn(factory: RemoteActorRef<FactoryActor>) -> ActorRef<Self> {
        spawn(Self { factory })
    }
}

impl Message<TaskStatusMsg> for RelayActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskStatusMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.factory.tell(&msg).await.unwrap();
    }
}

impl Message<TaskDoneMsg> for RelayActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.factory.tell(&msg).await.unwrap();
    }
}
