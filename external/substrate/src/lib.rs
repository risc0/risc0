// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![cfg_attr(not(feature = "std"), no_std)]

#[cfg(not(feature = "std"))]
#[panic_handler]
pub fn panic(_info: &core::panic::PanicInfo) -> ! {
    core::arch::wasm32::unreachable();
}
