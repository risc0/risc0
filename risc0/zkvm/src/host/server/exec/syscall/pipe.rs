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

use std::{
    cell::RefCell,
    collections::VecDeque,
    io::{Read, Write},
    rc::Rc,
};

use anyhow::{anyhow, Result};

use crate::host::client::posix_io::PosixIo;

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
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let posix_io = &ctx.syscall_table().posix_io;
        let pipe = Rc::new(RefCell::new(VecDeque::new()));
        (to_guest[0], to_guest[1]) = posix_io
            .borrow_mut()
            .alloc_pipe(pipe)
            .ok_or(anyhow!("Could not allocate pipe"))?;
        Ok((0, 0))
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
