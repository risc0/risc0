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

use std::{collections::HashMap, net::SocketAddr, ops::ControlFlow};

use kameo::{error::Infallible, prelude::*};
use multi_index_map::MultiIndexMap;
use tokio::{io::AsyncWriteExt as _, net::TcpStream};

use super::{
    job::JobActor,
    protocol::{
        factory::{DropJob, GetTask, SubmitTaskMsg, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
        GlobalId, JobId, Task, TaskHeader, TaskKind,
    },
    RemoteRequest,
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
    actor_id: ActorID,
    actor_ref: ActorRef<WorkerProxyActor>,
}

pub(crate) struct FactoryActor {
    jobs: HashMap<JobId, ActorRef<JobActor>>,
    workers: MultiIndexWorkerRowMap,
    pending_tasks: MultiIndexTaskRowMap,
    active_tasks: HashMap<GlobalId, TaskMsg>,
}

impl FactoryActor {
    pub fn new() -> Self {
        Self {
            jobs: HashMap::default(),
            workers: Default::default(),
            pending_tasks: Default::default(),
            active_tasks: HashMap::default(),
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

    async fn on_link_died(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        id: ActorID,
        _reason: ActorStopReason,
    ) -> Result<ControlFlow<ActorStopReason>, Self::Error> {
        self.workers.remove_by_actor_id(&id);
        Ok(ControlFlow::Continue(()))
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
        self.jobs.insert(msg.job_id, msg.job);
        let task = TaskMsg {
            header: msg.header.clone(),
            task: msg.task.clone(),
        };

        let workers = self.workers.get_by_task_kind(&msg.header.task_kind);
        if let Some(worker) = workers.first() {
            self.active_tasks
                .insert(task.header.global_id, task.clone());
            worker.actor_ref.tell(task).await.unwrap();
        } else {
            self.pending_tasks.insert(TaskRow {
                job_id: msg.header.global_id.job_id,
                global_id: msg.header.global_id,
                task_kind: msg.header.task_kind,
                task: msg.task,
            });
        }
    }
}

impl Message<GetTask> for FactoryActor {
    type Reply = DelegatedReply<TaskMsg>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        // tracing::info!("GetTask");
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
                };
                self.pending_tasks.remove_by_global_id(&row.global_id);
                self.active_tasks.insert(row.global_id, task_msg.clone());
                return ctx.reply(task_msg);
            }
        }

        let (delegated_reply, reply_sender) = ctx.reply_sender();
        let worker_ref = spawn_link(&ctx.actor_ref(), WorkerProxyActor { reply_sender }).await;

        // tracing::info!("new worker: {:?}", msg.kinds);
        for task_kind in msg.kinds {
            let worker = WorkerRow {
                task_kind,
                actor_id: worker_ref.id(),
                actor_ref: worker_ref.clone(),
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

#[derive(Actor)]
struct WorkerProxyActor {
    reply_sender: Option<ReplySender<TaskMsg>>,
}

impl Message<TaskMsg> for WorkerProxyActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskMsg, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        self.reply_sender.take().unwrap().send(msg);
        ctx.actor_ref().stop_gracefully().await.unwrap();
    }
}

#[derive(Actor)]
pub(crate) enum FactoryRouterActor {
    Local(ActorRef<FactoryActor>),
    Remote(ActorRef<RemoteFactoryActor>),
}

impl Message<GetTask> for FactoryRouterActor {
    type Reply = ForwardedReply<GetTask, DelegatedReply<TaskMsg>>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        match self {
            FactoryRouterActor::Local(actor_ref) => ctx.forward(actor_ref, msg).await,
            FactoryRouterActor::Remote(actor_ref) => ctx.forward(actor_ref, msg).await,
        }
    }
}

impl Message<TaskUpdateMsg> for FactoryRouterActor {
    type Reply = ForwardedReply<TaskUpdateMsg, ()>;

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self {
            FactoryRouterActor::Local(actor_ref) => ctx.forward(actor_ref, msg).await,
            FactoryRouterActor::Remote(actor_ref) => ctx.forward(actor_ref, msg).await,
        }
    }
}

impl Message<TaskDoneMsg> for FactoryRouterActor {
    type Reply = ForwardedReply<TaskDoneMsg, ()>;

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self {
            FactoryRouterActor::Local(actor_ref) => ctx.forward(actor_ref, msg).await,
            FactoryRouterActor::Remote(actor_ref) => ctx.forward(actor_ref, msg).await,
        }
    }
}

pub(crate) struct RemoteFactoryActor {
    tcp: TcpStream,
}

impl RemoteFactoryActor {
    pub(crate) async fn new(addr: SocketAddr) -> anyhow::Result<Self> {
        let tcp = TcpStream::connect(addr).await?;
        Ok(Self { tcp })
    }
}

impl Actor for RemoteFactoryActor {
    type Error = anyhow::Error;

    async fn on_start(&mut self, _actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        _reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        self.tcp.shutdown().await?;
        Ok(())
    }
}

impl Message<GetTask> for RemoteFactoryActor {
    type Reply = DelegatedReply<TaskMsg>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        let msg = RemoteRequest::GetTask(msg);
        super::send(&mut self.tcp, msg).await.unwrap();
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        let reply: TaskMsg = super::recv(&mut self.tcp).await.unwrap().unwrap();
        reply_sender.unwrap().send(reply);
        delegated_reply
    }
}

impl Message<TaskUpdateMsg> for RemoteFactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let msg = RemoteRequest::TaskUpdate(msg);
        super::send(&mut self.tcp, msg).await.unwrap();
    }
}

impl Message<TaskDoneMsg> for RemoteFactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let msg = RemoteRequest::TaskDone(msg);
        super::send(&mut self.tcp, msg).await.unwrap();
    }
}
