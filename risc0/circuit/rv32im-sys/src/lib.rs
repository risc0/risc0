// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(feature = "cuda")]
use cust::memory::DevicePointer;
use derive_more::Debug;
use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

#[derive(Clone, Debug, PartialEq)]
#[repr(C)]
pub struct RawMemoryTransaction {
    #[debug("{addr:#010x}")]
    pub addr: u32,
    pub cycle: u32,
    #[debug("{word:#010x}")]
    pub word: u32,
    pub prev_cycle: u32,
    #[debug("{word:#010x}")]
    pub prev_word: u32,
}

#[derive(Clone, Debug, PartialEq)]
#[repr(C)]
pub struct RawPreflightCycle {
    pub state: u32,
    #[debug("{pc:#010x}")]
    pub pc: u32,
    pub major: u8,
    pub minor: u8,
    pub machine_mode: u8,
    #[debug(skip)]
    pub padding: u8,
    pub user_cycle: u32,
    pub txn_idx: u32,
    pub paging_idx: u32,
    pub bigint_idx: u32,
    pub diff_count: [u32; 2],
}

#[repr(C)]
pub struct RawPreflightTrace {
    pub cycles: *const RawPreflightCycle,
    pub txns: *const RawMemoryTransaction,
    pub bigint_bytes: *const u8,
    pub txns_len: u32,
    pub bigint_bytes_len: u32,
    pub table_split_cycle: u32,
}

#[repr(C)]
pub struct RawBuffer {
    pub buf: *const BabyBearElem,
    pub rows: usize,
    pub cols: usize,
    pub checked: bool,
}

#[repr(C)]
pub struct RawExecBuffers {
    pub global: RawBuffer,
    pub data: RawBuffer,
}

#[repr(C)]
pub struct RawAccumBuffers {
    pub data: RawBuffer,
    pub accum: RawBuffer,
    pub global: RawBuffer,
    pub mix: RawBuffer,
}

unsafe extern "C" {
    pub fn risc0_circuit_rv32im_cpu_witgen(
        mode: u32,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_rv32im_cpu_accum(
        buffers: *const RawAccumBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_rv32im_cpu_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mixs: *const BabyBearExtElem,
        args_ptr: *const *const BabyBearElem,
        result: *mut BabyBearExtElem,
    ) -> *const std::os::raw::c_char;
}

#[cfg(feature = "cuda")]
unsafe extern "C" {
    pub fn risc0_circuit_rv32im_cuda_witgen(
        mode: u32,
        buffers: *const RawExecBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_rv32im_cuda_accum(
        buffers: *const RawAccumBuffers,
        preflight: *const RawPreflightTrace,
        cycles: u32,
    ) -> *const std::os::raw::c_char;

    pub fn risc0_circuit_rv32im_cuda_eval_check(
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
}
