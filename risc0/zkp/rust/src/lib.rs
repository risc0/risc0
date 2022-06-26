#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

pub mod core;

#[cfg(feature = "hal")]
pub mod hal;
