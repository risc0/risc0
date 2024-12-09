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

use std::rc::Rc;

use cfg_if::cfg_if;
use risc0_circuit_keccak_methods::{KECCAK_ELF, KECCAK_ID};
use risc0_zkp::{
    core::digest::Digest,
    digest,
    hal::{Buffer as _, Hal as _},
};
use risc0_zkvm::{get_prover_server, register_zkr, ExecutorEnv, ProverOpts};
use test_log::test;

use super::{testutil::test_inputs, zkr::get_keccak_zkr};
use crate::{
    get_control_id,
    prove::{keccak_prover, CircuitWitnessGenerator as _, MetaBuffer, PreflightTrace, StepMode},
    zirgen::circuit::*,
    KECCAK_PO2_RANGE,
};

#[test]
fn basic() {
    let po2 = 8; // 256
    let inputs = test_inputs(po2);
    let prover = keccak_prover().unwrap();
    let seal = prover.prove(&inputs, po2).unwrap();
    prover.verify(&seal).expect("Verification failed");
}

#[test]
fn fwd_rev_ab() {
    cfg_if! {
        if #[cfg(feature = "cuda")] {
            use risc0_zkp::hal::cuda::CudaHalPoseidon2;
            use crate::prove::hal::cuda::CudaCircuitHalPoseidon2;
            let hal = Rc::new(CudaHalPoseidon2::new());
            let circuit_hal = CudaCircuitHalPoseidon2::new(hal.clone());
        } else {
            use risc0_zkp::{core::hash::sha::Sha256HashSuite, hal::cpu::CpuHal};
            use crate::prove::hal::cpu::CpuCircuitHal;
            let suite = Sha256HashSuite::new_suite();
            let hal = Rc::new(CpuHal::new(suite));
            let circuit_hal = CpuCircuitHal;
        }
    }

    let po2 = 8;
    let inputs = test_inputs(po2);
    let cycles: usize = 1 << po2;
    let preflight = PreflightTrace::new(&inputs, cycles);

    let fwd_data = {
        let global = MetaBuffer::new("global", hal.as_ref(), 1, REGCOUNT_GLOBAL, true);
        let data = MetaBuffer::new("data", hal.as_ref(), cycles, REGCOUNT_DATA, true);
        circuit_hal
            .generate_witness(StepMode::SeqForward, &preflight, &global, &data)
            .unwrap();
        hal.eltwise_zeroize_elem(&data.buf);
        data.buf.to_vec()
    };

    let rev_data = {
        let global = MetaBuffer::new("global", hal.as_ref(), 1, REGCOUNT_GLOBAL, true);
        let data = MetaBuffer::new("data", hal.as_ref(), cycles, REGCOUNT_DATA, true);
        circuit_hal
            .scatter_preflight(&data, &preflight.scatter, &preflight.data)
            .unwrap();
        circuit_hal
            .generate_witness(StepMode::SeqReverse, &preflight, &global, &data)
            .unwrap();
        hal.eltwise_zeroize_elem(&data.buf);
        data.buf.to_vec()
    };

    assert_eq!(fwd_data, rev_data);
}

static REGISTER_ZKRS: std::sync::Once = std::sync::Once::new();

fn register_zkrs() {
    REGISTER_ZKRS.call_once(|| {
        for po2 in KECCAK_PO2_RANGE {
            register_zkr(get_control_id(po2), move || get_keccak_zkr(po2));
        }
    });
}

fn run_test(po2: usize, claim_digest: Digest) {
    let to_guest: (Digest, u32) = (claim_digest, po2 as u32);

    let env = ExecutorEnv::builder()
        .write(&to_guest)
        .unwrap()
        .build()
        .unwrap();

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, KECCAK_ELF).unwrap().receipt;

    // Make sure this receipt actually depends on the assumption;
    // otherwise this test might give a false negative.
    assert!(!receipt
        .inner
        .composite()
        .unwrap()
        .assumption_receipts
        .is_empty());

    // Make sure the receipt verifies OK
    receipt.verify(KECCAK_ID).unwrap();
}

#[test]
fn lift_16() {
    run_test(
        16,
        digest!("822a0c0b9cd04788833b9366addf8343c27563733ec1f3fc4ca405915e1ae162"),
    );
}

#[test]
#[ignore] // causes OOM in some environments
fn lift_17() {
    run_test(
        17,
        digest!("a1b1e7b58b6e1ab761bd4f55cc763d9eef886b26e0942e4a3916d0c465f3d962"),
    );
}
