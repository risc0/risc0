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

//! This module implements functionality that mirrors the `getrandom` crate.
//! This mod serves as a temporary solution to provide a "batteries
//! included" implementation to use getrandom directly in the guest
//! without modifications.

use alloc::vec;

use anyhow::Error;
use risc0_zkvm_platform::syscall::sys_rand;
use risc0_zkvm_platform::WORD_SIZE;

/// this getrandom function fills the buffer with contents from zkVM's
/// sys_rand function.
pub fn getrandom(dest: &mut [u8]) -> Result<(), Error> {
    if dest.is_empty() {
        return Ok(());
    }

    let words = (dest.len() + WORD_SIZE - 1) / WORD_SIZE;
    let mut buf = vec![0u32; words];
    unsafe {
        sys_rand(buf.as_mut_ptr(), words);
    }
    dest.clone_from_slice(&bytemuck::cast_slice(buf.as_slice())[..dest.len()]);
    Ok(())
}
