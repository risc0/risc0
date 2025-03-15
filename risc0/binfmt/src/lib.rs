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
mod image;
mod sys_state;

use anyhow::Result;
use risc0_zkp::core::digest::Digest;

pub use self::image::{MemoryImage, Page, KERNEL_START_ADDR};

pub use crate::{
    addr::{ByteAddr, WordAddr},
    elf::{AbiKind, Program, ProgramBinary, ProgramBinaryHeader},
    exit_code::{ExitCode, InvalidExitCodeError},
    hash::{tagged_iter, tagged_list, tagged_list_cons, tagged_struct, Digestible},
    sys_state::{read_sha_halfs, write_sha_halfs, DecodeError, SystemState},
};

pub(crate) const WORD_SIZE: usize = 4;
const PAGE_BYTES: usize = 1024;
pub(crate) const PAGE_WORDS: usize = PAGE_BYTES / WORD_SIZE;

/// Compute and return the ImageID of the specified combined user ELF + kernel ELF binary.
pub fn compute_image_id(blob: &[u8]) -> Result<Digest> {
    ProgramBinary::decode(blob)?.compute_image_id()
}
