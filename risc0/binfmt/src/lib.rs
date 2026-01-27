// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Manages formatted binaries used by the RISC Zero zkVM

#![cfg_attr(all(not(feature = "std"), not(test)), no_std)]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg))]

mod addr;
mod elf;
mod exit_code;
mod hash;
mod image;
mod povw;
mod sys_state;

use anyhow::Result;
use risc0_zkp::core::digest::Digest;

pub use self::image::{KERNEL_START_ADDR, MemoryImage, Page};

pub use crate::{
    addr::{ByteAddr, WordAddr},
    elf::{AbiKind, Program, ProgramBinary, ProgramBinaryHeader},
    exit_code::{ExitCode, InvalidExitCodeError},
    hash::{Digestible, tagged_iter, tagged_list, tagged_list_cons, tagged_struct},
    povw::{PovwJobId, PovwLogId, PovwNonce},
    sys_state::{DecodeError, SystemState, read_sha_halfs, write_sha_halfs},
};

pub(crate) const WORD_SIZE: usize = 4;
const PAGE_BYTES: usize = 1024;
pub(crate) const PAGE_WORDS: usize = PAGE_BYTES / WORD_SIZE;

/// Compute and return the ImageID of the specified combined user ELF + kernel ELF binary.
pub fn compute_image_id(blob: &[u8]) -> Result<Digest> {
    ProgramBinary::decode(blob)?.compute_image_id()
}

/// Compute and return the kernel ID of the specified binary.
///
/// The given binary is expected to be a combined user ELF + kernel ELF binary. The returned digest
/// is of the kernel, and is constant with respect to the user program.
pub fn compute_kernel_id(blob: &[u8]) -> Result<Digest> {
    ProgramBinary::decode(blob)?.kernel_id()
}
