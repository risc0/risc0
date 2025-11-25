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

use anyhow::{Result, anyhow, bail};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::REG_A3;

use crate::sha::{DIGEST_BYTES, Digest};

use super::{Syscall, SyscallContext, SyscallKind};

#[derive(Clone)]
pub(crate) struct SysVerify;

fn not_found_err(claim_digest: &Digest, control_root: &Digest) -> anyhow::Error {
    anyhow!(
        "sys_verify_integrity: no receipt found to resolve assumption: claim digest {claim_digest}, control root {control_root}"
    )
}

impl Syscall for SysVerify {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_verify call");
        }

        let from_guest_ptr = ByteAddr(ctx.load_register(REG_A3));
        let from_guest_len = DIGEST_BYTES as u32 * 2;
        let from_guest = ctx.load_region(from_guest_ptr, from_guest_len)?;

        let claim_digest: Digest = from_guest[..DIGEST_BYTES]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;
        let control_root: Digest = from_guest[DIGEST_BYTES..]
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))?;

        tracing::debug!("SYS_VERIFY_INTEGRITY: ({}, {})", claim_digest, control_root);

        let assumption = ctx
            .syscall_table()
            .assumptions
            .borrow()
            .find_assumption(&claim_digest, &control_root)?
            .ok_or_else(|| not_found_err(&claim_digest, &control_root))?;

        // Mark the assumption as accessed, pushing it to the head of the list, and return the success code.
        ctx.syscall_table()
            .assumptions_used
            .lock()
            .unwrap()
            .insert(0, assumption);

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::VerifyIntegrity];
        metric.count += 1;
        metric.size += from_guest_len as u64;

        Ok((0, 0))
    }
}
