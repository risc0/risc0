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

use std::{cell::RefCell, collections::VecDeque, rc::Rc};

use anyhow::Result;
use risc0_binfmt::read_sha_halfs;
use risc0_circuit_keccak_methods::{KECCAK_ELF, KECCAK_ID};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{
    core::digest::{Digest, DIGEST_SHORTS},
    digest,
};
use risc0_zkvm::{
    get_prover_server, register_zkr, ExecutorEnv, KeccakCoprocessorCallback, ProveKeccakRequest,
    ProveKeccakResponse, ProveZkrRequest, ProverOpts,
};
use test_log::test;

use crate::{
    control_id::{KECCAK_CONTROL_IDS, KECCAK_CONTROL_ROOT},
    get_control_id,
    prove::{keccak_prover, testutil::test_inputs, zkr::get_zkr, KeccakState},
    KECCAK_PO2_RANGE,
};

static REGISTER_ZKRS: std::sync::Once = std::sync::Once::new();

fn register_zkrs() {
    REGISTER_ZKRS.call_once(|| {
        for (po2, control_id) in KECCAK_PO2_RANGE.zip(KECCAK_CONTROL_IDS) {
            register_zkr(control_id, move || get_zkr(po2));
        }
    });
}

struct Coprocessor;

impl KeccakCoprocessorCallback for Coprocessor {
    fn prove_keccak(&mut self, req: ProveKeccakRequest) -> Result<ProveKeccakResponse> {
        let input: &[KeccakState] = bytemuck::cast_slice(req.input.as_slice());

        let prover = keccak_prover()?;
        let seal = prover.prove(input, req.po2)?;

        // Make sure we have a valid seal so we can fail early if anything went wrong
        prover.verify(&seal).expect("Verification failed");

        let claim_digest: Digest = read_sha_halfs(&mut VecDeque::from_iter(
            bytemuck::checked::cast_slice::<_, BabyBearElem>(&seal[0..DIGEST_SHORTS])
                .iter()
                .copied()
                .map(u32::from),
        ))?;
        tracing::debug!("claim_digest: {claim_digest:?}");
        let claim_sha_input: Vec<_> = claim_digest
            .as_words()
            .iter()
            .copied()
            .flat_map(|x| [x & 0xffff, x >> 16])
            .map(BabyBearElem::new)
            .collect();

        let mut zkr_input: Vec<u32> = Vec::new();
        zkr_input.extend(KECCAK_CONTROL_ROOT.as_words());
        zkr_input.extend(seal);
        zkr_input.extend(bytemuck::cast_slice(claim_sha_input.as_slice()));

        // Lift to recursion circuit
        let control_id = *get_control_id(req.po2);
        let zkr_lift = ProveZkrRequest {
            control_id,
            claim_digest,
            input: bytemuck::cast_slice(zkr_input.as_slice()).into(),
        };

        Ok(ProveKeccakResponse { zkr_lift })
    }
}

fn run_test(po2: u32, claim_digest: Digest, input: &[KeccakState]) -> Result<()> {
    let input: &[u32] = bytemuck::cast_slice(input);
    let to_guest: (u32, Digest, &[u32]) = (po2, claim_digest, input);

    let coprocessor = Rc::new(RefCell::new(Coprocessor));

    let env = ExecutorEnv::builder()
        .keccak_coprocessor_callback_ref(coprocessor.clone())
        .write(&to_guest)?
        .build()?;

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
        17,
        digest!("680f716f1ee30dcd2c4f7d9c91540e2c363bc435bee14414e160434bf5f53a46"),
        &inputs,
    )
    .unwrap();
}
