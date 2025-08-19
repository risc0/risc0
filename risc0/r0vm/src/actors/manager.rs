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

use std::{collections::HashMap, path::PathBuf};

use derive_more::From;
use kameo::prelude::*;
use risc0_zkvm::Receipt;
use tokio::task::JoinSet;

use super::{
    factory::FactoryActor,
    job::JobActor,
    protocol::{
        JobId, JobInfo, JobRequestReply, JobStatus, JobStatusReply, JobStatusRequest, ProofRequest,
        ProofResult, ShrinkWrapRequest, ShrinkWrapResult,
    },
};

#[derive(Clone, From)]
enum InactiveJobEntry {
    Proof(JobInfo<ProofResult>),
    ShrinkWrap(JobInfo<ShrinkWrapResult>),
}

impl From<InactiveJobEntry> for JobStatusReply {
    fn from(e: InactiveJobEntry) -> Self {
        match e {
            InactiveJobEntry::Proof(info) => JobStatusReply::Proof(info),
            InactiveJobEntry::ShrinkWrap(info) => JobStatusReply::ShrinkWrap(info),
        }
    }
}

enum JobEntry {
    Active(ActorRef<JobActor>),
    Inactive(InactiveJobEntry),
}

struct JobDone<ResultT> {
    pub job_id: JobId,
    pub info: JobInfo<ResultT>,
}

#[derive(Actor)]
pub(crate) struct ManagerActor {
    factory: ActorRef<FactoryActor>,
    jobs: HashMap<JobId, JobEntry>,
    join_set: JoinSet<()>,
    storage_root: Option<PathBuf>,
}

impl ManagerActor {
    pub fn new(factory: ActorRef<FactoryActor>, storage_root: Option<PathBuf>) -> Self {
        Self {
            factory,
            jobs: HashMap::new(),
            join_set: JoinSet::new(),
            storage_root,
        }
    }

    async fn job_request<RequestT, ResultT>(
        &mut self,
        request: RequestT,
        actor_ref: ActorRef<ManagerActor>,
        reply_sender: Option<ReplySender<JobRequestReply>>,
    ) -> JobId
    where
        JobActor: Message<RequestT, Reply = DelegatedReply<JobStatusReply>>,
        RequestT: Send + 'static,
        ResultT: HasReceipt + Send + 'static,
        JobInfo<ResultT>: TryFrom<JobStatusReply>,
        <JobInfo<ResultT> as TryFrom<JobStatusReply>>::Error: std::fmt::Debug,
        InactiveJobEntry: From<JobInfo<ResultT>>,
    {
        let job_id = JobId::new_v4();
        let actor_ref = actor_ref.clone();
        let job = kameo::spawn(JobActor::new(job_id, self.factory.clone()));
        self.jobs.insert(job_id, JobEntry::Active(job.clone()));
        self.join_set.spawn(async move {
            let reply = job.ask(request).await.unwrap();
            actor_ref
                .tell(JobDone::<ResultT> {
                    job_id,
                    info: reply.clone().try_into().unwrap(),
                })
                .await
                .unwrap();
            job.wait_for_stop().await;
            if let Some(reply_sender) = reply_sender {
                reply_sender.send(JobRequestReply {
                    job_id,
                    status: reply,
                });
            }
        });
        job_id
    }
}

impl Message<ProofRequest> for ManagerActor {
    type Reply = DelegatedReply<JobRequestReply>;

    async fn handle(
        &mut self,
        msg: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.job_request::<_, ProofResult>(msg, ctx.actor_ref(), reply_sender)
            .await;
        delegated_reply
    }
}

impl Message<ShrinkWrapRequest> for ManagerActor {
    type Reply = DelegatedReply<JobRequestReply>;

    async fn handle(
        &mut self,
        msg: ShrinkWrapRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.job_request::<_, ShrinkWrapResult>(msg, ctx.actor_ref(), reply_sender)
            .await;
        delegated_reply
    }
}

trait HasReceipt {
    fn receipt(&self) -> &Receipt;
}

impl HasReceipt for ProofResult {
    fn receipt(&self) -> &Receipt {
        self.receipt.as_ref()
    }
}

impl HasReceipt for ShrinkWrapResult {
    fn receipt(&self) -> &Receipt {
        self.receipt.as_ref()
    }
}

impl<ResultT> Message<JobDone<ResultT>> for ManagerActor
where
    InactiveJobEntry: From<JobInfo<ResultT>>,
    ResultT: HasReceipt + Send + 'static,
{
    type Reply = ();

    async fn handle(
        &mut self,
        msg: JobDone<ResultT>,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("JobDone: {}", msg.job_id);
        if let JobStatus::Succeeded(ref result) = msg.info.status {
            if let Some(ref storage_root) = self.storage_root {
                let encoded = bincode::serialize(result.receipt()).unwrap();
                let receipts_dir = storage_root.join("receipts");
                std::fs::create_dir_all(&receipts_dir).unwrap();
                let receipt_path = receipts_dir.join(msg.job_id.to_string());
                tokio::fs::write(receipt_path, encoded).await.unwrap();
            }
        }
        self.jobs
            .insert(msg.job_id, JobEntry::Inactive(msg.info.into()));
    }
}

impl Message<JobStatusRequest> for ManagerActor {
    type Reply = JobStatusReply;

    async fn handle(
        &mut self,
        msg: JobStatusRequest,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match self.jobs.get(&msg.job_id) {
            Some(JobEntry::Active(job)) => job
                .ask(JobStatusRequest { job_id: msg.job_id })
                .await
                .unwrap(),
            Some(JobEntry::Inactive(inactive)) => inactive.clone().into(),
            None => JobStatusReply::NotFound,
        }
    }
}
