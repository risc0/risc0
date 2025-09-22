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

use std::collections::HashMap;
use std::error::Error as StdError;
use std::net::SocketAddr;

use kameo::{error::Infallible, prelude::*};
use multi_index_map::MultiIndexMap;

use super::{
    RemoteActor, RemoteFactoryRequest, RpcDisconnect, RpcMessageId, WorkerRouterActor,
    allocator::{AllocatorRouterActor, ChooseWorker, CpuCores, GpuTokens},
    job::JobActor,
    protocol::{
        GlobalId, JobId, TaskKind, WorkerId,
        factory::{DropJob, GetTasks, SubmitTaskMsg, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
    },
    remote_actor_tell, routing_actor_impl,
};

#[derive(MultiIndexMap)]
struct WorkerRow {
    #[multi_index(hashed_non_unique)]
    task_kind: TaskKind,
    #[multi_index(hashed_non_unique)]
    worker_id: WorkerId,
}

pub(crate) struct FactoryActor {
    jobs: HashMap<JobId, ActorRef<JobActor>>,
    workers: MultiIndexWorkerRowMap,
    pending_tasks: Vec<SubmitTaskMsg>,
    active_tasks: HashMap<GlobalId, TaskMsg>,
    worker_actors: HashMap<WorkerId, ActorRef<WorkerRouterActor>>,
    allocator: ActorRef<AllocatorRouterActor>,
    require_gpu: bool,
}

impl FactoryActor {
    pub fn new(allocator: ActorRef<AllocatorRouterActor>, require_gpu: bool) -> Self {
        Self {
            jobs: HashMap::default(),
            workers: Default::default(),
            pending_tasks: Default::default(),
            active_tasks: HashMap::default(),
            worker_actors: HashMap::default(),
            require_gpu,
            allocator,
        }
    }
}

impl Actor for FactoryActor {
    type Error = Infallible;

    async fn on_start(&mut self, _actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        // start timer
        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        _reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        for worker in self.worker_actors.values() {
            let _ = worker.stop_gracefully().await;
        }

        // stop timer
        tracing::info!("Factory: on_stop");
        Ok(())
    }
}

impl FactoryActor {
    async fn maybe_schedule_tasks(&mut self) {
        for msg in std::mem::take(&mut self.pending_tasks) {
            let workers = self.workers.get_by_task_kind(&msg.header.task_kind);

            if !workers.is_empty() {
                tracing::info!("Factory: scheduling job {:?}", &msg.header);
                let job_id = msg.header.global_id.job_id;

                self.jobs.insert(job_id, msg.job);

                let gpu_tokens = match msg.header.task_kind {
                    TaskKind::Execute => GpuTokens::from(0),
                    _ => {
                        if self.require_gpu {
                            GpuTokens::from(100)
                        } else {
                            GpuTokens::from(0)
                        }
                    }
                };

                let task = TaskMsg {
                    header: msg.header.clone(),
                    task: msg.task.clone(),
                    // XXX remi
                    cores: CpuCores::from(0),
                    gpu_tokens,
                };

                let response = self
                    .allocator
                    .ask(ChooseWorker {
                        candidates: workers.iter().map(|w| w.worker_id).collect(),
                        task_id: msg.header.global_id,
                        description: format!("{:?}", &msg.header.task_kind),
                    })
                    .await
                    .unwrap();

                let worker_id = response.worker_id;
                let worker_actor = self.worker_actors.get(&worker_id).unwrap();
                tracing::info!(
                    "Factory: sending job {:?} to worker {worker_id:?}",
                    &msg.header
                );
                worker_actor.tell(task).await.unwrap();
            } else {
                self.pending_tasks.push(msg);
            }
        }
    }
}

impl Message<DropJob> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: DropJob, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        self.jobs.remove(&msg.job_id);
        self.pending_tasks
            .retain(|t| t.header.global_id.job_id != msg.job_id);
    }
}

impl Message<SubmitTaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SubmitTaskMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.pending_tasks.push(msg);

        self.maybe_schedule_tasks().await;
    }
}

impl Message<GetTasks> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: GetTasks, _ctx: &mut Context<Self, Self::Reply>) {
        self.worker_actors
            .insert(msg.worker_id, msg.worker.unwrap());

        for task_kind in msg.kinds {
            let worker = WorkerRow {
                task_kind,
                worker_id: msg.worker_id,
            };
            self.workers.insert(worker);
        }

        self.maybe_schedule_tasks().await;
    }
}

impl Message<TaskUpdateMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        // refresh active worker
        if let Some(job) = self.jobs.get(&msg.header.global_id.job_id) {
            ctx.forward(job, msg).await;
        }
    }
}

impl Message<TaskDoneMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.active_tasks.remove(&msg.header.global_id);
        if let Some(job) = self.jobs.get(&msg.header.global_id.job_id) {
            ctx.forward(job, msg).await;
        }
    }
}

impl Message<RpcDisconnect> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, _msg: RpcDisconnect, _ctx: &mut Context<Self, Self::Reply>) {
        // nothing to do
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

#[derive(Actor)]
pub(crate) enum FactoryRouterActor {
    Local(ActorRef<FactoryActor>),
    Remote(ActorRef<RemoteFactoryActor>),
}

impl FactoryRouterActor {
    pub async fn new<RemoteMsgT, FutT>(
        addr: &Option<SocketAddr>,
        local: &Option<ActorRef<FactoryActor>>,
        remote_msg_callback: impl FnMut(Option<RemoteMsgT>, Option<RpcMessageId>, SocketAddr) -> FutT
        + Send
        + 'static,
    ) -> Result<ActorRef<Self>, Box<dyn StdError>>
    where
        RemoteMsgT: serde::de::DeserializeOwned,
        FutT: Future<Output = ()> + Send,
    {
        if let Some(addr) = addr {
            let remote = kameo::spawn(
                RemoteFactoryActor::new_with_remote_msg_callback(*addr, remote_msg_callback)
                    .await?,
            );
            Ok(kameo::spawn(Self::Remote(remote)))
        } else {
            Ok(kameo::spawn(Self::Local(
                local.as_ref().ok_or("no factory configured")?.clone(),
            )))
        }
    }
}

routing_actor_impl!(FactoryRouterActor, GetTasks, ());
routing_actor_impl!(FactoryRouterActor, TaskUpdateMsg, ());
routing_actor_impl!(FactoryRouterActor, TaskDoneMsg, ());

pub type RemoteFactoryActor = RemoteActor<FactoryActor>;

remote_actor_tell!(RemoteActor<FactoryActor>, GetTasks, RemoteFactoryRequest);

remote_actor_tell!(
    RemoteActor<FactoryActor>,
    TaskUpdateMsg,
    RemoteFactoryRequest
);
remote_actor_tell!(RemoteActor<FactoryActor>, TaskDoneMsg, RemoteFactoryRequest);
