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

use std::{collections::HashSet, fmt::Write, process::Command};

use clap::Parser;
use risc0_circuit_recursion::zkr::{get_all_zkrs, get_zkr};
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{
            blake2b::Blake2bCpuHashSuite, hash_suite_from_name, poseidon2::Poseidon2HashSuite,
            poseidon_254::Poseidon254HashSuite, sha::Sha256HashSuite,
        },
    },
    field::baby_bear::BabyBear,
    hal::cpu::CpuHal,
};
use risc0_zkvm::{
    recursion::{MerkleGroup, Program},
    Loader,
};

#[derive(Parser)]
pub struct Bootstrap;

const CONTROL_ID_PATH_RV32IM: &str = "risc0/circuit/rv32im/src/control_id.rs";
const CONTROL_ID_PATH_RECURSION: &str = "risc0/circuit/recursion/src/control_id.rs";

impl Bootstrap {
    pub fn run(&self) {
        let poseidon2_control_ids = Self::generate_rv32im_control_ids();
        Self::generate_recursion_control_ids(poseidon2_control_ids);
    }

    fn generate_rv32im_control_ids() -> Vec<Digest> {
        tracing::info!("computing control IDs with SHA-256");
        let control_id_sha256 = Loader::compute_control_id_table(&CpuHal::new(Sha256HashSuite::<
            BabyBear,
        >::new_suite(
        )));
        tracing::info!("computing control IDs with Poseidon2");
        let control_id_poseidon2 =
            Loader::compute_control_id_table(&CpuHal::new(Poseidon2HashSuite::new_suite()));
        tracing::info!("computing control IDs with Blake2b");
        let control_id_blake2b =
            Loader::compute_control_id_table(&CpuHal::new(Blake2bCpuHashSuite::new_suite()));

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
            control_id_poseidon2[0],
            control_id_poseidon2[1],
            control_id_poseidon2[2],
            control_id_poseidon2[3],
            control_id_poseidon2[4],
            control_id_poseidon2[5],
            control_id_poseidon2[6],
            control_id_poseidon2[7],
            control_id_poseidon2[8],
            control_id_poseidon2[9],
            control_id_poseidon2[10],
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
        tracing::debug!("contents of rv32im control_id.rs:\n{contents}");

        tracing::info!("writing control ids to {CONTROL_ID_PATH_RV32IM}");
        std::fs::write(CONTROL_ID_PATH_RV32IM, contents).unwrap();

        // Use rustfmt to format the file.
        Command::new("rustfmt")
            .arg(CONTROL_ID_PATH_RV32IM)
            .status()
            .expect("failed to format {CONTROL_ID_PATH_RV32IM}");

        control_id_poseidon2
    }

    fn generate_recursion_control_ids(poseidon2_rv32im_control_ids: Vec<Digest>) {
        // Recursion programs (ZKRs) that are too be included in the allowed set.
        // NOTE: We use an allow list here, rather than including all ZKRs in the zip archive,
        // because there may be ZKRs included only for tests, or ones that are not part of the main
        // set of allowed programs (e.g. accelerators).
        let allowed_zkr_names: HashSet<String> = ["join.zkr", "resolve.zkr", "identity.zkr"]
            .map(str::to_string)
            .into_iter()
            .chain((14..=24).map(|i| format!("lift_{i}.zkr")))
            .collect();

        tracing::info!("unzipping recursion programs (zkrs)");
        let zkrs = get_all_zkrs().unwrap();

        let poseidon2_control_ids =
            Self::generate_recursion_control_ids_with_hash(&zkrs, "poseidon2");
        let sha256_control_ids = Self::generate_recursion_control_ids_with_hash(&zkrs, "sha-256");

        let allowed_control_ids: Vec<Digest> = poseidon2_rv32im_control_ids
            .iter()
            .chain(
                poseidon2_control_ids
                    .iter()
                    .filter(|(name, _)| allowed_zkr_names.contains(name))
                    .map(|(_, digest)| digest),
            )
            .cloned()
            .collect();
        let mut allowed_control_ids_str = String::new();
        for digest in allowed_control_ids.iter() {
            writeln!(&mut allowed_control_ids_str, r#"digest!("{digest}"),"#).unwrap();
        }

        // Calculuate a Merkle root for the allowed control IDs and add it to the file.
        let merkle_group = MerkleGroup::new(allowed_control_ids).unwrap();
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let allowed_control_root = merkle_group.calc_root(hashfn);
        tracing::info!("Computed allowed_control_root: {allowed_control_root}");

        let control_ids_str = |control_ids: &[(String, Digest)]| -> String {
            let mut string = String::new();
            for (name, digest) in control_ids.iter() {
                writeln!(&mut string, r#"("{name}", digest!("{digest}")),"#).unwrap();
            }
            string
        };

        let bn254_identity_control_id = Self::generate_identity_bn254_control_id();
        tracing::info!("Computed bn254_identity_control_id: {bn254_identity_control_id}");
        let contents = format!(
            include_str!("templates/control_id_zkr.rs"),
            allowed_control_ids_str,
            allowed_control_root,
            bn254_identity_control_id,
            poseidon2_control_ids.len(),
            control_ids_str(&poseidon2_control_ids),
            sha256_control_ids.len(),
            control_ids_str(&sha256_control_ids),
        );

        tracing::info!("writing control ids to {CONTROL_ID_PATH_RECURSION}");
        std::fs::write(CONTROL_ID_PATH_RECURSION, contents).unwrap();

        // Use rustfmt to format the file.
        Command::new("rustfmt")
            .arg(CONTROL_ID_PATH_RECURSION)
            .status()
            .expect("failed to format {CONTROL_ID_PATH_RECURSION}");
    }

    pub fn generate_recursion_control_ids_with_hash(
        zkrs: &[(String, Vec<u32>)],
        hashfn: &str,
    ) -> Vec<(String, Digest)> {
        let hash_suite = hash_suite_from_name(hashfn).unwrap();

        zkrs.into_iter()
            .map(|(name, encoded_program)| {
                let program = Program::from_encoded(&encoded_program);

                tracing::info!("computing control ID for {name} with {hashfn}");
                let control_id = program.compute_control_id(hash_suite.clone());

                tracing::debug!("{name} control id: {control_id:?}");
                (name.clone(), control_id)
            })
            .collect()
    }

    pub fn generate_identity_bn254_control_id() -> Digest {
        let encoded_program = get_zkr("identity.zkr").unwrap();
        let program = Program::from_encoded(&encoded_program);
        program.compute_control_id(Poseidon254HashSuite::new_suite())
    }
}
