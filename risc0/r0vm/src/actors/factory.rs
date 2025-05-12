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

use std::{
    collections::{HashMap, VecDeque},
    net::SocketAddr,
    ops::ControlFlow,
};

use kameo::{error::Infallible, prelude::*};
use multi_index_map::MultiIndexMap;
use tokio::{io::AsyncWriteExt as _, net::TcpStream};

use super::{
    job::JobActor,
    protocol::{
        factory::{GetTask, SubmitTaskMsg, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
        GlobalId, TaskKind,
    },
    RemoteRequest,
};

#[derive(MultiIndexMap)]
struct Worker {
    #[multi_index(hashed_non_unique)]
    task_kind: TaskKind,
    #[multi_index(hashed_non_unique)]
    actor_id: ActorID,
    actor_ref: ActorRef<WorkerProxyActor>,
}

pub(crate) struct FactoryActor {
    jobs: HashMap<ActorID, ActorRef<JobActor>>,
    workers: MultiIndexWorkerMap,
    pending_tasks: HashMap<TaskKind, VecDeque<TaskMsg>>,
    active_tasks: HashMap<GlobalId, TaskMsg>,
}

impl FactoryActor {
    pub fn new() -> Self {
        Self {
            jobs: HashMap::default(),
            workers: MultiIndexWorkerMap::default(),
            pending_tasks: HashMap::default(),
            active_tasks: HashMap::default(),
        }
    }

    fn pending_tasks(&mut self, task_kind: TaskKind) -> &mut VecDeque<TaskMsg> {
        self.pending_tasks.entry(task_kind).or_default()
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

impl Message<TaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskMsg, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        let workers = self.workers.get_by_task_kind(&msg.header.task_kind);
        if let Some(worker) = workers.first() {
            self.active_tasks.insert(msg.header.global_id, msg.clone());
            worker.actor_ref.tell(msg).await.unwrap();
        } else {
            self.pending_tasks(msg.header.task_kind).push_back(msg);
        }
    }
}

impl Message<SubmitTaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SubmitTaskMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.jobs.insert(msg.job.id(), msg.job);
        let task = TaskMsg {
            header: msg.header.clone(),
            task: msg.task,
        };

        let workers = self.workers.get_by_task_kind(&msg.header.task_kind);
        if let Some(worker) = workers.first() {
            self.active_tasks
                .insert(task.header.global_id, task.clone());
            worker.actor_ref.tell(task).await.unwrap();
        } else {
            self.pending_tasks(task.header.task_kind).push_back(task);
        }
    }
}

impl Message<GetTask> for FactoryActor {
    type Reply = DelegatedReply<TaskMsg>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        // tracing::info!("GetTask");
        for kind in msg.kinds.iter() {
            let pending_tasks = self.pending_tasks(*kind);
            if !pending_tasks.is_empty() {
                // tracing::info!("pending: {kind:?}");
                let task = pending_tasks.pop_front().unwrap();
                self.active_tasks
                    .insert(task.header.global_id, task.clone());
                return ctx.reply(task);
            }
        }

        let (delegated_reply, reply_sender) = ctx.reply_sender();
        let worker_ref = spawn_link(&ctx.actor_ref(), WorkerProxyActor { reply_sender }).await;

        // tracing::info!("new worker: {:?}", msg.kinds);
        for task_kind in msg.kinds {
            let worker = Worker {
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
        let job = self.jobs.get(&msg.header.global_id.job_id).unwrap();
        ctx.forward(job, msg).await;
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
        let job = self.jobs.get(&msg.header.global_id.job_id).unwrap();
        ctx.forward(job, msg).await;
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

// pub(crate) struct VirtualReply<R> {
//     phantom: PhantomData<R>,
// }

// impl<R> VirtualReply<R> {
//     pub(crate) fn new() -> Self {
//         Self {
//             phantom: PhantomData,
//         }
//     }
// }

// impl<R> Reply for VirtualReply<R>
// where
//     R: Reply,
// {
//     type Ok = R::Ok;
//     type Error = R::Error;
//     type Value = R::Value;

//     fn to_result(self) -> Result<Self::Ok, Self::Error> {
//         unimplemented!()
//     }

//     fn into_any_err(self) -> Option<Box<dyn ReplyError>> {
//         None
//     }

//     fn into_value(self) -> Self::Value {
//         unimplemented!()
//     }
// }
