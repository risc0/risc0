#![feature(extern_types)]
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

#[cxx::bridge(namespace = "risc0")]
pub mod ffi {
    unsafe extern "C++" {
        include!("risc0/zkvm/prove/method_id.h");

        type MethodID;

        // How do I get this constexpr from C++?
        //static DIGEST_BYTES: usize;

        fn method_id_from_elf(path: &CxxString) -> Result<UniquePtr<MethodID>>;
        fn method_id_from_bytes(bytes: &[u8; 384]) -> Result<UniquePtr<MethodID>>;

        fn toBytes(self: &MethodID) -> Result<[u8; 384]>;
    }
}

pub struct MethodID {
    raw: UniquePtr<ffi::MethodID>,
}

impl MethodID {
    pub fn from_elf(path: &str) -> Result<Self> {
        let_cxx_string!(cxx_path = path);
        ffi::method_id_from_elf(&cxx_path)
            .map_err(|err| Error::msg(format!("{}", err.what())))
            .map(|raw| MethodID { raw })
    }

    pub fn from_bytes(bytes: &[u8; 384]) -> Result<Self> {
        ffi::method_id_from_bytes(bytes)
            .map_err(|err| Error::msg(format!("{}", err.what())))
            .map(|raw| MethodID { raw })
    }

    pub fn to_bytes(&self) -> Result<[u8; 384]> {
        return self
            .raw
            .toBytes()
            .map_err(|err| Error::msg(format!("{}", err.what())));
    }
}
