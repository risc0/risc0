// Copyright 2026 RISC Zero, Inc.
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

use anyhow::{Result, bail};

use super::{Syscall, SyscallContext};

use risc0_zkvm_platform::WORD_SIZE;

pub(crate) struct SysCycleCount;
impl Syscall for SysCycleCount {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        if to_guest.len() != WORD_SIZE * 2 {
            bail!("invalid sys_cycle_count call");
        }

        let rows = ctx.get_rows();
        let hi = (rows >> 32) as u32;
        let lo = rows as u32;

        to_guest[..WORD_SIZE].copy_from_slice(&hi.to_le_bytes());
        to_guest[WORD_SIZE..].copy_from_slice(&lo.to_le_bytes());

        Ok(to_guest.len())
    }
}
