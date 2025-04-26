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

use risc0_circuit_recursion::{
    control_id::ALLOWED_CONTROL_IDS,
    prove::{DigestKind, Program, Prover},
};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{
    adapter::CircuitInfo as _,
    core::{hash::hash_suite_from_name, log2_ceil},
    verify::ReadIOP,
    ZK_CYCLES,
};
use risc0_zkvm::{recursion::MerkleGroup, SegmentReceipt};
use std::collections::HashMap;

const RECURSION_CODE_SIZE: usize = 23;

fn run_lift_join(n: u32, zkrs: &HashMap<String, Vec<u32>>) {
    let mut segments = vec![];

    for i in 75..(75 + n + 1) {
        let path = format!("risc0/zkvm/examples/zeth_segment_receipts/receipt{i}.bin");
        let segment: SegmentReceipt =
            bincode::deserialize(&std::fs::read(&path).expect(&format!("{path} should exist")))
                .unwrap();
        segments.push(segment);
    }

    let out_size = risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE;

    let seal0 = &segments[0].seal[1..];

    let inner_hash_suite = hash_suite_from_name(&segments[0].hashfn).unwrap();
    let allowed_ids = MerkleGroup::new(ALLOWED_CONTROL_IDS.to_vec()).unwrap();
    let merkle_root = allowed_ids.calc_root(inner_hash_suite.hashfn.as_ref());
    let mut iop = ReadIOP::new(seal0, inner_hash_suite.rng.as_ref());
    iop.read_field_elem_slice::<BabyBearElem>(out_size);
    let po2 = *iop.read_u32s(1).first().unwrap() as usize;

    let program_name = if n == 1 {
        format!("lift_join_rv32im_v2_{po2}.zkr")
    } else {
        format!("lift_join{n}_rv32im_v2_{po2}.zkr")
    };

    let encoded_program = zkrs.get(&program_name).unwrap();
    let padded_cycles =
        ((encoded_program.len() + ZK_CYCLES) / RECURSION_CODE_SIZE).next_power_of_two();
    let recursion_po2 = log2_ceil(padded_cycles);
    let program = Program::from_encoded(&encoded_program, recursion_po2);
    let mut prover = Prover::new(program, "poseidon2");

    prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
    for segment in &segments {
        let seal = &segment.seal[1..];
        prover.add_input(seal);
    }

    let start = std::time::Instant::now();
    for _ in 0..10 {
        let receipt = prover.run().unwrap();
        std::hint::black_box(receipt);
    }
    let elapsed = start.elapsed();
    let average = elapsed / 10;

    println!(
        "ran {program_name} took on average {average:?}, {average:?} / (n + 1) = {:?}",
        average / (n + 1)
    );
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let zkrs: HashMap<_, _> = risc0_circuit_recursion::prove::zkr::get_all_zkrs()
        .unwrap()
        .into_iter()
        .collect();

    for n in 1..11 {
        run_lift_join(n, &zkrs);
    }
}
