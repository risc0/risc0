// Copyright 2023 RISC Zero, Inc.
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

use std::collections::VecDeque;

use anyhow::{anyhow, Context, Result};
use risc0_circuit_recursion::prove::vm::{
    poseidon254_hal_pair, Prover, ProverOpts, RecursionReceipt,
};

use crate::{
    receipt_claim::Merge, recursion::SuccinctReceipt, sha::Digestible, Output, ReceiptClaim,
    SegmentReceipt,
};

/// Run the lift program to transform an rv32im segment receipt into a recursion receipt.
///
/// The lift program verifies the rv32im circuit STARK proof inside the recursion circuit,
/// resulting in a recursion circuit STARK proof. This recursion proof has a single
/// constant-time verification procedure, with respect to the original segment length, and is then
/// used as the input to all other recursion programs (e.g. join, resolve, and identity_p254).
pub fn lift(input: &SegmentReceipt) -> Result<SuccinctReceipt> {
    tracing::debug!("Proving lift: claim = {:#?}", input.claim);
    let mut prover = Prover::new_lift(&input.seal, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.data.iter());
    let claim_decoded = ReceiptClaim::decode(&mut out_stream)?;
    tracing::debug!("Proving lift finished: decoded claim = {claim_decoded:#?}");
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim: claim_decoded.merge(&input.claim)?,
    })
}

/// Run the join program to compress two receipts of the same session into one.
///
/// By repeated application of the join program, any number of receipts for execution spans within
/// the same session can be compressed into a single receipt for the entire session.
pub fn join(left: &SuccinctReceipt, right: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    tracing::debug!("Proving join: left.claim  = {:#?}", left.claim);
    tracing::debug!("Proving join: right.claim = {:#?}", right.claim);

    let mut prover =
        Prover::new_join(&left.try_into()?, &right.try_into()?, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.data.iter());

    // Construct the expected claim that should have result from the join.
    let ab_claim = ReceiptClaim {
        pre: left.claim.pre.clone(),
        post: right.claim.post.clone(),
        exit_code: right.claim.exit_code,
        input: left.claim.input.clone(),
        output: right.claim.output.clone(),
    };

    let claim_decoded = ReceiptClaim::decode(&mut out_stream)?;
    tracing::debug!("Proving join finished: decoded claim = {claim_decoded:#?}");
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim: claim_decoded.merge(&ab_claim)?,
    })
}

/// Run the resolve program to remove an assumption from a conditional receipt upon verifying a
/// corroborating receipt for the assumption.
///
/// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution using
/// the `env::verify` API to logically verify a receipt) can be made into an unconditional receipt.
pub fn resolve(
    conditional: &SuccinctReceipt,
    corroborating: &SuccinctReceipt,
) -> Result<SuccinctReceipt> {
    tracing::debug!(
        "Proving resolve: conditional.claim = {:#?}",
        conditional.claim,
    );
    tracing::debug!(
        "Proving resolve: corroborating.claim = {:#?}",
        corroborating.claim,
    );

    // Construct the resolved claim by copying the conditional receipt claim and resolving
    // the head assumption. If this fails, then so would the resolve program.
    let mut resolved_claim = conditional.claim.clone();
    resolved_claim
        .output
        .as_value_mut()
        .context("conditional receipt output is pruned")?
        .as_mut()
        .ok_or(anyhow!(
            "conditional receipt has empty output and no assumptions"
        ))?
        .assumptions
        .as_value_mut()
        .context("conditional receipt assumptions are pruned")?
        .resolve(&corroborating.claim.digest())?;

    let Output {
        assumptions,
        journal,
    } = conditional
        .claim
        .output
        .as_value()
        .context("cannot resolve conditional receipt with pruned output")?
        .as_ref()
        .ok_or(anyhow!("cannot resolve conditional receipt with no output"))?
        .clone();

    // Unwrap the MaybePruned assumptions list and resolve the corroborated assumption,
    // removing the head and leaving the tail of the list.
    let mut assumptions_tail = assumptions
        .value()
        .context("cannot resolve conditional receipt with pruned assumptions")?;
    assumptions_tail.resolve(&corroborating.claim.digest())?;

    let mut prover = Prover::new_resolve(
        &conditional.try_into()?,
        &corroborating.try_into()?,
        &assumptions_tail.digest(),
        &journal.digest(),
        ProverOpts::default(),
    )?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.data.iter());

    let claim_decoded = ReceiptClaim::decode(&mut out_stream)?;
    tracing::debug!("Proving resolve finished: decoded claim = {claim_decoded:#?}");
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim: claim_decoded.merge(&resolved_claim)?,
    })
}

/// Prove the verification of a recursion receipt using the Poseidon254 hash function for FRI.
///
/// The identity_p254 program is used as the last step in the prover pipeline before running the
/// Groth16 prover. In Groth16 over BN254, it is much more efficient to verify a STARK that was
/// produced with Poseidon over the BN254 base field compared to using Posidon over BabyBear.
pub fn identity_p254(input: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
    let mut prover = Prover::new_identity(&input.try_into()?, ProverOpts::default())?;
    let receipt = prover.run_with_hal(hal, circuit_hal)?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.data.iter());
    let claim = ReceiptClaim::decode(&mut out_stream)?.merge(&input.claim)?;
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim,
    })
}

impl TryFrom<&SuccinctReceipt> for RecursionReceipt {
    type Error = anyhow::Error;

    fn try_from(value: &SuccinctReceipt) -> Result<Self> {
        let mut data = Vec::new();
        value.claim.encode(&mut data)?;
        Ok(Self {
            control_id: value.control_id,
            seal: value.seal.to_vec(),
            data,
        })
    }
}
