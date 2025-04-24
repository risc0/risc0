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

use anyhow::Result;
use risc0_zkvm_platform::WORD_SIZE;

use super::{Syscall, SyscallContext};

pub(crate) struct SysRandom;
impl Syscall for SysRandom {
    fn syscall(
        &mut self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        tracing::debug!("SYS_RANDOM: {}", to_guest.len());
        let mut rand_buf = vec![0u8; to_guest.len() * WORD_SIZE];
        rand::fill(rand_buf.as_mut_slice());
        bytemuck::cast_slice_mut(to_guest).clone_from_slice(rand_buf.as_slice());
        Ok(((to_guest.len() * WORD_SIZE) as u32, 0))
    }
}
