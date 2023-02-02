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

//! Run the zkVM guest and prove its results

mod exec;
pub(crate) mod loader;
mod plonk;
#[cfg(feature = "profiler")]
pub mod profiler;

use std::{collections::HashMap, fmt::Debug, io::Write, rc::Rc};

use anyhow::{bail, Result};
use risc0_circuit_rv32im::{REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA};
use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};
use risc0_zkp::{
    adapter::TapsProvider,
    core::sha::Digest,
    hal::{EvalCheck, Hal},
    prove::adapter::ProveAdapter,
};
use risc0_zkvm_platform::{
    io::{SENDRECV_CHANNEL_INITIAL_INPUT, SENDRECV_CHANNEL_STDERR, SENDRECV_CHANNEL_STDOUT},
    memory::MEM_SIZE,
    WORD_SIZE,
};

use crate::binfmt::elf::Program;
use crate::{
    receipt::{insecure_skip_seal, Receipt},
    sha, CIRCUIT,
};

/// Options available to modify the prover's behavior.
pub struct ProverOpts<'a> {
    pub(crate) skip_seal: bool,

    pub(crate) sendrecv_callbacks: HashMap<u32, Box<dyn Fn(u32, &[u8]) -> Vec<u8> + 'a + Sync>>,

    pub(crate) trace_callback: Option<Box<dyn FnMut(TraceEvent) -> Result<()> + 'a>>,
}

impl<'a> ProverOpts<'a> {
    /// If true, skip generating the seal in receipt.  This should
    /// only be used for testing.  In this case, performace will be
    /// much better but we will not be able to cryptographically
    /// verify the execution.
    pub fn with_skip_seal(self, skip_seal: bool) -> Self {
        Self { skip_seal, ..self }
    }

    /// Add a callback handler for sendrecv ports, indexed by channel
    /// numbers.  The guest can call these callbacks by invoking
    /// `risc0_zkvm::guest::env::send_recv`.
    pub fn with_sendrecv_callback(
        mut self,
        channel_id: u32,
        callback: impl Fn(u32, &[u8]) -> Vec<u8> + 'a + Sync,
    ) -> Self {
        self.sendrecv_callbacks
            .insert(channel_id, Box::new(callback));
        self
    }

    /// Add a callback handler for raw trace messages.
    pub fn with_trace_callback(
        mut self,
        callback: impl FnMut(TraceEvent) -> Result<()> + 'a,
    ) -> Self {
        assert!(!self.trace_callback.is_some(), "Duplicate trace callback");
        self.trace_callback = Some(Box::new(callback));
        self
    }
}

impl<'a> Default for ProverOpts<'a> {
    fn default() -> ProverOpts<'a> {
        ProverOpts {
            skip_seal: false,
            sendrecv_callbacks: HashMap::new(),
            trace_callback: None,
        }
    }
}

/// Manages communication with and execution of a zkVM [Program]
pub struct Prover<'a> {
    elf: Program,
    inner: ProverImpl<'a>,
    image_id: Digest,
    pub cycles: usize,
}

cfg_if::cfg_if! {
    if #[cfg(feature = "cuda")] {
        use risc0_circuit_rv32im::cuda::CudaEvalCheck;
        use risc0_zkp::hal::cuda::CudaHal;

        thread_local! {
            static HAL: (Rc<CudaHal>, CudaEvalCheck) = default_hal();
        }

        pub fn default_hal() -> (Rc<CudaHal>, CudaEvalCheck) {
            let hal = Rc::new(CudaHal::new());
            let eval = CudaEvalCheck::new(hal.clone());
            (hal, eval)
        }
    } else if #[cfg(feature = "metal")] {
        use risc0_circuit_rv32im::metal::MetalEvalCheck;
        use risc0_zkp::hal::metal::MetalHal;

        thread_local! {
            static HAL: (Rc<MetalHal>, MetalEvalCheck) = default_hal();
        }

        pub fn default_hal() -> (Rc<MetalHal>, MetalEvalCheck) {
            let hal = Rc::new(MetalHal::new());
            let eval = MetalEvalCheck::new(hal.clone());
            (hal, eval)
        }
    } else {
        use risc0_circuit_rv32im::{CircuitImpl, cpu::CpuEvalCheck};
        use risc0_zkp::hal::cpu::BabyBearCpuHal;

        thread_local! {
            static HAL: (Rc<BabyBearCpuHal>, CpuEvalCheck<'static, CircuitImpl>) = default_hal();
        }

        pub fn default_hal() -> (Rc<BabyBearCpuHal>, CpuEvalCheck<'static, CircuitImpl>) {
            let hal = Rc::new(BabyBearCpuHal::new());
            let eval = CpuEvalCheck::new(&CIRCUIT);
            (hal, eval)
        }
    }
}

impl<'a> Prover<'a> {
    pub fn new<D>(elf: &[u8], image_id: D) -> Result<Self>
    where
        Digest: From<D>,
    {
        Self::new_with_opts(elf, image_id, ProverOpts::default())
    }

    pub fn new_with_opts<D>(elf: &[u8], image_id: D, opts: ProverOpts<'a>) -> Result<Self>
    where
        Digest: From<D>,
    {
        Ok(Prover {
            elf: Program::load_elf(&elf, MEM_SIZE as u32)?,
            inner: ProverImpl::new(opts),
            image_id: image_id.into(),
            cycles: 0,
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

    pub fn get_output_u8_slice(&self) -> &[u8] {
        &self.inner.output
    }

    pub fn get_output_u32_vec(&self) -> Result<Vec<u32>> {
        if self.inner.output.len() % WORD_SIZE != 0 {
            bail!("Private output must be word-aligned");
        }
        Ok(self
            .inner
            .output
            .chunks_exact(WORD_SIZE)
            .map(|x| u32::from_ne_bytes(x.try_into().unwrap()))
            .collect())
    }

    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<Receipt> {
        HAL.with(|(hal, eval)| {
            cfg_if::cfg_if! {
                if #[cfg(feature = "dual")] {
                    let cpu_hal = risc0_zkp::hal::cpu::BabyBearCpuHal::new();
                    let cpu_eval = risc0_circuit_rv32im::cpu::CpuEvalCheck::new(&CIRCUIT);
                    let hal = risc0_zkp::hal::dual::DualHal::new(hal.as_ref(), &cpu_hal);
                    let eval = risc0_zkp::hal::dual::DualEvalCheck::new(eval, &cpu_eval);
                    self.run_with_hal(&hal, &eval)
                } else {
                    self.run_with_hal(hal.as_ref(), eval)
                }
            }
        })
    }

    #[tracing::instrument(skip_all)]
    pub fn run_with_hal<H, E>(&mut self, hal: &H, eval: &E) -> Result<Receipt>
    where
        H: Hal<Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
        E: EvalCheck<H>,
    {
        let skip_seal = self.inner.opts.skip_seal || insecure_skip_seal();

        let mut executor = exec::RV32Executor::new(&CIRCUIT, &self.elf, &mut self.inner);
        self.cycles = executor.run()?;

        let mut adapter = ProveAdapter::new(&mut executor.executor);
        let mut prover = risc0_zkp::prove::Prover::<_, sha::Impl>::new(hal, CIRCUIT.get_taps());

        adapter.execute(prover.iop());

        let seal = if skip_seal {
            Vec::new()
        } else {
            prover.set_po2(adapter.po2() as usize);

            prover.commit_group(
                REGISTER_GROUP_CODE,
                hal.copy_from_elem("code", adapter.get_code()),
            );
            prover.commit_group(
                REGISTER_GROUP_DATA,
                hal.copy_from_elem("data", adapter.get_data()),
            );
            adapter.accumulate(prover.iop());
            prover.commit_group(
                REGISTER_GROUP_ACCUM,
                hal.copy_from_elem("accum", adapter.get_accum()),
            );

            let mix = hal.copy_from_elem("mix", adapter.get_mix());
            let out = hal.copy_from_elem("out", adapter.get_io());

            prover.finalize(&[&mix, &out], eval)
        };

        // Attach the full version of the output journal & construct receipt object
        let receipt = Receipt {
            journal: self.inner.commit.clone(),
            seal,
        };

        if !skip_seal {
            // Verify receipt to make sure it works
            receipt.verify(&self.image_id)?;
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

impl<'a> exec::HostHandler for ProverImpl<'a> {
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

    fn on_panic(&mut self, msg: &str) -> Result<()> {
        bail!("{}", msg)
    }
}

fn split_word8(value: u32) -> (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem) {
    (
        BabyBearElem::new(value & 0xff),
        BabyBearElem::new(value >> 8 & 0xff),
        BabyBearElem::new(value >> 16 & 0xff),
        BabyBearElem::new(value >> 24 & 0xff),
    )
}

fn split_word16(value: u32) -> (BabyBearElem, BabyBearElem) {
    (
        BabyBearElem::new(value & 0xffff),
        BabyBearElem::new(value >> 16),
    )
}

fn merge_word8((x0, x1, x2, x3): (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem)) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    let x2: u32 = x2.into();
    let x3: u32 = x3.into();
    x0 | x1 << 8 | x2 << 16 | x3 << 24
}

/// An event traced from the running VM.
#[non_exhaustive]
#[derive(PartialEq)]
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

impl Debug for TraceEvent {
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
