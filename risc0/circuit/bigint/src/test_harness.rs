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

use crate::{BigIntContext, BytePoly};
use num_bigint::BigUint;
use num_traits::Num;
use pretty_assertions::assert_eq;
use risc0_circuit_recursion::{prove::Prover, CHECKED_COEFFS_PER_POLY};
use risc0_zkp::{
    core::hash::poseidon2::Poseidon2HashSuite,
    field::{baby_bear::BabyBearExtElem, Elem},
};
use tracing::trace;

pub(crate) fn test_witgen(
    ctx: BigIntContext,
    pub_wit: Vec<BytePoly>,
    priv_wit: Vec<BytePoly>,
    const_wit: Vec<BytePoly>,
    gold_z: BabyBearExtElem,
) -> anyhow::Result<()> {
    assert_eq!(ctx.public_witness, pub_wit);
    assert_eq!(ctx.private_witness, priv_wit);
    assert_eq!(ctx.constant_witness, const_wit);

    let hash_suite = Poseidon2HashSuite::new_suite();

    let public_digest = BytePoly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
    trace!("public_digest: {public_digest}");
    let private_digest = BytePoly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    trace!("private_digest: {private_digest}");
    let folded = (&*hash_suite.hashfn).hash_pair(&public_digest, &private_digest);
    trace!("folded: {folded}");

    let mut rng = (&*hash_suite.rng).new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();
    assert_eq!(z, gold_z);

    Ok(())
}

pub(crate) fn test_zkr(ctx: BigIntContext, zkr_name: &str) -> anyhow::Result<()> {
    tracing::error!("Hello world!!!");

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

    let public_digest = BytePoly::compute_digest(&*hash_suite.hashfn, &ctx.public_witness, 1);
    tracing::error!("public_digest: {public_digest}");
    let private_digest = BytePoly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
    tracing::error!("private_digest: {private_digest}");
    let folded = (&*hash_suite.hashfn).hash_pair(&public_digest, &private_digest);
    tracing::error!("folded: {folded}");

    let mut rng = (&*hash_suite.rng).new_rng();
    rng.mix(&folded);
    let z = rng.random_ext_elem();

    tracing::error!("chkpt A");

    let program = crate::zkr::get_zkr_for_test(zkr_name)?;
    tracing::error!("chkpt B");

    tracing::error!("z is {z:?}");
    tracing::error!("all_coeffs is {all_coeffs:?}");
    let mut prover = Prover::new(program, "poseidon2");
    prover.add_input(&[0u32; 8]); //control id
    prover.add_input(&z.to_u32_words());
    prover.add_input(&all_coeffs);
    let receipt = prover.run()?;
    tracing::error!("chkpt C");

    tracing::error!("Test receipt: {receipt:?}");

    risc0_zkp::verify::verify(
        &risc0_circuit_recursion::CIRCUIT,
        &hash_suite,
        &receipt.seal,
        |_, _| Ok(()),
    )?;

    Ok(())
}

pub(crate) fn witness_test_data(data: &[&str]) -> Vec<BytePoly> {
    data.into_iter().map(|d| BytePoly::from_hex(d)).collect()
}

pub(crate) fn from_hex(s: &str) -> BigUint {
    BigUint::from_str_radix(s, 16).expect("Unable to parse hex value")
}
