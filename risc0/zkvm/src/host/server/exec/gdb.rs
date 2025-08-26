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
use anyhow::Result;
use anyhow::anyhow;
use gdbstub::{conn::ConnectionExt, stub::GdbStub};
use risc0_circuit_rv32im::execute::{
    Executor as CircuitExecutor, gdb::Debugger as CircuitDebugger,
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
            // NOTE: PoVW nonce has no effect on execution.
            None,
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

#[cfg(test)]
mod tests {
    use super::*;
    use crate::ExecutorEnv;
    use risc0_zkvm_methods::{MULTI_TEST_ELF, multi_test::MultiTestSpec};

    #[test]
    fn end_to_end() {
        let (send, recv) = std::sync::mpsc::channel();

        std::thread::spawn(move || {
            let env = ExecutorEnv::builder()
                .write(&MultiTestSpec::Profiler)
                .unwrap()
                .build()
                .unwrap();
            let mut exec = ExecutorImpl::from_elf(env, MULTI_TEST_ELF).unwrap();
            let debugger = GdbExecutor::new(&mut exec).unwrap();
            let elf_path = debugger.elf_path().to_owned();
            let address = debugger.local_addr().unwrap();
            send.send((elf_path, address)).unwrap();
            debugger.run().unwrap();
        });

        let (elf_path, address) = recv.recv().unwrap();

        let rzup = rzup::Rzup::new().unwrap();
        let (_, path) = rzup
            .get_default_version(&rzup::Component::Gdb)
            .unwrap()
            .unwrap();
        let gdb_bin = path.join("riscv32im-gdb");

        let mut gdb_script = NamedTempFile::with_suffix(".txt").unwrap();
        writeln!(&mut gdb_script, "target remote {address}").unwrap();
        writeln!(
            &mut gdb_script,
            "break multi_test::profiler::profile_test_func1"
        )
        .unwrap();
        writeln!(&mut gdb_script, "continue").unwrap();
        writeln!(&mut gdb_script, "bt").unwrap();
        gdb_script.flush().unwrap();

        let gdb_output = std::process::Command::new(gdb_bin)
            .arg("-x")
            .arg(gdb_script.path())
            .arg(elf_path)
            .output()
            .unwrap();
        assert!(
            gdb_output.status.success(),
            "{}",
            String::from_utf8_lossy(&gdb_output.stderr)
        );
        let output_str = String::from_utf8_lossy(&gdb_output.stdout);

        let start = output_str
            .find("Reading symbols")
            .unwrap_or_else(|| panic!("\"Reading symbols\" not found in: {output_str}"));
        let end = output_str
            .find("\tInferior 1 [process 1] will be detached.")
            .unwrap_or_else(|| {
                panic!("\"Inferior 1 [process 1] will be detached\" not found in: {output_str}")
            });

        let reg = regex::Regex::new(
            "\
            Reading symbols from .*\\.elf\\.\\.\\.\n\
            0xc0000000 in \\?\\? \\(\\)\n\
            Breakpoint 1 at 0x[0-9a-f]*: file src/bin/multi_test/profiler.rs, line [0-9]+\\.\n\n\
            Breakpoint 1, multi_test::profiler::profile_test_func1 \\(\\)\n\
            \\s+at src/bin/multi_test/profiler.rs:[0-9]+\n\
            [0-9]+\t    profile_test_func2\\(\\);\n\
            #0  multi_test::profiler::profile_test_func1 \\(\\)\n\
            \\s+at src/bin/multi_test/profiler.rs:[0-9]+\n.*\
            #1  0x002[0-9a-f]* in multi_test::main \\(\\) at src/bin/multi_test.rs:[0-9]+\n\
            #2  0x002[0-9a-f]* in risc0_zkvm::guest::__start \\(\\) at src/guest/mod.rs:[0-9]+\n\
            #3  0x002[0-9a-f]* in _start \\(\\)\n\
            Backtrace stopped: frame did not save the PC\n\
            \\(gdb\\) A debugging session is active.\n\n\
            ",
        )
        .unwrap();
        let to_match = &output_str[start..end];
        assert!(reg.is_match(to_match), "{to_match}");
    }
}
