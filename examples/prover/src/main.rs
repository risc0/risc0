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

//! This is an example of how the public 1.0 API can be used to build a proving service.
//! It's not meant to be used in production since it doesn't handle failures.
//! This is also not an optimal implementation; many performance improvements could be made.

mod plan;
mod task_mgr;
mod worker;

use risc0_zkvm::{ApiClient, Asset, AssetRequest, ExecutorEnv, InnerReceipt, Receipt};
use risc0_zkvm_methods::{FIB_ELF, FIB_ID};

use self::{plan::Planner, task_mgr::TaskManager};

fn main() {
    prover_example();
}

fn prover_example() {
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

    let client = ApiClient::from_env().unwrap();
    let mut segment_idx = 0;
    let session = client
        .execute(
            &env,
            Asset::Inline(FIB_ELF.into()),
            AssetRequest::Inline,
            |_info, segment| {
                planner.enqueue_segment(segment_idx).unwrap();
                task_manager.add_segment(segment_idx, segment);
                while let Some(task) = planner.next_task() {
                    task_manager.add_task(task.clone());
                }
                segment_idx += 1;
                Ok(())
            },
        )
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
        session.journal.bytes.clone(),
    );
    receipt.verify(FIB_ID).unwrap();
    println!("Receipt verified!");
}

#[test]
fn smoke_test() {
    prover_example();
}
