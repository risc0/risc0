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

use std::{error::Error as StdError, time::Duration};

use kameo::{error::RegistryError, prelude::*, remote::dial_opts::DialOpts};
use risc0_zkvm::{ExecutorEnv, ExecutorImpl, NullSegmentRef};
use tokio::{task::JoinSet, time::sleep};

use crate::Cli;

use super::{
    manager::TaskManagerActor,
    protocol::{ExecuteTask, ExecuteTaskRequest, SegmentReady, SessionDone, SessionWrapper},
};

pub(crate) async fn main(_args: Cli) -> Result<(), Box<dyn StdError>> {
    ActorSwarm::bootstrap()?
        .dial(
            DialOpts::unknown_peer_id()
                .address("/ip4/127.0.0.1/udp/9000/quic-v1".parse()?)
                .build(),
        )
        .await?;

    let task_mgr = retry_lookup().await?.unwrap();

    let mut worker_tasks = JoinSet::new();

    worker_tasks.spawn(run_executor(task_mgr.clone()));
    worker_tasks.spawn(run_prover(task_mgr.clone()));

    worker_tasks.join_all().await;

    Ok(())
}

async fn run_executor(task_mgr: RemoteActorRef<TaskManagerActor>) -> anyhow::Result<()> {
    let task = task_mgr.ask(&ExecuteTaskRequest).await?;
    tracing::info!("ELF: {} bytes", task.binary.len());

    let relay = RelayActor::spawn(task_mgr.clone());
    let executor = ExecutorActor::spawn_in_thread(relay.clone());
    let session = executor.ask(task).await?;

    relay.stop_gracefully().await?;
    relay.wait_for_stop().await;

    task_mgr.tell(&SessionDone(session)).await?;

    Ok(())
}

async fn run_prover(_task_mgr: RemoteActorRef<TaskManagerActor>) -> anyhow::Result<()> {
    // let task = task_mgr.ask(&ProveSegmentTaskRequest).await?;

    Ok(())
}

async fn retry_lookup() -> Result<Option<RemoteActorRef<TaskManagerActor>>, RegistryError> {
    for _ in 0..5 {
        if let Some(actor) = RemoteActorRef::<TaskManagerActor>::lookup("task_mgr").await? {
            return Ok(Some(actor));
        }
        sleep(Duration::from_millis(100)).await;
    }
    Ok(None)
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

impl Message<ExecuteTask> for ExecutorActor {
    type Reply = anyhow::Result<SessionWrapper>;

    async fn handle(
        &mut self,
        task: ExecuteTask,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let env = ExecutorEnv::builder().write_slice(&task.input).build()?;
        let mut exec = ExecutorImpl::from_elf(env, &task.binary)?;
        let session = exec.run_with_callback(|segment| {
            self.relay.tell(SegmentReady(segment)).blocking_send()?;
            Ok(Box::new(NullSegmentRef))
        })?;

        let session = SessionWrapper {
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
    task_mgr: RemoteActorRef<TaskManagerActor>,
}

impl RelayActor {
    pub fn spawn(task_mgr: RemoteActorRef<TaskManagerActor>) -> ActorRef<Self> {
        spawn(Self { task_mgr })
    }
}

impl Message<SegmentReady> for RelayActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SegmentReady,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.task_mgr.tell(&msg).await.unwrap();
    }
}
