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

use std::collections::HashMap;

use multi_index_map::MultiIndexMap;

use super::{
    RemoteActor, RemoteFactoryRequest, RpcDisconnect,
    actor::{Actor, ActorRef, Context, Message},
    allocator::{CpuCores, GpuTokens, RemoteAllocatorActor, ScheduleTask},
    error::{Error, Result as ActorResult},
    job::JobActor,
    protocol::{
        GlobalId, JobId, TaskKind, WorkerId,
        factory::{DropJob, GetTasks, SubmitTaskMsg, TaskDoneMsg, TaskUpdateMsg},
        worker::TaskMsg,
    },
    remote_actor_tell,
    worker::RemoteWorkerActor,
};

#[derive(MultiIndexMap)]
struct WorkerRow {
    #[multi_index(hashed_non_unique)]
    task_kind: TaskKind,
    #[multi_index(hashed_non_unique)]
    worker_id: WorkerId,
}

pub(crate) struct FactoryActor {
    jobs: HashMap<JobId, ActorRef<JobActor>>,
    workers: MultiIndexWorkerRowMap,
    pending_tasks: Vec<SubmitTaskMsg>,
    active_tasks: HashMap<GlobalId, SubmitTaskMsg>,
    worker_actors: HashMap<WorkerId, ActorRef<RemoteWorkerActor>>,
    allocator: ActorRef<RemoteAllocatorActor>,
    require_gpu: bool,
}

impl FactoryActor {
    pub fn new(allocator: ActorRef<RemoteAllocatorActor>, require_gpu: bool) -> Self {
        Self {
            jobs: HashMap::default(),
            workers: Default::default(),
            pending_tasks: Default::default(),
            active_tasks: HashMap::default(),
            worker_actors: HashMap::default(),
            require_gpu,
            allocator,
        }
    }
}

impl Actor for FactoryActor {
    async fn on_stop(&mut self) {
        for worker in self.worker_actors.values() {
            let _ = worker.stop_gracefully().await;
        }

        for task in self.pending_tasks.iter().chain(self.active_tasks.values()) {
            let _ = task
                .job
                .tell(TaskDoneMsg {
                    header: task.header.clone(),
                    payload: Err(Error::new("factory has stopped").into()),
                })
                .await;
        }

        // stop timer
        tracing::info!("Factory: on_stop");
    }
}

impl FactoryActor {
    async fn maybe_schedule_tasks(&mut self) -> ActorResult<()> {
        for msg in std::mem::take(&mut self.pending_tasks) {
            let workers = self.workers.get_by_task_kind(&msg.header.task_kind);

            if !workers.is_empty() {
                tracing::info!("Factory: scheduling job {:?}", &msg.header);
                let job_id = msg.header.global_id.job_id;

                self.jobs.insert(job_id, msg.job.clone());

                let (cores, gpu_tokens) = self.choose_tokens(msg.header.task_kind);
                let task = TaskMsg {
                    header: msg.header.clone(),
                    task: msg.task.clone(),
                    cores,
                    gpu_tokens,
                };

                let response = self
                    .allocator
                    .ask(ScheduleTask {
                        candidates: workers.iter().map(|w| w.worker_id).collect(),
                        task_id: msg.header.global_id,
                        description: format!("{:?}", &msg.header.task_kind),
                    })
                    .await??;

                let worker_id = response.worker_id;
                let worker_actor = self.worker_actors.get(&worker_id).ok_or_else(|| {
                    Error::new("received candidate worker from allocator outside given set")
                })?;
                tracing::info!(
                    "Factory: sending job {:?} to worker {worker_id:?}",
                    &msg.header
                );

                // XXX remi: If we error when talking with a worker, we should instead remove the
                // worker and reschedule
                worker_actor.tell(task).await?;
                self.active_tasks.insert(msg.header.global_id, msg);
            } else {
                self.pending_tasks.push(msg);
            }
        }

        Ok(())
    }

    fn choose_tokens(&self, task_kind: TaskKind) -> (CpuCores, GpuTokens) {
        let (cores, mut gpu_tokens) = match task_kind {
            TaskKind::Execute => (CpuCores::from(1), GpuTokens::from(0)),
            TaskKind::ProveSegment => (CpuCores::from(1), GpuTokens::from(100)),
            TaskKind::ProveKeccak => (CpuCores::ZERO, GpuTokens::from(100)),
            _ => (CpuCores::ZERO, GpuTokens::from(50)),
        };

        if !self.require_gpu {
            gpu_tokens = GpuTokens::ZERO;
        }
        (cores, gpu_tokens)
    }

    async fn maybe_fail(&mut self, res: ActorResult<()>, self_ref: ActorRef<Self>) {
        if let Err(error) = res {
            tracing::error!("Factory has encountered fatal error: {error:?}");

            let _ = self_ref.stop_gracefully().await;
        }
    }
}

impl Message<DropJob> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: DropJob, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        self.jobs.remove(&msg.job_id);
        self.pending_tasks
            .retain(|t| t.header.global_id.job_id != msg.job_id);
    }
}

impl Message<SubmitTaskMsg> for FactoryActor {
    type Reply = ActorResult<()>;

    async fn handle(&mut self, msg: SubmitTaskMsg, ctx: &mut Context<Self, Self::Reply>) {
        self.pending_tasks.push(msg);

        let res = self.maybe_schedule_tasks().await;
        self.maybe_fail(res, ctx.actor_ref()).await;
    }
}

impl Message<GetTasks> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, msg: GetTasks, ctx: &mut Context<Self, Self::Reply>) {
        tracing::info!("factory received connection from worker: {}", msg.worker_id);

        self.worker_actors.insert(
            msg.worker_id,
            msg.worker
                .expect("worker should always be filled in locally"),
        );

        for task_kind in msg.kinds {
            let worker = WorkerRow {
                task_kind,
                worker_id: msg.worker_id,
            };
            self.workers.insert(worker);
        }

        let res = self.maybe_schedule_tasks().await;
        self.maybe_fail(res, ctx.actor_ref()).await;
    }
}

impl Message<TaskUpdateMsg> for FactoryActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        if let Some(job) = self.jobs.get(&msg.header.global_id.job_id) {
            ctx.forward(job, msg).await;
        }
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
        if let Some(job) = self.jobs.get(&msg.header.global_id.job_id) {
            ctx.forward(job, msg).await;
        }
    }
}

impl Message<RpcDisconnect> for FactoryActor {
    type Reply = ();

    async fn handle(&mut self, _msg: RpcDisconnect, _ctx: &mut Context<Self, Self::Reply>) {
        // XXX remi: We should remove any workers associated with the RPC connection here.
    }
}

//
//  _ __ _ __   ___
// | '__| '_ \ / __|
// | |  | |_) | (__
// |_|  | .__/ \___|
//      |_|

pub type RemoteFactoryActor = RemoteActor<FactoryActor>;

remote_actor_tell!(RemoteActor<FactoryActor>, GetTasks, RemoteFactoryRequest);

remote_actor_tell!(
    RemoteActor<FactoryActor>,
    TaskUpdateMsg,
    RemoteFactoryRequest
);
remote_actor_tell!(RemoteActor<FactoryActor>, TaskDoneMsg, RemoteFactoryRequest);
