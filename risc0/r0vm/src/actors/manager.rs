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

use kameo::prelude::*;
use tokio::task::JoinSet;

use super::{
    factory::FactoryActor,
    job::JobActor,
    protocol::{
        CreateJobReply, CreateJobRequest, JobId, JobInfo, JobStatus, JobStatusReply,
        JobStatusRequest, ProofRequest,
    },
};

enum JobEntry {
    Active(ActorRef<JobActor>),
    Inactive(JobInfo),
}

struct JobDone {
    pub job_id: JobId,
    pub info: JobInfo,
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

    async fn proof_request(
        &mut self,
        request: ProofRequest,
        actor_ref: ActorRef<ManagerActor>,
        reply_sender: Option<ReplySender<JobStatusReply>>,
    ) -> JobId {
        let job_id = JobId::new_v4();
        let actor_ref = actor_ref.clone();
        let job = kameo::spawn(JobActor::new(job_id, self.factory.clone()));
        self.jobs.insert(job_id, JobEntry::Active(job.clone()));
        self.join_set.spawn(async move {
            let reply = job.ask(request).await.unwrap();
            actor_ref
                .tell(JobDone {
                    job_id,
                    info: reply.info.clone().unwrap(),
                })
                .await
                .unwrap();
            job.wait_for_stop().await;
            if let Some(reply_sender) = reply_sender {
                reply_sender.send(JobStatusReply { info: reply.info });
            }
        });
        job_id
    }
}

impl Message<ProofRequest> for ManagerActor {
    type Reply = DelegatedReply<JobStatusReply>;

    async fn handle(
        &mut self,
        msg: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.proof_request(msg, ctx.actor_ref(), reply_sender).await;
        delegated_reply
    }
}

impl Message<JobDone> for ManagerActor {
    type Reply = ();

    async fn handle(&mut self, msg: JobDone, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        tracing::info!("JobDone: {}", msg.job_id);
        if let JobStatus::Succeeded(ref result) = msg.info.status {
            if let Some(ref storage_root) = self.storage_root {
                let encoded = bincode::serialize(result.receipt.as_ref()).unwrap();
                let receipts_dir = storage_root.join("receipts");
                std::fs::create_dir_all(&receipts_dir).unwrap();
                let receipt_path = receipts_dir.join(msg.job_id.to_string());
                tokio::fs::write(receipt_path, encoded).await.unwrap();
            }
        }
        self.jobs.insert(msg.job_id, JobEntry::Inactive(msg.info));
    }
}

impl Message<CreateJobRequest> for ManagerActor {
    type Reply = CreateJobReply;

    async fn handle(
        &mut self,
        msg: CreateJobRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let job_id = self.proof_request(msg.request, ctx.actor_ref(), None).await;
        CreateJobReply { job_id }
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
            Some(job) => match job {
                JobEntry::Active(job) => job
                    .ask(JobStatusRequest { job_id: msg.job_id })
                    .await
                    .unwrap(),
                JobEntry::Inactive(info) => JobStatusReply {
                    info: Some(info.clone()),
                },
            },
            None => JobStatusReply { info: None },
        }
    }
}
