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

use std::collections::{HashMap, HashSet, VecDeque};
use std::net::SocketAddr;

use derive_more::From;
use multi_index_map::MultiIndexMap;

use super::{
    RemoteActor, RemoteFactoryRequest, RpcDisconnect,
    actor::{Actor, ActorRef, Context, Message, SendError},
    allocator::{CpuCores, GpuTokens, RemoteAllocatorActor, ScheduleTask, ScheduleTaskReply},
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
    #[multi_index(hashed_non_unique)]
    remote_address: SocketAddr,
}

pub(crate) trait FactoryDeps: 'static {
    type Allocator: Actor + Message<ScheduleTask, Reply = ActorResult<ScheduleTaskReply>>;
    type Worker: Actor + Message<TaskMsg, Reply = ()>;
    type Job: Actor + Message<TaskDoneMsg, Reply = ()> + Message<TaskUpdateMsg, Reply = ()>;
}

pub(crate) struct DefaultFactoryDeps;

impl FactoryDeps for DefaultFactoryDeps {
    type Allocator = RemoteAllocatorActor;
    type Worker = RemoteWorkerActor;
    type Job = JobActor;
}

struct ActiveTask<JobT: Actor> {
    worker_id: WorkerId,
    msg: SubmitTaskMsg<JobT>,
}

enum PendingTaskState {
    Submitted,
    WaitingForWorker { task: TaskMsg },
    ReadyForWorker { worker_id: WorkerId, task: TaskMsg },
}

struct PendingTask<JobT: Actor> {
    msg: SubmitTaskMsg<JobT>,
    state: PendingTaskState,
}

pub(crate) struct FactoryActor<DepsT: FactoryDeps = DefaultFactoryDeps> {
    jobs: HashMap<JobId, ActorRef<DepsT::Job>>,
    workers: MultiIndexWorkerRowMap,
    pending_tasks: VecDeque<PendingTask<DepsT::Job>>,
    active_tasks: HashMap<GlobalId, ActiveTask<DepsT::Job>>,
    worker_actors: HashMap<WorkerId, ActorRef<DepsT::Worker>>,
    allocator: ActorRef<DepsT::Allocator>,
    require_gpu: bool,
}

impl<DepsT: FactoryDeps> FactoryActor<DepsT> {
    pub fn new(allocator: ActorRef<DepsT::Allocator>, require_gpu: bool) -> Self {
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

impl<DepsT: FactoryDeps> Actor for FactoryActor<DepsT> {
    async fn on_stop(&mut self) {
        for worker in self.worker_actors.values() {
            let _ = worker.stop_gracefully("factory shutdown");
        }

        for task in self
            .pending_tasks
            .iter()
            .map(|pt| &pt.msg)
            .chain(self.active_tasks.values().map(|t| &t.msg))
        {
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

type ScheduleResult<T> = std::result::Result<T, ScheduleError>;

#[derive(From)]
enum ScheduleError {
    #[from(skip)]
    WorkerDisconnected {
        worker_id: WorkerId,
    },
    ActorError(Error),
}

impl From<SendError> for ScheduleError {
    fn from(e: SendError) -> Self {
        Self::ActorError(e.into())
    }
}

struct TaskGotWorker {
    worker_id: ActorResult<WorkerId>,
    task_id: GlobalId,
}

impl<DepsT: FactoryDeps> Message<TaskGotWorker> for FactoryActor<DepsT> {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskGotWorker,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let res = self.handle_task_got_worker(msg, ctx.actor_ref()).await;
        if let Err(error) = res {
            self.fail(error, ctx.actor_ref()).await;
        }
    }
}

async fn schedule_task_cb<DepsT: FactoryDeps>(
    factory_ref: ActorRef<FactoryActor<DepsT>>,
    task_id: GlobalId,
    res: Result<ActorResult<ScheduleTaskReply>, SendError>,
) {
    let response = match res {
        Ok(resp) => resp,
        Err(error) => {
            let msg = format!("ScheduleTask reply error: {error}");
            tracing::error!("{msg}");
            let _ = factory_ref.stop_gracefully(msg);
            return;
        }
    };
    let _ = factory_ref
        .tell(TaskGotWorker {
            worker_id: response.map(|resp| resp.worker_id),
            task_id,
        })
        .await;
}

impl<DepsT: FactoryDeps> FactoryActor<DepsT> {
    async fn handle_task_got_worker(
        &mut self,
        TaskGotWorker { task_id, worker_id }: TaskGotWorker,
        self_ref: ActorRef<Self>,
    ) -> ActorResult<()> {
        let Some(pending) = self
            .pending_tasks
            .iter_mut()
            .find(|pending| pending.msg.header.global_id == task_id)
        else {
            // The task is for a job that is gone.
            return Ok(());
        };

        let PendingTaskState::WaitingForWorker { task } = &pending.state else {
            return Err(Error::new(format!(
                "received unexpected ScheduleTask response: task {task_id} not waiting for worker"
            )));
        };

        match worker_id {
            Ok(worker_id) => {
                pending.state = PendingTaskState::ReadyForWorker {
                    worker_id,
                    task: task.clone(),
                };
            }
            Err(error) => {
                tracing::error!("received allocator error when scheduling task: {error}");
                pending.state = PendingTaskState::Submitted;
            }
        }

        self.maybe_schedule_tasks(self_ref).await;

        Ok(())
    }

    async fn maybe_allocate_submitted_task(
        &mut self,
        pending_task_state: &mut PendingTaskState,
        self_ref: ActorRef<FactoryActor<DepsT>>,
        msg: &SubmitTaskMsg<<DepsT as FactoryDeps>::Job>,
    ) -> Result<(), ScheduleError> {
        let workers = self.workers.get_by_task_kind(&msg.header.task_kind);
        if workers.is_empty() {
            return Ok(());
        }

        tracing::info!("Factory: scheduling job {:?}", &msg.header);
        let (cores, gpu_tokens) = self.choose_tokens(msg.header.task_kind);

        let task = TaskMsg {
            header: msg.header.clone(),
            task: msg.task.clone(),
            cores,
            gpu_tokens,
            tracing: msg.tracing.clone(),
        };

        let task_id = msg.header.global_id;
        let mut candidates: Vec<_> = workers.iter().map(|w| w.worker_id).collect();
        candidates.sort();

        self.allocator
            .ask_callback(
                ScheduleTask {
                    candidates,
                    task_id,
                    description: format!("{:?}", &msg.header.task_kind),
                },
                move |res| schedule_task_cb(self_ref, task_id, res),
            )
            .await?;

        *pending_task_state = PendingTaskState::WaitingForWorker { task };

        Ok(())
    }

    async fn maybe_schedule_ready_task(
        &mut self,
        pending_task_state: &mut PendingTaskState,
        msg: &SubmitTaskMsg<<DepsT as FactoryDeps>::Job>,
        worker_id: uuid::Uuid,
        task: TaskMsg,
    ) -> Result<(), ScheduleError> {
        let job_id = task.header.global_id.job_id;

        let Some(worker_actor) = self.worker_actors.get(&worker_id) else {
            *pending_task_state = PendingTaskState::Submitted;
            return Err(ScheduleError::WorkerDisconnected { worker_id });
        };

        tracing::info!(
            "Factory: sending job {:?} to worker {worker_id:?}",
            &task.header
        );
        if worker_actor.tell(task).await.is_err() {
            *pending_task_state = PendingTaskState::Submitted;
            return Err(ScheduleError::WorkerDisconnected { worker_id });
        }

        self.jobs.insert(job_id, msg.job.clone());
        self.active_tasks.insert(
            msg.header.global_id,
            ActiveTask {
                worker_id,
                msg: msg.clone(),
            },
        );

        Ok(())
    }

    async fn maybe_schedule_task(
        &mut self,
        pending_task: &mut PendingTask<DepsT::Job>,
        self_ref: ActorRef<Self>,
    ) -> ScheduleResult<bool> {
        let msg = &pending_task.msg;

        match &pending_task.state {
            PendingTaskState::Submitted => {
                self.maybe_allocate_submitted_task(&mut pending_task.state, self_ref, msg)
                    .await?;
                Ok(false)
            }
            PendingTaskState::ReadyForWorker { worker_id, task } => {
                let worker_id = *worker_id;
                let task = task.clone();
                self.maybe_schedule_ready_task(&mut pending_task.state, msg, worker_id, task)
                    .await?;
                Ok(true)
            }
            _ => Ok(false),
        }
    }

    async fn maybe_schedule_tasks_inner(&mut self, self_ref: ActorRef<Self>) -> ScheduleResult<()> {
        let mut skipped_tasks = VecDeque::new();

        let mut res: ScheduleResult<bool> = Ok(false);

        while let Some(mut msg) = self.pending_tasks.pop_front() {
            res = self.maybe_schedule_task(&mut msg, self_ref.clone()).await;

            // If the task wasn't scheduled, skip it
            if matches!(&res, Ok(false) | Err(_)) {
                skipped_tasks.push_back(msg);
            }

            if res.is_err() {
                break;
            }
        }

        self.pending_tasks.extend(skipped_tasks);
        res.map(|_| ())
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

    async fn fail(&mut self, error: Error, self_ref: ActorRef<Self>) {
        tracing::error!("Factory has encountered fatal error: {error:?}");
        let _ = self_ref.stop_gracefully(format!("fatal error: {error:?}"));
    }

    async fn remove_workers(&mut self, workers: HashSet<WorkerId>) {
        for worker_id in &workers {
            self.workers.remove_by_worker_id(worker_id);
        }

        self.worker_actors
            .retain(|worker_id, _| !workers.contains(worker_id));

        for (id, task) in std::mem::take(&mut self.active_tasks) {
            if workers.contains(&task.worker_id) {
                self.pending_tasks.push_back(PendingTask {
                    state: PendingTaskState::Submitted,
                    msg: task.msg,
                });
            } else {
                self.active_tasks.insert(id, task);
            }
        }
    }

    async fn remove_worker(&mut self, worker_id: WorkerId) {
        let mut workers = HashSet::new();
        workers.insert(worker_id);
        self.remove_workers(workers).await;
    }

    async fn maybe_schedule_tasks(&mut self, self_ref: ActorRef<Self>) {
        while let Err(error) = self.maybe_schedule_tasks_inner(self_ref.clone()).await {
            match error {
                ScheduleError::WorkerDisconnected { worker_id } => {
                    self.remove_worker(worker_id).await;
                }
                ScheduleError::ActorError(error) => {
                    self.fail(error, self_ref).await;
                    break;
                }
            }
        }
    }
}

impl<DepsT: FactoryDeps> Message<DropJob> for FactoryActor<DepsT> {
    type Reply = ();

    async fn handle(&mut self, msg: DropJob, _ctx: &mut Context<Self, Self::Reply>) -> Self::Reply {
        self.jobs.remove(&msg.job_id);
        self.pending_tasks
            .retain(|t| t.msg.header.global_id.job_id != msg.job_id);
        self.active_tasks.retain(|id, _| id.job_id != msg.job_id);
    }
}

impl<DepsT: FactoryDeps> Message<SubmitTaskMsg<DepsT::Job>> for FactoryActor<DepsT> {
    type Reply = ActorResult<()>;

    async fn handle(
        &mut self,
        msg: SubmitTaskMsg<DepsT::Job>,
        ctx: &mut Context<Self, Self::Reply>,
    ) {
        self.pending_tasks.push_back(PendingTask {
            state: PendingTaskState::Submitted,
            msg,
        });

        self.maybe_schedule_tasks(ctx.actor_ref()).await;
    }
}

impl<DepsT: FactoryDeps> Message<GetTasks<DepsT::Worker>> for FactoryActor<DepsT> {
    type Reply = ();

    async fn handle(&mut self, msg: GetTasks<DepsT::Worker>, ctx: &mut Context<Self, Self::Reply>) {
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
                remote_address: msg
                    .remote_address
                    .expect("remote_address should always be filled in locally"),
            };
            self.workers.insert(worker);
        }

        self.maybe_schedule_tasks(ctx.actor_ref()).await;
    }
}

impl<DepsT: FactoryDeps> Message<TaskUpdateMsg> for FactoryActor<DepsT> {
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

impl<DepsT: FactoryDeps> Message<TaskDoneMsg> for FactoryActor<DepsT> {
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

impl<DepsT: FactoryDeps> Message<RpcDisconnect> for FactoryActor<DepsT> {
    type Reply = ();

    async fn handle(&mut self, msg: RpcDisconnect, ctx: &mut Context<Self, Self::Reply>) {
        let worker_ids: HashSet<_> = self
            .workers
            .get_by_remote_address(&msg.remote_address)
            .into_iter()
            .map(|w| w.worker_id)
            .collect();

        self.remove_workers(worker_ids).await;

        self.maybe_schedule_tasks(ctx.actor_ref()).await;
    }
}

#[cfg(test)]
mod tests {
    use std::sync::{Arc, Mutex};

    use super::*;
    use crate::actors::actor::{self, Actor, ActorRunner};
    use crate::actors::protocol::{ExecuteTask, ProofRequest, Task, TaskError, TaskHeader};

    #[derive(Clone, Default)]
    struct TestAllocator {
        #[allow(clippy::type_complexity)]
        messages: Arc<Mutex<VecDeque<(ScheduleTask, ActorResult<ScheduleTaskReply>)>>>,
    }

    impl Actor for TestAllocator {}

    impl Message<ScheduleTask> for TestAllocator {
        type Reply = ActorResult<ScheduleTaskReply>;

        async fn handle(&mut self, msg: ScheduleTask, ctx: &mut Context<Self, Self::Reply>) {
            let (expected_msg, reply) = self
                .messages
                .lock()
                .unwrap()
                .pop_front()
                .unwrap_or_else(|| panic!("unexpected message: {msg:?}"));

            assert_eq!(msg, expected_msg);
            ctx.reply_sender().unwrap().send(reply).await;
        }
    }

    impl TestAllocator {
        fn expect(&self, msg: ScheduleTask, reply: ActorResult<ScheduleTaskReply>) {
            self.messages.lock().unwrap().push_back((msg, reply));
        }
    }

    impl Drop for TestAllocator {
        fn drop(&mut self) {
            let messages = self.messages.lock().unwrap();
            assert!(messages.is_empty(), "{messages:?}");
        }
    }

    #[derive(PartialEq, Eq, Debug)]
    struct TaskMsgExpectation {
        header: TaskHeader,
        task: TaskKind,
        gpu_tokens: GpuTokens,
        cores: CpuCores,
    }

    impl From<TaskMsg> for TaskMsgExpectation {
        fn from(msg: TaskMsg) -> Self {
            Self {
                header: msg.header,
                task: msg.task.kind(),
                gpu_tokens: msg.gpu_tokens,
                cores: msg.cores,
            }
        }
    }

    #[derive(Clone, Default)]
    struct TestWorker {
        messages: Arc<Mutex<VecDeque<TaskMsgExpectation>>>,
    }

    impl Actor for TestWorker {}

    impl Message<TaskMsg> for TestWorker {
        type Reply = ();

        async fn handle(&mut self, msg: TaskMsg, _ctx: &mut Context<Self, Self::Reply>) {
            let msg = TaskMsgExpectation::from(msg);
            let expected_msg = self
                .messages
                .lock()
                .unwrap()
                .pop_front()
                .unwrap_or_else(|| panic!("unexpected message: {msg:?}"));

            assert_eq!(msg, expected_msg);
        }
    }

    impl TestWorker {
        fn expect(&self, msg: TaskMsgExpectation) {
            self.messages.lock().unwrap().push_back(msg);
        }
    }

    impl Drop for TestWorker {
        fn drop(&mut self) {
            let messages = self.messages.lock().unwrap();
            assert!(messages.is_empty(), "{messages:?}");
        }
    }

    #[derive(Debug, From, PartialEq, Eq)]
    struct TaskDoneExpectation {
        header: TaskHeader,
        payload: Result<TaskKind, TaskError>,
    }

    #[derive(Debug, From, PartialEq, Eq)]
    struct TaskUpdateExpectation {
        header: TaskHeader,
    }

    #[derive(Debug, From, PartialEq, Eq)]
    enum TestJobMsg {
        Done(TaskDoneExpectation),
        Update(TaskUpdateExpectation),
    }

    impl From<TaskUpdateMsg> for TestJobMsg {
        fn from(u: TaskUpdateMsg) -> Self {
            Self::Update(TaskUpdateExpectation { header: u.header })
        }
    }

    impl From<TaskDoneMsg> for TestJobMsg {
        fn from(d: TaskDoneMsg) -> Self {
            Self::Done(TaskDoneExpectation {
                header: d.header,
                payload: d.payload.map(|t| t.kind()),
            })
        }
    }

    #[derive(Clone, Default)]
    struct TestJob {
        messages: Arc<Mutex<VecDeque<TestJobMsg>>>,
    }

    impl Actor for TestJob {}

    impl Message<TaskDoneMsg> for TestJob {
        type Reply = ();

        async fn handle(&mut self, msg: TaskDoneMsg, _ctx: &mut Context<Self, Self::Reply>) {
            let msg = TestJobMsg::from(msg);
            let expected_msg = self
                .messages
                .lock()
                .unwrap()
                .pop_front()
                .unwrap_or_else(|| panic!("unexpected message: {msg:?}"));

            assert_eq!(msg, expected_msg);
        }
    }

    impl Message<TaskUpdateMsg> for TestJob {
        type Reply = ();

        async fn handle(&mut self, msg: TaskUpdateMsg, _ctx: &mut Context<Self, Self::Reply>) {
            let msg = TestJobMsg::from(msg);
            let expected_msg = self
                .messages
                .lock()
                .unwrap()
                .pop_front()
                .unwrap_or_else(|| panic!("unexpected message: {msg:?}"));

            assert_eq!(msg, expected_msg);
        }
    }

    impl TestJob {
        fn expect(&self, msg: impl Into<TestJobMsg>) {
            self.messages.lock().unwrap().push_back(msg.into());
        }
    }

    impl Drop for TestJob {
        fn drop(&mut self) {
            let messages = self.messages.lock().unwrap();
            assert!(messages.is_empty(), "{messages:?}");
        }
    }

    struct TestFactoryDeps;

    impl FactoryDeps for TestFactoryDeps {
        type Allocator = TestAllocator;
        type Worker = TestWorker;
        type Job = TestJob;
    }

    struct FixtureWorker {
        id: WorkerId,
        test_worker: TestWorker,
        worker_runner: ActorRunner<TestWorker>,
        remote_address: SocketAddr,
    }

    struct Fixture {
        factory_ref: ActorRef<FactoryActor<TestFactoryDeps>>,
        factory_runner: ActorRunner<FactoryActor<TestFactoryDeps>>,

        test_alloc: TestAllocator,
        alloc_runner: ActorRunner<TestAllocator>,

        workers: Vec<FixtureWorker>,

        job_ref: ActorRef<TestJob>,
        job_runner: ActorRunner<TestJob>,
        test_job: TestJob,
    }

    impl Fixture {
        async fn new(num_workers: usize) -> Self {
            let test_alloc = TestAllocator::default();
            let (alloc_ref, alloc_runner) = actor::run(test_alloc.clone()).await;
            let (factory_ref, mut factory_runner) = actor::run(
                FactoryActor::<TestFactoryDeps>::new(alloc_ref, /* require_gpu= */ false),
            )
            .await;

            let mut workers = Vec::new();
            for i in 0..num_workers {
                let worker_id = WorkerId::new_v4();
                let test_worker = TestWorker::default();
                let (worker_ref, worker_runner) = actor::run(test_worker.clone()).await;
                let remote_address: SocketAddr = format!("1.2.3.4:100{i}").parse().unwrap();
                factory_ref
                    .tell_with_runner(
                        GetTasks {
                            worker_id,
                            worker: Some(worker_ref),
                            remote_address: Some(remote_address),
                            kinds: vec![TaskKind::Execute],
                        },
                        &mut factory_runner,
                    )
                    .await
                    .unwrap();

                workers.push(FixtureWorker {
                    id: worker_id,
                    test_worker,
                    worker_runner,
                    remote_address,
                });
            }

            workers.sort_by_key(|w| w.id);

            let test_job = TestJob::default();
            let (job_ref, job_runner) = actor::run(test_job.clone()).await;

            Self {
                factory_ref,
                factory_runner,
                test_alloc,
                alloc_runner,
                workers,
                job_ref,
                job_runner,
                test_job,
            }
        }

        async fn disconnect_worker(&mut self, worker_id: WorkerId) {
            let worker_idx = self.workers.iter().position(|w| w.id == worker_id).unwrap();
            let worker = self.workers.remove(worker_idx);
            let remote_address = worker.remote_address;
            drop(worker);

            self.factory_ref
                .tell(RpcDisconnect { remote_address })
                .await
                .unwrap();
        }

        fn worker(&self, worker_id: WorkerId) -> &FixtureWorker {
            self.workers.iter().find(|w| w.id == worker_id).unwrap()
        }

        fn worker_mut(&mut self, worker_id: WorkerId) -> &mut FixtureWorker {
            self.workers.iter_mut().find(|w| w.id == worker_id).unwrap()
        }
    }

    impl Drop for Fixture {
        fn drop(&mut self) {
            assert!(!self.factory_runner.has_messages());

            assert_eq!(self.factory_ref.stop_reason(), None);

            assert!(!self.alloc_runner.has_messages());
            assert!(!self.job_runner.has_messages());

            for worker in &self.workers {
                assert!(!worker.worker_runner.has_messages());
            }
        }
    }

    fn test_exec_task() -> (TaskHeader, Task) {
        let task_id = GlobalId {
            job_id: JobId::new_v4(),
            task_id: 1,
        };

        let task_header = TaskHeader {
            global_id: task_id,
            task_kind: TaskKind::Execute,
        };
        let task = Task::Execute(Arc::new(ExecuteTask {
            request: ProofRequest {
                binary: vec![],
                input: vec![],
                assumptions: vec![],
                segment_limit_po2: None,
                execute_only: false,
            },
        }));

        (task_header, task)
    }

    async fn schedule_task_on_worker(
        fixture: &mut Fixture,
        worker_id: WorkerId,
        task_header: TaskHeader,
        task: Task,
    ) {
        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                task: task.clone(),
                tracing: Default::default(),
            })
            .await
            .unwrap();

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id }),
        );

        // Process SubmitTaskMsg
        fixture.factory_runner.try_handle_one().await.unwrap();

        // Process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        fixture
            .worker(worker_id)
            .test_worker
            .expect(TaskMsgExpectation {
                header: task_header.clone(),
                task: task.kind(),
                gpu_tokens: GpuTokens::ZERO,
                cores: CpuCores::from(1),
            });
        fixture
            .worker_mut(worker_id)
            .worker_runner
            .try_handle_one()
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn simple_task_schedule() {
        let mut fixture = Fixture::new(/* num_workers= */ 1).await;

        let worker1 = fixture.workers[0].id;
        let (task_header, task) = test_exec_task();
        schedule_task_on_worker(&mut fixture, worker1, task_header, task).await;
    }

    #[tokio::test]
    async fn allocator_schedule_error() {
        let mut fixture = Fixture::new(/* num_workers= */ 1).await;

        let worker1 = fixture.workers[0].id;
        let (task_header, task) = test_exec_task();

        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                task: task.clone(),
                tracing: Default::default(),
            })
            .await
            .unwrap();

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            Err(Error::new("no eligible candidate workers")),
        );

        // Process SubmitTaskMsg
        fixture.factory_runner.try_handle_one().await.unwrap();

        // Process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process TaskGotWorker, it should retry
        fixture.factory_runner.try_handle_one().await.unwrap();

        // this time we make it succeed
        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id: worker1 }),
        );
        // Process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        // worker1 gets the task
        fixture
            .worker(worker1)
            .test_worker
            .expect(TaskMsgExpectation {
                header: task_header.clone(),
                task: task.kind(),
                gpu_tokens: GpuTokens::ZERO,
                cores: CpuCores::from(1),
            });
        fixture
            .worker_mut(worker1)
            .worker_runner
            .try_handle_one()
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn schedule_task_no_worker() {
        let mut fixture = Fixture::new(/* num_workers= */ 0).await;

        let (task_header, task) = test_exec_task();

        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                tracing: Default::default(),
                task: task.clone(),
            })
            .await
            .unwrap();

        fixture.factory_runner.handle_one().await;
    }

    #[tokio::test]
    async fn schedule_task_missing_worker() {
        let mut fixture = Fixture::new(/* num_workers= */ 1).await;

        let (task_header, task) = test_exec_task();

        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                task: task.clone(),
                tracing: Default::default(),
            })
            .await
            .unwrap();

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            // reply with some worker the factory doesn't know about
            Ok(ScheduleTaskReply {
                worker_id: WorkerId::new_v4(),
            }),
        );

        // Process SubmitTaskMsg
        fixture.factory_runner.try_handle_one().await.unwrap();

        // Process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        let worker1 = fixture.workers[0].id;
        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            // reply with a worker it can use now
            Ok(ScheduleTaskReply { worker_id: worker1 }),
        );

        // Process 2nd ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process 2nd TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        fixture
            .worker(worker1)
            .test_worker
            .expect(TaskMsgExpectation {
                header: task_header.clone(),
                task: task.kind(),
                gpu_tokens: GpuTokens::ZERO,
                cores: CpuCores::from(1),
            });
        fixture
            .worker_mut(worker1)
            .worker_runner
            .try_handle_one()
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn worker_disconnect_before_scheduling_task() {
        let mut fixture = Fixture::new(/* num_workers= */ 2).await;

        let task_id = GlobalId {
            job_id: JobId::new_v4(),
            task_id: 1,
        };

        let task_header = TaskHeader {
            global_id: task_id,
            task_kind: TaskKind::Execute,
        };
        let task = Task::Execute(Arc::new(ExecuteTask {
            request: ProofRequest {
                binary: vec![],
                input: vec![],
                assumptions: vec![],
                segment_limit_po2: None,
                execute_only: false,
            },
        }));

        let worker1 = fixture.workers[0].id;
        let worker2 = fixture.workers[1].id;

        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                task: task.clone(),
                tracing: Default::default(),
            })
            .await
            .unwrap();

        fixture.disconnect_worker(worker1).await;

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: vec![worker1, worker2],
                task_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id: worker1 }),
        );

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: vec![worker2],
                task_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id: worker2 }),
        );

        // process SubmitTaskMsg
        fixture.factory_runner.try_handle_one().await.unwrap();

        // process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // process RpcDisconnect
        fixture.factory_runner.try_handle_one().await.unwrap();

        // process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        // process 2nd ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // process 2nd TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        fixture
            .worker(worker2)
            .test_worker
            .expect(TaskMsgExpectation {
                header: task_header.clone(),
                task: task.kind(),
                gpu_tokens: GpuTokens::ZERO,
                cores: CpuCores::from(1),
            });
        fixture
            .worker_mut(worker2)
            .worker_runner
            .try_handle_one()
            .await
            .unwrap();
    }

    #[tokio::test]
    async fn job_drop_before_scheduling_task() {
        let mut fixture = Fixture::new(/* num_workers= */ 2).await;

        let task_id = GlobalId {
            job_id: JobId::new_v4(),
            task_id: 1,
        };

        let task_header = TaskHeader {
            global_id: task_id,
            task_kind: TaskKind::Execute,
        };
        let task = Task::Execute(Arc::new(ExecuteTask {
            request: ProofRequest {
                binary: vec![],
                input: vec![],
                assumptions: vec![],
                segment_limit_po2: None,
                execute_only: false,
            },
        }));

        let worker1 = fixture.workers[0].id;
        let worker2 = fixture.workers[1].id;

        fixture
            .factory_ref
            .tell(SubmitTaskMsg {
                job: fixture.job_ref.clone(),
                header: task_header.clone(),
                task: task.clone(),
                tracing: Default::default(),
            })
            .await
            .unwrap();

        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: vec![worker1, worker2],
                task_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id: worker1 }),
        );

        fixture
            .factory_ref
            .tell(DropJob {
                job_id: task_id.job_id,
            })
            .await
            .unwrap();

        // process SubmitTaskMsg
        fixture.factory_runner.try_handle_one().await.unwrap();

        // process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // process DropJob
        fixture.factory_runner.try_handle_one().await.unwrap();

        // process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();
    }

    #[tokio::test]
    async fn factory_stop_while_running_task() {
        let mut fixture = Fixture::new(/* num_workers= */ 2).await;

        let worker1 = fixture.workers[0].id;

        let (task_header, task) = test_exec_task();
        schedule_task_on_worker(&mut fixture, worker1, task_header.clone(), task).await;

        fixture.factory_runner.stop().await;

        fixture.test_job.expect(TaskDoneMsg {
            header: task_header,
            payload: Err(Error::new("factory has stopped").into()),
        });
        fixture.job_runner.handle_one().await;
    }

    #[tokio::test]
    async fn worker_disconnect_while_running_task() {
        let mut fixture = Fixture::new(/* num_workers= */ 2).await;

        let worker1 = fixture.workers[0].id;
        let worker2 = fixture.workers[1].id;

        let (task_header, task) = test_exec_task();
        schedule_task_on_worker(&mut fixture, worker1, task_header.clone(), task.clone()).await;

        fixture.disconnect_worker(worker1).await;

        // show that when processing the disconnect, we reschedule the task on another worker.
        fixture.test_alloc.expect(
            ScheduleTask {
                candidates: fixture.workers.iter().map(|w| w.id).collect(),
                task_id: task_header.global_id,
                description: "Execute".into(),
            },
            Ok(ScheduleTaskReply { worker_id: worker2 }),
        );

        // Process RpcDisconnect
        fixture.factory_runner.try_handle_one().await.unwrap();

        // Process ScheduleTask
        fixture.alloc_runner.try_handle_one().await.unwrap();

        // Process TaskGotWorker
        fixture.factory_runner.try_handle_one().await.unwrap();

        fixture
            .worker(worker2)
            .test_worker
            .expect(TaskMsgExpectation {
                header: task_header.clone(),
                task: task.kind(),
                gpu_tokens: GpuTokens::ZERO,
                cores: CpuCores::from(1),
            });
        fixture
            .worker_mut(worker2)
            .worker_runner
            .try_handle_one()
            .await
            .unwrap();
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
