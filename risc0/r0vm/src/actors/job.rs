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

mod execute_only;
mod proof;
mod shrink_wrap;
mod tracer;

use derive_more::From;
use kameo::{error::Infallible, prelude::*};
use tokio::task::JoinSet;

use super::{
    TaskDoneMsg, TaskUpdateMsg,
    factory::FactoryActor,
    protocol::{JobId, JobStatusReply, JobStatusRequest, ProofRequest, ShrinkWrapRequest},
};

pub(crate) struct JobActor {
    job_id: JobId,
    factory: ActorRef<FactoryActor>,
    join_set: JoinSet<()>,
    inner: Option<InnerJobActor>,
}

#[derive(From)]
enum InnerJobActor {
    Proof(ActorRef<proof::JobActor>),
    ShrinkWrap(ActorRef<shrink_wrap::JobActor>),
    ExecuteOnly(ActorRef<execute_only::JobActor>),
}

impl Actor for JobActor {
    type Error = Infallible;

    async fn on_start(&mut self, _actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        Ok(())
    }
}

trait JobActorNew {
    fn new(
        job_id: JobId,
        parent_ref: WeakActorRef<JobActor>,
        factory: ActorRef<FactoryActor>,
    ) -> Self;
}

impl JobActor {
    pub fn new(job_id: JobId, factory: ActorRef<FactoryActor>) -> Self {
        Self {
            job_id,
            factory,
            join_set: JoinSet::new(),
            inner: None,
        }
    }

    fn request<RequestT, ActorT>(
        &mut self,
        request: RequestT,
        self_ref: ActorRef<Self>,
        reply_sender: Option<ReplySender<JobStatusReply>>,
    ) where
        InnerJobActor: From<ActorRef<ActorT>>,
        ActorT: Message<RequestT, Reply = DelegatedReply<JobStatusReply>> + JobActorNew,
        RequestT: Send + 'static,
    {
        let job = kameo::spawn(ActorT::new(
            self.job_id,
            self_ref.downgrade(),
            self.factory.clone(),
        ));
        self.inner = Some(job.clone().into());

        self.join_set.spawn(async move {
            let reply = job.ask(request).await.unwrap();
            job.wait_for_stop().await;
            if let Some(reply_sender) = reply_sender {
                reply_sender.send(reply);
            }
            self_ref.stop_gracefully().await.unwrap();
        });
    }
}

impl Message<ProofRequest> for JobActor {
    type Reply = DelegatedReply<JobStatusReply>;

    async fn handle(
        &mut self,
        request: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        if request.execute_only {
            self.request::<_, execute_only::JobActor>(request, ctx.actor_ref(), reply_sender);
        } else {
            self.request::<_, proof::JobActor>(request, ctx.actor_ref(), reply_sender);
        }
        delegated_reply
    }
}

impl Message<ShrinkWrapRequest> for JobActor {
    type Reply = DelegatedReply<JobStatusReply>;

    async fn handle(
        &mut self,
        request: ShrinkWrapRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.request::<_, shrink_wrap::JobActor>(request, ctx.actor_ref(), reply_sender);
        delegated_reply
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(
        &mut self,
        msg: JobStatusRequest,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self.inner.as_mut().unwrap() {
            InnerJobActor::Proof(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ShrinkWrap(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ExecuteOnly(job) => job.ask(msg).await.unwrap(),
        }
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self.inner.as_mut().unwrap() {
            InnerJobActor::Proof(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ShrinkWrap(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ExecuteOnly(job) => job.ask(msg).await.unwrap(),
        }
    }
}

impl Message<TaskDoneMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self.inner.as_mut().unwrap() {
            InnerJobActor::Proof(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ShrinkWrap(job) => job.ask(msg).await.unwrap(),
            InnerJobActor::ExecuteOnly(job) => job.ask(msg).await.unwrap(),
        }
    }
}
