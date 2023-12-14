// Copyright 2023 RISC Zero, Inc.
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

#[cfg(any(feature = "client", feature = "prove"))]
pub(crate) mod api;
#[cfg(feature = "client")]
pub(crate) mod client;
pub(crate) mod groth16;
pub(crate) mod receipt;
pub(crate) mod recursion;
#[cfg(feature = "prove")]
pub(crate) mod server;

use anyhow::Result;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};

use crate::sha::Digest;

#[cfg(any(feature = "client", feature = "prove"))]
mod protos {
    pub(crate) mod api {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.api.rs"));
    }

    pub(crate) mod base {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.base.rs"));
    }

    pub(crate) mod core {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.core.rs"));
    }
}

/// Compute and return the ImageID of the specified ELF binary.
pub fn compute_image_id(elf: &[u8]) -> Result<Digest> {
    let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
    let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
    image.compute_id()
}
