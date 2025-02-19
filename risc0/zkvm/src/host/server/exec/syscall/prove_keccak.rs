// Copyright 2025 RISC Zero, Inc.
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

// Manages system calls for accelerators and other proof composition

use anyhow::Result;
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::{syscall::reg_abi::*, WORD_SIZE};

use crate::{
    host::{api::convert::try_keccak_bytes_to_input, client::env::ProveKeccakRequest},
    Assumption, AssumptionReceipt,
};

use super::{Syscall, SyscallContext, SyscallKind};

#[derive(Clone)]
pub(crate) struct SysProveKeccak;

impl Syscall for SysProveKeccak {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let claim = ctx.load_digest_from_register(REG_A3)?;
        let po2 = ctx.load_register(REG_A4) as usize;
        let control_root = ctx.load_digest_from_register(REG_A5)?;
        let input_ptr = ByteAddr(ctx.load_register(REG_A6));
        let input_len = ctx.load_register(REG_A7);
        let input: Vec<u8> = ctx.load_region(input_ptr, input_len * WORD_SIZE as u32)?;
        let input = try_keccak_bytes_to_input(&input)?;

        let proof_request = ProveKeccakRequest {
            claim_digest: claim,
            po2,
            control_root,
            input,
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
        metric.size += 1 << po2 as u64;

        Ok((0, 0))
    }
}
