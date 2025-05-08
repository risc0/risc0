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

use std::{
    collections::{BTreeMap, HashMap, VecDeque},
    ops::ControlFlow,
};

use kameo::{error::Infallible, prelude::*};
use multi_index_map::MultiIndexMap;

use super::{
    manager::TaskManagerActor,
    protocol::{
        factory::{GetTask, SubmitTaskMsg, TaskDoneMsg, TaskStatusMsg},
        worker::TaskMsg,
        TaskId, TaskKind,
    },
};

#[derive(MultiIndexMap)]
struct Worker {
    #[multi_index(hashed_non_unique)]
    task_kind: TaskKind,
    #[multi_index(hashed_non_unique)]
    actor_id: ActorID,
    actor_ref: ActorRef<WorkerProxyActor>,
}

#[derive(RemoteActor)]
pub(crate) struct FactoryActor {
    task_mgrs: HashMap<ActorID, ActorRef<TaskManagerActor>>,
    workers: MultiIndexWorkerMap,
    pending_tasks: HashMap<TaskKind, VecDeque<TaskMsg>>,
    active_tasks: HashMap<TaskId, TaskMsg>,
}

impl FactoryActor {
    pub fn new() -> Self {
        Self {
            task_mgrs: HashMap::default(),
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

    async fn on_start(&mut self, actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        // start timer
        Ok(())
    }

    async fn on_stop(
        &mut self,
        actor_ref: WeakActorRef<Self>,
        reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        // stop timer
        Ok(())
    }

    async fn on_link_died(
        &mut self,
        actor_ref: WeakActorRef<Self>,
        id: ActorID,
        reason: ActorStopReason,
    ) -> Result<ControlFlow<ActorStopReason>, Self::Error> {
        self.workers.remove_by_actor_id(&id);
        Ok(ControlFlow::Continue(()))
    }
}

impl Message<TaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskMsg, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        let workers = self.workers.get_by_task_kind(&msg.task_kind);
        if let Some(worker) = workers.first() {
            self.active_tasks.insert(msg.task_id, msg.clone());
            worker.actor_ref.tell(msg).await;
        } else {
            self.pending_tasks(msg.task_kind).push_back(msg);
        }
    }
}

impl Message<SubmitTaskMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: SubmitTaskMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let job_id = msg.task_mgr.id();
        self.task_mgrs.insert(job_id, msg.task_mgr);
        let task = TaskMsg {
            job_id,
            task_id: msg.task_id,
            task_kind: msg.task_kind,
            task: msg.task,
        };

        let workers = self.workers.get_by_task_kind(&msg.task_kind);
        if let Some(worker) = workers.first() {
            self.active_tasks.insert(task.task_id, task.clone());
            worker.actor_ref.tell(task).await;
        } else {
            self.pending_tasks(task.task_kind).push_back(task);
        }
    }
}

#[remote_message("ce409cb3-b36f-4a08-b067-3cfc1027a873")]
impl Message<GetTask> for FactoryActor {
    type Reply = DelegatedReply<TaskMsg>;

    async fn handle(&mut self, msg: GetTask, ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        tracing::info!("GetTask");
        for kind in msg.kinds.iter() {
            let pending_tasks = self.pending_tasks(*kind);
            if !pending_tasks.is_empty() {
                tracing::info!("pending: {kind:?}");
                let task = pending_tasks.pop_front().unwrap();
                self.active_tasks.insert(task.task_id, task.clone());
                return ctx.reply(task);
            }
        }

        let (delegated_reply, reply_sender) = ctx.reply_sender();
        let worker_ref = spawn_link(&ctx.actor_ref(), WorkerProxyActor { reply_sender }).await;

        for task_kind in msg.kinds {
            tracing::info!("new worker: {task_kind:?}");
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

#[remote_message("cb686d44-b971-401c-acc6-9eef9c0fff3f")]
impl Message<TaskStatusMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskStatusMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        // refresh active worker
        let task_mgr = self.task_mgrs.get(&msg.job_id).unwrap();
        ctx.forward(task_mgr, msg).await;
    }
}

#[remote_message("3b6df2c3-fdd4-4487-b93a-c7c5c0f005ae")]
impl Message<TaskDoneMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        self.active_tasks.remove(&msg.task_id);
        let task_mgr = self.task_mgrs.get(&msg.job_id).unwrap();
        ctx.forward(task_mgr, msg).await;
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
        ctx.actor_ref().stop_gracefully().await;
    }
}
