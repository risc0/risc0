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
    adapter::{CircuitStepContext, CustomStep},
    core::fp::Fp,
};

type Callback = unsafe extern "C" fn(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const Fp,
    args_len: usize,
    ok: &mut bool,
    result_ptr: *mut Fp,
    result_len: usize,
);

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

    pub(crate) fn risc0_circuit_rv32im_step_accum(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut Fp,
        args_len: usize,
    ) -> Fp;

    pub(crate) fn risc0_circuit_rv32im_step_exec(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut Fp,
        args_len: usize,
    ) -> Fp;

    pub(crate) fn risc0_circuit_rv32im_step_verify(
        err: *mut RawError,
        ctx: *mut c_void,
        cb: Callback,
        steps: usize,
        cycle: usize,
        args_ptr: *const *mut Fp,
        args_len: usize,
    ) -> Fp;
}

pub fn get_trampoline<F>(_closure: &F) -> Callback
where
    F: FnMut(&str, &str, &[Fp], &mut bool, &mut [Fp]),
{
    trampoline::<F>
}

extern "C" fn trampoline<F>(
    ctx: *mut c_void,
    name: *const c_char,
    extra: *const c_char,
    args_ptr: *const Fp,
    args_len: usize,
    ok: &mut bool,
    result_ptr: *mut Fp,
    result_len: usize,
) where
    F: FnMut(&str, &str, &[Fp], &mut bool, &mut [Fp]),
{
    unsafe {
        let name = CStr::from_ptr(name).to_str().unwrap();
        let extra = CStr::from_ptr(extra).to_str().unwrap();
        let args = slice::from_raw_parts(args_ptr, args_len);
        let result = slice::from_raw_parts_mut(result_ptr, result_len);
        let callback = &mut *(ctx as *mut F);
        callback(name, extra, args, ok, result);
    }
}

pub(crate) struct CustomBridge<'a, S: CustomStep> {
    custom: &'a mut S,
}

impl<'a, S: CustomStep> CustomBridge<'a, S> {
    pub fn new(custom: &'a mut S) -> Self {
        Self { custom }
    }

    pub fn call(&mut self, name: &str, extra: &str, args: &[Fp], ok: &mut bool, result: &mut [Fp]) {
        match self.custom.call(name, extra, args) {
            Ok(value) => {
                *ok = true;
                for i in 0..value.len() {
                    result[i] = value[i];
                }
            }
            Err(_err) => {
                *ok = false;
            }
        };
    }
}

pub(crate) fn call_step<S, F>(
    ctx: &CircuitStepContext,
    custom: &mut S,
    args: &mut [&mut [Fp]],
    inner: F,
) -> Result<Fp>
where
    S: CustomStep,
    F: FnOnce(*mut RawError, *mut c_void, Callback, usize, usize, *const *mut Fp, usize) -> Fp,
{
    let mut bridge = CustomBridge::new(custom);
    let mut call = |name: &str, extra: &str, args: &[Fp], ok: &mut bool, result: &mut [Fp]| {
        bridge.call(name, extra, args, ok, result);
    };
    let trampoline = get_trampoline(&call);
    let mut err = RawError::default();
    let args: Vec<*mut Fp> = args.iter_mut().map(|x| (*x).as_mut_ptr()).collect();
    let result = inner(
        &mut err,
        &mut call as *mut _ as *mut c_void,
        trampoline,
        ctx.size,
        ctx.cycle,
        args.as_ptr(),
        args.len(),
    );
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
