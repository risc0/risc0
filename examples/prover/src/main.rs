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

#![allow(unused)]

// mod plan;
// mod task_mgr;
// mod worker;

use std::{
    cell::RefCell,
    collections::{BTreeMap, HashMap},
    rc::Rc,
    sync::mpsc::{channel, Receiver, RecvError, Sender},
    thread::JoinHandle,
};

use anyhow::Result;
use risc0_zkvm::{
    default_executor,
    sha::{Digest, Digestible},
    ApiClient, Asset, AssetRequest, CoprocessorCallback, ExecutorEnv, ExecutorImpl, InnerReceipt,
    NullSegmentRef, ProveKeccakRequest, ProveZkrRequest, ProverOpts, Receipt, Segment,
    SuccinctReceipt, Unknown,
};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF, MULTI_TEST_ID};

// use self::{plan::Planner, task_mgr::TaskManager};

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    prover_example();
}

enum TaskManagerMessage {
    Segment(Segment),
    SessionHalted,
    SegmentProof,
    JoinProof,
}

struct TaskManagerActor {
    rx: Receiver<TaskManagerMessage>,
    tasks: BTreeMap<u32, u32>,
}

impl TaskManagerActor {
    pub fn new(rx: Receiver<TaskManagerMessage>) -> Self {
        Self {
            rx,
            tasks: BTreeMap::new(),
        }
    }

    pub fn run(&mut self) {
        while let Ok(msg) = self.rx.recv() {
            if !self.on_message(msg) {
                break;
            }
        }
    }

    fn on_message(&mut self, msg: TaskManagerMessage) -> bool {
        match msg {
            TaskManagerMessage::Segment(ref segment) => {
                println!("Segment: {}", segment.index);
                true
            }
            TaskManagerMessage::SessionHalted => {
                println!("SegmentHalted");
                false
            }
            TaskManagerMessage::SegmentProof => true,
            TaskManagerMessage::JoinProof => true,
        }
    }
}

#[derive(Clone)]
struct TaskManager {
    tx: Sender<TaskManagerMessage>,
}

impl TaskManager {
    pub fn new() -> (Self, JoinHandle<()>) {
        let (tx, rx) = channel();
        let mut task_mgr = TaskManagerActor::new(rx);
        let handle = std::thread::spawn(move || {
            task_mgr.run();
        });
        (Self { tx }, handle)
    }

    pub fn add_segment(&self, segment: Segment) {
        self.tx.send(TaskManagerMessage::Segment(segment)).unwrap();
    }

    pub fn session_halted(&self) {
        self.tx.send(TaskManagerMessage::SessionHalted).unwrap();
    }
}

struct Coprocessor<'a> {
    next_proof_idx: u32,
    // pub(crate) receipts: HashMap<Digest, SuccinctReceipt<Unknown>>,
    // pub(crate) task_manager: &'a RefCell<TaskManager>,
    // pub(crate) planner: &'a RefCell<Planner>,
    task_mgr: &'a TaskManager,
}

impl<'a> Coprocessor<'a> {
    // fn new(task_manager: &'a RefCell<TaskManager>, planner: &'a RefCell<Planner>) -> Self {
    fn new(task_mgr: &'a TaskManager) -> Self {
        Self {
            next_proof_idx: 0,
            // receipts: HashMap::new(),
            // task_manager,
            // planner,
            task_mgr,
        }
    }
}

impl CoprocessorCallback for Coprocessor<'_> {
    fn prove_zkr(&mut self, proof_request: ProveZkrRequest) -> Result<()> {
        // println!("prove_zkr");
        // let client = ApiClient::from_env().unwrap();
        // let claim_digest = proof_request.claim_digest;
        // let receipt = client.prove_zkr(proof_request, AssetRequest::Inline)?;
        // self.receipts.insert(claim_digest, receipt);
        Ok(())
    }

    fn prove_keccak(&mut self, proof_request: ProveKeccakRequest) -> Result<()> {
        // println!("prove_keccak: {}", proof_request.po2);
        // self.planner
        //     .borrow_mut()
        //     .enqueue_keccak(self.next_proof_idx)
        //     .unwrap();
        // self.task_manager
        //     .borrow_mut()
        //     .add_keccak_segment(self.next_proof_idx, proof_request);
        // while let Some(task) = self.planner.borrow_mut().next_task() {
        //     self.task_manager.borrow_mut().add_task(task.clone());
        // }
        self.next_proof_idx += 1;
        Ok(())
    }
}

fn prover_example() {
    println!("Submitting proof request...");

    // let task_manager = RefCell::new(TaskManager::new());
    // let planner = RefCell::new(Planner::default());

    let (task_mgr, handle) = TaskManager::new();

    let coprocessor = Rc::new(RefCell::new(Coprocessor::new(&task_mgr)));

    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::KeccakUnion(3))
        .unwrap()
        .coprocessor_callback_ref(coprocessor.clone())
        .build()
        .unwrap();

    // let client = ApiClient::from_env().unwrap();
    // let mut segment_idx = 0;
    // let session = client
    //     .execute(
    //         &env,
    //         Asset::Inline(MULTI_TEST_ELF.into()),
    //         AssetRequest::Inline,
    //         |info, segment| {
    //             // println!("{info:?}");
    //             // planner.borrow_mut().enqueue_segment(segment_idx).unwrap();
    //             // task_manager.borrow_mut().add_segment(segment_idx, segment);
    //             // while let Some(task) = planner.borrow_mut().next_task() {
    //             //     task_manager.borrow_mut().add_task(task.clone());
    //             // }
    //             task_mgr.add_segment(segment_idx);
    //             segment_idx += 1;
    //             Ok(())
    //         },
    //     )
    //     .unwrap();

    let mut executor = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
    let session = executor
        .run_with_callback(|segment| {
            // let segment_bytes = postcard::to_stdvec(&segment)?;
            task_mgr.add_segment(segment);
            Ok(Box::new(NullSegmentRef))
        })
        .unwrap();

    task_mgr.session_halted();
    handle.join().unwrap();

    // planner.borrow_mut().finish().unwrap();

    // println!("Plan:");
    // println!("{:?}", planner.borrow());

    // while let Some(task) = planner.borrow_mut().next_task() {
    //     task_manager.borrow_mut().add_task(task.clone());
    // }

    // let opts = ProverOpts::default();
    // let (conditional_receipt, union_root) = task_manager.borrow_mut().finish();

    // let coprocessor = coprocessor.borrow();
    // let mut all_receipts = coprocessor.receipts.clone();
    // if let Some(union_root) = union_root {
    //     all_receipts.insert(union_root.claim.digest(), union_root);
    // }

    // let output = conditional_receipt
    //     .claim
    //     .as_value()
    //     .unwrap()
    //     .output
    //     .as_value()
    //     .unwrap()
    //     .as_ref()
    //     .unwrap();
    // let assumptions = output.assumptions.as_value().unwrap();

    // let mut succinct_receipt = conditional_receipt.clone();
    // for assumption in assumptions.iter() {
    //     let assumption = assumption.as_value().unwrap();
    //     println!("Resolve: {assumption:?}");

    //     let assumption_receipt = all_receipts.get(&assumption.claim).unwrap().clone();
    //     succinct_receipt = client
    //         .resolve(
    //             &opts,
    //             succinct_receipt.try_into().unwrap(),
    //             assumption_receipt.try_into().unwrap(),
    //             AssetRequest::Inline,
    //         )
    //         .unwrap();
    // }

    // let receipt = Receipt::new(
    //     InnerReceipt::Succinct(succinct_receipt),
    //     session.journal.bytes.clone(),
    // );
    // let asset = receipt.try_into().unwrap();
    // client.verify(asset, MULTI_TEST_ID).unwrap();
    // println!("Receipt verified!");
}

#[test_log::test]
fn smoke_test() {
    prover_example();
}
