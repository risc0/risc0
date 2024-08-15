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

use crate::test_harness::{from_hex, test_witgen, test_zkr, witness_test_data};
use crate::{control_id, prove, BigIntClaim, BigIntContext, BytePoly, BIGINT_PO2};
use anyhow::Result;
use num_bigint::BigUint;
use risc0_zkp::core::hash::sha;
use risc0_zkp::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    Elem, ExtElem,
};
use test_log::test;

pub(crate) mod generated {
    #![allow(dead_code)]

    use crate::codegen_prelude::*;
    include! {"bigint.rs.inc"}
}

fn golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&[])
}

// add (8 bit) Tests

fn addition_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("01"), // lhs:      ...
        from_hex("01"), // rhs:      ...
        from_hex("02"), // expected: ...
    ])
}

fn addition_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [962489600, 684492455, 226996643, 1609451183]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn addition_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["01", "01", "0200"])
}

fn addition_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["2222"])
}

fn run_addition_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = addition_test_golden_values().try_into().unwrap();
    generated::add_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn addition_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_addition_test()?,
        addition_golden_public_witness(),
        addition_golden_private_witness(),
        golden_constant_witness(),
        addition_test_golden_z(),
    )
}

#[test]
fn addition_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_addition_test()?, "add_test_8.zkr")
}

#[test]
fn addition16_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_addition16_test()?, "add_test_16.zkr")
}

// Runs the end-to-end test for Add
#[test]
fn addition_test_prove_and_verify() -> Result<()> {
    use generated::ADD_TEST_8;
    let [lhs, rhs, expected] = addition_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&ADD_TEST_8, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("add_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ADD_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&ADD_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

// add (16 bit) Tests

fn addition16_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("4701"), // lhs:      ...
        from_hex("a301"), // rhs:      ...
        from_hex("ea02"), // expected: ...
    ])
}

fn addition16_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1628396028, 1163057258, 1159504641, 518219607]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn addition16_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["0147", "01a3", "02ea00"])
}

fn addition16_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["222222"])
}

fn run_addition16_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = addition16_test_golden_values().try_into().unwrap();
    generated::add_test_16(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn addition16_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_addition16_test()?,
        addition16_golden_public_witness(),
        addition16_golden_private_witness(),
        golden_constant_witness(),
        addition16_test_golden_z(),
    )
}

// Runs the end-to-end test for Add (16 bit)
#[test]
fn addition16_test_prove_and_verify() -> Result<()> {
    use generated::ADD_TEST_16;
    let [lhs, rhs, expected] = addition16_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&ADD_TEST_16, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("add_test_16.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ADD_TEST_16, zkr)?;
    crate::verify::<sha::Impl>(&ADD_TEST_16, &[&claim], &receipt)?;
    Ok(())
}

fn add128_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [28354054, 127316002, 814881045, 149531627]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn add128_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("330e091fd68889efcc15be1e6244d811"), // lhs: ...
        from_hex("748ac69a07f0e07a234ac687f6749ea8"), // rhs:      ...
        from_hex("a798cfb9de796a69ef6084a658b976b9"), // expected:      ...
    ])
}

fn add128_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "11d844621ebe15ccef8988d61f090e33",
        "a89e74f687c64a237ae0f0079ac68a74",
        "b976b958a68460ef696a79deb9cf98a700",
    ])
}

fn add128_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["2223222322232222232323222222222222"])
}

fn run_add128_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = add128_test_golden_values().try_into().unwrap();
    generated::add_test_128(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn add128_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_add128_test()?,
        add128_test_golden_public_witness(),
        add128_test_golden_private_witness(),
        golden_constant_witness(),
        add128_test_golden_z(),
    )
}

#[test]
fn add128_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_add128_test()?, "add_test_128.zkr")
}

#[test]
fn add128_test_prove_and_verify() -> Result<()> {
    use generated::ADD_TEST_128;
    let [lhs, rhs, expected] = add128_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&ADD_TEST_128, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("add_test_128.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ADD_TEST_128, zkr)?;
    crate::verify::<sha::Impl>(&ADD_TEST_128, &[&claim], &receipt)?;
    Ok(())
}

// Add with a carry beyond the original size of the inputs

fn add128_carry_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1617379037, 864333486, 348868579, 937145574]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn add128_carry_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("a0000000000000000000000000000000"), // lhs: ...
        from_hex("a0000000000000000000000000000000"), // rhs:      ...
        from_hex("0140000000000000000000000000000000"), // expected:      ...
    ])
}

fn add128_carry_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "000000000000000000000000000000a0",
        "000000000000000000000000000000a0",
        "0000000000000000000000000000004001",
    ])
}

fn add128_carry_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["2222222222222222222222222222222322"])
}

fn run_add128_carry_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = add128_carry_test_golden_values().try_into().unwrap();
    generated::add_test_128(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn add128_carry_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_add128_carry_test()?,
        add128_carry_test_golden_public_witness(),
        add128_carry_test_golden_private_witness(),
        golden_constant_witness(),
        add128_carry_test_golden_z(),
    )
}

#[test]
fn add128_carry_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_add128_carry_test()?, "add_test_128.zkr")
}

#[test]
fn add128_carry_test_prove_and_verify() -> Result<()> {
    use generated::ADD_TEST_128;
    let [lhs, rhs, expected] = add128_carry_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&ADD_TEST_128, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("add_test_128.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ADD_TEST_128, zkr)?;
    crate::verify::<sha::Impl>(&ADD_TEST_128, &[&claim], &receipt)?;
    Ok(())
}

// add16 const style Test
// Does a 16 bit add test with the same data as used in the const add test

#[test]
fn add16cs_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_add16cs_test()?, "add_test_16.zkr")
}

fn add16cs_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("4747"), // lhs:      ...
        from_hex("0033"), // rhs:      ...
        from_hex("477a"), // expected: ...
    ])
}

fn add16cs_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1227093942, 1425511815, 962696871, 1223972504]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn add16cs_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["4747", "3300", "7a4700"])
}

fn add16cs_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["222222"])
}

fn run_add16cs_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = add16cs_test_golden_values().try_into().unwrap();
    generated::add_test_16(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn add16cs_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_add16cs_test()?,
        add16cs_golden_public_witness(),
        add16cs_golden_private_witness(),
        golden_constant_witness(),
        add16cs_test_golden_z(),
    )
}

// Runs the end-to-end test for Add (16 bit)
#[test]
fn add16cs_test_prove_and_verify() -> Result<()> {
    use generated::ADD_TEST_16;
    let [lhs, rhs, expected] = add16cs_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&ADD_TEST_16, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("add_test_16.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &ADD_TEST_16, zkr)?;
    crate::verify::<sha::Impl>(&ADD_TEST_16, &[&claim], &receipt)?;
    Ok(())
}

// add_const Tests

fn add_const_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("33"),   // inp:      ...
        from_hex("477a"), // expected: ...
    ])
}

fn add_const_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1842985763, 737835842, 1760309670, 1101972070]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn add_const_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&["4747"])
}

fn add_const_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["33", "7a4700"])
}

fn add_const_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["222222"])
}

fn run_add_const_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = add_const_test_golden_values().try_into().unwrap();
    generated::const_add_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn add_const_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_add_const_test()?,
        add_const_golden_public_witness(),
        add_const_golden_private_witness(),
        add_const_golden_constant_witness(),
        add_const_test_golden_z(),
    )
}

#[test]
fn add_const_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_add_const_test()?, "const_add_test_8.zkr")
}

// Runs the end-to-end test for Adding a Constant
#[test]
fn add_const_test_prove_and_verify() -> Result<()> {
    use generated::CONST_ADD_TEST_8;
    let [inp, expected] = add_const_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&CONST_ADD_TEST_8, &[inp, expected]);
    let zkr = crate::zkr::get_zkr("const_add_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &CONST_ADD_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&CONST_ADD_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

// const_mul Tests

fn const_mul_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("b7"),     // inp:      ...
        from_hex("3c2fbe"), // expected: ...
    ])
}

fn const_mul_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1727847174, 1070626030, 998371662, 1475457516]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn const_mul_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&["3254"])
}

fn const_mul_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["b7", "be2f3c"])
}

fn const_mul_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["a6bf83", "3f3f3f"])
}

fn run_const_mul_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = const_mul_test_golden_values().try_into().unwrap();
    generated::const_mul_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn const_mul_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_const_mul_test()?,
        const_mul_golden_public_witness(),
        const_mul_golden_private_witness(),
        const_mul_golden_constant_witness(),
        const_mul_test_golden_z(),
    )
}

#[test]
fn const_mul_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_const_mul_test()?, "const_mul_test_8.zkr")
}

// Runs the end-to-end test for the constant 0x5432
#[test]
fn const_mul_test_prove_and_verify() -> Result<()> {
    use generated::CONST_MUL_TEST_8;
    let [inp, expected] = const_mul_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&CONST_MUL_TEST_8, &[inp, expected]);
    let zkr = crate::zkr::get_zkr("const_mul_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &CONST_MUL_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&CONST_MUL_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

// const_add_alt Tests

/// Construct a bigint claim of 0x5432 + 0xb7 == 0x54e9 with a const times a variable
fn const_add_alt_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("b7"),   // inp:      ...
        from_hex("54e9"), // expected: ...
    ])
}

fn const_add_alt_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1159662004, 1670679337, 1194077248, 1372635486]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn const_add_alt_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&["3254"])
}

fn const_add_alt_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["b700", "e95400"])
}

fn const_add_alt_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["222222"])
}

fn run_const_add_alt_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = const_add_alt_test_golden_values().try_into().unwrap();
    generated::const_add_alt_test_16(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn const_add_alt_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_const_add_alt_test()?,
        const_add_alt_golden_public_witness(),
        const_add_alt_golden_private_witness(),
        const_add_alt_golden_constant_witness(),
        const_add_alt_test_golden_z(),
    )
}

#[test]
fn const_add_alt_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_const_add_alt_test()?, "const_add_alt_test_16.zkr")
}

// Runs the end-to-end test for the constant 0x5432
#[test]
fn const_add_alt_test_prove_and_verify() -> Result<()> {
    use generated::CONST_ADD_ALT_TEST_16;
    let [inp, expected] = const_add_alt_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&CONST_ADD_ALT_TEST_16, &[inp, expected]);
    let zkr = crate::zkr::get_zkr("const_add_alt_test_16.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &CONST_ADD_ALT_TEST_16, zkr)?;
    crate::verify::<sha::Impl>(&CONST_ADD_ALT_TEST_16, &[&claim], &receipt)?;
    Ok(())
}

// const_one Tests

fn const_one_test_golden_values() -> Vec<BigUint> {
    Vec::from([from_hex("01")])
}

fn const_one_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1981369411, 178339811, 860262558, 1122064780]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn const_one_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&["01"])
}

fn const_one_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["01"])
}

fn const_one_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["22"])
}

fn run_const_one_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = const_one_test_golden_values().try_into().unwrap();
    generated::const_one_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn const_one_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_const_one_test()?,
        const_one_golden_public_witness(),
        const_one_golden_private_witness(),
        const_one_golden_constant_witness(),
        const_one_test_golden_z(),
    )
}

#[test]
fn const_one_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_const_one_test()?, "const_one_test_8.zkr")
}

// Runs the end-to-end test for the constant 1
#[test]
fn const_one_test_prove_and_verify() -> Result<()> {
    use generated::CONST_ONE_TEST_8;
    let [inp] = const_one_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&CONST_ONE_TEST_8, &[inp]);
    let zkr = crate::zkr::get_zkr("const_one_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &CONST_ONE_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&CONST_ONE_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

// const_twobyte Tests

/// Construct a bigint claim of 0x1234 - 0x1234 == 0 with a const minus a variable
fn const_twobyte_test_golden_values() -> Vec<BigUint> {
    Vec::from([from_hex("1234")])
}

fn const_twobyte_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [704963733, 1314188424, 65714486, 1269082877]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn const_twobyte_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&["3412"])
}

fn const_twobyte_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["3412"])
}

fn const_twobyte_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["2222"])
}

fn run_const_twobyte_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = const_twobyte_test_golden_values().try_into().unwrap();
    generated::const_twobyte_test_16(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn const_twobyte_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_const_twobyte_test()?,
        const_twobyte_golden_public_witness(),
        const_twobyte_golden_private_witness(),
        const_twobyte_golden_constant_witness(),
        const_twobyte_test_golden_z(),
    )
}

#[test]
fn const_twobyte_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_const_twobyte_test()?, "const_twobyte_test_16.zkr")
}

// Runs the end-to-end test for the constant 0x1234
#[test]
fn const_twobyte_test_prove_and_verify() -> Result<()> {
    use generated::CONST_TWOBYTE_TEST_16;
    let [inp] = const_twobyte_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&CONST_TWOBYTE_TEST_16, &[inp]);
    let zkr = crate::zkr::get_zkr("const_twobyte_test_16.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &CONST_TWOBYTE_TEST_16, zkr)?;
    crate::verify::<sha::Impl>(&CONST_TWOBYTE_TEST_16, &[&claim], &receipt)?;
    Ok(())
}

// sub Tests

fn sub8_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [776049965, 343441276, 1146763350, 1587586042]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn sub8_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("ef"), // lhs:      ...
        from_hex("47"), // rhs:      ...
        from_hex("a8"), // expected: ...
    ])
}

fn sub_test_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&[])
}

fn sub8_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["ef", "47", "a8"])
}

fn sub8_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["22"])
}

fn run_sub8_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = sub8_test_golden_values().try_into().unwrap();
    generated::sub_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn sub8_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_sub8_test()?,
        sub8_test_golden_public_witness(),
        sub8_test_golden_private_witness(),
        sub_test_golden_constant_witness(),
        sub8_test_golden_z(),
    )
}

#[test]
fn sub8_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_sub8_test()?, "sub_test_8.zkr")
}

#[test]
fn sub8_test_prove_and_verify() -> Result<()> {
    use generated::SUB_TEST_8;
    let [lhs, rhs, expected] = sub8_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&SUB_TEST_8, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("sub_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &SUB_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&SUB_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

fn sub128_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [890455888, 513281154, 753054158, 64454700]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn sub128_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("a798cfb9de796a69ef6084a658b976b9"), // lhs:      ...
        from_hex("748ac69a07f0e07a234ac687f6749ea8"), // rhs:      ...
        from_hex("330e091fd68889efcc15be1e6244d811"), // expected: ...
    ])
}

fn sub128_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "b976b958a68460ef696a79deb9cf98a7",
        "a89e74f687c64a237ae0f0079ac68a74",
        "11d844621ebe15ccef8988d61f090e33",
    ])
}

fn sub128_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["22212221222122222121212222222222"])
}

fn run_sub128_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = sub128_test_golden_values().try_into().unwrap();
    generated::sub_test_128(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn sub128_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_sub128_test()?,
        sub128_test_golden_public_witness(),
        sub128_test_golden_private_witness(),
        sub_test_golden_constant_witness(),
        sub128_test_golden_z(),
    )
}

#[test]
fn sub128_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_sub128_test()?, "sub_test_128.zkr")
}

#[test]
fn sub128_test_prove_and_verify() -> Result<()> {
    use generated::SUB_TEST_128;
    let [lhs, rhs, expected] = sub128_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&SUB_TEST_128, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("sub_test_128.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &SUB_TEST_128, zkr)?;
    crate::verify::<sha::Impl>(&SUB_TEST_128, &[&claim], &receipt)?;
    Ok(())
}

// mul Tests

fn mul8_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1429446629, 1772489311, 98405109, 498936513]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn mul8_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("ef"),   // lhs:      ...
        from_hex("47"),   // rhs:      ...
        from_hex("4249"), // expected: ...
    ])
}

fn mul_test_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&[])
}

fn mul8_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["ef", "47", "4942"])
}

fn mul8_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["05c3", "201f"])
}

fn run_mul8_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = mul8_test_golden_values().try_into().unwrap();
    generated::mul_test_8(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn mul8_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_mul8_test()?,
        mul8_test_golden_public_witness(),
        mul8_test_golden_private_witness(),
        mul_test_golden_constant_witness(),
        mul8_test_golden_z(),
    )
}

#[test]
fn mul8_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_mul8_test()?, "mul_test_8.zkr")
}

#[test]
fn mul8_test_prove_and_verify() -> Result<()> {
    use generated::MUL_TEST_8;
    let [lhs, rhs, expected] = mul8_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&MUL_TEST_8, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("mul_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &MUL_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&MUL_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

fn mul128_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [1269517810, 1259488229, 1292517392, 1940782769]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn mul128_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        // from_hex("12341234a00a12341234123412341234"), // lhs:      ...
        // from_hex("10000000000000000000000000000003"), // rhs:      ...
        // from_hex("012341234a00a1234123412341234123769c369d301e369c369c369c369c369c"), // expected: ...
        from_hex("a9ff9e10"),         // lhs:      ...
        from_hex("1c1f1d23"),         // rhs:      ...
        from_hex("12ac9e9716ca6c30"), // expected: ...
    ])
}

fn mul128_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "109effa9000000000000000000000000",
        "231d1f1c000000000000000000000000",
        "306cca16979eac12000000000000000000000000000000000000000000000000",
    ])
}

fn mul128_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "071c3b4e48351705050505050505050505050505050505050505050505050505",
        "fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc",
        "0101010101010101010101010101010101010101010101010101010101010101",
        "0404040404040404040404040404040404040404040404040404040404040404",
    ])
}

fn run_mul128_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = mul128_test_golden_values().try_into().unwrap();
    generated::mul_test_128(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn mul128_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_mul128_test()?,
        mul128_test_golden_public_witness(),
        mul128_test_golden_private_witness(),
        mul_test_golden_constant_witness(),
        mul128_test_golden_z(),
    )
}

#[test]
fn mul128_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_mul128_test()?, "mul_test_128.zkr")
}

#[test]
fn mul128_test_prove_and_verify() -> Result<()> {
    use generated::MUL_TEST_128;
    let [lhs, rhs, expected] = mul128_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&MUL_TEST_128, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("mul_test_128.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &MUL_TEST_128, zkr)?;
    crate::verify::<sha::Impl>(&MUL_TEST_128, &[&claim], &receipt)?;
    Ok(())
}

// reduce Tests

fn reduce8_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [247502032, 682060654, 655156825, 1411118715]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn reduce128_test_golden_z() -> BabyBearExtElem {
    BabyBearExtElem::from_subelems(
        [108881840, 768445877, 1224562786, 1348962832]
            .into_iter()
            .map(BabyBearElem::from_u64),
    )
}

fn reduce8_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("af"), // lhs:      ...
        from_hex("11"), // rhs:      ...
        from_hex("05"), // expected: ...
    ])
}

fn reduce128_test_golden_values() -> Vec<BigUint> {
    Vec::from([
        from_hex("13311441233256657667877895590007"), // lhs:      ...
        from_hex("11"),                               // rhs:      ...
        from_hex("07"),                               // expected: ...
    ])
}

fn reduce_test_golden_constant_witness() -> Vec<BytePoly> {
    witness_test_data(&[])
}

fn reduce8_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&["af", "11", "05"])
}

fn reduce128_test_golden_public_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "07005995788767766556322341143113",
        "11000000000000000000000000000000",
        "07000000000000000000000000000000",
    ])
}

fn reduce8_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&["0a", "05", "c3c3", "1f1f", "22"])
}

fn reduce128_test_golden_private_witness() -> Vec<BytePoly> {
    witness_test_data(&[
        "0000c908f807f7061505120231012101",
        "07000000000000000000000000000000",
        "0505120515051505060506050805070505050505050505050505050505050505",
        "fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc",
        "0101010101010101010101010101010101010101010101010101010101010101",
        "0404040404040404040404040404040404040404040404040404040404040404",
        "22222222222222222222222222222222",
    ])
}

fn run_reduce8_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = reduce8_test_golden_values().try_into().unwrap();
    generated::reduce_test_8(&mut ctx)?;
    Ok(ctx)
}

fn run_reduce128_test() -> Result<BigIntContext> {
    let mut ctx = BigIntContext::default();
    ctx.in_values = reduce128_test_golden_values().try_into().unwrap();
    generated::reduce_test_128(&mut ctx)?;
    Ok(ctx)
}

#[test]
fn reduce8_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_reduce8_test()?,
        reduce8_test_golden_public_witness(),
        reduce8_test_golden_private_witness(),
        reduce_test_golden_constant_witness(),
        reduce8_test_golden_z(),
    )
}

#[test]
fn reduce128_test_witgen() -> anyhow::Result<()> {
    test_witgen(
        run_reduce128_test()?,
        reduce128_test_golden_public_witness(),
        reduce128_test_golden_private_witness(),
        reduce_test_golden_constant_witness(),
        reduce128_test_golden_z(),
    )
}

#[test]
fn reduce8_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_reduce8_test()?, "reduce_test_8.zkr")
}

#[test]
fn reduce128_test_zkr() -> anyhow::Result<()> {
    test_zkr(run_reduce128_test()?, "reduce_test_128.zkr")
}

#[test]
fn reduce8_test_prove_and_verify() -> Result<()> {
    use generated::REDUCE_TEST_8;
    let [lhs, rhs, expected] = reduce8_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&REDUCE_TEST_8, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("reduce_test_8.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &REDUCE_TEST_8, zkr)?;
    crate::verify::<sha::Impl>(&REDUCE_TEST_8, &[&claim], &receipt)?;
    Ok(())
}

#[test]
fn reduce128_test_prove_and_verify() -> Result<()> {
    use generated::REDUCE_TEST_128;
    let [lhs, rhs, expected] = reduce128_test_golden_values().try_into().unwrap();
    let claim = BigIntClaim::from_biguints(&REDUCE_TEST_128, &[lhs, rhs, expected]);
    let zkr = crate::zkr::get_zkr("reduce_test_128.zkr", BIGINT_PO2)?;
    let receipt = prove::<sha::Impl>(&[&claim], &REDUCE_TEST_128, zkr)?;
    crate::verify::<sha::Impl>(&REDUCE_TEST_128, &[&claim], &receipt)?;
    Ok(())
}
