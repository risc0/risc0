// Copyright 2025 RISC Zero, Inc.
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

use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

#[repr(C)]
pub struct RawExecBuffers {
    pub ctrl: *const BabyBearElem,
    pub data: *const BabyBearElem,
    pub global: *const BabyBearElem,
}

#[repr(C)]
pub struct RawAccumBuffers {
    pub ctrl: *const BabyBearElem,
    pub global: *const BabyBearElem,
    pub data: *const BabyBearElem,
    pub mix: *const BabyBearElem,
    pub accum: *const BabyBearElem,
}

#[derive(Clone, Debug, PartialEq)]
#[repr(C)]
pub struct RawPreflightCycle {
    pub iop_idx: u32,
    pub is_par_safe: bool,
}

#[repr(C)]
pub struct RawPreflightTrace {
    pub wom: *const BabyBearExtElem,
    pub cycles: *const RawPreflightCycle,
    pub iops: *const BabyBearExtElem,
    pub steps: u32,
}

#[derive(Clone, Copy, PartialEq)]
#[repr(u32)]
pub enum StepMode {
    Parallel,
    SeqForward,
    SeqReverse,
}

extern "C" {
    pub fn risc0_circuit_recursion_cpu_witgen(
        mode: StepMode,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        steps: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_recursion_cpu_accum(
        buffers: *const RawAccumBuffers,
        steps: u32,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_recursion_cpu_eval_check(
        buffers: *const RawAccumBuffers,
        poly_mix: *const BabyBearExtElem,
        check: *const BabyBearElem,
        rou: BabyBearElem,
        po2: u32,
        steps: u32,
    ) -> *const std::os::raw::c_char;
}
