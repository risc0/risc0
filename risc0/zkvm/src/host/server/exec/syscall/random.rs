// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
