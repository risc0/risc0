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

use std::{
    io::{BufReader, BufWriter},
    path::Path,
    process::{Command, Stdio},
};

use anyhow::{anyhow, Result};
use bytes::Bytes;
use serde::{Deserialize, Serialize};

use crate::ExecutorEnv;

/// An event traced from the running VM.
#[derive(Clone, Eq, Ord, PartialEq, PartialOrd, Serialize, Deserialize)]
pub enum TraceEvent {
    /// An instruction has started at the given program counter
    InstructionStart {
        /// Cycle number since startup
        cycle: u32,
        /// Program counter of the instruction being executed
        pc: u32,
    },

    /// A register has been set
    RegisterSet {
        /// Register ID (0-16)
        reg: usize,
        /// New value in the register
        value: u32,
    },

    /// A memory location has been written
    MemorySet {
        /// Address of word that's been written
        addr: u32,
        /// Value of word that's been written
        value: u32,
    },
}

#[derive(Serialize, Deserialize)]
enum PosixCmd {
    ReadAvail,
    Read,
    Write,
}

#[derive(Serialize, Deserialize)]
enum IpcSyscall {
    Posix { fd: u32, cmd: PosixCmd },
    Io { name: String },
    Trace { event: TraceEvent },
    Exit,
}

#[derive(Serialize, Deserialize)]
struct IpcRequest {
    syscall: IpcSyscall,
    from_guest: Bytes,
}

#[derive(Serialize, Deserialize)]
struct IpcResponse {
    from_host: Bytes,
    result: u32,
}

impl Default for IpcResponse {
    fn default() -> Self {
        Self {
            from_host: Default::default(),
            result: 0,
        }
    }
}

impl IpcResponse {
    fn new(from_host: Bytes, result: u32) -> Self {
        Self { from_host, result }
    }

    fn with_bytes(from_host: Bytes) -> Self {
        Self {
            from_host,
            result: 0,
        }
    }

    fn with_result(result: u32) -> Self {
        Self {
            from_host: Default::default(),
            result,
        }
    }
}

impl std::fmt::Debug for TraceEvent {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        match self {
            Self::InstructionStart { cycle, pc } => {
                write!(f, "InstructionStart({cycle}, 0x{pc:08X})")
            }
            Self::RegisterSet { reg, value } => write!(f, "RegisterSet({reg}, 0x{value:08X})"),
            Self::MemorySet { addr, value } => write!(f, "MemorySet(0x{addr:08X}, 0x{value:08X})"),
        }
    }
}

#[allow(dead_code)]
struct ExecutorClient {}

impl ExecutorClient {
    #[allow(dead_code)]
    pub fn new<P: AsRef<Path>>(env: ExecutorEnv<'_>, r0vm_path: P) {
        let r0vm_path = r0vm_path.as_ref();
        let mut child = Command::new(r0vm_path)
            .stdin(Stdio::piped())
            .stdout(Stdio::piped())
            .spawn()
            .unwrap();

        let mut reader = BufReader::new(child.stdout.take().unwrap());
        let mut writer = BufWriter::new(child.stdin.take().unwrap());

        while let Some(response) =
            dispatch(&env, bincode::deserialize_from(&mut reader).unwrap()).unwrap()
        {
            bincode::serialize_into(&mut writer, &response).unwrap();
        }

        let status = child.wait().unwrap();
        assert!(status.success());
    }
}

#[allow(dead_code)]
fn dispatch(env: &ExecutorEnv<'_>, request: IpcRequest) -> Result<Option<IpcResponse>> {
    Ok(match request.syscall {
        IpcSyscall::Posix { fd, cmd } => match cmd {
            PosixCmd::ReadAvail => {
                let posix_io = env.posix_io.borrow();
                let reader = posix_io
                    .read_fds
                    .get(&fd)
                    .ok_or(anyhow!("Bad read file descriptor: {fd}"))?;
                let result = reader.borrow_mut().fill_buf()?.len() as u32;
                Some(IpcResponse::with_result(result))
            }
            PosixCmd::Read => {
                let mut from_host = Vec::new();
                let posix_io = env.posix_io.borrow();
                let reader = posix_io
                    .read_fds
                    .get(&fd)
                    .ok_or(anyhow!("Bad read file descriptor: {fd}"))?;
                let nread = reader.borrow_mut().read_to_end(&mut from_host)? as u32;
                Some(IpcResponse::new(Bytes::from(from_host), nread))
            }
            PosixCmd::Write => {
                let posix_io = env.posix_io.borrow();
                let writer = posix_io
                    .write_fds
                    .get(&fd)
                    .ok_or(anyhow!("Bad write file descriptor: {fd}"))?;
                writer.borrow_mut().write_all(&request.from_guest)?;
                Some(IpcResponse::default())
            }
        },
        IpcSyscall::Io { name } => {
            let slice_io = env
                .slice_io
                .get(&name)
                .ok_or(anyhow!("Unknown io channel name: {name}"))?;
            let mut stored_buf = slice_io.stored_buf.borrow_mut();
            match stored_buf.take() {
                None => {
                    let mut callback = slice_io.callback.borrow_mut();
                    let buf = callback(Bytes::from(request.from_guest))?;
                    let result = buf.len() as u32;
                    *stored_buf = Some(buf);
                    Some(IpcResponse::with_result(result))
                }
                Some(buf) => Some(IpcResponse::with_bytes(buf)),
            }
        }
        IpcSyscall::Trace { event } => {
            if let Some(ref callback) = env.trace {
                callback.borrow_mut()(event)?;
            }
            Some(IpcResponse::default())
        }
        IpcSyscall::Exit => None,
    })
}
