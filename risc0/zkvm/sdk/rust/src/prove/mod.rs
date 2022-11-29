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

pub mod cpu_eval;
pub mod exec;
mod ffpu;

use std::io::Write;

use anyhow::{bail, Result};
use risc0_zkp::{
    core::sha::default_implementation,
    hal::{cpu::CpuHal, EvalCheck, Hal},
    prove::adapter::ProveAdapter,
};
use risc0_zkvm_platform::{
    io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_STDERR, SENDRECV_CHANNEL_STDOUT},
    memory::MEM_SIZE,
};

use self::cpu_eval::CpuEvalCheck;
use crate::{
    elf::Program,
    host::{ProverOpts, TraceEvent},
    method_id::MethodId,
    receipt::Receipt,
    CIRCUIT,
};

pub struct Prover<'a> {
    elf: Program,
    inner: ProverImpl<'a>,
    method_id: MethodId,
}

impl<'a> Prover<'a> {
    pub fn new(elf: &[u8], method_id: &[u8]) -> Result<Self> {
        Self::new_with_opts(elf, method_id, ProverOpts::default())
    }

    pub fn new_with_opts(elf: &[u8], method_id: &[u8], opts: ProverOpts<'a>) -> Result<Self> {
        Ok(Prover {
            elf: Program::load_elf(&elf, MEM_SIZE as u32)?,
            inner: ProverImpl::new(opts),
            method_id: MethodId::from_slice(method_id).unwrap(),
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
        let hal = CpuHal::new();
        let eval = CpuEvalCheck::new(&CIRCUIT);
        self.run_with_hal(&hal, &eval)
    }

    pub fn run_with_hal<H: Hal, E: EvalCheck<H>>(&mut self, hal: &H, eval: &E) -> Result<Receipt> {
        let skip_seal = self.inner.opts.skip_seal;

        let mut executor = exec::RV32Executor::new(&CIRCUIT, &self.elf, &mut self.inner);
        executor.run()?;

        let mut prover = ProveAdapter::new(&mut executor.executor);
        let sha = default_implementation();

        let seal = if skip_seal {
            risc0_zkp::prove::prove_without_seal(sha, &mut prover);
            Vec::new()
        } else {
            risc0_zkp::prove::prove(hal, sha, &mut prover, eval)
        };

        // Attach the full version of the output journal & construct receipt object
        let receipt = Receipt {
            journal: self.inner.commit.clone(),
            seal,
        };

        if !skip_seal {
            // Verify receipt to make sure it works
            receipt.verify(&self.method_id)?;
        }

        Ok(receipt)
    }
}

struct ProverImpl<'a> {
    pub input: Vec<u8>,
    pub output: Vec<u8>,
    pub commit: Vec<u32>,
    pub opts: ProverOpts<'a>,
}

impl<'a> ProverImpl<'a> {
    fn new(opts: ProverOpts<'a>) -> Self {
        Self {
            input: Vec::new(),
            output: Vec::new(),
            commit: Vec::new(),
            opts,
        }
    }
}

impl<'a> exec::IoHandler for ProverImpl<'a> {
    fn on_txrx(&mut self, channel: u32, buf: &[u8]) -> Result<Vec<u8>> {
        if let Some(cb) = self.opts.sendrecv_callbacks.get(&channel) {
            return Ok(cb(channel, buf));
        }
        match channel {
            SENDRECV_CHANNEL_INITIAL_INPUT => {
                log::debug!("SENDRECV_CHANNEL_INITIAL_INPUT: {}", buf.len());
                Ok(self.input.clone())
            }
            SENDRECV_CHANNEL_STDOUT => {
                log::debug!("SENDRECV_CHANNEL_STDOUT: {}", buf.len());
                self.output.extend(buf);
                Ok(Vec::new())
            }
            SENDRECV_CHANNEL_STDERR => {
                log::debug!("SENDRECV_CHANNEL_STDERR: {}", buf.len());
                std::io::stderr().lock().write_all(buf).unwrap();
                Ok(Vec::new())
            }
            _ => bail!("Unknown channel: {channel}"),
        }
    }

    fn is_trace_enabled(&self) -> bool {
        self.opts.trace_callback.is_some()
    }

    fn on_trace(&mut self, event: TraceEvent) -> Result<()> {
        if let Some(ref mut cb) = self.opts.trace_callback {
            cb(event)
        } else {
            Ok(())
        }
    }

    fn on_commit(&mut self, buf: &[u32]) -> Result<()> {
        self.commit.extend_from_slice(buf);
        Ok(())
    }

    fn on_fault(&mut self, msg: &str) -> Result<()> {
        bail!("{}", msg)
    }
}
