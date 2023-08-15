// Copyright 2023 RISC Zero, Inc.
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

use clap::Parser;
use risc0_zkp::{
    core::hash::{blake2b::Blake2bCpuHashSuite, poseidon::PoseidonHashSuite, sha::Sha256HashSuite},
    field::baby_bear::BabyBear,
    hal::cpu::CpuHal,
};
use risc0_zkvm::Loader;

#[derive(Parser)]
pub struct Bootstrap;

impl Bootstrap {
    pub fn run(&self) {
        let loader = Loader::new();
        let control_id_sha256 =
            loader.compute_control_id(&CpuHal::new(Sha256HashSuite::<BabyBear>::new_suite()));
        let control_id_poseidon =
            loader.compute_control_id(&CpuHal::new(PoseidonHashSuite::new_suite()));
        let control_id_blake2b =
            loader.compute_control_id(&CpuHal::new(Blake2bCpuHashSuite::new_suite()));
        let contents = format!(
            include_str!("control_id.rs"),
            control_id_sha256[0],
            control_id_sha256[1],
            control_id_sha256[2],
            control_id_sha256[3],
            control_id_sha256[4],
            control_id_sha256[5],
            control_id_sha256[6],
            control_id_sha256[7],
            control_id_sha256[8],
            control_id_sha256[9],
            control_id_sha256[10],
            control_id_poseidon[0],
            control_id_poseidon[1],
            control_id_poseidon[2],
            control_id_poseidon[3],
            control_id_poseidon[4],
            control_id_poseidon[5],
            control_id_poseidon[6],
            control_id_poseidon[7],
            control_id_poseidon[8],
            control_id_poseidon[9],
            control_id_poseidon[10],
            control_id_blake2b[0],
            control_id_blake2b[1],
            control_id_blake2b[2],
            control_id_blake2b[3],
            control_id_blake2b[4],
            control_id_blake2b[5],
            control_id_blake2b[6],
            control_id_blake2b[7],
            control_id_blake2b[8],
            control_id_blake2b[9],
            control_id_blake2b[10],
        );
        println!("{contents}");
        std::fs::write("risc0/zkvm/src/control_id.rs", contents).unwrap();
    }
}
