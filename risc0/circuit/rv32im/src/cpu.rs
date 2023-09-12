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

use rayon::prelude::*;
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    Elem, ExtElem, RootsOfUnity,
};
use risc0_zkp::{
    adapter::PolyFp,
    core::log2_ceil,
    hal::{cpu::CpuBuffer, CircuitHal, Hal},
    INV_RATE,
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
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
    C: PolyFp<BabyBear> + Sync,
    H: Hal<
        Elem = BabyBearElem,
        ExtElem = BabyBearExtElem,
        Buffer<<H as Hal>::Elem> = CpuBuffer<BabyBearElem>,
    >,
{
    #[tracing::instrument(skip_all)]
    fn eval_check(
        &self,
        check: &H::Buffer<BabyBearElem>,
        groups: &[&H::Buffer<BabyBearElem>],
        globals: &[&H::Buffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;

        // SAFETY: Convert a borrow of a cell into a raw const slice so that we can pass
        // it over the thread boundary. This should be safe because the scope of the
        // usage is within this function and each thread access will not overlap with
        // each other.

        let code = groups[REGISTER_GROUP_CODE].as_slice();
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

        let args: &[&[BabyBearElem]] = &[code, out, data, mix, accum];

        (0..domain).into_par_iter().for_each(|cycle| {
            let tot = self.circuit.poly_fp(cycle, domain, &poly_mix, args);
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
}
