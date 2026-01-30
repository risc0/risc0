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

use std::cmp::min;

use anyhow::{Result, anyhow, bail};
use risc0_circuit_rv32im::execute::MAX_IO_BYTES;
use risc0_zkvm_platform::{
    WORD_SIZE,
    syscall::{
        nr::{SYS_ARGC, SYS_ARGV},
        reg_abi::{REG_A3, REG_A4},
    },
};

use super::{Syscall, SyscallContext};

#[derive(Clone)]
pub(crate) struct SysArgs(pub Vec<String>);

impl Syscall for SysArgs {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        if syscall == SYS_ARGC.as_str() {
            if to_guest.len() != WORD_SIZE * 2 {
                bail!("invalid sys_argc call");
            }

            let arg_len: u32 = self
                .0
                .len()
                .try_into()
                .map_err(|e| anyhow!("too many arguments: {e}"))?;
            to_guest[..WORD_SIZE].copy_from_slice(&arg_len.to_le_bytes());
            Ok(to_guest.len())
        } else if syscall == SYS_ARGV.as_str() {
            // Get the arg or return an error if out of bounds.
            let arg_index = ctx.load_register(REG_A3);
            let arg_val = self.0.get(arg_index as usize).ok_or_else(|| {
                anyhow!(
                    "guest requested index {arg_index} from argv of len {}",
                    self.0.len()
                )
            })?;

            let get_arg_len = ctx.load_register(REG_A4) != 0;
            if get_arg_len {
                if to_guest.len() != WORD_SIZE * 2 {
                    bail!("invalid get-env with get_var_len=1")
                }
                if arg_val.len() >= MAX_IO_BYTES as usize {
                    bail!("sys_argv failure: argv is too large");
                }
                let ret = arg_val.len() as u32;
                to_guest[..WORD_SIZE].copy_from_slice(&ret.to_le_bytes());
                Ok(to_guest.len())
            } else {
                let nbytes = min(to_guest.len(), arg_val.len());
                to_guest[0..nbytes].clone_from_slice(&arg_val.as_bytes()[0..nbytes]);

                Ok(nbytes)
            }
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}
