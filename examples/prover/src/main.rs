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

//! This is an example of how the public 1.0 API can be used to build a proving service.
//! It's not meant to be used in production since it doesn't handle failures.
//! This is also not an optimal implementation; many performance improvements could be made.

mod plan;
mod task_mgr;
mod worker;

use std::{cell::RefCell, collections::HashMap, rc::Rc};

use anyhow::Result;
use risc0_zkvm::{
    sha::Digest, ApiClient, Asset, AssetRequest, CoprocessorCallback, ExecutorEnv, InnerReceipt,
    ProveKeccakRequest, ProveZkrRequest, ProverOpts, Receipt, ReceiptClaim, SuccinctReceipt,
    Unknown,
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};
use worker::KeccakWorker;

use crate::{plan::Planner, worker::Worker};

use self::{plan::KeccakPlanner, plan::Rv32imPlanner, task_mgr::TaskManager};

fn main() {
    prover_example();
}

struct Coprocessor<'a> {
    next_proof_idx: u32,
    pub(crate) receipts: HashMap<Digest, SuccinctReceipt<Unknown>>,
    pub(crate) task_manager:
        &'a RefCell<TaskManager<SuccinctReceipt<Unknown>, ProveKeccakRequest, KeccakWorker>>,
    pub(crate) planner: &'a RefCell<KeccakPlanner>,
}

impl<'a> Coprocessor<'a> {
    fn new(
        task_manager: &'a RefCell<
            TaskManager<SuccinctReceipt<Unknown>, ProveKeccakRequest, KeccakWorker>,
        >,
        planner: &'a RefCell<KeccakPlanner>,
    ) -> Self {
        Self {
            next_proof_idx: 0,
            receipts: HashMap::new(),
            task_manager,
            planner,
        }
    }
}

impl<'a> CoprocessorCallback for Coprocessor<'a> {
    fn prove_zkr(&mut self, proof_request: ProveZkrRequest) -> Result<()> {
        let client = ApiClient::from_env().unwrap();
        let claim_digest = proof_request.claim_digest;
        let receipt = client.prove_zkr(proof_request, AssetRequest::Inline)?;
        self.receipts.insert(claim_digest, receipt);
        Ok(())
    }

    fn prove_keccak(&mut self, proof_request: ProveKeccakRequest) -> Result<()> {
        println!(
            "keccak proof request: idx({}) claim: {}",
            self.next_proof_idx, proof_request.claim_digest
        );
        self.planner
            .borrow_mut()
            .enqueue_segment(self.next_proof_idx)
            .unwrap();
        self.task_manager
            .borrow_mut()
            .add_segment(self.next_proof_idx, proof_request);
        while let Some(task) = self.planner.borrow_mut().next_task() {
            self.task_manager.borrow_mut().add_task(task.clone());
        }
        self.next_proof_idx += 1;
        Ok(())
    }

    fn finalize_keccak(&mut self) -> Result<()> {
        self.planner.borrow_mut().finish().unwrap();
        Ok(())
    }
}

fn prover_example() {
    println!("Submitting proof request...");

    let mut task_manager = TaskManager::<SuccinctReceipt<ReceiptClaim>, Asset, Worker>::new();
    let mut planner = Rv32imPlanner::default();
    let keccak_planner = RefCell::new(KeccakPlanner::default());
    let keccak_task_manager = RefCell::new(TaskManager::<
        SuccinctReceipt<Unknown>,
        ProveKeccakRequest,
        KeccakWorker,
    >::new());

    let coprocessor = Rc::new(RefCell::new(Coprocessor::new(
        &keccak_task_manager,
        &keccak_planner,
    )));

    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::KeccakUnion(3))
        .unwrap()
        .coprocessor_callback_ref(coprocessor.clone())
        .build()
        .unwrap();

    let client = ApiClient::from_env().unwrap();
    let mut segment_idx = 0;
    let session = client
        .execute(
            &env,
            Asset::Inline(MULTI_TEST_ELF.into()),
            AssetRequest::Inline,
            |info, segment| {
                println!("info: {info:?}");
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

    println!("Keccak Plan:");
    println!("{:?}", keccak_planner.borrow());

    while let Some(task) = planner.next_task() {
        task_manager.add_task(task.clone());
    }

    while let Some(task) = keccak_planner.borrow_mut().next_task() {
        keccak_task_manager.borrow_mut().add_task(task.clone());
    }

    let conditional_receipt = task_manager.run();
    println!("rv32im complete");

    let unioned_receipt = keccak_task_manager.borrow_mut().run();
    println!("Keccak complete {:#?}", unioned_receipt.claim);

    let output = conditional_receipt
        .claim
        .as_value()
        .unwrap()
        .output
        .as_value()
        .unwrap()
        .as_ref()
        .unwrap();
    let assumptions = output.assumptions.as_value().unwrap();

    let coprocessor = coprocessor.borrow();
    let mut succinct_receipt = conditional_receipt.clone();
    for assumption in assumptions.iter() {
        let assumption = assumption.as_value().unwrap();
        println!("{assumption:?}");
        let assumption_receipt = coprocessor.receipts.get(&assumption.claim).unwrap().clone();
        let opts = ProverOpts::default();
        succinct_receipt = client
            .resolve(
                &opts,
                succinct_receipt.try_into().unwrap(),
                assumption_receipt.try_into().unwrap(),
                AssetRequest::Inline,
            )
            .unwrap();
    }

    let receipt = Receipt::new(
        InnerReceipt::Succinct(succinct_receipt),
        session.journal.bytes.clone(),
    );
    let asset = receipt.try_into().unwrap();
    client.verify(asset, MULTI_TEST_ID).unwrap();
    println!("Receipt verified!");
}

#[test]
fn smoke_test() {
    prover_example();
}
