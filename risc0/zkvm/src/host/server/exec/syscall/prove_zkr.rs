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

// Manages system calls for accelerators and other proof composition

use anyhow::{bail, Result};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A3, REG_A4, REG_A5, REG_A6, REG_A7},
    WORD_SIZE,
};

use crate::{
    host::client::env::ProveZkrRequest, recursion::prove::get_registered_zkr, Assumption,
    AssumptionReceipt,
};

use super::{Syscall, SyscallContext};

#[derive(Clone)]
pub(crate) struct SysProveZkr;

impl Syscall for SysProveZkr {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_prove_zkr call");
        }

        let claim_digest = ctx.load_digest_from_register(REG_A3)?;
        let control_id = ctx.load_digest_from_register(REG_A4)?;
        let control_root = ctx.load_digest_from_register(REG_A5)?;
        let input_ptr = ByteAddr(ctx.load_register(REG_A6));
        let input_len = ctx.load_register(REG_A7);
        let input: Vec<u8> = ctx.load_region(input_ptr, input_len * WORD_SIZE as u32)?;

        let assumption = ctx
            .syscall_table()
            .assumptions
            .borrow()
            .find_assumption(&claim_digest, &control_root)?;
        if assumption.is_some() {
            // This assumption is already known, no need to create another proof.
            return Ok((0, 0));
        }

        let proof_request = ProveZkrRequest {
            claim_digest,
            control_id,
            input,
        };

        if let Some(coprocessor) = &ctx.syscall_table().coprocessor {
            coprocessor.borrow_mut().prove_zkr(proof_request)?;
        } else {
            get_registered_zkr(&control_id)?;
            ctx.syscall_table()
                .pending_zkrs
                .borrow_mut()
                .push(proof_request);
        }

        let assumption = Assumption {
            claim: claim_digest,
            control_root,
        };
        ctx.syscall_table()
            .assumptions
            .borrow_mut()
            .0
            .push(AssumptionReceipt::Unresolved(assumption));

        Ok((0, 0))
    }
}
