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

use std::rc::Rc;

use anyhow::{bail, Result};
use rayon::prelude::*;
use risc0_circuit_rv32im_sys::ffi::RawPreflightTrace;
use risc0_core::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    map_pow, Elem, ExtElem, RootsOfUnity,
};
use risc0_sys::CppError;
use risc0_zkp::{
    adapter::PolyFp,
    core::{
        hash::{poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite},
        log2_ceil,
    },
    field::baby_bear::BabyBear,
    hal::{
        cpu::{CpuBuffer, CpuHal},
        CircuitHal, Hal,
    },
    INV_RATE, ZK_CYCLES,
};

use crate::{
    prove::{engine::SegmentProverImpl, SegmentProver},
    CIRCUIT, GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL,
    REGISTER_GROUP_DATA,
};

use super::{CircuitWitnessGenerator, StepMode};

#[derive(Default)]
pub struct CpuCircuitHal;

impl CpuCircuitHal {
    pub fn new() -> Self {
        Self
    }
}

impl CircuitWitnessGenerator<CpuHal<BabyBear>> for CpuCircuitHal {
    fn generate_witness(
        &self,
        mode: StepMode,
        trace: &RawPreflightTrace,
        steps: usize,
        count: usize,
        ctrl: &CpuBuffer<BabyBearElem>,
        io: &CpuBuffer<BabyBearElem>,
        data: &CpuBuffer<BabyBearElem>,
    ) {
        tracing::debug!("witgen: {steps}, {count}");
        extern "C" {
            fn risc0_circuit_rv32im_cpu_witgen(
                mode: u32,
                trace: *const RawPreflightTrace,
                steps: u32,
                count: u32,
                ctrl: *const BabyBearElem,
                io: *const BabyBearElem,
                data: *const BabyBearElem,
            ) -> CppError;
        }
        unsafe {
            risc0_circuit_rv32im_cpu_witgen(
                mode as u32,
                trace,
                steps as u32,
                count as u32,
                ctrl.as_slice().as_ptr(),
                io.as_slice().as_ptr(),
                data.as_slice().as_ptr(),
            )
            .unwrap();
        }
    }
}

impl<H> CircuitHal<H> for CpuCircuitHal
where
    H: Hal<
        Elem = BabyBearElem,
        ExtElem = BabyBearExtElem,
        Buffer<<H as Hal>::Elem> = CpuBuffer<BabyBearElem>,
    >,
{
    #[tracing::instrument(skip_all)]
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

        let ctrl = groups[REGISTER_GROUP_CTRL].as_slice();
        let ctrl = unsafe { std::slice::from_raw_parts(ctrl.as_ptr(), ctrl.len()) };
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

        let args: &[&[BabyBearElem]] = &[ctrl, out, data, mix, accum];

        (0..domain).into_par_iter().for_each(|cycle| {
            let tot = CIRCUIT.poly_fp(cycle, domain, poly_mix_pows, args);
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

    #[tracing::instrument(skip_all)]
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

            let accum_ctx = CIRCUIT.alloc_accum_ctx(steps);

            tracing::info_span!("step_compute_accum").in_scope(|| {
                (0..steps - ZK_CYCLES).into_par_iter().for_each(|cycle| {
                    CIRCUIT
                        .par_step_compute_accum(steps, cycle, &accum_ctx, args)
                        .unwrap();
                });
            });
            tracing::info_span!("calc_prefix_products").in_scope(|| {
                CIRCUIT.calc_prefix_products(&accum_ctx).unwrap();
            });
            tracing::info_span!("step_verify_accum").in_scope(|| {
                (0..steps - ZK_CYCLES).into_par_iter().for_each(|cycle| {
                    CIRCUIT
                        .par_step_verify_accum(steps, cycle, &accum_ctx, args)
                        .unwrap();
                });
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

pub fn segment_prover(hashfn: &str) -> Result<Box<dyn SegmentProver>> {
    let suite = match hashfn {
        "sha-256" => Sha256HashSuite::new_suite(),
        "poseidon2" => Poseidon2HashSuite::new_suite(),
        _ => bail!("Unsupported hashfn: {hashfn}"),
    };

    let hal = Rc::new(CpuHal::new(suite));
    let circuit_hal = Rc::new(CpuCircuitHal::new());
    Ok(Box::new(SegmentProverImpl::new(hal, circuit_hal)))
}
