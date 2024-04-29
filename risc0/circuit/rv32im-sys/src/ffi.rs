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

use std::os::raw::c_char;

use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

pub enum RawString {}
pub enum RawAccumContext {}
pub enum RawMachineContext {}

#[repr(C)]
pub struct RawError {
    pub msg: *const RawString,
}

#[repr(C)]
pub struct RawMemoryTransaction {
    pub cycle: usize,
    pub addr: u32,
    pub data: u32,
}

#[repr(C)]
pub struct RawPreflightCycle {
    pub major: u32,
    pub minor: u32,
    pub mem_idx: usize,
    pub extra_idx: usize,
}

#[repr(C)]
pub struct RawPreflightTrace {
    pub cycles: *const RawPreflightCycle,
    pub txns: *const RawMemoryTransaction,
    pub extras: *const u32,
    pub is_trace: u32,
}

unsafe impl Sync for RawPreflightTrace {}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

extern "C" {
    pub fn risc0_circuit_string_ptr(str: *const RawString) -> *const c_char;

    pub fn risc0_circuit_string_free(str: *const RawString);

    pub fn risc0_circuit_rv32im_machine_context_alloc(
        trace: *const RawPreflightTrace,
        steps: usize,
    ) -> *const RawMachineContext;

    pub fn risc0_circuit_rv32im_machine_context_free(ctx: *const RawMachineContext);

    pub fn risc0_circuit_rv32im_accum_context_alloc(steps: usize) -> *const RawAccumContext;

    pub fn risc0_circuit_rv32im_accum_context_free(ctx: *const RawAccumContext);

    pub fn risc0_circuit_rv32im_step_exec(
        err: *mut RawError,
        ctx: *const RawMachineContext,
        steps: usize,
        cycle: usize,
        args: *const *mut BabyBearElem,
    ) -> BabyBearElem;

    pub fn risc0_circuit_rv32im_step_verify_mem(
        err: *mut RawError,
        ctx: *const RawMachineContext,
        steps: usize,
        cycle: usize,
        args: *const *mut BabyBearElem,
    ) -> BabyBearElem;

    pub fn risc0_circuit_rv32im_step_verify_bytes(
        err: *mut RawError,
        ctx: *const RawMachineContext,
        steps: usize,
        cycle: usize,
        args: *const *mut BabyBearElem,
    ) -> BabyBearElem;

    pub fn risc0_circuit_rv32im_sort_ram(err: *mut RawError, ctx: *const RawMachineContext);

    pub fn risc0_circuit_rv32im_inject_ram_backs(
        err: *mut RawError,
        ctx: *const RawMachineContext,
        steps: usize,
        cycle: usize,
        data: *mut BabyBearElem,
    );

    pub fn risc0_circuit_rv32im_sort_bytes(err: *mut RawError, ctx: *const RawMachineContext);

    pub fn risc0_circuit_rv32im_step_compute_accum(
        err: *mut RawError,
        ctx: *const RawAccumContext,
        steps: usize,
        cycle: usize,
        args: *const *mut BabyBearElem,
    ) -> BabyBearElem;

    pub fn risc0_circuit_rv32im_calc_prefix_products(
        err: *mut RawError,
        ctx: *const RawAccumContext,
    );

    pub fn risc0_circuit_rv32im_step_verify_accum(
        err: *mut RawError,
        ctx: *const RawAccumContext,
        steps: usize,
        cycle: usize,
        args: *const *mut BabyBearElem,
    ) -> BabyBearElem;

    pub fn risc0_circuit_rv32im_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mix: *const BabyBearExtElem,
        args: *const *const BabyBearElem,
    ) -> BabyBearExtElem;
}
