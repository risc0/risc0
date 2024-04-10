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

use std::sync::Mutex;

use rayon::prelude::*;
use risc0_zkp::{
    adapter::{CircuitStep, CircuitStepContext, PolyFp},
    core::log2_ceil,
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        map_pow, Elem, ExtElem, RootsOfUnity,
    },
    hal::{cpu::CpuBuffer, CircuitHal, Hal},
    prove::accum::{Accum, Handler},
    INV_RATE, ZK_CYCLES,
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

pub struct CpuCircuitHal<'a, C: PolyFp<BabyBear>> {
    circuit: &'a C,
}

impl<'a, C: PolyFp<BabyBear>> CpuCircuitHal<'a, C> {
    pub fn new(circuit: &'a C) -> Self {
        Self { circuit }
    }
}

impl<'a, C, H> CircuitHal<H> for CpuCircuitHal<'a, C>
where
    C: PolyFp<BabyBear> + Sync + CircuitStep<BabyBearElem>,
    H: Hal<
        Elem = BabyBearElem,
        ExtElem = BabyBearExtElem,
        Buffer<<H as Hal>::Elem> = CpuBuffer<BabyBearElem>,
    >,
{
    fn eval_check(
        &self,
        check: &CpuBuffer<BabyBearElem>,
        groups: &[&CpuBuffer<BabyBearElem>],
        globals: &[&CpuBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;

        let poly_mix_pows = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);

        // SAFETY: Convert a borrow of a cell into a raw const slice so that we can pass
        // it over the thread boundary. This should be safe because the scope of the
        // usage is within this function and each thread access will not overlap with
        // each other.

        let code = groups[REGISTER_GROUP_CTRL].as_slice();
        let code = unsafe { std::slice::from_raw_parts(code.as_ptr(), code.len()) };
        let data = groups[REGISTER_GROUP_DATA].as_slice();
        let data = unsafe { std::slice::from_raw_parts(data.as_ptr(), data.len()) };
        let accum = groups[REGISTER_GROUP_ACCUM].as_slice();
        let accum = unsafe { std::slice::from_raw_parts(accum.as_ptr(), accum.len()) };
        let mix = globals[GLOBAL_MIX].as_slice();
        let mix = unsafe { std::slice::from_raw_parts(mix.as_ptr(), mix.len()) };
        let out = globals[GLOBAL_OUT].as_slice();
        let out = unsafe { std::slice::from_raw_parts(out.as_ptr(), out.len()) };
        let check = check.as_slice();
        let check = unsafe { std::slice::from_raw_parts(check.as_ptr(), check.len()) };
        let poly_mix_pows = poly_mix_pows.as_slice();

        let args: &[&[BabyBearElem]] = &[&code, &out, &data, &mix, &accum];

        (0..domain).into_par_iter().for_each(|cycle| {
            let tot = self.circuit.poly_fp(cycle, domain, poly_mix_pows, args);
            let x = BabyBearElem::ROU_FWD[po2 + EXP_PO2].pow(cycle);
            // TODO: what is this magic number 3?
            let y = (BabyBearElem::new(3) * x).pow(1 << po2);
            let ret = tot * (y - BabyBearElem::new(1)).inv();

            // SAFETY: This conversion is to make the check slice mutable, which should be
            // safe because each thread access will not overlap with each other.
            let check = unsafe {
                std::slice::from_raw_parts_mut(check.as_ptr() as *mut BabyBearElem, check.len())
            };
            for i in 0..BabyBearExtElem::EXT_SIZE {
                check[i * domain + cycle] = ret.elems()[i];
            }
        });
    }

    fn accumulate(
        &self,
        ctrl: &CpuBuffer<BabyBearElem>,
        io: &CpuBuffer<BabyBearElem>,
        data: &CpuBuffer<BabyBearElem>,
        mix: &CpuBuffer<BabyBearElem>,
        accum: &CpuBuffer<BabyBearElem>,
        steps: usize,
    ) {
        {
            let args = &[
                ctrl.as_slice_sync(),
                io.as_slice_sync(),
                data.as_slice_sync(),
                mix.as_slice_sync(),
                accum.as_slice_sync(),
            ];

            let accumulator: Mutex<Accum<BabyBearExtElem>> = Mutex::new(Accum::new(steps));
            tracing::info_span!("step_compute_accum").in_scope(|| {
                (0..steps - ZK_CYCLES).into_par_iter().for_each_init(
                    || Handler::<BabyBear>::new(&accumulator),
                    |handler, cycle| {
                        self.circuit
                            .step_compute_accum(
                                &CircuitStepContext { size: steps, cycle },
                                handler,
                                args,
                            )
                            .unwrap();
                    },
                );
            });
            tracing::info_span!("calc_prefix_products").in_scope(|| {
                accumulator.lock().unwrap().calc_prefix_products();
            });
            tracing::info_span!("step_verify_accum").in_scope(|| {
                (0..steps - ZK_CYCLES).into_par_iter().for_each_init(
                    || Handler::<BabyBear>::new(&accumulator),
                    |handler, cycle| {
                        self.circuit
                            .step_verify_accum(
                                &CircuitStepContext { size: steps, cycle },
                                handler,
                                args,
                            )
                            .unwrap();
                    },
                );
            });
        }

        {
            // Zero out 'invalid' entries in accum and io
            let mut accum_slice = accum.as_slice_mut();
            let mut io = io.as_slice_mut();
            for value in accum_slice.iter_mut().chain(io.iter_mut()) {
                *value = value.valid_or_zero();
            }
        }
    }
}
