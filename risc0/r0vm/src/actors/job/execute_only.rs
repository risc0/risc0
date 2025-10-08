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

use std::sync::Arc;

use tokio::time::Instant;

use super::{JobActorNew, tracer::JobTracer};
use crate::actors::{
    actor::{Actor, ActorRef, Context, Message, ReplySender, WeakActorRef},
    error::{Error, Result},
    factory::FactoryActor,
    protocol::{
        ExecuteTask, GlobalId, JobId, JobInfo, JobStatus, JobStatusReply, JobStatusRequest,
        ProofRequest, ProofResult, Task, TaskError, TaskHeader,
        factory::{DropJob, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg},
    },
};

pub(crate) struct JobActor {
    job_id: JobId,
    parent_ref: WeakActorRef<super::JobActor>,
    factory: ActorRef<FactoryActor>,
    reply_sender: Option<ReplySender<JobStatusReply>>,
    start_time: Instant,
    status: JobStatus<ProofResult>,

    tracer: JobTracer,
}

impl Actor for JobActor {
    async fn on_stop(&mut self) {
        let _ = self
            .factory
            .tell(DropJob {
                job_id: self.job_id,
            })
            .await;

        let elapsed_time = self.start_time.elapsed();

        if let Some(reply_sender) = self.reply_sender.take() {
            let info = JobInfo {
                status: self.status.clone(),
                elapsed_time,
            };
            reply_sender.send(JobStatusReply::Proof(info));
        }

        self.tracer.end();
    }
}

impl JobActorNew for JobActor {
    fn new(
        job_id: JobId,
        parent_ref: WeakActorRef<super::JobActor>,
        factory: ActorRef<FactoryActor>,
    ) -> Self {
        let tracer = JobTracer::new("execute_only_job", job_id);
        Self {
            job_id,
            parent_ref,
            factory,
            reply_sender: None,
            start_time: Instant::now(),
            status: JobStatus::Running("init".to_string()),

            tracer,
        }
    }
}

impl JobActor {
    fn task_start(&mut self, header: TaskHeader) {
        let name = format!("{:?}", header.task_kind);
        self.tracer.span_start(header.global_id.task_id, name);
    }

    async fn execution_done(&mut self, self_ref: ActorRef<Self>, result: ProofResult) {
        tracing::info!("ExecutionDone");

        self.status = JobStatus::Succeeded(result);

        // on_stop will reply
        let _ = self_ref.stop_gracefully();
    }

    async fn submit_task(&mut self, task: Task) -> Result<()> {
        let msg = SubmitTaskMsg {
            job: self
                .parent_ref
                .upgrade()
                .ok_or_else(|| Error::new("parent job has stopped"))?,
            header: TaskHeader {
                global_id: GlobalId {
                    job_id: self.job_id,
                    task_id: 0,
                },
                task_kind: task.kind(),
            },
            task,
        };
        self.factory.tell(msg).await?;
        Ok(())
    }

    async fn maybe_fail(
        &mut self,
        self_ref: ActorRef<Self>,
        res: std::result::Result<(), impl Into<TaskError>>,
    ) {
        if let Err(error) = res {
            self.fail_with_error(self_ref, error).await;
        }
    }

    async fn fail_with_error(&mut self, self_ref: ActorRef<Self>, error: impl Into<TaskError>) {
        self.status = JobStatus::Failed(error.into());

        // on_stop will reply
        let _ = self_ref.stop_gracefully();
    }
}

impl Message<ProofRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(&mut self, request: ProofRequest, ctx: &mut Context<Self, Self::Reply>) {
        tracing::info!("execute_only ProofRequest");
        let reply_sender = ctx.reply_sender();
        self.reply_sender = reply_sender;

        let res = self
            .submit_task(Task::Execute(Arc::new(ExecuteTask { request })))
            .await;
        self.maybe_fail(ctx.actor_ref(), res).await;
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        match msg.payload {
            TaskUpdate::Start => self.task_start(msg.header),
            TaskUpdate::Segment(_) => {}
            TaskUpdate::Keccak(_) => {
                self.fail_with_error(
                    ctx.actor_ref(),
                    Error::new("unexpected TaskUpdate::Keccak in execute_only job"),
                )
                .await;
            }
        }
    }
}

impl Message<TaskDoneMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskDoneMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let res = self.handle_task_done(msg, ctx.actor_ref()).await;
        self.maybe_fail(ctx.actor_ref(), res).await;
    }
}

impl JobActor {
    async fn handle_task_done(
        &mut self,
        msg: TaskDoneMsg,
        self_ref: ActorRef<Self>,
    ) -> std::result::Result<(), TaskError> {
        self.tracer.span_end(msg.header.global_id.task_id);

        match msg.payload? {
            TaskDone::Session(session) => {
                self.execution_done(
                    self_ref,
                    ProofResult {
                        session,
                        receipt: None,
                    },
                )
                .await;
                Ok(())
            }
            _ => Err(Error::new("ExecuteOnly JobActor received unexpected task").into()),
        }
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = Result<JobStatusReply>;

    async fn handle(&mut self, _msg: JobStatusRequest, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(Ok(JobStatusReply::Proof(JobInfo {
            status: self.status.clone(),
            elapsed_time: self.start_time.elapsed(),
        })))
    }
}
