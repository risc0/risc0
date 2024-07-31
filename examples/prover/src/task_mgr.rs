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

use risc0_zkvm::{Asset, ReceiptClaim, SuccinctReceipt};
use workerpool::Pool;

use crate::{
    plan::{Command, Task},
    worker::Worker,
};

type TaskNumber = usize;

pub enum JobKind {
    Segment(Asset),
    Join(SuccinctReceipt<ReceiptClaim>, SuccinctReceipt<ReceiptClaim>),
    Receipt(SuccinctReceipt<ReceiptClaim>),
}

pub struct Job {
    pub task: Task,
    pub kind: JobKind,
}

pub struct TaskManager {
    segments: HashMap<u32, Asset>,
    receipts: HashMap<TaskNumber, SuccinctReceipt<ReceiptClaim>>,
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
            receipts: HashMap::new(),
            pending_tasks: BTreeMap::new(),
            completed: HashSet::new(),
            pool: Pool::new(4),
            job_tx,
            job_rx,
        }
    }

    pub fn add_segment(&mut self, idx: u32, segment: Asset) {
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

    pub fn run(&mut self) -> SuccinctReceipt<ReceiptClaim> {
        let mut root_receipt = None;
        for job in self.job_rx.iter() {
            let job_id = job.task.task_number;
            let receipt = match job.kind {
                JobKind::Receipt(receipt) => receipt.clone(),
                _ => unreachable!(),
            };
            self.receipts.insert(job_id, receipt.clone());
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
        root_receipt.unwrap()
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
                    kind: JobKind::Join(left.clone(), right.clone()),
                }
            }
            Command::Finalize => {
                let receipt = self.receipts.get(&task.depends_on[0]).unwrap();
                Job {
                    task,
                    kind: JobKind::Receipt(receipt.clone()),
                }
            }
        };
        self.pool.execute_to(self.job_tx.clone(), job);
    }
}
