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

pub mod loader;
pub mod machine;
#[cfg(test)]
mod tests;
pub mod witgen;

use std::rc::Rc;

use anyhow::Result;
use rand::thread_rng;
use risc0_zkp::{
    adapter::{CircuitInfo, TapsProvider, PROOF_SYSTEM_INFO},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem as _,
    },
    hal::{Buffer as _, CircuitHal, Hal},
    prove::Prover,
    ZK_CYCLES,
};

use self::witgen::WitnessGenerator;
use super::{hal::CircuitWitnessGenerator, segment::Segment, Seal, SegmentProver};
use crate::{
    prove::hal::StepMode, CircuitImpl, CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL,
    REGISTER_GROUP_DATA,
};

pub(crate) struct SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    hal: Rc<H>,
    circuit_hal: Rc<C>,
}

impl<H, C> SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    pub fn new(hal: Rc<H>, circuit_hal: Rc<C>) -> Self {
        Self { hal, circuit_hal }
    }
}

impl<H, C> SegmentProver for SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
{
    #[tracing::instrument(skip_all)]
    fn prove_segment(&self, segment: &Segment) -> Result<Seal> {
        nvtx::range_push!("prove_segment");

        nvtx::range_push!("preflight");
        let trace = segment.preflight()?;
        nvtx::range_pop!();

        nvtx::range_push!("prepare_globals");
        let io = segment.prepare_globals();
        nvtx::range_pop!();

        nvtx::range_push!("witgen");
        let witgen = WitnessGenerator::new(
            self.hal.as_ref(),
            self.circuit_hal.as_ref(),
            segment.po2,
            &io,
            trace,
            StepMode::Parallel,
        );
        nvtx::range_pop!();
        let steps = witgen.steps;

        let seal = tracing::info_span!("prove").in_scope(|| {
            nvtx::range_push!("prove");

            let mut prover = Prover::new(self.hal.as_ref(), CIRCUIT.get_taps());
            let hashfn = &self.hal.get_hash_suite().hashfn;

            // At the start of the protocol, seed the Fiat-Shamir transcript with context information
            // about the proof system and circuit.
            prover
                .iop()
                .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
            prover
                .iop()
                .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

            // Concat io (i.e. globals) and po2 into a vector.
            let mut io_po2 = vec![BabyBearElem::ZERO; io.len() + 1];
            witgen.io.view_mut(|view| {
                for (i, elem) in view.iter_mut().enumerate() {
                    *elem = elem.valid_or_zero();
                    io_po2[i] = *elem;
                }
                io_po2[io.len()] = BabyBearElem::new_raw(segment.po2 as u32);
            });

            let io_po2_digest = hashfn.hash_elem_slice(&io_po2);
            prover.iop().commit(&io_po2_digest);
            prover.iop().write_field_elem_slice(io_po2.as_slice());
            prover.set_po2(segment.po2);

            prover.commit_group(REGISTER_GROUP_CTRL, &witgen.ctrl);
            prover.commit_group(REGISTER_GROUP_DATA, &witgen.data);

            // Make the mixing values
            nvtx::range_push!("mix");
            let mix: Vec<_> = (0..CircuitImpl::MIX_SIZE)
                .map(|_| prover.iop().random_elem())
                .collect();
            nvtx::range_pop!();

            nvtx::range_push!("copy(mix)");
            let mix = self.hal.copy_from_elem("mix", mix.as_slice());
            nvtx::range_pop!();

            nvtx::range_push!("alloc(accum)");
            let mut accum = vec![BabyBearElem::INVALID; steps * CIRCUIT.accum_size()];
            nvtx::range_pop!();

            // Add random noise to end of accum
            nvtx::range_push!("noise");
            let mut rng = thread_rng();
            for i in steps - ZK_CYCLES..steps {
                for j in 0..CIRCUIT.accum_size() {
                    accum[j * steps + i] = BabyBearElem::random(&mut rng);
                }
            }
            nvtx::range_pop!();

            nvtx::range_push!("copy(accum)");
            let accum = self.hal.copy_from_elem("accum", accum.as_slice());
            nvtx::range_pop!();

            self.circuit_hal.accumulate(
                &witgen.ctrl,
                &witgen.io,
                &witgen.data,
                &mix,
                &accum,
                steps,
            );

            prover.commit_group(REGISTER_GROUP_ACCUM, &accum);

            let seal = prover.finalize(&[&mix, &witgen.io], self.circuit_hal.as_ref());

            nvtx::range_pop!();
            seal
        });

        nvtx::range_pop!();
        Ok(seal)
    }
}
