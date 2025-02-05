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

// use substrate_bn::Fq;
use bn254_methods::{BN254_VERIFY_ELF, BN254_VERIFY_ID};
use risc0_zkvm::{default_prover, ExecutorEnv, Receipt};

fn todo_do_a_thing() -> Receipt { // TODO
    // TODO: actually handle real inputs
    let in1 = hex::decode("01").expect("valid hex");
    let in2 = hex::decode("03").expect("valid hex");
    // let in1 = 1u32;
    // let in2 = 3u32;
    let input = (in1, in2);
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();

    let prover = default_prover();

    prover.prove(env, BN254_VERIFY_ELF).unwrap().receipt
}

fn main() {
    let receipt = todo_do_a_thing();

    // Verify the receipt and then access the journal.
    receipt.verify(BN254_VERIFY_ID).unwrap();
    // TODO: Actually handle real outputs
    let (r1, r2): ([u8; 32], [u8; 32]) =
        receipt.journal.decode().unwrap();

    println!(
        "TODO some message related to journal {:?}, {:?}", r1, r2,
    );
}
