// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use cust::memory::DevicePointer;

pub use sppark::Error as SpparkError;

unsafe extern "C" {
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

    pub fn sppark_poseidon254_fold(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        num_hashes: usize,
    ) -> sppark::Error;

    pub fn sppark_poseidon254_rows(
        d_out: DevicePointer<u8>,
        d_in: DevicePointer<u8>,
        count: usize,
        col_size: u32,
    ) -> sppark::Error;

    pub fn supra_poly_divide(
        polynomial: DevicePointer<u8>,
        poly_size: usize,
        remainder: *mut u32,
        pow: *const u32,
    ) -> sppark::Error;
}
