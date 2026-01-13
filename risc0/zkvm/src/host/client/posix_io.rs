// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{
    cell::RefCell,
    collections::BTreeMap,
    io::{Cursor, Read, Write, stderr, stdout},
    rc::Rc,
};

use anyhow::{Result, anyhow};

use risc0_zkvm_platform::fileno;

type SharedRead<'a> = Rc<RefCell<dyn Read + 'a>>;
type SharedWrite<'a> = Rc<RefCell<dyn Write + 'a>>;

/// Posix-style I/O
#[derive(Clone)]
pub struct PosixIo<'a> {
    pub(crate) read_fds: BTreeMap<u32, SharedRead<'a>>,
    pub(crate) write_fds: BTreeMap<u32, SharedWrite<'a>>,
}

impl Default for PosixIo<'_> {
    fn default() -> Self {
        let mut new = Self::new();
        new.with_read_fd(fileno::STDIN, Cursor::new(vec![]))
            .with_write_fd(fileno::STDOUT, stdout())
            .with_write_fd(fileno::STDERR, stderr());
        new
    }
}

impl<'a> PosixIo<'a> {
    pub fn new() -> Self {
        Self {
            read_fds: Default::default(),
            write_fds: Default::default(),
        }
    }

    pub fn with_read_fd(&mut self, fd: u32, reader: impl Read + 'a) -> &mut Self {
        self.with_shared_read_fd(fd, Rc::new(RefCell::new(reader)))
    }

    pub fn with_shared_read_fd<T>(&mut self, fd: u32, reader: Rc<RefCell<T>>) -> &mut Self
    where
        T: Read + 'a,
    {
        self.read_fds.insert(fd, reader);
        self
    }

    pub fn with_write_fd(&mut self, fd: u32, writer: impl Write + 'a) -> &mut Self {
        self.with_shared_write_fd(fd, Rc::new(RefCell::new(writer)))
    }

    pub fn with_shared_write_fd<T>(&mut self, fd: u32, writer: Rc<RefCell<T>>) -> &mut Self
    where
        T: Write + 'a,
    {
        self.write_fds.insert(fd, writer);
        self
    }

    #[cfg(feature = "prove")]
    pub fn get_reader(&self, fd: u32) -> Result<SharedRead<'a>> {
        self.read_fds
            .get(&fd)
            .ok_or_else(|| anyhow!("Bad read file descriptor {fd}"))
            .cloned()
    }

    pub fn get_writer(&self, fd: u32) -> Result<SharedWrite<'a>> {
        self.write_fds
            .get(&fd)
            .ok_or_else(|| anyhow!("Bad write file descriptor {fd}"))
            .cloned()
    }
}
