// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub const GUEST_MIN_MEM: usize = 0x0000_4000;
pub const GUEST_MAX_MEM: usize = 0xC000_0000;

/// Top of stack; stack grows down from this location.
pub const STACK_TOP: u32 = 0x0020_0400;

/// Program (text followed by data and then bss) gets loaded in
/// starting at this location.  HEAP begins right afterwards.
pub const TEXT_START: u32 = 0x0020_0800;

/// Returns whether `addr` is within guest memory bounds.
pub fn is_guest_memory(addr: u32) -> bool {
    GUEST_MIN_MEM <= (addr as usize) && (addr as usize) < GUEST_MAX_MEM
}
