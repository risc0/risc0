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

#[cfg(feature = "cuda")]
use cust::memory::DevicePointer;

use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

#[derive(Debug)]
#[repr(C)]
pub struct ScatterInfo {
    pub offset: u32,
    pub row: u32,
    pub col: u16,
    pub count: u16,
    pub bits: u32,
}

#[repr(C)]
pub struct RawPreflightTrace {
    pub preimages: *const [u64; 25],
    pub preimages_count: u32,
    pub preimage_idxs: *const u32,
    pub run_order: *const u32,
}

#[repr(C)]
pub struct RawExecBuffers {
    pub global: RawBuffer,
    pub data: RawBuffer,
}

#[repr(C)]
pub struct RawBuffer {
    pub buf: *const BabyBearElem,
    pub rows: usize,
    pub cols: usize,
    pub checked_reads: bool,
}

unsafe extern "C" {
    pub fn risc0_circuit_keccak_cpu_witgen(
        mode: u32,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_keccak_cpu_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mixs: *const BabyBearExtElem,
        args_ptr: *const *const BabyBearElem,
        result: *mut BabyBearExtElem,
    ) -> *const std::os::raw::c_char;
}

#[cfg(feature = "cuda")]
unsafe extern "C" {
    pub fn risc0_circuit_keccak_cuda_scatter(
        into: DevicePointer<u8>,
        infos: *const ScatterInfo,
        from: DevicePointer<u8>,
        rows: u32,
        count: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_keccak_cuda_witgen(
        mode: u32,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_keccak_cuda_eval_check(
        check: DevicePointer<u8>,
        ctrl: DevicePointer<u8>,
        data: DevicePointer<u8>,
        accum: DevicePointer<u8>,
        mix: DevicePointer<u8>,
        out: DevicePointer<u8>,
        rou: *const BabyBearElem,
        po2: u32,
        domain: u32,
        poly_mix_pows: *const u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_keccak_cuda_reset() -> *const std::os::raw::c_char;
}
