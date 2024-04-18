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

mod exec;
pub mod merkle;
mod plonk;
pub mod preflight;
mod program;
pub mod zkr;

use std::{collections::VecDeque, mem::take, rc::Rc};

use anyhow::{anyhow, Context, Result};
use hex::FromHex;
use merkle::MerkleGroup;
use rand::thread_rng;
use risc0_circuit_recursion::{
    cpu::CpuCircuitHal, CircuitImpl, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};
use risc0_circuit_rv32im::control_id::POSEIDON2_CONTROL_ID;
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStepContext, TapsProvider, PROOF_SYSTEM_INFO},
    core::{
        digest::Digest,
        hash::{poseidon::PoseidonHashSuite, poseidon2::Poseidon2HashSuite, HashSuite},
    },
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem,
    },
    hal::{cpu::CpuHal, CircuitHal, Hal},
    prove::adapter::ProveAdapter,
    verify::ReadIOP,
    MIN_CYCLES_PO2, ZK_CYCLES,
};
use serde::{Deserialize, Serialize};

pub use self::program::Program;
use super::CIRCUIT;
use crate::{
    receipt_claim::{Merge, Output},
    recursion::{valid_control_ids, SuccinctReceipt},
    sha::Digestible,
    HalPair, ReceiptClaim, SegmentReceipt,
};

// TODO: Automatically generate these constants from the circuit somehow without
// messing up bootstrap dependencies.
/// Number of rows to use for the recursion circuit witness as a power of 2.
pub const RECURSION_PO2: usize = 18;
/// Depth of the Merkle tree to use for encoding the set of allowed control IDs.
/// NOTE: Changing this constant must be coordinated with the circuit. In order to avoid needing to
/// change the circuit later, this is set to 8 which allows for enough control IDs to be encoded
/// that we are unlikely to need more.
const ALLOWED_CODE_MERKLE_DEPTH: usize = 8;
/// Size of the code group in the taps of the recursion circuit.
const RECURSION_CODE_SIZE: usize = 23;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RecursionReceipt {
    pub control_id: Digest,
    pub seal: Vec<u32>,
    pub output: Vec<u32>,
}

/// Run the lift program to transform an rv32im segment receipt into a recursion receipt.
///
/// The lift program verifies the rv32im circuit STARK proof inside the recursion circuit,
/// resulting in a recursion circuit STARK proof. This recursion proof has a single
/// constant-time verification procedure, with respect to the original segment length, and is then
/// used as the input to all other recursion programs (e.g. join, resolve, and identity_p254).
pub fn lift(segment_receipt: &SegmentReceipt) -> Result<SuccinctReceipt> {
    tracing::debug!("Proving lift: claim = {:#?}", segment_receipt.claim);
    let mut prover = Prover::new_lift(&segment_receipt.seal, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());
    let claim_decoded = ReceiptClaim::decode(&mut out_stream)?;
    tracing::debug!("Proving lift finished: decoded claim = {claim_decoded:#?}");
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim: claim_decoded.merge(&segment_receipt.claim)?,
    })
}

/// Run the join program to compress two receipts of the same session into one.
///
/// By repeated application of the join program, any number of receipts for execution spans within
/// the same session can be compressed into a single receipt for the entire session.
pub fn join(a: &SuccinctReceipt, b: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    tracing::debug!("Proving join: a.claim = {:#?}", a.claim);
    tracing::debug!("Proving join: b.claim = {:#?}", b.claim);

    let mut prover = Prover::new_join(a, b, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());

    // Construct the expected claim that should have result from the join.
    let ab_claim = ReceiptClaim {
        pre: a.claim.pre.clone(),
        post: b.claim.post.clone(),
        exit_code: b.claim.exit_code,
        input: a.claim.input.clone(),
        output: b.claim.output.clone(),
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
/// receipt proving the validity of the assumption.
///
/// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution using
/// the `env::verify` API to logically verify a receipt) can be made into an unconditional receipt.
pub fn resolve(
    conditional: &SuccinctReceipt,
    assumption: &SuccinctReceipt,
) -> Result<SuccinctReceipt> {
    tracing::debug!(
        "Proving resolve: conditional.claim = {:#?}",
        conditional.claim,
    );
    tracing::debug!(
        "Proving resolve: assumption.claim = {:#?}",
        assumption.claim,
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
        .resolve(&assumption.claim.digest())?;

    let mut prover = Prover::new_resolve(conditional, assumption, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());

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
/// produced with Poseidon over the BN254 base field compared to using Poseidon over BabyBear.
pub fn identity_p254(a: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
    let mut prover = Prover::new_identity(a, ProverOpts::default())?;
    let receipt = prover.run_with_hal(hal, circuit_hal)?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());
    let claim = ReceiptClaim::decode(&mut out_stream)?.merge(&a.claim)?;
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        claim,
    })
}

/// Options available to modify the prover's behavior.
pub struct ProverOpts {
    pub(crate) skip_seal: bool,
    suite: HashSuite<BabyBear>,
}

impl ProverOpts {
    /// If true, skip generating the seal in receipt.  This should
    /// only be used for testing. In this case, performance will be
    /// much better but we will not be able to cryptographically
    /// verify the execution.
    pub fn with_skip_seal(self, skip_seal: bool) -> Self {
        Self { skip_seal, ..self }
    }
}

impl Default for ProverOpts {
    fn default() -> ProverOpts {
        ProverOpts {
            skip_seal: false,
            suite: Poseidon2HashSuite::new_suite(),
        }
    }
}

/// Prover for the recursion circuit.
pub struct Prover {
    program: Program,
    control_id: Digest,
    opts: ProverOpts,
    input: VecDeque<u32>,
    split_points: Vec<usize>,
    output: Vec<u32>,
}

#[cfg(feature = "cuda")]
mod cuda {
    pub use risc0_circuit_recursion::cuda::{
        CudaCircuitHalPoseidon, CudaCircuitHalPoseidon2, CudaCircuitHalSha256,
    };
    pub use risc0_zkp::hal::cuda::{CudaHalPoseidon, CudaHalPoseidon2, CudaHalSha256};

    use super::{HalPair, Rc};

    pub fn sha256_hal_pair() -> HalPair<CudaHalSha256, CudaCircuitHalSha256> {
        let hal = Rc::new(CudaHalSha256::new());
        let circuit_hal = Rc::new(CudaCircuitHalSha256::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }

    pub fn poseidon_hal_pair() -> HalPair<CudaHalPoseidon, CudaCircuitHalPoseidon> {
        let hal = Rc::new(CudaHalPoseidon::new());
        let circuit_hal = Rc::new(CudaCircuitHalPoseidon::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }

    pub fn poseidon2_hal_pair() -> HalPair<CudaHalPoseidon2, CudaCircuitHalPoseidon2> {
        let hal = Rc::new(CudaHalPoseidon2::new());
        let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }
}

#[cfg(feature = "metal")]
mod metal {
    pub use risc0_circuit_recursion::metal::MetalCircuitHal;
    pub use risc0_zkp::hal::metal::{
        MetalHalPoseidon, MetalHalPoseidon2, MetalHalSha256, MetalHashPoseidon, MetalHashPoseidon2,
        MetalHashSha256,
    };

    use super::{HalPair, Rc};

    pub fn sha256_hal_pair() -> HalPair<MetalHalSha256, MetalCircuitHal<MetalHashSha256>> {
        let hal = Rc::new(MetalHalSha256::new());
        let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashSha256>::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }

    pub fn poseidon_hal_pair() -> HalPair<MetalHalPoseidon, MetalCircuitHal<MetalHashPoseidon>> {
        let hal = Rc::new(MetalHalPoseidon::new());
        let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashPoseidon>::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }

    pub fn poseidon2_hal_pair() -> HalPair<MetalHalPoseidon2, MetalCircuitHal<MetalHashPoseidon2>> {
        let hal = Rc::new(MetalHalPoseidon2::new());
        let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashPoseidon2>::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }
}

mod cpu {
    use risc0_zkp::core::hash::{poseidon_254::Poseidon254HashSuite, sha::Sha256HashSuite};

    use super::{
        BabyBear, CircuitImpl, CpuCircuitHal, CpuHal, HalPair, Poseidon2HashSuite,
        PoseidonHashSuite, Rc, CIRCUIT,
    };

    #[allow(dead_code)]
    pub fn sha256_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(Sha256HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(PoseidonHashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon2_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(Poseidon2HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>>
    {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }
}

cfg_if::cfg_if! {
    if #[cfg(feature = "cuda")] {
        /// TODO
        #[allow(dead_code)]
        pub fn sha256_hal_pair() -> HalPair<cuda::CudaHalSha256, cuda::CudaCircuitHalSha256> {
            cuda::sha256_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon_hal_pair() -> HalPair<cuda::CudaHalPoseidon, cuda::CudaCircuitHalPoseidon> {
            cuda::poseidon_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon2_hal_pair() -> HalPair<cuda::CudaHalPoseidon2, cuda::CudaCircuitHalPoseidon2> {
            cuda::poseidon2_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon254_hal_pair()
        }
    } else if #[cfg(feature = "metal")] {
        /// TODO
        #[allow(dead_code)]
        pub fn sha256_hal_pair() -> HalPair<metal::MetalHalSha256, metal::MetalCircuitHal<metal::MetalHashSha256>> {
            metal::sha256_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon_hal_pair() -> HalPair<metal::MetalHalPoseidon, metal::MetalCircuitHal<metal::MetalHashPoseidon>> {
            metal::poseidon_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon2_hal_pair() -> HalPair<metal::MetalHalPoseidon2, metal::MetalCircuitHal<metal::MetalHashPoseidon2>> {
            metal::poseidon2_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon254_hal_pair()
        }
    } else {
        /// TODO
        #[allow(dead_code)]
        pub fn sha256_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::sha256_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon2_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon2_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon254_hal_pair()
        }
    }
}

/// Kinds of digests recognized by the recursion program language.
// NOTE: Default is additionally a recognized type in the recursion program language. It's not
// yet supported here because some of the code in this module assumes Poseidon2 is Default.
enum DigestKind {
    Poseidon2,
    Sha256,
}

impl Prover {
    fn new(program: Program, control_id: Digest, opts: ProverOpts) -> Self {
        Self {
            program,
            control_id,
            opts,
            input: VecDeque::new(),
            split_points: Vec::new(),
            output: Vec::new(),
        }
    }

    /// Construct a Merkle tree encoding the set of accepted control IDs.
    ///
    /// This set of control IDs forms the closure of recursion programs that can be applied to the
    /// receipts. Verifiers will use the root of this tree to constrain the Prover to only apply
    /// those programs in its processing of receipts.
    pub fn make_allowed_tree() -> MerkleGroup {
        MerkleGroup {
            depth: ALLOWED_CODE_MERKLE_DEPTH,
            leaves: valid_control_ids(),
        }
    }

    /// Construct a Merkle tree encoding the set of accepted control IDs.
    ///
    /// Provide the set of allowed IDs during the bootstrapping process.
    pub fn bootstrap_allowed_tree(leaves: Vec<Digest>) -> MerkleGroup {
        MerkleGroup {
            depth: ALLOWED_CODE_MERKLE_DEPTH,
            leaves,
        }
    }

    /// Initialize a recursion prover with the test recursion program. This program is used in
    /// testing the basic correctness of the recursion circuit.
    pub fn new_test_recursion_circuit(digests: [&Digest; 2], opts: ProverOpts) -> Result<Self> {
        let (program, control_id) = zkr::test_recursion_circuit()?;
        let mut prover = Prover::new(program, control_id, opts);

        for digest in digests {
            prover.add_input_digest(digest, DigestKind::Poseidon2);
        }

        Ok(prover)
    }

    /// Add a recursion seal (i.e. STARK proof) to input tape of the recursion program.
    pub fn add_seal(
        &mut self,
        seal: &[u32],
        control_id: &Digest,
        allowed_ids: &MerkleGroup,
    ) -> Result<()> {
        tracing::debug!("Control ID = {:?}", control_id);
        self.add_input(seal);
        let proof = allowed_ids.get_proof(control_id, self.opts.suite.hashfn.as_ref())?;
        tracing::debug!("index = {:?}", proof.index);
        self.add_input(bytemuck::cast_slice(&[BabyBearElem::new(
            proof.index as u32,
        )]));
        for digest in proof.digests {
            tracing::debug!("path = {:?}", digest);
            self.add_input_digest(&digest, DigestKind::Poseidon2);
        }
        tracing::debug!(
            "root = {:?}",
            allowed_ids.calc_root(self.opts.suite.hashfn.as_ref())
        );
        Ok(())
    }

    /// Initialize a recursion prover with the lift program to transform an rv32im segment receipt
    /// into a recursion receipt.
    ///
    /// The lift program is verifies the rv32im circuit STARK proof inside the recursion circuit,
    /// resulting in a recursion circuit STARK proof. This recursion proof has a single
    /// constant-time verification procedure, with respect to the original segment length, and is
    /// then used as the input to all other recursion programs (e.g. join, resolve, and
    /// identity_p254).
    pub fn new_lift(seal: &[u32], opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let mut iop = ReadIOP::new(seal, opts.suite.rng.as_ref());
        iop.read_field_elem_slice::<BabyBearElem>(risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE);
        let po2 = *iop.read_u32s(1).first().unwrap() as usize;

        let (program, control_id) = zkr::lift(po2)?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);

        let which = po2 - MIN_CYCLES_PO2;
        let inner_control_id = Digest::from_hex(POSEIDON2_CONTROL_ID[which]).unwrap();
        prover.add_seal(seal, &inner_control_id, &allowed_ids)?;

        Ok(prover)
    }

    fn add_segment_receipt(
        &mut self,
        a: &SuccinctReceipt,
        allowed_ids: &MerkleGroup,
    ) -> Result<()> {
        self.add_seal(&a.seal, &a.control_id, &allowed_ids)?;
        let mut data = Vec::<u32>::new();
        a.claim.encode(&mut data)?;
        let data_fp: Vec<BabyBearElem> = data.iter().map(|x| BabyBearElem::new(*x)).collect();
        self.add_input(bytemuck::cast_slice(&data_fp));
        Ok(())
    }

    /// Initialize a recursion prover with the join program to compress two receipts of the same
    /// session into one.
    ///
    /// By repeated application of the join program, any number of receipts for execution spans
    /// within the same session can be compressed into a single receipt for the entire session.
    pub fn new_join(a: &SuccinctReceipt, b: &SuccinctReceipt, opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::join()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_segment_receipt(a, &allowed_ids)?;
        prover.add_segment_receipt(b, &allowed_ids)?;
        Ok(prover)
    }

    /// Initialize a recursion prover with the resolve program to remove an assumption from a
    /// conditional receipt upon verifying a receipt proving the validity of the assumption.
    ///
    /// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution
    /// using the `env::verify` API to logically verify a receipt) can be made into an
    /// unconditional receipt.
    pub fn new_resolve(
        cond: &SuccinctReceipt,
        assum: &SuccinctReceipt,
        opts: ProverOpts,
    ) -> Result<Self> {
        // Construct the Merkle tree of all acceptable recursion predicate control IDs.
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        // Load the resolve predicate as a Program and construct the prover.
        let (program, control_id) = zkr::resolve()?;
        let mut prover = Prover::new(program, control_id, opts);

        // Load the input values needed by the predicate.
        // Resolve predicate needs both seals as input, and the journal and assumptions tail digest
        // to compute the opening of the conditional receipt claim to the first assumption.
        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_segment_receipt(cond, &allowed_ids)?;
        prover.add_segment_receipt(assum, &allowed_ids)?;

        let Output {
            assumptions,
            journal,
        } = cond
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
        assumptions_tail.resolve(&assum.claim.digest())?;

        prover.add_input_digest(&assumptions_tail.digest(), DigestKind::Sha256);
        prover.add_input_digest(&journal.digest(), DigestKind::Sha256);
        Ok(prover)
    }

    /// Prove the verification of a recursion receipt, applying no changes to [ReceiptClaim].
    ///
    /// The primary use for this program is to transform the receipt itself, e.g. using a different
    /// hash function for FRI. See [identity_p254] for more information.
    pub fn new_identity(a: &SuccinctReceipt, opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::identity()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon2);
        prover.add_segment_receipt(a, &allowed_ids)?;
        Ok(prover)
    }

    fn add_input(&mut self, input: &[u32]) {
        self.input.extend(input);
    }

    /// Add a digest to the input for the recursion program.
    fn add_input_digest(&mut self, digest: &Digest, kind: DigestKind) {
        match kind {
            // Poseidon2 digests consist of  BabyBear field elems and do not need to be split.
            DigestKind::Poseidon2 => self.add_input(digest.as_words()),
            // SHA-256 digests need to be split into 16-bit half words to avoid overflowing.
            DigestKind::Sha256 => self.add_input(bytemuck::cast_slice(
                &digest
                    .as_words()
                    .iter()
                    .copied()
                    .flat_map(|x| [x & 0xffff, x >> 16])
                    .map(BabyBearElem::new)
                    .collect::<Vec<_>>(),
            )),
        }
    }

    /// Run the prover, producing a receipt of execution for the recursion circuit over the loaded
    /// program and input.
    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<RecursionReceipt> {
        let hal_pair = poseidon2_hal_pair();
        let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
        self.run_with_hal(hal, circuit_hal)
    }

    /// Run the prover, producing a receipt of execution for the recursion circuit over the loaded
    /// program and input, using the specified HAL.
    #[tracing::instrument(skip_all)]
    pub fn run_with_hal<H, C>(&mut self, hal: &H, circuit_hal: &C) -> Result<RecursionReceipt>
    where
        H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
        C: CircuitHal<H>,
    {
        let skip_seal = self.opts.skip_seal;

        let machine_ctx = self.preflight()?;

        let split_points = core::mem::take(&mut self.split_points);

        let mut executor =
            exec::RecursionExecutor::new(&CIRCUIT, &self.program, machine_ctx, split_points);
        executor.run()?;

        let mut adapter = ProveAdapter::new(&mut executor.executor);
        let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());
        let hashfn = Rc::clone(&hal.get_hash_suite().hashfn);

        // At the start of the protocol, seed the Fiat-Shamir transcript with context information
        // about the proof system and circuit.
        prover
            .iop()
            .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
        prover
            .iop()
            .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

        adapter.execute(prover.iop(), hal);

        let seal = if skip_seal {
            Vec::new()
        } else {
            prover.set_po2(adapter.po2() as usize);

            let ctrl = hal.copy_from_elem("ctrl", &adapter.get_code().as_slice());
            prover.commit_group(REGISTER_GROUP_CTRL, &ctrl);

            let data = hal.copy_from_elem("data", &adapter.get_data().as_slice());
            prover.commit_group(REGISTER_GROUP_DATA, &data);

            // Make the mixing values
            let mix: Vec<_> = (0..CircuitImpl::MIX_SIZE)
                .map(|_| prover.iop().random_elem())
                .collect();
            let mix = hal.copy_from_elem("mix", mix.as_slice());

            let steps = adapter.get_steps();
            let mut accum = vec![BabyBearElem::INVALID; steps * CIRCUIT.accum_size()];

            // Add random noise to end of accum
            let mut rng = thread_rng();
            for i in steps - ZK_CYCLES..steps {
                for j in 0..CIRCUIT.accum_size() {
                    accum[j * steps + i] = BabyBearElem::random(&mut rng);
                }
            }

            let io = hal.copy_from_elem("io", &adapter.get_io().as_slice());
            let accum = hal.copy_from_elem("accum", accum.as_slice());

            circuit_hal.accumulate(&ctrl, &io, &data, &mix, &accum, steps);

            prover.commit_group(REGISTER_GROUP_ACCUM, &accum);

            prover.finalize(&[&mix, &io], circuit_hal)
        };

        Ok(RecursionReceipt {
            control_id: self.control_id,
            seal: seal.into(),
            output: self.output.clone(),
        })
    }

    #[tracing::instrument(skip_all)]
    fn preflight(&mut self) -> Result<exec::MachineContext> {
        let mut machine = exec::MachineContext::new(take(&mut self.input).into());
        let mut preflight = preflight::Preflight::new(&mut machine);

        for (cycle, row) in self.program.code_by_row().enumerate() {
            let ctx = CircuitStepContext {
                cycle,
                size: (1 << RECURSION_PO2) - ZK_CYCLES,
            };

            preflight.set_top(&ctx, row)?
        }

        // TODO: is this necessary?
        let zero_row = vec![BabyBearElem::ZERO; self.program.code_size];
        for cycle in self.program.code_rows()..(1 << RECURSION_PO2) - ZK_CYCLES {
            let ctx = CircuitStepContext {
                cycle,
                size: (1 << RECURSION_PO2) - ZK_CYCLES,
            };

            preflight.set_top(&ctx, &zero_row)?
        }

        self.split_points = preflight.split_points;
        self.split_points.push((1 << RECURSION_PO2) - ZK_CYCLES);
        self.output = preflight.output;
        machine.iop_reads = preflight.iop_reads;
        Ok(machine)
    }
}
