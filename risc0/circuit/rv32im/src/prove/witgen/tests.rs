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

use std::rc::Rc;

use rand::thread_rng;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkp::field::Elem;
use test_log::test;

use crate::{
    execute::{
        testutil::{self, NullSyscall, DEFAULT_SESSION_LIMIT},
        DEFAULT_SEGMENT_LIMIT_PO2,
    },
    prove::{hal::StepMode, witgen::WitnessGenerator},
    zirgen::circuit::{ExtVal, REGCOUNT_DATA},
    MAX_INSN_CYCLES,
};

fn run_preflight(program: Program) {
    let image = MemoryImage::new_kernel(program);
    let result = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall,
        None,
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let mut rng = thread_rng();
    let rand_z = ExtVal::random(&mut rng);

    segment.preflight(rand_z).unwrap();
}

#[test]
fn basic() {
    run_preflight(testutil::kernel::basic());
}

#[test]
fn simple_loop() {
    run_preflight(testutil::kernel::simple_loop(500000));
}

fn fwd_rev_ab_test(program: Program) {
    let image = MemoryImage::new_kernel(program);

    let session = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        MAX_INSN_CYCLES,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();

    cfg_if::cfg_if! {
        if #[cfg(feature = "cuda")] {
            use risc0_zkp::hal::cuda::CudaHalPoseidon2;
            use crate::prove::hal::cuda::CudaCircuitHalPoseidon2;
            let hal = Rc::new(CudaHalPoseidon2::new());
            let circuit_hal = CudaCircuitHalPoseidon2::new(hal.clone());
        // } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
        //     use risc0_zkp::hal::metal::MetalHalSha256;
        //     use crate::prove::hal::metal::MetalCircuitHal;
        //     let hal = Rc::new(MetalHalSha256::new());
        //     let circuit_hal = MetalCircuitHal::new(hal.clone());
        } else {
            let suite = risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite::new_suite();
            let hal = Rc::new(risc0_zkp::hal::cpu::CpuHal::new(suite));
            let circuit_hal = crate::prove::hal::cpu::CpuCircuitHal;
        }
    }

    let mut rng = thread_rng();
    let rand_z = ExtVal::random(&mut rng);

    let segments = session.segments;
    for segment in segments {
        tracing::debug!("fwd");
        let fwd_witgen = WitnessGenerator::new(
            hal.as_ref(),
            &circuit_hal,
            &segment,
            StepMode::SeqForward,
            rand_z,
        )
        .unwrap();
        tracing::debug!("rev");
        let rev_witgen = WitnessGenerator::new(
            hal.as_ref(),
            &circuit_hal,
            &segment,
            StepMode::SeqReverse,
            rand_z,
        )
        .unwrap();
        let cycles = 1 << segment.po2;
        let fwd_vec = fwd_witgen.data.to_vec();
        let rev_vec = rev_witgen.data.to_vec();
        for row in 0..cycles {
            let fwd_row = &fwd_vec[row * REGCOUNT_DATA..row * REGCOUNT_DATA + REGCOUNT_DATA];
            let rev_row = &rev_vec[row * REGCOUNT_DATA..row * REGCOUNT_DATA + REGCOUNT_DATA];
            assert_eq!(fwd_row, rev_row, "cycle: {row}");
        }
    }
}

#[test]
fn fwd_rev_ab_basic() {
    fwd_rev_ab_test(testutil::kernel::basic());
}

#[test]
fn fwd_rev_ab_split() {
    fwd_rev_ab_test(testutil::kernel::simple_loop(2000));
}
