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

mod exec;
pub mod merkle;
mod plonk;
pub mod preflight;
mod program;
pub mod zkr;

use std::{collections::VecDeque, mem::take, rc::Rc};

use anyhow::Result;
use hex::FromHex;
use merkle::MerkleGroup;
use risc0_circuit_recursion::{
    cpu::CpuCircuitHal, CircuitImpl, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStepContext, TapsProvider},
    core::{
        digest::{Digest, DIGEST_WORDS},
        hash::{poseidon::PoseidonHashSuite, HashSuite},
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
    recursion::{valid_control_ids, SuccinctReceipt},
    HalPair, ReceiptMetadata, SegmentReceipt, POSEIDON_CONTROL_ID,
};

const RECURSION_PO2: usize = 18;
const ALLOWED_CODE_MERKLE_DEPTH: usize = 8;
// TODO: Automatically generate this from the circuit somehow without
// messing up bootstrap dependencies.
const RECURSION_CODE_SIZE: usize = 21;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RecursionReceipt {
    pub control_id: Digest,
    pub allowed_code: Digest,
    pub output_digest: Digest,
    pub seal: Vec<u32>,
    pub output: Vec<u32>,
}

/// TODO
pub fn lift(receipt: &SegmentReceipt) -> Result<SuccinctReceipt> {
    let mut prover = Prover::new_lift(&receipt.seal, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());
    let meta = ReceiptMetadata::decode(&mut out_stream)?;
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        meta,
    })
}

/// TODO
pub fn join(a: &SuccinctReceipt, b: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    let mut prover = Prover::new_join(a, b, ProverOpts::default())?;
    let receipt = prover.run()?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());
    let meta = ReceiptMetadata::decode(&mut out_stream)?;
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        meta,
    })
}

/// TODO
pub fn identity_p254(a: &SuccinctReceipt) -> Result<SuccinctReceipt> {
    let hal_pair = poseidon254_hal_pair();
    let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
    let mut prover = Prover::new_identity(a, ProverOpts::default())?;
    let receipt = prover.run_with_hal(hal, circuit_hal)?;
    let mut out_stream = VecDeque::<u32>::new();
    out_stream.extend(receipt.output.iter());
    let meta = ReceiptMetadata::decode(&mut out_stream)?;
    Ok(SuccinctReceipt {
        seal: receipt.seal,
        control_id: receipt.control_id,
        meta,
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
            suite: PoseidonHashSuite::new_suite(),
        }
    }
}

/// TODO
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
    pub use risc0_circuit_recursion::cuda::{CudaCircuitHalPoseidon, CudaCircuitHalSha256};
    pub use risc0_zkp::{
        core::hash::poseidon_254::Poseidon254HashSuite,
        hal::cuda::{CudaHalPoseidon, CudaHalSha256},
    };

    use super::{BabyBear, CircuitImpl, CpuCircuitHal, CpuHal, HalPair, Rc, CIRCUIT};

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

    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>>
    {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }
}

#[cfg(feature = "metal")]
mod metal {
    pub use risc0_circuit_recursion::metal::MetalCircuitHal;
    pub use risc0_zkp::{
        core::hash::poseidon_254::Poseidon254HashSuite,
        hal::metal::{MetalHalPoseidon, MetalHalSha256, MetalHashPoseidon, MetalHashSha256},
    };

    use super::{BabyBear, CircuitImpl, CpuCircuitHal, CpuHal, HalPair, Rc, CIRCUIT};

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

    pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>>
    {
        let hal = Rc::new(CpuHal::new(Poseidon254HashSuite::new_suite()));
        let circuit_hal = Rc::new(CpuCircuitHal::new(&CIRCUIT));
        HalPair { hal, circuit_hal }
    }
}

mod cpu {
    use risc0_zkp::core::hash::{poseidon_254::Poseidon254HashSuite, sha::Sha256HashSuite};

    use super::{
        BabyBear, CircuitImpl, CpuCircuitHal, CpuHal, HalPair, PoseidonHashSuite, Rc, CIRCUIT,
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
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
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
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            metal::poseidon254_hal_pair()
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
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon254_hal_pair()
        }
    }
}

fn shorts_to_digest(elems: &[BabyBearElem]) -> Digest {
    let words: Vec<u32> = elems
        .chunks_exact(2)
        .map(|shortpair| {
            let [a, b] = shortpair else { unreachable!() };
            ((u64::from(*b) << 16) + u64::from(*a)) as u32
        })
        .collect();
    Digest::try_from(words.as_slice()).unwrap()
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

    /// TODO
    pub fn make_allowed_tree() -> MerkleGroup {
        MerkleGroup {
            depth: ALLOWED_CODE_MERKLE_DEPTH,
            leaves: valid_control_ids(),
        }
    }

    /// TODO
    pub fn new_test_recursion_circuit(digests: [&Digest; 2], opts: ProverOpts) -> Result<Self> {
        let (program, control_id) = zkr::test_recursion_circuit()?;
        let mut prover = Prover::new(program, control_id, opts);

        for digest in digests {
            prover.add_input_digest(digest);
        }

        Ok(prover)
    }

    /// TODO
    pub fn add_seal(
        &mut self,
        seal: &[u32],
        control_id: &Digest,
        allowed_ids: &MerkleGroup,
    ) -> Result<()> {
        log::debug!("Control ID = {:?}", control_id);
        self.add_input(seal);
        let proof = allowed_ids.get_proof(control_id, self.opts.suite.hashfn.as_ref())?;
        log::debug!("index = {:?}", proof.index);
        self.add_input(bytemuck::cast_slice(&[BabyBearElem::new(
            proof.index as u32,
        )]));
        for digest in proof.digests {
            log::debug!("path = {:?}", digest);
            self.add_input_digest(&digest);
        }
        log::debug!(
            "root = {:?}",
            allowed_ids.calc_root(self.opts.suite.hashfn.as_ref())
        );
        Ok(())
    }

    /// TODO
    pub fn new_lift(seal: &[u32], opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let mut iop = ReadIOP::new(seal, opts.suite.rng.as_ref());
        iop.read_field_elem_slice::<BabyBearElem>(risc0_circuit_rv32im::CircuitImpl::OUTPUT_SIZE);
        let po2 = *iop.read_u32s(1).first().unwrap() as usize;

        let (program, control_id) = zkr::lift(po2)?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root);

        let which = po2 - MIN_CYCLES_PO2;
        let inner_control_id = Digest::from_hex(POSEIDON_CONTROL_ID[which]).unwrap();
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
        a.meta.encode(&mut data)?;
        let data_fp: Vec<BabyBearElem> = data.iter().map(|x| BabyBearElem::new(*x)).collect();
        self.add_input(bytemuck::cast_slice(&data_fp));
        Ok(())
    }

    /// TODO
    pub fn new_join(a: &SuccinctReceipt, b: &SuccinctReceipt, opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::join()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root);
        prover.add_segment_receipt(a, &allowed_ids)?;
        prover.add_segment_receipt(b, &allowed_ids)?;
        Ok(prover)
    }

    /// TODO
    pub fn new_identity(a: &SuccinctReceipt, opts: ProverOpts) -> Result<Self> {
        let hashfn = opts.suite.hashfn.as_ref();
        let allowed_ids = Self::make_allowed_tree();
        let merkle_root = allowed_ids.calc_root(hashfn);

        let (program, control_id) = zkr::identity()?;
        let mut prover = Prover::new(program, control_id, opts);

        prover.add_input_digest(&merkle_root);
        prover.add_segment_receipt(a, &allowed_ids)?;
        Ok(prover)
    }

    fn add_input(&mut self, input: &[u32]) {
        self.input.extend(input);
    }

    fn add_input_digest(&mut self, digest: &Digest) {
        self.add_input(digest.as_words())
    }

    /// TODO
    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<RecursionReceipt> {
        let hal_pair = poseidon_hal_pair();
        let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
        self.run_with_hal(hal, circuit_hal)
    }

    /// TODO
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

        adapter.execute(prover.iop());

        let seal = if skip_seal {
            Vec::new()
        } else {
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

            prover.finalize(&[&mix, &out], circuit_hal)
        };

        let output_elems: &[BabyBearElem] = bytemuck::cast_slice(&seal[..CircuitImpl::OUTPUT_SIZE]);

        const DIGEST_SHORTS: usize = DIGEST_WORDS * 2;
        assert_eq!(CircuitImpl::OUTPUT_SIZE, DIGEST_SHORTS * 2);

        let allowed_code = shorts_to_digest(&output_elems[0..DIGEST_SHORTS]);
        let output_digest = shorts_to_digest(&output_elems[DIGEST_SHORTS..2 * DIGEST_SHORTS]);

        Ok(RecursionReceipt {
            control_id: self.control_id,
            allowed_code,
            output_digest,
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
