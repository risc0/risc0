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

use std::ffi::CStr;

use anyhow::{anyhow, Result};
use risc0_circuit_rv32im_sys::ffi::{
    risc0_circuit_rv32im_accum_context_alloc, risc0_circuit_rv32im_accum_context_free,
    risc0_circuit_rv32im_calc_prefix_products, risc0_circuit_rv32im_poly_fp,
    risc0_circuit_rv32im_step_compute_accum, risc0_circuit_rv32im_step_verify_accum,
    risc0_circuit_string_free, risc0_circuit_string_ptr, RawAccumContext, RawError,
};
use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_zkp::{adapter::PolyFp, hal::cpu::SyncSlice};

use crate::CircuitImpl;

pub struct SyncAccumContext(pub *const RawAccumContext);

unsafe impl Sync for SyncAccumContext {}

impl Drop for SyncAccumContext {
    fn drop(&mut self) {
        unsafe { risc0_circuit_rv32im_accum_context_free(self.0) };
    }
}

impl PolyFp<BabyBear> for CircuitImpl {
    fn poly_fp(
        &self,
        cycle: usize,
        steps: usize,
        mix: &[BabyBearExtElem],
        args: &[&[BabyBearElem]],
    ) -> BabyBearExtElem {
        let args: Vec<*const BabyBearElem> = args.iter().map(|x| (*x).as_ptr()).collect();
        unsafe { risc0_circuit_rv32im_poly_fp(cycle, steps, mix.as_ptr(), args.as_ptr()) }
    }
}

impl CircuitImpl {
    pub fn alloc_accum_ctx(&self, steps: usize) -> SyncAccumContext {
        SyncAccumContext(unsafe { risc0_circuit_rv32im_accum_context_alloc(steps) })
    }

    pub fn par_step_compute_accum(
        &self,
        steps: usize,
        cycle: usize,
        ctx: &SyncAccumContext,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<()> {
        let args: Vec<*mut BabyBearElem> = args.iter().map(SyncSlice::get_ptr).collect();
        self.wrap_ffi(|err| unsafe {
            risc0_circuit_rv32im_step_compute_accum(err, ctx.0, steps, cycle, args.as_ptr())
        })
    }

    pub fn calc_prefix_products(&self, ctx: &SyncAccumContext) -> Result<()> {
        self.wrap_ffi(|err| unsafe { risc0_circuit_rv32im_calc_prefix_products(err, ctx.0) })
    }

    pub fn par_step_verify_accum(
        &self,
        steps: usize,
        cycle: usize,
        ctx: &SyncAccumContext,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<()> {
        let args: Vec<*mut BabyBearElem> = args.iter().map(SyncSlice::get_ptr).collect();
        self.wrap_ffi(|err| unsafe {
            risc0_circuit_rv32im_step_verify_accum(err, ctx.0, steps, cycle, args.as_ptr())
        })
    }

    fn wrap_ffi<R, F: Fn(*mut RawError) -> R>(&self, inner: F) -> Result<R> {
        let mut err = RawError::default();
        let result = inner(&mut err);
        if err.msg.is_null() {
            Ok(result)
        } else {
            let what = unsafe {
                let str = risc0_circuit_string_ptr(err.msg);
                let msg = CStr::from_ptr(str).to_str().unwrap().to_string();
                risc0_circuit_string_free(err.msg);
                msg
            };
            Err(anyhow!(what))
        }
    }
}
