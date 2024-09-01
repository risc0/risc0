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

//! Handlers for two-way private I/O between host and guest.

mod fork;
mod pipe;
mod prove_zkr;
mod verify;

use std::{cell::RefCell, cmp::min, collections::HashMap, rc::Rc};

use anyhow::{anyhow, bail, Result};
use bytes::Bytes;
use risc0_circuit_rv32im::prove::emu::addr::ByteAddr;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::{
    fileno,
    syscall::{
        nr::{
            SYS_ARGC, SYS_ARGV, SYS_CYCLE_COUNT, SYS_FORK, SYS_GETENV, SYS_LOG, SYS_PANIC,
            SYS_PIPE, SYS_PROVE_ZKR, SYS_RANDOM, SYS_READ, SYS_VERIFY_INTEGRITY, SYS_WRITE,
        },
        reg_abi::{REG_A3, REG_A4, REG_A5},
        SyscallName, DIGEST_BYTES,
    },
    WORD_SIZE,
};

use crate::{
    host::client::{
        env::{AssumptionReceipts, CoprocessorCallbackRef, ProveZkrRequest},
        posix_io::PosixIo,
        slice_io::SliceIo,
    },
    Assumption, AssumptionReceipt, ExecutorEnv,
};

use self::{fork::SysFork, pipe::SysPipe, prove_zkr::SysProveZkr, verify::SysVerify};

/// A host-side implementation of a system call.
pub(crate) trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub(crate) trait SyscallContext<'a> {
    /// Returns the current program counter.
    fn get_pc(&self) -> u32;

    /// Returns the current cycle being executed.
    fn get_cycle(&self) -> u64;

    /// Loads the value of the given register, e.g. REG_A0.
    fn load_register(&mut self, idx: usize) -> u32;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: ByteAddr) -> Result<u8>;

    /// Loads an individual word from memory.
    fn load_u32(&mut self, addr: ByteAddr) -> Result<u32>;

    /// Loads bytes from the given region of memory. A region may span multiple pages.
    fn load_region(&mut self, addr: ByteAddr, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for i in 0..size {
            region.push(self.load_u8(addr + i)?);
        }
        Ok(region)
    }

    /// Loads a digest from the given address.
    fn load_digest_from_register(&mut self, idx: usize) -> Result<Digest> {
        let addr = ByteAddr(self.load_register(idx));
        self.load_region(addr, DIGEST_BYTES as u32)?
            .try_into()
            .map_err(|vec| anyhow!("invalid digest: {vec:?}"))
    }

    /// Load a page from memory at the specified page index.
    fn load_page(&mut self, page_idx: u32) -> Result<Vec<u8>>;

    /// Access the syscall table.
    fn syscall_table(&self) -> &SyscallTable<'a>;
}

pub(crate) type AssumptionUsage = Vec<(Assumption, AssumptionReceipt)>;

#[derive(Clone)]
pub(crate) struct SyscallTable<'a> {
    pub(crate) inner: HashMap<String, Rc<RefCell<dyn Syscall + 'a>>>,
    pub(crate) posix_io: Rc<RefCell<PosixIo<'a>>>,
    pub(crate) assumptions: Rc<RefCell<AssumptionReceipts>>,
    pub(crate) assumptions_used: Rc<RefCell<AssumptionUsage>>,
    pub(crate) coprocessor: Option<CoprocessorCallbackRef<'a>>,
    pub(crate) pending_zkrs: Rc<RefCell<Vec<ProveZkrRequest>>>,
}

impl<'a> SyscallTable<'a> {
    pub fn new(env: &ExecutorEnv<'a>) -> Self {
        Self {
            inner: Default::default(),
            posix_io: env.posix_io.clone(),
            assumptions: env.assumptions.clone(),
            assumptions_used: Default::default(),
            coprocessor: env.coprocessor.clone(),
            pending_zkrs: Default::default(),
        }
    }

    pub fn from_env(env: &ExecutorEnv<'a>) -> Self {
        let mut this = Self::new(env);

        this.with_syscall(SYS_ARGC, Args(env.args.clone()))
            .with_syscall(SYS_ARGV, Args(env.args.clone()))
            .with_syscall(SYS_CYCLE_COUNT, SysCycleCount)
            .with_syscall(SYS_FORK, SysFork)
            .with_syscall(SYS_GETENV, SysGetenv(env.env_vars.clone()))
            .with_syscall(SYS_LOG, SysLog)
            .with_syscall(SYS_PANIC, SysPanic)
            .with_syscall(SYS_PIPE, SysPipe::default())
            .with_syscall(SYS_RANDOM, SysRandom)
            .with_syscall(SYS_READ, SysRead)
            .with_syscall(SYS_VERIFY_INTEGRITY, SysVerify)
            .with_syscall(SYS_PROVE_ZKR, SysProveZkr)
            .with_syscall(SYS_WRITE, SysWrite);
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
        let cycle = ctx.get_cycle();
        let hi = (cycle >> 32) as u32;
        let lo = cycle as u32;
        Ok((hi, lo))
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
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = std::str::from_utf8(&from_guest)?;

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

pub(crate) struct SysPanic;
impl Syscall for SysPanic {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
        let buf_len = ctx.load_register(REG_A4);
        let from_guest = ctx.load_region(buf_ptr, buf_len)?;
        let msg = std::str::from_utf8(&from_guest)?;
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
        tracing::debug!("SYS_RANDOM: {}", to_guest.len());
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
                    "guest requested index {arg_index} from argv of len {}",
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
        let buf_ptr = ByteAddr(ctx.load_register(REG_A3));
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

struct SysRead;
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

        Ok((
            (nread_main + nread_end) as u32,
            u32::from_le_bytes(to_guest_end),
        ))
    }
}

struct SysWrite;
impl Syscall for SysWrite {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let buf_ptr = ByteAddr(ctx.load_register(REG_A4));
        let buf_len = ctx.load_register(REG_A5);
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len)?;
        let writer = ctx.syscall_table().posix_io.borrow().get_writer(fd)?;

        tracing::trace!("sys_write(fd: {fd}, bytes: {buf_len})");

        writer.borrow_mut().write_all(from_guest_bytes.as_slice())?;
        Ok((0, 0))
    }
}

struct SysLog;
impl Syscall for SysLog {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        _to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
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
