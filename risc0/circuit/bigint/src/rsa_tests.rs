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

use std::borrow::Borrow;

use anyhow::Result;
use num_bigint::BigUint;
use risc0_circuit_bigint_test_methods::{RSA_ELF, RSA_ID};
use risc0_zkp::core::hash::sha;
use risc0_zkvm::{get_prover_server, ExecutorEnv, ProverOpts};
use test_log::test;

use crate::{
    rsa::RSA_256_X2,
    test_harness::{bigint_short_tests, from_hex, test_zkr},
    zkr::register_zkrs,
    BigIntClaim, BigIntContext, BIGINT_PO2,
};

// "golden" values are the values from running the C++ version:
// bazelisk run //zirgen/Dialect/BigInt/IR/test:test -- --test

fn golden_values() -> Vec<BigUint> {
    vec![
        from_hex("9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5"),
        from_hex("de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677"),
        from_hex("1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa"),
    ]
}

// name(zkr, in_values)
bigint_short_tests! {
    rsa_test_256(
        rsa_256_x1,
        [
            "9c98f9aacfc0b73c916a824db9afe39673dcb56c42dffe9de5b86d5748aca4d5",
            "de67116c809a5cc876cebb5e8c72d998f983a4d61b499dd9ae23b789a7183677",
            "1fb897fac8aa8870b936631d3af1a17930c8af0ca4376b3056677ded52adf5aa",
        ]
    ),
}

fn run_guest_compose(claims: &[impl Borrow<[BigUint; 3]>]) -> Result<()> {
    let claims: Vec<[BigUint; 3]> = claims.iter().map(Borrow::borrow).cloned().collect();
    let env = ExecutorEnv::builder()
        // Send a & b to the guest
        .write(&claims)?
        .build()?;

    register_zkrs();

    let prover = get_prover_server(&ProverOpts::fast())?;

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, RSA_ELF)?.receipt;

    // Make sure this receipt actually depends on the assumption;
    // otherwise this test might give a false negative.
    assert!(!receipt
        .inner
        .composite()
        .unwrap()
        .assumption_receipts
        .is_empty());

    // Make sure the receipt verifies OK
    receipt.verify(RSA_ID)?;

    Ok(())
}

// Tries a single claim
#[test]
fn guest_compose_oneclaim() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    run_guest_compose(&[&vals]).unwrap()
}

// Completely fills up a zkr's claim-verifying capacity
#[test]
fn guest_compose_iters() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    let claims = vec![&vals; RSA_256_X2.iters];
    run_guest_compose(&claims).unwrap()
}

// Exceeds a zkr's claim-verifying capacity; should not work at all.
#[test]
fn guest_compose_exceed_iters() {
    let vals: [BigUint; 3] = golden_values().try_into().unwrap();

    let claims = vec![&vals; RSA_256_X2.iters + 1];
    run_guest_compose(&claims).expect_err("Expected too many iterations error");
}

// Supplies no claims to the ZKR to verify; at least one is required.
#[test]
fn guest_compose_empty() {
    run_guest_compose(&[] as &[&[BigUint; 3]]).expect_err("Expected empty claims error");
}

// Makes sure composition fails if any of the data changes
#[test]
fn guest_compose_corrupted() {
    for idx in 0..3 {
        let mut vals: [BigUint; 3] = golden_values().try_into().unwrap();
        vals[idx] += 1usize;
        run_guest_compose(&[vals]).expect_err(&format!(
            "Expected zkr verification failure when corrupting RSA value #{idx}"
        ));
    }
}
