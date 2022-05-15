#![no_std]

#[cfg(not(target_arch = "riscv32"))]
pub mod methods {
    include!(concat!(env!("OUT_DIR"), "/methods.rs"));
}
