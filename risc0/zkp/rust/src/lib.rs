#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

pub mod core;
#[cfg(feature = "hal")]
pub mod hal;
mod merkle;
#[cfg(feature = "prove")]
pub mod prove;
pub mod taps;
#[cfg(feature = "verify")]
pub mod verify;

const MAX_CYCLES_PO2: usize = 20;
pub const MAX_CYCLES: usize = 1 << MAX_CYCLES_PO2;

/// ~100 bits of conjectured security
pub const QUERIES: usize = 50;

pub const INV_RATE: usize = 4;
const FRI_FOLD_PO2: usize = 4;
const FRI_FOLD: usize = 1 << FRI_FOLD_PO2;
const FRI_MIN_DEGREE: usize = 256;

const CHECK_SIZE: usize = INV_RATE * core::fp4::EXT_SIZE;
