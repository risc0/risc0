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

use core::ffi::{c_void, CStr};

use anyhow::{anyhow, Result};
use risc0_circuit_recursion_sys::ffi::{
    get_trampoline, risc0_circuit_recursion_poly_fp, risc0_circuit_recursion_step_compute_accum,
    risc0_circuit_recursion_step_exec, risc0_circuit_recursion_step_verify_accum,
    risc0_circuit_recursion_step_verify_bytes, risc0_circuit_recursion_step_verify_mem,
    risc0_circuit_recursion_string_free, risc0_circuit_recursion_string_ptr, Callback, RawError,
};
use risc0_zkp::{
    adapter::{CircuitProveDef, CircuitStep, CircuitStepContext, CircuitStepHandler, PolyFp},
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    hal::cpu::SyncSlice,
};

use crate::CircuitImpl;

impl CircuitStep<BabyBearElem> for CircuitImpl {
    fn step_compute_accum<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_recursion_step_compute_accum(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_accum<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_recursion_step_verify_accum(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_exec<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_recursion_step_exec(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_bytes<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_recursion_step_verify_bytes(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_mem<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_recursion_step_verify_mem(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
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
        unsafe {
            risc0_circuit_recursion_poly_fp(cycle, steps, mix.as_ptr(), args.as_ptr(), args.len())
        }
    }
}

impl CircuitProveDef<BabyBear> for CircuitImpl {}

pub(crate) fn call_step<S, F>(
    ctx: &CircuitStepContext,
    handler: &mut S,
    args: &[SyncSlice<BabyBearElem>],
    inner: F,
) -> Result<BabyBearElem>
where
    S: CircuitStepHandler<BabyBearElem>,
    F: FnOnce(
        *mut RawError,
        *mut c_void,
        Callback,
        usize,
        usize,
        *const *mut BabyBearElem,
        usize,
    ) -> BabyBearElem,
{
    let mut last_err = None;
    let mut call =
        |name: &str, extra: &str, args: &[BabyBearElem], outs: &mut [BabyBearElem]| match handler
            .call(ctx.cycle, name, extra, args, outs)
        {
            Ok(()) => true,
            Err(err) => {
                last_err = Some(err);
                false
            }
        };
    let trampoline = get_trampoline(&call);
    let mut err = RawError::default();
    let args: Vec<*mut BabyBearElem> = args.iter().map(SyncSlice::get_ptr).collect();
    let result = inner(
        &mut err,
        &mut call as *mut _ as *mut c_void,
        trampoline,
        ctx.size,
        ctx.cycle,
        args.as_ptr(),
        args.len(),
    );
    if let Some(err) = last_err {
        return Err(err);
    }
    if err.msg.is_null() {
        Ok(result)
    } else {
        let what = unsafe {
            let str = risc0_circuit_recursion_string_ptr(err.msg);
            let msg = CStr::from_ptr(str).to_str().unwrap().to_string();
            risc0_circuit_recursion_string_free(err.msg);
            msg
        };
        Err(anyhow!(what))
    }
}
