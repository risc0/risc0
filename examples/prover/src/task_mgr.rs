// Copyright 2024 RISC Zero, Inc.
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
    collections::{BTreeMap, HashMap, HashSet},
    sync::mpsc::{Receiver, Sender},
};

use risc0_zkvm::{
    ApiClient, Asset, AssetRequest, ProveKeccakRequest, ProverOpts, ReceiptClaim, SuccinctReceipt,
    Unknown,
};
use workerpool::Pool;

use crate::plan::{Command, Task};

type TaskNumber = usize;

#[allow(dead_code)]
pub enum JobKind<ReceiptType, SegmentType>
where
    ReceiptType: Clone,
    SegmentType: Clone,
{
    Segment(SegmentType),
    Join(Box<(ReceiptType, ReceiptType)>),
    Receipt(Box<ReceiptType>),
}

pub struct Job<ReceiptType, SegmentType>
where
    ReceiptType: Clone,
    SegmentType: Clone,
{
    pub task: Task,
    pub kind: JobKind<ReceiptType, SegmentType>,
}

impl Job<SuccinctReceipt<ReceiptClaim>, Asset> {
    pub fn execute(self) -> Self {
        match self.kind {
            JobKind::Segment(segment) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(Self::prove_and_lift(segment))),
            },
            JobKind::Join(pair) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(Self::join(pair.0, pair.1))),
            },
            JobKind::Receipt(receipt) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(*receipt)),
            },
        }
    }

    fn prove_and_lift(segment: Asset) -> SuccinctReceipt<ReceiptClaim> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();

        let segment_receipt = client
            .prove_segment(&opts, segment, AssetRequest::Inline)
            .unwrap();

        let segment_receipt_asset = segment_receipt.try_into().unwrap();
        client
            .lift(&opts, segment_receipt_asset, AssetRequest::Inline)
            .unwrap()
    }

    fn join(
        left: SuccinctReceipt<ReceiptClaim>,
        right: SuccinctReceipt<ReceiptClaim>,
    ) -> SuccinctReceipt<ReceiptClaim> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();
        let left_asset = left.try_into().unwrap();
        let right_asset = right.try_into().unwrap();
        client
            .join(&opts, left_asset, right_asset, AssetRequest::Inline)
            .unwrap()
    }
}

impl Job<SuccinctReceipt<Unknown>, ProveKeccakRequest> {
    pub fn execute(self) -> Self {
        match self.kind {
            JobKind::Segment(proof_request) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(Self::keccak(proof_request))),
            },
            JobKind::Join(pair) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(Self::union(pair.0, pair.1))),
            },
            JobKind::Receipt(receipt) => Job {
                task: self.task.clone(),
                kind: JobKind::Receipt(Box::new(*receipt)),
            },
        }
    }

    fn keccak(proof_request: ProveKeccakRequest) -> SuccinctReceipt<Unknown> {
        let client = ApiClient::from_env().unwrap();
        client
            .prove_keccak(proof_request, AssetRequest::Inline)
            .unwrap()
    }

    fn union(
        left: SuccinctReceipt<Unknown>,
        right: SuccinctReceipt<Unknown>,
    ) -> SuccinctReceipt<Unknown> {
        let opts = ProverOpts::default();
        let client = ApiClient::from_env().unwrap();
        let left_asset = left.try_into().unwrap();
        let right_asset = right.try_into().unwrap();
        client
            .union(&opts, left_asset, right_asset, AssetRequest::Inline)
            .unwrap()
            .into_unknown()
    }
}

pub struct TaskManager<ReceiptType, SegmentType, WorkerType>
where
    ReceiptType: Clone,
    SegmentType: Clone,
    WorkerType: workerpool::Worker,
{
    segments: HashMap<u32, SegmentType>,
    receipts: HashMap<TaskNumber, ReceiptType>,
    pending_tasks: BTreeMap<TaskNumber, Task>,
    completed: HashSet<TaskNumber>,
    pool: Pool<WorkerType>,
    job_tx: Sender<Job<ReceiptType, SegmentType>>,
    job_rx: Receiver<Job<ReceiptType, SegmentType>>,
}

impl<ReceiptType, SegmentType, WorkerType> TaskManager<ReceiptType, SegmentType, WorkerType>
where
    ReceiptType: Clone,
    SegmentType: Clone,
    WorkerType: workerpool::Worker<
        Input = Job<ReceiptType, SegmentType>,
        Output = Job<ReceiptType, SegmentType>,
    >,
{
    pub fn new() -> Self {
        let (job_tx, job_rx) = std::sync::mpsc::channel();
        Self {
            segments: HashMap::new(),
            receipts: HashMap::new(),
            pending_tasks: BTreeMap::new(),
            completed: HashSet::new(),
            pool: Pool::new(1),
            job_tx,
            job_rx,
        }
    }

    pub fn add_segment(&mut self, idx: u32, segment: SegmentType) {
        self.segments.insert(idx, segment);
    }

    pub fn add_task(&mut self, task: Task) {
        let deps = HashSet::from_iter(task.depends_on.iter().cloned());
        if self.completed.is_superset(&deps) {
            self.run_task(task);
        } else {
            self.pending_tasks.insert(task.task_number, task);
        }
    }

    pub fn run(&mut self) -> ReceiptType {
        let mut root_receipt = None;
        for job in self.job_rx.iter() {
            let job_id = job.task.task_number;
            let receipt = match job.kind {
                JobKind::Receipt(receipt) => receipt.clone(),
                _ => unreachable!(),
            };
            self.receipts.insert(job_id, *receipt.clone());
            self.completed.insert(job_id);
            let ready_tasks = self.collect_ready_tasks();
            for next_task in ready_tasks {
                self.pending_tasks.remove(&next_task.task_number);
                self.run_task(next_task);
            }
            if job.task.command == Command::Finalize {
                root_receipt = Some(receipt);
                break;
            }
        }
        *root_receipt.unwrap()
    }

    fn collect_ready_tasks(&self) -> Vec<Task> {
        self.pending_tasks
            .values()
            .filter(|task| {
                let deps = HashSet::from_iter(task.depends_on.iter().cloned());
                self.completed.is_superset(&deps)
            })
            .cloned()
            .collect()
    }

    fn run_task(&self, task: Task) {
        let job = match task.command {
            Command::Segment => {
                let segment = self.segments.get(&task.segment_idx.unwrap()).unwrap();
                Job {
                    task,
                    kind: JobKind::Segment(segment.clone()),
                }
            }
            Command::Join => {
                let left = self.receipts.get(&task.depends_on[0]).unwrap();
                let right = self.receipts.get(&task.depends_on[1]).unwrap();
                Job {
                    task,
                    kind: JobKind::Join(Box::new((left.clone(), right.clone()))),
                }
            }
            Command::Finalize => {
                let receipt = self.receipts.get(&task.depends_on[0]).unwrap();
                Job {
                    task,
                    kind: JobKind::Receipt(Box::new(receipt.clone())),
                }
            }
            Command::FinalizeProofSet => todo!(),
            Command::Keccak => todo!(),
            Command::Union => todo!(),
        };
        self.pool.execute_to(self.job_tx.clone(), job);
    }
}
