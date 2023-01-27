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

use anyhow::Result;
use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_zkp::adapter::{CircuitDef, CircuitStep, CircuitStepContext, CircuitStepHandler, PolyFp};

use crate::{
    ffi::{
        call_step, risc0_circuit_rv32im_poly_fp, risc0_circuit_rv32im_step_compute_accum,
        risc0_circuit_rv32im_step_exec, risc0_circuit_rv32im_step_verify_accum,
        risc0_circuit_rv32im_step_verify_bytes, risc0_circuit_rv32im_step_verify_mem,
    },
    CircuitImpl,
};

impl CircuitStep<BabyBearElem> for CircuitImpl {
    fn step_compute_accum<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &mut [&mut [BabyBearElem]],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_compute_accum(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_accum<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &mut [&mut [BabyBearElem]],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_verify_accum(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_exec<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &mut [&mut [BabyBearElem]],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_exec(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_bytes<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &mut [&mut [BabyBearElem]],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_verify_bytes(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_mem<S: CircuitStepHandler<BabyBearElem>>(
        &self,
        ctx: &CircuitStepContext,
        handler: &mut S,
        args: &mut [&mut [BabyBearElem]],
    ) -> Result<BabyBearElem> {
        call_step(
            ctx,
            handler,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_verify_mem(
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
        mix: &BabyBearExtElem,
        args: &[&[BabyBearElem]],
    ) -> BabyBearExtElem {
        let args: Vec<*const BabyBearElem> = args.iter().map(|x| (*x).as_ptr()).collect();
        unsafe {
            risc0_circuit_rv32im_poly_fp(
                cycle,
                steps,
                mix as *const BabyBearExtElem,
                args.as_ptr(),
                args.len(),
            )
        }
    }
}

impl<'a> CircuitDef<BabyBear> for CircuitImpl {}
