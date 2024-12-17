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

use rand::thread_rng;
use risc0_binfmt::Program;
use risc0_zkp::{
    core::hash::poseidon2::Poseidon2HashSuite,
    field::{baby_bear::BabyBearExtElem, Elem as _},
    hal::cpu::CpuHal,
};
use test_log::test;

use super::{hal::StepMode, segment_prover};
use crate::{
    execute::{image::MemoryImage2, testutil, DEFAULT_SEGMENT_LIMIT_PO2},
    prove::witgen::WitnessGenerator,
    zirgen::circuit::REGCOUNT_DATA,
};

#[test]
fn basic() {
    let program = testutil::basic();
    let image = MemoryImage2::new(program);

    let result = testutil::execute(
        image,
        DEFAULT_SEGMENT_LIMIT_PO2,
        testutil::DEFAULT_SESSION_LIMIT,
        &testutil::NullSyscall,
        None,
    )
    .unwrap();
    let segments = result.segments;
    let segment = segments.first().unwrap();

    let prover = segment_prover().unwrap();
    let seal = prover.prove(segment).unwrap();
    prover.verify(&seal).unwrap();
}
