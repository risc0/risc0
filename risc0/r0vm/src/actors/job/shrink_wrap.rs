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

use std::{sync::Arc, time::Instant};

use kameo::{error::Infallible, prelude::*};
use risc0_zkvm::Receipt;

use super::{tracer::JobTracer, JobActorNew};
use crate::actors::{
    factory::FactoryActor,
    protocol::{
        factory::{DropJob, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg},
        GlobalId, JobId, JobStatus, JobStatusReply, JobStatusRequest, ShrinkWrapRequest,
        ShrinkWrapResult, ShrinkWrapTask, Task, TaskError, TaskHeader,
    },
    JobInfo,
};

pub(crate) struct JobActor {
    job_id: JobId,
    parent_ref: WeakActorRef<super::JobActor>,
    next_task_id: u64,
    self_ref: Option<WeakActorRef<Self>>,
    factory: ActorRef<FactoryActor>,
    start_time: Instant,
    status: JobStatus<ShrinkWrapResult>,
    reply_sender: Option<ReplySender<JobStatusReply>>,

    tracer: JobTracer,
}

impl Actor for JobActor {
    type Error = Infallible;

    async fn on_start(&mut self, actor_ref: ActorRef<Self>) -> Result<(), Self::Error> {
        self.self_ref = Some(actor_ref.downgrade());
        Ok(())
    }

    async fn on_stop(
        &mut self,
        _actor_ref: WeakActorRef<Self>,
        reason: ActorStopReason,
    ) -> Result<(), Self::Error> {
        let _ = self
            .factory
            .tell(DropJob {
                job_id: self.job_id,
            })
            .await;

        let elapsed_time = self.start_time.elapsed();

        if let ActorStopReason::Panicked(err) = reason {
            tracing::error!("{err}");
            self.tracer.record_error(&err);
            if let Some(reply_sender) = self.reply_sender.take() {
                let info = JobInfo {
                    status: JobStatus::Failed(TaskError::Generic(err.to_string())),
                    elapsed_time,
                };
                reply_sender.send(JobStatusReply::ShrinkWrap(info));
            }
        } else if let Some(reply_sender) = self.reply_sender.take() {
            let info = JobInfo {
                status: self.status.clone(),
                elapsed_time,
            };
            reply_sender.send(JobStatusReply::ShrinkWrap(info));
        }

        self.tracer.end();
        Ok(())
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
            self_ref: None,
            factory,
            start_time: Instant::now(),
            status: JobStatus::Running("init".into()),
            reply_sender: None,

            tracer,
        }
    }
}

impl JobActor {
    fn self_ref(&self) -> ActorRef<Self> {
        self.self_ref.as_ref().unwrap().upgrade().unwrap()
    }

    fn next_task_id(&mut self) -> u64 {
        let id = self.next_task_id;
        self.next_task_id += 1;
        id
    }

    async fn submit_task(&mut self, task: Task) {
        let task_id = self.next_task_id();
        let msg = SubmitTaskMsg {
            job: self.parent_ref.upgrade().unwrap(),
            header: TaskHeader {
                global_id: GlobalId {
                    job_id: self.job_id,
                    task_id,
                },
                task_kind: task.kind(),
            },
            task,
        };
        self.factory.tell(msg).await.unwrap();
    }

    async fn shrink_wrap_done(&mut self, receipt: Arc<Receipt>) {
        let result = ShrinkWrapResult { receipt };
        self.status = JobStatus::Succeeded(result);
        self.self_ref().stop_gracefully().await.unwrap();
    }

    fn task_start(&mut self, header: TaskHeader) {
        let name = format!("{:?}", header.task_kind);
        self.tracer.span_start(header.global_id.task_id, name);
    }
}

impl Message<ShrinkWrapRequest> for JobActor {
    type Reply = DelegatedReply<JobStatusReply>;

    async fn handle(
        &mut self,
        request: ShrinkWrapRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("ShrinkWrapRequest");
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.reply_sender = reply_sender;
        self.submit_task(Task::ShrinkWrap(Arc::new(ShrinkWrapTask {
            kind: request.kind,
            receipt: Arc::new(request.receipt),
        })))
        .await;
        delegated_reply
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        if matches!(msg.payload, TaskUpdate::Start) {
            self.task_start(msg.header);
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
        // tracing::info!("TaskDoneMsg: {}", msg.header.global_id.task_id);
        let task_done = match msg.payload {
            Ok(task_done) => task_done,
            Err(err) => {
                self.status = JobStatus::Failed(err);
                let _ = ctx.actor_ref().stop_gracefully().await;
                return;
            }
        };
        self.tracer.span_end(msg.header.global_id.task_id);
        match task_done {
            TaskDone::ShrinkWrap(receipt) => self.shrink_wrap_done(receipt).await,
            _ => {
                panic!("ShrinkWrap JobActor received unexpected task")
            }
        }
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(
        &mut self,
        _msg: JobStatusRequest,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        JobStatusReply::ShrinkWrap(JobInfo {
            status: self.status.clone(),
            elapsed_time: self.start_time.elapsed(),
        })
    }
}
