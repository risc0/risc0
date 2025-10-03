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

use std::{collections::HashMap, path::PathBuf, time::Duration};

use derive_more::From;
use risc0_zkvm::{Journal, Receipt, rpc::JobRequest};
use tokio::task::JoinSet;
use uuid::Uuid;

use super::{
    actor::{self, Actor, ActorRef, Context, Message, ReplySender},
    error::{Error, Result},
    factory::FactoryActor,
    job::JobActor,
    protocol::{
        CreateJobReply, CreateJobRequest, JobId, JobInfo, JobRequestReply, JobStatus,
        JobStatusReply, JobStatusRequest, ProofRequest, ProofResult, ShrinkWrapRequest,
        ShrinkWrapResult,
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

async fn job_request_task<RequestT, ResultT>(
    request: RequestT,
    reply_sender: Option<ReplySender<JobRequestReply>>,
    job_id: Uuid,
    self_ref: ActorRef<ManagerActor>,
    job: ActorRef<JobActor>,
) where
    JobActor: Message<RequestT, Reply = Result<JobStatusReply>>,
    JobInfo<ResultT>: TryFrom<JobStatusReply>,
    JobStatusReply: From<JobInfo<ResultT>>,
    ManagerActor: Message<JobDone<ResultT>>,
    RequestT: Send + 'static,
    ResultT: Send + 'static,
{
    // Send the request to the job and wait for it to finish.
    // If it fails, we change the error into a failed job status.
    let res = job.ask(request).await.map_err(Error::from).flatten();
    let reply = res.unwrap_or_else(|error| {
        JobInfo {
            status: JobStatus::<ResultT>::Failed(error.into()),
            // XXX remi: This is lame, we should somehow avoid this.
            elapsed_time: Duration::MAX,
        }
        .into()
    });

    // We should always be getting some job status which matches our request type, but if not, just
    // ignore it.
    if let Ok(info) = reply.clone().try_into() {
        // If the manager it shutting down for some reason, don't worry about delivering this
        // message.
        let _ = self_ref.tell(JobDone::<ResultT> { job_id, info }).await;
    }

    // After the job sends its reply it should be done, but lets wait for it to clean up resources.
    job.wait_for_stop().await;

    // If the job requester is waiting for a response send it to them
    if let Some(reply_sender) = reply_sender {
        reply_sender.send(JobRequestReply {
            job_id,
            status: reply,
        });
    }
}

pub(crate) struct ManagerActor {
    factory: ActorRef<FactoryActor>,
    jobs: HashMap<JobId, JobEntry>,
    join_set: JoinSet<()>,
    storage_root: Option<PathBuf>,
}

impl Actor for ManagerActor {}

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
        self_ref: ActorRef<Self>,
        reply_sender: Option<ReplySender<JobRequestReply>>,
    ) -> JobId
    where
        <JobInfo<ResultT> as TryFrom<JobStatusReply>>::Error: Send,
        JobActor: Message<RequestT, Reply = Result<JobStatusReply>>,
        JobInfo<ResultT>: TryFrom<JobStatusReply>,
        JobStatusReply: From<JobInfo<ResultT>>,
        ManagerActor: Message<JobDone<ResultT>>,
        RequestT: Send + 'static,
        ResultT: Send + 'static,
    {
        let job_id = JobId::new_v4();
        let self_ref = self_ref.clone();
        let job = actor::spawn(JobActor::new(job_id, self.factory.clone()));
        self.jobs.insert(job_id, JobEntry::Active(job.clone()));
        self.join_set.spawn(async move {
            job_request_task(request, reply_sender, job_id, self_ref, job).await;
        });
        job_id
    }

    async fn write_receipt(&self, job_id: &Uuid, receipt: &Receipt) -> Result<()> {
        let Some(storage_root) = &self.storage_root else {
            return Ok(());
        };

        let encoded = bincode::serialize(receipt)?;
        let receipts_dir = storage_root.join("receipts");
        std::fs::create_dir_all(&receipts_dir)?;
        let receipt_path = receipts_dir.join(job_id.to_string());
        tokio::fs::write(receipt_path, encoded).await?;

        Ok(())
    }

    async fn write_journal(&self, job_id: &Uuid, journal: &Journal) -> Result<()> {
        let Some(storage_root) = &self.storage_root else {
            return Ok(());
        };

        let encoded = bincode::serialize(journal)?;
        let journal_dir = storage_root.join("journals");
        std::fs::create_dir_all(&journal_dir)?;
        let journal_path = journal_dir.join(job_id.to_string());
        tokio::fs::write(journal_path, encoded).await?;

        Ok(())
    }
}

impl Message<CreateJobRequest> for ManagerActor {
    type Reply = CreateJobReply;

    async fn handle(&mut self, msg: CreateJobRequest, ctx: &mut Context<Self, Self::Reply>) {
        let job_id = match msg.request {
            JobRequest::Proof(request) => {
                self.job_request::<_, ProofResult>(request, ctx.actor_ref(), None)
                    .await
            }
            JobRequest::ShrinkWrap(request) => {
                self.job_request::<_, ShrinkWrapResult>(request, ctx.actor_ref(), None)
                    .await
            }
        };
        ctx.reply(CreateJobReply { job_id })
    }
}

impl Message<ProofRequest> for ManagerActor {
    type Reply = JobRequestReply;

    async fn handle(&mut self, msg: ProofRequest, ctx: &mut Context<Self, Self::Reply>) {
        let reply_sender = ctx.reply_sender();
        self.job_request::<_, ProofResult>(msg, ctx.actor_ref(), reply_sender)
            .await;
    }
}

impl Message<ShrinkWrapRequest> for ManagerActor {
    type Reply = JobRequestReply;

    async fn handle(&mut self, msg: ShrinkWrapRequest, ctx: &mut Context<Self, Self::Reply>) {
        let reply_sender = ctx.reply_sender();
        self.job_request::<_, ShrinkWrapResult>(msg, ctx.actor_ref(), reply_sender)
            .await;
    }
}

impl Message<JobDone<ShrinkWrapResult>> for ManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        mut msg: JobDone<ShrinkWrapResult>,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("JobDone: {}", msg.job_id);

        if let JobStatus::Succeeded(result) = &msg.info.status
            && let Err(error) = self.shrink_wrap_success(&msg.job_id, result).await
        {
            msg.info.status = JobStatus::Failed(error.into());
        }
        self.jobs
            .insert(msg.job_id, JobEntry::Inactive(msg.info.into()));
    }
}

impl ManagerActor {
    async fn shrink_wrap_success(
        &mut self,
        job_id: &Uuid,
        result: &ShrinkWrapResult,
    ) -> Result<()> {
        self.write_receipt(job_id, &result.receipt).await?;
        Ok(())
    }
}

impl Message<JobDone<ProofResult>> for ManagerActor {
    type Reply = ();

    async fn handle(
        &mut self,
        mut msg: JobDone<ProofResult>,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("JobDone: {}", msg.job_id);

        if let JobStatus::Succeeded(result) = &msg.info.status
            && let Err(error) = self.proof_success(&msg.job_id, result).await
        {
            msg.info.status = JobStatus::Failed(error.into());
        }
        self.jobs
            .insert(msg.job_id, JobEntry::Inactive(msg.info.into()));
    }
}

impl ManagerActor {
    async fn proof_success(&mut self, job_id: &Uuid, result: &ProofResult) -> Result<()> {
        if let Some(receipt) = &result.receipt {
            self.write_receipt(job_id, receipt).await?;
        } else if let Some(journal) = &result.session.journal {
            self.write_journal(job_id, journal).await?;
        }
        Ok(())
    }
}

impl Message<JobStatusRequest> for ManagerActor {
    type Reply = Result<JobStatusReply>;

    async fn handle(&mut self, msg: JobStatusRequest, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(match self.jobs.get(&msg.job_id) {
            Some(JobEntry::Active(job)) => job
                .ask(JobStatusRequest { job_id: msg.job_id })
                .await
                .map_err(Error::from)
                .flatten(),
            Some(JobEntry::Inactive(inactive)) => Ok(inactive.clone().into()),
            None => Ok(JobStatusReply::NotFound),
        })
    }
}
