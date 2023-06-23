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

#[cfg(feature = "binfmt")]
pub mod binfmt;
mod control_id;
#[cfg(feature = "prove")]
mod exec;
pub mod guest;
#[cfg(feature = "prove")]
mod opcode;
#[cfg(feature = "prove")]
pub mod prove;
pub mod receipt;
pub mod recursion;
pub mod serde;
#[cfg(feature = "prove")]
mod session;
pub mod sha;

#[cfg(test)]
mod testutils;

pub use anyhow::Result;
use risc0_zkp::core::hash::{
    blake2b::{Blake2b, Blake2bHashFn},
    poseidon::PoseidonHashFn,
    sha::{Sha256, Sha256HashFn},
};
pub use risc0_zkvm_platform::{declare_syscall, memory::MEM_SIZE, PAGE_SIZE};

#[cfg(feature = "binfmt")]
pub use self::binfmt::{elf::Program, image::MemoryImage};
#[cfg(feature = "profiler")]
pub use self::exec::profiler::Profiler;
pub use self::receipt::{ExitCode, SegmentReceipt, SessionFlatReceipt, SessionReceipt};
#[cfg(feature = "prove")]
pub use self::{
    exec::io::{Syscall, SyscallContext},
    exec::{Executor, ExecutorEnv, ExecutorEnvBuilder},
    prove::loader::Loader,
    session::{FileSegmentRef, Segment, SegmentRef, Session, SimpleSegmentRef},
};
use crate::control_id::{RawControlId, BLAKE2B_CONTROL_ID, POSEIDON_CONTROL_ID, SHA256_CONTROL_ID};
#[cfg(not(target_os = "zkvm"))]
pub use crate::receipt::verify;
pub use crate::receipt::{ReceiptMetadata, SystemState};
const CIRCUIT: risc0_circuit_rv32im::CircuitImpl = risc0_circuit_rv32im::CircuitImpl::new();

/// Associate a specific CONTROL_ID with a HashFn.
pub trait ControlId {
    /// The associated CONTROL_ID for a HashFn.
    const CONTROL_ID: RawControlId;
}

impl<S: Sha256> ControlId for Sha256HashFn<S> {
    const CONTROL_ID: RawControlId = SHA256_CONTROL_ID;
}

impl ControlId for PoseidonHashFn {
    const CONTROL_ID: RawControlId = POSEIDON_CONTROL_ID;
}

impl<T: Blake2b> ControlId for Blake2bHashFn<T> {
    const CONTROL_ID: RawControlId = BLAKE2B_CONTROL_ID;
}

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
pub const fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}
