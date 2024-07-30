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

use cust::memory::DevicePointer;

pub use sppark::Error as SpparkError;

extern "C" {
    pub fn sppark_init() -> sppark::Error;

    pub fn sppark_batch_expand(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        lg_domain_size: u32,
        lg_blowup: u32,
        poly_count: u32,
    ) -> sppark::Error;

    pub fn sppark_batch_NTT(
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> sppark::Error;

    pub fn sppark_batch_iNTT(
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> sppark::Error;

    pub fn sppark_batch_zk_shift(
        d_inout: DevicePointer<u8>,
        lg_domain_size: u32,
        poly_count: u32,
    ) -> sppark::Error;

    pub fn sppark_poseidon_fold(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        num_hashes: usize,
    ) -> sppark::Error;

    pub fn sppark_poseidon_rows(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        count: u32,
        col_size: u32,
    ) -> sppark::Error;

    pub fn sppark_poseidon2_fold(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        num_hashes: usize,
    ) -> sppark::Error;

    pub fn sppark_poseidon2_rows(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        count: u32,
        col_size: u32,
    ) -> sppark::Error;
}
