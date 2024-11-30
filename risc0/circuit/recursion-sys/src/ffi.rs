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

use std::{
    ffi::CStr,
    os::raw::{c_char, c_void},
    slice,
};

use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

pub type Callback = unsafe extern "C" fn(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const BabyBearElem,
    args_len: usize,
    outs_ptr: *mut BabyBearElem,
    outs_len: usize,
) -> bool;

pub enum RawString {}

#[repr(C)]
pub struct RawError {
    pub msg: *const RawString,
}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

extern "C" {
    pub fn risc0_circuit_recursion_string_ptr(str: *const RawString) -> *const c_char;

    pub fn risc0_circuit_recursion_string_free(str: *const RawString);

    pub fn risc0_circuit_recursion_step_compute_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub fn risc0_circuit_recursion_step_verify_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub fn risc0_circuit_recursion_step_exec(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub fn risc0_circuit_recursion_step_verify_bytes(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub fn risc0_circuit_recursion_step_verify_mem(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub fn risc0_circuit_recursion_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mixs: *const BabyBearExtElem,
        args_ptr: *const *const BabyBearElem,
        args_len: usize,
    ) -> BabyBearExtElem;
}

pub fn get_trampoline<F>(_closure: &F) -> Callback
where
    F: FnMut(&str, &str, &[BabyBearElem], &mut [BabyBearElem]) -> bool,
{
    trampoline::<F>
}

extern "C" fn trampoline<F>(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const BabyBearElem,
    args_len: usize,
    outs_ptr: *mut BabyBearElem,
    outs_len: usize,
) -> bool
where
    F: FnMut(&str, &str, &[BabyBearElem], &mut [BabyBearElem]) -> bool,
{
    unsafe {
        let name = CStr::from_ptr(name).to_str().unwrap();
        let extra = CStr::from_ptr(extra).to_str().unwrap();
        let args = slice::from_raw_parts(args_ptr, args_len);
        let outs = slice::from_raw_parts_mut(outs_ptr, outs_len);
        let callback = &mut *(ctx as *mut F);
        callback(name, extra, args, outs)
    }
}
