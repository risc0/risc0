// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::cmp::min;

use anyhow::{Result, anyhow, bail};
use risc0_circuit_rv32im::execute::MAX_IO_BYTES;
use risc0_zkvm_platform::{
    WORD_SIZE,
    syscall::{
        nr::{SYS_ARGC, SYS_ARGV},
        reg_abi::REG_A3,
    },
};

use super::{Syscall, SyscallContext};

#[derive(Clone)]
pub(crate) struct SysArgs(pub Vec<String>);

impl Syscall for SysArgs {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if syscall == SYS_ARGC.as_str() {
            if !to_guest.is_empty() {
                bail!("invalid sys_argc call");
            }

            Ok((self.0.len().try_into()?, 0))
        } else if syscall == SYS_ARGV.as_str() {
            // Get the arg or return an error if out of bounds.
            let arg_index = ctx.load_register(REG_A3);
            let arg_val = self.0.get(arg_index as usize).ok_or_else(|| {
                anyhow!(
                    "guest requested index {arg_index} from argv of len {}",
                    self.0.len()
                )
            })?;

            let nbytes = min(to_guest.len() * WORD_SIZE, arg_val.len());
            let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
            to_guest_u8s[0..nbytes].clone_from_slice(&arg_val.as_bytes()[0..nbytes]);

            if arg_val.len() >= MAX_IO_BYTES as usize {
                bail!("sys_argv failure: argv is too large");
            }

            Ok((arg_val.len() as u32, 0))
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}
