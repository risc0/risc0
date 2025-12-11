// Copyright 2025 RISC Zero, Inc.
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

use std::io::Write;
use std::net::{SocketAddr, TcpListener};

use crate::host::server::exec::executor::CircuitSyscallTable;

use super::executor::ExecutorImpl;
use anyhow::{Result, anyhow};
use gdbstub::{conn::ConnectionExt, stub::GdbStub};
use risc0_circuit_rv32im::execute::gdb::Debugger as CircuitDebugger;
use tempfile::NamedTempFile;

type GdbConnection = Box<dyn ConnectionExt<Error = std::io::Error>>;

pub struct GdbExecutor<'a, 'b> {
    #[allow(dead_code)] // Keeps the temp file alive while debugger runs
    pub(crate) elf: NamedTempFile,
    debugger: CircuitDebugger<'a, 'b, CircuitSyscallTable<'a>>,
    pub(crate) listener: TcpListener,
}

impl<'a, 'b> GdbExecutor<'a, 'b> {
    pub fn new(exec: &'b mut ExecutorImpl<'a>) -> Result<Self> {
        let mut elf = NamedTempFile::with_suffix(".elf")?;
        elf.write_all(
            exec.elf
                .as_ref()
                .ok_or_else(|| anyhow!("cannot run debugger without elf"))?,
        )?;
        elf.flush()?;

        let listener = TcpListener::bind("127.0.0.1:0")?;

        Ok(Self {
            elf,
            debugger: CircuitDebugger::new(&mut exec.inner),
            listener,
        })
    }

    pub fn local_addr(&self) -> Result<SocketAddr> {
        Ok(self.listener.local_addr()?)
    }

    pub fn run(mut self) -> Result<()> {
        let (stream, addr) = self.listener.accept()?;
        eprintln!("debugger connected from {addr}");

        let connection: GdbConnection = Box::new(stream);
        let gdb_stub = GdbStub::new(connection);

        match gdb_stub
            .run_blocking::<CircuitDebugger<'a, 'b, CircuitSyscallTable<'a>>>(&mut self.debugger)
        {
            Ok(_) => eprintln!("target terminated!"),
            Err(e) => {
                eprintln!("gdbstub encountered a fatal error: {e}")
            }
        }
        Ok(())
    }
}
