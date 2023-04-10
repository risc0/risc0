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
    collections::HashMap,
    io::{BufRead, Cursor, Write},
    rc::Rc,
};

use bytemuck::Pod;
use risc0_zkvm_platform::{
    fileno,
    syscall::{
        nr::{SYS_GETENV, SYS_READ, SYS_READ_AVAIL, SYS_WRITE},
        SyscallName,
    },
};

use super::io::{syscalls, PosixIo, Syscall, SyscallTable};

const DEFAULT_SEGMENT_LIMIT_PO2: usize = 20; // 1M cycles

const DEFAULT_SESSION_LIMIT: usize = 64 * 1024 * 1024; // 64M cycles

/// TODO
#[derive(Clone)]
pub struct ExecutorEnvBuilder {
    inner: ExecutorEnv,
}

/// TODO
#[derive(Clone)]
pub struct ExecutorEnv {
    pub(crate) env_vars: HashMap<String, String>,
    pub(crate) segment_limit_po2: usize,
    pub(crate) session_limit: usize,
    pub(crate) syscalls: SyscallTable,
    pub(crate) io: PosixIo,
    input: Vec<u8>,
}

impl ExecutorEnv {
    /// TODO
    pub fn default() -> ExecutorEnvBuilder {
        ExecutorEnvBuilder::default()
    }
}

impl Default for ExecutorEnvBuilder {
    fn default() -> Self {
        Self {
            inner: ExecutorEnv {
                env_vars: Default::default(),
                segment_limit_po2: DEFAULT_SEGMENT_LIMIT_PO2,
                session_limit: DEFAULT_SESSION_LIMIT,
                syscalls: Default::default(),
                io: Default::default(),
                input: Default::default(),
            },
        }
    }
}

impl ExecutorEnvBuilder {
    /// TODO
    pub fn build(&mut self) -> ExecutorEnv {
        let mut new = self.clone();
        let getenv = Rc::new(RefCell::new(syscalls::Getenv(self.inner.env_vars.clone())));
        if !new.inner.input.is_empty() {
            let reader = Rc::new(RefCell::new(Cursor::new(new.inner.input.clone())));
            new.inner.io.with_read_fd(fileno::STDIN, reader);
        }
        let io = Rc::new(RefCell::new(new.inner.io.clone()));
        new.syscall(SYS_GETENV, getenv)
            .syscall(SYS_READ, io.clone())
            .syscall(SYS_READ_AVAIL, io.clone())
            .syscall(SYS_WRITE, io);
        new.inner
    }

    /// TODO
    pub fn segment_limit_po2(&mut self, limit: usize) -> &mut Self {
        self.inner.segment_limit_po2 = limit;
        self
    }

    /// TODO
    pub fn session_limit(&mut self, limit: usize) -> &mut Self {
        self.inner.session_limit = limit;
        self
    }

    /// TODO
    pub fn env_vars(&mut self, vars: HashMap<String, String>) -> &mut Self {
        self.inner.env_vars = vars;
        self
    }

    /// Add an environment variable to the guest environment.
    pub fn env_var(&mut self, name: &str, val: &str) -> &mut Self {
        self.inner
            .env_vars
            .insert(name.to_string(), val.to_string());
        self
    }

    /// TODO
    pub fn add_input<T: Pod>(&mut self, slice: &[T]) -> &mut Self {
        self.inner
            .input
            .extend_from_slice(bytemuck::cast_slice(slice));
        self
    }

    /// Add a handler for a raw syscall implementation.
    pub fn syscall(
        &mut self,
        syscall: SyscallName,
        handler: Rc<RefCell<dyn Syscall>>,
    ) -> &mut Self {
        self.inner
            .syscalls
            .inner
            .insert(syscall.as_str().to_string(), handler);
        self
    }

    /// Add a posix-style file descriptor for reading
    pub fn stdin(&mut self, reader: Rc<RefCell<dyn BufRead>>) -> &mut Self {
        self.inner.io.with_read_fd(fileno::STDIN, reader);
        self
    }

    /// Add a posix-style file descriptor for reading.
    pub fn read_fd(&mut self, fd: u32, reader: Rc<RefCell<dyn BufRead>>) -> &mut Self {
        self.inner.io.with_read_fd(fd, reader);
        self
    }

    /// Add a posix-style file descriptor for writing.
    pub fn write_fd(&mut self, fd: u32, writer: Rc<RefCell<dyn Write>>) -> &mut Self {
        self.inner.io.with_write_fd(fd, writer);
        self
    }

    // pub fn slice_io(self, syscall: SyscallName, handler: impl SliceIo + 'a)
    // -> Self { self.with_syscall(syscall, handler.to_syscall())
    // }

    // pub fn sendrecv_callback(
    //     self,
    //     syscall: SyscallName,
    //     f: impl Fn(&[u8]) -> Vec<u8> + 'a,
    // ) -> Self {
    //     self.with_slice_io(syscall, io::slice_io_from_fn(f))
    // }
}
