// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::{Result, bail};
use risc0_binfmt::ByteAddr;
use risc0_zkvm_platform::{
    fileno,
    syscall::reg_abi::{REG_A3, REG_A4},
};

use super::{Syscall, SyscallContext};

pub(crate) struct SysLog;

impl Syscall for SysLog {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if !to_guest.is_empty() {
            bail!("invalid sys_log call");
        }

        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let writer = ctx
            .syscall_table()
            .posix_io
            .borrow()
            .get_writer(fileno::STDOUT)?;

        tracing::debug!("sys_log({buf_len} bytes)");

        let msg = format!("R0VM[{}] ", ctx.get_cycle());
        writer
            .borrow_mut()
            .write_all(&[msg.as_bytes(), &from_guest, b"\n"].concat())?;
        Ok((0, 0))
    }
}
