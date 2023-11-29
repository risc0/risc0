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

use std::io::Write;

use clap::Parser;
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{blake2b::Blake2bCpuHashSuite, poseidon::PoseidonHashSuite, sha::Sha256HashSuite},
    },
    field::baby_bear::BabyBear,
    hal::cpu::CpuHal,
};
use risc0_zkvm::Loader;

#[derive(Parser)]
pub struct Bootstrap;

impl Bootstrap {
    pub fn run(&self) {
        //Self::generate_rv32im_control_ids();
        Self::generate_recursion_control_ids();
    }

    #[allow(unused)]
    fn generate_rv32im_control_ids() {
        let loader = Loader::new();
        let control_id_sha256 =
            loader.compute_control_id(&CpuHal::new(Sha256HashSuite::<BabyBear>::new_suite()));
        let control_id_poseidon =
            loader.compute_control_id(&CpuHal::new(PoseidonHashSuite::new_suite()));
        let control_id_blake2b =
            loader.compute_control_id(&CpuHal::new(Blake2bCpuHashSuite::new_suite()));
        let contents = format!(
            include_str!("templates/control_id_rv32im.rs"),
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
        std::fs::write("risc0/zkvm/src/host/control_id.rs", contents).unwrap();
    }

    fn generate_recursion_control_ids() {
        // TODO: Avoid parsing the zip twice?
        let zkr_listing = risc0_circuit_recursion::zkr::get_all_zkrs().unwrap();
        let zkr_names = zkr_listing
            .into_iter()
            .map(|(name, _)| name)
            .collect::<Vec<_>>();
        let zkr_control_ids: Vec<(String, Digest)> = zkr_names
            .into_iter()
            .map(|name| {
                (
                    name.clone(),
                    risc0_circuit_recursion::zkr::get_control_id(&name).unwrap(),
                )
            })
            .collect::<Vec<_>>();

        // Generate the tree of acceptable control IDs.
        let output_path = "risc0/circuit/recursion/src/control_id.rs";
        let mut cntlf = std::fs::File::create(&output_path).unwrap();
        let license = "
        // Copyright 2023 RISC Zero, Inc.
        //
        // Licensed under the Apache License, Version 2.0 (the \"License\");
        // you may not use this file except in compliance with the License.
        // You may obtain a copy of the License at
        //
        //     http://www.apache.org/licenses/LICENSE-2.0
        //
        // Unless required by applicable law or agreed to in writing, software
        // distributed under the License is distributed on an \"AS IS\" BASIS,
        // WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        // See the License for the specific language governing permissions and
        // limitations under the License.";
        writeln!(&mut cntlf, "{}", license).unwrap();
        writeln!(&mut cntlf, "").unwrap();
        writeln!(
            &mut cntlf,
            "pub const RECURSION_CONTROL_IDS: [&str; {}] = [",
            zkr_control_ids.len()
        )
        .unwrap();
        for (name, digest) in zkr_control_ids {
            writeln!(&mut cntlf, "    \"{}\", // {}", digest, name,).unwrap();
        }
        writeln!(&mut cntlf, "];").unwrap();

        let hash_suite = PoseidonHashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let allowed_ids = risc0_zkvm::recursion::Prover::make_allowed_tree();
        let allowed_ids_root = allowed_ids.calc_root(hashfn);

        writeln!(&mut cntlf, "").unwrap();
        writeln!(&mut cntlf, "/// Merkle root of the RECURSION_CONTROL_IDS").unwrap();
        writeln!(&mut cntlf, "pub const ALLOWED_IDS_ROOT: &str = ").unwrap();
        writeln!(&mut cntlf, "    \"{}\";", allowed_ids_root).unwrap();
    }
}
