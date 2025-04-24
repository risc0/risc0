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
    prove::{DigestKind, Prover},
};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::{adapter::CircuitInfo as _, core::hash::hash_suite_from_name, verify::ReadIOP};
use risc0_zkvm::{recursion::MerkleGroup, SegmentReceipt};

pub const RECURSION_PO2: usize = 18;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let segment: SegmentReceipt =
        bincode::deserialize(include_bytes!("zeth_receipt_1.bin")).unwrap();

    let out_size = risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE;

    let seal = &segment.seal[1..];

    // Read the output fields in the rv32im seal to get the po2. We need this po2 to chose
    // which lift program we are going to run.
    let inner_hash_suite = hash_suite_from_name(&segment.hashfn).unwrap();
    let allowed_ids = MerkleGroup::new(ALLOWED_CONTROL_IDS.to_vec()).unwrap();
    let merkle_root = allowed_ids.calc_root(inner_hash_suite.hashfn.as_ref());
    let mut iop = ReadIOP::new(seal, inner_hash_suite.rng.as_ref());
    iop.read_field_elem_slice::<BabyBearElem>(out_size);
    let po2 = *iop.read_u32s(1).first().unwrap() as usize;

    // Instantiate the prover with the lift recursion program and its control ID.
    let program = risc0_circuit_recursion::prove::zkr::get_zkr(
        &format!("lift_rv32im_v2_{po2}.zkr"),
        RECURSION_PO2,
    )
    .unwrap();
    let mut prover = Prover::new(program, "poseidon2");

    prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
    prover.add_input(seal);

    let receipt = prover.run().unwrap();
    std::hint::black_box(receipt);
}
