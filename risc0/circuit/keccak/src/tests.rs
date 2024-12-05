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

//use std::{cell::RefCell, collections::VecDeque, rc::Rc};

use anyhow::Result;
use risc0_circuit_keccak_methods::{KECCAK_ELF, KECCAK_ID};
use risc0_zkp::{core::digest::Digest, digest};
use risc0_zkvm::{get_prover_server, register_zkr, ExecutorEnv, ProverOpts};
use test_log::test;

use crate::{
    control_id::KECCAK_CONTROL_ID,
    prove::{testutil::test_inputs, zkr::get_zkr, KeccakState},
};

static REGISTER_ZKRS: std::sync::Once = std::sync::Once::new();

fn register_zkrs() {
    REGISTER_ZKRS.call_once(|| {
        register_zkr(&KECCAK_CONTROL_ID, get_zkr);
    });
}

fn run_test(claim_digest: Digest, input: &[KeccakState]) -> Result<()> {
    let input: &[u32] = bytemuck::cast_slice(input);
    let to_guest: (Digest, &[u32]) = (claim_digest, input);

    let env = ExecutorEnv::builder().write(&to_guest)?.build()?;

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast())?;

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, KECCAK_ELF)?.receipt;

    // Make sure this receipt actually depends on the assumption;
    // otherwise this test might give a false negative.
    assert!(!receipt
        .inner
        .composite()
        .unwrap()
        .assumption_receipts
        .is_empty());

    // Make sure the receipt verifies OK
    receipt.verify(KECCAK_ID)?;

    Ok(())
}

#[test]
fn basic() {
    let inputs = test_inputs();
    run_test(
        digest!("680f716f1ee30dcd2c4f7d9c91540e2c363bc435bee14414e160434bf5f53a46"),
        &inputs,
    )
    .unwrap();
}
