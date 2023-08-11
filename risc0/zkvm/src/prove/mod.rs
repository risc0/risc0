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
//! use risc0_zkvm::{default_prover, ExecutorEnv};
//! use risc0_zkvm_methods::FIB_ELF;
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! let env = ExecutorEnv::builder().add_input(&[20]).build().unwrap();
//! let receipt = default_prover().prove_elf(env, FIB_ELF).unwrap();
//! # }
//! ```

#[cfg(not(feature = "disable-dev-mode"))]
mod dev_mode;
mod exec;
pub(crate) mod loader;
mod local;
mod plonk;
mod remote;
#[cfg(test)]
mod tests;

use std::{collections::HashMap, rc::Rc};

use anyhow::Result;
use risc0_binfmt::{MemoryImage, Program};
use risc0_circuit_rv32im::CircuitImpl;
use risc0_core::field::{
    baby_bear::{BabyBear, Elem, ExtElem},
    Elem as _,
};
use risc0_zkp::{
    adapter::CircuitInfo,
    core::digest::DIGEST_WORDS,
    hal::{EvalCheck, Hal},
};
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE, WORD_SIZE};

use self::{local::LocalProver, remote::RemoteProver};
use crate::{
    receipt::{Receipt, VerifierContext},
    ExecutorEnv, Segment, SegmentReceipt, Session,
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
        let hal = Rc::new(CpuHal::new(Sha256HashSuite::new_suite()));
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
        let hal = Rc::new(CpuHal::new(PoseidonHashSuite::new_suite()));
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

/// A Prover can execute a given [MemoryImage] and produce a [Receipt] that can
/// be used to verify correct computation.
pub trait Prover {
    /// Prove the specified [MemoryImage].
    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        image: MemoryImage,
    ) -> Result<Receipt>;

    /// Prove the specified ELF binary.
    fn prove_elf(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<Receipt> {
        self.prove_elf_with_ctx(env, &VerifierContext::default(), elf)
    }

    /// Prove the specified [MemoryImage] with the specified [VerifierContext].
    fn prove_elf_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
    ) -> Result<Receipt> {
        let program = Program::load_elf(elf, MEM_SIZE as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
        self.prove(env, ctx, image)
    }

    /// Prove the specified [Session].
    fn prove_session(&self, ctx: &VerifierContext, session: &Session) -> Result<Receipt>;

    /// Prove the specified [Segment].
    fn prove_segment(&self, ctx: &VerifierContext, segment: &Segment) -> Result<SegmentReceipt>;

    /// Return the peak memory usage that this [Prover] has experienced.
    fn get_peak_memory_usage(&self) -> usize;

    /// Return a name for this [Prover].
    fn get_name(&self) -> String;
}

fn provers() -> HashMap<String, Rc<dyn Prover>> {
    if cfg!(feature = "disable-dev-mode") && std::env::var("RISC0_DEV_MODE").is_ok() {
        panic!("zkVM: Inconsistent settings -- please resolve. \
                The RISC0_DEV_MODE environment variable is set but dev mode has been disabled by feature flag. \
                To produce valid proofs, unset the RISC0_DEV_MODE environment variable. \
                To enable dev mode and accept INSECURE, invalid proofs, remove the `disable-dev-mode` feature flag.")
    }
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
    #[cfg(not(feature = "disable-dev-mode"))]
    {
        let prover = Rc::new(dev_mode::DevModeProver::new("devmode"));
        table.insert("$devmode".to_string(), prover);
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
    if cfg!(not(feature = "disable-dev-mode")) && std::env::var("RISC0_DEV_MODE").is_ok() {
        eprintln!("WARNING: proving in dev mode. This will not generate valid, secure proofs.");
        if let Some(prover) = provers.get("$devmode") {
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
    pub fn prove(&self) -> Result<Receipt> {
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
