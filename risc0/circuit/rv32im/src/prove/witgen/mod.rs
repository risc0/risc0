// Copyright 2025 RISC Zero, Inc.
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

pub(crate) mod bigint;
pub(crate) mod byte_poly;
pub(crate) mod paged_map;
pub(crate) mod poseidon2;
pub(crate) mod preflight;
pub(crate) mod sha2;
#[cfg(test)]
mod tests;

use std::iter::zip;

use anyhow::{Context, Result};
use preflight::PreflightTrace;
use risc0_binfmt::WordAddr;
use risc0_circuit_rv32im_sys::RawPreflightCycle;
use risc0_core::scope;
use risc0_zkp::{
    core::digest::DIGEST_WORDS,
    field::{Elem as _, ExtElem as _},
    hal::Hal,
};

use self::{
    bigint::BigIntState,
    byte_poly::{BigIntAccum, BigIntAccumState},
    preflight::Back,
};
use super::hal::{CircuitAccumulator, CircuitWitnessGenerator, MetaBuffer, StepMode};
use crate::{
    execute::{
        platform::MERKLE_TREE_END_ADDR, poseidon2::Poseidon2State, segment::Segment,
        sha2::Sha2State,
    },
    zirgen::circuit::{
        CircuitField, ExtVal, Val, LAYOUT_GLOBAL, LAYOUT_TOP, REGCOUNT_ACCUM, REGCOUNT_CODE,
        REGCOUNT_DATA, REGCOUNT_GLOBAL, REGCOUNT_MIX,
    },
};

#[derive(Clone, Default)]
pub struct PreflightResults {
    global: Vec<Val>,
    injector: Injector,
    cycles: usize,
    trace: PreflightTrace,
    po2: u32,
}

impl PreflightResults {
    pub fn new(segment: &Segment, rand_z: ExtVal) -> Result<Self> {
        scope!("preflight_result_new");

        let trace = segment.preflight(rand_z)?;

        tracing::trace!("{segment:#?}");
        tracing::trace!("{trace:#?}");

        let cycles = trace.cycles.len();
        assert!(cycles <= 1 << segment.po2, "cycles <= 1 << segment.po2");
        let cycles = 1 << segment.po2;

        let global = build_global_vec(segment, &trace);
        let injector = build_injector(&trace, cycles);

        Ok(Self {
            global,
            injector,
            cycles,
            trace,
            po2: segment.po2,
        })
    }

    pub fn po2(&self) -> u32 {
        self.po2
    }
}

pub(crate) struct WitnessGenerator<H: Hal> {
    cycles: usize,
    pub global: MetaBuffer<H>,
    pub code: MetaBuffer<H>,
    pub data: MetaBuffer<H>,
    pub accum: MetaBuffer<H>,
    pub trace: PreflightTrace,
}

impl<H> WitnessGenerator<H>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
{
    pub fn new<C: CircuitWitnessGenerator<H>>(
        hal: &H,
        circuit_hal: &C,
        preflight_results: PreflightResults,
        mode: StepMode,
    ) -> Result<Self> {
        scope!("witness_generator_new");

        let (global, code, data, accum) = Self::hal_generate_witness(
            hal,
            circuit_hal,
            mode,
            &preflight_results.trace,
            preflight_results.global,
            preflight_results.cycles,
            preflight_results.injector,
        )?;

        Ok(Self {
            cycles: preflight_results.cycles,
            global,
            code,
            data,
            accum,
            trace: preflight_results.trace,
        })
    }

    #[allow(clippy::type_complexity)]
    fn hal_generate_witness<C: CircuitWitnessGenerator<H>>(
        hal: &H,
        circuit_hal: &C,
        mode: StepMode,
        trace: &PreflightTrace,
        global: Vec<Val>,
        cycles: usize,
        injector: Injector,
    ) -> Result<(MetaBuffer<H>, MetaBuffer<H>, MetaBuffer<H>, MetaBuffer<H>), anyhow::Error> {
        scope!("hal_generate_witness");

        let global = MetaBuffer {
            buf: hal.copy_from_elem("global", &global),
            rows: 1,
            cols: REGCOUNT_GLOBAL,
            checked: true,
        };
        let code = MetaBuffer::new("code", hal, cycles, REGCOUNT_CODE, false);
        let data = scope!(
            "alloc(data)",
            MetaBuffer::new("data", hal, cycles, REGCOUNT_DATA, true)
        );
        hal.scatter(
            &data.buf,
            &injector.index,
            &injector.offsets,
            &injector.values,
        );
        circuit_hal
            .generate_witness(mode, trace, &global, &data)
            .context("witness generation failure")?;
        scope!("zeroize", {
            hal.eltwise_zeroize_elem(&global.buf);
            hal.eltwise_zeroize_elem(&code.buf);
            hal.eltwise_zeroize_elem(&data.buf);
        });
        let accum = scope!(
            "alloc(accum)",
            MetaBuffer::new("accum", hal, cycles, REGCOUNT_ACCUM, true)
        );
        Ok((global, code, data, accum))
    }

    pub fn accum<C: CircuitAccumulator<H>>(
        &self,
        hal: &H,
        circuit_hal: &C,
        mix: &[Val],
    ) -> Result<MetaBuffer<H>> {
        // use final mix to compute BigIntAccumPowers
        let last_mix = ExtVal::from_subelems(mix[mix.len() - 4..].iter().cloned());

        // inject BigIntAccumState backs
        let mut injector = Injector::new(self.cycles);
        let mut bigint_accum = BigIntAccum::new(last_mix);

        for (row, back) in self.trace.backs.iter().enumerate() {
            if let Back::BigInt(state) = back {
                bigint_accum.step(state)?;
                for (col, value) in zip(BigIntAccumState::offsets(), bigint_accum.state.as_array())
                {
                    injector.set(row, col, value);
                }
                injector.push();
            }
        }

        hal.scatter(
            &self.accum.buf,
            &injector.index,
            &injector.offsets,
            &injector.values,
        );

        let mix = MetaBuffer {
            buf: hal.copy_from_elem("mix", mix),
            rows: 1,
            cols: REGCOUNT_MIX,
            checked: true,
        };

        circuit_hal.step_accum(&self.trace, &self.data, &self.accum, &self.global, &mix)?;

        scope!("zeroize(accum)", {
            hal.eltwise_zeroize_elem(&self.accum.buf);
        });

        Ok(mix)
    }
}

fn build_injector(trace: &PreflightTrace, cycles: usize) -> Injector {
    scope!("build_injector");

    // Set stateful columns from 'top'
    let mut injector = Injector::new(cycles);
    for (row, back) in trace.backs.iter().enumerate() {
        let cycle = &trace.cycles[row];
        // tracing::trace!(
        //     "[{row}] pc: {:#010x}, state: {:?}",
        //     cycle.pc,
        //     crate::execute::CycleState::from_u32(cycle.state).unwrap()
        // );
        match back {
            Back::None => {}
            Back::Ecall(s0, s1, s2) => {
                const ECALL_S0: usize = LAYOUT_TOP.inst_result.arm8.s0._super.offset;
                const ECALL_S1: usize = LAYOUT_TOP.inst_result.arm8.s1._super.offset;
                const ECALL_S2: usize = LAYOUT_TOP.inst_result.arm8.s2._super.offset;
                injector.set(row, ECALL_S0, *s0);
                injector.set(row, ECALL_S1, *s1);
                injector.set(row, ECALL_S2, *s2);
            }
            Back::Poseidon2(p2_state) => {
                for (col, value) in zip(Poseidon2State::offsets(), p2_state.as_array()) {
                    injector.set(row, col, value);
                }
            }
            Back::Sha2(sha2_state) => {
                for (col, value) in zip(Sha2State::fp_offsets(), sha2_state.fp_array()) {
                    injector.set(row, col, value);
                }
                for (col, value) in zip(Sha2State::u32_offsets(), sha2_state.u32_array()) {
                    injector.set_u32_bits(row, col, value);
                }
            }
            Back::BigInt(state) => {
                for (col, value) in zip(BigIntState::offsets(), state.as_array()) {
                    injector.set(row, col, value);
                }
            }
        }
        injector.set_cycle(row, cycle);
    }
    injector
}

fn build_global_vec(segment: &Segment, trace: &PreflightTrace) -> Vec<Val> {
    scope!("build_global_vec");

    let mut global = vec![Val::INVALID; REGCOUNT_GLOBAL];

    // state in
    for (i, word) in segment.claim.pre_state.as_words().iter().enumerate() {
        let low = word & 0xffff;
        let high = word >> 16;
        global[LAYOUT_GLOBAL.state_in.values[i].low._super.offset] = low.into();
        global[LAYOUT_GLOBAL.state_in.values[i].high._super.offset] = high.into();
    }

    // input digest
    for (i, word) in segment.claim.input.as_words().iter().enumerate() {
        let low = word & 0xffff;
        let high = word >> 16;
        global[LAYOUT_GLOBAL.input.values[i].low._super.offset] = low.into();
        global[LAYOUT_GLOBAL.input.values[i].high._super.offset] = high.into();
    }

    // rand_z
    for (i, &elem) in trace.rand_z.elems().iter().enumerate() {
        global[LAYOUT_GLOBAL.rng._super.offset + i] = elem;
    }

    // is_terminate
    let is_terminate = if segment.claim.terminate_state.is_some() {
        1u32
    } else {
        0u32
    };
    global[LAYOUT_GLOBAL.is_terminate._super.offset] = is_terminate.into();

    // shutdown_cycle
    global[LAYOUT_GLOBAL.shutdown_cycle._super.offset] = segment.segment_threshold.into();

    // povw nonce
    // TODO: Fill in with real values
    for i in 0..DIGEST_WORDS {
        global[LAYOUT_GLOBAL.povw_nonce.values[i].low._super.offset] = Val::ZERO;
        global[LAYOUT_GLOBAL.povw_nonce.values[i].high._super.offset] = Val::ZERO;
    }

    global
}

#[derive(Clone, Debug, Default)]
struct Injector {
    rows: usize,
    offsets: Vec<u32>,
    values: Vec<Val>,
    index: Vec<u32>,
}

impl Injector {
    fn new(rows: usize) -> Self {
        let mut index = Vec::with_capacity(rows + 1);
        index.push(0);
        Self {
            rows,
            offsets: vec![],
            values: vec![],
            index,
        }
    }

    fn push(&mut self) {
        self.index.push(self.offsets.len() as u32);
    }

    fn set_cycle(&mut self, row: usize, cycle: &RawPreflightCycle) {
        const CYCLE_COL: usize = LAYOUT_TOP.cycle._super.offset;
        const NEXT_PC_LOW: usize = LAYOUT_TOP.next_pc_low._super.offset;
        const NEXT_PC_HIGH: usize = LAYOUT_TOP.next_pc_high._super.offset;
        const NEXT_STATE: usize = LAYOUT_TOP.next_state_0._super.offset;
        const NEXT_MACHINE_MODE: usize = LAYOUT_TOP.next_machine_mode._super.offset;
        self.set(row, CYCLE_COL, row as u32);
        self.set(row, NEXT_PC_LOW, cycle.pc & 0xffff);
        self.set(row, NEXT_PC_HIGH, cycle.pc >> 16);
        self.set(row, NEXT_STATE, cycle.state);
        self.set(row, NEXT_MACHINE_MODE, cycle.machine_mode as u32);
        self.push();
    }

    fn set(&mut self, row: usize, col: usize, value: u32) {
        let idx = col * self.rows + row;
        self.offsets.push(idx as u32);
        self.values.push(value.into());
    }

    fn set_u32_bits(&mut self, row: usize, col: usize, value: u32) {
        for i in 0..32 {
            self.set(row, col + i, (value >> i) & 1);
        }
    }
}

fn node_addr_to_idx(addr: WordAddr) -> u32 {
    (MERKLE_TREE_END_ADDR - addr).0 / DIGEST_WORDS as u32
}

fn node_idx_to_addr(idx: u32) -> WordAddr {
    MERKLE_TREE_END_ADDR - idx * DIGEST_WORDS as u32
}
