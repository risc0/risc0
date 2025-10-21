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

use std::net::{SocketAddr, TcpListener};

use super::executor::{ExecutorImpl, circuit_version};
use anyhow::Result;
use gdbstub::{conn::ConnectionExt, stub::GdbStub};
use risc0_circuit_rv32im::execute::{
    Executor as CircuitExecutor, gdb::Debugger as CircuitDebugger,
};

type GdbConnection = Box<dyn ConnectionExt<Error = std::io::Error>>;

pub struct GdbExecutor<'a, 'b, 'c> {
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
        let listener = TcpListener::bind("127.0.0.1:0")?;

        let exec = CircuitExecutor::new(
            exec.image.clone(),
            exec,
            exec.env.input_digest,
            exec.env.trace.clone(),
            // NOTE: PoVW nonce has no effect on execution.
            None,
            circuit_version(),
        );
        Ok(Self {
            debugger: CircuitDebugger::new(exec),
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
