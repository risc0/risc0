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

use anyhow::{bail, Result};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::{
    syscall::reg_abi::{REG_A3, REG_A4, REG_A5},
    WORD_SIZE,
};

use super::{Syscall, SyscallContext, SyscallKind};

pub(crate) struct SysRead;

impl Syscall for SysRead {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let nbytes = ctx.load_register(REG_A4) as usize;

        tracing::trace!(
            "sys_read(fd: {fd}, nbytes: {nbytes}, into: {} bytes)",
            to_guest.len() * WORD_SIZE
        );

        assert!(
            nbytes >= to_guest.len() * WORD_SIZE,
            "Word-aligned read buffer must be fully filled"
        );

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

        let to_guest_u8 = bytemuck::cast_slice_mut(to_guest);
        let nread_main = read_all(to_guest_u8)?;

        tracing::trace!("read: {nread_main}, requested: {}", to_guest_u8.len());

        // It's possible that there's an unaligned word at the end
        let unaligned_end = if nbytes - nread_main <= WORD_SIZE {
            nbytes - nread_main
        } else {
            // We encountered an EOF. There's nothing left to read
            0
        };

        // Fill unaligned word out.
        let mut to_guest_end: [u8; WORD_SIZE] = [0; WORD_SIZE];
        let nread_end = read_all(&mut to_guest_end[0..unaligned_end])?;
        let nread_total = nread_main + nread_end;

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::Read];
        metric.count += 1;
        metric.size += nread_total as u64;

        Ok((nread_total as u32, u32::from_le_bytes(to_guest_end)))
    }
}

pub(crate) struct SysWrite;

impl Syscall for SysWrite {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_write call");
        }

        let fd = ctx.load_register(REG_A3);
        let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
        let buf_len = ctx.load_register(REG_A5);
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;
        let writer = ctx.syscall_table().posix_io.borrow().get_writer(fd)?;

        tracing::trace!("sys_write(fd: {fd}, bytes: {buf_len})");

        writer.borrow_mut().write_all(from_guest_bytes.as_slice())?;

        let metric = &mut ctx.syscall_table().metrics.borrow_mut()[SyscallKind::Write];
        metric.count += 1;
        metric.size += buf_len as u64;

        Ok((0, 0))
    }
}
