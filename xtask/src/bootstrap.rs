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

use std::{borrow::Borrow, collections::HashSet, fmt::Write, process::Command, sync::Arc};

use clap::Parser;
use risc0_circuit_keccak::{KECCAK_PO2_RANGE, prove::zkr::get_keccak_zkr};
use risc0_circuit_recursion::prove::zkr::{get_all_zkrs, get_zkr};
use risc0_zkp::core::{
    digest::Digest,
    hash::{
        hash_suite_from_name, poseidon_254::Poseidon254HashSuite, poseidon2::Poseidon2HashSuite,
    },
};
use risc0_zkvm::{
    DEFAULT_MAX_PO2, RECURSION_PO2,
    recursion::{MerkleGroup, Program},
};

#[derive(Parser)]
pub struct Bootstrap;

const CONTROL_ID_PATH_RECURSION: &str = "risc0/circuit/recursion/src/control_id.rs";
const CONTROL_ID_PATH_KECCAK: &str = "risc0/circuit/keccak/src/control_id.rs";

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

    // Format a list of control IDs, including the names as data in a tuple of (&str, Digest)
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
        Self::generate_recursion_control_ids();
        Self::bootstrap_keccak();
    }

    fn rustfmt(path: &str) {
        Command::new("rustfmt")
            .arg(path)
            .status()
            .unwrap_or_else(|_| panic!("failed to format {path}"));
    }

    fn generate_recursion_control_ids() {
        let allowed_zkr_names: HashSet<String> = [
            "join.zkr",
            "join_povw.zkr",
            "join_unwrap_povw.zkr",
            "resolve.zkr",
            "resolve_povw.zkr",
            "resolve_unwrap_povw.zkr",
            "identity.zkr",
            "unwrap_povw.zkr",
            "union.zkr",
        ]
        .map(str::to_string)
        .into_iter()
        .chain((MIN_LIFT_PO2..=DEFAULT_MAX_PO2).map(|i| format!("lift_rv32im_v2_{i}.zkr")))
        .chain((MIN_LIFT_PO2..=DEFAULT_MAX_PO2).map(|i| format!("lift_rv32im_v2_povw_{i}.zkr")))
        .collect();

        tracing::info!("Using allowed_zkr_names {allowed_zkr_names:#?}");

        tracing::info!("Unzipping recursion programs (zkrs)");
        let zkrs = get_all_zkrs().unwrap();

        tracing::info!(
            "Unzipped zkrs list is {:#?}",
            zkrs.iter()
                .map(|(name, _)| name)
                .cloned()
                .collect::<Vec<_>>()
        );

        let poseidon2_suite = Arc::new(Poseidon2HashSuite::new_suite());
        let poseidon2_control_ids =
            Self::generate_recursion_control_ids_with_hash(&zkrs, poseidon2_suite.clone());
        let sha256_control_ids = Self::generate_recursion_control_ids_with_hash(
            &zkrs,
            Arc::new(hash_suite_from_name("sha-256").unwrap()),
        );

        let allowed_control_ids: Vec<(String, Digest)> = poseidon2_control_ids
            .iter()
            .filter(|(name, _digest)| allowed_zkr_names.contains(name))
            .map(|(name, digest)| (format!("recursion {name}"), *digest))
            .collect();
        tracing::info!("Calculate allowed_control_ids {allowed_control_ids:#?}");

        let merkle_group = MerkleGroup::new(
            allowed_control_ids
                .iter()
                .map(|(_name, digest)| *digest)
                .collect(),
        )
        .unwrap();

        let allowed_control_root = merkle_group.calc_root(poseidon2_suite.hashfn.as_ref());
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

        Self::rustfmt(CONTROL_ID_PATH_RECURSION);
    }

    pub fn generate_recursion_control_ids_with_hash(
        zkrs: &[(String, Vec<u32>)],
        hash_suite: Arc<dyn risc0_zkp::core::hash::HashSuite>,
    ) -> Vec<(String, Digest)> {
        zkrs.par_iter()
            .map(|(name, encoded_program)| {
                let program = Program::from_encoded(encoded_program, RECURSION_PO2);
                let control_id = program.compute_control_id(hash_suite.clone()).unwrap();
                (name.clone(), control_id)
            })
            .collect()
    }

    pub fn generate_identity_bn254_control_id() -> Digest {
        let program = get_zkr("identity.zkr", RECURSION_PO2).unwrap();
        program
            .compute_control_id(Poseidon254HashSuite::new_suite())
            .unwrap()
    }

    fn bootstrap_keccak() {
        let poseidon2_suite = Arc::new(Poseidon2HashSuite::new_suite());
        let control_ids = Self::generate_keccak_control_ids(poseidon2_suite.clone());
        let control_root = Self::generate_keccak_control_root(
            control_ids.iter().map(|(_name, digest)| *digest).collect(),
            poseidon2_suite,
        );
        let contents = format!(
            include_str!("templates/control_id_keccak.rs"),
            Self::format_control_ids(control_ids),
            control_root
        );
        std::fs::write(CONTROL_ID_PATH_KECCAK, contents).unwrap();

        Self::rustfmt(CONTROL_ID_PATH_KECCAK);
    }

    fn generate_keccak_control_ids(
        hash_suite: Arc<Poseidon2HashSuite>,
    ) -> Vec<(String, Digest)> {
        KECCAK_PO2_RANGE
            .into_par_iter()
            .map(|po2| {
                let program = get_keccak_zkr(po2).unwrap();
                let control_id = program.compute_control_id(hash_suite.clone()).unwrap();
                (format!("keccak_lift po2={po2}"), control_id)
            })
            .collect()
    }

    fn generate_keccak_control_root(control_ids: Vec<Digest>, hash_suite: Arc<Poseidon2HashSuite>) -> Digest {
        let group = MerkleGroup::new(control_ids).unwrap();
        group.calc_root(hash_suite.hashfn.as_ref())
    }
}
