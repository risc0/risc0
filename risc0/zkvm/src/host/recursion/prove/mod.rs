// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub mod zkr;

use std::{
    collections::{BTreeMap, VecDeque},
    fmt::Debug,
    sync::Mutex,
};

use anyhow::{Context, Result, anyhow, bail, ensure};
use risc0_binfmt::read_sha_halfs;
use risc0_circuit_recursion::{
    CircuitImpl,
    control_id::BN254_IDENTITY_CONTROL_ID,
    prove::{DigestKind, RecursionReceipt},
};
use risc0_circuit_rv32im::RV32IM_SEAL_VERSION;
use risc0_zkp::{
    adapter::{CircuitInfo, PROOF_SYSTEM_INFO},
    core::{
        digest::{DIGEST_SHORTS, Digest},
        hash::{hash_suite_from_name, poseidon2::Poseidon2HashSuite},
    },
    field::baby_bear::BabyBearElem,
    verify::ReadIOP,
};

use crate::{
    Assumptions, MaybePruned, Output, ProverOpts, ReceiptClaim, WorkClaim,
    claim::{
        Unknown,
        merge::Merge,
        receipt::{Assumption, UnionClaim},
    },
    receipt::{
        SegmentReceipt, SuccinctReceipt, SuccinctReceiptVerifierParameters,
        merkle::{MerkleGroup, MerkleProof},
    },
    sha::Digestible,
};

use risc0_circuit_recursion::prove::Program;

/// Number of rows to use for the recursion circuit witness as a power of 2.
pub const RECURSION_PO2: usize = 18;

pub(crate) type ZkrRegistryEntry = Box<dyn Fn() -> Result<Program> + Send + 'static>;

pub(crate) type ZkrRegistry = BTreeMap<Digest, ZkrRegistryEntry>;

/// A registry to look up programs by control ID.
pub(crate) static ZKR_REGISTRY: Mutex<ZkrRegistry> = Mutex::new(BTreeMap::new());

/// Run the lift program to transform an rv32im segment receipt into a recursion receipt.
///
/// The lift program verifies the rv32im circuit STARK proof inside the recursion circuit,
/// resulting in a recursion circuit STARK proof. This recursion proof has a single
/// constant-time verification procedure, with respect to the original segment length, and is then
/// used as the input to all other recursion programs (e.g. join, resolve, and identity_p254).
pub fn lift(segment_receipt: &SegmentReceipt) -> Result<SuccinctReceipt<ReceiptClaim>> {
    tracing::debug!("Proving lift: claim = {:#?}", segment_receipt.claim);
    let mut prover = Prover::new_lift(segment_receipt, ProverOpts::succinct())?;

    let receipt = prover.prover.run()?;
    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving lift finished: decoded claim = {claim_decoded:#?}");

    let claim = claim_decoded.merge(&segment_receipt.claim)?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the lift program to create a succinct work claim receipt from a segment receipt.
///
/// Similar to [`lift`], but additionally tracks verifiable work by computing the work value
/// from the segment proof and embedding it in the resulting work claim.
pub fn lift_povw(
    segment_receipt: &SegmentReceipt,
) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
    tracing::debug!("Proving lift_povw: claim = {:#?}", segment_receipt.claim);
    let mut prover = Prover::new_lift_povw(segment_receipt, ProverOpts::succinct())?;

    let receipt = prover.prover.run()?;
    let mut out_stream = receipt.out_stream();
    tracing::debug!("Proving lift_povw finished: out = {out_stream:?}");
    let claim_decoded = WorkClaim::<ReceiptClaim>::decode_from_seal(&mut out_stream)?;
    tracing::debug!("Proving lift_povw finished: decoded claim = {claim_decoded:#?}");

    // Merge the full claim from the segment receipt into the decoded work claim.
    let mut claim = claim_decoded;
    claim
        .claim
        .merge_with(&segment_receipt.claim.clone().into())
        .context("failed to merge segment receipt claim into decode claim")?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the join program to compress two receipts of the same session into one.
///
/// By repeated application of the join program, any number of receipts for execution spans within
/// the same session can be compressed into a single receipt for the entire session.
pub fn join(
    a: &SuccinctReceipt<ReceiptClaim>,
    b: &SuccinctReceipt<ReceiptClaim>,
) -> Result<SuccinctReceipt<ReceiptClaim>> {
    tracing::debug!("Proving join: a.claim = {:#?}", a.claim);
    tracing::debug!("Proving join: b.claim = {:#?}", b.claim);

    let mut prover = Prover::new_join(a, b, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;

    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving join finished: decoded claim = {claim_decoded:#?}");

    // Compute the expected claim and merge it with the decoded claim, checking that they match.
    let claim = claim_decoded.merge(&a.claim.join(&b.claim)?.value()?)?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the join program to compress two work claim receipts of the same session into one.
///
/// Similar to [`join`], but operates on work claim receipts and combines their work values
/// while ensuring the consumed nonce ranges are disjoint.
pub fn join_povw(
    a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>> {
    tracing::debug!("Proving join_povw: a.claim = {:#?}", a.claim);
    tracing::debug!("Proving join_povw: b.claim = {:#?}", b.claim);

    let mut prover = Prover::new_join_povw(a, b, false, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;

    let claim_decoded = WorkClaim::<ReceiptClaim>::decode_from_seal(&mut receipt.out_stream())?;
    tracing::debug!("Proving join_povw finished: decoded claim = {claim_decoded:#?}");

    // Compute the expected claim and merge it with the decoded claim, checking that they match.
    let claim = claim_decoded.merge(&a.claim.join(&b.claim)?.value()?)?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the join_unwrap program to compress two work claim receipts into a regular receipt.
///
/// This combines the functionality of [`join_povw`] and [`unwrap_povw`] in a single recursion
/// step, with reduced latency relative to running a separate unwrap.
pub fn join_unwrap_povw(
    a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
) -> Result<SuccinctReceipt<ReceiptClaim>> {
    tracing::debug!("Proving join_unwrap_povw: a.claim = {:#?}", a.claim);
    tracing::debug!("Proving join_unwrap_povw: b.claim = {:#?}", b.claim);

    let mut prover = Prover::new_join_povw(a, b, true, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;

    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving join_unwrap_povw finished: decoded claim = {claim_decoded:#?}");

    // Compute the expected claim and merge it with the decoded claim, checking that they match.
    let claim = claim_decoded.merge(&a.claim.join(&b.claim)?.value()?.claim.value()?)?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the union program to compress two succinct receipts into one.
///
/// By repeated application of the union program, any number of succinct
/// receipts can be compressed into a single receipt.
pub fn union(
    a: &SuccinctReceipt<Unknown>,
    b: &SuccinctReceipt<Unknown>,
) -> Result<SuccinctReceipt<UnionClaim>> {
    // NOTE: This will run into issues if the assumption is made with a control root of zero. Right
    // now, this is only used for keccak so this issue has not been hit.
    let a_assumption = a.to_assumption(false)?.digest();
    let b_assumption = b.to_assumption(false)?.digest();

    let ((left_assumption, left_receipt), (right_assumption, right_receipt)) =
        if a_assumption <= b_assumption {
            ((a_assumption, a), (b_assumption, b))
        } else {
            ((b_assumption, b), (a_assumption, a))
        };

    tracing::debug!("Proving union: left assumption = {:#?}", left_assumption);
    tracing::debug!("Proving union: right assumption = {:#?}", right_assumption);

    let mut prover = Prover::new_union(left_receipt, right_receipt, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;

    let claim = UnionClaim {
        left: left_assumption,
        right: right_assumption,
    };

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the resolve program to remove an assumption from a conditional receipt upon verifying a
/// receipt proving the validity of the assumption.
///
/// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution using
/// the `env::verify` API to logically verify a receipt) can be made into an unconditional receipt.
pub fn resolve<Claim>(
    conditional: &SuccinctReceipt<ReceiptClaim>,
    assumption: &SuccinctReceipt<Claim>,
) -> Result<SuccinctReceipt<ReceiptClaim>>
where
    Claim: risc0_binfmt::Digestible + Debug,
{
    tracing::debug!(
        "Proving resolve: conditional.claim = {:#?}",
        conditional.claim,
    );
    tracing::debug!(
        "Proving resolve: assumption.claim = {:#?}",
        assumption.claim,
    );

    let mut prover = Prover::new_resolve(conditional, assumption, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;
    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving resolve finished: decoded claim = {claim_decoded:#?}");

    let claim = conditional
        .claim
        .as_value()
        .context("conditional receipt claim is pruned")?
        .resolve(&assumption.claim)
        .context("failed to compute resolved claim")?
        .merge(&claim_decoded)
        .context("failed to merge resolved and decoded claims")?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the resolve program to remove an assumption from a conditional work claim receipt.
///
/// Similar to [`resolve`], but operates on work claim receipts while preserving the work value
/// from the conditional receipt.
pub fn resolve_povw<Claim>(
    conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    assumption: &SuccinctReceipt<Claim>,
) -> Result<SuccinctReceipt<WorkClaim<ReceiptClaim>>>
where
    Claim: risc0_binfmt::Digestible + Debug,
{
    tracing::debug!(
        "Proving resolve_povw: conditional.claim = {:#?}",
        conditional.claim,
    );
    tracing::debug!(
        "Proving resolve_povw: assumption.claim = {:#?}",
        assumption.claim,
    );

    let mut prover =
        Prover::new_resolve_povw(conditional, assumption, false, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;
    let claim_decoded = WorkClaim::<ReceiptClaim>::decode_from_seal(&mut receipt.out_stream())?;
    tracing::debug!("Proving resolve_povw finished: decoded claim = {claim_decoded:#?}");

    let claim = conditional
        .claim
        .as_value()
        .context("conditional receipt povw claim is pruned")?
        .resolve(&assumption.claim)
        .context("failed to compute resolved claim")?
        .merge(&claim_decoded)
        .context("failed to merge resolved and decoded claims")?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the resolve_unwrap program to remove an assumption from a conditional work claim receipt.
///
/// This combines the functionality of [`resolve_povw`] and [`unwrap_povw`] in a single recursion
/// step, with reduced latency relative to running a separate unwrap.
pub fn resolve_unwrap_povw<Claim>(
    conditional: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    assumption: &SuccinctReceipt<Claim>,
) -> Result<SuccinctReceipt<ReceiptClaim>>
where
    Claim: risc0_binfmt::Digestible + Debug,
{
    tracing::debug!(
        "Proving resolve_unwrap_povw: conditional.claim = {:#?}",
        conditional.claim,
    );
    tracing::debug!(
        "Proving resolve_unwrap_povw: assumption.claim = {:#?}",
        assumption.claim,
    );

    let mut prover =
        Prover::new_resolve_povw(conditional, assumption, true, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;
    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving resolve_unwrap_povw finished: decoded claim = {claim_decoded:#?}");

    let claim = conditional
        .claim
        .as_value()
        .context("conditional receipt povw claim is pruned")?
        .claim
        .as_value()
        .context("conditional receipt claim is pruned")?
        .resolve(&assumption.claim)
        .context("failed to compute resolved claim")?
        .merge(&claim_decoded)
        .context("failed to merge resolved and decoded claims")?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Run the unwrap program to convert a work claim receipt to a regular receipt claim.
///
/// This removes the work tracking wrapper from a receipt, producing a standard receipt
/// that can be sent to verifiers of the underlying claim.
pub fn unwrap_povw(
    a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
) -> Result<SuccinctReceipt<ReceiptClaim>> {
    tracing::debug!("Proving unwrap_povw: a.claim = {:#?}", a.claim);

    let mut prover = Prover::new_unwrap_povw(a, ProverOpts::succinct())?;
    let receipt = prover.prover.run()?;

    let claim_decoded = ReceiptClaim::decode(&mut receipt.out_stream())?;
    tracing::debug!("Proving unwrap_povw finished: decoded claim = {claim_decoded:#?}");

    // Compute the expected claim and merge it with the decoded claim, checking that they match.
    let claim = MaybePruned::Value(claim_decoded).merge(&a.claim.as_value()?.claim)?;

    make_succinct_receipt(prover, receipt, claim)
}

/// Prove the verification of a recursion receipt using the Poseidon254 hash function for FRI.
///
/// The identity_p254 program is used as the last step in the prover pipeline before running the
/// Groth16 prover. In Groth16 over BN254, it is much more efficient to verify a STARK that was
/// produced with Poseidon over the BN254 base field compared to using Poseidon over BabyBear.
pub fn identity_p254(
    inner: &SuccinctReceipt<ReceiptClaim>,
) -> Result<SuccinctReceipt<ReceiptClaim>> {
    tracing::debug!("identity_p254");

    let opts = ProverOpts::succinct()
        .with_hashfn("poseidon_254".to_string())
        .with_control_ids(vec![BN254_IDENTITY_CONTROL_ID]);
    let mut prover = Prover::new_identity(inner, opts)?;
    let receipt = prover.prover.run()?;
    let claim =
        MaybePruned::Value(ReceiptClaim::decode(&mut receipt.out_stream())?).merge(&inner.claim)?;

    // Include an inclusion proof for control_id to allow verification against a root.
    let hashfn = prover.opts.hash_suite()?.hashfn;
    let control_inclusion_proof = prover.control_inclusion_proof()?;
    let control_root = control_inclusion_proof.root(&prover.control_id, hashfn.as_ref());
    let params = SuccinctReceiptVerifierParameters {
        control_root,
        inner_control_root: Some(inner.control_root()?),
        proof_system_info: PROOF_SYSTEM_INFO,
        circuit_info: CircuitImpl::CIRCUIT_INFO,
    };

    Ok(SuccinctReceipt {
        seal: receipt.seal,
        hashfn: prover.opts.hashfn.clone(),
        control_id: prover.control_id,
        control_inclusion_proof,
        claim,
        verifier_parameters: params.digest(),
    })
}

/// Prove the specified program identified by the `control_id` using the specified `input`.
pub fn prove_zkr(
    program: Program,
    control_id: &Digest,
    allowed_control_ids: Vec<Digest>,
    input: &[u8],
) -> Result<SuccinctReceipt<Unknown>> {
    let opts = ProverOpts::succinct().with_control_ids(allowed_control_ids);
    let mut prover = Prover::new(program, *control_id, opts.clone());
    prover.add_input(bytemuck::cast_slice(input));

    tracing::debug!("Running prover");
    let receipt = prover.run()?;

    tracing::trace!("zkr receipt: {receipt:?}");

    // Read the claim digest from the second of the global output slots.
    let claim_digest: Digest = read_sha_halfs(&mut VecDeque::from_iter(
        bytemuck::checked::cast_slice::<_, BabyBearElem>(
            &receipt.seal[DIGEST_SHORTS..2 * DIGEST_SHORTS],
        )
        .iter()
        .copied()
        .map(u32::from),
    ))?;

    let hashfn = opts.hash_suite()?.hashfn;
    let control_group = MerkleGroup::new(opts.control_ids.clone())?;
    let control_root = control_group.calc_root(hashfn.as_ref());
    let control_inclusion_proof = control_group.get_proof(control_id, hashfn.as_ref())?;

    let verifier_parameters = SuccinctReceiptVerifierParameters {
        control_root,
        inner_control_root: None,
        proof_system_info: PROOF_SYSTEM_INFO,
        circuit_info: CircuitImpl::CIRCUIT_INFO,
    }
    .digest();

    Ok(SuccinctReceipt {
        seal: receipt.seal,
        hashfn: opts.hashfn,
        control_id: *control_id,
        control_inclusion_proof,
        claim: MaybePruned::<Unknown>::Pruned(claim_digest),
        verifier_parameters,
    })
}

/// Prove the specified program identified by the `control_id` using the specified `input`.
pub fn prove_registered_zkr(
    control_id: &Digest,
    allowed_control_ids: Vec<Digest>,
    input: &[u8],
) -> Result<SuccinctReceipt<Unknown>> {
    let zkr = get_registered_zkr(control_id)?;
    prove_zkr(zkr, control_id, allowed_control_ids, input)
}

/// Registers a function to retrieve a recursion program (zkr) based on a control id.
pub fn register_zkr(
    control_id: &Digest,
    get_program_fn: impl Fn() -> Result<Program> + Send + 'static,
) -> Option<ZkrRegistryEntry> {
    let mut registry = ZKR_REGISTRY.lock().unwrap();
    registry.insert(*control_id, Box::new(get_program_fn))
}

/// Returns a registered ZKR program, or an error if not found.
pub fn get_registered_zkr(control_id: &Digest) -> Result<Program> {
    let registry = ZKR_REGISTRY.lock().unwrap();
    registry
        .get(control_id)
        .map(|f| f())
        .unwrap_or_else(|| bail!("Control id {control_id} unregistered"))
}

/// Private utility to make a SuccinctReceipt from a RecursionReceipt, the Prover and the Claim.
fn make_succinct_receipt<Claim>(
    prover: Prover,
    receipt: RecursionReceipt,
    claim: impl Into<MaybePruned<Claim>>,
) -> Result<SuccinctReceipt<Claim>> {
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        hashfn: prover.opts.hashfn.clone(),
        control_id: prover.control_id,
        control_inclusion_proof: prover.control_inclusion_proof()?,
        claim: claim.into(),
        // TODO(victor): This should be derived from the ProverOpts instead of being default.
        verifier_parameters: SuccinctReceiptVerifierParameters::default().digest(),
    })
}

/// Prove the test_recursion_circuit. This is useful for testing purposes.
///
/// digest1 will be passed through to the first of the output globals, as the "inner control root".
/// digest1 and digest2 will be used to calculate a "claim digest", placed in the second output.
#[cfg(test)]
pub fn test_zkr(
    digest1: &Digest,
    digest2: &Digest,
    po2: usize,
) -> Result<SuccinctReceipt<crate::claim::Unknown>> {
    use risc0_circuit_recursion::prove::zkr::get_zkr;
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;

    let program = get_zkr("test_recursion_circuit.zkr", po2)?;
    let suite = Poseidon2HashSuite::new_suite();
    let control_id = program.compute_control_id(suite.clone()).unwrap();
    let opts = ProverOpts::succinct().with_control_ids(vec![control_id]);

    let mut prover = Prover::new(program, control_id, opts.clone());
    prover.add_input_digest(digest1, DigestKind::Poseidon2);
    prover.add_input_digest(digest2, DigestKind::Poseidon2);

    let receipt = prover.run()?;

    // Read the claim digest from the second of the global output slots.
    let claim_digest = read_sha_halfs(&mut VecDeque::from_iter(
        bytemuck::checked::cast_slice::<_, BabyBearElem>(
            &receipt.seal[DIGEST_SHORTS..2 * DIGEST_SHORTS],
        )
        .iter()
        .copied()
        .map(u32::from),
    ))?;

    // Include an inclusion proof for control_id to allow verification against a root.
    let hashfn = opts.hash_suite()?.hashfn;
    let control_inclusion_proof = MerkleGroup::new(opts.control_ids.clone())?
        .get_proof(&prover.control_id, hashfn.as_ref())?;
    let control_root = control_inclusion_proof.root(&prover.control_id, hashfn.as_ref());
    let params = SuccinctReceiptVerifierParameters {
        control_root,
        inner_control_root: Some(digest1.to_owned()),
        proof_system_info: PROOF_SYSTEM_INFO,
        circuit_info: CircuitImpl::CIRCUIT_INFO,
    };
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        hashfn: suite.name,
        control_id: prover.control_id,
        control_inclusion_proof,
        claim: MaybePruned::Pruned(claim_digest),
        verifier_parameters: params.digest(),
    })
}

/// Prover for zkVM use of the recursion circuit.
pub struct Prover {
    prover: risc0_circuit_recursion::prove::Prover,
    control_id: Digest,
    opts: ProverOpts,
}

/// Utility macro to compress repeated checks that a receipt uses the poseidon2 hash.
macro_rules! ensure_poseidon2 {
    ($receipt:expr) => {
        ensure!(
            $receipt.hashfn == "poseidon2",
            "recursion programs only supports poseidon2 hashfn; received {}",
            $receipt.hashfn
        );
    };
}

impl Prover {
    pub(crate) fn new(program: Program, control_id: Digest, opts: ProverOpts) -> Self {
        Self {
            prover: risc0_circuit_recursion::prove::Prover::new(program, &opts.hashfn),
            control_id,
            opts,
        }
    }

    /// Returns the control id of the recursion VM program being proven.
    pub fn control_id(&self) -> &Digest {
        &self.control_id
    }

    /// Returns a Merkle inclusion proof of this prover's control ID in the set of allowed IDs.
    pub fn control_inclusion_proof(&self) -> Result<MerkleProof> {
        let hashfn = self
            .opts
            .hash_suite()
            .context("ProverOpts contains invalid hashfn")?
            .hashfn;
        MerkleGroup::new(self.opts.control_ids.clone())?
            .get_proof(&self.control_id, hashfn.as_ref())
    }

    /// Initialize a recursion prover with the test recursion program. This program is used in
    /// testing the basic correctness of the recursion circuit.
    pub fn new_test_recursion_circuit(digests: [&Digest; 2], opts: ProverOpts) -> Result<Self> {
        let (program, control_id) = zkr::test_recursion_circuit(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        for digest in digests {
            prover.add_input_digest(digest, DigestKind::Poseidon2);
        }

        Ok(prover)
    }

    /// Initialize a recursion prover with the lift program to transform an rv32im segment receipt
    /// into a recursion receipt.
    ///
    /// The lift program is verifies the rv32im circuit STARK proof inside the recursion circuit,
    /// resulting in a recursion circuit STARK proof. This recursion proof has a single
    /// constant-time verification procedure, with respect to the original segment length, and is
    /// then used as the input to all other recursion programs (e.g. join, resolve, and
    /// identity_p254).
    pub fn new_lift(segment: &SegmentReceipt, opts: ProverOpts) -> Result<Self> {
        Self::new_lift_inner(segment, opts, false)
    }

    /// Create a prover job for the lift program that produces a work claim receipt.
    ///
    /// Similar to [`Self::new_lift`], but produces a work claim receipt that tracks
    /// verifiable work by computing the work value from the segment proof.
    pub fn new_lift_povw(segment: &SegmentReceipt, opts: ProverOpts) -> Result<Self> {
        Self::new_lift_inner(segment, opts, true)
    }

    /// Instantiate a lift program, with the option of PoVW or not. Note that these programs
    /// produce different output but have the same inputs and so share the same logic here.
    fn new_lift_inner(segment: &SegmentReceipt, opts: ProverOpts, povw: bool) -> Result<Self> {
        ensure_poseidon2!(segment);

        let inner_hash_suite = hash_suite_from_name(&segment.hashfn)
            .ok_or_else(|| anyhow!("unsupported hash function: {}", segment.hashfn))?;
        let allowed_ids = MerkleGroup::new(opts.control_ids.clone())?;
        let merkle_root = allowed_ids.calc_root(inner_hash_suite.hashfn.as_ref());

        let out_size = risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE;

        ensure!(
            segment.seal[0] == RV32IM_SEAL_VERSION,
            "seal version mismatch"
        );

        let seal = &segment.seal[1..];

        // Read the output fields in the rv32im seal to get the po2. We need this po2 to chose
        // which lift program we are going to run.
        let mut iop = ReadIOP::new(seal, inner_hash_suite.rng.as_ref());
        iop.read_field_elem_slice::<BabyBearElem>(out_size);
        let po2 = *iop.read_u32s(1).first().unwrap() as usize;

        // Instantiate the prover with the lift recursion program and its control ID.
        let (program, control_id) = match povw {
            false => zkr::lift(po2, &opts.hashfn)?,
            true => zkr::lift_povw(po2, &opts.hashfn)?,
        };
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_input(seal);

        Ok(prover)
    }

    /// Initialize a recursion prover with the union program to compress two
    /// succinct receipts into one.
    ///
    /// By repeated application of the union program, any number of succinct
    /// receipts can be compressed into a single receipt.
    pub fn new_union(
        a: &SuccinctReceipt<Unknown>,
        b: &SuccinctReceipt<Unknown>,
        opts: ProverOpts,
    ) -> Result<Self> {
        ensure_poseidon2!(a);
        ensure_poseidon2!(b);

        let hash_suite = Poseidon2HashSuite::new_suite();
        let allowed_ids = MerkleGroup::new(opts.control_ids.clone())?;
        let merkle_root = allowed_ids.calc_root(hash_suite.hashfn.as_ref());

        let (program, control_id) = zkr::union(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_succinct_generic_receipt(a)?;
        prover.add_succinct_generic_receipt(b)?;
        Ok(prover)
    }

    /// Initialize a recursion prover with the join program to compress two receipts of the same
    /// session into one.
    ///
    /// By repeated application of the join program, any number of receipts for execution spans
    /// within the same session can be compressed into a single receipt for the entire session.
    pub fn new_join(
        a: &SuccinctReceipt<ReceiptClaim>,
        b: &SuccinctReceipt<ReceiptClaim>,
        opts: ProverOpts,
    ) -> Result<Self> {
        ensure_poseidon2!(a);
        ensure_poseidon2!(b);

        let (program, control_id) = zkr::join(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        // Determine the control root from the receipts themselves, and ensure they are equal. If
        // the determined control root does not match what the downstream verifier expects, they
        // will reject.
        let merkle_root = a.control_root()?;
        ensure!(
            merkle_root == b.control_root()?,
            "merkle roots for a and b do not match: {} != {}",
            merkle_root,
            b.control_root()?
        );

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_succinct_rv32im_receipt(a)?;
        prover.add_succinct_rv32im_receipt(b)?;
        Ok(prover)
    }

    /// Create a prover job for the join program that operates on work claim receipts.
    ///
    /// Similar to [`Self::new_join`], but operates on work claim receipts and combines their
    /// work values while ensuring the consumed nonce ranges are disjoint. The `unwrap` parameter
    /// determines whether the result is unwrapped to a regular receipt claim.
    pub fn new_join_povw(
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        b: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        unwrap: bool,
        opts: ProverOpts,
    ) -> Result<Self> {
        ensure_poseidon2!(a);
        ensure_poseidon2!(b);

        let (program, control_id) = match unwrap {
            false => zkr::join_povw(&opts.hashfn)?,
            true => zkr::join_unwrap_povw(&opts.hashfn)?,
        };
        let mut prover = Prover::new(program, control_id, opts);

        // Determine the control root from the receipts themselves, and ensure they are equal. If
        // the determined control root does not match what the downstream verifier expects, they
        // will reject.
        let merkle_root = a.control_root()?;
        ensure!(
            merkle_root == b.control_root()?,
            "merkle roots for a and b do not match: {} != {}",
            merkle_root,
            b.control_root()?
        );

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_succinct_work_claim_rv32im_receipt(a)?;
        prover.add_succinct_work_claim_rv32im_receipt(b)?;
        Ok(prover)
    }

    /// Initialize a recursion prover with the resolve program to remove an assumption from a
    /// conditional receipt upon verifying a receipt proving the validity of the assumption.
    ///
    /// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution
    /// using the `env::verify` API to logically verify a receipt) can be made into an
    /// unconditional receipt.
    pub fn new_resolve<Claim>(
        cond: &SuccinctReceipt<ReceiptClaim>,
        assum: &SuccinctReceipt<Claim>,
        opts: ProverOpts,
    ) -> Result<Self>
    where
        Claim: risc0_binfmt::Digestible + Debug,
    {
        ensure_poseidon2!(cond);
        ensure_poseidon2!(assum);

        // Load the resolve predicate as a Program and construct the prover.
        let (program, control_id) = zkr::resolve(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        // Load the input values needed by the predicate.
        // Resolve predicate needs both seals as input, and the journal and assumptions tail digest
        // to compute the opening of the conditional receipt claim to the first assumption.
        prover.add_input_digest(&cond.control_root()?, DigestKind::Poseidon2);
        prover.add_succinct_rv32im_receipt(cond)?;

        let (head, tail, output) = check_resolve_assumption(&cond.claim, &assum.claim)?;

        // Ensure that the assumption receipt has the right control root.
        let expected_root = match head.control_root == Digest::ZERO {
            true => cond.control_root()?,
            false => head.control_root,
        };
        ensure!(
            expected_root == assum.control_root()?,
            "assumption receipt control root does not match head of assumptions list"
        );

        prover.add_assumption_receipt(head, assum)?;
        prover.add_input_digest(&tail.digest(), DigestKind::Sha256);
        prover.add_input_digest(&output.journal.digest(), DigestKind::Sha256);
        Ok(prover)
    }

    /// Create a prover job for the resolve program that operates on work claim receipts.
    ///
    /// Similar to [`Self::new_resolve`], but operates on work claim receipts while preserving
    /// the work value from the conditional receipt. The `unwrap` parameter determines whether
    /// the result is unwrapped to a regular receipt claim.
    pub fn new_resolve_povw<Claim>(
        cond: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        assum: &SuccinctReceipt<Claim>,
        unwrap: bool,
        opts: ProverOpts,
    ) -> Result<Self>
    where
        Claim: risc0_binfmt::Digestible + Debug,
    {
        ensure_poseidon2!(cond);
        ensure_poseidon2!(assum);

        // Load the resolve predicate as a Program and construct the prover.
        let (program, control_id) = match unwrap {
            false => zkr::resolve_povw(&opts.hashfn)?,
            true => zkr::resolve_unwrap_povw(&opts.hashfn)?,
        };
        let mut prover = Prover::new(program, control_id, opts);

        // Load the input values needed by the predicate.
        // Resolve predicate needs both seals as input, and the journal and assumptions tail digest
        // to compute the opening of the conditional receipt claim to the first assumption.
        prover.add_input_digest(&cond.control_root()?, DigestKind::Poseidon2);
        prover.add_succinct_work_claim_rv32im_receipt(cond)?;

        let cond_claim = &cond
            .claim
            .as_value()
            .context("cannot resolve assumption receipt with pruned work claim")?
            .claim;
        let (head, tail, output) = check_resolve_assumption(cond_claim, &assum.claim)?;

        // Ensure that the assumption receipt has the right control root.
        let expected_root = match head.control_root == Digest::ZERO {
            true => cond.control_root()?,
            false => head.control_root,
        };
        ensure!(
            expected_root == assum.control_root()?,
            "assumption receipt control root does not match head of assumptions list"
        );

        prover.add_assumption_receipt(head, assum)?;
        prover.add_input_digest(&tail.digest(), DigestKind::Sha256);
        prover.add_input_digest(&output.journal.digest(), DigestKind::Sha256);
        Ok(prover)
    }

    /// Prove the verification of a recursion receipt, applying no changes to [ReceiptClaim].
    ///
    /// The primary use for this program is to transform the receipt itself, e.g. using a different
    /// hash function for FRI. See [identity_p254] for more information.
    pub fn new_identity(a: &SuccinctReceipt<ReceiptClaim>, opts: ProverOpts) -> Result<Self> {
        ensure_poseidon2!(a);

        let (program, control_id) = zkr::identity(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&a.control_root()?, DigestKind::Poseidon2);
        prover.add_succinct_rv32im_receipt(a)?;
        Ok(prover)
    }

    /// Create a prover job for the unwrap program that converts a work claim receipt to a
    /// regular receipt.
    ///
    /// This removes the work tracking wrapper from a receipt, producing a standard receipt
    /// that can be sent to verifiers of the underlying claim.
    pub fn new_unwrap_povw(
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
        opts: ProverOpts,
    ) -> Result<Self> {
        ensure_poseidon2!(a);

        let (program, control_id) = zkr::unwrap_povw(&opts.hashfn)?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&a.control_root()?, DigestKind::Poseidon2);
        prover.add_succinct_work_claim_rv32im_receipt(a)?;
        Ok(prover)
    }

    pub(crate) fn add_input(&mut self, input: &[u32]) {
        self.prover.add_input(input)
    }

    /// Add a digest to the input for the recursion program.
    fn add_input_digest(&mut self, digest: &Digest, kind: DigestKind) {
        self.prover.add_input_digest(digest, kind)
    }

    /// Add a recursion seal (i.e. STARK proof) to input tape of the recursion program.
    pub fn add_seal(
        &mut self,
        seal: &[u32],
        control_id: &Digest,
        control_inclusion_proof: &MerkleProof,
    ) -> Result<()> {
        tracing::debug!("Control ID = {:?}", control_id);
        self.add_input(seal);
        tracing::debug!("index = {:?}", control_inclusion_proof.index);
        self.add_input(bytemuck::cast_slice(&[BabyBearElem::new(
            control_inclusion_proof.index,
        )]));
        for digest in &control_inclusion_proof.digests {
            tracing::debug!("path = {:?}", digest);
            self.add_input_digest(digest, DigestKind::Poseidon2);
        }
        Ok(())
    }

    /// Add a receipt covering some generic claim. Do not include any claim information.
    fn add_assumption_receipt<Claim>(
        &mut self,
        assumption: Assumption,
        receipt: &SuccinctReceipt<Claim>,
    ) -> Result<()> {
        self.add_seal(
            &receipt.seal,
            &receipt.control_id,
            &receipt.control_inclusion_proof,
        )?;
        // Resolve program expects an additional boolean to tell it when the control root is zero.
        let zero_root = BabyBearElem::new((assumption.control_root == Digest::ZERO) as u32);
        self.add_input(bytemuck::cast_slice(&[zero_root]));
        Ok(())
    }

    fn add_succinct_work_claim_rv32im_receipt(
        &mut self,
        a: &SuccinctReceipt<WorkClaim<ReceiptClaim>>,
    ) -> Result<()> {
        self.add_seal(&a.seal, &a.control_id, &a.control_inclusion_proof)?;
        let mut data = Vec::<u32>::new();
        a.claim.as_value()?.encode_to_seal(&mut data)?;
        let data_fp: Vec<BabyBearElem> = data.iter().map(|x| BabyBearElem::new(*x)).collect();
        self.add_input(bytemuck::cast_slice(&data_fp));
        Ok(())
    }

    /// Add a receipt covering rv32im execution, and include the first level of ReceiptClaim.
    fn add_succinct_rv32im_receipt(&mut self, a: &SuccinctReceipt<ReceiptClaim>) -> Result<()> {
        self.add_seal(&a.seal, &a.control_id, &a.control_inclusion_proof)?;
        let mut data = Vec::<u32>::new();
        a.claim.as_value()?.encode(&mut data)?;
        let data_fp: Vec<BabyBearElem> = data.iter().map(|x| BabyBearElem::new(*x)).collect();
        self.add_input(bytemuck::cast_slice(&data_fp));
        Ok(())
    }

    /// Add a receipt for a succinct receipt
    fn add_succinct_generic_receipt<Claim>(&mut self, a: &SuccinctReceipt<Claim>) -> Result<()> {
        self.add_seal(&a.seal, &a.control_id, &a.control_inclusion_proof)?;
        // Union program expects an additional boolean to indicate that control root is zero.
        let zero_root = BabyBearElem::new((a.control_root()? == Digest::ZERO) as u32);
        self.add_input(bytemuck::cast_slice(&[zero_root]));
        Ok(())
    }

    /// Run the prover, producing a receipt of execution for the recursion circuit over the loaded
    /// program and input.
    pub fn run(&mut self) -> Result<RecursionReceipt> {
        self.prover.run()
    }
}

fn check_resolve_assumption<Claim>(
    cond: &MaybePruned<ReceiptClaim>,
    assum: &MaybePruned<Claim>,
) -> Result<(Assumption, Assumptions, Output)>
where
    Claim: risc0_binfmt::Digestible + Debug,
{
    let output = cond
        .as_value()
        .context("cannot resolve conditional receipt with pruned claim")?
        .output
        .as_value()
        .context("cannot resolve conditional receipt with pruned output")?
        .as_ref()
        .ok_or_else(|| anyhow!("cannot resolve conditional receipt with no output"))?
        .clone();

    // Unwrap the MaybePruned assumptions list and resolve the corroborated assumption,
    // removing the head and leaving the tail of the list.
    let assumptions = output
        .assumptions
        .clone()
        .value()
        .context("cannot resolve conditional receipt with pruned assumptions")?;
    let head: Assumption = assumptions
        .0
        .first()
        .ok_or_else(|| anyhow!("cannot resolve conditional receipt with no assumptions"))?
        .as_value()
        .context("cannot resolve conditional receipt with pruned head assumption")?
        .clone();

    ensure!(
        head.claim == assum.digest(),
        "assumption receipt claim does not match head of assumptions list"
    );

    let mut assumptions_tail = assumptions;
    assumptions_tail.resolve(&head.digest())?;

    Ok((head, assumptions_tail, output))
}
