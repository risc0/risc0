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

//! Prover implementation for the recursion VM.
//!
//! This module contains the recursion [Prover].

mod exec;
mod plonk;
mod preflight;
mod program;
pub mod zkr;

use std::{collections::VecDeque, fmt::Debug, mem::take, rc::Rc};

use crate::{
    cpu::CpuCircuitHal, CircuitImpl, CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL,
    REGISTER_GROUP_DATA,
};
use anyhow::{bail, Result};
use rand::thread_rng;
use risc0_core::scope;
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStepContext, TapsProvider, PROOF_SYSTEM_INFO},
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem,
    },
    hal::{cpu::CpuHal, CircuitHal, Hal},
    prove::adapter::ProveAdapter,
    ZK_CYCLES,
};
use serde::{Deserialize, Serialize};

use self::exec::RecursionExecutor;
pub use self::program::Program;

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

// TODO: Automatically generate this constant from the circuit somehow without
// messing up bootstrap dependencies.
/// Size of the code group in the taps of the recursion circuit.
const RECURSION_CODE_SIZE: usize = 23;

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct RecursionReceipt {
    pub seal: Vec<u32>,
    pub output: Vec<u32>,
}

impl RecursionReceipt {
    /// Total number of bytes used by the seal of this receipt.
    pub fn seal_size(&self) -> usize {
        core::mem::size_of_val(self.seal.as_slice())
    }
}

/// Prover for the recursion circuit.
pub struct Prover {
    program: Program,
    hashfn: String,
    input: VecDeque<u32>,
    split_points: Vec<usize>,
    output: Vec<u32>,
}

#[cfg(feature = "cuda")]
mod cuda {
    pub use crate::cuda::{CudaCircuitHalPoseidon2, CudaCircuitHalSha256};
    pub use risc0_zkp::hal::cuda::{CudaHalPoseidon2, CudaHalSha256};

    use super::{HalPair, Rc};

    pub fn sha256_hal_pair() -> HalPair<CudaHalSha256, CudaCircuitHalSha256> {
        let hal = Rc::new(CudaHalSha256::new());
        let circuit_hal = Rc::new(CudaCircuitHalSha256::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }

    pub fn poseidon2_hal_pair() -> HalPair<CudaHalPoseidon2, CudaCircuitHalPoseidon2> {
        let hal = Rc::new(CudaHalPoseidon2::new());
        let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
        HalPair { hal, circuit_hal }
    }
}

#[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))]
mod metal {
    pub use crate::metal::MetalCircuitHal;
    pub use risc0_zkp::hal::metal::{
        MetalHalPoseidon2, MetalHalSha256, MetalHashPoseidon2, MetalHashSha256,
    };

    use super::{HalPair, Rc};

    pub fn sha256_hal_pair() -> HalPair<MetalHalSha256, MetalCircuitHal<MetalHashSha256>> {
        let hal = Rc::new(MetalHalSha256::new());
        let circuit_hal = Rc::new(MetalCircuitHal::<MetalHashSha256>::new(hal.clone()));
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
        BabyBear, CircuitImpl, CpuCircuitHal, CpuHal, HalPair, Poseidon2HashSuite, Rc, CIRCUIT,
    };

    #[allow(dead_code)]
    pub fn sha256_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
        let hal = Rc::new(CpuHal::new(Sha256HashSuite::new_suite()));
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
        pub fn poseidon2_hal_pair() -> HalPair<cuda::CudaHalPoseidon2, cuda::CudaCircuitHalPoseidon2> {
            cuda::poseidon2_hal_pair()
        }

        /// TODO
        #[allow(dead_code)]
        pub fn poseidon254_hal_pair() -> HalPair<CpuHal<BabyBear>, CpuCircuitHal<'static, CircuitImpl>> {
            cpu::poseidon254_hal_pair()
        }
    } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
        /// TODO
        #[allow(dead_code)]
        pub fn sha256_hal_pair() -> HalPair<metal::MetalHalSha256, metal::MetalCircuitHal<metal::MetalHashSha256>> {
            metal::sha256_hal_pair()
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
#[non_exhaustive]
pub enum DigestKind {
    Poseidon2,
    Sha256,
}

impl Prover {
    /// Creates a new prover with the given recursion program.  This
    /// is a low-level interface; for the zkVM, prefer to use
    /// risc0_zkvm::host::recursion::prove::Prover.
    pub fn new(program: Program, hashfn: &str) -> Self {
        Self {
            program,
            hashfn: hashfn.to_string(),
            input: VecDeque::new(),
            split_points: Vec::new(),
            output: Vec::new(),
        }
    }

    /// Add a set of u32s to the input for the recursion program.
    pub fn add_input(&mut self, input: &[u32]) {
        self.input.extend(input);
    }

    /// Add a digest to the input for the recursion program.
    pub fn add_input_digest(&mut self, digest: &Digest, kind: DigestKind) {
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
    pub fn run(&mut self) -> Result<RecursionReceipt> {
        // NOTE: Code is repeated across match arms to satisfy generics.
        match self.hashfn.as_ref() {
            "poseidon2" => {
                let hal_pair = poseidon2_hal_pair();
                let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
                self.run_with_hal(hal, circuit_hal)
            }
            "poseidon_254" => {
                let hal_pair = poseidon254_hal_pair();
                let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
                self.run_with_hal(hal, circuit_hal)
            }
            "sha-256" => {
                let hal_pair = sha256_hal_pair();
                let (hal, circuit_hal) = (hal_pair.hal.as_ref(), hal_pair.circuit_hal.as_ref());
                self.run_with_hal(hal, circuit_hal)
            }
            _ => bail!("no hal found for {}", self.hashfn),
        }
    }

    /// Run the prover, producing a receipt of execution for the recursion circuit over the loaded
    /// program and input, using the specified HAL.
    pub fn run_with_hal<H, C>(&mut self, hal: &H, circuit_hal: &C) -> Result<RecursionReceipt>
    where
        H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
        C: CircuitHal<H>,
    {
        scope!("run_with_hal");

        let machine_ctx = self.preflight()?;

        let split_points = core::mem::take(&mut self.split_points);

        let mut executor = scope!("witgen", {
            let mut executor =
                RecursionExecutor::new(&CIRCUIT, &self.program, machine_ctx, split_points);
            executor.run()?;
            Result::<RecursionExecutor, anyhow::Error>::Ok(executor)
        })?;

        let seal = scope!("prove", {
            let mut adapter = ProveAdapter::new(&mut executor.executor);
            let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());
            let hashfn = Rc::clone(&hal.get_hash_suite().hashfn);

            let (mix, io) = scope!("main", {
                // At the start of the protocol, seed the Fiat-Shamir transcript with context information
                // about the proof system and circuit.
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

                adapter.execute(prover.iop(), hal);

                prover.set_po2(adapter.po2() as usize);

                let ctrl = hal.copy_from_elem("ctrl", &adapter.get_code().as_slice());
                prover.commit_group(REGISTER_GROUP_CTRL, &ctrl);

                let data = hal.copy_from_elem("data", &adapter.get_data().as_slice());
                prover.commit_group(REGISTER_GROUP_DATA, &data);

                // Make the mixing values
                let mix = scope!("alloc+copy(mix)", {
                    let mix: Vec<_> = (0..CircuitImpl::MIX_SIZE)
                        .map(|_| prover.iop().random_elem())
                        .collect();
                    hal.copy_from_elem("mix", mix.as_slice())
                });

                let steps = adapter.get_steps();

                let accum = scope!(
                    "alloc(accum)",
                    hal.alloc_elem_init(
                        "accum",
                        steps * CIRCUIT.accum_size(),
                        BabyBearElem::INVALID,
                    )
                );

                // Add random noise to end of accum
                scope!("noise(accum)", {
                    let mut rng = thread_rng();
                    let noise =
                        vec![BabyBearElem::random(&mut rng); ZK_CYCLES * CIRCUIT.accum_size()];
                    hal.eltwise_copy_elem_slice(
                        &accum,
                        &noise,
                        CIRCUIT.accum_size(), // from_rows
                        ZK_CYCLES,            // from_cols
                        0,                    // from_offset
                        ZK_CYCLES,            // from_stride
                        steps - ZK_CYCLES,    // into_offset
                        steps,                // into_stride
                    );
                });

                let io = scope!(
                    "copy(io)",
                    hal.copy_from_elem("io", &adapter.get_io().as_slice())
                );

                circuit_hal.accumulate(&ctrl, &io, &data, &mix, &accum, steps);

                prover.commit_group(REGISTER_GROUP_ACCUM, &accum);

                (mix, io)
            });

            prover.finalize(&[&mix, &io], circuit_hal)
        });

        Ok(RecursionReceipt {
            seal,
            output: self.output.clone(),
        })
    }

    fn preflight(&mut self) -> Result<exec::MachineContext> {
        scope!("preflight");

        let mut machine = exec::MachineContext::new(take(&mut self.input));
        let mut preflight = preflight::Preflight::new(&mut machine);
        let size = (1 << self.program.po2) - ZK_CYCLES;

        for (cycle, row) in self.program.code_by_row().enumerate() {
            let ctx = CircuitStepContext { cycle, size };

            preflight.set_top(&ctx, row)?
        }

        // TODO: is this necessary?
        let zero_row = vec![BabyBearElem::ZERO; self.program.code_size];
        for cycle in self.program.code_rows()..size {
            let ctx = CircuitStepContext { cycle, size };

            preflight.set_top(&ctx, &zero_row)?
        }

        self.split_points = preflight.split_points;
        self.split_points.push(size);
        self.output = preflight.output;
        (machine.iop_reads, machine.byte_reads) = (preflight.iop_reads, preflight.byte_reads);
        Ok(machine)
    }
}
