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
//! use risc0_zkvm::{prove::default_hal, ControlId, Executor, ExecutorEnv, Session, SessionReceipt};
//! use risc0_zkvm_methods::FIB_ELF;
//!
//!
//! # #[cfg(not(feature = "cuda"))]
//! # {
//! let env = ExecutorEnv::builder().add_input(&[20]).build();
//! let mut exec = Executor::from_elf(env, FIB_ELF).unwrap();
//! let session = exec.run().unwrap();
//! let (hal, eval) = default_hal();
//! let receipt = session.prove(hal.as_ref(), &eval).unwrap();
//! # }
//! ```

mod exec;
pub(crate) mod loader;
mod plonk;
#[cfg(test)]
mod tests;

use anyhow::{anyhow, Result};
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
    prove::{adapter::ProveAdapter, executor::Executor, Prover},
    verify::CpuVerifyHal,
};
use risc0_zkvm_platform::WORD_SIZE;

use self::{exec::MachineContext, loader::Loader};
use crate::{ControlId, Segment, SegmentReceipt, Session, SessionReceipt, CIRCUIT};

/// HAL creation functions for CUDA.
#[cfg(feature = "cuda")]
pub mod cuda {
    use std::rc::Rc;

    use risc0_circuit_rv32im::cuda::{CudaEvalCheckPoseidon, CudaEvalCheckSha256};
    use risc0_zkp::hal::cuda::{CudaHalPoseidon, CudaHalSha256};

    /// Returns the default SHA-256 HAL for the rv32im circuit.
    pub fn default_hal() -> (Rc<CudaHalSha256>, CudaEvalCheckSha256) {
        let hal = Rc::new(CudaHalSha256::new());
        let eval = CudaEvalCheckSha256::new(hal.clone());
        (hal, eval)
    }

    /// Returns the default Poseidon HAL for the rv32im circuit.
    pub fn default_poseidon_hal() -> (Rc<CudaHalPoseidon>, CudaEvalCheckPoseidon) {
        let hal = Rc::new(CudaHalPoseidon::new());
        let eval = CudaEvalCheckPoseidon::new(hal.clone());
        (hal, eval)
    }
}

/// HAL creation functions for Metal.
#[cfg(feature = "metal")]
pub mod metal {
    use std::rc::Rc;

    use risc0_circuit_rv32im::metal::{MetalEvalCheck, MetalEvalCheckSha256};
    use risc0_zkp::hal::metal::{MetalHalPoseidon, MetalHalSha256, MetalHashPoseidon};

    /// Returns the default SHA-256 HAL for the rv32im circuit.
    pub fn default_hal() -> (Rc<MetalHalSha256>, MetalEvalCheckSha256) {
        let hal = Rc::new(MetalHalSha256::new());
        let eval = MetalEvalCheckSha256::new(hal.clone());
        (hal, eval)
    }

    /// Returns the default Poseidon HAL for the rv32im circuit.
    pub fn default_poseidon_hal() -> (Rc<MetalHalPoseidon>, MetalEvalCheck<MetalHashPoseidon>) {
        let hal = Rc::new(MetalHalPoseidon::new());
        let eval = MetalEvalCheck::<MetalHashPoseidon>::new(hal.clone());
        (hal, eval)
    }
}

/// HAL creation functions for the CPU.
pub mod cpu {
    use std::rc::Rc;

    use risc0_circuit_rv32im::{cpu::CpuEvalCheck, CircuitImpl};
    use risc0_zkp::hal::cpu::{BabyBearPoseidonCpuHal, BabyBearSha256CpuHal};

    use crate::CIRCUIT;

    /// Returns the default SHA-256 HAL for the rv32im circuit.
    ///
    /// RISC Zero uses a
    /// [HAL](https://docs.rs/risc0-zkp/latest/risc0_zkp/hal/index.html)
    /// (Hardware Abstraction Layer) to interface with the zkVM circuit.
    /// This function returns the default HAL for the selected `risc0-zkvm`
    /// features. It also returns the associated
    /// [EvalCheck](https://docs.rs/risc0-zkp/latest/risc0_zkp/hal/trait.EvalCheck.html)
    /// used for computing the cryptographic check polynomial.
    ///
    /// Note that this function will return different types when
    /// `risc0-zkvm` is built with features that select different the target
    /// hardware. The version documented here is used when no special
    /// hardware features are selected.
    pub fn default_hal() -> (Rc<BabyBearSha256CpuHal>, CpuEvalCheck<'static, CircuitImpl>) {
        let hal = Rc::new(BabyBearSha256CpuHal::new());
        let eval = CpuEvalCheck::new(&CIRCUIT);
        (hal, eval)
    }

    /// Returns the default Poseidon HAL for the rv32im circuit.
    ///
    /// The same as [default_hal] except it gives the default HAL for
    /// securing the circuit using Poseidon (instead of SHA-256).
    pub fn default_poseidon_hal() -> (
        Rc<BabyBearPoseidonCpuHal>,
        CpuEvalCheck<'static, CircuitImpl>,
    ) {
        let hal = Rc::new(BabyBearPoseidonCpuHal::new());
        let eval = CpuEvalCheck::new(&CIRCUIT);
        (hal, eval)
    }
}

cfg_if::cfg_if! {
    if #[cfg(feature = "cuda")] {
        pub use cuda::{default_hal, default_poseidon_hal};
    } else if #[cfg(feature = "metal")] {
        pub use metal::{default_hal, default_poseidon_hal};
    } else {
        pub use cpu::{default_hal, default_poseidon_hal};
    }
}

impl Session {
    /// For each segment, call [Segment::prove] and collect the receipts.
    pub fn prove<H, E>(&self, hal: &H, eval: &E) -> Result<SessionReceipt>
    where
        H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
        <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
        E: EvalCheck<H>,
    {
        let mut segments = Vec::new();
        for segment in self.segments.iter() {
            segments.push(segment.prove(hal, eval)?);
        }
        let receipt = SessionReceipt {
            segments,
            journal: self.journal.clone(),
        };
        let image_id = self.segments[0].pre_image.get_root();
        let hal = CpuVerifyHal::<_, H::HashSuite, _>::new(&crate::CIRCUIT);
        receipt
            .verify_with_hal(&hal, image_id)
            .map_err(|err| anyhow!("Verification error: {err}"))?;
        Ok(receipt)
    }
}

impl Segment {
    /// Call the ZKP system to produce a [SegmentReceipt].
    pub fn prove<H, E>(&self, hal: &H, eval: &E) -> Result<SegmentReceipt>
    where
        H: Hal<Field = BabyBear, Elem = Elem, ExtElem = ExtElem>,
        <<H as Hal>::HashSuite as HashSuite<BabyBear>>::HashFn: ControlId,
        E: EvalCheck<H>,
    {
        let io = self.prepare_globals();
        let machine = MachineContext::new(&self);
        let mut executor = Executor::new(&CIRCUIT, machine, self.po2, self.po2, &io);

        let loader = Loader::new();
        loader.load(|chunk, fini| executor.step(chunk, fini))?;
        executor.finalize();

        let mut adapter = ProveAdapter::new(&mut executor);
        let mut prover = Prover::new(hal, CIRCUIT.get_taps());

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

        let seal = prover.finalize(&[&mix, &out], eval);

        let receipt = SegmentReceipt { seal };
        let hal = CpuVerifyHal::<_, H::HashSuite, _>::new(&crate::CIRCUIT);
        receipt
            .verify_with_hal(&hal)
            .map_err(|err| anyhow!("Verification error: {err}"))?;

        Ok(receipt)
    }

    fn prepare_globals(&self) -> Vec<Elem> {
        let mut io = vec![Elem::INVALID; CircuitImpl::OUTPUT_SIZE];
        log::debug!("run> pc: 0x{:08x}", self.pc);

        // initialize PC
        let pc_bytes = self.pc.to_le_bytes();
        for i in 0..WORD_SIZE {
            io[i] = (pc_bytes[i] as u32).into();
        }

        // initialize ImageID
        let image_id = self.pre_image.get_root();
        let image_id = image_id.as_words();
        for i in 0..DIGEST_WORDS {
            let bytes = image_id[i].to_le_bytes();
            for j in 0..WORD_SIZE {
                io[(i + 1) * WORD_SIZE + j] = (bytes[j] as u32).into();
            }
        }

        io
    }
}
