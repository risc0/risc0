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

// use substrate_bn::Fq;
use bn254_methods::{BN254_VERIFY_ELF, BN254_VERIFY_ID};
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover};

/// Prove and get the receipt for an example of (batch) pairing
///
/// This example demonstrates the core pairing functionality that could be used
/// to make cryptographic operations like signature schemes; it is a toy example
/// and should not be used directly except as an example.
///
/// The specific operation demonstrated is that, given base points g1 ∈ G1 and
/// g2 ∈ G2 as well as random scalars a and b, the result of the batch pairing
/// operation
///    pair(a × g1, b × g2) * pair(g1, -ab × g2)
/// is the identity.
fn prove_pairing() -> Receipt {
    // g1 and g2 are the generators from EIP-197
    let g1_compressed =
        hex::decode("020000000000000000000000000000000000000000000000000000000000000001")
            .expect("valid hex");
    let g2_compressed = hex::decode("0A04D4BF3239F77CEE7B47C7245E9281B3E9C1182D6381A87BBF81F9F2A6254B731DF569CDA95E060BEE91BA69B3F2D103658A7AEA6B10E5BDC761E5715E7EE4BB").expect("valid hex");
    // Factors are arbitrary and were chosen at random
    let a = hex::decode("9c0d02eaaf8e7e7ad09595ef6e3b896f8915124ba5bef9287f0997557580caeb")
        .expect("valid hex");
    let b = hex::decode("db6764642f7bb1f415d93fcd5aace586161ec2e4305f0d6fb57dbabf1d141a5b")
        .expect("valid hex");
    let input = bn254_core::Inputs {
        g1_compressed,
        g2_compressed,
        a,
        b,
    };

    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();

    let prover = default_prover();

    prover.prove(env, BN254_VERIFY_ELF).unwrap().receipt
}

fn main() {
    let receipt = prove_pairing();
    receipt.verify(BN254_VERIFY_ID).unwrap();

    let is_one: bool = receipt
        .journal
        .decode()
        .expect("Journal should contain a single `bool`");
    println!("Pairing batch should give one; did it? {is_one}");
}

#[test]
#[gpu_guard::gpu_guard(skip_if_dev_mode = true)]
fn test_pairing() {
    assert!(
        prove_pairing().journal.decode::<bool>().unwrap(),
        "Pairing expected to give identity"
    );
}
