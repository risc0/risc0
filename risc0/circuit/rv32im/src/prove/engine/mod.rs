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

use anyhow::Result;
use risc0_zkp::{
    adapter::TapsProvider,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem, Elem},
    hal::{CircuitHal, Hal},
    layout::Buffer as _,
    prove::Prover,
};

use self::witgen::WitnessGenerator;
use super::emu::{preflight::preflight_segment, Segment};
use crate::{
    layout::{OutBuffer, LAYOUT},
    CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

type Twin = (Elem, Elem);
type Quad = (Elem, Elem, Elem, Elem);

pub fn prove_segment<H, C>(hal: &H, circuit_hal: &C, segment: &Segment) -> Result<Vec<u32>>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    let trace = preflight_segment(segment)?;

    let io = segment.prepare_globals();
    let mut witgen = WitnessGenerator::new(segment.po2, &io);
    witgen.execute(trace)?;

    let mut prover = Prover::new(hal, CIRCUIT.get_taps());
    prover.iop().write_field_elem_slice(&witgen.io.as_slice());
    prover.iop().write_u32_slice(&[segment.po2 as u32]);
    prover.set_po2(segment.po2);

    let ctrl = hal.copy_from_elem("ctrl", &witgen.ctrl.as_slice());
    prover.commit_group(REGISTER_GROUP_CTRL, ctrl);

    let data = hal.copy_from_elem("data", &witgen.data.as_slice());
    prover.commit_group(REGISTER_GROUP_DATA, data);

    let (mix, accum) = witgen.accumulate(prover.iop());

    let accum = hal.copy_from_elem("accum", &accum.as_slice());
    prover.commit_group(REGISTER_GROUP_ACCUM, accum);

    let io = &witgen.io.as_slice();
    tracing::debug!("Globals: {:?}", OutBuffer(io).tree(LAYOUT));
    let io = hal.copy_from_elem("io", io);
    let mix = hal.copy_from_elem("mix", &mix.as_slice());

    let seal = prover.finalize(&[&mix, &io], circuit_hal);
    Ok(seal)
}

fn split_word8(value: u32) -> Quad {
    (
        Elem::new(value & 0xff),
        Elem::new(value >> 8 & 0xff),
        Elem::new(value >> 16 & 0xff),
        Elem::new(value >> 24 & 0xff),
    )
}

fn merge_word8((x0, x1, x2, x3): Quad) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    let x2: u32 = x2.into();
    let x3: u32 = x3.into();
    x0 | x1 << 8 | x2 << 16 | x3 << 24
}

fn split_twin(value: u32) -> Twin {
    (Elem::new(value >> 8 & 0xff), Elem::new(value & 0xff))
}

fn merge_twin((x0, x1): Twin) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    x0 << 8 | x1
}
