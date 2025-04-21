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

use std::{cmp::min, collections::HashMap};

use anyhow::{bail, Result};
use risc0_binfmt::ByteAddr;
use risc0_circuit_rv32im::execute::MAX_IO_BYTES;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A3, REG_A4},
    WORD_SIZE,
};

use super::{Syscall, SyscallContext};

pub(crate) struct SysGetenv(pub HashMap<String, String>);
impl Syscall for SysGetenv {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = std::str::from_utf8(&from_guest)?;

        match self.0.get(msg) {
            None => Ok((u32::MAX, 0)),
            Some(val) => {
                let nbytes = min(to_guest.len() * WORD_SIZE, val.len());
                let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                to_guest_u8s[0..nbytes].clone_from_slice(&val.as_bytes()[0..nbytes]);

                if val.len() >= MAX_IO_BYTES as usize {
                    bail!("sys_getenv failure: value is too large");
                }

                Ok((val.len() as u32, 0))
            }
        }
    }
}
