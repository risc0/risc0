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

use std::{cmp::min, collections::HashMap};

use anyhow::{Result, bail};
use risc0_binfmt::ByteAddr;
use risc0_circuit_rv32im::execute::MAX_IO_BYTES;
use risc0_zkvm_platform::{
    WORD_SIZE,
    syscall::reg_abi::{REG_A3, REG_A4, REG_A5},
};

use super::{Syscall, SyscallContext};

pub(crate) struct SysGetenv(pub HashMap<String, String>);
impl Syscall for SysGetenv {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);

        // Read the env var take from the guest. Read with MAX_IO_BYTES + 1 to detect when a too
        // long env var is supplied.
        let from_guest = ctx.load_region(buf_ptr, u32::min(buf_len, MAX_IO_BYTES + 1))?;
        let msg = std::str::from_utf8(&from_guest)?;
        if msg.len() > MAX_IO_BYTES as usize {
            bail!("sys_getenv failure: env var name is too large");
        }

        let get_var_len = ctx.load_register(REG_A5) != 0;

        if get_var_len {
            if to_guest.len() != WORD_SIZE * 2 {
                bail!("invalid get-env with get_var_len=1")
            }
            let ret = match self.0.get(msg) {
                None => u32::MAX,
                Some(val) => {
                    if val.len() >= MAX_IO_BYTES as usize {
                        bail!("sys_getenv failure: value is too large");
                    }
                    val.len() as u32
                }
            };

            to_guest[..WORD_SIZE].copy_from_slice(&ret.to_le_bytes());
            Ok(to_guest.len())
        } else {
            match self.0.get(msg) {
                None => Ok(0),
                Some(val) => {
                    let nbytes = min(to_guest.len(), val.len());
                    to_guest[0..nbytes].clone_from_slice(&val.as_bytes()[0..nbytes]);

                    Ok(nbytes)
                }
            }
        }
    }
}
