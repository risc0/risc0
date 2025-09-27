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
    factory::FactoryActor,
    protocol::{
        ExecuteTask, GlobalId, JobId, JobInfo, JobStatus, JobStatusReply, JobStatusRequest,
        ProofRequest, ProofResult, Task, TaskHeader,
        factory::{DropJob, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdate, TaskUpdateMsg},
    },
};

pub(crate) struct JobActor {
    job_id: JobId,
    parent_ref: WeakActorRef<super::JobActor>,
    self_ref: Option<WeakActorRef<Self>>,
    factory: ActorRef<FactoryActor>,
    reply_sender: Option<ReplySender<JobStatusReply>>,
    start_time: Instant,
    status: JobStatus<ProofResult>,

    tracer: JobTracer,
}

impl Actor for JobActor {
    async fn on_start(&mut self, actor_ref: ActorRef<Self>) -> anyhow::Result<()> {
        self.self_ref = Some(actor_ref.downgrade());
        Ok(())
    }

    async fn on_stop(&mut self) -> anyhow::Result<()> {
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
        Ok(())
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
            self_ref: None,
            factory,
            reply_sender: None,
            start_time: Instant::now(),
            status: JobStatus::Running("init".to_string()),

            tracer,
        }
    }
}

impl JobActor {
    fn self_ref(&self) -> ActorRef<Self> {
        self.self_ref.as_ref().unwrap().upgrade().unwrap()
    }

    fn task_start(&mut self, header: TaskHeader) {
        let name = format!("{:?}", header.task_kind);
        self.tracer.span_start(header.global_id.task_id, name);
    }

    async fn execution_done(&mut self, result: ProofResult) {
        tracing::info!("ExecutionDone");
        self.status = JobStatus::Succeeded(result);
        self.self_ref().stop_gracefully().await.unwrap();
    }

    async fn submit_task(&mut self, task: Task) {
        let msg = SubmitTaskMsg {
            job: self.parent_ref.upgrade().unwrap(),
            header: TaskHeader {
                global_id: GlobalId {
                    job_id: self.job_id,
                    task_id: 0,
                },
                task_kind: task.kind(),
            },
            task,
        };
        self.factory.tell(msg).await.unwrap();
    }
}

impl Message<ProofRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(&mut self, request: ProofRequest, ctx: &mut Context<Self, Self::Reply>) {
        tracing::info!("execute_only ProofRequest");
        let reply_sender = ctx.reply_sender();
        self.reply_sender = reply_sender;
        self.submit_task(Task::Execute(Arc::new(ExecuteTask { request })))
            .await;
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        _ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        // tracing::info!("TaskUpdateMsg: {}", msg.header.global_id.task_id);
        match msg.payload {
            TaskUpdate::Start => self.task_start(msg.header),
            TaskUpdate::Segment(_) => {}
            TaskUpdate::Keccak(_) => panic!("unexpected TaskUpdate::Keccak in execute_only job"),
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
        if let TaskDone::Session(session) = task_done {
            self.execution_done(ProofResult {
                session,
                receipt: None,
            })
            .await;
        } else {
            panic!("ExecuteOnly JobActor received unexpected task")
        }
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(&mut self, _msg: JobStatusRequest, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(JobStatusReply::Proof(JobInfo {
            status: self.status.clone(),
            elapsed_time: self.start_time.elapsed(),
        }))
    }
}
