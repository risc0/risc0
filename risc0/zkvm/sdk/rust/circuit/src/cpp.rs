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

use anyhow::Result;
use risc0_zkp::{
    adapter::{
        CircuitStepAccum, CircuitStepContext, CircuitStepExec, CircuitStepVerify, CustomStep,
    },
    core::fp::Fp,
};

use crate::{
    ffi::{
        call_step, risc0_circuit_rv32im_step_accum, risc0_circuit_rv32im_step_exec,
        risc0_circuit_rv32im_step_verify_bytes, risc0_circuit_rv32im_step_verify_mem,
    },
    CircuitImpl,
};

impl<S: CustomStep> CircuitStepAccum<S> for CircuitImpl {
    fn step_accum(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        call_step(
            ctx,
            custom,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_accum(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }
}

impl<S: CustomStep> CircuitStepExec<S> for CircuitImpl {
    fn step_exec(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        call_step(
            ctx,
            custom,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_exec(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }
}

impl<S: CustomStep> CircuitStepVerify<S> for CircuitImpl {
    fn step_verify_bytes(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        call_step(
            ctx,
            custom,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_verify_bytes(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }

    fn step_verify_mem(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        call_step(
            ctx,
            custom,
            args,
            |err, ctx, trampoline, size, cycle, args_ptr, args_len| unsafe {
                risc0_circuit_rv32im_step_verify_mem(
                    err, ctx, trampoline, size, cycle, args_ptr, args_len,
                )
            },
        )
    }
}
