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

//! The execution phase is implemented by this module.
//!
//! The result of the execution phase is a [crate::Session]. Each
//! [crate::Session] contains one or more [crate::Segment]s, each of which
//! contains an execution trace of the specified program.

pub(crate) mod executor;
mod gdb;
pub(crate) mod profiler;
mod proto;
pub(crate) mod syscall;
#[cfg(test)]
mod tests;

use std::{
    io::{ErrorKind, Write},
    sync::{Arc, Mutex},
};

// Capture the journal output in a buffer that we can access afterwards.
#[derive(Clone, Default)]
struct Journal {
    buf: Arc<Mutex<Vec<u8>>>,
}

impl Journal {
    /// Wrap the [Journal] in a writer that limits the total amount of data that can be written.
    pub(crate) fn limit_writer(&self, limit: usize) -> impl Write + 'static {
        struct LimitedWriter {
            journal: Journal,
            limit: usize,
        }

        impl Write for LimitedWriter {
            fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
                let mut vec = self.journal.buf.lock().unwrap();
                if buf.len() + vec.len() > self.limit {
                    let err =
                        std::io::Error::new(ErrorKind::WriteZero, "journal write limit reached");
                    return Err(err);
                }
                vec.write(buf)
            }

            fn flush(&mut self) -> std::io::Result<()> {
                self.journal.flush()
            }
        }

        LimitedWriter {
            journal: self.clone(),
            limit,
        }
    }
}

impl Write for Journal {
    fn write(&mut self, bytes: &[u8]) -> std::io::Result<usize> {
        self.buf.lock().unwrap().write(bytes)
    }

    fn flush(&mut self) -> std::io::Result<()> {
        self.buf.lock().unwrap().flush()
    }
}
