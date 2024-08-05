// Copyright 2024 RISC Zero, Inc.
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
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

extern crate alloc;

pub mod adapter;
pub mod core;
#[cfg(feature = "prove")]
pub mod hal;
pub mod layout;
mod merkle;
#[cfg(feature = "prove")]
pub mod prove;
pub mod taps;
pub mod verify;

#[cfg(not(feature = "prove"))]
pub mod hal {
    pub mod cpu {
        use core::marker::PhantomData;
        // TODO: Don't depend on SyncSlice in non-proving code.
        pub struct SyncSlice<T>(PhantomData<T>);
    }
}

pub use risc0_core::field;

pub const MIN_CYCLES_PO2: usize = 13;
pub const MIN_CYCLES: usize = 1 << MIN_CYCLES_PO2; // 8K
pub const MAX_CYCLES_PO2: usize = 24;
pub const MAX_CYCLES: usize = 1 << MAX_CYCLES_PO2; // 16M

/// 50 FRI queries is sufficient to achieve our security target of 99 bits (conjectured security)
pub const QUERIES: usize = 50;
pub const ZK_CYCLES: usize = 1994; // TODO: Ideally we'd compute ZK_CYCLES programmatically
pub const MIN_PO2: usize = core::log2_ceil(1 + ZK_CYCLES);

/// Inverse of Reed-Solomon Expansion Rate
pub const INV_RATE: usize = 4;

const FRI_FOLD_PO2: usize = 4;

/// FRI folding factor is 2 ^ FRI_FOLD_PO2
pub const FRI_FOLD: usize = 1 << FRI_FOLD_PO2;

/// FRI continues until the degree of the FRI polynomial reaches FRI_MIN_DEGREE
const FRI_MIN_DEGREE: usize = 256;
