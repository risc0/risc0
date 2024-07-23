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

use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

use anyhow::anyhow;
use anyhow::Result;

use super::{Syscall, SyscallContext};

type Pipe = Rc<RefCell<VecDeque<u8>>>;

#[derive(Default)]
pub(crate) struct SysPipe {
    pipes: Vec<Pipe>,
}

impl Syscall for SysPipe {
    fn syscall(
        &mut self,
        _syscall: &str,
        ctx: &mut dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let pipe = Rc::new(RefCell::new(VecDeque::new()));
        self.pipes.push(pipe.clone());

        let posix_io = &ctx.syscall_table().posix_io;
        let read_fd = posix_io
            .borrow_mut()
            .alloc_shared_read_fd(pipe.clone())
            .ok_or(anyhow!("No free read file descriptors"))?;
        let write_fd = posix_io
            .borrow_mut()
            .alloc_shared_write_fd(pipe)
            .ok_or(anyhow!("No free write file descriptors"))?;

        // only write to_guest if both succeed
        (to_guest[0], to_guest[1]) = (read_fd, write_fd);

        Ok((0, 0))
    }
}
