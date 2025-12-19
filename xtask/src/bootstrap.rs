// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{borrow::Borrow, collections::HashSet, fmt::Write, process::Command};

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
    pub fn run(&self) {
        Self::generate_recursion_control_ids();
        Self::bootstrap_keccak();
    }

    fn generate_recursion_control_ids() {
        // Recursion programs (ZKRs) that are to be included in the allowed set, used in the
        // default verifier context.
        // NOTE: We use an allow list here, rather than including all ZKRs in the zip archive,
        // because there may be ZKRs included only for tests, or ones that are not part of the main
        // set of allowed programs (e.g. accelerators, and po2 22-24). Those programs can be
        // enabled by using a custom VerifierContext.
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
        .chain((risc0_circuit_recursion::LIFT_PO2_RANGE).map(|i| format!("lift_rv32im_m3_{i}.zkr")))
        .chain(
            (risc0_circuit_recursion::LIFT_PO2_RANGE)
                .map(|i| format!("lift_rv32im_m3_povw_{i}.zkr")),
        )
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

        let poseidon2_control_ids =
            Self::generate_recursion_control_ids_with_hash(&zkrs, "poseidon2");
        let sha256_control_ids = Self::generate_recursion_control_ids_with_hash(&zkrs, "sha-256");

        let allowed_control_ids: Vec<(String, Digest)> = poseidon2_control_ids
            .iter()
            .filter(|(name, _digest)| allowed_zkr_names.contains(name))
            .map(|(name, digest)| (format!("recursion {name}"), *digest))
            .collect();
        tracing::info!("Calculate allowed_control_ids {allowed_control_ids:#?}");

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
        Self::rustfmt(CONTROL_ID_PATH_RECURSION);
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
                let control_id = program.compute_control_id(hash_suite.clone()).unwrap();

                tracing::debug!("{name} control id: {control_id:?}");
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
        let control_ids = Self::generate_keccak_control_ids();
        let control_root = Self::generate_keccak_control_root(
            control_ids.iter().map(|(_name, digest)| *digest).collect(),
        );
        let contents = format!(
            include_str!("templates/control_id_keccak.rs"),
            Self::format_control_ids(control_ids),
            control_root
        );
        std::fs::write(CONTROL_ID_PATH_KECCAK, contents).unwrap();

        // Use rustfmt to format the file.
        Self::rustfmt(CONTROL_ID_PATH_KECCAK);
    }

    fn generate_keccak_control_ids() -> Vec<(String, Digest)> {
        let mut ret = vec![];
        for po2 in KECCAK_PO2_RANGE {
            let program = get_keccak_zkr(po2).unwrap();
            let hash_suite = Poseidon2HashSuite::new_suite();
            ret.push((
                format!("keccak_lift po2={po2}"),
                program.compute_control_id(hash_suite).unwrap(),
            ))
        }
        ret
    }

    fn generate_keccak_control_root(control_ids: Vec<Digest>) -> Digest {
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let group = MerkleGroup::new(control_ids).unwrap();
        group.calc_root(hashfn)
    }

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

    fn rustfmt(path: &str) {
        Command::new("rustfmt")
            .arg(path)
            .status()
            .unwrap_or_else(|_| panic!("failed to format {path}"));
    }
}
