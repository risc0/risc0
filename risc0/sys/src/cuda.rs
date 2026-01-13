// Copyright 2026 RISC Zero, Inc.
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

use cust::memory::DevicePointer;

pub use risc0_sppark::Error as SpparkError;

unsafe extern "C" {
    pub fn sppark_batch_expand(
        stream: cust::sys::CUstream,
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        lg_domain_size: u32,
        lg_blowup: u32,
        poly_count: u32,
    ) -> risc0_sppark::Error;

    pub fn sppark_batch_NTT(
        stream: cust::sys::CUstream,
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> risc0_sppark::Error;

    pub fn sppark_batch_iNTT(
        stream: cust::sys::CUstream,
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> risc0_sppark::Error;

    pub fn sppark_batch_zk_shift(
        stream: cust::sys::CUstream,
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> risc0_sppark::Error;

    pub fn sppark_poseidon2_fold(
        stream: cust::sys::CUstream,
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        num_hashes: usize,
    ) -> risc0_sppark::Error;

    pub fn sppark_poseidon2_rows(
        stream: cust::sys::CUstream,
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        count: u32,
        col_size: u32,
    ) -> risc0_sppark::Error;

    pub fn sppark_poseidon254_fold(
        stream: cust::sys::CUstream,
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        num_hashes: usize,
    ) -> risc0_sppark::Error;

    pub fn sppark_poseidon254_rows(
        stream: cust::sys::CUstream,
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        count: usize,
        col_size: u32,
    ) -> risc0_sppark::Error;

    pub fn supra_poly_divide(
        stream: cust::sys::CUstream,
        polynomial: DevicePointer<u8>,
        poly_size: usize,
        remainder: *mut u32,
        pow: *const u32,
    ) -> risc0_sppark::Error;

    pub fn risc0_zkp_cuda_fri_fold(
        stream: cust::sys::CUstream,
        output: DevicePointer<u8>,
        input: DevicePointer<u8>,
        mix: *const u32, // FpExt*
        count: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_zkp_cuda_mix_poly_coeffs(
        stream: cust::sys::CUstream,
        output: DevicePointer<u8>,
        input: DevicePointer<u8>,
        combos: DevicePointer<u8>,
        mix_start: *const u32, // FpExt*
        mix: *const u32,       // FpExt*
        input_size: u32,
        count: u32,
    ) -> *const std::os::raw::c_char;
}
