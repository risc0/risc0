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

//! Manages formatted binaries used by the RISC Zero zkVM

#![cfg_attr(all(not(feature = "std"), not(test)), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod addr;
mod elf;
mod exit_code;
mod hash;
#[cfg(not(target_os = "zkvm"))]
mod image;
#[cfg(feature = "std")]
mod image2;
mod sys_state;

use borsh::{BorshDeserialize, BorshSerialize};
use serde::{Deserialize, Serialize};

#[cfg(not(target_os = "zkvm"))]
pub use self::image::{MemoryImage, PageTableInfo};

#[cfg(feature = "std")]
pub use self::image2::{MemoryImage2, Page, KERNEL_START_ADDR};

pub use crate::{
    addr::{ByteAddr, WordAddr},
    elf::Program,
    exit_code::{ExitCode, InvalidExitCodeError},
    hash::{tagged_iter, tagged_list, tagged_list_cons, tagged_struct, Digestible},
    sys_state::{read_sha_halfs, write_sha_halfs, DecodeError, SystemState},
};

pub(crate) const WORD_SIZE: usize = 4;
const PAGE_BYTES: usize = 1024;
pub(crate) const PAGE_WORDS: usize = PAGE_BYTES / WORD_SIZE;

/// Compute and return the ImageID of the specified ELF binary.
#[cfg(not(target_os = "zkvm"))]
pub fn compute_image_id(elf: &[u8]) -> anyhow::Result<risc0_zkp::core::digest::Digest> {
    use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};

    let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
    let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
    Ok(image.compute_id())
}

/// Compute and return the ImageID of the user-mode portion of the specified ELF binary.
#[cfg(feature = "std")]
pub fn compute_user_id_v2(elf: &[u8]) -> anyhow::Result<risc0_zkp::core::digest::Digest> {
    let program = Program::load_elf(elf, KERNEL_START_ADDR.0)?;
    let mut image = MemoryImage2::new_user(program);
    Ok(image.user_id())
}

/// Compute and return the ImageID of the kernel-mode portion of the specified ELF binary.
#[cfg(feature = "std")]
pub fn compute_kernel_id_v2(elf: &[u8]) -> anyhow::Result<risc0_zkp::core::digest::Digest> {
    let program = Program::load_elf(elf, u32::MAX)?;
    let mut image = MemoryImage2::new_kernel(program);
    Ok(image.kernel_id())
}

/// Compute and return the ImageID of the user-mode portion of the specified ELF binary.
#[cfg(feature = "std")]
pub fn compute_image_id_v2(
    user_id: impl Into<risc0_zkp::core::digest::Digest>,
    kernel_id: impl Into<risc0_zkp::core::digest::Digest>,
) -> anyhow::Result<risc0_zkp::core::digest::Digest> {
    use crate::Digestible;
    use risc0_zkp::core::hash::sha::Impl;

    let merkle_root = self::image2::DigestPair {
        lhs: user_id.into(),
        rhs: kernel_id.into(),
    }
    .digest();
    Ok(SystemState { pc: 0, merkle_root }.digest::<Impl>())
}

/// TODO(flaub)
#[derive(
    Clone, Copy, Debug, Eq, Serialize, Deserialize, BorshSerialize, BorshDeserialize, PartialEq,
)]
pub enum SegmentVersion {
    /// TODO(flaub)
    V1,

    /// TODO(flaub)
    V2,
}

/// TODO(flaub)
#[cfg(feature = "std")]
pub fn risc0_rv32im_ver() -> Option<SegmentVersion> {
    let version = std::env::var("RISC0_RV32IM_VER").unwrap_or_default();
    match version.as_str() {
        "1" => Some(SegmentVersion::V1),
        "2" => Some(SegmentVersion::V2),
        _ => None,
    }
}
