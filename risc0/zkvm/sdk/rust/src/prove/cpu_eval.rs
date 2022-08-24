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

use risc0_zkp::{
    adapter::{PolyFp, PolyFpContext},
    core::{
        fp::Fp,
        fp4::{Fp4, EXT_SIZE},
        log2_ceil,
        rou::ROU_FWD,
    },
    field::Elem,
    hal::{
        cpu::{CpuBuffer, CpuHal},
        EvalCheck,
    },
    INV_RATE,
};

pub struct CpuEvalCheck<'a, C: PolyFp> {
    circuit: &'a C,
}

impl<'a, C: PolyFp> CpuEvalCheck<'a, C> {
    pub fn new(circuit: &'a C) -> Self {
        Self { circuit }
    }
}

impl<'a, C: PolyFp> EvalCheck<CpuHal> for CpuEvalCheck<'a, C> {
    fn eval_check(
        &self,
        check: &CpuBuffer<Fp>,
        code: &CpuBuffer<Fp>,
        data: &CpuBuffer<Fp>,
        accum: &CpuBuffer<Fp>,
        mix: &CpuBuffer<Fp>,
        out: &CpuBuffer<Fp>,
        poly_mix: Fp4,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);

        let domain = steps * INV_RATE;
        let code = code.as_slice();
        let data = data.as_slice();
        let accum = accum.as_slice();
        let mix = mix.as_slice();
        let out = out.as_slice();
        let mut check = check.as_slice_mut();
        // TODO: parallelize
        for cycle in 0..domain {
            let args: &[&[Fp]] = &[&code, &out, &data, &mix, &accum];
            let cond = self.circuit.poly_fp(
                &PolyFpContext {
                    size: domain,
                    cycle,
                    mix: poly_mix,
                },
                args,
            );
            let x = Fp::new(ROU_FWD[po2 + EXP_PO2]).pow(cycle);
            // TODO: what is this magic number 3?
            let y = (Fp::new(3) * x).pow(1 << po2);
            let ret = cond.tot * (y - Fp::new(1)).inv();
            for i in 0..EXT_SIZE {
                check[i * domain + cycle] = ret.elems()[i];
            }
        }
    }
}
