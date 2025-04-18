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

use std::net::{TcpListener, TcpStream};

use super::executor::ExecutorImpl;
use anyhow::Result;
use gdbstub::{conn::ConnectionExt, stub::GdbStub};
use risc0_circuit_rv32im::execute::{
    gdb::Debugger as CircuitDebugger, Executor as CircuitExecutor,
};

type GdbConnection = Box<dyn ConnectionExt<Error = std::io::Error>>;

fn accept_socket() -> Result<TcpStream> {
    let sock = TcpListener::bind("127.0.0.1:0")?;
    eprintln!(
        "listening for debugger connections on {}",
        sock.local_addr()?
    );
    let (stream, addr) = sock.accept()?;
    eprintln!("debugger connected from {addr}");

    Ok(stream)
}

pub struct GdbExecutor<'a, 'b, 'c> {
    debugger: CircuitDebugger<'a, 'b, ExecutorImpl<'c>>,
    gdb_stub: GdbStub<'static, CircuitDebugger<'a, 'b, ExecutorImpl<'c>>, GdbConnection>,
}

impl<'a, 'b, 'c> GdbExecutor<'a, 'b, 'c> {
    pub fn new(exec: &'a mut ExecutorImpl<'c>) -> Result<Self>
    where
        'b: 'a,
        'b: 'c,
        'c: 'b,
    {
        let connection: GdbConnection = Box::new(accept_socket()?);
        let gdb_stub = GdbStub::new(connection);
        let exec = CircuitExecutor::new(
            exec.image.clone(),
            exec,
            exec.env.input_digest,
            exec.env.trace.clone(),
        );
        Ok(Self {
            debugger: CircuitDebugger::new(exec),
            gdb_stub,
        })
    }

    pub fn run(mut self) -> Result<()> {
        match self
            .gdb_stub
            .run_blocking::<CircuitDebugger<'a, 'b, ExecutorImpl<'c>>>(&mut self.debugger)
        {
            Ok(_) => println!("target terminated!"),
            Err(e) => {
                println!("gdbstub encountered a fatal error: {e}")
            }
        }
        Ok(())
    }
}
