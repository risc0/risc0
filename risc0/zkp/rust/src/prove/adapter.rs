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

use std::marker::PhantomData;

use rand::thread_rng;

use crate::{
    adapter::{CircuitDef, CircuitStepContext, CustomStep, PolyFpContext},
    core::{
        fp::Fp,
        fp4::{Fp4, EXT_SIZE},
        log2_ceil,
        rou::ROU_FWD,
        sha::Sha,
        Random,
    },
    hal::Buffer,
    prove::{executor::Executor, write_iop::WriteIOP, Circuit},
    taps::{RegisterGroup, TapSet},
    INV_RATE, ZK_CYCLES,
};

pub struct ProveAdapter<'a, C: CircuitDef<S>, S: CustomStep> {
    exec: &'a mut Executor<C, S>,
    mix: Vec<Fp>,
    accum: Vec<Fp>,
    steps: usize,
    _custom: PhantomData<S>,
}

impl<'a, C: CircuitDef<S>, S: CustomStep> ProveAdapter<'a, C, S> {
    pub fn new(exec: &'a mut Executor<C, S>) -> Self {
        let steps = exec.steps;
        ProveAdapter {
            exec,
            mix: Vec::new(),
            accum: Vec::new(),
            steps,
            _custom: PhantomData,
        }
    }
}

impl<'a, C: CircuitDef<CS>, CS: CustomStep> Circuit for ProveAdapter<'a, C, CS> {
    fn get_taps(&self) -> &TapSet {
        self.exec.circuit.get_taps()
    }

    fn execute<S: Sha>(&mut self, iop: &mut WriteIOP<S>) {
        iop.write_fp_slice(&self.exec.output);
        iop.write_u32_slice(&[self.exec.po2 as u32]);
    }

    fn accumulate<S: Sha>(&mut self, iop: &mut WriteIOP<S>) {
        // Make the mixing values
        self.mix
            .resize_with(self.exec.circuit.mix_size(), || Fp::random(&mut iop.rng));
        // Make and compute accum data
        let accum_size = self
            .exec
            .circuit
            .get_taps()
            .group_size(RegisterGroup::Accum);
        self.accum.resize(self.steps * accum_size, Fp::invalid());
        let args: &mut [&mut [Fp]] = &mut [
            &mut self.exec.code,
            &mut self.exec.output,
            &mut self.exec.data,
            &mut self.mix,
            &mut self.accum,
        ];
        for cycle in 0..self.steps - ZK_CYCLES {
            self.exec
                .circuit
                .step_accum(
                    &CircuitStepContext {
                        size: self.steps,
                        cycle,
                    },
                    &mut self.exec.custom,
                    args,
                )
                .unwrap();
        }
        // Add random noise to end of accum
        let mut rng = thread_rng();
        for i in self.steps - ZK_CYCLES..self.steps {
            for j in 0..accum_size {
                self.accum[j * self.steps + i] = Fp::random(&mut rng);
            }
        }
        // Zero out 'invalid' entries in accum
        for x in self.accum.iter_mut() {
            if *x == Fp::invalid() {
                *x = Fp::new(0);
            }
        }
    }

    fn eval_check(
        &mut self,
        check: &Buffer<Fp>,
        code: &Buffer<Fp>,
        data: &Buffer<Fp>,
        accum: &Buffer<Fp>,
        poly_mix: Fp4,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);

        let domain = self.steps * INV_RATE;
        code.view_mut(&mut |code| {
            data.view_mut(&mut |data| {
                accum.view_mut(&mut |accum| {
                    check.view_mut(&mut |check| {
                        // TODO: parallelize
                        for cycle in 0..domain {
                            let args: &[&[Fp]] =
                                &[&code, &self.exec.output, &data, &self.mix, &accum];
                            let cond = self.exec.circuit.poly_fp(
                                &PolyFpContext {
                                    size: domain,
                                    cycle,
                                    mix: poly_mix,
                                },
                                args,
                            );
                            let x = Fp::new(ROU_FWD[self.exec.po2 + EXP_PO2]).pow(cycle);
                            // TODO: what is this magic number 3?
                            let y = (Fp::new(3) * x).pow(1 << self.exec.po2);
                            let ret = cond.tot * (y - Fp::new(1)).inv();
                            for i in 0..EXT_SIZE {
                                check[i * domain + cycle] = ret.elems()[i];
                            }
                        }
                    });
                });
            });
        });
    }

    fn po2(&self) -> u32 {
        self.exec.po2 as u32
    }

    fn get_code(&self) -> &[Fp] {
        &self.exec.code
    }

    fn get_data(&self) -> &[Fp] {
        &self.exec.data
    }

    fn get_accum(&self) -> &[Fp] {
        &self.accum
    }
}
