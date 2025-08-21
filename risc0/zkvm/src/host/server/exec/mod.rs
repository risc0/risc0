// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
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
