// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#[cfg(feature = "cuda")]
pub mod cuda;

use std::ffi::CStr;

use anyhow::{Result, anyhow};

#[repr(C)]
pub struct CppError {
    msg: *const std::os::raw::c_char,
}

impl Drop for CppError {
    fn drop(&mut self) {
        unsafe extern "C" {
            fn free(str: *const std::os::raw::c_char);
        }
        unsafe { free(self.msg) };
    }
}

impl Default for CppError {
    fn default() -> Self {
        Self {
            msg: std::ptr::null(),
        }
    }
}

impl CppError {
    pub fn unwrap(self) {
        if !self.msg.is_null() {
            let c_str = unsafe { std::ffi::CStr::from_ptr(self.msg) };
            panic!("{}", c_str.to_str().unwrap_or("unknown error"));
        }
    }
}

pub fn ffi_wrap<F>(mut inner: F) -> Result<()>
where
    F: FnMut() -> *const std::os::raw::c_char,
{
    unsafe extern "C" {
        fn free(str: *const std::os::raw::c_char);
    }

    let c_ptr = inner();
    if c_ptr.is_null() {
        Ok(())
    } else {
        let what = unsafe {
            let msg = CStr::from_ptr(c_ptr)
                .to_str()
                .unwrap_or("Invalid error msg pointer")
                .to_string();
            free(c_ptr);
            msg
        };
        Err(anyhow!(what))
    }
}
