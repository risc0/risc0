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
// TODO: Temp
// use substrate_bn::{arith::U256, Fq};

fn todo_do_a_thing() -> Receipt { // TODO
    // TODO: Different values
    let a_g1x = hex::decode("1c76476f4def4bb94541d57ebba1193381ffa7aa76ada664dd31c16024c43f59").expect("valid hex");
    let a_g1y = hex::decode("3034dd2920f673e204fee2811c678745fc819b55d3e9d294e45c9b03a76aef41").expect("valid hex");
    let a_g2x_i = hex::decode("209dd15ebff5d46c4bd888e51a93cf99a7329636c63514396b4a452003a35bf7").expect("valid hex");
    let a_g2x_r = hex::decode("04bf11ca01483bfa8b34b43561848d28905960114c8ac04049af4b6315a41678").expect("valid hex");
    let a_g2y_i = hex::decode("2bb8324af6cfc93537a2ad1a445cfd0ca2a71acd7ac41fadbf933c2a51be344d").expect("valid hex");
    let a_g2y_r = hex::decode("120a2a4cf30c1bf9845f20c6fe39e07ea2cce61f0c9bb048165fe5e4de877550").expect("valid hex");
    // let b_g1x = hex::decode("111e129f1cf1097710d41c4ac70fcdfa5ba2023c6ff1cbeac322de49d1b6df7c").expect("valid hex");
    // let b_g1y = hex::decode("2032c61a830e3c17286de9462bf242fca2883585b93870a73853face6a6bf411").expect("valid hex");
    // let b_g2x_i = hex::decode("198e9393920d483a7260bfb731fb5d25f1aa493335a9e71297e485b7aef312c2").expect("valid hex");
    // let b_g2x_r = hex::decode("1800deef121f1e76426a00665e5c4479674322d4f75edadd46debd5cd992f6ed").expect("valid hex");
    // let b_g2y_i = hex::decode("090689d0585ff075ec9e99ad690c3395bc4b313370b38ef355acdadcd122975b").expect("valid hex");
    // let b_g2y_r = hex::decode("12c85ea5db8c6deb4aab71808dcb408fe3d1e7690c43d37b4ce6cc0166fa7daa").expect("valid hex");
    let a_factor = hex::decode("0000000000000000000000000000000000000000000000000000000000000002").expect("valid hex");
    let b_factor = hex::decode("0000000000000000000000000000000000000000000000000000000000000002").expect("valid hex");
    let input = (a_g1x, a_g1y, a_g2x_i, a_g2x_r, a_g2y_i, a_g2y_r, a_factor, b_factor);

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
    // let (r1, r2): ([u8; 32], [u8; 32]) =
    //     receipt.journal.decode().unwrap();
    let is_one: bool = receipt.journal.decode().unwrap();

    // println!(
    //     "TODO some message related to journal {:?}, {:?}", r1, r2,
    // );
    println!("Pairing gave one? {}", is_one);
}
