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
    RemoteActor, RemoteFactoryRequest, RpcDisconnect,
    allocator::{AllocatorRouterActor, ChooseWorker, CpuCores, GpuTokens},
    job::JobActor,
    protocol::{
        GlobalId, JobId, Task, TaskHeader, TaskKind, WorkerId,
        factory::{DropJob, GetTask, SubmitTaskMsg, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
    },
    remote_actor_ask, remote_actor_tell, routing_actor_impl,
};

#[derive(Clone, MultiIndexMap)]
struct TaskRow {
    #[multi_index(hashed_non_unique)]
    job_id: JobId,
    #[multi_index(hashed_unique)]
    global_id: GlobalId,
    #[multi_index(hashed_non_unique)]
    task_kind: TaskKind,
    task: Task,
}

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
    pending_tasks: MultiIndexTaskRowMap,
    active_tasks: HashMap<GlobalId, TaskMsg>,
    reply_senders: HashMap<WorkerId, ReplySender<TaskMsg>>,
    allocator: ActorRef<AllocatorRouterActor>,
}

impl FactoryActor {
    pub fn new(allocator: ActorRef<AllocatorRouterActor>) -> Self {
        Self {
            jobs: HashMap::default(),
            workers: Default::default(),
            pending_tasks: Default::default(),
            active_tasks: HashMap::default(),
            reply_senders: HashMap::default(),
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
        // stop timer
        tracing::info!("Factory: on_stop");
        Ok(())
    }
}

impl Message<DropJob> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: DropJob, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        self.jobs.remove(&msg.job_id);
        self.pending_tasks.remove_by_job_id(&msg.job_id);
    }
}

impl Message<SubmitTaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SubmitTaskMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let global_id = msg.header.global_id;
        let job_id = msg.header.global_id.job_id;
        let task_kind = msg.header.task_kind;

        self.jobs.insert(job_id, msg.job);
        let task = TaskMsg {
            header: msg.header.clone(),
            task: msg.task.clone(),
            // XXX remi
            cores: CpuCores::from(0),
            gpu_tokens: GpuTokens::from(100),
        };

        let workers = self.workers.get_by_task_kind(&msg.header.task_kind);

        if !workers.is_empty() {
            let response = self
                .allocator
                .ask(ChooseWorker {
                    candidates: workers.iter().map(|w| w.worker_id).collect(),
                })
                .await
                .unwrap();

            let worker_id = response.worker_id;
            self.workers.remove_by_worker_id(&worker_id);
            let reply_sender = self.reply_senders.remove(&worker_id).unwrap();
            reply_sender.send(task);
        } else {
            self.pending_tasks.insert(TaskRow {
                job_id,
                global_id,
                task_kind,
                task: msg.task,
            });
        }
    }
}

impl Message<GetTask> for FactoryActor {
    type Reply = DelegatedReply<TaskMsg>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        for &task_kind in msg.kinds.iter() {
            let row = self
                .pending_tasks
                .get_by_task_kind(&task_kind)
                .first()
                .cloned()
                .cloned();
            if let Some(row) = row {
                let task_msg = TaskMsg {
                    header: TaskHeader {
                        global_id: row.global_id,
                        task_kind,
                    },
                    task: row.task.clone(),
                    // XXX remi
                    cores: CpuCores::from(0),
                    gpu_tokens: GpuTokens::from(100),
                };
                self.pending_tasks.remove_by_global_id(&row.global_id);
                self.active_tasks.insert(row.global_id, task_msg.clone());
                return ctx.reply(task_msg);
            }
        }

        let (delegated_reply, reply_sender) = ctx.reply_sender();
        let Some(reply_sender) = reply_sender else {
            tracing::error!("No reply sender for GetTask!!");
            return delegated_reply;
        };

        self.reply_senders.insert(msg.worker_id, reply_sender);

        for task_kind in msg.kinds {
            let worker = WorkerRow {
                task_kind,
                worker_id: msg.worker_id,
            };
            self.workers.insert(worker);
        }

        delegated_reply
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

#[derive(Actor)]
pub(crate) enum FactoryRouterActor {
    Local(ActorRef<FactoryActor>),
    Remote(ActorRef<RemoteFactoryActor>),
}

impl FactoryRouterActor {
    pub async fn new(
        addr: &Option<SocketAddr>,
        local: &Option<ActorRef<FactoryActor>>,
    ) -> Result<ActorRef<Self>, Box<dyn StdError>> {
        if let Some(addr) = addr {
            let remote = kameo::spawn(RemoteFactoryActor::new(*addr).await?);
            Ok(kameo::spawn(Self::Remote(remote)))
        } else {
            Ok(kameo::spawn(Self::Local(
                local.as_ref().ok_or("no factory configured")?.clone(),
            )))
        }
    }
}

routing_actor_impl!(FactoryRouterActor, GetTask, DelegatedReply<TaskMsg>);
routing_actor_impl!(FactoryRouterActor, TaskUpdateMsg, ());
routing_actor_impl!(FactoryRouterActor, TaskDoneMsg, ());

pub type RemoteFactoryActor = RemoteActor<FactoryActor>;

remote_actor_ask!(
    RemoteActor<FactoryActor>,
    GetTask,
    TaskMsg,
    RemoteFactoryRequest
);

remote_actor_tell!(
    RemoteActor<FactoryActor>,
    TaskUpdateMsg,
    RemoteFactoryRequest
);
remote_actor_tell!(RemoteActor<FactoryActor>, TaskDoneMsg, RemoteFactoryRequest);
