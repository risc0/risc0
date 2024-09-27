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

use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4, REG_A5};
use risc0_zkvm_platform::WORD_SIZE;

use tiny_keccak::Hasher;
use tiny_keccak::Keccak;

use super::{Syscall, SyscallContext};

#[derive(Clone, Default)]
pub(crate) struct SysKeccak(Vec<u8>);

impl Syscall for SysKeccak {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> anyhow::Result<(u32, u32)> {
        let mode = ctx.load_register(REG_A3);
        if mode == risc0_zkvm_platform::syscall::keccak::WRITE {
            // This writes raw data to be hashed. Invoked during `hasher.update(data)` in cryptographic hashing crates in the guest.
            let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
            let buf_len = ctx.load_register(REG_A5);
            tracing::debug!("SYS_KECCAK: write {buf_len} bytes");
            let mut from_guest = ctx.load_region(buf_ptr, buf_len)?;
            self.0.append(&mut from_guest);
            Ok((0, 0))
        } else if mode == risc0_zkvm_platform::syscall::keccak::READ {
            // read the keccak hash. Invoked during `hasher.finalize(output)` in cryptographic hashing crates in the guest.
            tracing::debug!("SYS_KECCAK: read");
            let mut hasher = Keccak::v256();
            hasher.update(&self.0);
            let mut out_buf = vec![0u8; to_guest.len() * WORD_SIZE];
            hasher.finalize(&mut out_buf);
            bytemuck::cast_slice_mut(to_guest).clone_from_slice(out_buf.as_slice());
            Ok((0, 0))
        } else {
            Err(anyhow::anyhow!("Unsupported keccak mode {}", mode))
        }
    }
}
