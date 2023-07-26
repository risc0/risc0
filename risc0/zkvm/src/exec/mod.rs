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

//! The execution phase is implemented by this module.
//!
//! The result of the execution phase is a [Session]. Each [Session] contains
//! one or more [crate::Segment]s, each of which contains an execution trace of
//! the specified program.

mod env;
pub(crate) mod io;
mod local;
mod monitor;
#[cfg(feature = "profiler")]
pub(crate) mod profiler;
mod remote;
#[cfg(test)]
mod tests;

use std::fmt::Debug;

use anyhow::Result;
pub use local::{LocalExecutor, SyscallRecord};
use remote::RemoteExecutor;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};

pub use self::env::{ExecutorEnv, ExecutorEnvBuilder};
use crate::Session;

/// [Executor] trait
///
/// This trait abstracts over different kinds of executors that run the guest
/// code locally or remotely.
pub trait Executor {
    /// This will run the executor to get a [Session] which contain the results
    /// of the execution.
    fn run(&mut self) -> Result<Session>;
}

/// Construct a new [Executor] from the ELF binary of the guest program you
/// want to run and an [ExecutorEnv] containing relevant environmental
/// configuration details.
pub fn default_executor_from_elf<'a>(
    env: ExecutorEnv<'a>,
    elf: &[u8],
) -> Result<Box<dyn Executor + 'a>> {
    let program = Program::load_elf(&elf, MEM_SIZE as u32)?;
    let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
    if std::env::var("BONSAI_API_URL").is_ok() && std::env::var("BONSAI_API_KEY").is_ok() {
        Ok(Box::new(RemoteExecutor::new(env, image)))
    } else {
        Ok(Box::new(LocalExecutor::new(env, image, program.entry)))
    }
}

/// An event traced from the running VM.
#[derive(Clone, Eq, Ord, PartialEq, PartialOrd)]
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
