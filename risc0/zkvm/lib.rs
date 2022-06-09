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
use cxx::let_cxx_string;

pub const METHOD_ID_LEN: usize = 384; // https://github.com/dtolnay/cxx/issues/1051
pub type MethodId = [u8; METHOD_ID_LEN];

#[cxx::bridge(namespace = "risc0")]
pub mod ffi {
    unsafe extern "C++" {
        include!("risc0/zkvm/prove/method_id.h");

        #[cxx_name = "makeMethodId"]
        fn make_method_id_from_elf(path: &CxxString) -> Result<[u8; 384]>;
    }
}

pub fn make_method_id_from_elf(path: &str) -> Result<MethodId> {
    let_cxx_string!(cxx_path = path);
    ffi::make_method_id_from_elf(&cxx_path)
        .map_err(|err| Error::msg(format!("{}", err.what())))
}
