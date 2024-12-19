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

pub(crate) mod paged_map;
pub(crate) mod poseidon2;
pub(crate) mod preflight;
#[cfg(test)]
mod tests;

use std::iter::zip;

use anyhow::{Context, Result};
use preflight::PreflightTrace;
use risc0_circuit_rv32im_v2_sys::RawPreflightCycle;
use risc0_core::scope;
use risc0_zkp::{core::digest::DIGEST_WORDS, field::Elem as _, hal::Hal};

use self::{poseidon2::Poseidon2State, preflight::Back};
use super::hal::{CircuitWitnessGenerator, MetaBuffer, StepMode};
use crate::{
    execute::{addr::WordAddr, platform::MERKLE_TREE_END_ADDR, segment::Segment},
    zirgen::circuit::{
        CircuitField, ExtVal, Val, LAYOUT_GLOBAL, LAYOUT_TOP, REGCOUNT_CODE, REGCOUNT_DATA,
        REGCOUNT_GLOBAL,
    },
};

pub(crate) struct WitnessGenerator<H: Hal> {
    pub cycles: usize,
    pub global: MetaBuffer<H>,
    pub code: MetaBuffer<H>,
    pub data: MetaBuffer<H>,
    pub trace: PreflightTrace,
}

impl<H: Hal> WitnessGenerator<H> {
    pub fn new<C>(
        hal: &H,
        circuit_hal: &C,
        segment: &Segment,
        mode: StepMode,
        rand_z: ExtVal,
    ) -> Result<Self>
    where
        H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
        C: CircuitWitnessGenerator<H>,
    {
        scope!("witgen");

        let trace = segment.preflight(rand_z)?;
        let cycles = trace.cycles.len();

        tracing::trace!("{segment:#?}");
        tracing::trace!("{trace:#?}");

        // assert_eq!(
        //     segment.suspend_cycle + segment.paging_cycles + LOOKUP_TABLE_CYCLES as u32 + 1,
        //     cycles as u32,
        //     "suspend_cycle: {} + paging_cycles: {} + {LOOKUP_TABLE_CYCLES} + 1 == trace.cycles",
        //     segment.suspend_cycle,
        //     segment.paging_cycles
        // );
        // assert_eq!(cycles, 1 << segment.po2, "cycles == 1 << segment.po2");
        assert!(cycles <= 1 << segment.po2, "cycles <= 1 << segment.po2");
        let cycles = 1 << segment.po2;

        let mut global = vec![Val::INVALID; REGCOUNT_GLOBAL];

        for i in 0..DIGEST_WORDS {
            // state in
            let low = segment.pre_digest.as_words()[i] & 0xffff;
            let high = segment.pre_digest.as_words()[i] >> 16;
            global[LAYOUT_GLOBAL.state_in.values[i].low._super.offset] = low.into();
            global[LAYOUT_GLOBAL.state_in.values[i].high._super.offset] = high.into();

            // input digest
            let low = 0u32;
            let high = 0u32;
            global[LAYOUT_GLOBAL.input.values[i].low._super.offset] = low.into();
            global[LAYOUT_GLOBAL.input.values[i].high._super.offset] = high.into();
        }

        // rand_z
        for (i, &elem) in trace.rand_z.elems().iter().enumerate() {
            global[LAYOUT_GLOBAL.rng._super.offset + i] = elem;
        }

        // is_terminate
        global[LAYOUT_GLOBAL.is_terminate._super.offset] = 1u32.into();

        let global = MetaBuffer {
            buf: hal.copy_from_elem("global", &global),
            rows: 1,
            cols: REGCOUNT_GLOBAL,
            checked_reads: true,
        };

        let code = MetaBuffer::new("code", hal, cycles, REGCOUNT_CODE, false);

        let data = scope!(
            "alloc(data)",
            MetaBuffer::new("data", hal, cycles, REGCOUNT_DATA, true)
        );

        // Set stateful columns from 'top'
        let mut injector = Injector::new(cycles);
        for (row, back) in trace.backs.iter().enumerate() {
            let cycle = &trace.cycles[row];
            // tracing::trace!(
            //     "[{row}] pc: {:#010x}, state: {:?}",
            //     cycle.pc,
            //     CycleState::from_u32(cycle.state).unwrap()
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
            }
            injector.set_cycle(row, cycle);
        }

        hal.scatter(
            &data.buf,
            &injector.index,
            &injector.offsets,
            &injector.values,
        );

        circuit_hal
            .generate_witness(mode, &trace, &global, &data)
            .context("witness generation failure")?;

        // Zero out 'invalid' entries in data and output.
        scope!("zeroize", {
            hal.eltwise_zeroize_elem(&global.buf);
            hal.eltwise_zeroize_elem(&code.buf);
            hal.eltwise_zeroize_elem(&data.buf);
        });

        Ok(Self {
            cycles,
            global,
            code,
            data,
            trace,
        })
    }
}

#[derive(Debug)]
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

    fn set_cycle(&mut self, row: usize, cycle: &RawPreflightCycle) {
        const NEXT_PC_LOW: usize = LAYOUT_TOP.next_pc_low._super.offset;
        const NEXT_PC_HIGH: usize = LAYOUT_TOP.next_pc_high._super.offset;
        const NEXT_STATE: usize = LAYOUT_TOP.next_state_0._super.offset;
        const MACHINE_MODE: usize = LAYOUT_TOP.next_machine_mode._super.offset;
        self.set(row, NEXT_PC_LOW, cycle.pc & 0xffff);
        self.set(row, NEXT_PC_HIGH, cycle.pc >> 16);
        self.set(row, NEXT_STATE, cycle.state);
        self.set(row, MACHINE_MODE, cycle.machine_mode as u32);
        self.index.push(self.offsets.len() as u32);
    }

    fn set(&mut self, row: usize, col: usize, value: u32) {
        let idx = col * self.rows + row;
        self.offsets.push(idx as u32);
        self.values.push(value.into());
    }
}

fn node_idx_to_addr(idx: u32) -> WordAddr {
    MERKLE_TREE_END_ADDR - idx * DIGEST_WORDS as u32
}

fn node_addr_to_idx(addr: WordAddr) -> u32 {
    (MERKLE_TREE_END_ADDR - addr).0 / DIGEST_WORDS as u32
}
