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

use anyhow::Result;
use num_bigint::BigUint;
use num_traits::Num;
use pretty_assertions::assert_eq;
use risc0_circuit_recursion::{prove::Prover, CHECKED_COEFFS_PER_POLY};
use risc0_zkp::{
    core::hash::poseidon2::Poseidon2HashSuite,
    field::{baby_bear::BabyBearExtElem, Elem},
};
use tracing::trace;

use crate::{byte_poly, BigIntContext};

impl BigIntContext {
    pub(crate) fn from_values(in_values: Vec<BigUint>) -> Self {
        Self {
            in_values,
            ..Default::default()
        }
    }
}

macro_rules! bigint_tests {
    ($($name:ident($zkr:ident, $in:expr, $pub:expr, $priv:expr, $const:expr, $z:expr),)*) => {
        $(
            paste::paste! {
                fn [<$name _values>]() -> Vec<BigUint> {
                    $in.into_iter().map($crate::test_harness::from_hex).collect()
                }

                fn [<$name _context>]() -> anyhow::Result<BigIntContext> {
                    let mut ctx = BigIntContext::from_values([<$name _values>]());
                    $crate::generated::$zkr(&mut ctx)?;
                    Ok(ctx)
                }

                #[test]
                fn [<$name _witgen>]() -> anyhow::Result<()> {
                    let z = BabyBearExtElem::from_subelems(
                        $z.into_iter().map(BabyBearElem::from_u64)
                    );

                    test_witgen(
                        [<$name _context>]()?,
                        witness_test_data(&$pub),
                        witness_test_data(&$priv),
                        witness_test_data(&$const),
                        z,
                    )
                }

                fn [<$name _filename>]() -> &'static str {
                    concat!(stringify!($zkr), ".zkr")
                }

                #[test]
                fn [<$name _zkr>]() -> anyhow::Result<()> {
                    test_zkr([<$name _context>]()?, [<$name _filename>]())
                }

                #[test]
                fn [<$name _prove>]() -> Result<()> {
                    use $crate::generated::[<$zkr:snake:upper>];
                    let claim = BigIntClaim::from_biguints(&[<$zkr:snake:upper>], &[<$name _values>]());
                    let zkr = $crate::zkr::get_zkr([<$name _filename>](), BIGINT_PO2)?;
                    let receipt = $crate::prove::<sha::Impl>(&[&claim], &[<$zkr:snake:upper>], zkr)?;
                    crate::verify::<sha::Impl>(&[<$zkr:snake:upper>], &[&claim], &receipt)?;
                    Ok(())
                }
            }
        )*
    }
}

// Testing that witgen produces expected "golden" values for the public, private, and constant witnesses is only occasionally helpful and is quite tedious to generate golden values for, especially on the longer tests. This test macro omits the witgen test.
macro_rules! bigint_short_tests {
    ($($name:ident($zkr:ident, $in:expr, $z:expr),)*) => {
        $(
            paste::paste! {
                fn [<$name _values>]() -> Vec<BigUint> {
                    $in.into_iter().map($crate::test_harness::from_hex).collect()
                }

                fn [<$name _context>]() -> anyhow::Result<BigIntContext> {
                    let mut ctx = BigIntContext::from_values([<$name _values>]());
                    $crate::generated::$zkr(&mut ctx)?;
                    Ok(ctx)
                }

                fn [<$name _filename>]() -> &'static str {
                    concat!(stringify!($zkr), ".zkr")
                }

                #[test]
                fn [<$name _zkr>]() -> anyhow::Result<()> {
                    test_zkr([<$name _context>]()?, [<$name _filename>]())
                }

                #[test]
                fn [<$name _prove>]() -> Result<()> {
                    use $crate::generated::[<$zkr:snake:upper>];
                    let claim = BigIntClaim::from_biguints(&[<$zkr:snake:upper>], &[<$name _values>]());
                    let zkr = $crate::zkr::get_zkr([<$name _filename>](), BIGINT_PO2)?;
                    let receipt = $crate::prove::<sha::Impl>(&[&claim], &[<$zkr:snake:upper>], zkr)?;
                    crate::verify::<sha::Impl>(&[<$zkr:snake:upper>], &[&claim], &receipt)?;
                    Ok(())
                }
            }
        )*
    }
}

// Tests that input values which should cause failures do cause failures
macro_rules! bigint_should_fail_tests {
    ($($name:ident($zkr:ident, $in:expr),)*) => {
        $(
            paste::paste! {
                fn [<$name _values>]() -> Vec<BigUint> {
                    $in.into_iter().map($crate::test_harness::from_hex).collect()
                }

                fn [<$name _filename>]() -> &'static str {
                    concat!(stringify!($zkr), ".zkr")
                }


                #[test]
                #[should_panic(expected = "Invalid carry computation")]
                fn [<$name _prove_fails>]() -> () {
                    use $crate::generated::[<$zkr:snake:upper>];
                    let claim = BigIntClaim::from_biguints(&[<$zkr:snake:upper>], &[<$name _values>]());
                    let zkr = $crate::zkr::get_zkr([<$name _filename>](), BIGINT_PO2).unwrap();
                    let receipt = $crate::prove::<sha::Impl>(&[&claim], &[<$zkr:snake:upper>], zkr).unwrap();
                    crate::verify::<sha::Impl>(&[<$zkr:snake:upper>], &[&claim], &receipt).unwrap();
                }
            }
        )*
    }
}

pub(crate) use bigint_short_tests;
pub(crate) use bigint_should_fail_tests;
pub(crate) use bigint_tests;

pub(crate) fn test_witgen(
    ctx: BigIntContext,
    pub_wit: Vec<Vec<i32>>,
    priv_wit: Vec<Vec<i32>>,
    const_wit: Vec<Vec<i32>>,
    gold_z: BabyBearExtElem,
) -> Result<()> {
    assert_eq!(ctx.public_witness, pub_wit);
    assert_eq!(ctx.private_witness, priv_wit);
    assert_eq!(ctx.constant_witness, const_wit);

    let hash_suite = Poseidon2HashSuite::new_suite();

    let public_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
    trace!("public_digest: {public_digest}");
    let private_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    trace!("private_digest: {private_digest}");
    let folded = hash_suite.hashfn.hash_pair(&public_digest, &private_digest);
    trace!("folded: {folded}");

    let mut rng = hash_suite.rng.new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();
    assert_eq!(z, gold_z);

    Ok(())
}

pub(crate) fn test_zkr(ctx: BigIntContext, zkr_name: &str) -> Result<()> {
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
    let private_digest = byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    let folded = hash_suite.hashfn.hash_pair(&public_digest, &private_digest);

    let mut rng = hash_suite.rng.new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();

    tracing::trace!("test_zkr: z is {z:?}");

    let program = crate::zkr::get_zkr_for_test(zkr_name)?;

    tracing::trace!("test_zkr: Program created from ZKR named {zkr_name:?}");

    let mut prover = Prover::new(program, "poseidon2");
    tracing::trace!("test_zkr: Prover made");
    prover.add_input(&[0u32; 8]); //control id
    prover.add_input(&z.to_u32_words());
    prover.add_input(&all_coeffs);
    tracing::trace!("test_zkr: Inputs added, all_coeffs is {all_coeffs:?}");
    let receipt = prover.run()?;

    tracing::trace!("test_zkr: receipt is {receipt:?}");

    risc0_zkp::verify::verify(
        &risc0_circuit_recursion::CIRCUIT,
        &hash_suite,
        &receipt.seal,
        |_, _| Ok(()),
    )?;

    Ok(())
}

pub(crate) fn witness_test_data(data: &[&str]) -> Vec<Vec<i32>> {
    data.iter().map(|d| byte_poly::from_hex(d)).collect()
}

pub(crate) fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}
