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

use std::{borrow::Borrow, collections::VecDeque};

use anyhow::{bail, Result};
use risc0_binfmt::read_sha_halfs;
use risc0_circuit_recursion::{
    prove::RecursionReceipt,
    prove::{Program, Prover},
};
use risc0_zkp::{
    adapter::CircuitInfo,
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite, hash::sha::Sha256},
    field::baby_bear::BabyBearElem,
    verify::VerificationError,
};

use crate::{claim_list_digest, generate_proof_input, BigIntClaim, BigIntProgram};

pub fn prove<S: Sha256>(
    claims: &[impl Borrow<BigIntClaim>],
    prog: &BigIntProgram,
    zkr: Program,
) -> Result<RecursionReceipt> {
    let input = generate_proof_input(claims, prog)?;

    let mut prover = Prover::new(zkr, "poseidon2");
    prover.add_input(&input);

    tracing::trace!("Running prover");
    let receipt = prover.run()?;

    tracing::trace!("bigint proved successfully");
    Ok(receipt)
}

/// Verifies the given BigIntClaim.  Prefer using a recursion
/// predicate such as "resolve" over verifying the receipt directly.
pub fn verify<S: Sha256>(
    prog: &BigIntProgram,
    claims: &[impl Borrow<BigIntClaim>],
    receipt: &RecursionReceipt,
) -> Result<()> {
    tracing::trace!("bigint verify {} claims", claims.len());
    let claim_digest = claim_list_digest::<S>(prog, claims)?;
    tracing::trace!("claim_digest: {claim_digest:?}");

    let hash_suite = Poseidon2HashSuite::new_suite();

    risc0_zkp::verify::verify(
        &risc0_circuit_recursion::CIRCUIT,
        &hash_suite,
        &receipt.seal,
        |receipt_po2, receipt_control_id| {
            if *receipt_control_id == prog.control_id {
                Ok(())
            } else {
                tracing::debug!(
                    "Expecting control id {}, got {receipt_control_id} (po2 = {receipt_po2}",
                    prog.control_id
                );
                Err(VerificationError::ControlVerificationError {
                    control_id: *receipt_control_id,
                })
            }
        },
    )?;

    // Extract the globals from the seal
    let output_elems: &[BabyBearElem] = bytemuck::checked::cast_slice(
        &receipt.seal[..risc0_circuit_recursion::CircuitImpl::OUTPUT_SIZE],
    );
    let mut seal_claim = VecDeque::new();
    for elem in output_elems {
        seal_claim.push_back(elem.as_u32())
    }

    // Read the Poseidon2 control root digest from the first 16 words of the output.
    // NOTE: Implemented recursion programs have two output slots, each of size 16 elems.
    // A SHA2 digest is encoded as 16 half words. Poseidon digests are encoded in 8 elems,
    // but are interspersed with padding to fill out the whole 16 elems.
    let inner_control_root: Digest = seal_claim
        .drain(0..16)
        .enumerate()
        .filter_map(|(i, word)| (i & 1 == 0).then_some(word))
        .collect::<Vec<_>>()
        .try_into()
        .map_err(|_| VerificationError::ReceiptFormatError)?;
    // Future-proof in case we want to use inner control root for something else later.
    assert_eq!(inner_control_root, prog.control_root);

    let output_hash =
        read_sha_halfs(&mut seal_claim).map_err(|_| VerificationError::ReceiptFormatError)?;
    if output_hash != claim_digest {
        tracing::debug!(
            "succinct receipt claim does not match the output digest, output_hash: {output_hash:?}, expected digest for claim: {claim_digest:?}",
        );
        for claim in claims.iter().map(Borrow::borrow) {
            tracing::debug!("claim: {claim:?}");
        }
        bail!(VerificationError::JournalDigestMismatch);
    }

    // Everything passed
    Ok(())
}
