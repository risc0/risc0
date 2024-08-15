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
pub mod rsa;
#[cfg(feature = "prove")]
pub mod zkr;

#[cfg(not(target_os = "zkvm"))]
mod host;
#[cfg(not(target_os = "zkvm"))]
pub use host::*;

#[cfg(target_os = "zkvm")]
mod guest;
#[cfg(target_os = "zkvm")]
pub use guest::*;

#[cfg(not(feature = "make_control_ids"))]
pub(crate) mod control_id;

#[cfg(test)]
mod op_tests;
#[cfg(test)]
#[cfg(feature = "prove")]
mod rsa_tests;
#[cfg(test)]
mod test_harness;

pub(crate) mod generated {
    #![allow(dead_code)]
    #![allow(clippy::all)]

    use crate::codegen_prelude::*;
    include! {"bigint.rs.inc"}
}

use std::borrow::Borrow;

use anyhow::{ensure, Context, Result};
use byte_poly::{BytePoly, BITS_PER_COEFF};
use num_bigint::BigUint;
use risc0_binfmt::{tagged_list, Digestible};
use risc0_circuit_recursion::CHECKED_COEFFS_PER_POLY;
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};

pub use generated::PROGRAMS;

// PO2 to use to execute bigint ZKRs.
pub const BIGINT_PO2: usize = 18;

const CLAIM_LIST_TAG: &str = "risc0.BigIntClaims";

#[derive(Default, Debug)]
pub struct BigIntContext {
    pub in_values: Vec<BigUint>,

    pub constant_witness: Vec<BytePoly>,
    pub public_witness: Vec<BytePoly>,
    pub private_witness: Vec<BytePoly>,
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
    pub public_witness: Vec<BytePoly>,
}

impl BigIntClaim {
    pub fn new(public_witness: Vec<BytePoly>) -> Self {
        BigIntClaim { public_witness }
    }

    pub fn from_biguints(
        prog_info: &BigIntProgram,
        biguints: &[impl ToOwned<Owned = BigUint>],
    ) -> Self {
        assert_eq!(biguints.len(), prog_info.witness_info.len());
        let public_witness: Vec<BytePoly> = biguints
            .iter()
            .zip(prog_info.witness_info.iter())
            .map(|(val, wit_info)| BytePoly::from_biguint(val.to_owned(), wit_info.coeffs()))
            .collect();
        BigIntClaim { public_witness }
    }
}

impl Digestible for BigIntClaim {
    fn digest<S: Sha256>(&self) -> Digest {
        let mut u32s: Vec<u32> = Vec::new();

        for wit in self.public_witness.iter() {
            u32s.extend(wit.clone().into_padded_u32s())
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
