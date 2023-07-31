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

#![doc = include_str!("../README.md")]
#![cfg_attr(not(feature = "std"), no_std)]
#![deny(rustdoc::broken_intra_doc_links)]
#![deny(missing_docs)]

extern crate alloc;
#[cfg(not(target_os = "zkvm"))]
mod control_id;
#[cfg(feature = "prove")]
mod exec;
pub mod guest;
#[cfg(feature = "prove")]
mod opcode;
#[cfg(feature = "prove")]
pub mod prove;
#[cfg(not(target_os = "zkvm"))]
pub mod receipt;
#[cfg(not(target_os = "zkvm"))]
pub mod recursion;
pub mod serde;
#[cfg(feature = "prove")]
mod session;
pub mod sha;

#[cfg(test)]
mod testutils;

pub use anyhow::Result;
#[cfg(not(target_os = "zkvm"))]
pub use risc0_binfmt::{MemoryImage, Program, SystemState};
pub use risc0_zkvm_platform::{declare_syscall, memory::MEM_SIZE, PAGE_SIZE};

#[cfg(not(target_os = "zkvm"))]
pub use self::control_id::POSEIDON_CONTROL_ID;
#[cfg(feature = "profiler")]
pub use self::exec::profiler::Profiler;
#[cfg(not(target_os = "zkvm"))]
pub use self::receipt::{ExitCode, Receipt, ReceiptMetadata, SegmentReceipt, VerifierContext};
#[cfg(feature = "prove")]
pub use self::{
    exec::io::{Syscall, SyscallContext},
    exec::{Executor, ExecutorEnv, ExecutorEnvBuilder},
    prove::{default_prover, loader::Loader},
    session::{FileSegmentRef, Segment, SegmentRef, Session, SessionEvents, SimpleSegmentRef},
};

#[cfg(not(target_os = "zkvm"))]
const CIRCUIT: risc0_circuit_rv32im::CircuitImpl = risc0_circuit_rv32im::CircuitImpl::new();

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
pub const fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}
