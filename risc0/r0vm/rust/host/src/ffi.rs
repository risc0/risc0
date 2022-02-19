use std::{ffi::CStr, os::raw::c_char};

use crate::exception::Exception;

pub(crate) enum RawString {}
pub(crate) enum RawProver {}
pub(crate) enum RawProof {}

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
pub(crate) fn check<T, F>(err: RawError, ok: F) -> crate::Result<T>
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

    pub(crate) fn risc0_prover_new(err: *mut RawError, elf_path: *const i8) -> *mut RawProver;

    pub(crate) fn risc0_prover_free(err: *mut RawError, prover: *mut RawProver);

    pub(crate) fn risc0_prover_add_input(
        err: *mut RawError,
        prover: *mut RawProver,
        buf: *const u8,
        len: usize,
    );

    pub(crate) fn risc0_prover_get_num_outputs(err: *mut RawError, prover: *mut RawProver)
        -> usize;

    pub(crate) fn risc0_prover_get_output(
        err: *mut RawError,
        prover: *mut RawProver,
        idx: usize,
        len: usize,
    ) -> *const u8;

    pub(crate) fn risc0_prover_run(err: *mut RawError, prover: *mut RawProver) -> *const RawProof;

    pub(crate) fn risc0_proof_verify(err: *mut RawError, proof: *const RawProof);

    pub(crate) fn risc0_proof_get_core_buf(err: *mut RawError, proof: *const RawProof) -> *mut u32;

    pub(crate) fn risc0_proof_get_core_len(err: *mut RawError, proof: *const RawProof) -> usize;

    pub(crate) fn risc0_proof_get_message_buf(
        err: *mut RawError,
        proof: *const RawProof,
    ) -> *const u8;

    pub(crate) fn risc0_proof_get_message_len(err: *mut RawError, proof: *const RawProof) -> usize;

    pub(crate) fn risc0_proof_free(err: *mut RawError, proof: *const RawProof);
}
