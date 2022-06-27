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

use std::{ffi::CStr, os::raw::c_char};

use super::exception::Exception;

pub(crate) enum RawString {}
pub(crate) enum RawProver {}
pub(crate) enum RawReceipt {}
pub(crate) enum RawMethodId {}

#[repr(C)]
pub(crate) struct RawError {
    msg: *const RawString,
}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

#[inline]
pub(crate) fn check<T, F>(err: RawError, ok: F) -> super::Result<T>
where
    F: FnOnce() -> T,
{
    if err.msg.is_null() {
        Ok(ok())
    } else {
        let what = unsafe {
            let str = risc0_string_ptr(err.msg);
            let msg = CStr::from_ptr(str).to_str().unwrap().to_string();
            risc0_string_free(err.msg);
            msg
        };
        Err(Exception { what })
    }
}

extern "C" {
    pub(crate) fn risc0_init();

    pub(crate) fn risc0_string_ptr(str: *const RawString) -> *const c_char;

    pub(crate) fn risc0_string_free(str: *const RawString);

    pub(crate) fn risc0_method_id_compute(
        err: *mut RawError,
        elf_contents: *const u8,
        elf_len: usize,
        limit: u32,
    ) -> *const RawMethodId;

    pub(crate) fn risc0_method_id_load(
        err: *mut RawError,
        bytes: *const u8,
        len: usize,
    ) -> *const RawMethodId;

    pub(crate) fn risc0_method_id_get_buf(
        err: *mut RawError,
        ptr: *const RawMethodId,
        len: *mut u32,
    ) -> *const u8;

    pub(crate) fn risc0_method_id_free(err: *mut RawError, ptr: *const RawMethodId);

    pub(crate) fn risc0_prover_new(
        err: *mut RawError,
        elf_bytes: *const u8,
        elf_len: usize,
        method_id: *const u8,
        method_id_len: usize,
    ) -> *mut RawProver;

    pub(crate) fn risc0_prover_free(err: *mut RawError, prover: *mut RawProver);

    pub(crate) fn risc0_prover_add_input(
        err: *mut RawError,
        prover: *mut RawProver,
        buf: *const u8,
        len: usize,
    );

    pub(crate) fn risc0_prover_get_output_buf(
        err: *mut RawError,
        prover: *mut RawProver,
    ) -> *const u8;

    pub(crate) fn risc0_prover_get_output_len(err: *mut RawError, prover: *mut RawProver) -> usize;

    pub(crate) fn risc0_prover_run(err: *mut RawError, prover: *mut RawProver)
        -> *const RawReceipt;

    pub(crate) fn risc0_receipt_new(
        err: *mut RawError,
        journal: *const u8,
        journal_len: usize,
        seal: *const u32,
        seal_len: usize,
    ) -> *const RawReceipt;

    pub(crate) fn risc0_receipt_verify(
        err: *mut RawError,
        receipt: *const RawReceipt,
        method_id: *const u8,
        method_id_len: usize,
    );

    pub(crate) fn risc0_receipt_get_seal_buf(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> *mut u32;

    pub(crate) fn risc0_receipt_get_seal_len(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> usize;

    pub(crate) fn risc0_receipt_get_journal_buf(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> *const u8;

    pub(crate) fn risc0_receipt_get_journal_len(
        err: *mut RawError,
        receipt: *const RawReceipt,
    ) -> usize;

    pub(crate) fn risc0_receipt_free(err: *mut RawError, receipt: *const RawReceipt);
}
