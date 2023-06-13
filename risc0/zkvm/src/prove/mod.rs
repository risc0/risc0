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

//! Run the zkVM guest and prove its results.
//!
//! # Usage
//! The primary use of this module is to provably run a zkVM guest by use of a
//! [Session]. See the [Session] documentation for more detailed usage
//! information.
//!
//! ```rust
//! use risc0_zkvm::{Executor, ExecutorEnv};
//! use risc0_zkvm_methods::FIB_ELF;
//!
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
//! let mut exec = Executor::from_elf(env, FIB_ELF).unwrap();
//! let session = exec.run().unwrap();
//! let receipt = session.prove().unwrap();
//! # }
//! ```

mod exec;
pub(crate) mod loader;
mod plonk;
#[cfg(test)]
mod tests;

use std::{collections::HashMap, rc::Rc};

use anyhow::Result;
use risc0_circuit_rv32im::{
    layout::{OutBuffer, LAYOUT},
    CircuitImpl, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};
use risc0_core::field::{
    baby_bear::{BabyBear, Elem, ExtElem},
    Elem as _,
};
use risc0_zkp::{
    adapter::{CircuitInfo, TapsProvider},
    core::{digest::DIGEST_WORDS, hash::HashSuite},
    hal::{EvalCheck, Hal},
    layout::Buffer,
    prove::{adapter::ProveAdapter, executor::Executor},
    verify::CpuVerifyHal,
};
use risc0_zkvm_platform::WORD_SIZE;

use self::{exec::MachineContext, loader::Loader};
use crate::{
    receipt::SessionReceipt, ControlId, Segment, SegmentReceipt, Session, SessionFlatReceipt,
    CIRCUIT,
};

/// HAL creation functions for CUDA.
#[cfg(feature = "cuda")]
pub mod cuda {
    use std::rc::Rc;

    use risc0_circuit_rv32im::cuda::{CudaEvalCheckPoseidon, CudaEvalCheckSha256};
    use risc0_zkp::hal::cuda::{CudaHalPoseidon, CudaHalSha256};

    use super::HalEval;

    /// Creates a HAL for the rv32im circuit that uses the SHA-256 hashing
    /// function.
    pub fn sha256_hal_eval() -> HalEval<CudaHalSha256, CudaEvalCheckSha256> {
        let hal = Rc::new(CudaHalSha256::new());
        let eval = Rc::new(CudaEvalCheckSha256::new(hal.clone()));
        HalEval { hal, eval }
    }

    /// Creates a HAL for the rv32im circuit that uses the Poseidon hashing
    /// function.
    pub fn poseidon_hal_eval() -> HalEval<CudaHalPoseidon, CudaEvalCheckPoseidon> {
        let hal = Rc::new(CudaHalPoseidon::new());
        let eval = Rc::new(CudaEvalCheckPoseidon::new(hal.clone()));
        HalEval { hal, eval }
    }
}

/// HAL creation functions for Metal.
#[cfg(feature = "metal")]
pub mod metal {
    use std::rc::Rc;

    use risc0_circuit_rv32im::metal::{MetalEvalCheck, MetalEvalCheckSha256};
    use risc0_zkp::hal::metal::{MetalHalPoseidon, MetalHalSha256, MetalHashPoseidon};

    use super::HalEval;

    /// Creates a HAL for the rv32im circuit that uses the SHA-256 hashing
    /// function.
    pub fn sha256_hal_eval() -> HalEval<MetalHalSha256, MetalEvalCheckSha256> {
        let hal = Rc::new(MetalHalSha256::new());
        let eval = Rc::new(MetalEvalCheckSha256::new(hal.clone()));
        HalEval { hal, eval }
    }

    /// Creates a HAL for the rv32im circuit that uses the Poseidon hashing
    /// function.
    pub fn poseidon_hal_eval() -> HalEval<MetalHalPoseidon, MetalEvalCheck<MetalHashPoseidon>> {
        let hal = Rc::new(MetalHalPoseidon::new());
        let eval = Rc::new(MetalEvalCheck::<MetalHashPoseidon>::new(hal.clone()));
        HalEval { hal, eval }
    }
}

/// HAL creation functions for the CPU.
pub mod cpu {
    use std::rc::Rc;

    use risc0_circuit_rv32im::{cpu::CpuEvalCheck, CircuitImpl};
    use risc0_zkp::hal::cpu::{BabyBearPoseidonCpuHal, BabyBearSha256CpuHal};

    use super::HalEval;
    use crate::CIRCUIT;

    /// Creates a HAL for the rv32im circuit that uses the SHA-256 hashing
    /// function.
    ///
    /// The zkVM uses a
    /// [HAL](https://docs.rs/risc0-zkp/latest/risc0_zkp/hal/index.html)
    /// (Hardware Abstraction Layer) to accelerate computationally intensive
    /// operations. This function returns a HAL implementation that makes use of
    /// multi-core CPUs.
    pub fn sha256_hal_eval() -> HalEval<BabyBearSha256CpuHal, CpuEvalCheck<'static, CircuitImpl>> {
        let hal = Rc::new(BabyBearSha256CpuHal::new());
        let eval = Rc::new(CpuEvalCheck::new(&CIRCUIT));
        HalEval { hal, eval }
    }

    /// Creates a HAL for the rv32im circuit that uses the Poseidon hashing
    /// function.
    ///
    /// The zkVM uses a
    /// [HAL](https://docs.rs/risc0-zkp/latest/risc0_zkp/hal/index.html)
    /// (Hardware Abstraction Layer) to accelerate computationally intensive
    /// operations. This function returns a HAL implementation that makes use of
    /// multi-core CPUs.
    pub fn poseidon_hal_eval() -> HalEval<BabyBearPoseidonCpuHal, CpuEvalCheck<'static, CircuitImpl>>
    {
        let hal = Rc::new(BabyBearPoseidonCpuHal::new());
        let eval = Rc::new(CpuEvalCheck::new(&CIRCUIT));
        HalEval { hal, eval }
    }
}

/// A pair of [Hal] and [EvalCheck].
#[derive(Clone)]
pub struct HalEval<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    E: EvalCheck<H>,
{
    /// A [Hal] implementation.
    pub hal: Rc<H>,

    /// An [EvalCheck] implementation.
    pub eval: Rc<E>,
}

/// TODO
pub trait Prover {
    /// TODO
    fn prove_session(&self, session: &Session) -> Result<Box<dyn SessionReceipt>>;

    /// TODO
    fn prove_segment(&self, segment: &Segment) -> Result<SegmentReceipt>;

    /// TODO
    fn get_peak_memory_usage(&self) -> usize;

    /// TODO
    fn get_name(&self) -> String;
}

/// An implementation of a [Prover] that runs locally.
pub struct LocalProver<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    name: String,
    hal_eval: HalEval<H, E>,
}

impl<H, E> LocalProver<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    /// Construct a [LocalProver] with the given name and [HalEval].
    pub fn new(name: &str, hal_eval: HalEval<H, E>) -> Self {
        Self {
            name: name.to_string(),
            hal_eval,
        }
    }
}

impl<H, E> Prover for LocalProver<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
    E: EvalCheck<H>,
{
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn get_peak_memory_usage(&self) -> usize {
        self.hal_eval.hal.get_memory_usage()
    }

    fn prove_session(&self, session: &Session) -> Result<Box<dyn SessionReceipt>> {
        log::info!("prove_session: {}", self.name);
        let mut segments = Vec::new();
        for segment_ref in session.segments.iter() {
            let segment = segment_ref.resolve()?;
            segments.push(self.prove_segment(&segment)?);
        }
        let receipt = SessionFlatReceipt {
            segments,
            journal: session.journal.clone(),
        };
        let image_id = session.segments[0].resolve()?.pre_image.compute_id();
        let hal = CpuVerifyHal::<_, H::HashSuite, _>::new(&crate::CIRCUIT);
        receipt.verify_with_hal(&hal, image_id)?;
        Ok(Box::new(receipt))
    }

    fn prove_segment(&self, segment: &Segment) -> Result<SegmentReceipt> {
        log::info!(
            "prove_segment[{}]: po2: {}, insn_cycles: {}",
            segment.index,
            segment.po2,
            segment.insn_cycles,
        );
        let (hal, eval) = (self.hal_eval.hal.as_ref(), &self.hal_eval.eval);

        let io = segment.prepare_globals();
        let machine = MachineContext::new(segment);
        let mut executor = Executor::new(&CIRCUIT, machine, segment.po2, segment.po2, &io);

        let loader = Loader::new();
        loader.load(|chunk, fini| executor.step(chunk, fini))?;
        executor.finalize();

        let mut adapter = ProveAdapter::new(&mut executor);
        let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());

        adapter.execute(prover.iop());

        prover.set_po2(adapter.po2() as usize);

        prover.commit_group(
            REGISTER_GROUP_CODE,
            hal.copy_from_elem("code", &adapter.get_code().as_slice()),
        );
        prover.commit_group(
            REGISTER_GROUP_DATA,
            hal.copy_from_elem("data", &adapter.get_data().as_slice()),
        );
        adapter.accumulate(prover.iop());
        prover.commit_group(
            REGISTER_GROUP_ACCUM,
            hal.copy_from_elem("accum", &adapter.get_accum().as_slice()),
        );

        let mix = hal.copy_from_elem("mix", &adapter.get_mix().as_slice());
        let out_slice = &adapter.get_io().as_slice();

        log::debug!("Globals: {:?}", OutBuffer(out_slice).tree(&LAYOUT));
        let out = hal.copy_from_elem("out", &adapter.get_io().as_slice());

        let seal = prover.finalize(&[&mix, &out], eval.as_ref());

        let receipt = SegmentReceipt {
            seal,
            index: segment.index,
        };
        let hal = CpuVerifyHal::<_, H::HashSuite, _>::new(&crate::CIRCUIT);
        receipt.verify_with_hal(&hal)?;

        Ok(receipt)
    }
}

fn provers() -> HashMap<String, Rc<dyn Prover>> {
    let mut table: HashMap<String, Rc<dyn Prover>> = HashMap::new();
    {
        let prover = Rc::new(LocalProver::new("cpu", cpu::sha256_hal_eval()));
        table.insert("cpu".to_string(), prover.clone());
        table.insert("$default".to_string(), prover);

        let prover = Rc::new(LocalProver::new("cpu:poseidon", cpu::poseidon_hal_eval()));
        table.insert("cpu:poseidon".to_string(), prover.clone());
        table.insert("$poseidon".to_string(), prover);
    }
    #[cfg(feature = "cuda")]
    {
        let prover = Rc::new(LocalProver::new("cuda", cuda::sha256_hal_eval()));
        table.insert("cuda".to_string(), prover.clone());
        table.insert("$gpu".to_string(), prover.clone());
        table.insert("$default".to_string(), prover);

        let prover = Rc::new(LocalProver::new("cuda:poseidon", cuda::poseidon_hal_eval()));
        table.insert("cuda:poseidon".to_string(), prover.clone());
        table.insert("$poseidon".to_string(), prover);
    }
    #[cfg(feature = "metal")]
    {
        let prover = Rc::new(LocalProver::new("metal", metal::sha256_hal_eval()));
        table.insert("metal".to_string(), prover.clone());
        table.insert("$gpu".to_string(), prover.clone());
        table.insert("$default".to_string(), prover);

        let prover = Rc::new(LocalProver::new(
            "metal:poseidon",
            metal::poseidon_hal_eval(),
        ));
        table.insert("metal:poseidon".to_string(), prover.clone());
        table.insert("$poseidon".to_string(), prover);
    }
    table
}

/// Return a default [Prover] based on environment variables, falling back to a
/// default CPU-based prover.
pub fn default_prover() -> Rc<dyn Prover> {
    let provers = provers();
    if let Ok(requested) = std::env::var("RISC0_PROVER") {
        if let Some(prover) = provers.get(&requested) {
            return prover.clone();
        }
    }
    if let Some(prover) = provers.get("$default") {
        return prover.clone();
    }
    provers.get("cpu").unwrap().clone()
}

/// Return a [Prover] registered by with specified `name`.
pub fn get_prover(name: &str) -> Rc<dyn Prover> {
    provers().get(name).unwrap().clone()
}

impl Session {
    /// For each segment, call [Segment::prove] and collect the receipts.
    pub fn prove(&self) -> Result<Box<dyn SessionReceipt>> {
        default_prover().prove_session(self)
    }
}

impl Segment {
    /// Call the ZKP system to produce a [SegmentReceipt].
    pub fn prove(&self) -> Result<SegmentReceipt> {
        default_prover().prove_segment(self)
    }

    fn prepare_globals(&self) -> Vec<Elem> {
        let mut io = vec![Elem::INVALID; CircuitImpl::OUTPUT_SIZE];
        log::debug!("run> pc: 0x{:08x}", self.pre_image.pc);

        // initialize Input
        let mut offset = 0;
        for i in 0..DIGEST_WORDS * WORD_SIZE {
            io[offset + i] = Elem::ZERO;
        }
        offset += DIGEST_WORDS * WORD_SIZE;

        // initialize PC
        let pc_bytes = self.pre_image.pc.to_le_bytes();
        for i in 0..WORD_SIZE {
            io[offset + i] = (pc_bytes[i] as u32).into();
        }
        offset += WORD_SIZE;

        // initialize ImageID
        let merkle_root = self.pre_image.compute_root_hash();
        let merkle_root = merkle_root.as_words();
        for i in 0..DIGEST_WORDS {
            let bytes = merkle_root[i].to_le_bytes();
            for j in 0..WORD_SIZE {
                io[offset + i * WORD_SIZE + j] = (bytes[j] as u32).into();
            }
        }

        io
    }
}
