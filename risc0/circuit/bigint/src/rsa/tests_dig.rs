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

use num_bigint_dig::BigUint;
use risc0_circuit_bigint_test_methods::RSA_DIG_ELF;
use risc0_zkvm::{get_prover_server, ExecutorEnv, ProverOpts};
use test_log::test;

use crate::zkr::register_zkrs;

// Makes sure the RSA `modpow_65537` accelerator can run in the guest
#[test]
fn guest_compute_dig() {
    // Test using small inputs based on Fermat's Little Theorem
    // (Since 65537 is prime, a = modpow_65537(a, 65537) for any 0 <= a < 65537)
    let base = BigUint::new(vec!(0x47)); // arbitrary (but less than 65537)
    let modulus = BigUint::new(vec!(0x010001)); // 65537
    let expected_result = base.clone();
    let inputs = vec![[base, modulus]];
    let env = ExecutorEnv::builder()
        .write(&inputs)
        .unwrap()
        .build()
        .unwrap();

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast()).unwrap();
    let result: Vec<BigUint> = prover
        .prove(env, RSA_DIG_ELF)
        .unwrap()
        .receipt
        .journal
        .decode()
        .unwrap();
    assert_eq!(result[0], expected_result);
}