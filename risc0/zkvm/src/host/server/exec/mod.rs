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

//! The execution phase is implemented by this module.
//!
//! The result of the execution phase is a [crate::Session]. Each
//! [crate::Session] contains one or more [crate::Segment]s, each of which
//! contains an execution trace of the specified program.

pub(crate) mod executor2;
pub(crate) mod profiler;
mod proto;
pub(crate) mod syscall;
#[cfg(test)]
mod tests;

use std::{
    io::Write,
    sync::{Arc, Mutex},
};

// Capture the journal output in a buffer that we can access afterwards.
#[derive(Clone, Default)]
struct Journal {
    buf: Arc<Mutex<Vec<u8>>>,
}

impl Write for Journal {
    fn write(&mut self, bytes: &[u8]) -> std::io::Result<usize> {
        self.buf.lock().unwrap().write(bytes)
    }

    fn flush(&mut self) -> std::io::Result<()> {
        self.buf.lock().unwrap().flush()
    }
}
