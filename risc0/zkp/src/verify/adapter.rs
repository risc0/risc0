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

use alloc::vec::Vec;

use risc0_core::field::{baby_bear::BabyBearElem, Elem};

use crate::{
    adapter::{CircuitInfo, TapsProvider},
    core::sha::Sha256,
    taps::TapSet,
    verify::read_iop::ReadIOP,
};

pub struct VerifyAdapter<'a, C: CircuitInfo + TapsProvider> {
    circuit: &'a C,
    po2: u32,
    steps: usize,
    pub out: Option<&'a [BabyBearElem]>,
    pub mix: Vec<BabyBearElem>,
}

impl<'a, C: CircuitInfo + TapsProvider> VerifyAdapter<'a, C> {
    pub fn new(circuit: &'a C) -> Self {
        VerifyAdapter {
            circuit,
            po2: 0,
            steps: 0,
            out: None,
            mix: Vec::new(),
        }
    }

    pub fn taps(&self) -> &'static TapSet<'static> {
        self.circuit.get_taps()
    }

    pub fn execute<S: Sha256>(&mut self, iop: &mut ReadIOP<'a, S>) {
        // Read the outputs + size
        self.out = Some(iop.read_field_elem_slice(C::OUTPUT_SIZE));
        self.po2 = match iop.read_u32s(1) {
            &[po2] => po2,
            _ => unreachable!(),
        };
        self.steps = 1 << self.po2;
    }

    pub fn accumulate<S: Sha256>(&mut self, iop: &mut ReadIOP<'a, S>) {
        // Fill in accum mix
        self.mix = (0..C::MIX_SIZE)
            .map(|_| BabyBearElem::random(iop))
            .collect();
    }

    pub fn po2(&self) -> u32 {
        self.po2
    }
}
