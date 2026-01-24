// Copyright 2026 RISC Zero, Inc.
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

use std::{sync::Arc, time::Instant};

use risc0_zkvm::Receipt;

use super::{JobActorNew, tracer::JobTracer};
use crate::actors::{
    JobInfo,
    actor::{Actor, ActorRef, Context, Message, ReplySender, WeakActorRef},
    error::{Error, Result},
    factory::FactoryActor,
    protocol::{
        GlobalId, JobId, JobStatus, JobStatusReply, JobStatusRequest, ShrinkWrapRequest,
        ShrinkWrapResult, ShrinkWrapTask, Task, TaskError, TaskHeader,
        factory::{DropJob, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdateMsg},
    },
};

pub(crate) struct JobActor {
    job_id: JobId,
    parent_ref: WeakActorRef<super::JobActor>,
    next_task_id: u64,
    factory: ActorRef<FactoryActor>,
    start_time: Instant,
    status: JobStatus<ShrinkWrapResult>,
    reply_sender: Option<ReplySender<JobStatusReply>>,

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
            reply_sender.send(JobStatusReply::ShrinkWrap(info)).await;
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
        let tracer = JobTracer::new("shrink_wrap_job", job_id);
        Self {
            job_id,
            parent_ref,
            next_task_id: 0,
            factory,
            start_time: Instant::now(),
            status: JobStatus::Running("init".into()),
            reply_sender: None,

            tracer,
        }
    }
}

impl JobActor {
    fn next_task_id(&mut self) -> u64 {
        let id = self.next_task_id;
        self.next_task_id += 1;
        id
    }

    async fn submit_task(&mut self, task: Task) -> Result<()> {
        let task_id = self.next_task_id();
        let header = TaskHeader {
            global_id: GlobalId {
                job_id: self.job_id,
                task_id,
            },
            task_kind: task.kind(),
        };
        self.task_start(header.clone());
        let msg = SubmitTaskMsg {
            job: self
                .parent_ref
                .upgrade()
                .ok_or_else(|| Error::new("parent job not running"))?,
            header,
            task,
            tracing: self.tracer.saved_task_context(task_id),
        };
        self.factory.tell(msg).await?;

        Ok(())
    }

    async fn shrink_wrap_done(&mut self, self_ref: ActorRef<Self>, receipt: Arc<Receipt>) {
        let result = ShrinkWrapResult { receipt };
        self.status = JobStatus::Succeeded(result);

        // on_stop will reply
        let _ = self_ref.stop_gracefully("job shutdown");
    }

    fn task_start(&mut self, header: TaskHeader) {
        let name = format!("{:?}", header.task_kind);
        self.tracer.span_start(header.global_id.task_id, name);
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
        let error: TaskError = error.into();

        // on_stop will reply
        let _ = self_ref.stop_gracefully(format!("job failure: {error:?}"));

        self.status = JobStatus::Failed(error);
    }
}

impl Message<ShrinkWrapRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(&mut self, request: ShrinkWrapRequest, ctx: &mut Context<Self, Self::Reply>) {
        let res = self.handle_shrink_wrap(request, ctx).await;
        self.maybe_fail(ctx.actor_ref(), res).await;
    }
}

impl JobActor {
    async fn handle_shrink_wrap(
        &mut self,
        request: ShrinkWrapRequest,
        ctx: &mut Context<Self, JobStatusReply>,
    ) -> Result<()> {
        tracing::info!("ShrinkWrapRequest");

        if self.reply_sender.is_some() {
            return Err(Error::new("received duplicate ShrinkWrapRequest"));
        }
        self.reply_sender = ctx.reply_sender();

        self.submit_task(Task::ShrinkWrap(Arc::new(ShrinkWrapTask {
            kind: request.kind,
            receipt: Arc::new(request.receipt),
            dev_mode: request.dev_mode,
        })))
        .await?;

        Ok(())
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        _msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
    }
}

impl Message<TaskDoneMsg> for JobActor {
    type Reply = ();

    async fn handle(&mut self, msg: TaskDoneMsg, ctx: &mut Context<Self, Self::Reply>) {
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
            TaskDone::ShrinkWrap(receipt) => {
                self.shrink_wrap_done(self_ref, receipt).await;
                Ok(())
            }
            _ => Err(Error::new("ShrinkWrap JobActor received unexpected task").into()),
        }
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = Result<JobStatusReply>;

    async fn handle(&mut self, _msg: JobStatusRequest, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(Ok(JobStatusReply::ShrinkWrap(JobInfo {
            status: self.status.clone(),
            elapsed_time: self.start_time.elapsed(),
        })))
        .await
    }
}
