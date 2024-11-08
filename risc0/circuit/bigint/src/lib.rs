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

pub mod byte_poly;
mod codegen_prelude;
#[cfg(not(feature = "make_control_ids"))]
pub(crate) mod control_id;
#[cfg(not(target_os = "zkvm"))]
mod host;
#[cfg(test)]
mod op_tests;
pub mod rsa;
#[cfg(test)]
mod testutil;
#[cfg(feature = "prove")]
pub mod zkr;

// // TODO: So this comes through as an extern just fine...
// #[no_mangle]
// pub fn todo_test_fn(x: u32) -> u32 {
//     x
// }

pub(crate) mod generated {
    #![allow(dead_code)]
    #![allow(non_camel_case_types)]
    #![allow(clippy::all)]

    use crate::codegen_prelude::*;
    include! {"bigint.rs.inc"}
}

use std::borrow::Borrow;

use anyhow::{ensure, Context, Result};
use num_bigint::BigUint;
use risc0_binfmt::{tagged_list, Digestible};
use risc0_circuit_recursion::CHECKED_COEFFS_PER_POLY;
use risc0_zkp::{
    core::{
        digest::Digest,
        hash::{poseidon2::Poseidon2HashSuite, sha::Sha256},
    },
    field::Elem as _,
};

use self::byte_poly::BITS_PER_COEFF;

#[cfg(not(target_os = "zkvm"))]
pub use host::*;
#[cfg(target_os = "zkvm")]
mod guest;
pub use generated::PROGRAMS;

#[cfg(target_os = "zkvm")]
pub use guest::*;

// PO2 to use to execute bigint ZKRs.
pub const BIGINT_PO2: usize = 18;

const CLAIM_LIST_TAG: &str = "risc0.BigIntClaims";

#[derive(Default, Debug)]
pub struct BigIntContext {
    pub in_values: Vec<BigUint>,

    pub constant_witness: Vec<Vec<i32>>,
    pub public_witness: Vec<Vec<i32>>,
    pub private_witness: Vec<Vec<i32>>,
}

/// Information about a big integer included in a bigint witness.
#[derive(Debug)]
pub struct WitnessInfo {
    pub bits: usize,
    pub label: usize,
    pub public: bool,
    pub min_bits: usize,
}

impl WitnessInfo {
    // Number of coefficients/field elements used by this bigint
    pub fn coeffs(&self) -> usize {
        const ROUND_WIDTH: usize = BITS_PER_COEFF * CHECKED_COEFFS_PER_POLY;
        let polys = self.bits.div_ceil(ROUND_WIDTH);
        polys * CHECKED_COEFFS_PER_POLY
    }
}

pub struct BigIntProgram<'a> {
    pub name: &'a str,
    pub witness_info: &'a [WitnessInfo],
    pub unconstrained_eval_fn: fn(&mut BigIntContext) -> anyhow::Result<()>,
    // Control ID of this program
    pub control_id: Digest,
    // Control root of a merkle tree with a single element containing control_id
    pub control_root: Digest,
    // Number of claims to be verified per invocation of the ZKR
    pub iters: usize,
}

#[derive(Debug, Clone)]
pub struct BigIntClaim {
    pub public_witness: Vec<Vec<i32>>,
}

impl BigIntClaim {
    pub fn new(public_witness: Vec<Vec<i32>>) -> Self {
        BigIntClaim { public_witness }
    }

    pub fn from_biguints(prog_info: &BigIntProgram, biguints: &[impl Borrow<BigUint>]) -> Self {
        assert_eq!(biguints.len(), prog_info.witness_info.len());
        let public_witness: Vec<Vec<i32>> = biguints
            .iter()
            .zip(prog_info.witness_info.iter())
            .map(|(val, wit_info)| byte_poly::from_biguint(val.borrow(), wit_info.coeffs()))
            .collect();
        BigIntClaim { public_witness }
    }
}

impl Digestible for BigIntClaim {
    fn digest<S: Sha256>(&self) -> Digest {
        let mut u32s: Vec<u32> = Vec::new();

        for wit in self.public_witness.iter() {
            u32s.extend(byte_poly::into_padded_u32s(wit))
        }

        tracing::trace!("digest of {} u32s: {:x?}", u32s.len(), u32s);
        *S::hash_raw_data_slice(&u32s)
    }
}

pub(crate) fn claim_list_digest<S: Sha256>(
    prog: &BigIntProgram,
    claims: &[impl Borrow<BigIntClaim>],
) -> Result<Digest> {
    ensure!(
        claims.len() <= prog.iters,
        "Tried to verify {} claims in a {}-claim bigint program",
        claims.len(),
        prog.iters
    );
    let mut digests: Vec<Digest> = Vec::with_capacity(prog.iters);
    digests.extend(
        claims
            .iter()
            .map(Borrow::borrow)
            .map(Digestible::digest::<S>),
    );
    digests.resize(
        prog.iters,
        *digests
            .last()
            .context("At least one claim must be specified in a list of claims")?,
    );
    Ok(tagged_list::<S>(CLAIM_LIST_TAG, &digests))
}

pub(crate) fn pad_claim_list<'a>(
    prog: &BigIntProgram,
    claims: &'a [impl Borrow<BigIntClaim>],
) -> Result<Vec<&'a BigIntClaim>> {
    ensure!(
        claims.len() <= prog.iters,
        "Tried to verify {} claims in a {}-claim bigint program",
        claims.len(),
        prog.iters
    );
    let mut claim_refs: Vec<&BigIntClaim> = Vec::with_capacity(prog.iters);
    claim_refs.extend(claims.iter().map(Borrow::borrow));
    claim_refs.resize(
        prog.iters,
        claim_refs
            .last()
            .context("At least one claim must be specified in a list of claims")?,
    );
    Ok(claim_refs)
}

pub fn generate_proof_input(
    claims: &[impl Borrow<BigIntClaim>],
    prog: &BigIntProgram,
) -> Result<Vec<u32>> {
    let mut input: Vec<u32> = Vec::new();
    input.extend(prog.control_root.as_words());

    let hash_suite = Poseidon2HashSuite::new_suite();
    let mut rng = hash_suite.rng.new_rng();

    for claim in pad_claim_list(prog, claims)? {
        tracing::debug!("claim: {claim:?}");
        let mut ctx = BigIntContext {
            in_values: claim
                .public_witness
                .iter()
                .map(Vec::as_slice)
                .map(byte_poly::to_biguint)
                .collect(),
            ..Default::default()
        };

        (prog.unconstrained_eval_fn)(&mut ctx)?;

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
        let private_digest =
            byte_poly::compute_digest(&*hash_suite.hashfn, &ctx.private_witness, 3);
        let folded = hash_suite.hashfn.hash_pair(&public_digest, &private_digest);
        tracing::trace!("folded: {folded}");

        // Calculate the evaluation point Z
        rng.mix(&folded);
        let z = rng.random_ext_elem();

        tracing::trace!("evaluation point: {z:?}");
        input.extend(z.to_u32_words());
        input.extend(all_coeffs);
    }

    Ok(input)
}
