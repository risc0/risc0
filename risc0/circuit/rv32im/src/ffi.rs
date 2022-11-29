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

use std::{
    ffi::CStr,
    os::raw::{c_char, c_void},
    slice,
};

use anyhow::{anyhow, Result};
use risc0_zkp::{
    adapter::{CircuitStepContext, CircuitStepHandler},
    field::baby_bear::{BabyBearElem, BabyBearExtElem},
};

type Callback = unsafe extern "C" fn(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const BabyBearElem,
    args_len: usize,
    outs_ptr: *mut BabyBearElem,
    outs_len: usize,
) -> bool;

pub(crate) enum RawString {}

#[repr(C)]
pub(crate) struct RawError {
    pub(crate) msg: *const RawString,
}

impl Default for RawError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

extern "C" {
    pub(crate) fn risc0_circuit_string_ptr(str: *const RawString) -> *const c_char;

    pub(crate) fn risc0_circuit_string_free(str: *const RawString);

    pub(crate) fn risc0_circuit_rv32im_step_compute_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub(crate) fn risc0_circuit_rv32im_step_verify_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub(crate) fn risc0_circuit_rv32im_step_exec(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub(crate) fn risc0_circuit_rv32im_step_verify_bytes(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub(crate) fn risc0_circuit_rv32im_step_verify_mem(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut BabyBearElem,
        args_len: usize,
    ) -> BabyBearElem;

    pub(crate) fn risc0_circuit_rv32im_poly_fp(
        cycle: usize,
        steps: usize,
        poly_mix: *const BabyBearExtElem,
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

pub(crate) fn call_step<S, F>(
    ctx: &CircuitStepContext,
    handler: &mut S,
    args: &mut [&mut [BabyBearElem]],
    inner: F,
) -> Result<BabyBearElem>
where
    S: CircuitStepHandler<BabyBearElem>,
    F: FnOnce(
        *mut RawError,
        *mut c_void,
        Callback,
        usize,
        usize,
        *const *mut BabyBearElem,
        usize,
    ) -> BabyBearElem,
{
    let mut last_err = None;
    let mut call =
        |name: &str, extra: &str, args: &[BabyBearElem], outs: &mut [BabyBearElem]| match handler
            .call(ctx.cycle, name, extra, args, outs)
        {
            Ok(()) => true,
            Err(err) => {
                last_err = Some(err);
                false
            }
        };
    let trampoline = get_trampoline(&call);
    let mut err = RawError::default();
    let args: Vec<*mut BabyBearElem> = args.iter_mut().map(|x| (*x).as_mut_ptr()).collect();
    let result = inner(
        &mut err,
        &mut call as *mut _ as *mut c_void,
        trampoline,
        ctx.size,
        ctx.cycle,
        args.as_ptr(),
        args.len(),
    );
    if let Some(err) = last_err {
        return Err(err);
    }
    if err.msg.is_null() {
        Ok(result)
    } else {
        let what = unsafe {
            let str = risc0_circuit_string_ptr(err.msg);
            let msg = CStr::from_ptr(str).to_str().unwrap().to_string();
            risc0_circuit_string_free(err.msg);
            msg
        };
        Err(anyhow!(what))
    }
}
