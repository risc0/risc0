// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Prover implementation for the recursion VM.
//!
//! This module contains the recursion [Prover].

mod hal;
mod preflight;
mod program;
mod witgen;
pub mod zkr;

use std::{collections::VecDeque, fmt::Debug, rc::Rc};

use anyhow::Result;
use cfg_if::cfg_if;
use risc0_core::scope;
use risc0_zkp::{
    adapter::{CircuitInfo, PROOF_SYSTEM_INFO},
    core::digest::Digest,
    field::{
        Elem as _,
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    },
    hal::{Buffer, CircuitHal, Hal},
};
use serde::{Deserialize, Serialize};

use self::{
    hal::{CircuitAccumulator, CircuitWitnessGenerator},
    preflight::Preflight,
    witgen::WitnessGenerator,
};
use crate::{
    CircuitImpl, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA, taps::TAPSET,
};

pub use self::program::Program;

// TODO: Automatically generate this constant from the circuit somehow without
// messing up bootstrap dependencies.
/// Size of the code group in the taps of the recursion circuit.
const RECURSION_CODE_SIZE: usize = 23;

#[derive(Clone, Debug, Serialize, Deserialize)]
#[non_exhaustive]
pub struct RecursionReceipt {
    pub seal: Vec<u32>,
    pub output: Vec<u32>,
}

impl RecursionReceipt {
    /// Total number of bytes used by the seal of this receipt.
    pub fn seal_size(&self) -> usize {
        core::mem::size_of_val(self.seal.as_slice())
    }

    /// Allocates a [VecDeque] and copies the output stream into it for decoding.
    pub fn out_stream(&self) -> VecDeque<u32> {
        let mut vec: VecDeque<u32> = VecDeque::new();
        vec.extend(self.output.iter());
        vec
    }
}

pub trait RecursionProver {
    fn prove(&self, program: Program, input: VecDeque<u32>) -> Result<RecursionReceipt>;
}

pub fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
    cfg_if! {
        if #[cfg(feature = "dual")] {
            self::hal::dual::recursion_prover(hashfn)
        } else if #[cfg(feature = "cuda")] {
            self::hal::cuda::recursion_prover(hashfn)
        // } else if #[cfg(any(all(target_os = "macos", target_arch = "aarch64"), target_os = "ios"))] {
        // self::hal::metal::recursion_prover(hashfn)
        } else {
            self::hal::cpu::recursion_prover(hashfn)
        }
    }
}

/// Prover for the recursion circuit.
pub struct Prover {
    program: Program,
    hashfn: String,
    input: VecDeque<u32>,
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
    /// Creates a new prover with the given recursion program.
    pub fn new(program: Program, hashfn: &str) -> Self {
        Self {
            program,
            hashfn: hashfn.to_string(),
            input: VecDeque::new(),
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
        let prover = recursion_prover(&self.hashfn)?;
        prover.prove(self.program.clone(), self.input.clone())
    }
}

pub(crate) struct RecursionProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    hal: Rc<H>,
    circuit_hal: Rc<C>,
}

impl<H, C> RecursionProver for RecursionProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H> + CircuitAccumulator<H>,
{
    fn prove(&self, program: Program, input: VecDeque<u32>) -> Result<RecursionReceipt> {
        scope!("prove");

        let preflight = self.preflight(&program, input)?;

        let witgen = WitnessGenerator::new(
            self.hal.as_ref(),
            self.circuit_hal.as_ref(),
            &program,
            &preflight,
        )?;

        let global = &witgen.global;

        let seal = scope!("prove", {
            let mut prover = risc0_zkp::prove::Prover::new(self.hal.as_ref(), TAPSET);
            let hashfn = &self.hal.get_hash_suite().hashfn;

            let mix = scope!("main", {
                // At the start of the protocol, seed the Fiat-Shamir transcript with context information
                // about the proof system and circuit.
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

                // Concat globals and po2 into a vector.
                let global_len = global.size();
                let mut header = vec![BabyBearElem::ZERO; global_len + 1];
                global.view_mut(|view| {
                    for (i, elem) in view.iter_mut().enumerate() {
                        *elem = elem.valid_or_zero();
                        header[i] = *elem;
                    }
                    header[global_len] = BabyBearElem::new_raw(program.po2 as u32);
                });

                let header_digest = hashfn.hash_elem_slice(&header);
                prover.iop().commit(&header_digest);
                prover.iop().write_field_elem_slice(header.as_slice());
                prover.set_po2(program.po2);

                prover.commit_group(REGISTER_GROUP_CTRL, &witgen.ctrl);
                prover.commit_group(REGISTER_GROUP_DATA, &witgen.data);

                // Make the mixing values
                let mix: [BabyBearElem; CircuitImpl::MIX_SIZE] =
                    std::array::from_fn(|_| prover.iop().random_elem());

                let mix = witgen.accum(&self.hal, self.circuit_hal.as_ref(), &mix)?;

                prover.commit_group(REGISTER_GROUP_ACCUM, &witgen.accum);

                mix
            });

            prover.finalize(&[&mix, global], self.circuit_hal.as_ref())
        });

        Ok(RecursionReceipt {
            seal,
            output: preflight.output,
        })
    }
}

impl<H, C> RecursionProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    pub fn new(hal: Rc<H>, circuit_hal: Rc<C>) -> Self {
        Self { hal, circuit_hal }
    }

    fn preflight(&self, program: &Program, input: VecDeque<u32>) -> Result<Preflight> {
        scope!("preflight");

        let mut preflight = Preflight::new(input);
        for (cycle, row) in program.code_by_row().enumerate() {
            preflight.step(cycle, row)?
        }

        Ok(preflight)
    }
}
