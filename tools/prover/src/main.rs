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

mod plan;
mod task_mgr;
mod worker;

use risc0_zkvm::{ExecutorEnv, ExecutorImpl, InnerReceipt, NullSegmentRef, Receipt};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

use self::{plan::Planner, task_mgr::TaskManager};

fn main() {
    println!("Submitting proof request...");

    let mut task_manager = TaskManager::new();
    let mut planner = Planner::default();

    let iterations = 100;
    let env = ExecutorEnv::builder()
        .write_slice(&[iterations])
        // Use a low segment size to generate more jobs in this example.
        .segment_limit_po2(15)
        .build()
        .unwrap();
    let mut exec = ExecutorImpl::from_elf(env, FIB_ELF).unwrap();
    let session = exec
        .run_with_callback(|segment| {
            planner.enqueue_segment(segment.index).unwrap();
            task_manager.add_segment(segment);
            while let Some(task) = planner.next_task() {
                task_manager.add_task(task.clone());
            }
            Ok(Box::new(NullSegmentRef))
        })
        .unwrap();

    planner.finish().unwrap();

    println!("Plan:");
    println!("{planner:?}");

    while let Some(task) = planner.next_task() {
        task_manager.add_task(task.clone());
    }

    let root_receipt = task_manager.run();
    let receipt = Receipt::new(
        InnerReceipt::Succinct(root_receipt),
        session.journal.unwrap().bytes.clone(),
    );
    receipt.verify(FIB_ID).unwrap();
    println!("Receipt verified!");
}
