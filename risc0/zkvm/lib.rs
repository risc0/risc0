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

use anyhow::{Error, Result};
use cxx::{let_cxx_string, UniquePtr};
use std::{slice, mem};


#[cxx::bridge(namespace = "risc0::rust")]
mod ffi {
    unsafe extern "C++" {
        include!("risc0/zkvm/prove/method_id.h");

        type MethodID;

        fn make_method_id(elf_path: &CxxString) -> Result<UniquePtr<MethodID>>;
    }
}

// Can we remove this?
pub struct MethodID {
    raw: UniquePtr<ffi::MethodID>,
}

impl MethodID {
    pub fn new(elf_path: &str) -> Result<Self> {
        let_cxx_string!(elf_path = elf_path);
        let raw = ffi::make_method_id(&elf_path)?;
        Ok(MethodID { raw })
    }

    pub unsafe fn to_bytes(&self) -> Result<&[u8]> {
        match self.raw.as_ref() {
            Some(method) => Ok(slice::from_raw_parts((method as *const ffi::MethodID) as *const u8, mem::size_of::<ffi::MethodID>())),
            None => Ok(&[]) // TODO: Fix
        }

    }
}