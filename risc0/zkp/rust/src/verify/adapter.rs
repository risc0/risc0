// Copyright 2022 Risc0, Inc.
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

use crate::{
    adapter::{CircuitInfo, PolyExt, PolyExtContext, TapsProvider},
    core::{fp::Fp, fp4::Fp4, sha::Sha},
    field::Elem,
    taps::TapSet,
    verify::{read_iop::ReadIOP, Circuit},
};

pub struct VerifyAdapter<'a, C: CircuitInfo + PolyExt + TapsProvider> {
    circuit: &'a C,
    po2: u32,
    steps: usize,
    out: Option<&'a [Fp]>,
    mix: Vec<Fp>,
}

impl<'a, C: CircuitInfo + PolyExt + TapsProvider> VerifyAdapter<'a, C> {
    pub fn new(circuit: &'a C) -> Self {
        VerifyAdapter {
            circuit,
            po2: 0,
            steps: 0,
            out: None,
            mix: Vec::new(),
        }
    }
}

impl<'a, C: CircuitInfo + PolyExt + TapsProvider> Circuit<'a> for VerifyAdapter<'a, C> {
    fn taps(&self) -> &'static TapSet<'static> {
        self.circuit.get_taps()
    }

    fn execute<S: Sha>(&mut self, iop: &mut ReadIOP<'a, S>) {
        // Read the outputs + size
        self.out = Some(iop.read_pod_slice(self.circuit.output_size()));
        self.po2 = match iop.read_u32s(1) {
            &[po2] => po2,
            _ => unreachable!(),
        };
        self.steps = 1 << self.po2;
    }

    fn accumulate<S: Sha>(&mut self, iop: &mut ReadIOP<S>) {
        // Fill in accum mix
        self.mix = (0..self.circuit.mix_size())
            .map(|_| Fp::random(iop))
            .collect();
    }

    fn po2(&self) -> u32 {
        self.po2
    }

    fn compute_polynomial(&self, u: &[Fp4], poly_mix: Fp4) -> Fp4 {
        let ctx = PolyExtContext { mix: poly_mix };
        let args: &[&[Fp]] = &[&self.out.unwrap(), &self.mix];
        let result = self.circuit.poly_ext(&ctx, u, args);
        result.tot
    }
}
