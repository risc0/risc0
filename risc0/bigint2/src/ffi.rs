// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

unsafe extern "C" {
    pub fn sys_bigint2_1(blob_ptr: *const u8, a1: *const u32);

    pub fn sys_bigint2_2(blob_ptr: *const u8, a1: *const u32, a2: *const u32);

    pub fn sys_bigint2_3(blob_ptr: *const u8, a1: *const u32, a2: *const u32, a3: *const u32);

    pub fn sys_bigint2_4(
        blob_ptr: *const u8,
        a1: *const u32,
        a2: *const u32,
        a3: *const u32,
        a4: *const u32,
    );

    pub fn sys_bigint2_5(
        blob_ptr: *const u8,
        a1: *const u32,
        a2: *const u32,
        a3: *const u32,
        a4: *const u32,
        a5: *const u32,
    );

    pub fn sys_bigint2_6(
        blob_ptr: *const u8,
        a1: *const u32,
        a2: *const u32,
        a3: *const u32,
        a4: *const u32,
        a5: *const u32,
        a6: *const u32,
    );
}
