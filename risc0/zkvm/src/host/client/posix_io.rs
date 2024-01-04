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
    collections::BTreeMap,
    io::{stderr, stdout, BufRead, Cursor, Write},
    rc::Rc,
};

use risc0_zkvm_platform::fileno;

/// Posix-style I/O
#[derive(Clone)]
pub struct PosixIo<'a> {
    pub(crate) read_fds: BTreeMap<u32, Rc<RefCell<dyn BufRead + 'a>>>,
    pub(crate) write_fds: BTreeMap<u32, Rc<RefCell<dyn Write + 'a>>>,
}

impl<'a> Default for PosixIo<'a> {
    fn default() -> Self {
        let mut new = Self {
            read_fds: Default::default(),
            write_fds: Default::default(),
        };
        new.with_read_fd(fileno::STDIN, Cursor::new(vec![]))
            .with_write_fd(fileno::STDOUT, stdout())
            .with_write_fd(fileno::STDERR, stderr());
        new
    }
}

impl<'a> PosixIo<'a> {
    pub fn with_read_fd(&mut self, fd: u32, reader: impl BufRead + 'a) -> &mut Self {
        self.read_fds.insert(fd, Rc::new(RefCell::new(reader)));
        self
    }

    pub fn with_write_fd(&mut self, fd: u32, writer: impl Write + 'a) -> &mut Self {
        self.write_fds.insert(fd, Rc::new(RefCell::new(writer)));
        self
    }
}
