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

use anyhow::{anyhow, Context, Result};
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4};

use crate::{
    host::client::env::AssumptionReceipts,
    sha::{Digest, DIGEST_BYTES},
    Assumption, AssumptionReceipt,
};

use super::{Syscall, SyscallContext};

#[derive(Clone)]
pub(crate) struct SysVerify;

impl Syscall for SysVerify {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let from_guest_ptr = ByteAddr(ctx.load_register(REG_A3));
        let from_guest_len = ctx.load_register(REG_A4);
        let from_guest: Vec<u8> = ctx.load_region(from_guest_ptr, from_guest_len)?;

        let claim_digest: Digest = from_guest[..DIGEST_BYTES]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;
        let control_root: Digest = from_guest[DIGEST_BYTES..]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;

        tracing::debug!("SYS_VERIFY_INTEGRITY: ({}, {})", claim_digest, control_root);

        let assumption = self
            .find_assumption(&ctx.syscall_table().assumptions.borrow(), &claim_digest, &control_root)?
            .ok_or(anyhow!(
                "sys_verify_integrity: no receipt found to resolve assumption: claim digest {claim_digest}, control root {control_root}"
            )
        )?;

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        ctx.syscall_table()
            .assumptions_used
            .borrow_mut()
            .insert(0, assumption);
        Ok((0, 0))
    }
}

impl SysVerify {
    // Iterate over the list looking for a matching assumption.
    fn find_assumption(
        &self,
        assumptions: &AssumptionReceipts,
        claim_digest: &Digest,
        control_root: &Digest,
    ) -> Result<Option<(Assumption, AssumptionReceipt)>> {
        for cached_assumption in assumptions.iter() {
            let cached_claim_digest = cached_assumption
                .claim_digest()
                .context("failed to access claim digest on cached assumption")?;

            if cached_claim_digest != *claim_digest {
                tracing::debug!(
                    "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} does not match"
                );
                continue;
            }

            // If the control root supplied by the guest is not zero, then they are requesting a
            // specific set of recursion programs be used to resolve the assumption. Check that the
            // given receipt can indeed resolve the assumption.
            // NOTE: We currently only support using Succinct receipts here.
            if *control_root != Digest::ZERO {
                let Some(cached_control_root) = (match cached_assumption {
                    AssumptionReceipt::Proven(receipt) => receipt
                        .succinct()
                        .ok()
                        .map(|r| r.control_root())
                        .transpose()?,
                    AssumptionReceipt::Unresolved(unresolved) => Some(unresolved.control_root),
                }) else {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} is not a succinct receipt"
                    );
                    continue;
                };
                if cached_control_root != *control_root {
                    // Elevate to warning because this really is likely an error.
                    tracing::warn!(
                        "SYS_VERIFY_INTEGRITY: receipt with claim {cached_claim_digest} has control root {cached_control_root}; guest requested {control_root}"
                    );
                    continue;
                }
            }

            return Ok(Some((
                Assumption {
                    claim: *claim_digest,
                    control_root: *control_root,
                },
                cached_assumption.clone(),
            )));
        }

        Ok(None)
    }
}
