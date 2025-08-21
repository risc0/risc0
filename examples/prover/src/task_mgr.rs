// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    collections::{BTreeMap, HashMap, HashSet},
    sync::mpsc::{Receiver, Sender},
};

use risc0_zkvm::{Asset, ProveKeccakRequest, ReceiptClaim, SuccinctReceipt, Unknown};
use workerpool::Pool;

use crate::{
    plan::{Command, Task},
    worker::Worker,
};

type TaskNumber = usize;

pub enum JobKind {
    Segment(Asset),
    Join(Box<(SuccinctReceipt<ReceiptClaim>, SuccinctReceipt<ReceiptClaim>)>),
    FinalizeJoins(Box<SuccinctReceipt<ReceiptClaim>>),
    Keccak(ProveKeccakRequest),
    Union(Box<(SuccinctReceipt<Unknown>, SuccinctReceipt<Unknown>)>),
    FinalizeUnions(Box<SuccinctReceipt<Unknown>>),
}

pub struct Job {
    pub task: Task,
    pub kind: JobKind,
}

pub struct TaskManager {
    segments: HashMap<u32, Asset>,
    keccak_segments: HashMap<u32, ProveKeccakRequest>,
    join_receipts: HashMap<TaskNumber, SuccinctReceipt<ReceiptClaim>>,
    union_receipts: HashMap<TaskNumber, SuccinctReceipt<Unknown>>,
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
            join_receipts: HashMap::new(),
            union_receipts: HashMap::new(),
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

    pub fn finish(
        &mut self,
    ) -> (
        SuccinctReceipt<ReceiptClaim>,
        Option<SuccinctReceipt<Unknown>>,
    ) {
        let mut join_root_receipt = None;
        let mut union_root_receipt = None;
        for job in self.job_rx.iter() {
            let job_id = job.task.task_number;
            match job.kind {
                JobKind::FinalizeJoins(receipt) => {
                    self.join_receipts.insert(job_id, *receipt.clone());
                    join_root_receipt = Some(receipt);
                }
                JobKind::FinalizeUnions(receipt) => {
                    self.union_receipts.insert(job_id, *receipt.clone());
                    // the very last receipt will be the union root receipt
                    union_root_receipt = Some(*receipt);
                }
                _ => unreachable!(),
            };
            self.completed.insert(job_id);
            let ready_tasks = self.collect_ready_tasks();
            for next_task in ready_tasks {
                self.pending_tasks.remove(&next_task.task_number);
                self.run_task(next_task);
            }
            if job.task.command == Command::FinalizeJoins {
                break;
            }
        }
        if let Some(ref receipt) = union_root_receipt {
            println!(
                "union root receipt: claim {:?} control id: {}",
                receipt.claim, receipt.control_id
            );
        }
        (*join_root_receipt.unwrap(), union_root_receipt)
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
                let left = self.join_receipts.get(&task.depends_on[0]).unwrap();
                let right = self.join_receipts.get(&task.depends_on[1]).unwrap();
                Job {
                    task,
                    kind: JobKind::Join(Box::new((left.clone(), right.clone()))),
                }
            }
            Command::FinalizeJoins => {
                let receipt = self.join_receipts.get(&task.depends_on[0]).unwrap();
                Job {
                    task,
                    kind: JobKind::FinalizeJoins(Box::new(receipt.clone())),
                }
            }
            Command::FinalizeUnions => {
                let receipt = self.union_receipts.get(&task.depends_on[0]).unwrap();
                Job {
                    task,
                    kind: JobKind::FinalizeUnions(Box::new(receipt.clone())),
                }
            }
            Command::Keccak => {
                let keccak_segment = self
                    .keccak_segments
                    .get(&task.segment_idx.unwrap())
                    .unwrap();
                Job {
                    task,
                    kind: JobKind::Keccak(keccak_segment.clone()),
                }
            }
            Command::Union => {
                let left = self.union_receipts.get(&task.depends_on[0]).unwrap();
                let right = self.union_receipts.get(&task.depends_on[1]).unwrap();
                Job {
                    task,
                    kind: JobKind::Union(Box::new((left.clone(), right.clone()))),
                }
            }
        };
        self.pool.execute_to(self.job_tx.clone(), job);
    }
}
