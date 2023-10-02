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

use std::{cell::RefCell, cmp::min, collections::HashMap, rc::Rc, str::from_utf8};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_zkvm_platform::{
    syscall::{
        nr::{
            SYS_ARGC, SYS_ARGV, SYS_CYCLE_COUNT, SYS_GETENV, SYS_LOG, SYS_PANIC, SYS_RANDOM,
            SYS_READ, SYS_READ_AVAIL, SYS_WRITE,
        },
        reg_abi::{REG_A3, REG_A4, REG_A5},
        SyscallName,
    },
    WORD_SIZE,
};

use crate::host::client::{env::ExecutorEnv, posix_io::PosixIo, slice_io::SliceIo};

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
        this.with_syscall(SYS_CYCLE_COUNT, SysCycleCount)
            .with_syscall(SYS_LOG, SysLog)
            .with_syscall(SYS_PANIC, SysPanic)
            .with_syscall(SYS_RANDOM, SysRandom)
            .with_syscall(SYS_GETENV, SysGetenv(env.env_vars.clone()))
            .with_syscall(SYS_READ, posix_io.clone())
            .with_syscall(SYS_READ_AVAIL, posix_io.clone())
            .with_syscall(SYS_WRITE, posix_io)
            .with_syscall(SYS_ARGC, Args(env.args.clone()))
            .with_syscall(SYS_ARGV, Args(env.args.clone()));
        for (syscall, handler) in env.slice_io.borrow().inner.iter() {
            let handler = SysSliceIo::new(handler.clone());
            this.inner
                .insert(syscall.clone(), Rc::new(RefCell::new(handler)));
        }

        this
    }

    pub(crate) fn with_syscall(
        &mut self,
        syscall: SyscallName,
        handler: impl Syscall + 'a,
    ) -> &mut Self {
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

#[derive(Clone)]
pub(crate) struct Args(pub Vec<String>);

impl Syscall for Args {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        if syscall == SYS_ARGC.as_str() {
            Ok((self.0.len().try_into()?, 0))
        } else if syscall == SYS_ARGV.as_str() {
            // Get the arg or return an error if out of bounds.
            let arg_index = ctx.load_register(REG_A3);
            let arg_val = self.0.get(arg_index as usize).ok_or_else(|| {
                anyhow!(
                    "guest requested index {} from argv of len {}",
                    arg_index,
                    self.0.len()
                )
            })?;

            let nbytes = min(to_guest.len() * WORD_SIZE, arg_val.as_bytes().len());
            let to_guest_u8s: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
            to_guest_u8s[0..nbytes].clone_from_slice(&arg_val.as_bytes()[0..nbytes]);
            Ok((arg_val.as_bytes().len() as u32, 0))
        } else {
            bail!("Unknown syscall {syscall}")
        }
    }
}

/// A wrapper around a SliceIo that exposes it as a Syscall handler.
pub struct SysSliceIo<'a> {
    handler: Rc<RefCell<dyn SliceIo + 'a>>,
    stored_result: RefCell<Option<Bytes>>,
}

impl<'a> SysSliceIo<'a> {
    /// Wraps the given [SliceIo] into a [SysSliceIo].
    pub fn new(handler: Rc<RefCell<dyn SliceIo + 'a>>) -> Self {
        Self {
            handler,
            stored_result: RefCell::new(None),
        }
    }
}

/// An implementation of a [Syscall] for a [SliceIo].
///
/// When activated as a SyscallHandler, the SyscallHandler expects two
/// calls. The first call returns (nelem, _) indicating how many
/// elements are to be sent back to the guest, and the second call
/// actually returns the elements after the guest allocates space.
impl<'a> Syscall for SysSliceIo<'a> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mut stored_result = self.stored_result.borrow_mut();
        let buf_ptr = ctx.load_register(REG_A3);
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        Ok(match stored_result.take() {
            None => {
                // First call of pair. Send the data from the guest to the SliceIo
                // and save what it returns.
                assert_eq!(to_guest.len(), 0);
                let mut handler = self.handler.borrow_mut();
                let result = handler.handle_io(syscall, from_guest.into())?;
                let len = result.len() as u32;
                *stored_result = Some(result);
                (len, 0)
            }
            Some(stored) => {
                // Second call of pair. We already have data to send
                // to the guest; send it to the buffer that the guest
                // allocated.
                let to_guest_bytes: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
                assert!(stored.len() <= to_guest_bytes.len());
                assert!(stored.len() + WORD_SIZE > to_guest_bytes.len());
                to_guest_bytes[..stored.len()].clone_from_slice(&stored);
                (0, 0)
            }
        })
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
        log::debug!("sys_read_avail");
        let fd = ctx.load_register(REG_A3);
        let reader = self
            .read_fds
            .get_mut(&fd)
            .ok_or(anyhow!("Bad read file descriptor {fd}"))?;
        let navail = reader.borrow_mut().fill_buf()?.len() as u32;
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
        let nread_end = read_all(&mut to_guest_end[0..unaligned_end])?;

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

        writer.borrow_mut().write_all(from_guest_bytes.as_slice())?;
        Ok((0, 0))
    }
}
