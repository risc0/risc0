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
//! use risc0_zkvm::{default_executor_from_elf, ExecutorEnv};
//! use risc0_zkvm_methods::FIB_ELF;
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
//! let mut exec = default_executor_from_elf(env, FIB_ELF).unwrap();
//! let session = exec.run().unwrap();
//! let receipt = session.prove().unwrap();
//! # }
//! ```

mod exec;
pub(crate) mod loader;
mod plonk;
#[cfg(test)]
mod tests;

use std::{collections::HashMap, rc::Rc, time::Duration};

use anyhow::{bail, Result};
use bonsai_sdk::alpha as bonsai_sdk;
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
    core::digest::DIGEST_WORDS,
    hal::{EvalCheck, Hal},
    layout::Buffer,
    prove::{adapter::ProveAdapter, executor::Executor},
};
use risc0_zkvm_platform::WORD_SIZE;

use self::{exec::MachineContext, loader::Loader};
use crate::{
    receipt::{InnerReceipt, SegmentReceipts, SessionReceipt, VerifierContext},
    Segment, SegmentReceipt, Session, CIRCUIT,
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
    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::{poseidon::PoseidonHashSuite, sha::Sha256HashSuite},
        hal::cpu::CpuHal,
    };

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
    pub fn sha256_hal_eval() -> HalEval<CpuHal<BabyBear>, CpuEvalCheck<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(Sha256HashSuite::new()));
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
    pub fn poseidon_hal_eval() -> HalEval<CpuHal<BabyBear>, CpuEvalCheck<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(PoseidonHashSuite::new()));
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
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<SessionReceipt>;

    /// TODO
    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt>;

    /// TODO
    fn get_peak_memory_usage(&self) -> usize;

    /// TODO
    fn get_name(&self) -> String;
}

/// An implementation of a [Prover] that runs proof workloads remotely.
pub struct RemoteProver {
    name: String,
}

impl RemoteProver {
    /// construct a remote prover. Unlike the [LocalProver], the hal is taken
    /// care of by the remote prover.
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for RemoteProver {
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn get_peak_memory_usage(&self) -> usize {
        0
    }

    fn prove_session(&self, _ctx: &VerifierContext, session: &Session) -> Result<SessionReceipt> {
        log::debug!("prove_session: {}", self.name);
        let client = bonsai_sdk::Client::from_env()?;

        let session = match &session.bonsai_session_id {
            Some(id) => bonsai_sdk::SessionId::new(id.clone()),
            None => bail!("Session does not have a bonsai session ID"),
        };

        loop {
            // The session has already been started in the executor. Poll bonsai to check if
            // the proof request succeeded.
            let res = session.status(&client)?;
            if res.status == "RUNNING" {
                std::thread::sleep(Duration::from_secs(5));
                continue;
            }
            if res.status == "SUCCEEDED" {
                // Download the receipt, containing the output
                let receipt_url = match res.receipt_url {
                    Some(url) => url,
                    None => bail!("API error, missing receipt on completed session"),
                };

                let receipt_buf = client.download(&receipt_url)?;
                let receipt: SessionReceipt = bincode::deserialize(&receipt_buf)?;
                return Ok(receipt);
            } else {
                bail!("Bonsai prover workflow exited: {}", res.status);
            }
        }
    }

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        bail!("this is unimplemented for prover [{}]", self.get_name())
    }
}

/// An implementation of a [Prover] that runs locally.
pub struct LocalProver<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
    E: EvalCheck<H>,
{
    name: String,
    hal_eval: HalEval<H, E>,
}

impl<H, E> LocalProver<H, E>
where
    H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
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
    E: EvalCheck<H>,
{
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn get_peak_memory_usage(&self) -> usize {
        self.hal_eval.hal.get_memory_usage()
    }

    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<SessionReceipt> {
        log::info!("prove_session: {}", self.name);
        let mut segments = Vec::new();
        for segment_ref in session.segments.iter() {
            let segment = segment_ref.resolve()?;
            for hook in &session.hooks {
                hook.on_pre_prove_segment(&segment);
            }
            segments.push(self.prove_segment(ctx, &segment)?);
            for hook in &session.hooks {
                hook.on_post_prove_segment(&segment);
            }
        }
        let inner = InnerReceipt::Flat(SegmentReceipts(segments));
        let receipt = SessionReceipt::new(inner, session.journal.clone());
        let image_id = session.segments[0].resolve()?.pre_image.compute_id();
        receipt.verify_with_context(ctx, image_id)?;
        Ok(receipt)
    }

    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt> {
        log::info!(
            "prove_segment[{}]: po2: {}, insn_cycles: {}",
            segment.index,
            segment.po2,
            segment.insn_cycles,
        );
        let (hal, eval) = (self.hal_eval.hal.as_ref(), &self.hal_eval.eval);
        let hashfn = &hal.get_hash_suite().name;

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
            hashfn: hashfn.clone(),
        };
        receipt.verify_with_context(ctx)?;

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

        let prover = Rc::new(RemoteProver::new("bonsai"));
        table.insert("$bonsai".to_string(), prover);
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
        #[cfg(feature = "dual")]
        {
            use risc0_zkp::hal::dual::{DualEvalCheck, DualHal};

            let lhs = cpu::sha256_hal_eval();
            let rhs = cuda::sha256_hal_eval();
            let dual = HalEval {
                hal: Rc::new(DualHal::new(lhs.hal, rhs.hal)),
                eval: Rc::new(DualEvalCheck::new(lhs.eval, rhs.eval)),
            };
            let prover = Rc::new(LocalProver::new("dual", dual));
            table.insert("$default".to_string(), prover);

            let lhs = cpu::poseidon_hal_eval();
            let rhs = cuda::poseidon_hal_eval();
            let dual = HalEval {
                hal: Rc::new(DualHal::new(lhs.hal, rhs.hal)),
                eval: Rc::new(DualEvalCheck::new(lhs.eval, rhs.eval)),
            };
            let prover = Rc::new(LocalProver::new("dual", dual));
            table.insert("$poseidon".to_string(), prover);
        }
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
        #[cfg(feature = "dual")]
        {
            use risc0_zkp::hal::dual::{DualEvalCheck, DualHal};

            let lhs = cpu::sha256_hal_eval();
            let rhs = metal::sha256_hal_eval();
            let dual = HalEval {
                hal: Rc::new(DualHal::new(lhs.hal, rhs.hal)),
                eval: Rc::new(DualEvalCheck::new(lhs.eval, rhs.eval)),
            };
            let prover = Rc::new(LocalProver::new("dual", dual));
            table.insert("$default".to_string(), prover);

            let lhs = cpu::poseidon_hal_eval();
            let rhs = metal::poseidon_hal_eval();
            let dual = HalEval {
                hal: Rc::new(DualHal::new(lhs.hal, rhs.hal)),
                eval: Rc::new(DualEvalCheck::new(lhs.eval, rhs.eval)),
            };
            let prover = Rc::new(LocalProver::new("dual", dual));
            table.insert("$poseidon".to_string(), prover);
        }
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
    if std::env::var("BONSAI_API_URL").is_ok() && std::env::var("BONSAI_API_KEY").is_ok() {
        if let Some(prover) = provers.get("$bonsai") {
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
    pub fn prove(&self) -> Result<SessionReceipt> {
        default_prover().prove_session(&VerifierContext::default(), self)
    }
}

impl Segment {
    /// Call the ZKP system to produce a [SegmentReceipt].
    pub fn prove(&self, ctx: &VerifierContext) -> Result<SegmentReceipt> {
        default_prover().prove_segment(ctx, self)
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
