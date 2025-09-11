// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub(crate) mod bibc;
pub(crate) mod bigint;
mod executor;
pub mod gdb;
pub(crate) mod pager;
pub mod platform;
pub(crate) mod poseidon2;
pub(crate) mod r0vm;
pub(crate) mod rv32im;
pub(crate) mod segment;
pub(crate) mod sha2;
mod syscall;
#[cfg(test)]
mod tests;
pub mod testutil;

pub use self::{
    bigint::analyze::analyze as bigint_analyze,
    executor::{CycleLimit, Executor, ExecutorResult, SimpleSession},
    platform::*,
    segment::Segment,
    syscall::{Syscall, SyscallContext},
};

pub const DEFAULT_SEGMENT_LIMIT_PO2: usize = 20;

pub(crate) fn node_idx(page_idx: u32) -> u32 {
    MEMORY_PAGES as u32 + page_idx
}

#[inline]
#[cold]
fn cold() {}

#[inline]
#[allow(dead_code)]
fn likely(b: bool) -> bool {
    if !b {
        cold()
    }
    b
}

#[inline]
fn unlikely(b: bool) -> bool {
    if b {
        cold()
    }
    b
}
