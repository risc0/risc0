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

use anyhow::{anyhow, bail, Result};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4};

use crate::{
    sha::{Digest, DIGEST_BYTES},
    Assumption, AssumptionReceipt,
};

use super::{Syscall, SyscallContext, SyscallKind};

#[derive(Clone)]
pub(crate) struct SysVerify2;

impl Syscall for SysVerify2 {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_verify2 call");
        }
        let from_guest_ptr = ByteAddr(ctx.load_register(REG_A3));
        let from_guest_len = ctx.load_register(REG_A4);
        let from_guest: Vec<u8> = ctx.load_region(from_guest_ptr, from_guest_len)?;

        let claim_digest: Digest = from_guest[..DIGEST_BYTES]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;
        let control_root: Digest = from_guest[DIGEST_BYTES..]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;

        tracing::info!(
            "SYS_VERIFY_INTEGRITY2: ({}, {})",
            claim_digest,
            control_root
        );

        let assumption = Assumption {
            claim: claim_digest,
            control_root,
        };

        let assumption_receipt = AssumptionReceipt::Unresolved(assumption.clone());

        ctx.syscall_table()
            .assumptions
            .borrow_mut()
            .0
            .push(assumption_receipt.clone());

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        ctx.syscall_table()
            .assumptions_used
            .lock()
            .unwrap()
            .insert(0, (assumption, assumption_receipt));

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::VerifyIntegrity2];
        metric.count += 1;
        metric.size += from_guest_len as u64;

        Ok((0, 0))
    }
}
