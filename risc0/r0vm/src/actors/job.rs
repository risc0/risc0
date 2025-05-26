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

use std::{
    borrow::Cow,
    collections::{BTreeMap, HashMap, VecDeque},
    sync::Arc,
};

use kameo::{error::Infallible, prelude::*};
use opentelemetry::{
    global::{BoxedSpan, BoxedTracer},
    trace::{Span, SpanKind, TraceContextExt as _, Tracer},
    KeyValue,
};
use risc0_zkvm::{
    sha::Digestible, AssumptionReceipt, InnerReceipt, ProveKeccakRequest, Receipt, ReceiptClaim,
    Segment, SegmentReceipt, SuccinctReceipt, Unknown,
};
use tokio::time::Instant;

use super::{
    factory::FactoryActor,
    protocol::{
        factory::{
            DropJob, JoinNode, ProveKeccakDone, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdate,
            TaskUpdateMsg, UnionDone,
        },
        ExecuteTask, GlobalId, JobId, JobInfo, JobStatus, JobStatusReply, JobStatusRequest,
        JoinTask, LiftTask, ProofRequest, ProofResult, ProveKeccakTask, ProveSegmentTask,
        ResolveTask, SegmentRange, Session, Task, TaskError, TaskHeader, TaskId, UnionTask,
    },
};

#[derive(PartialEq)]
enum KeccakPhase {
    Build,
    MergePeaks,
    Done,
}

pub(crate) struct JobActor {
    job_id: JobId,
    self_ref: Option<WeakActorRef<Self>>,
    factory: ActorRef<FactoryActor>,
    joins: BTreeMap<SegmentRange, Arc<SuccinctReceipt<ReceiptClaim>>>,
    next_task_id: u64,
    session: Option<Arc<Session>>,
    ctx: opentelemetry::Context,
    tracer: BoxedTracer,
    pending_spans: HashMap<TaskId, BoxedSpan>,
    reply_sender: Option<ReplySender<JobStatusReply>>,
    start_time: Instant,
    status: JobStatus,
    unions: Vec<Vec<Option<UnknownReceipt>>>,
    keccak_phase: KeccakPhase,
    keccak_count: usize,
    required_keccak_layers: Vec<usize>,
    pending_keccak_peaks: VecDeque<UnknownReceipt>,
    keccak_root: Option<UnknownReceipt>,
    assumptions: Option<VecDeque<UnknownReceipt>>,
    final_receipt: Option<Arc<SuccinctReceipt<ReceiptClaim>>>,
}

type UnknownReceipt = Arc<SuccinctReceipt<Unknown>>;

impl JobActor {
    async fn prove_keccak_done(&mut self, done: Arc<ProveKeccakDone>) {
        tracing::info!("ProveKeccakDone: {}", done.index);
        let receipt = Arc::new(done.receipt.clone());
        self.process_union(done.index, 0, receipt).await;
    }

    async fn union_done(&mut self, done: Arc<UnionDone>) {
        let receipt = Arc::new(done.receipt.clone().into_unknown());
        match self.keccak_phase {
            KeccakPhase::Build => {
                tracing::info!("UnionDone: {}/{}", done.height, done.pos);
                self.process_union(done.pos, done.height, receipt).await;
            }
            KeccakPhase::MergePeaks => {
                if let Some(rhs) = self.pending_keccak_peaks.pop_front() {
                    self.union(0, 0, receipt, rhs).await;
                } else {
                    assert!(self.keccak_root.is_none());
                    self.keccak_root = Some(receipt);
                    self.keccak_phase = KeccakPhase::Done;
                    tracing::info!("KeccakPhase::Done from UnionDone");
                    self.maybe_finish().await;
                }
            }
            KeccakPhase::Done => {
                unreachable!();
            }
        }
    }

    async fn process_union(&mut self, pos: usize, height: usize, receipt: UnknownReceipt) {
        if self.unions.len() < height + 1 {
            self.unions.resize_with(height + 1, Vec::new);
        }
        let layer = self.unions.get_mut(height).unwrap();
        if layer.len() < pos + 1 {
            layer.resize(pos + 1, None);
        }
        layer[pos] = Some(receipt.clone());
        let (lhs_pos, rhs_pos) = if pos % 2 == 0 {
            (pos, pos + 1)
        } else {
            (pos - 1, pos)
        };
        if let (Some(Some(lhs)), Some(Some(rhs))) =
            (layer.get(lhs_pos).cloned(), layer.get(rhs_pos).cloned())
        {
            let up_height = height + 1;
            let up_pos = pos / 2;
            tracing::info!("Union: {height}/({lhs_pos}, {rhs_pos}) -> {up_height}/{up_pos}");
            self.union(up_height, up_pos, lhs, rhs).await;
        } else {
            self.maybe_finish().await;
        }
    }

    async fn union(&mut self, height: usize, pos: usize, lhs: UnknownReceipt, rhs: UnknownReceipt) {
        self.submit_task(Task::Union(Arc::new(UnionTask {
            height,
            pos,
            receipts: vec![lhs, rhs],
        })))
        .await;
    }
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
        let span = self.ctx.span();

        if let ActorStopReason::Panicked(err) = reason {
            tracing::error!("{err}");
            span.record_error(&err);
            if let Some(reply_sender) = self.reply_sender.take() {
                let info = JobInfo {
                    status: JobStatus::Failed(TaskError::Generic(err.to_string())),
                    elapsed_time,
                };
                reply_sender.send(JobStatusReply { info: Some(info) });
            }
        } else if let Some(reply_sender) = self.reply_sender.take() {
            let info = JobInfo {
                status: self.status.clone(),
                elapsed_time,
            };
            reply_sender.send(JobStatusReply { info: Some(info) });
        }

        span.end();
        Ok(())
    }
}

impl JobActor {
    pub fn new(job_id: JobId, factory: ActorRef<FactoryActor>) -> Self {
        let tracer = opentelemetry::global::tracer("job");
        let span = tracer
            .span_builder("job")
            .with_kind(SpanKind::Client)
            .with_attributes([KeyValue::new("job_id", job_id.to_string())])
            .start(&tracer);
        let ctx = opentelemetry::Context::current_with_span(span);
        Self {
            job_id,
            self_ref: None,
            factory,
            joins: BTreeMap::new(),
            next_task_id: 0,
            session: None,
            ctx,
            tracer,
            pending_spans: HashMap::new(),
            reply_sender: None,
            start_time: Instant::now(),
            status: JobStatus::Running("init".to_string()),
            unions: Default::default(),
            keccak_count: 0,
            keccak_phase: KeccakPhase::Build,
            keccak_root: None,
            required_keccak_layers: Vec::new(),
            pending_keccak_peaks: VecDeque::new(),
            assumptions: None,
            final_receipt: None,
        }
    }

    fn self_ref(&self) -> ActorRef<Self> {
        self.self_ref.as_ref().unwrap().upgrade().unwrap()
    }

    fn next_task_id(&mut self) -> u64 {
        self.next_task_id += 1;
        self.next_task_id
    }

    fn next_keccak_index(&mut self) -> usize {
        let ret = self.keccak_count;
        self.keccak_count += 1;
        ret
    }

    fn span_start<T>(&mut self, task_id: TaskId, name: T)
    where
        T: Into<Cow<'static, str>>,
    {
        self.pending_spans
            .insert(task_id, self.tracer.start_with_context(name, &self.ctx));
    }

    fn span_end(&mut self, task_id: TaskId) {
        self.pending_spans.remove(&task_id).as_mut().unwrap().end();
    }

    async fn task_start(&mut self, header: TaskHeader) {
        self.pending_spans
            .get_mut(&header.global_id.task_id)
            .unwrap()
            .add_event("start", vec![]);
    }

    async fn prove_segment(&mut self, segment: Segment) {
        tracing::info!("ProveSegment: {}", segment.index);
        self.submit_task(Task::ProveSegment(Arc::new(ProveSegmentTask { segment })))
            .await;
    }

    async fn prove_keccak(&mut self, request: ProveKeccakRequest) {
        tracing::info!("ProveKeccak: {} hashes", request.input.len());
        let index = self.next_keccak_index();
        self.submit_task(Task::ProveKeccak(Arc::new(ProveKeccakTask {
            index,
            request,
        })))
        .await;
    }

    async fn session_done(&mut self, session: Arc<Session>) {
        tracing::info!("SessionDone");
        for ref receipt in session.assumptions.iter() {
            tracing::info!("{receipt:#?}");
        }
        self.session = Some(session);
        self.required_keccak_layers = mmr_layers(self.keccak_count);
        self.maybe_finish().await;
    }

    async fn prove_segment_done(&mut self, receipt: Box<SegmentReceipt>) {
        tracing::info!("ProveSegmentDone: {}", receipt.index);
        self.submit_task(Task::Lift(Arc::new(LiftTask { receipt: *receipt })))
            .await;
    }

    async fn lift_done(&mut self, node: Box<JoinNode>) {
        tracing::info!("LiftDone: {:?}", node.range);
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join().await;
        self.maybe_finish().await;
    }

    async fn join_done(&mut self, node: Box<JoinNode>) {
        tracing::info!("JoinDone: {:?}", node.range);
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join().await;
        self.maybe_finish().await;
    }

    async fn resolve_done(&mut self, receipt: Arc<SuccinctReceipt<ReceiptClaim>>) {
        self.final_receipt = Some(receipt);
        self.maybe_finish().await;
    }

    async fn submit_task(&mut self, task: Task) {
        let task_id = self.next_task_id();
        self.span_start(task_id, task.name());
        let msg = SubmitTaskMsg {
            job: self.self_ref(),
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

    async fn maybe_join(&mut self) {
        if let Some(((a_range, a_receipt), (b_range, b_receipt))) = self
            .joins
            .iter()
            .zip(self.joins.iter().skip(1))
            .filter(|((a, _), (b, _))| a.end == b.start)
            .map(|((a_range, a_receipt), (b_range, b_receipt))| {
                ((*a_range, a_receipt.clone()), (*b_range, b_receipt.clone()))
            })
            .take(1)
            .next()
        {
            self.joins.remove(&a_range);
            self.joins.remove(&b_range);
            let range = (a_range.start..b_range.end).into();
            let receipts = vec![(*a_receipt).clone(), (*b_receipt).clone()];
            self.submit_task(Task::Join(Arc::new(JoinTask { range, receipts })))
                .await;
        }
    }

    async fn maybe_finish(&mut self) {
        if self.session.is_some() && !self.maybe_finish_keccak_mmr().await {
            return;
        }

        if let Some(ref session) = self.session {
            // tracing::info!("maybe_finish: session done");

            if let Some(join_root) = self.join_root(session) {
                let final_receipt = self
                    .final_receipt
                    .get_or_insert_with(|| join_root.clone())
                    .clone();

                if self.assumptions.is_none() {
                    let mut assumptions = VecDeque::new();
                    for receipt in session.assumptions.iter() {
                        match receipt.as_ref() {
                            AssumptionReceipt::Proven(inner) => {
                                tracing::info!(
                                    "Adding proven assumption: {:?}",
                                    inner.claim_digest()
                                );
                                assumptions.push_back(Arc::new(inner.succinct().unwrap().clone()));
                            }
                            AssumptionReceipt::Unresolved(assumption) => {
                                if let Some(keccak_root) = self.keccak_root.clone() {
                                    if keccak_root.claim.digest() == assumption.claim {
                                        tracing::info!("Using keccak_root");
                                        assumptions.push_back(keccak_root);
                                        continue;
                                    }
                                }
                                panic!("Missing assumption: {assumption:?}");
                            }
                        }
                    }
                    self.assumptions = Some(assumptions);
                }

                let assumptions = self.assumptions.as_mut().unwrap();
                if let Some(assumption) = assumptions.pop_front() {
                    tracing::info!("Resolve: {:?}", assumption.claim.digest());
                    self.submit_task(Task::Resolve(Arc::new(ResolveTask {
                        conditional: final_receipt.clone(),
                        assumption: assumption.clone(),
                    })))
                    .await;
                    return;
                }

                tracing::info!("done");
                let receipt = Receipt::new(
                    InnerReceipt::Succinct(final_receipt.as_ref().clone()),
                    session.journal.clone().unwrap().bytes,
                );
                let result = ProofResult {
                    session: session.clone(),
                    receipt: Arc::new(receipt),
                };
                self.status = JobStatus::Succeeded(result);
                self.self_ref().stop_gracefully().await.unwrap();
            }
        }
    }

    fn join_root(&self, session: &Arc<Session>) -> Option<Arc<SuccinctReceipt<ReceiptClaim>>> {
        if let Some((range, join_root)) = self.joins.first_key_value() {
            if range.start == 0 && range.end == session.segment_count {
                return Some(join_root.clone());
            }
        }
        None
    }

    async fn maybe_finish_keccak_mmr(&mut self) -> bool {
        if self.keccak_count == 0 || self.keccak_phase == KeccakPhase::Done {
            self.keccak_phase = KeccakPhase::Done;
            return true;
        }

        if self.keccak_phase == KeccakPhase::Build {
            if self.unions.is_empty() || self.unions[0].len() != self.keccak_count {
                return false;
            }

            println!("required: {:?}", self.required_keccak_layers);
            println!(
                "actual:   {:?}",
                self.unions.iter().map(|x| x.len()).collect::<Vec<_>>()
            );
            if self.required_keccak_layers.len() != self.unions.len()
                || self
                    .required_keccak_layers
                    .iter()
                    .zip(self.unions.iter().map(|x| x.len()))
                    .any(|(x, y)| *x != y)
            {
                return false;
            }

            for layer_pos in mmr_peaks(&self.required_keccak_layers) {
                let receipt = self.unions[layer_pos].last().unwrap().clone().unwrap();
                self.pending_keccak_peaks.push_back(receipt);
            }

            if self.pending_keccak_peaks.len() > 1 {
                let lhs = self.pending_keccak_peaks.pop_front().unwrap();
                let rhs = self.pending_keccak_peaks.pop_front().unwrap();
                self.union(0, 0, lhs, rhs).await;
                self.keccak_phase = KeccakPhase::MergePeaks;
            }
        }

        if self.keccak_phase == KeccakPhase::MergePeaks {
            tracing::info!("MergePeaks");
            return false;
        }

        if self.pending_keccak_peaks.len() == 1 {
            assert!(self.keccak_root.is_none());
            self.keccak_root = Some(self.pending_keccak_peaks.pop_front().unwrap());
            self.keccak_phase = KeccakPhase::Done;
            tracing::info!("KeccakPhase::Done from Singleton");
        }

        true
    }
}

impl Message<ProofRequest> for JobActor {
    type Reply = DelegatedReply<JobStatusReply>;

    async fn handle(
        &mut self,
        request: ProofRequest,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        tracing::info!("ProofRequest");
        let (delegated_reply, reply_sender) = ctx.reply_sender();
        self.reply_sender = reply_sender;
        self.submit_task(Task::Execute(Arc::new(ExecuteTask { request })))
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
        // tracing::info!("TaskUpdateMsg: {}", msg.header.global_id.task_id);
        match msg.payload {
            TaskUpdate::Start => self.task_start(msg.header).await,
            TaskUpdate::Segment(segment) => self.prove_segment(segment).await,
            TaskUpdate::Keccak(request) => self.prove_keccak(request).await,
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
        // tracing::info!("TaskDoneMsg: {}", msg.header.global_id.task_id);
        let task_done = match msg.payload {
            Ok(task_done) => task_done,
            Err(err) => {
                self.status = JobStatus::Failed(err);
                let _ = _ctx.actor_ref().stop_gracefully().await;
                return;
            }
        };
        self.span_end(msg.header.global_id.task_id);
        match task_done {
            TaskDone::Session(session) => self.session_done(session).await,
            TaskDone::ProveSegment(receipt) => self.prove_segment_done(receipt).await,
            TaskDone::ProveKeccak(done) => self.prove_keccak_done(done).await,
            TaskDone::Lift(node) => self.lift_done(node).await,
            TaskDone::Join(node) => self.join_done(node).await,
            TaskDone::Union(done) => self.union_done(done).await,
            TaskDone::Resolve(receipt) => self.resolve_done(receipt).await,
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
        JobStatusReply {
            info: Some(JobInfo {
                status: self.status.clone(),
                elapsed_time: self.start_time.elapsed(),
            }),
        }
    }
}

fn mmr_layers(count: usize) -> Vec<usize> {
    let mut cur = count;
    let mut layers = vec![cur];
    while cur > 1 {
        cur /= 2;
        layers.push(cur);
    }
    layers
}

fn mmr_peaks(layers: &[usize]) -> VecDeque<usize> {
    let mut peaks = VecDeque::new();
    for (i, count) in layers.iter().enumerate().rev() {
        if count % 2 == 1 {
            peaks.push_back(i);
        }
    }
    peaks
}

#[test]
fn test_mmr_layers() {
    let test = |count| {
        let layers = mmr_layers(count);
        println!(
            "mmr_layers({count}) = {layers:?}, mmr_peaks = {:?}",
            mmr_peaks(&layers)
        );
    };

    test(0);
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    test(6);
    test(7);
    test(8);
    test(19);
    test(93);
}
