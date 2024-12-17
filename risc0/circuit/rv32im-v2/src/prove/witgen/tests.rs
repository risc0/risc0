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

use rand::thread_rng;
use risc0_binfmt::Program;
use risc0_zkp::{core::hash::poseidon2::Poseidon2HashSuite, field::Elem, hal::cpu::CpuHal};
use std::rc::Rc;
use test_log::test;

use crate::{
    execute::{
        image::MemoryImage2,
        testutil::{self, NullSyscall, DEFAULT_SESSION_LIMIT},
        DEFAULT_SEGMENT_LIMIT_PO2,
    },
    prove::{hal::StepMode, witgen::WitnessGenerator},
    zirgen::circuit::{ExtVal, REGCOUNT_DATA},
};

#[test]
fn basic() {
    let program = testutil::basic();
    let image = MemoryImage2::new(program);

    let result = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        DEFAULT_SESSION_LIMIT,
        &NullSyscall,
        None,
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let mut rng = thread_rng();
    let rand_z = ExtVal::random(&mut rng);

    let mut trace = segment.preflight(rand_z).unwrap();
    // let expected_cycles = [
    //     add_cycle(InsnKind::LUI, 0, Some(0x4000)),
    //     add_cycle(InsnKind::LUI, 3, Some(0x4004)),
    //     add_cycle(InsnKind::ADD, 6, Some(0x4008)),
    //     add_cycle(InsnKind::LUI, 9, Some(0x400c)),
    //     add_cycle(InsnKind::EANY, 12, None),
    // ];
    // trace.body.cycles.truncate(expected_cycles.len());

    // assert_slice_eq(&trace.body.cycles, &expected_cycles);
    // assert_slice_eq(
    //     &trace.body.txns,
    //     &[
    //         MemoryTransaction::new(0, ByteAddr(0x00004000), 0x1234b137),
    //         MemoryTransaction::new(0, ByteAddr(0x0c000024), 0),
    //         MemoryTransaction::new(0, ByteAddr(0x0c00000c), 0),
    //         MemoryTransaction::new(1, ByteAddr(0x00004004), 0xf387e1b7),
    //         MemoryTransaction::new(1, ByteAddr(0x0c00003c), 0),
    //         MemoryTransaction::new(1, ByteAddr(0x0c000060), 0),
    //         MemoryTransaction::new(2, ByteAddr(0x00004008), 0x003100b3),
    //         MemoryTransaction::new(2, ByteAddr(0x0c000008), 0x1234b000),
    //         MemoryTransaction::new(2, ByteAddr(0x0c00000c), 0xf387e000),
    //         MemoryTransaction::new(3, ByteAddr(0x0000400c), 0x000045b7),
    //         MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
    //         MemoryTransaction::new(3, ByteAddr(0x0c000000), 0),
    //         MemoryTransaction::new(4, ByteAddr(0x00004010), 0x00000073),
    //         MemoryTransaction::new(4, ByteAddr(0x0c000014), 0),
    //         MemoryTransaction::new(4, ByteAddr(0x0c00002c), 0x00004000),
    //         MemoryTransaction::new(4, ByteAddr(0x0c000028), 0x00000000),
    //         // reset(1)
    //         MemoryTransaction::new(4380, ByteAddr(0x00004000), 0x1234b137),
    //         MemoryTransaction::new(4380, ByteAddr(0x00004004), 0xf387e1b7),
    //         MemoryTransaction::new(4380, ByteAddr(0x00004008), 0x003100b3),
    //         MemoryTransaction::new(4380, ByteAddr(0x0000400c), 0x000045b7),
    //         MemoryTransaction::new(4381, ByteAddr(0x00004010), 0x00000073),
    //         MemoryTransaction::new(4381, ByteAddr(0x00004014), 0x00000000),
    //         MemoryTransaction::new(4381, ByteAddr(0x00004018), 0x00000000),
    //         MemoryTransaction::new(4381, ByteAddr(0x0000401c), 0x00000000),
    //         // reset(2)
    //         MemoryTransaction::new(4382, ByteAddr(0x0d6b5ac0), 0x2ea10cf3),
    //         MemoryTransaction::new(4382, ByteAddr(0x0d6b5ac4), 0x41559d09),
    //         MemoryTransaction::new(4382, ByteAddr(0x0d6b5ac8), 0x032b0b9e),
    //         MemoryTransaction::new(4382, ByteAddr(0x0d6b5acc), 0xda56a7af),
    //         MemoryTransaction::new(4383, ByteAddr(0x0d6b5ad0), 0x7c9d8024),
    //         MemoryTransaction::new(4383, ByteAddr(0x0d6b5ad4), 0x9bfea1c1),
    //         MemoryTransaction::new(4383, ByteAddr(0x0d6b5ad8), 0xc37b44c3),
    //         MemoryTransaction::new(4383, ByteAddr(0x0d6b5adc), 0x554f49f5),
    //     ],
    // );

    // assert_eq!(trace.body.extras.len(), 0);
}

fn fwd_rev_ab_test(program: Program) {
    let image = MemoryImage2::new(program);

    let session = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
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
            use crate::prove::hal::cpu::CpuCircuitHal;
            let suite = Poseidon2HashSuite::new_suite();
            let hal = Rc::new(CpuHal::new(suite));
            let circuit_hal = CpuCircuitHal::new();
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
    fwd_rev_ab_test(testutil::basic());
}

#[test]
fn fwd_rev_ab_split() {
    fwd_rev_ab_test(testutil::simple_loop(2000));
}

// #[test]
// fn fwd_rev_ab_large_text() {
//     fwd_rev_ab_test(testutil::large_text());
// }
