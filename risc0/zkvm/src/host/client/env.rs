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

//! This module defines the [ExecutorEnv] and [ExecutorEnvBuilder].

use std::{
    cell::RefCell,
    collections::HashMap,
    io::{BufRead, BufReader, Cursor, Read, Write},
    rc::Rc,
};

use anyhow::Result;
use bytemuck::Pod;
use bytes::Bytes;
use risc0_zkvm_platform::{self, fileno};

use super::{
    exec::TraceEvent,
    posix_io::PosixIo,
    slice_io::{slice_io_from_fn, SliceIo, SliceIoTable},
};

/// A builder pattern used to construct an [ExecutorEnv].
#[derive(Clone, Default)]
pub struct ExecutorEnvBuilder<'a> {
    inner: ExecutorEnv<'a>,
}

/// A callback used to collect [TraceEvent]s.
pub type TraceCallback<'a> = dyn FnMut(TraceEvent) -> Result<()> + 'a;

/// The [crate::Executor] is configured from this object.
///
/// The executor environment holds configuration details that inform how the
/// guest environment is set up prior to guest program execution.
#[derive(Clone, Default)]
pub struct ExecutorEnv<'a> {
    pub(crate) env_vars: HashMap<String, String>,
    pub(crate) segment_limit_po2: Option<usize>,
    pub(crate) session_limit: Option<usize>,
    pub(crate) posix_io: Rc<RefCell<PosixIo<'a>>>,
    pub(crate) slice_io: Rc<RefCell<SliceIoTable<'a>>>,
    pub(crate) input: Vec<u8>,
    pub(crate) trace: Option<Rc<RefCell<TraceCallback<'a>>>>,
}

impl<'a> ExecutorEnv<'a> {
    /// Construct a [ExecutorEnvBuilder].
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let env = ExecutorEnv::builder().build();
    /// ```
    pub fn builder() -> ExecutorEnvBuilder<'a> {
        ExecutorEnvBuilder::default()
    }
}

impl<'a> ExecutorEnvBuilder<'a> {
    /// Finalize this builder to construct an [ExecutorEnv].
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let env = ExecutorEnv::builder().build().unwrap();
    /// ```
    pub fn build(&mut self) -> Result<ExecutorEnv<'a>> {
        let inner = self.inner.clone();

        if !inner.input.is_empty() {
            let reader = Cursor::new(inner.input.clone());
            inner
                .posix_io
                .borrow_mut()
                .with_read_fd(fileno::STDIN, reader);
        }

        Ok(inner)
    }

    /// Set a segment limit, specified in powers of 2 cycles.
    ///
    /// Given value must be between [risc0_zkp::MIN_CYCLES_PO2] and
    /// [risc0_zkp::MAX_CYCLES_PO2] (inclusive).
    pub fn segment_limit_po2(&mut self, limit: usize) -> &mut Self {
        self.inner.segment_limit_po2 = Some(limit);
        self
    }

    /// Set a session limit, specified in number of cycles.
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let env = ExecutorEnv::builder()
    ///     .session_limit(Some(32 * 1024 * 1024)) // 32M cycles
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn session_limit(&mut self, limit: Option<usize>) -> &mut Self {
        self.inner.session_limit = limit;
        self
    }

    /// Add environment variables to the guest environment.
    ///
    /// # Example
    ///
    /// ```
    /// use std::collections::HashMap;
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let mut vars = HashMap::new();
    /// vars.insert("VAR1".to_string(), "SOME_VALUE".to_string());
    /// vars.insert("VAR2".to_string(), "SOME_VALUE".to_string());
    ///
    /// let env = ExecutorEnv::builder()
    ///     .env_vars(vars)
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn env_vars(&mut self, vars: HashMap<String, String>) -> &mut Self {
        self.inner.env_vars = vars;
        self
    }

    /// Add an environment variable to the guest environment.
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let env = ExecutorEnv::builder()
    ///     .env_var("VAR1", "SOME_VALUE")
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn env_var(&mut self, name: &str, val: &str) -> &mut Self {
        self.inner
            .env_vars
            .insert(name.to_string(), val.to_string());
        self
    }

    /// Add initial input that can be read by the guest from stdin.
    ///
    /// Calling `add_input` iteratively concatenates inputs; the guest can
    /// access each input using consecutive reads.
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    /// use risc0_zkvm::serde::to_vec;
    ///
    /// let a: u64 = 400;
    /// let b: u64 = 200;
    ///
    /// let env = ExecutorEnv::builder()
    ///     .add_input(&to_vec(&a).unwrap())
    ///     .add_input(&to_vec(&b).unwrap())
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn add_input<T: Pod>(&mut self, slice: &[T]) -> &mut Self {
        self.inner
            .input
            .extend_from_slice(bytemuck::cast_slice(slice));
        self
    }

    /// Add a posix-style standard input.
    pub fn stdin(&mut self, reader: impl Read + 'a) -> &mut Self {
        self.read_fd(fileno::STDIN, BufReader::new(reader))
    }

    /// Add a posix-style standard output.
    pub fn stdout(&mut self, writer: impl Write + 'a) -> &mut Self {
        self.write_fd(fileno::STDOUT, writer)
    }

    /// Add a posix-style standard error.
    pub fn stderr(&mut self, writer: impl Write + 'a) -> &mut Self {
        self.write_fd(fileno::STDERR, writer)
    }

    /// Add a posix-style file descriptor for reading.
    pub fn read_fd(&mut self, fd: u32, reader: impl BufRead + 'a) -> &mut Self {
        self.inner.posix_io.borrow_mut().with_read_fd(fd, reader);
        self
    }

    /// Add a posix-style file descriptor for writing.
    pub fn write_fd(&mut self, fd: u32, writer: impl Write + 'a) -> &mut Self {
        self.inner.posix_io.borrow_mut().with_write_fd(fd, writer);
        self
    }

    /// Add a handler for simple I/O handling.
    pub fn slice_io(&mut self, channel: &str, handler: impl SliceIo + 'a) -> &mut Self {
        self.inner
            .slice_io
            .borrow_mut()
            .with_handler(channel, handler);
        self
    }

    /// Add a handler for simple I/O handling.
    pub fn io_callback<C: AsRef<str>>(
        &mut self,
        channel: C,
        callback: impl Fn(Bytes) -> Result<Bytes> + 'a,
    ) -> &mut Self {
        self.inner
            .slice_io
            .borrow_mut()
            .with_handler(channel.as_ref(), slice_io_from_fn(callback));
        self
    }

    /// Add a callback handler for raw trace messages.
    pub fn trace_callback(
        &mut self,
        callback: impl FnMut(TraceEvent) -> Result<()> + 'a,
    ) -> &mut Self {
        self.inner.trace = Some(Rc::new(RefCell::new(callback)));
        self
    }
}
