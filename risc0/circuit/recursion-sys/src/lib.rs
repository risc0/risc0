// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
    pub is_par_safe: u32,
}

#[repr(C)]
pub struct RawPreflightTrace {
    pub wom: *const BabyBearExtElem,
    pub cycles: *const RawPreflightCycle,
    pub iops: *const BabyBearExtElem,
    pub num_woms: u32,
    pub num_cycles: u32,
    pub num_iops: u32,
}

#[derive(Clone, Copy, PartialEq)]
#[repr(u32)]
pub enum StepMode {
    Parallel,
    SeqForward,
    SeqReverse,
}

unsafe extern "C" {
    pub fn risc0_circuit_recursion_cpu_witgen(
        mode: StepMode,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        total_cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_recursion_cpu_accum(
        buffers: *const RawAccumBuffers,
        work_cycles: u32,
        total_cycles: u32,
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

#[cfg(feature = "cuda")]
unsafe extern "C" {
    pub fn risc0_circuit_recursion_cuda_witgen(
        mode: StepMode,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        steps: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_recursion_cuda_accum(
        buffers: *const RawAccumBuffers,
        steps: u32,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_recursion_cuda_eval_check(
        check: *const BabyBearElem,
        ctrl: *const BabyBearElem,
        data: *const BabyBearElem,
        accum: *const BabyBearElem,
        mix: *const BabyBearElem,
        out: *const BabyBearElem,
        rou: *const BabyBearElem,
        po2: u32,
        domain: u32,
        poly_mix: *const BabyBearExtElem,
    ) -> *const std::os::raw::c_char;
}
