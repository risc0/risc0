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

use anyhow::{bail, Result};
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_circuit_keccak::{KECCAK_DEFAULT_PO2, KeccakState, max_keccak_inputs};
use risc0_zkvm_platform::{syscall::reg_abi::*};

use crate::{host::client::env::ProveKeccakRequest, Assumption, AssumptionReceipt};

use super::{Syscall, SyscallContext, SyscallKind};

#[derive(Clone, Default)]
pub(crate) struct SysKeccak {
    inputs: Vec<KeccakState>,
    max_po2: usize,
    max_inputs: usize,
}

const PERMUTE: u32 = 1;
const PROVE: u32 = 2;

impl Syscall for SysKeccak {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mode = ctx.load_register(REG_A3);
        if mode == PERMUTE {
            self.keccak_permute(ctx, to_guest)
        } else if mode == PROVE {
            self.keccak_prove(ctx, to_guest)
        } else {
            bail!("sys_keccak: invalid mode: {mode}")
        }
    }
}

impl SysKeccak {
    pub fn new(max_po2: Option<u32>) -> Self {
        let max_po2 = match max_po2 {
            Some(po2) => po2 as usize,
            None => KECCAK_DEFAULT_PO2,
        };

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
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let claim = ctx.load_digest_from_register(REG_A4)?;
        let control_root = ctx.load_digest_from_register(REG_A5)?;

        let proof_request = ProveKeccakRequest {
            claim_digest: claim,
            control_root,
            input: bytemuck::cast_slice(self.inputs.as_slice()).to_vec(),
            po2: self.max_po2 as usize,
        };

        if let Some(coprocessor) = &ctx.syscall_table().coprocessor {
            coprocessor.borrow_mut().prove_keccak(proof_request)?;
        } else {
            ctx.syscall_table()
                .pending_keccaks
                .borrow_mut()
                .push(proof_request);
        }

        let assumption = Assumption {
            claim,
            control_root,
        };

        ctx.syscall_table()
            .assumptions
            .borrow_mut()
            .0
            .push(AssumptionReceipt::Unresolved(assumption));

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::ProveKeccak];
        metric.count += 1;
        metric.size += 1 << self.max_po2 as u64;

        // reset
        self.inputs.clear();

        Ok((0, 0))
    }
}
