// Copyright 2025 RISC Zero, Inc.
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

pub(crate) mod cpu;
#[cfg(feature = "cuda")]
pub(crate) mod cuda;

use std::rc::Rc;

use anyhow::Result;
use risc0_core::scope;
use risc0_zkp::{
    adapter::{CircuitInfo as _, PROOF_SYSTEM_INFO},
    field::Elem as _,
    hal::{Buffer, CircuitHal, Hal},
    prove::Prover,
};

use super::{
    witgen::{preflight::PreflightTrace, PreflightResults, WitnessGenerator},
    Seal, SegmentProver,
};
use crate::{
    execute::segment::Segment,
    zirgen::{
        circuit::{
            CircuitField, ExtVal, Val, REGCOUNT_MIX, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE,
            REGISTER_GROUP_DATA,
        },
        taps::TAPSET,
        CircuitImpl,
    },
    RV32IM_SEAL_VERSION,
};

pub(crate) struct MetaBuffer<H: Hal> {
    pub buf: H::Buffer<H::Elem>,
    pub rows: usize,
    pub cols: usize,
    pub checked: bool,
}

impl<H> MetaBuffer<H>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
{
    pub fn new(name: &'static str, hal: &H, rows: usize, cols: usize, checked: bool) -> Self {
        let buf = hal.alloc_elem_init(name, rows * cols, Val::INVALID);
        Self {
            buf,
            rows,
            cols,
            checked,
        }
    }

    #[cfg(test)]
    pub fn to_vec(&self) -> Vec<Val> {
        self.buf.to_vec()
    }
}

#[allow(dead_code)]
#[derive(Clone, Copy, PartialEq)]
pub(crate) enum StepMode {
    Parallel,
    SeqForward,
    SeqReverse,
}

pub(crate) trait CircuitWitnessGenerator<H: Hal> {
    fn generate_witness(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace,
        global: &MetaBuffer<H>,
        data: &MetaBuffer<H>,
    ) -> Result<()>;
}

pub(crate) trait CircuitAccumulator<H: Hal> {
    fn step_accum(
        &self,
        preflight: &PreflightTrace,
        data: &MetaBuffer<H>,
        accum: &MetaBuffer<H>,
        global: &MetaBuffer<H>,
        mix: &MetaBuffer<H>,
    ) -> Result<()>;
}

pub(crate) struct SegmentProverImpl<H, C>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    hal: Rc<H>,
    circuit_hal: Rc<C>,
}

impl<H, C> SegmentProverImpl<H, C>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    pub fn new(hal: Rc<H>, circuit_hal: Rc<C>) -> Self {
        Self { hal, circuit_hal }
    }
}

impl<H, C> SegmentProver for SegmentProverImpl<H, C>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H> + CircuitAccumulator<H>,
{
    fn preflight(&self, segment: &Segment) -> Result<PreflightResults> {
        scope!("preflight");

        cfg_if::cfg_if! {
            if #[cfg(feature = "witgen_debug")] {
                let rand_z = ExtVal::ONE;
            } else {
                let mut rng = rand::rng();
                let rand_z = ExtVal::random(&mut rng);
            }
        }
        PreflightResults::new(segment, rand_z)
    }

    fn prove_core(&self, preflight_results: PreflightResults) -> Result<Seal> {
        scope!("prove_core");

        cfg_if::cfg_if! {
            if #[cfg(feature = "witgen_debug")] {
                let mode = if std::env::var_os("RISC0_WITGEN_DEBUG").is_some() {
                    StepMode::SeqForward
                } else {
                    StepMode::Parallel
                };
            } else {
                let mode = StepMode::Parallel;
            }
        }

        let po2 = preflight_results.po2;
        let witgen = WitnessGenerator::new(
            self.hal.as_ref(),
            self.circuit_hal.as_ref(),
            preflight_results,
            mode,
        )?;

        let code = &witgen.code.buf;
        let data = &witgen.data.buf;
        let global = &witgen.global.buf;

        Ok(scope!("prove_inner", {
            tracing::debug!("prove_inner");

            let mut prover = Prover::new(self.hal.as_ref(), TAPSET);
            let hashfn = &self.hal.get_hash_suite().hashfn;

            // Add a version tag to the start of the seal. It's not intended for
            // this value to be consumed by downstream lift predicates. Instead
            // it's meant to be a header which can be used by future versions in
            // case we'd like to adjust the encoding of the seal.
            //
            // We write via the IOP to avoid having to prepend a value to an
            // already allocated vector.
            prover.iop().write_u32_slice(&[RV32IM_SEAL_VERSION]);

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
                let mut header = vec![Val::ZERO; global_len + 1];
                global.view_mut(|view| {
                    for (i, elem) in view.iter_mut().enumerate() {
                        *elem = elem.valid_or_zero();
                        header[i] = *elem;
                    }
                    header[global_len] = Val::new_raw(po2);
                });

                let header_digest = hashfn.hash_elem_slice(&header);
                prover.iop().commit(&header_digest);
                prover.iop().write_field_elem_slice(header.as_slice());
                prover.set_po2(po2 as usize);

                prover.commit_group(REGISTER_GROUP_CODE, code);
                prover.commit_group(REGISTER_GROUP_DATA, data);

                // Make the mixing values
                let mix: [Val; REGCOUNT_MIX] = std::array::from_fn(|_| prover.iop().random_elem());

                let mix = witgen.accum(self.hal.as_ref(), self.circuit_hal.as_ref(), &mix)?;

                prover.commit_group(REGISTER_GROUP_ACCUM, &witgen.accum.buf);

                mix
            });

            prover.finalize(&[&mix.buf, global], self.circuit_hal.as_ref())
        }))
    }
}
