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

//! TODO

use std::{
    cell::RefCell,
    collections::{BTreeMap, HashMap},
    io::{stderr, stdin, stdout, BufRead, BufReader, Write},
    rc::Rc,
};

use anyhow::{bail, Result};
use risc0_zkvm_platform::{
    fileno,
    memory::SYSTEM,
    syscall::{
        nr::{SYS_CYCLE_COUNT, SYS_LOG, SYS_PANIC, SYS_READ, SYS_READ_AVAIL, SYS_WRITE},
        reg_abi::{REG_A3, REG_A4, REG_A5},
        SyscallName,
    },
    WORD_SIZE,
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
    fn load_register(&mut self, num: usize) -> u32 {
        self.load_u32((SYSTEM.start() + num * WORD_SIZE) as u32)
    }

    /// Loads bytes from the given region of memory.
    fn load_region(&mut self, addr: u32, size: u32) -> Vec<u8> {
        let mut region = Vec::new();
        for addr in addr..addr + size {
            region.push(self.load_u8(addr));
        }
        region
    }

    /// Loads an individual word from memory.
    fn load_u32(&mut self, addr: u32) -> u32;

    /// Loads an individual byte from memory.
    fn load_u8(&mut self, addr: u32) -> u8;

    /// Loads a null-terminated string from memory.
    fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let b = self.load_u8(addr);
            if b == 0 {
                break;
            }
            s.push(b);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }
}

/// Posix-style I/O
#[derive(Clone)]
pub struct PosixIo {
    read_fds: BTreeMap<u32, Rc<RefCell<dyn BufRead>>>,
    write_fds: BTreeMap<u32, Rc<RefCell<dyn Write>>>,
}

impl PosixIo {
    pub fn with_read_fd(&mut self, fd: u32, reader: Rc<RefCell<dyn BufRead>>) -> &mut Self {
        self.read_fds.insert(fd, reader);
        self
    }

    pub fn with_write_fd(&mut self, fd: u32, writer: Rc<RefCell<dyn Write>>) -> &mut Self {
        self.write_fds.insert(fd, writer);
        self
    }

    fn sys_read_avail(&mut self, ctx: &mut dyn SyscallContext) -> Result<(u32, u32)> {
        let fd = ctx.load_register(REG_A3);
        let reader = self
            .read_fds
            .get_mut(&fd)
            .expect(&format!("Bad read file descriptor {fd}"));
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

        log::debug!("sys_read, attempting to read {nbytes} bytes from fd {fd}");

        assert!(
            nbytes >= to_guest.len() * WORD_SIZE,
            "Word-aligned read buffer must be fully filled"
        );

        let reader = self
            .read_fds
            .get_mut(&fd)
            .expect(&format!("Bad read file descriptor {fd}"));
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

        let to_guest_u8: &mut [u8] = bytemuck::cast_slice_mut(to_guest);
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
        let from_guest_bytes = ctx.load_region(buf_ptr, buf_len);
        let writer = self
            .write_fds
            .get_mut(&fd)
            .expect(&format!("Bad write file descriptor {fd}"));

        log::debug!("Writing {buf_len} bytes to file descriptor {fd}");

        writer
            .borrow_mut()
            .write_all(from_guest_bytes.as_slice())
            .unwrap();
        Ok((0, 0))
    }
}

impl Default for PosixIo {
    fn default() -> Self {
        let mut new = Self {
            read_fds: Default::default(),
            write_fds: Default::default(),
        };
        new.with_read_fd(
            fileno::STDIN,
            Rc::new(RefCell::new(BufReader::new(stdin()))),
        )
        .with_write_fd(fileno::STDOUT, Rc::new(RefCell::new(stdout())))
        .with_write_fd(fileno::STDERR, Rc::new(RefCell::new(stderr())));
        new
    }
}

impl Syscall for PosixIo {
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

impl Syscall for Rc<RefCell<PosixIo>> {
    fn syscall(
        &mut self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        self.borrow_mut().syscall(syscall, ctx, to_guest)
    }
}

#[derive(Clone)]
pub(crate) struct SyscallTable {
    pub(crate) inner: HashMap<String, Rc<RefCell<dyn Syscall>>>,
}

impl Default for SyscallTable {
    fn default() -> Self {
        let mut new = Self {
            inner: Default::default(),
        };
        new.with_syscall(SYS_CYCLE_COUNT, Rc::new(RefCell::new(syscalls::CycleCount)))
            .with_syscall(SYS_LOG, Rc::new(RefCell::new(syscalls::Log)))
            .with_syscall(SYS_PANIC, Rc::new(RefCell::new(syscalls::Panic)));
        new
    }
}

impl SyscallTable {
    pub fn with_syscall(
        &mut self,
        syscall: SyscallName,
        handler: Rc<RefCell<dyn Syscall>>,
    ) -> &mut Self {
        self.inner.insert(syscall.as_str().to_string(), handler);
        self
    }
}

pub(crate) mod syscalls {
    use std::{cmp::min, collections::HashMap, str::from_utf8};

    use anyhow::{bail, Result};
    use risc0_zkvm_platform::{
        syscall::reg_abi::{REG_A3, REG_A4},
        WORD_SIZE,
    };

    use super::{Syscall, SyscallContext};

    pub(crate) struct CycleCount;
    impl Syscall for CycleCount {
        fn syscall(
            &mut self,
            _syscall: &str,
            ctx: &mut dyn SyscallContext,
            _to_guest: &mut [u32],
        ) -> Result<(u32, u32)> {
            Ok((ctx.get_cycle() as u32, 0))
        }
    }

    pub(crate) struct Getenv(pub HashMap<String, String>);
    impl Syscall for Getenv {
        fn syscall(
            &mut self,
            _syscall: &str,
            ctx: &mut dyn SyscallContext,
            to_guest: &mut [u32],
        ) -> Result<(u32, u32)> {
            let buf_ptr = ctx.load_register(REG_A3);
            let buf_len = ctx.load_register(REG_A4);
            let from_guest = ctx.load_region(buf_ptr, buf_len);
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

    pub(crate) struct Log;
    impl Syscall for Log {
        fn syscall(
            &mut self,
            _syscall: &str,
            ctx: &mut dyn SyscallContext,
            _to_guest: &mut [u32],
        ) -> Result<(u32, u32)> {
            let buf_ptr = ctx.load_register(REG_A3);
            let buf_len = ctx.load_register(REG_A4);
            let from_guest = ctx.load_region(buf_ptr, buf_len);
            let msg = from_utf8(&from_guest)?;
            println!("R0VM[{}] {}", ctx.get_cycle(), msg);
            Ok((0, 0))
        }
    }

    pub(crate) struct Panic;
    impl Syscall for Panic {
        fn syscall(
            &mut self,
            _syscall: &str,
            ctx: &mut dyn SyscallContext,
            _to_guest: &mut [u32],
        ) -> Result<(u32, u32)> {
            let buf_ptr = ctx.load_register(REG_A3);
            let buf_len = ctx.load_register(REG_A4);
            let from_guest = ctx.load_region(buf_ptr, buf_len);
            let msg = from_utf8(&from_guest)?;
            bail!("Guest panicked: {msg}");
        }
    }
}
