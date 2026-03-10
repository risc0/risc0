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

use std::rc::Rc;

use anyhow::{Result, bail};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::syscall::reg_abi::{REG_A3, REG_A4, REG_A5};

use super::{Syscall, SyscallContext, SyscallKind};

pub(crate) struct SysRead;

impl Syscall for SysRead {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        let fd = ctx.load_register(REG_A3);

        tracing::trace!("sys_read(fd: {fd}, into: {} bytes)", to_guest.len());
        let reader = ctx.syscall_table().posix_io.borrow().get_reader(fd)?;

        // So that we don't have to deal with short reads, keep
        // reading until we get EOF or fill the buffer.
        let read_all = |mut buf: &mut [u8]| -> Result<usize> {
            let mut tot_nread = 0;
            while !buf.is_empty() {
                let nread = reader.borrow_mut().read(buf)?;
                if nread == 0 {
                    break;
                }
                tot_nread += nread;
                (_, buf) = buf.split_at_mut(nread);
            }
            Ok(tot_nread)
        };

        let nread_main = read_all(to_guest)?;

        tracing::trace!("read: {nread_main}, requested: {}", to_guest.len());

        Ok(nread_main)
    }
}

pub(crate) struct SysWrite;

impl Syscall for SysWrite {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u8],
    ) -> Result<usize> {
        if !to_guest.is_empty() {
            bail!("invalid sys_write call");
        }

        let posix_io = Rc::clone(&ctx.syscall_table().posix_io);
        let fd = ctx.load_register(REG_A3);
        let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
        let buf_len = ctx.load_register(REG_A5);
        let mut from_guest = ctx.read_region(buf_ptr, buf_len)?;
        let writer = posix_io.borrow().get_writer(fd)?;

        tracing::trace!("sys_write(fd: {fd}, bytes: {buf_len})");

        std::io::copy(&mut from_guest, &mut *writer.borrow_mut())?;
        drop(from_guest);

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::Write];
        metric.count += 1;
        metric.size += buf_len as u64;

        Ok(0)
    }
}
