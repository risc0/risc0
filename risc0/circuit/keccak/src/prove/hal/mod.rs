// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub(crate) mod cpu;
#[cfg(feature = "cuda")]
pub(crate) mod cuda;

use anyhow::Result;
use risc0_circuit_keccak_sys::ScatterInfo;
use risc0_core::field::Elem as _;
use risc0_zkp::hal::Hal;

use super::preflight::{ForwardPreflightOrder, PreflightCycleOrder, PreflightTrace};
use crate::zirgen::circuit::{CircuitField, ExtVal, Val};

pub(crate) struct MetaBuffer<H: Hal> {
    pub buf: H::Buffer<H::Elem>,
    pub rows: usize,
    pub cols: usize,
    pub checked_reads: bool,
}

impl<H> MetaBuffer<H>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
{
    pub fn new(name: &'static str, hal: &H, rows: usize, cols: usize, checked_reads: bool) -> Self {
        let buf = hal.alloc_elem_init(name, rows * cols, H::Elem::INVALID);
        Self {
            buf,
            rows,
            cols,
            checked_reads,
        }
    }
}

#[derive(Clone, Copy, PartialEq)]
#[allow(dead_code)]
pub(crate) enum StepMode {
    Parallel,
    SeqForward,
    SeqReverse,
}

pub(crate) trait CircuitWitnessGenerator<H: Hal> {
    type PreferredPreflightOrder: PreflightCycleOrder;

    fn scatter_preflight(
        &self,
        into: &MetaBuffer<H>,
        infos: &[ScatterInfo],
        data: &[u32],
    ) -> Result<()>;

    fn generate_witness<Order: PreflightCycleOrder>(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace<Order>,
        global: &MetaBuffer<H>,
        data: &MetaBuffer<H>,
    ) -> Result<()>;
}
