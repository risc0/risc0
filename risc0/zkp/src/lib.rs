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

extern crate alloc;
#[cfg(feature = "prove")]
extern crate ff;

pub mod adapter;
pub mod core;
#[cfg(feature = "prove")]
pub mod hal;
pub mod layout;
#[cfg(not(target_os = "zkvm"))]
mod merkle;
#[cfg(feature = "prove")]
pub mod prove;
pub mod taps;
#[cfg(not(target_os = "zkvm"))]
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

/// A protocol info string for the proof system. Used to seed the Fiat-Shamir transcript and
/// provide domain seperation between different protocol and circuit versions.
#[derive(Debug)]
pub struct ProtocolInfo(pub &'static [u8; 16]);

impl ProtocolInfo {
    /// Encode a fixed context byte-string to elements, with one element per byte.
    // NOTE: This function is intended to be compatible with const, but is not const currently because
    // E::from_u64 is not const, as const functions on traits is not stable.
    pub fn encode<E: field::Elem>(&self) -> [E; 16] {
        let mut elems = [E::ZERO; 16];
        for i in 0..self.0.len() {
            elems[i] = E::from_u64(self.0[i] as u64);
        }
        elems
    }
}

/// Versioned info string for the proof system.
///
/// NOTE: This string should be bumped with every change to the proof system, as defined by a
/// change to checks applied by the verifier.
pub const PROOF_SYSTEM_INFO: ProtocolInfo = ProtocolInfo(b"RISC0_STARK:v1__");

pub const MIN_CYCLES_PO2: usize = 13;
pub const MIN_CYCLES: usize = 1 << MIN_CYCLES_PO2; // 8K
pub const MAX_CYCLES_PO2: usize = 24;
pub const MAX_CYCLES: usize = 1 << MAX_CYCLES_PO2; // 16M

/// 50 FRI queries gives ~100 bits of conjectured security
pub const QUERIES: usize = 50;
pub const ZK_CYCLES: usize = QUERIES;
pub const MIN_PO2: usize = core::log2_ceil(1 + ZK_CYCLES);

/// Inverse of Reed-Solomon Expansion Rate
pub const INV_RATE: usize = 4;

const FRI_FOLD_PO2: usize = 4;

/// FRI folding factor is 2 ^ FRI_FOLD_PO2
pub const FRI_FOLD: usize = 1 << FRI_FOLD_PO2;

/// FRI continues until the degree of the FRI polynomial reaches FRI_MIN_DEGREE
#[cfg(not(target_os = "zkvm"))]
const FRI_MIN_DEGREE: usize = 256;
