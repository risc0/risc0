// Copyright 2022 Risc0, Inc.
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

pub mod exec;

use std::io::Write;

use anyhow::Result;
use risc0_zkp::{
    core::sha::default_implementation, hal::cpu::CpuHal, prove::adapter::ProveAdapter,
};

use crate::{
    elf::Program,
    host::ProverOpts,
    method_id::MethodId,
    platform::{
        io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_STDERR, SENDRECV_CHANNEL_STDOUT},
        memory::MEM_SIZE,
    },
    receipt::Receipt,
};

use self::exec::{IoHandler, RV32Executor};

pub struct Prover<'a> {
    elf: Program,
    inner: ProverImpl,
    method_id: MethodId,
    opts: ProverOpts<'a>,
}

impl<'a> Prover<'a> {
    pub fn new(elf: &[u8], method_id: &[u8]) -> Result<Self> {
        Self::new_with_opts(elf, method_id, ProverOpts::default())
    }

    pub fn new_with_opts(elf: &[u8], method_id: &[u8], opts: ProverOpts<'a>) -> Result<Self> {
        Ok(Prover {
            elf: Program::load_elf(&elf, MEM_SIZE as u32)?,
            inner: ProverImpl::new(),
            method_id: MethodId::from_slice(method_id).unwrap(),
            opts,
        })
    }

    pub fn add_input_u8_slice(&mut self, slice: &[u8]) {
        self.inner.input.extend_from_slice(slice);
    }

    pub fn add_input_u32_slice(&mut self, slice: &[u32]) {
        self.inner
            .input
            .extend_from_slice(bytemuck::cast_slice(slice));
    }

    pub fn get_output(&self) -> Result<&[u8]> {
        Ok(&self.inner.output)
    }

    pub fn run(&mut self) -> Result<Receipt> {
        let mut executor = RV32Executor::new(&self.elf, &mut self.inner);
        executor.run()?;

        let mut prover = ProveAdapter::new(&mut executor.executor);
        let hal = CpuHal {};
        let sha = default_implementation();
        let seal = risc0_zkp::prove::prove(&hal, sha, &mut prover);

        // Attach the full version of the output journal & construct receipt object
        let receipt = Receipt {
            journal: self.inner.commit.clone(),
            seal,
        };

        // Verify receipt to make sure it works
        // TODO
        // receipt.verify(&self.method_id)?;

        Ok(receipt)
    }
}

struct ProverImpl {
    pub input: Vec<u8>,
    pub output: Vec<u8>,
    pub commit: Vec<u32>,
}

impl ProverImpl {
    fn new() -> Self {
        Self {
            input: Vec::new(),
            output: Vec::new(),
            commit: Vec::new(),
        }
    }
}

impl IoHandler for ProverImpl {
    fn on_txrx(&mut self, channel: u32, buf: &[u8]) -> Vec<u8> {
        match channel {
            SENDRECV_CHANNEL_INITIAL_INPUT => {
                log::debug!("SENDRECV_CHANNEL_INITIAL_INPUT: {}", buf.len());
                self.input.clone()
            }
            SENDRECV_CHANNEL_STDOUT => {
                log::debug!("SENDRECV_CHANNEL_STDOUT: {}", buf.len());
                // TODO
                Vec::new()
            }
            SENDRECV_CHANNEL_STDERR => {
                log::debug!("SENDRECV_CHANNEL_STDERR: {}", buf.len());
                std::io::stderr().lock().write_all(buf);
                Vec::new()
            }
            _ => panic!("Unknown channel: {channel}"),
        }
    }

    fn on_commit(&mut self, buf: &[u32]) {
        self.commit.extend_from_slice(buf);
    }

    fn on_fault(&mut self, msg: &str) {
        panic!("{}", msg);
    }
}
