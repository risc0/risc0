// Copyright 2025 RISC Zero, Inc.
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
