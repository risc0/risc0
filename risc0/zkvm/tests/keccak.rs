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

#![cfg(feature = "prove")]

use risc0_circuit_keccak::{
    KECCAK_CONTROL_IDS, KECCAK_CONTROL_ROOT, KECCAK_PO2_RANGE, prove::zkr::get_keccak_zkr,
};
use risc0_circuit_keccak_methods::{KECCAK_ELF, KECCAK_ID};
use risc0_zkp::{
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite},
    digest,
};
use risc0_zkvm::{ExecutorEnv, ProverOpts, get_prover_server, recursion::MerkleGroup};

fn run_test(po2: u32, claim_digest: Digest) {
    let to_guest: (Digest, u32) = (claim_digest, po2);

    let env = ExecutorEnv::builder()
        .write(&to_guest)
        .unwrap()
        .keccak_max_po2(po2)
        .unwrap()
        .build()
        .unwrap();

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, KECCAK_ELF).unwrap().receipt;

    // Make sure this receipt actually depends on the assumption;
    // otherwise this test might give a false negative.
    assert!(
        !receipt
            .inner
            .composite()
            .unwrap()
            .assumption_receipts
            .is_empty()
    );

    // Make sure the receipt verifies OK
    receipt.verify(KECCAK_ID).unwrap();
}

#[test]
#[cfg_attr(feature = "cuda", gpu_guard::gpu_guard)]
fn keccak_po2_16() {
    run_test(
        16,
        digest!("b83c10da0c23587bf318cbcec2c2ac0260dbd6c0fa6905df639f8f6056f0d56c"),
    );
}

#[test]
#[cfg_attr(feature = "cuda", gpu_guard::gpu_guard)]
#[ignore]
fn keccak_po2_17() {
    run_test(
        17,
        digest!("a920de1111b7fa680c29f0dbd8eea64a3b9e2994de1b242e30f53fd8cd727ba2"),
    );
}

fn compute_control_ids() -> Vec<Digest> {
    let mut ret = vec![];
    for po2 in KECCAK_PO2_RANGE {
        let program = get_keccak_zkr(po2).unwrap();
        let hash_suite = Poseidon2HashSuite::new_suite();
        ret.push(program.compute_control_id(hash_suite).unwrap())
    }
    ret
}

fn compute_control_root() -> Digest {
    let control_ids = compute_control_ids();
    let hash_suite = Poseidon2HashSuite::new_suite();
    let hashfn = hash_suite.hashfn.as_ref();
    let group = MerkleGroup::new(control_ids).unwrap();
    group.calc_root(hashfn)
}

// Makes sure our included control IDs are what we expect
#[test]
fn control_ids() {
    assert_eq!(KECCAK_CONTROL_IDS, compute_control_ids());
}

#[test]
fn control_roots() {
    assert_eq!(KECCAK_CONTROL_ROOT, compute_control_root());
}
