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

use anyhow::bail;
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::syscall::keccak::{ABSORB, CLOSE, OPEN, SQUEEZE};
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4, REG_A5, REG_A6};
use risc0_zkvm_platform::WORD_SIZE;
use std::collections::BTreeMap;

use tiny_keccak::Hasher;
use tiny_keccak::Keccak;

use super::{Syscall, SyscallContext};

#[derive(Clone, Default)]
pub(crate) struct SysKeccak {
    next_id: u32,
    hasher_data: BTreeMap<u32, (u8, Vec<u8>)>,
}

impl Syscall for SysKeccak {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> anyhow::Result<(u32, u32)> {
        let mode = ctx.load_register(REG_A3);

        if mode == ABSORB {
            self.absorb(ctx)
        } else if mode == SQUEEZE {
            self.squeeze(ctx, to_guest)
        } else if mode == OPEN {
            self.open(ctx)
        } else if mode == CLOSE {
            self.close(ctx)
        } else {
            Err(anyhow::anyhow!("Unsupported keccak mode {}", mode))
        }
    }
}

impl SysKeccak {
    fn open(&mut self, ctx: &mut dyn SyscallContext) -> anyhow::Result<(u32, u32)> {
        if self.hasher_data.len() == u32::MAX as usize {
            bail!("max number of hashers reached");
        }
        let key = self.next_id;
        if self.hasher_data.contains_key(&key) {
            bail!("hasher ID {key} already exists")
        }

        let hasher_type = ctx.load_register(REG_A4);
        if hasher_type != 0x01 {
            // TODO: allow sha3
            bail!("unsupported hasher delimitor {hasher_type:#x}")
        }
        self.hasher_data.insert(key, (hasher_type as u8, vec![]));
        self.next_id += 1;
        Ok((0, 0))
    }

    fn close(&mut self, ctx: &mut dyn SyscallContext) -> anyhow::Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A6);
        match self.hasher_data.remove(&fd) {
            Some(_) => Ok((0, 0)),
            None => bail!("hasher ID {fd} does not exist, cannot close"),
        }
    }

    // This writes raw data to be hashed. Invoked during `hasher.update(data)` in cryptographic hashing crates in the guest.
    fn absorb(&mut self, ctx: &mut dyn SyscallContext) -> anyhow::Result<(u32, u32)> {
        let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
        let buf_len = ctx.load_register(REG_A5);
        tracing::debug!("SYS_KECCAK: absorb {buf_len} bytes");
        let mut from_guest = ctx.load_region(buf_ptr, buf_len)?;

        let fd = ctx.load_register(REG_A6);

        let data = match self.hasher_data.get_mut(&fd) {
            Some((_, data)) => data,
            None => bail!("unknown keccak fd: {}", 0),
        };
        data.append(&mut from_guest);
        Ok((0, 0))
    }

    // read the keccak hash. Invoked during `hasher.finalize(output)` in cryptographic hashing crates in the guest.
    fn squeeze(
        &mut self,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> anyhow::Result<(u32, u32)> {
        tracing::debug!("SYS_KECCAK: squeeze");
        let mut hasher = Keccak::v256();

        let fd = ctx.load_register(REG_A6);
        let data = match self.hasher_data.get(&fd) {
            Some((0x01, data)) => data,
            Some((hasher_type, _)) => {
                bail!("unsupported hasher type with delimitor: {:#x}", hasher_type)
            }
            None => bail!("unknown keccak fd: {}", fd),
        };
        hasher.update(data);
        let mut out_buf = vec![0u8; to_guest.len() * WORD_SIZE];
        hasher.finalize(&mut out_buf);
        bytemuck::cast_slice_mut(to_guest).clone_from_slice(out_buf.as_slice());
        Ok((0, 0))
    }
}
