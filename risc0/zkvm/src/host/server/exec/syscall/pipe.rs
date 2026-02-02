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

use std::{
    cell::RefCell,
    collections::VecDeque,
    io::{Read, Write},
    rc::Rc,
};

use anyhow::{Result, anyhow, bail};

use crate::host::client::posix_io::PosixIo;
use risc0_zkvm_platform::WORD_SIZE;

use super::{Syscall, SyscallContext};

// This is an arbitrary maximum number of open file descriptors allowed.
const MAX_FD: u32 = 1000;

#[derive(Default)]
pub(crate) struct SysPipe {}

impl Syscall for SysPipe {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        if to_guest.len() != 2 * WORD_SIZE {
            bail!("invalid sys_pipe call");
        }

        let posix_io = &ctx.syscall_table().posix_io;
        let pipe = Rc::new(RefCell::new(VecDeque::new()));
        let (first, second) = posix_io
            .borrow_mut()
            .alloc_pipe(pipe)
            .ok_or_else(|| anyhow!("Could not allocate pipe"))?;

        to_guest[..WORD_SIZE].copy_from_slice(&first.to_le_bytes());
        to_guest[WORD_SIZE..].copy_from_slice(&second.to_le_bytes());

        Ok(to_guest.len())
    }
}

impl<'a> PosixIo<'a> {
    fn find_free_fd(&self, start: u32) -> Option<u32> {
        (start..MAX_FD)
            .find(|&i| !self.read_fds.contains_key(&i) && !self.write_fds.contains_key(&i))
    }

    fn alloc_pipe<T>(&mut self, pipe: Rc<RefCell<T>>) -> Option<(u32, u32)>
    where
        T: Read + Write + 'a,
    {
        let read_fd = self.find_free_fd(0)?;
        let write_fd = self.find_free_fd(read_fd)?;
        self.read_fds.insert(read_fd, pipe.clone());
        self.write_fds.insert(write_fd, pipe);
        Some((read_fd, write_fd))
    }
}
