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

use std::{borrow::Borrow, collections::HashSet, fmt::Write, process::Command};

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
    MIN_CYCLES_PO2,
};
use risc0_zkvm::{
    recursion::{MerkleGroup, Program},
    Loader, DEFAULT_MAX_PO2, RECURSION_PO2,
};

#[derive(Parser)]
pub struct Bootstrap;

const CONTROL_ID_PATH_RV32IM: &str = "risc0/circuit/rv32im/src/control_id.rs";
const CONTROL_ID_PATH_RECURSION: &str = "risc0/circuit/recursion/src/control_id.rs";

const MIN_LIFT_PO2: usize = 14;

impl Bootstrap {
    // Format a list of control IDs, including a description as comments.
    fn format_control_ids(ids: impl IntoIterator<Item = impl Borrow<(String, Digest)>>) -> String {
        let mut out = String::new();
        for elem in ids.into_iter() {
            let (description, digest) = elem.borrow();
            writeln!(out, r#"digest!("{digest}"), // {description}"#).unwrap();
        }
        out
    }

    // Format a list of control IDs, include the names as data in a tuple of (&str, Digest)
    fn format_control_ids_with_name(
        ids: impl IntoIterator<Item = impl Borrow<(String, Digest)>>,
    ) -> String {
        let mut out = String::new();
        for elem in ids.into_iter() {
            let (name, digest) = elem.borrow();
            writeln!(out, r#"("{name}", digest!("{digest}")),"#).unwrap();
        }
        out
    }

    pub fn run(&self) {
        let poseidon2_control_ids = Self::generate_rv32im_control_ids();
        Self::generate_recursion_control_ids(poseidon2_control_ids);
    }

    fn generate_rv32im_control_ids() -> Vec<(String, Digest)> {
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
            Self::format_control_ids(control_id_sha256),
            Self::format_control_ids(&control_id_poseidon2),
            Self::format_control_ids(control_id_blake2b),
        );
        tracing::debug!("contents of rv32im control_id.rs:\n{contents}");

        tracing::info!("writing control ids to {CONTROL_ID_PATH_RV32IM}");
        std::fs::write(CONTROL_ID_PATH_RV32IM, contents).unwrap();

        // Use rustfmt to format the file.
        Command::new("rustfmt")
            .arg(CONTROL_ID_PATH_RV32IM)
            .status()
            .expect("failed to format {CONTROL_ID_PATH_RV32IM}");

        // Return the control IDs that should be included in the allowed control IDs that are used
        // by default in segment receipt verification, and in forming the control root.
        control_id_poseidon2[..=DEFAULT_MAX_PO2 - MIN_CYCLES_PO2].to_vec()
    }

    fn generate_recursion_control_ids(poseidon2_rv32im_control_ids: Vec<(String, Digest)>) {
        // Recursion programs (ZKRs) that are to be included in the allowed set, used in the
        // default verifier context.
        // NOTE: We use an allow list here, rather than including all ZKRs in the zip archive,
        // because there may be ZKRs included only for tests, or ones that are not part of the main
        // set of allowed programs (e.g. accelerators, and po2 22-24). Those programs can be
        // enabled by using a custom VerifierContext.
        let allowed_zkr_names: HashSet<String> = ["join.zkr", "resolve.zkr", "identity.zkr"]
            .map(str::to_string)
            .into_iter()
            .chain((MIN_LIFT_PO2..=DEFAULT_MAX_PO2).map(|i| format!("lift_{i}.zkr")))
            .collect();

        tracing::info!("unzipping recursion programs (zkrs)");
        let zkrs = get_all_zkrs().unwrap();

        let poseidon2_control_ids =
            Self::generate_recursion_control_ids_with_hash(&zkrs, "poseidon2");
        let sha256_control_ids = Self::generate_recursion_control_ids_with_hash(&zkrs, "sha-256");

        let allowed_control_ids: Vec<(String, Digest)> = poseidon2_rv32im_control_ids
            .iter()
            .cloned()
            .chain(
                poseidon2_control_ids
                    .iter()
                    .filter(|(name, _digest)| allowed_zkr_names.contains(name))
                    .map(|(name, digest)| (format!("recursion {name}"), *digest)),
            )
            .collect();

        // Calculate a Merkle root for the allowed control IDs and add it to the file.
        let merkle_group = MerkleGroup::new(
            allowed_control_ids
                .iter()
                .map(|(_name, digest)| *digest)
                .collect(),
        )
        .unwrap();
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let allowed_control_root = merkle_group.calc_root(hashfn);
        tracing::info!("Computed allowed_control_root: {allowed_control_root}");

        let bn254_identity_control_id = Self::generate_identity_bn254_control_id();
        tracing::info!("Computed bn254_identity_control_id: {bn254_identity_control_id}");
        let contents = format!(
            include_str!("templates/control_id_zkr.rs"),
            MIN_LIFT_PO2,
            Self::format_control_ids(&allowed_control_ids),
            allowed_control_root,
            bn254_identity_control_id,
            poseidon2_control_ids.len(),
            Self::format_control_ids_with_name(&poseidon2_control_ids),
            sha256_control_ids.len(),
            Self::format_control_ids_with_name(&sha256_control_ids),
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

        zkrs.iter()
            .map(|(name, encoded_program)| {
                let program = Program::from_encoded(encoded_program, RECURSION_PO2);

                tracing::info!("computing control ID for {name} with {hashfn}");
                let control_id = program.compute_control_id(hash_suite.clone());

                tracing::debug!("{name} control id: {control_id:?}");
                (name.clone(), control_id)
            })
            .collect()
    }

    pub fn generate_identity_bn254_control_id() -> Digest {
        let encoded_program = get_zkr("identity.zkr").unwrap();
        let program = Program::from_encoded(&encoded_program, RECURSION_PO2);
        program.compute_control_id(Poseidon254HashSuite::new_suite())
    }
}
