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

//! This module defines the [ExecutorEnv] and [ExecutorEnvBuilder].

use std::{
    cell::RefCell,
    collections::HashMap,
    io::{BufRead, BufReader, Cursor, Read, Write},
    mem,
    path::{Path, PathBuf},
    rc::Rc,
    sync::Arc,
};

use anyhow::Result;
use bytemuck::Pod;
use bytes::Bytes;
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::{self, fileno};
use serde::Serialize;
use tempfile::TempDir;

#[cfg(feature = "prove")]
use crate::Assumption;
use crate::{
    host::client::{
        posix_io::PosixIo,
        slice_io::{slice_io_from_fn, SliceIo, SliceIoTable},
    },
    serde::to_vec,
    AssumptionReceipt, TraceCallback,
};

/// A builder pattern used to construct an [ExecutorEnv].
#[derive(Default)]
pub struct ExecutorEnvBuilder<'a> {
    inner: ExecutorEnv<'a>,
}

/// Container for assumptions in the executor environment.
#[derive(Debug, Default)]
pub(crate) struct AssumptionReceipts {
    pub(crate) cached: Vec<AssumptionReceipt>,
    // An ordered list of assumptions accessed during execution, along a receipt if available. Each
    // time an assumption is used, it is cloned and pushed to the head of the list.
    #[cfg(feature = "prove")]
    pub(crate) accessed: Vec<(Assumption, AssumptionReceipt)>,
}

#[allow(dead_code)]
#[derive(Clone)]
pub enum SegmentPath {
    TempDir(Arc<TempDir>),
    Path(PathBuf),
}

impl SegmentPath {
    pub(crate) fn path(&self) -> &Path {
        match self {
            Self::TempDir(dir) => dir.path(),
            Self::Path(path) => path.as_path(),
        }
    }
}

/// The [Executor][crate::Executor] is configured from this object.
///
/// The executor environment holds configuration details that inform how the
/// guest environment is set up prior to guest program execution.
#[derive(Default)]
pub struct ExecutorEnv<'a> {
    pub(crate) env_vars: HashMap<String, String>,
    pub(crate) args: Vec<String>,
    pub(crate) segment_limit_po2: Option<u32>,
    pub(crate) session_limit: Option<u64>,
    pub(crate) posix_io: Rc<RefCell<PosixIo<'a>>>,
    pub(crate) slice_io: Rc<RefCell<SliceIoTable<'a>>>,
    pub(crate) input: Vec<u8>,
    pub(crate) trace: Vec<Rc<RefCell<dyn TraceCallback + 'a>>>,
    pub(crate) assumptions: Rc<RefCell<AssumptionReceipts>>,
    pub(crate) segment_path: Option<SegmentPath>,
    pub(crate) pprof_out: Option<PathBuf>,
    pub(crate) input_digest: Option<Digest>,
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
    ///
    /// After calling `build`, the [ExecutorEnvBuilder] will be reset to
    /// default.
    pub fn build(&mut self) -> Result<ExecutorEnv<'a>> {
        let mut inner = mem::take(&mut self.inner);

        if !inner.input.is_empty() {
            let reader = Cursor::new(inner.input.clone());
            inner
                .posix_io
                .borrow_mut()
                .with_read_fd(fileno::STDIN, reader);
        }

        if inner.pprof_out.is_none() {
            if let Ok(env_var) = std::env::var("RISC0_PPROF_OUT") {
                inner.pprof_out = Some(env_var.into());
            }
        }

        Ok(inner)
    }

    /// Set a segment limit, specified in powers of 2 cycles.
    ///
    /// Given value must be between [risc0_zkp::MIN_CYCLES_PO2] and
    /// [risc0_zkp::MAX_CYCLES_PO2] (inclusive).
    pub fn segment_limit_po2(&mut self, limit: u32) -> &mut Self {
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
    pub fn session_limit(&mut self, limit: Option<u64>) -> &mut Self {
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

    /// Add an argument array to the guest environment.
    ///
    /// # Example
    /// ```
    /// # use risc0_zkvm::ExecutorEnv;
    ///
    /// let env = ExecutorEnv::builder()
    ///     .args(&["grep".to_string(), "-c".to_string(), "foo".to_string(), "-".to_string()])
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn args(&mut self, args: &[String]) -> &mut Self {
        self.inner.args.extend_from_slice(args);
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

    /// Write input data to the zkVM guest stdin.
    ///
    /// This function will serialize `data` using a zkVM-optimized codec that
    /// can be deserialized in the guest with a corresponding `env::read` with
    /// the same data type.
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    /// use serde::Serialize;
    ///
    /// #[derive(Serialize)]
    /// struct Input {
    ///     a: u32,
    ///     b: u32,
    /// }
    ///
    /// let input1 = Input{ a: 1, b: 2 };
    /// let input2 = Input{ a: 3, b: 4 };
    /// let env = ExecutorEnv::builder()
    ///     .write(&input1).unwrap()
    ///     .write(&input2).unwrap()
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn write<T: Serialize>(&mut self, data: &T) -> Result<&mut Self> {
        Ok(self.write_slice(&to_vec(data)?))
    }

    /// Write input data to the zkVM guest stdin.
    ///
    /// This function writes a slice directly to the underlying buffer. A
    /// corresponding `env::read_slice` can be used within the guest to read the
    /// data.
    ///
    /// # Example
    ///
    /// ```
    /// use risc0_zkvm::ExecutorEnv;
    ///
    /// let slice1 = [0, 1, 2, 3];
    /// let slice2 = [3, 2, 1, 0];
    /// let env = ExecutorEnv::builder()
    ///     .write_slice(&slice1)
    ///     .write_slice(&slice2)
    ///     .build()
    ///     .unwrap();
    /// ```
    pub fn write_slice<T: Pod>(&mut self, slice: &[T]) -> &mut Self {
        self.inner
            .input
            .extend_from_slice(bytemuck::cast_slice(slice));
        self
    }

    /// Write a frame to the zkVM guest via stdin.
    ///
    /// A frame contains a length header along with the payload. Reading a frame
    /// can be more efficient than deserializing a message on-demand. On-demand
    /// deserialization can cause many syscalls, whereas a frame will only have
    /// two.
    #[stability::unstable]
    pub fn write_frame(&mut self, payload: &[u8]) -> &mut Self {
        let len = payload.len() as u32;
        self.inner.input.extend_from_slice(&len.to_le_bytes());
        self.inner.input.extend_from_slice(payload);
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

    /// Add an [AssumptionReceipt] to the [ExecutorEnv], for use in [composition].
    ///
    /// During execution, when the guest calls `env::verify` or `env::verify_integrity`, this
    /// collection will be searched for an [AssumptionReceipt] that corresponds the verification
    /// call.
    ///
    /// Either a [crate::Receipt] or a [crate::ReceiptClaim] can be provided. If a [crate::Receipt]
    /// is provided, then an [AssumptionReceipt::Proven] will be added to the [ExecutorEnv]
    /// and the [crate::Receipt] generated by proving will be unconditional.
    ///
    /// [composition]: https://dev.risczero.com/terminology#composition
    pub fn add_assumption(&mut self, assumption: impl Into<AssumptionReceipt>) -> &mut Self {
        self.inner
            .assumptions
            .borrow_mut()
            .cached
            .push(assumption.into());
        self
    }

    /// Add a callback handler for raw trace messages.
    pub fn trace_callback(&mut self, callback: impl TraceCallback + 'a) -> &mut Self {
        self.inner.trace.push(Rc::new(RefCell::new(callback)));
        self
    }

    /// Set the path where segments will be stored.
    pub fn segment_path<P: AsRef<Path>>(&mut self, path: P) -> &mut Self {
        self.inner.segment_path = Some(SegmentPath::Path(path.as_ref().to_path_buf()));
        self
    }

    /// Enable the profiler and output results to the specified path.
    pub fn enable_profiler<P: AsRef<Path>>(&mut self, path: P) -> &mut Self {
        self.inner.pprof_out = Some(path.as_ref().to_path_buf());
        self
    }

    /// Set the input digest.
    pub fn input_digest(&mut self, digest: Digest) -> &mut Self {
        self.inner.input_digest = Some(digest);
        self
    }
}
