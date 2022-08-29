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

#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

#[cfg(any(feature = "prove", feature = "verify"))]
pub mod adapter;
pub mod core;
#[cfg(feature = "hal")]
pub mod hal;
#[cfg(any(feature = "prove", feature = "verify"))]
mod merkle;
#[cfg(feature = "prove")]
pub mod prove;
pub mod taps;
#[cfg(feature = "verify")]
pub mod verify;

pub mod field;

pub const MIN_CYCLES: usize = 512;
pub const MAX_CYCLES_PO2: usize = 24;
pub const MAX_CYCLES: usize = 1 << MAX_CYCLES_PO2;

/// ~100 bits of conjectured security
pub const QUERIES: usize = 50;
pub const ZK_CYCLES: usize = QUERIES;
pub const MIN_PO2: usize = core::log2_ceil(1 + ZK_CYCLES);

pub const INV_RATE: usize = 4;
#[cfg(any(feature = "prove", feature = "verify"))]
const FRI_FOLD_PO2: usize = 4;
#[cfg(any(feature = "prove", feature = "verify"))]
const FRI_FOLD: usize = 1 << FRI_FOLD_PO2;
#[cfg(any(feature = "prove", feature = "verify"))]
const FRI_MIN_DEGREE: usize = 256;
#[cfg(any(feature = "prove", feature = "verify"))]
const CHECK_SIZE: usize = INV_RATE * core::fp4::EXT_SIZE;
