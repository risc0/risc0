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

//! Manages formatted binaries used by the RISC Zero zkVM

#![cfg_attr(all(not(feature = "std"), not(test)), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod elf;
mod exit_code;
mod hash;
#[cfg(not(target_os = "zkvm"))]
mod image;
mod sys_state;

#[cfg(not(target_os = "zkvm"))]
pub use self::image::{MemoryImage, PageTableInfo};
pub use crate::{
    elf::Program,
    exit_code::{ExitCode, InvalidExitCodeError},
    hash::{tagged_iter, tagged_list, tagged_list_cons, tagged_struct, Digestible},
    sys_state::{read_sha_halfs, write_sha_halfs, DecodeError, SystemState},
};

/// Compute and return the ImageID of the specified ELF binary.
#[cfg(not(target_os = "zkvm"))]
pub fn compute_image_id(elf: &[u8]) -> anyhow::Result<risc0_zkp::core::digest::Digest> {
    use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};

    let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
    let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
    Ok(image.compute_id())
}
