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

pub mod exec;
mod memory_argument;
mod merkle;
mod preflight;
pub mod program;
mod zkr;

use std::{collections::VecDeque, rc::Rc};

use anyhow::Result;
use hex::FromHex;
use risc0_circuit_rv32im::control_id::POSEIDON_CONTROL_ID;
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    Elem,
};
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStepContext, TapsProvider},
    core::{
        digest::Digest,
        hash::{poseidon::PoseidonHashSuite, HashSuite},
    },
    hal::{cpu::CpuHal, CircuitHal, Hal},
    prove::adapter::ProveAdapter,
    verify::ReadIOP,
    MIN_CYCLES_PO2, ZK_CYCLES,
};

use self::{exec::RecursionExecutor, merkle::MerkleGroup, program::Program};
use super::cpu::CpuCircuitHal;
use crate::{
    valid_control_ids, CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};

// TODO: Automatically generate these constants from the circuit somehow without
// messing up bootstrap dependencies.

/// Number of rows to use for the recursion circuit witness as a power of 2.
const RECURSION_PO2: usize = 18;

/// Depth of the Merkle tree to use for encoding the set of allowed control IDs.
/// NOTE: Changing this constant must be coordinated with the circuit. In order to avoid needing to
/// change the circuit later, this is set to 8 which allows for enough control IDs to be ecoded
/// that we are unlikely to need more.
const ALLOWED_CODE_MERKLE_DEPTH: usize = 8;

#[derive(Clone, Debug)]
pub struct RecursionReceipt {
    pub control_id: Digest,
    pub seal: Vec<u32>,
    pub data: Vec<u32>,
}

/// Options available to modify the prover's behavior.
pub struct ProverOpts {
    suite: HashSuite<BabyBear>,
}

impl Default for ProverOpts {
    fn default() -> ProverOpts {
        ProverOpts {
            suite: PoseidonHashSuite::new_suite(),
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

/// Kinds of digests recognized by the recursion program language.
// NOTE: Default is additionally a recognized type in the recursion program language. It's not
// yet supported here because some of the code in this module assumes Poseidon is Default.
enum DigestKind {
    Poseidon,
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

    /// Initialize a recursion prover with the test recursion program. This program is used in
    /// testing the basic correctness of the recursion circuit.
    pub fn new_test_recursion_circuit(digests: [&Digest; 2], opts: ProverOpts) -> Result<Self> {
        let (program, control_id) = zkr::test_recursion_circuit()?;
        let mut prover = Prover::new(program, control_id, opts);

        for digest in digests {
            prover.add_input_digest(digest, DigestKind::Poseidon);
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
        tracing::debug!("Control ID = {control_id:?}");
        self.add_input(seal);
        let proof = allowed_ids.get_proof(control_id, self.opts.suite.hashfn.as_ref())?;
        tracing::debug!("index = {:?}", proof.index);
        self.add_input(bytemuck::cast_slice(&[BabyBearElem::new(
            proof.index as u32,
        )]));
        for digest in proof.digests {
            tracing::debug!("path = {digest:?}");
            self.add_input_digest(&digest, DigestKind::Poseidon);
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

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon);

        let which = po2 - MIN_CYCLES_PO2;
        let inner_control_id = Digest::from_hex(POSEIDON_CONTROL_ID[which]).unwrap();
        prover.add_seal(seal, &inner_control_id, &allowed_ids)?;

        Ok(prover)
    }

    fn add_segment_receipt(
        &mut self,
        segment: &RecursionReceipt,
        allowed_ids: &MerkleGroup,
    ) -> Result<()> {
        self.add_seal(&segment.seal, &segment.control_id, &allowed_ids)?;
        let data_fp: Vec<BabyBearElem> =
            segment.data.iter().map(|x| BabyBearElem::new(*x)).collect();
        self.add_input(bytemuck::cast_slice(&data_fp));
        Ok(())
    }

    /// Initialize a recursion prover with the join program to compress two receipts of the same
    /// session into one.
    ///
    /// By repeated application of the join program, any number of receipts for execution spans
    /// within the same session can be compressed into a single receipt for the entire session.
    pub fn new_join(
        left: &RecursionReceipt,
        right: &RecursionReceipt,
        opts: ProverOpts,
    ) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::join()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon);
        prover.add_segment_receipt(left, &allowed_ids)?;
        prover.add_segment_receipt(right, &allowed_ids)?;

        Ok(prover)
    }

    /// Initialize a recursion prover with the resolve program to remove an assumption from a
    /// conditional receipt upon verifying a corroborating receipt for the assumption.
    ///
    /// By applying the resolve program, a conditional receipt (i.e. a receipt for an execution
    /// using the `env::verify` API to logically verify a receipt) can be made into an
    /// unconditional receipt.
    pub fn new_resolve(
        cond: &RecursionReceipt,
        corr: &RecursionReceipt,
        assumptions_digest: &Digest,
        journal_digest: &Digest,
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
        prover.add_input_digest(&merkle_root, DigestKind::Poseidon);
        prover.add_segment_receipt(cond, &allowed_ids)?;
        prover.add_segment_receipt(corr, &allowed_ids)?;
        prover.add_input_digest(assumptions_digest, DigestKind::Sha256);
        prover.add_input_digest(journal_digest, DigestKind::Sha256);

        Ok(prover)
    }

    /// Prove the verification of a recursion receipt, applying no changes to [ReceiptClaim].
    ///
    /// The primary use for this program is to transform the receipt itself, e.g. using a different
    /// hash function for FRI. See [identity_p254] for more information.
    pub fn new_identity(segment: &RecursionReceipt, opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::identity()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root, DigestKind::Poseidon);
        prover.add_segment_receipt(segment, &allowed_ids)?;

        Ok(prover)
    }

    fn add_input(&mut self, input: &[u32]) {
        self.input.extend(input);
    }

    /// Add a digest to the input for the recursion program.
    fn add_input_digest(&mut self, digest: &Digest, kind: DigestKind) {
        match kind {
            // Poseidon digests consist of BabyBear field elems and do not need to be split.
            DigestKind::Poseidon => self.add_input(digest.as_words()),
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
        let hal_pair = poseidon_hal_pair();
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
        let machine_ctx = self.preflight()?;

        let split_points = std::mem::take(&mut self.split_points);

        let mut executor = RecursionExecutor::new(&self.program, machine_ctx, split_points);
        executor.run()?;

        let mut adapter = ProveAdapter::new(&mut executor.executor);
        let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());

        adapter.execute(prover.iop());

        prover.set_po2(adapter.po2() as usize);

        prover.commit_group(
            REGISTER_GROUP_CODE,
            hal.copy_from_elem("code", &*adapter.get_code().as_slice()),
        );
        prover.commit_group(
            REGISTER_GROUP_DATA,
            hal.copy_from_elem("data", &*adapter.get_data().as_slice()),
        );
        adapter.accumulate(prover.iop());
        prover.commit_group(
            REGISTER_GROUP_ACCUM,
            hal.copy_from_elem("accum", &*adapter.get_accum().as_slice()),
        );

        let mix = hal.copy_from_elem("mix", &*adapter.get_mix().as_slice());
        let out = hal.copy_from_elem("out", &*adapter.get_io().as_slice());

        let seal = prover.finalize(&[&mix, &out], circuit_hal);

        Ok(RecursionReceipt {
            control_id: self.control_id,
            seal: seal.into(),
            data: self.output.clone(),
        })
    }

    #[tracing::instrument(skip_all)]
    fn preflight(&mut self) -> Result<exec::MachineContext> {
        let mut machine = exec::MachineContext::new(std::mem::take(&mut self.input).into());
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

/// A pair of [Hal] and [CircuitHal].
#[derive(Clone)]
pub struct HalPair<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    /// A [Hal] implementation.
    pub hal: Rc<H>,

    /// An [CircuitHal] implementation.
    pub circuit_hal: Rc<C>,
}

#[cfg(feature = "cuda")]
mod cuda {
    pub use crate::prove::cuda::{
        CudaCircuitHalPoseidon, CudaCircuitHalPoseidon2, CudaCircuitHalSha256,
    };
    pub use risc0_zkp::{
        core::hash::poseidon_254::Poseidon254HashSuite,
        hal::cuda::{CudaHalPoseidon, CudaHalPoseidon2, CudaHalSha256},
    };

    use super::{BabyBear, CpuCircuitHal, CpuHal, HalPair, Rc};

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

    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        HalPair { hal, circuit_hal }
    }
}

#[cfg(feature = "metal")]
mod metal {
    pub use crate::prove::metal::MetalCircuitHal;
    pub use risc0_zkp::{
        core::hash::poseidon_254::Poseidon254HashSuite,
        hal::metal::{
            MetalHalPoseidon, MetalHalPoseidon2, MetalHalSha256, MetalHashPoseidon,
            MetalHashPoseidon2, MetalHashSha256,
        },
    };

    use super::{BabyBear, CpuCircuitHal, CpuHal, HalPair, Rc};

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

    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        HalPair { hal, circuit_hal }
    }
}

mod cpu {
    use risc0_zkp::{
        core::hash::{
            poseidon2::Poseidon2HashSuite, poseidon_254::Poseidon254HashSuite, sha::Sha256HashSuite,
        },
        hal::cpu::CpuHal,
    };
    use std::rc::Rc;

    use crate::prove::cpu::CpuCircuitHal;

    use super::{BabyBear, HalPair, PoseidonHashSuite};

    #[allow(dead_code)]
    pub fn sha256_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(Sha256HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(PoseidonHashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon2_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(Poseidon2HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
        HalPair { hal, circuit_hal }
    }

    #[allow(dead_code)]
    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new());
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
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            cuda::poseidon254_hal_pair()
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
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            metal::poseidon254_hal_pair()
        }
    } else {
        /// TODO
        #[allow(dead_code)]
        pub fn sha256_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            cpu::sha256_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            cpu::poseidon_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon2_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            cpu::poseidon2_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal> {
            cpu::poseidon254_hal_pair()
        }
    }
}
