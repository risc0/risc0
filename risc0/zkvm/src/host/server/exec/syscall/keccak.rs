// Copyright 2025 RISC Zero, Inc.
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

use crate::host::client::env::ProveKeccakRequest;
use anyhow::{Result, bail};
use risc0_binfmt::ByteAddr;
use risc0_circuit_keccak::{KECCAK_DEFAULT_PO2, KeccakState, max_keccak_inputs};
use risc0_circuit_rv32im::execute::MAX_IO_BYTES;
use risc0_zkvm_platform::syscall::{
    keccak_mode::{KECCAK_PERMUTE, KECCAK_PROVE},
    reg_abi::*,
};

use super::{Syscall, SyscallContext, SyscallKind};

#[derive(Clone, Default)]
pub(crate) struct SysKeccak {
    inputs: Vec<KeccakState>,
    max_po2: usize,
    max_inputs: usize,
}

impl Syscall for SysKeccak {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mode = ctx.load_register(REG_A3);
        if mode == KECCAK_PERMUTE {
            self.keccak_permute(ctx, to_guest)
        } else if mode == KECCAK_PROVE {
            self.keccak_prove(ctx, to_guest)
        } else {
            bail!("sys_keccak: invalid mode: {mode}")
        }
    }
}

impl SysKeccak {
    pub fn new(max_po2: Option<u32>) -> Self {
        let max_po2 = max_po2.unwrap_or(KECCAK_DEFAULT_PO2 as u32) as usize;

        Self {
            inputs: vec![],
            max_po2,
            max_inputs: max_keccak_inputs(max_po2),
        }
    }

    fn is_full(&self) -> bool {
        self.inputs.len() >= self.max_inputs
    }

    fn keccak_permute(
        &mut self,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        // if we are full at this point, it means that the guest forgot to call prove.
        if self.is_full() {
            bail!("keccak batch is full, prove must be called");
        }

        if to_guest.len() >= MAX_IO_BYTES as usize {
            bail!("invalid sys_keccak_permute");
        }

        let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
        let from_guest = &ctx.load_region(buf_ptr, 25 * 8)?;
        let mut from_guest: KeccakState = bytemuck::cast_slice(from_guest).try_into()?;
        self.inputs.push(from_guest);

        keccak::f1600(&mut from_guest);
        to_guest.clone_from_slice(bytemuck::cast_slice(&from_guest));

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::Keccak];
        metric.count += 1;

        // if full, the guest must call prove.
        Ok((self.is_full() as u32, 0))
    }

    fn keccak_prove(
        &mut self,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_keccak_prove");
        }

        let claim = ctx.load_digest_from_register(REG_A4)?;
        let control_root = ctx.load_digest_from_register(REG_A5)?;

        let proof_request = ProveKeccakRequest {
            claim_digest: claim,
            control_root,
            input: self.inputs.clone(),
            po2: self.max_po2,
        };

        if let Some(coprocessor) = &ctx.syscall_table().coprocessor {
            coprocessor.borrow_mut().prove_keccak(proof_request)?;
        } else {
            ctx.syscall_table()
                .pending_keccaks
                .borrow_mut()
                .push(proof_request);
        }

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::ProveKeccak];
        metric.count += 1;
        metric.size += 1 << self.max_po2 as u64;

        // reset
        self.inputs.clear();

        Ok((0, 0))
    }
}
