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

use std::{error::Error as StdError, sync::Arc, time::Duration};

use kameo::{error::RegistryError, prelude::*, remote::dial_opts::DialOpts};
use risc0_zkvm::{
    get_prover_server, ExecutorEnv, ExecutorImpl, NullSegmentRef, ProverOpts, VerifierContext,
};
use tokio::{task::JoinHandle, time::sleep};
use tokio_util::sync::CancellationToken;

use crate::{
    actors::{
        factory::FactoryActor,
        protocol::{
            factory::{
                GetTask, JoinNode, Session, TaskDone, TaskDoneMsg, TaskStatus, TaskStatusMsg,
            },
            worker::TaskMsg,
            ExecuteTask, JoinTask, LiftTask, ProveSegmentTask, Task, TaskId, TaskKind,
        },
    },
    Cli,
};

pub(crate) async fn main(_args: Cli) -> Result<(), Box<dyn StdError>> {
    ActorSwarm::bootstrap()?
        .dial(
            DialOpts::unknown_peer_id()
                .address("/ip4/127.0.0.1/udp/9000/quic-v1".parse()?)
                .build(),
        )
        .await?;

    let factory = retry_lookup().await?.unwrap();
    let task_kinds = vec![
        TaskKind::Execute,
        TaskKind::ProveSegment,
        TaskKind::Lift,
        TaskKind::Join,
    ];
    let mut worker = Worker::new(factory, task_kinds);
    worker.start();
    sleep(Duration::from_secs(5)).await;
    worker.stop().await;

    Ok(())
}

struct Processor {
    factory: RemoteActorRef<FactoryActor>,
}

pub(crate) struct Worker {
    factory: RemoteActorRef<FactoryActor>,
    task_kinds: Vec<TaskKind>,
    token: CancellationToken,
    join_handle: Option<JoinHandle<()>>,
}

impl Worker {
    pub fn new(factory: RemoteActorRef<FactoryActor>, task_kinds: Vec<TaskKind>) -> Self {
        Self {
            factory,
            task_kinds,
            token: CancellationToken::new(),
            join_handle: None,
        }
    }

    pub fn start(&mut self) {
        if self.join_handle.is_some() {
            return;
        }

        let request = GetTask {
            kinds: self.task_kinds.clone(),
        };
        let factory = self.factory.clone();
        let processor = Processor {
            factory: factory.clone(),
        };
        let token = self.token.clone();
        self.join_handle = Some(tokio::spawn(async move {
            loop {
                tokio::select! {
                    _ = token.cancelled() => {
                        tracing::info!("stopping");
                        break;
                    }
                    msg = factory.ask(&request) => {
                        processor.process_task(msg.unwrap()).await.unwrap();
                    }
                }
            }
        }));
    }

    pub async fn stop(self) {
        if let Some(join_handle) = self.join_handle {
            self.token.cancel();
            join_handle.await.unwrap();
        }
    }
}

impl Processor {
    async fn process_task(&self, msg: TaskMsg) -> anyhow::Result<()> {
        match msg.task {
            Task::Execute(task) => self.execute(msg.job_id, msg.task_id, task).await,
            Task::ProveSegment(task) => self.prove_segment(msg.job_id, msg.task_id, task).await,
            Task::Lift(task) => self.lift(msg.job_id, msg.task_id, task).await,
            Task::Join(task) => self.join(msg.job_id, msg.task_id, task).await,
            _ => unimplemented!(),
        }
    }

    async fn execute(
        &self,
        job_id: ActorID,
        task_id: TaskId,
        task: Arc<ExecuteTask>,
    ) -> anyhow::Result<()> {
        tracing::info!("ELF: {} bytes", task.binary.len());

        let relay = RelayActor::spawn(self.factory.clone());
        let executor = ExecutorActor::spawn_in_thread(relay.clone());

        let msg = ExecuteTaskMsg {
            job_id,
            task_id,
            task: Arc::into_inner(task).unwrap(),
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
        task: Arc<ProveSegmentTask>,
    ) -> anyhow::Result<()> {
        tracing::info!("ProveSegment: {}", task.segment.index);
        let receipt = tokio::task::spawn_blocking(move || {
            let ctx = VerifierContext::default();
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.prove_segment(&ctx, &task.segment)
        })
        .await??;
        self.factory
            .tell(&TaskDoneMsg {
                job_id,
                task_id,
                body: TaskDone::ProveSegment(Arc::new(receipt)),
            })
            .await?;
        Ok(())
    }

    async fn lift(
        &self,
        job_id: ActorID,
        task_id: TaskId,
        task: Arc<LiftTask>,
    ) -> anyhow::Result<()> {
        tracing::info!("Lift: {}", task.receipt.index);
        let segment_idx = task.receipt.index;
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.lift(&task.receipt)
        })
        .await??;
        self.factory
            .tell(&TaskDoneMsg {
                job_id,
                task_id,
                body: TaskDone::Lift(Arc::new(JoinNode {
                    range: (segment_idx..segment_idx + 1).into(),
                    receipt,
                })),
            })
            .await?;
        Ok(())
    }

    async fn join(
        &self,
        job_id: ActorID,
        task_id: TaskId,
        task: Arc<JoinTask>,
    ) -> anyhow::Result<()> {
        let range = task.range;
        tracing::info!("Join: {range:?}");
        let receipt = tokio::task::spawn_blocking(move || {
            let prover = get_prover_server(&ProverOpts::default())?;
            prover.join(&task.receipts[0], &task.receipts[1])
        })
        .await??;
        self.factory
            .tell(&TaskDoneMsg {
                job_id,
                task_id,
                body: TaskDone::Join(Arc::new(JoinNode { range, receipt })),
            })
            .await?;
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
