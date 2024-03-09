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

pub mod argument;
pub mod loader;
pub mod machine;
#[cfg(test)]
mod tests;
pub mod witgen;

use std::rc::Rc;

use anyhow::Result;
use risc0_zkp::{
    adapter::TapsProvider,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem, Elem},
    hal::{CircuitHal, Hal},
    layout::Buffer as _,
    prove::Prover,
};

use self::witgen::WitnessGenerator;
use super::{segment::Segment, Seal, SegmentProver};
use crate::{
    layout::{OutBuffer, LAYOUT},
    CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

struct Twin(Elem, Elem);

struct Quad(Elem, Elem, Elem, Elem);

pub struct SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    hal: Rc<H>,
    circuit_hal: Rc<C>,
}

impl<H, C> SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    pub fn new(hal: Rc<H>, circuit_hal: Rc<C>) -> Self {
        Self { hal, circuit_hal }
    }
}

impl<H, C> SegmentProver for SegmentProverImpl<H, C>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    #[tracing::instrument(skip_all)]
    fn prove_segment(&self, segment: &Segment) -> Result<Seal> {
        let trace = segment.preflight()?;

        let io = segment.prepare_globals();
        let mut witgen = WitnessGenerator::new(segment.po2, &io);
        witgen.execute(trace)?;

        let seal = tracing::info_span!("prove").in_scope(|| {
            let mut prover = Prover::new(self.hal.as_ref(), CIRCUIT.get_taps());
            prover.iop().write_field_elem_slice(&witgen.io.as_slice());
            prover.iop().write_u32_slice(&[segment.po2 as u32]);
            prover.set_po2(segment.po2);

            let ctrl = self.hal.copy_from_elem("ctrl", &witgen.ctrl.as_slice());
            prover.commit_group(REGISTER_GROUP_CTRL, ctrl);

            let data = self.hal.copy_from_elem("data", &witgen.data.as_slice());
            prover.commit_group(REGISTER_GROUP_DATA, data);

            let (mix, accum) = witgen.accumulate(prover.iop());

            let accum = self.hal.copy_from_elem("accum", &accum.as_slice());
            prover.commit_group(REGISTER_GROUP_ACCUM, accum);

            let io = &witgen.io.as_slice();
            tracing::debug!("Globals: {:?}", OutBuffer(io).tree(LAYOUT));
            let io = self.hal.copy_from_elem("io", io);
            let mix = self.hal.copy_from_elem("mix", &mix.as_slice());

            prover.finalize(&[&mix, &io], self.circuit_hal.as_ref())
        });

        Ok(seal)
    }
}

impl From<Twin> for u32 {
    fn from(value: Twin) -> Self {
        let x0: u32 = value.0.into();
        let x1: u32 = value.1.into();
        x0 << 8 | x1
    }
}

impl From<u32> for Twin {
    fn from(value: u32) -> Self {
        Self(Elem::new(value >> 8 & 0xff), Elem::new(value & 0xff))
    }
}

impl From<Quad> for u32 {
    fn from(value: Quad) -> Self {
        let x0: u32 = value.0.into();
        let x1: u32 = value.1.into();
        let x2: u32 = value.2.into();
        let x3: u32 = value.3.into();
        x0 | x1 << 8 | x2 << 16 | x3 << 24
    }
}

impl From<u32> for Quad {
    fn from(value: u32) -> Self {
        Self(
            Elem::new(value & 0xff),
            Elem::new(value >> 8 & 0xff),
            Elem::new(value >> 16 & 0xff),
            Elem::new(value >> 24 & 0xff),
        )
    }
}
