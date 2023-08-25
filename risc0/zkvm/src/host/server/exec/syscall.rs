// Copyright 2023 RISC Zero, Inc.
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

//! Handlers for two-way private I/O between host and guest.

use std::{cell::RefCell, cmp::min, collections::HashMap, io::Cursor, rc::Rc, str::from_utf8};

use anyhow::{anyhow, bail, ensure, Result};
use bytes::Bytes;
use risc0_zkvm_platform::{
    fileno,
    syscall::{
        nr::{
            SYS_CYCLE_COUNT, SYS_GETENV, SYS_LOG, SYS_PANIC, SYS_RANDOM, SYS_READ, SYS_READ_AVAIL,
            SYS_WRITE,
        },
        reg_abi::{REG_A3, REG_A4, REG_A5},
        SyscallName,
    },
    WORD_SIZE,
};

use crate::host::client::{
    env::{ExecutorEnv, SliceIo},
    posix_io::PosixIo,
};

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Returns the current cycle being executed.
    fn get_cycle(&self) -> usize;

    /// Loads the value of the given register, e.g. REG_A0.
    fn load_register(&mut self, idx: usize) -> u32;

    /// Loads bytes from the given region of memory.
    fn load_region(&mut self, addr: u32, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for addr in addr..addr + size {
            region.push(self.load_u8(addr)?);
        }
        Ok(region)
    }

    /// Loads an individual word from memory.
    fn load_u32(&mut self, addr: u32) -> Result<u32>;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: u32) -> Result<u8>;

    /// Loads a null-terminated string from memory.
    fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let b = self.load_u8(addr)?;
            if b == 0 {
                break;
            }
            s.push(b);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }
}

#[derive(Clone)]
pub(crate) struct SyscallTable<'a> {
    pub(crate) inner: HashMap<String, Rc<RefCell<dyn Syscall + 'a>>>,
}

impl<'a> SyscallTable<'a> {
    pub fn new(env: &ExecutorEnv<'a>) -> Self {
        let mut this = Self {
            inner: HashMap::new(),
        };

        let posix_io = env.posix_io.clone();
        if !env.input.is_empty() {
            let reader = Cursor::new(env.input.clone());
            posix_io.borrow_mut().with_read_fd(fileno::STDIN, reader);
        }
        this.with_syscall(SYS_CYCLE_COUNT, SysCycleCount)
            .with_syscall(SYS_LOG, SysLog)
            .with_syscall(SYS_PANIC, SysPanic)
            .with_syscall(SYS_RANDOM, SysRandom)
            .with_syscall(SYS_GETENV, SysGetenv(env.env_vars.clone()))
            .with_syscall(SYS_READ, posix_io.clone())
            .with_syscall(SYS_READ_AVAIL, posix_io.clone())
            .with_syscall(SYS_WRITE, posix_io);
        for (syscall, handler) in env.slice_io.iter() {
            this.inner
                .insert(syscall.clone(), Rc::new(RefCell::new(handler.clone())));
        }

        this
    }

    fn with_syscall(&mut self, syscall: SyscallName, handler: impl Syscall + 'a) -> &mut Self {
        self.inner
            .insert(syscall.as_str().to_string(), Rc::new(RefCell::new(handler)));
        self
    }

    pub(crate) fn get_syscall(&self, name: &str) -> Option<&Rc<RefCell<(dyn Syscall + 'a)>>> {
        self.inner.get(name)
    }
}

pub(crate) struct SysCycleCount;
impl Syscall for SysCycleCount {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        Ok((ctx.get_cycle() as u32, 0))
    }
}

pub(crate) struct SysGetenv(pub HashMap<String, String>);
impl Syscall for SysGetenv {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = from_utf8(&from_guest)?;

        match self.0.get(msg) {
            None => Ok((u32::MAX, 0)),
            Some(val) => {
                let nbytes = min(to_guest.len() * WORD_SIZE, val.as_bytes().len());
                let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                to_guest_u8s[0..nbytes].clone_from_slice(&val.as_bytes()[0..nbytes]);
                Ok((val.as_bytes().len() as u32, 0))
            }
        }
    }
}

pub(crate) struct SysLog;
impl Syscall for SysLog {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = from_utf8(&from_guest)?;
        println!("R0VM[{}] {}", ctx.get_cycle(), msg);
        Ok((0, 0))
    }
}

pub(crate) struct SysPanic;
impl Syscall for SysPanic {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = from_utf8(&from_guest)?;
        bail!("Guest panicked: {msg}");
    }
}

pub(crate) struct SysRandom;
impl Syscall for SysRandom {
    fn syscall(
        &mut self,
        _syscall: &str,
        _ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        log::debug!("SYS_RANDOM: {}", to_guest.len());
        let mut rand_buf = vec![0u8; to_guest.len() * WORD_SIZE];
        getrandom::getrandom(rand_buf.as_mut_slice())?;
        bytemuck::cast_slice_mut(to_guest).clone_from_slice(rand_buf.as_slice());
        Ok((0, 0))
    }
}

// pub(crate) fn sys_random(from_guest: Bytes) -> Result<Bytes> {
// let bytes_req = u32::from_le_bytes(
// <[u8; WORD_SIZE]>::try_from(from_guest)
// .context("SYS_RANDOM invalid request data from guest"),
// );
// log::debug!("SYS_RANDOM: {}", bytes_req.len());
// let mut rand_buf = vec![0u8; bytes_req];
// getrandom::getrandom(rand_buf.as_mut_slice())?;
// Ok(Bytes::from(rand_buf))
// }

/// An implementation of a [Syscall] for a [SliceIo].
///
/// When invoked by the guest, this [Syscall] implementation will pass the bytes
/// from the guest to the [SliceIo] callback. In return, the `to_guest` buffer
/// provided for response data will be filled with bytes from the callback
/// response. Any bytes remaining of the callback response will be stored, and
/// the syscall result will indicate how many bytes are left to be read.
///
/// Subsequent calls to this handler will continue to return the remaining
/// callback response until all of it has been returned to guest. The guest must
/// not pass new input to the host until all bytes have been read from the
/// previous callback.
///
/// A common pattern in the guest is to use [SliceIo] syscalls with two steps:
///
/// 1. Invoke the `syscall` with the callback input and empty `to_guest` buffer
///    to get the number of available bytes in the response.
/// 2. Invoke the `syscall` with a `from_host` buffer of large enough to accept
///    all bytes of the callback response.
///
/// This is the pattern implemented in `env::send_recv_slice`. It is also
/// possible to receive the available data either in a single call, by providing
/// a buffer to the host for receiving callback data on the first invocation,
/// and it is possible to receive the callback response in multiple calls to
/// support a smaller receive buffer.
impl<'a> Syscall for SliceIo<'a> {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let to_guest_bytes: &mut [u8] = bytemuck::cast_slice_mut(to_guest);

        let mut stored_buf = self.stored_buf.borrow_mut();
        let mut buf = match stored_buf.take() {
            None => {
                // No stored response available. Issue a call to the callback.
                let mut callback = self.callback.borrow_mut();
                callback(Bytes::from(from_guest))?
            }
            Some(buf) => {
                // We already have data to send to the guest; fill the provided buffer.
                // It is an error for the guest to provided additional input before reading
                // stored response in full.
                ensure!(
                    from_guest.len() == 0,
                    "unexpected input from guest to slice io syscall"
                );
                buf
            }
        };

        if buf.len() <= to_guest_bytes.len() {
            // Guest provided large enough buffer. Return the full response.
            to_guest_bytes[..buf.len()].clone_from_slice(&buf);
            Ok((0, 0))
        } else {
            // Fill the provided buffer and store any bytes that would not fit.
            to_guest_bytes.clone_from_slice(&buf.split_to(to_guest_bytes.len()));
            let navail = buf.len() as u32;
            *stored_buf = Some(buf);
            Ok((navail, 0))
        }
    }
}

impl<'a> Syscall for PosixIo<'a> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        // TODO: Is there a way to use "match" here instead of if statements?
        if syscall == SYS_READ_AVAIL.as_str() {
            self.sys_read_avail(ctx)
        } else if syscall == SYS_READ.as_str() {
            self.sys_read(ctx, to_guest)
        } else if syscall == SYS_WRITE.as_str() {
            self.sys_write(ctx)
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}

impl<'a> Syscall for Rc<RefCell<PosixIo<'a>>> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        self.borrow_mut().syscall(syscall, ctx, to_guest)
    }
}

impl<'a> PosixIo<'a> {
    fn sys_read_avail(&mut self, ctx: &mut dyn SyscallContext) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let reader = self
            .read_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad read file descriptor {fd}"))?;
        let navail = reader.borrow_mut().fill_buf().unwrap().len() as u32;
        log::debug!("navail: {navail}");
        Ok((navail, 0))
    }

    fn sys_read(
        &mut self,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let nbytes = ctx.load_register(REG_A4) as usize;

        log::debug!(
            "sys_read, attempting to read {nbytes} bytes from fd {fd}, to_guest: {}",
            to_guest.len()
        );

        assert!(
            nbytes >= to_guest.len() * WORD_SIZE,
            "Word-aligned read buffer must be fully filled"
        );

        let reader = self
            .read_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad read file descriptor {fd}"))?;

        // So that we don't have to deal with short reads, keep
        // reading until we get EOF or fill the buffer.
        let read_all = |mut buf: &mut [u8]| -> usize {
            let mut tot_nread = 0;
            while !buf.is_empty() {
                let nread = reader.borrow_mut().read(buf).unwrap();
                if nread == 0 {
                    break;
                }
                tot_nread += nread;
                (_, buf) = buf.split_at_mut(nread);
            }
            tot_nread
        };

        let to_guest_u8 = bytemuck::cast_slice_mut(to_guest);
        let nread_main = read_all(to_guest_u8);
        assert_eq!(
            nread_main,
            to_guest_u8.len(),
            "Guest requested more data than was available"
        );

        log::debug!(
            "Main read got {nread_main} bytes out of requested {}",
            to_guest_u8.len()
        );
        let unaligned_end = nbytes - nread_main;
        assert!(
            unaligned_end <= WORD_SIZE,
            "{unaligned_end} must be <= {WORD_SIZE}"
        );

        // Fill unaligned word out.
        let mut to_guest_end: [u8; WORD_SIZE] = [0; WORD_SIZE];
        let nread_end = read_all(&mut to_guest_end[0..unaligned_end]);

        Ok((
            (nread_main + nread_end) as u32,
            u32::from_le_bytes(to_guest_end),
        ))
    }

    fn sys_write(&mut self, ctx: &mut dyn SyscallContext) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let buf_ptr = ctx.load_register(REG_A4);
        let buf_len = ctx.load_register(REG_A5);
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;
        let writer = self
            .write_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad write file descriptor {fd}"))?;

        log::debug!("Writing {buf_len} bytes to file descriptor {fd}");

        writer
            .borrow_mut()
            .write_all(from_guest_bytes.as_slice())
            .unwrap();
        Ok((0, 0))
    }
}
