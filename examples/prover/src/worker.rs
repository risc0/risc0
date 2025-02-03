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

use risc0_zkvm::{Asset, ProveKeccakRequest, ReceiptClaim, SuccinctReceipt, Unknown};

use crate::task_mgr::Job;

#[derive(Default)]
pub struct Worker;

impl workerpool::Worker for Worker {
    type Input = Job<SuccinctReceipt<ReceiptClaim>, Asset>;
    type Output = Job<SuccinctReceipt<ReceiptClaim>, Asset>;

    fn execute(&mut self, job: Self::Input) -> Self::Output {
        println!("{:?}", job.task);
        std::panic::catch_unwind(|| job.execute()).unwrap_or_else(|_| {
            std::process::abort();
        })
    }
}

#[derive(Default)]
pub struct KeccakWorker;

impl workerpool::Worker for KeccakWorker {
    type Input = Job<SuccinctReceipt<Unknown>, ProveKeccakRequest>;
    type Output = Job<SuccinctReceipt<Unknown>, ProveKeccakRequest>;

    fn execute(&mut self, job: Self::Input) -> Self::Output {
        println!("{:?}", job.task);
        std::panic::catch_unwind(|| job.execute()).unwrap_or_else(|_| {
            std::process::abort();
        })
    }
}
