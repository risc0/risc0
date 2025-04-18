// Copyright 2025 RISC Zero, Inc.
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

use std::io::Write as _;
use std::net::{SocketAddr, TcpListener};
use std::path::Path;

use super::executor::ExecutorImpl;
use anyhow::anyhow;
use anyhow::Result;
use gdbstub::{conn::ConnectionExt, stub::GdbStub};
use risc0_circuit_rv32im::execute::{
    gdb::Debugger as CircuitDebugger, Executor as CircuitExecutor,
};
use tempfile::NamedTempFile;

type GdbConnection = Box<dyn ConnectionExt<Error = std::io::Error>>;

pub struct GdbExecutor<'a, 'b, 'c> {
    pub(crate) elf: NamedTempFile,
    debugger: CircuitDebugger<'a, 'b, ExecutorImpl<'c>>,
    pub(crate) listener: TcpListener,
}

impl<'a, 'b, 'c> GdbExecutor<'a, 'b, 'c> {
    pub fn new(exec: &'a mut ExecutorImpl<'c>) -> Result<Self>
    where
        'b: 'a,
        'b: 'c,
        'c: 'b,
    {
        let mut elf = NamedTempFile::with_suffix(".elf")?;
        elf.write_all(
            exec.elf
                .as_ref()
                .ok_or_else(|| anyhow!("cannot run debugger without elf"))?,
        )?;
        elf.flush()?;

        let listener = TcpListener::bind("127.0.0.1:0")?;

        let exec = CircuitExecutor::new(
            exec.image.clone(),
            exec,
            exec.env.input_digest,
            exec.env.trace.clone(),
        );
        Ok(Self {
            elf,
            debugger: CircuitDebugger::new(exec),
            listener,
        })
    }

    pub fn local_addr(&self) -> Result<SocketAddr> {
        Ok(self.listener.local_addr()?)
    }

    pub fn elf_path(&self) -> &Path {
        self.elf.path()
    }

    pub fn run(mut self) -> Result<()> {
        let (stream, addr) = self.listener.accept()?;
        eprintln!("debugger connected from {addr}");

        let connection: GdbConnection = Box::new(stream);
        let gdb_stub = GdbStub::new(connection);

        match gdb_stub.run_blocking::<CircuitDebugger<'a, 'b, ExecutorImpl<'c>>>(&mut self.debugger)
        {
            Ok(_) => eprintln!("target terminated!"),
            Err(e) => {
                eprintln!("gdbstub encountered a fatal error: {e}")
            }
        }
        Ok(())
    }
}
