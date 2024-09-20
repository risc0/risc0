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

use crate::{
    byte_poly,
    ecdsa_verify::{ECDSA_VERIFY_32 /*ECDSA_VERIFY_256*/, ECDSA_VERIFY_8}, // TODO clean up what's included
    prove,
    verify,
    BigIntContext,
    BIGINT_PO2,
};
use anyhow::Result;
use num_bigint::BigUint;
use num_traits::Num;
use risc0_circuit_recursion::{prove::Prover, CHECKED_COEFFS_PER_POLY};
use risc0_zkp::core::hash::{poseidon2::Poseidon2HashSuite, sha};
use risc0_zkp::field::Elem;
use test_log::test;
use tracing::trace;

fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}

fn golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("9d"), // base_pt_x: 157
        from_hex("22"), // base_pt_y: 34
        from_hex("78"), // pub_key_x: 120
        from_hex("94"), // pub_key_y: 148
        from_hex("05"), // msg_hash: 5
        from_hex("69"), // r: 105
        from_hex("b0"), // s: 176
    ])
}

fn run_bigint() -> Result<BigIntContext> {
    let mut ctx = BigIntContext {
        in_values: golden_values(),
        ..Default::default()
    };
    crate::generated::ecdsa_verify_8(&mut ctx)?;
    Ok(ctx)
}

fn run_bigint_32() -> Result<BigIntContext> {
    let mut ctx = BigIntContext {
        in_values: golden_values(),
        ..Default::default()
    };
    crate::generated::ecdsa_verify_32(&mut ctx)?;
    Ok(ctx)
}

// fn run_bigint_256() -> Result<BigIntContext> {
//     let mut ctx = BigIntContext {
//         in_values: golden_values(),
//         ..Default::default()
//     };
//     crate::generated::ecdsa_verify_256(&mut ctx)?;
//     Ok(ctx)
// }

#[test]
fn test_zkr() -> anyhow::Result<()> {
    // TODO: Switch over to the test_harness.rs code
    let ctx = run_bigint()?;

    let hash_suite = Poseidon2HashSuite::new_suite();

    let mut all_coeffs: Vec<u32> = Vec::new();
    for witness in ctx
        .constant_witness
        .iter()
        .chain(ctx.public_witness.iter())
        .chain(ctx.private_witness.iter())
    {
        for chunk in witness.chunks(CHECKED_COEFFS_PER_POLY) {
            let mut bytes: Vec<u8> = chunk
                .iter()
                .map(|b| u8::try_from(*b).expect("Byte out of range in witness coeffs"))
                .collect();
            while bytes.len() < CHECKED_COEFFS_PER_POLY {
                bytes.push(0);
            }

            for word in bytes.chunks(4) {
                all_coeffs.push(u32::from_le_bytes(
                    word.try_into().expect("Partial word present in witness?"),
                ));
            }
        }
    }

    let public_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
    trace!("public_digest: {public_digest}");
    let private_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    trace!("private_digest: {private_digest}");
    let folded = (&*hash_suite.hashfn).hash_pair(&public_digest, &private_digest);
    trace!("folded: {folded}");

    let mut rng = (&*hash_suite.rng).new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();

    let program = crate::zkr::get_zkr("ecdsa_verify_8.zkr", /*po2=*/ 14)?;

    let mut prover = Prover::new(program, "poseidon2");
    prover.add_input(&[0u32; 8]); //control id
    prover.add_input(&z.to_u32_words());
    prover.add_input(&all_coeffs);
    let receipt = prover.run()?;

    trace!("rsa receipt: {receipt:?}");

    risc0_zkp::verify::verify(
        &risc0_circuit_recursion::CIRCUIT,
        &hash_suite,
        &receipt.seal,
        |_, _| Ok(()),
    )?;

    Ok(())
}

#[test]
fn prove_and_verify_ecdsa_verify() -> Result<()> {
    let [base_pt_x, base_pt_y, pub_key_x, pub_key_y, msg_hash, r, s] =
        golden_values().try_into().unwrap();
    let claim = crate::ecdsa_verify::claim(
        &ECDSA_VERIFY_8,
        base_pt_x,
        base_pt_y,
        pub_key_x,
        pub_key_y,
        msg_hash,
        r,
        s,
    );
    let zkr = crate::zkr::get_zkr("ecdsa_verify_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ECDSA_VERIFY_8, zkr)?;
    // ecdsa_verify::<sha::Impl>(/*rsa_bits=*/ 8, BIGINT_PO2, &claim, &receipt)?; // TODO bitwidth
    // verify::<sha::Impl>(&crate::rsa::RSA_256, &claim, &receipt)?;
    verify::<sha::Impl>(&crate::ecdsa_verify::ECDSA_VERIFY_8, &[&claim], &receipt)?;
    Ok(())
}

#[test]
fn test_zkr_32() -> anyhow::Result<()> {
    // TODO: Switch over to the test_harness.rs code
    let ctx = run_bigint_32()?;

    let hash_suite = Poseidon2HashSuite::new_suite();

    let mut all_coeffs: Vec<u32> = Vec::new();
    for witness in ctx
        .constant_witness
        .iter()
        .chain(ctx.public_witness.iter())
        .chain(ctx.private_witness.iter())
    {
        for chunk in witness.chunks(CHECKED_COEFFS_PER_POLY) {
            let mut bytes: Vec<u8> = chunk
                .iter()
                .map(|b| u8::try_from(*b).expect("Byte out of range in witness coeffs"))
                .collect();
            while bytes.len() < CHECKED_COEFFS_PER_POLY {
                bytes.push(0);
            }

            for word in bytes.chunks(4) {
                all_coeffs.push(u32::from_le_bytes(
                    word.try_into().expect("Partial word present in witness?"),
                ));
            }
        }
    }

    let public_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
    trace!("public_digest: {public_digest}");
    let private_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    trace!("private_digest: {private_digest}");
    let folded = (&*hash_suite.hashfn).hash_pair(&public_digest, &private_digest);
    trace!("folded: {folded}");

    let mut rng = (&*hash_suite.rng).new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();

    let program = crate::zkr::get_zkr("ecdsa_verify_32.zkr", /*po2=*/ 14)?;

    let mut prover = Prover::new(program, "poseidon2");
    prover.add_input(&[0u32; 8]); //control id
    prover.add_input(&z.to_u32_words());
    prover.add_input(&all_coeffs);
    let receipt = prover.run()?;

    trace!("rsa receipt: {receipt:?}");

    risc0_zkp::verify::verify(
        &risc0_circuit_recursion::CIRCUIT,
        &hash_suite,
        &receipt.seal,
        |_, _| Ok(()),
    )?;

    Ok(())
}

#[test]
fn prove_and_verify_ecdsa_verify_32() -> Result<()> {
    let [base_pt_x, base_pt_y, pub_key_x, pub_key_y, msg_hash, r, s] =
        golden_values().try_into().unwrap();
    let claim = crate::ecdsa_verify::claim(
        &ECDSA_VERIFY_32,
        base_pt_x,
        base_pt_y,
        pub_key_x,
        pub_key_y,
        msg_hash,
        r,
        s,
    );
    let zkr = crate::zkr::get_zkr("ecdsa_verify_32.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ECDSA_VERIFY_32, zkr)?;
    verify::<sha::Impl>(&crate::ecdsa_verify::ECDSA_VERIFY_32, &[&claim], &receipt)?;
    Ok(())
}

// #[test]
// fn test_zkr_256() -> anyhow::Result<()> {
//     // TODO: Switch over to the test_harness.rs code
//     let ctx = run_bigint_256()?;

//     let hash_suite = Poseidon2HashSuite::new_suite();

//     let mut all_coeffs: Vec<u32> = Vec::new();
//     for witness in ctx
//         .constant_witness
//         .iter()
//         .chain(ctx.public_witness.iter())
//         .chain(ctx.private_witness.iter())
//     {
//         for chunk in witness.chunks(CHECKED_COEFFS_PER_POLY) {
//             let mut bytes: Vec<u8> = chunk
//                 .iter()
//                 .map(|b| u8::try_from(*b).expect("Byte out of range in witness coeffs"))
//                 .collect();
//             while bytes.len() < CHECKED_COEFFS_PER_POLY {
//                 bytes.push(0);
//             }

//             for word in bytes.chunks(4) {
//                 all_coeffs.push(u32::from_le_bytes(
//                     word.try_into().expect("Partial word present in witness?"),
//                 ));
//             }
//         }
//     }

//     let public_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
//     trace!("public_digest: {public_digest}");
//     let private_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
//     trace!("private_digest: {private_digest}");
//     let folded = (&*hash_suite.hashfn).hash_pair(&public_digest, &private_digest);
//     trace!("folded: {folded}");

//     let mut rng = (&*hash_suite.rng).new_rng();
//     rng.mix(&folded);
//     let z = rng.random_ext_elem();

//     let program = crate::zkr::get_zkr("ecdsa_verify_256.zkr", /*po2=*/ 14)?;

//     let mut prover = Prover::new(program, "poseidon2");
//     prover.add_input(&[0u32; 8]); //control id
//     prover.add_input(&z.to_u32_words());
//     prover.add_input(&all_coeffs);
//     let receipt = prover.run()?;

//     trace!("rsa receipt: {receipt:?}");

//     risc0_zkp::verify::verify(
//         &risc0_circuit_recursion::CIRCUIT,
//         &hash_suite,
//         &receipt.seal,
//         |_, _| Ok(()),
//     )?;

//     Ok(())
// }

// #[test]
// fn prove_and_verify_ecdsa_verify_256() -> Result<()> {
//     let [base_pt_x, base_pt_y, pub_key_x, pub_key_y, msg_hash, r, s] =
//         golden_values().try_into().unwrap();
//     let claim = crate::ecdsa_verify::claim(
//         &ECDSA_VERIFY_256,
//         base_pt_x,
//         base_pt_y,
//         pub_key_x,
//         pub_key_y,
//         msg_hash,
//         r,
//         s,
//     );
//     let zkr = crate::zkr::get_zkr("ecdsa_verify_256.zkr", BIGINT_PO2)?;
//     let receipt = prove::<sha::Impl>(&[&claim], &ECDSA_VERIFY_256, zkr)?;
//     // ecdsa_verify::<sha::Impl>(/*rsa_bits=*/ 8, BIGINT_PO2, &claim, &receipt)?; // TODO bitwidth
//     // verify::<sha::Impl>(&crate::rsa::RSA_256, &claim, &receipt)?;
//     verify::<sha::Impl>(&crate::ecdsa_verify::ECDSA_VERIFY_256, &[&claim], &receipt)?;
//     Ok(())
// }
