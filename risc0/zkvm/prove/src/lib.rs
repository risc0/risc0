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

use anyhow::Result;
use cxx::{let_cxx_string, UniquePtr};

#[cxx::bridge(namespace = "risc0::rust")]
mod ffi {
    unsafe extern "C++" {
        include!("risc0/zkvm/prove/method_id.h");

        type MethodID;

        fn new_method_id(elf_path: &CxxString) -> Result<UniquePtr<MethodID>>;
        fn write(&self, filename: &CxxString) -> Result<()>;
    }
}

pub struct MethodID {
    raw: UniquePtr<ffi::MethodID>,
}

impl MethodID {
    pub fn new(elf_path: &str) -> Result<Self> {
        let_cxx_string!(elf_path = elf_path);
        let raw = ffi::new_method_id(&elf_path)?;
        Ok(MethodID { raw })
    }

    pub fn write(&self, filename: &str) -> Result<()> {
        let_cxx_string!(filename = filename);
        Ok(self.raw.write(&filename)?)
    }
}
