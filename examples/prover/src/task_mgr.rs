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

use crate::{
    plan::{Command, Task},
    worker::Worker,
};

type TaskNumber = usize;

pub enum JobKind {
    Segment(Asset),
    Join(Box<(SuccinctReceipt<ReceiptClaim>, SuccinctReceipt<ReceiptClaim>)>),
    Receipt(Box<SuccinctReceipt<ReceiptClaim>>),
    KeccakSegment(ProveKeccakRequest),
    ZkrReceipt(Box<SuccinctReceipt<Unknown>>),
    Union(Box<(SuccinctReceipt<Unknown>, SuccinctReceipt<Unknown>)>),
}

pub struct Job {
    pub task: Task,
    pub kind: JobKind,
}

impl Job {
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
            JobKind::KeccakSegment(proof_request) => Job {
                task: self.task.clone(),
                kind: JobKind::ZkrReceipt(Box::new(Self::keccak(proof_request))),
            },
            JobKind::ZkrReceipt(receipt) => Job {
                task: self.task.clone(),
                kind: JobKind::ZkrReceipt(Box::new(*receipt)),
            },
            JobKind::Union(pair) => Job {
                task: self.task.clone(),
                kind: JobKind::ZkrReceipt(Box::new(Self::union(pair.0, pair.1))),
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

//impl Job<SuccinctReceipt<Unknown>, ProveKeccakRequest> {
//    pub fn execute(self) -> Self {
//        println!("executing...");
//        match self.kind {
//            JobKind::Segment(proof_request) => Job {
//                task: self.task.clone(),
//                kind: JobKind::Receipt(Box::new(Self::keccak(proof_request))),
//            },
//            JobKind::Join(pair) => Job {
//                task: self.task.clone(),
//                kind: JobKind::Receipt(Box::new(Self::union(pair.0, pair.1))),
//            },
//            JobKind::Receipt(receipt) => {
//                println!("matched with receipt");
//                Job {
//                    task: self.task.clone(),
//                    kind: JobKind::Receipt(Box::new(*receipt)),
//                }
//            }
//        }
//    }
//

//}

pub struct TaskManager {
    segments: HashMap<u32, Asset>,
    keccak_segments: HashMap<u32, ProveKeccakRequest>,
    receipts: HashMap<TaskNumber, SuccinctReceipt<ReceiptClaim>>,
    zkr_receipts: HashMap<TaskNumber, SuccinctReceipt<Unknown>>,
    pending_tasks: BTreeMap<TaskNumber, Task>,
    completed: HashSet<TaskNumber>,
    pool: Pool<Worker>,
    job_tx: Sender<Job>,
    job_rx: Receiver<Job>,
}

impl TaskManager {
    pub fn new() -> Self {
        let (job_tx, job_rx) = std::sync::mpsc::channel();
        Self {
            segments: HashMap::new(),
            keccak_segments: HashMap::new(),
            receipts: HashMap::new(),
            zkr_receipts: HashMap::new(),
            pending_tasks: BTreeMap::new(),
            completed: HashSet::new(),
            pool: Pool::new(1),
            job_tx,
            job_rx,
        }
    }

    pub fn add_segment(&mut self, idx: u32, segment: Asset) {
        self.segments.insert(idx, segment);
    }

    pub fn add_keccak_segment(&mut self, idx: u32, segment: ProveKeccakRequest) {
        self.keccak_segments.insert(idx, segment);
    }

    pub fn add_task(&mut self, task: Task) {
        let deps = HashSet::from_iter(task.depends_on.iter().cloned());
        if self.completed.is_superset(&deps) {
            self.run_task(task);
        } else {
            self.pending_tasks.insert(task.task_number, task);
        }
    }

    pub fn run(
        &mut self,
    ) -> (
        SuccinctReceipt<ReceiptClaim>,
        Option<SuccinctReceipt<Unknown>>,
    ) {
        let mut root_receipt = None;
        let mut root_zkr_receipt = None;
        for job in self.job_rx.iter() {
            let job_id = job.task.task_number;
            match job.kind {
                JobKind::Receipt(receipt) => {
                    self.receipts.insert(job_id, *receipt.clone());
                    root_receipt = Some(receipt);
                }
                JobKind::ZkrReceipt(receipt) => {
                    self.zkr_receipts.insert(job_id, *receipt.clone());
                    // the very last receipt will be the root keccak receipt
                    root_zkr_receipt = Some(*receipt);
                }
                _ => unreachable!(),
            };
            self.completed.insert(job_id);
            let ready_tasks = self.collect_ready_tasks();
            for next_task in ready_tasks {
                self.pending_tasks.remove(&next_task.task_number);
                self.run_task(next_task);
            }
            if job.task.command == Command::Finalize {
                break;
            }
        }
        println!("run complete");
        (*root_receipt.unwrap(), root_zkr_receipt)
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
        println!("running task: {:?}", task);
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
            Command::FinalizeProofSet => {
                let receipt = self.zkr_receipts.get(&task.depends_on[0]).unwrap();
                Job {
                    task,
                    kind: JobKind::ZkrReceipt(Box::new(receipt.clone())),
                }
            }
            Command::Keccak => {
                let keccak_segment = self
                    .keccak_segments
                    .get(&task.segment_idx.unwrap())
                    .unwrap();
                Job {
                    task,
                    kind: JobKind::KeccakSegment(keccak_segment.clone()),
                }
            }
            Command::Union => {
                let left = self.zkr_receipts.get(&task.depends_on[0]).unwrap();
                let right = self.zkr_receipts.get(&task.depends_on[1]).unwrap();
                Job {
                    task,
                    kind: JobKind::Union(Box::new((left.clone(), right.clone()))),
                }
            }
        };
        self.pool.execute_to(self.job_tx.clone(), job);
    }
}
