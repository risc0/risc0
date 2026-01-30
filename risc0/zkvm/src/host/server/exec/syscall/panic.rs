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
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4};

use super::{Syscall, SyscallContext};

// Maximum size, in bytes, for the panic message provided by the guest. Messages above this size
// are truncated.
const MAX_PANIC_MSG_SIZE: u32 = 1 << 20; // 1 MB

pub(crate) struct SysPanic;
impl Syscall for SysPanic {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_panic call");
        }

        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, u32::min(buf_len, MAX_PANIC_MSG_SIZE))?;
        let msg = std::str::from_utf8(&from_guest)?;
        bail!("Guest panicked: {msg}");
    }
}
