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

use std::{
    collections::{BTreeMap, VecDeque},
    sync::Arc,
};

use risc0_zkvm::{
    AssumptionReceipt, FakeReceipt, InnerReceipt, ProveKeccakRequest, Receipt, ReceiptClaim,
    Segment, SegmentReceipt, SuccinctReceipt, Unknown, sha::Digestible,
};
use tokio::time::Instant;

use super::{JobActorNew, tracer::JobTracer};
use crate::actors::{
    actor::{Actor, ActorRef, Context, Message, ReplySender, WeakActorRef},
    error::{Error, Result},
    factory::FactoryActor,
    protocol::{
        ExecuteTask, GlobalId, JobId, JobInfo, JobStatus, JobStatusReply, JobStatusRequest,
        JoinTask, LiftTask, ProofRequest, ProofResult, ProveKeccakTask, ProveSegmentTask,
        ResolveTask, SegmentIndex, SegmentRange, Session, Task, TaskError, TaskHeader, UnionTask,
        factory::{
            DropJob, JoinNode, ProveKeccakDone, SubmitTaskMsg, TaskDone, TaskDoneMsg, TaskUpdate,
            TaskUpdateMsg, UnionDone,
        },
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
    parent_ref: WeakActorRef<super::JobActor>,
    factory: ActorRef<FactoryActor>,
    joins: BTreeMap<SegmentRange, Arc<SuccinctReceipt<ReceiptClaim>>>,
    next_task_id: u64,
    session: Option<Arc<Session>>,
    reply_sender: Option<ReplySender<JobStatusReply>>,
    start_time: Instant,
    status: JobStatus<ProofResult>,
    unions: Vec<Vec<Option<UnknownReceipt>>>,
    keccak_phase: KeccakPhase,
    keccak_count: usize,
    required_keccak_layers: Vec<usize>,
    pending_keccak_peaks: VecDeque<UnknownReceipt>,
    keccak_root: Option<UnknownReceipt>,
    assumptions: Option<VecDeque<UnknownReceipt>>,
    final_receipt: Option<Arc<SuccinctReceipt<ReceiptClaim>>>,
    dev_mode: Option<bool>,

    tracer: JobTracer,
}

type UnknownReceipt = Arc<SuccinctReceipt<Unknown>>;

const ERR_DEV_MODE_DISABLED: &str =
    "zkVM: dev mode is disabled. Unset RISC0_DEV_MODE environment variable to produce valid proofs";

impl JobActor {
    async fn prove_keccak_done(
        &mut self,
        done: Arc<ProveKeccakDone>,
        self_ref: ActorRef<Self>,
    ) -> Result<()> {
        tracing::info!("ProveKeccakDone: {}", done.index);
        let receipt = Arc::new(done.receipt.clone());
        self.process_union(done.index, 0, receipt, self_ref).await?;
        Ok(())
    }

    async fn union_done(&mut self, done: Arc<UnionDone>, self_ref: ActorRef<Self>) -> Result<()> {
        let receipt = Arc::new(done.receipt.clone().into_unknown());
        match self.keccak_phase {
            KeccakPhase::Build => {
                tracing::info!("UnionDone: {}/{}", done.height, done.pos);
                self.process_union(done.pos, done.height, receipt, self_ref)
                    .await?;
            }
            KeccakPhase::MergePeaks => {
                if let Some(rhs) = self.pending_keccak_peaks.pop_front() {
                    self.union(0, 0, receipt, rhs).await?;
                } else {
                    assert!(self.keccak_root.is_none());
                    self.keccak_root = Some(receipt);
                    self.keccak_phase = KeccakPhase::Done;
                    tracing::info!("KeccakPhase::Done from UnionDone");
                    self.maybe_finish(self_ref).await?;
                }
            }
            KeccakPhase::Done => {
                return Err(Error::new("unexpected TaskDone::Union"));
            }
        };
        Ok(())
    }

    async fn process_union(
        &mut self,
        pos: usize,
        height: usize,
        receipt: UnknownReceipt,
        self_ref: ActorRef<Self>,
    ) -> Result<()> {
        if self.unions.len() < height + 1 {
            self.unions.resize_with(height + 1, Vec::new);
        }
        let layer = self
            .unions
            .get_mut(height)
            .ok_or_else(|| Error::new("union mismatch: bad height"))?;
        if layer.len() < pos + 1 {
            layer.resize(pos + 1, None);
        }
        *layer
            .get_mut(pos)
            .ok_or_else(|| Error::new("union mismatch: bad pos"))? = Some(receipt.clone());
        let (lhs_pos, rhs_pos) = if pos.is_multiple_of(2) {
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
            self.union(up_height, up_pos, lhs, rhs).await?;
        } else {
            self.maybe_finish(self_ref).await?;
        }
        Ok(())
    }

    fn dev_mode(&self) -> Result<bool> {
        let dev_mode = self
            .dev_mode
            .ok_or_else(|| Error::new("proof request should come first"))?;
        if dev_mode && cfg!(feature = "disable-dev-mode") {
            return Err(Error::new(ERR_DEV_MODE_DISABLED));
        }
        Ok(dev_mode)
    }

    async fn union(
        &mut self,
        height: usize,
        pos: usize,
        lhs: UnknownReceipt,
        rhs: UnknownReceipt,
    ) -> Result<()> {
        self.submit_task(Task::Union(Arc::new(UnionTask {
            height,
            pos,
            receipts: vec![lhs, rhs],
            dev_mode: self.dev_mode()?,
        })))
        .await?;
        Ok(())
    }
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
            reply_sender.send(JobStatusReply::Proof(info)).await;
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
        let tracer = JobTracer::new("proof_job", job_id);
        Self {
            job_id,
            parent_ref,
            factory,
            joins: BTreeMap::new(),
            next_task_id: 0,
            session: None,
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
            dev_mode: None,

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

    fn next_keccak_index(&mut self) -> usize {
        let ret = self.keccak_count;
        self.keccak_count += 1;
        ret
    }

    fn task_start(&mut self, header: TaskHeader) {
        let name = format!("{:?}", header.task_kind);
        self.tracer.span_start(header.global_id.task_id, name);
    }

    async fn prove_segment(&mut self, header: TaskHeader, segment: Segment) -> Result<()> {
        self.tracer.span_event(header, "segment");
        tracing::info!("ProveSegment: {}", segment.index);
        self.submit_task(Task::ProveSegment(Arc::new(ProveSegmentTask {
            segment,
            dev_mode: self.dev_mode()?,
        })))
        .await?;
        Ok(())
    }

    async fn prove_keccak(&mut self, request: ProveKeccakRequest) -> Result<()> {
        tracing::info!("ProveKeccak: {} hashes", request.input.len());
        let index = self.next_keccak_index();
        self.submit_task(Task::ProveKeccak(Arc::new(ProveKeccakTask {
            index,
            request,
            dev_mode: self.dev_mode()?,
        })))
        .await?;
        Ok(())
    }

    async fn session_done(
        &mut self,
        session: Arc<Session>,
        self_ref: ActorRef<Self>,
    ) -> Result<()> {
        tracing::info!("SessionDone");
        for ref receipt in session.assumptions.iter() {
            tracing::info!("{receipt:#?}");
        }
        self.session = Some(session);
        self.required_keccak_layers = mmr_layers(self.keccak_count);
        self.maybe_finish(self_ref).await?;
        Ok(())
    }

    async fn prove_segment_done(
        &mut self,
        receipt: Box<SegmentReceipt>,
        segment_range: SegmentRange,
    ) -> Result<()> {
        tracing::info!("ProveSegmentDone: {segment_range:?}");
        self.submit_task(Task::Lift(Arc::new(LiftTask {
            receipt: *receipt,
            segment_range,
            dev_mode: self.dev_mode()?,
        })))
        .await?;
        Ok(())
    }

    async fn lift_done(&mut self, node: Box<JoinNode>, self_ref: ActorRef<Self>) -> Result<()> {
        tracing::info!("LiftDone: {:?}", node.range);
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join().await?;
        self.maybe_finish(self_ref).await?;
        Ok(())
    }

    async fn join_done(&mut self, node: Box<JoinNode>, self_ref: ActorRef<Self>) -> Result<()> {
        tracing::info!("JoinDone: {:?}", node.range);
        self.joins.insert(node.range, Arc::new(node.receipt));
        self.maybe_join().await?;
        self.maybe_finish(self_ref).await?;
        Ok(())
    }

    async fn resolve_done(
        &mut self,
        receipt: Arc<SuccinctReceipt<ReceiptClaim>>,
        self_ref: ActorRef<Self>,
    ) -> Result<()> {
        self.final_receipt = Some(receipt);
        self.maybe_finish(self_ref).await?;
        Ok(())
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
                .ok_or_else(|| Error::new("parent job has stopped"))?,
            task,
            tracing: self.tracer.saved_task_context(task_id),
            header,
        };
        self.factory.tell(msg).await?;

        Ok(())
    }

    async fn maybe_join(&mut self) -> Result<()> {
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
            self.submit_task(Task::Join(Arc::new(JoinTask {
                range,
                receipts,
                dev_mode: self.dev_mode()?,
            })))
            .await?;
        }
        Ok(())
    }

    async fn resolve_assumptions(
        &mut self,
        session: &Arc<Session>,
        final_receipt: &Arc<SuccinctReceipt<ReceiptClaim>>,
    ) -> Result<bool> {
        if self.assumptions.is_none() {
            let mut assumptions = VecDeque::new();
            for receipt in session.assumptions.iter() {
                match receipt.as_ref() {
                    AssumptionReceipt::Proven(inner) => {
                        tracing::info!("Adding proven assumption: {:?}", inner.claim_digest());
                        assumptions.push_back(Arc::new(inner.succinct()?.clone()));
                    }
                    AssumptionReceipt::Unresolved(assumption) => {
                        if let Some(keccak_root) = self.keccak_root.clone()
                            && keccak_root.claim.digest() == assumption.claim
                        {
                            tracing::info!("Using keccak_root");
                            assumptions.push_back(keccak_root);
                            continue;
                        }

                        return Err(Error::new(format!("Missing assumption: {assumption:?}")));
                    }
                }
            }
            self.assumptions = Some(assumptions);
        }
        let assumptions = self
            .assumptions
            .as_mut()
            .expect("previous code should have set assumptions to Some");

        if let Some(assumption) = assumptions.pop_front() {
            tracing::info!("Resolve: {:?}", assumption.claim.digest());
            self.submit_task(Task::Resolve(Arc::new(ResolveTask {
                conditional: final_receipt.clone(),
                assumption: assumption.clone(),
                dev_mode: self.dev_mode()?,
            })))
            .await?;

            return Ok(false);
        }

        Ok(true)
    }

    async fn finish(
        &mut self,
        session: &Arc<Session>,
        final_receipt: Arc<SuccinctReceipt<ReceiptClaim>>,
        self_ref: ActorRef<Self>,
    ) -> Result<()> {
        tracing::info!("done");

        let journal_bytes = session
            .journal
            .clone()
            .ok_or_else(|| Error::new("missing journal"))?
            .bytes;
        let receipt = if self.dev_mode()? {
            Receipt::new(
                FakeReceipt::new(final_receipt.claim.clone()).into(),
                journal_bytes,
            )
        } else {
            Receipt::new(
                InnerReceipt::Succinct(final_receipt.as_ref().clone()),
                journal_bytes,
            )
        };

        let result = ProofResult {
            session: session.clone(),
            receipt: Some(Arc::new(receipt)),
        };

        self.status = JobStatus::Succeeded(result);

        // on_stop will reply
        let _ = self_ref.stop_gracefully("job shutdown");

        Ok(())
    }

    async fn maybe_finish(&mut self, self_ref: ActorRef<Self>) -> Result<()> {
        if self.session.is_some() && !self.maybe_finish_keccak_mmr().await? {
            return Ok(());
        }

        let Some(session) = self.session.clone() else {
            return Ok(());
        };

        let Some(join_root) = self.join_root(&session)? else {
            return Ok(());
        };

        let final_receipt = self
            .final_receipt
            .get_or_insert_with(|| join_root.clone())
            .clone();

        if !self.resolve_assumptions(&session, &final_receipt).await? {
            return Ok(());
        }

        self.finish(&session, final_receipt, self_ref).await?;

        Ok(())
    }

    fn join_root(
        &self,
        session: &Arc<Session>,
    ) -> Result<Option<Arc<SuccinctReceipt<ReceiptClaim>>>> {
        if let Some((range, join_root)) = self.joins.first_key_value()
            && range.start == SegmentIndex::ZERO
            && range.end == SegmentIndex::new(session.stats.segments, 0)
        {
            if self.dev_mode()? {
                let mut join_root = SuccinctReceipt::clone(join_root);
                join_root.claim = session.receipt_claim.clone().into();
                return Ok(Some(Arc::new(join_root)));
            }
            return Ok(Some(join_root.clone()));
        }
        Ok(None)
    }

    async fn maybe_finish_keccak_mmr(&mut self) -> Result<bool> {
        if self.keccak_count == 0 || self.keccak_phase == KeccakPhase::Done {
            self.keccak_phase = KeccakPhase::Done;
            return Ok(true);
        }

        if self.keccak_phase == KeccakPhase::Build {
            if self.unions.is_empty() || self.unions[0].len() != self.keccak_count {
                return Ok(false);
            }

            tracing::debug!("required: {:?}", self.required_keccak_layers);
            tracing::debug!(
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
                return Ok(false);
            }

            for layer_pos in mmr_peaks(&self.required_keccak_layers) {
                let receipt = self
                    .unions
                    .get(layer_pos)
                    .ok_or_else(|| Error::new("union mismatch: wrong length"))?
                    .last()
                    .ok_or_else(|| Error::new("union mismatch: empty layer"))?
                    .clone()
                    .ok_or_else(|| Error::new("union mismatch: missing receipt"))?;
                self.pending_keccak_peaks.push_back(receipt);
            }

            if self.pending_keccak_peaks.len() > 1 {
                let lhs = self
                    .pending_keccak_peaks
                    .pop_front()
                    .expect("len should be > 1");
                let rhs = self
                    .pending_keccak_peaks
                    .pop_front()
                    .expect("len should be > 1");
                self.union(0, 0, lhs, rhs).await?;
                self.keccak_phase = KeccakPhase::MergePeaks;
            }
        }

        if self.keccak_phase == KeccakPhase::MergePeaks {
            tracing::info!("MergePeaks");
            return Ok(false);
        }

        if self.pending_keccak_peaks.len() == 1 {
            if self.keccak_root.is_some() {
                return Err(Error::new("completed keccak root twice"));
            }
            self.keccak_root = Some(
                self.pending_keccak_peaks
                    .pop_front()
                    .expect("len should be == 1"),
            );
            self.keccak_phase = KeccakPhase::Done;
            tracing::info!("KeccakPhase::Done from Singleton");
        }

        Ok(true)
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

impl Message<ProofRequest> for JobActor {
    type Reply = JobStatusReply;

    async fn handle(&mut self, request: ProofRequest, ctx: &mut Context<Self, Self::Reply>) {
        let res = self.handle_proof(request, ctx).await;
        self.maybe_fail(ctx.actor_ref(), res).await;
    }
}

impl JobActor {
    async fn handle_proof(
        &mut self,
        request: ProofRequest,
        ctx: &mut Context<Self, JobStatusReply>,
    ) -> Result<()> {
        tracing::info!("ProofRequest");

        if self.reply_sender.is_some() {
            return Err(Error::new("received duplicate ProofRequest"));
        }
        self.reply_sender = ctx.reply_sender();
        self.dev_mode = Some(request.dev_mode);

        self.submit_task(Task::Execute(Arc::new(ExecuteTask { request })))
            .await?;
        Ok(())
    }
}

impl Message<TaskUpdateMsg> for JobActor {
    type Reply = ();

    async fn handle(
        &mut self,
        msg: TaskUpdateMsg,
        ctx: &mut Context<Self, Self::Reply>,
    ) -> Self::Reply {
        let res = self.handle_task_update(msg).await;
        self.maybe_fail(ctx.actor_ref(), res).await;
    }
}

impl JobActor {
    async fn handle_task_update(&mut self, msg: TaskUpdateMsg) -> Result<()> {
        match msg.payload {
            TaskUpdate::Start => {}
            TaskUpdate::Segment(segment) => self.prove_segment(msg.header, segment).await?,
            TaskUpdate::Keccak(request) => self.prove_keccak(request).await?,
            TaskUpdate::SegmentReceipt(receipt, segment_range) => {
                self.prove_segment_done(receipt, segment_range).await?
            }
        };
        Ok(())
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
            TaskDone::Session(session) => self.session_done(session, self_ref).await?,
            TaskDone::ProveSegment => {}
            TaskDone::ProveKeccak(done) => self.prove_keccak_done(done, self_ref).await?,
            TaskDone::Lift(node) => self.lift_done(node, self_ref).await?,
            TaskDone::Join(node) => self.join_done(node, self_ref).await?,
            TaskDone::Union(done) => self.union_done(done, self_ref).await?,
            TaskDone::Resolve(receipt) => self.resolve_done(receipt, self_ref).await?,
            TaskDone::ShrinkWrap(_) => {
                return Err(
                    Error::new("Proof JobActor received unexpected TaskDone::ShrinkWrap").into(),
                );
            }
        };
        Ok(())
    }
}

impl Message<JobStatusRequest> for JobActor {
    type Reply = Result<JobStatusReply>;

    async fn handle(&mut self, _msg: JobStatusRequest, ctx: &mut Context<Self, Self::Reply>) {
        ctx.reply(Ok(JobStatusReply::Proof(JobInfo {
            status: self.status.clone(),
            elapsed_time: self.start_time.elapsed(),
        })))
        .await
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
