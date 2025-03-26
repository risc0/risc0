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

use risc0_circuit_rv32im_sys::ffi::{RawMemoryTransaction, RawPreflightCycle, RawPreflightTrace};
use risc0_core::scope;
use risc0_zkp::{field::baby_bear::BabyBearElem, layout::Reg};

use crate::{
    layout::DATA_LAYOUT,
    prove::emu::{
        addr::{ByteAddr, WordAddr},
        mux::{Major, TopMux},
        preflight::{Back, PreflightCycle, PreflightStage, PreflightTrace},
    },
};

pub struct MachineContext<'a> {
    trace: &'a PreflightTrace,
    pub raw_trace: Box<RawPreflightTrace>,
    _raw_cycles: Vec<RawPreflightCycle>,
    _raw_txns: Vec<RawMemoryTransaction>,
    _raw_extras: Vec<u32>,
}

struct Injector<'a> {
    steps: usize,
    cycle: usize,
    offsets: &'a mut Vec<u32>,
    values: &'a mut Vec<BabyBearElem>,
}

impl<'a> Injector<'a> {
    fn new(
        steps: usize,
        cycle: usize,
        offsets: &'a mut Vec<u32>,
        values: &'a mut Vec<BabyBearElem>,
    ) -> Self {
        Self {
            steps,
            cycle,
            offsets,
            values,
        }
    }

    fn get_idx(&self, reg: &Reg) -> usize {
        reg.offset * self.steps + self.cycle - 1
    }

    fn add(&mut self, reg: &Reg, value: u32) {
        self.offsets.push(self.get_idx(reg) as u32);
        self.values.push(value.into());
    }

    fn set_pc(&mut self, pc: ByteAddr) {
        let pc = pc + 4u32;
        let bytes = pc.0.to_le_bytes();
        let bot2 = bytes[3] & 0b11;
        let top2 = (bytes[3] >> 2) & 0b11;
        let pc = DATA_LAYOUT.mux.body.pc;
        self.add(pc.bytes[0], bytes[0] as u32);
        self.add(pc.bytes[1], bytes[1] as u32);
        self.add(pc.bytes[2], bytes[2] as u32);
        self.add(pc.twits[0], bot2 as u32);
        self.add(pc.twits[1], top2 as u32);
    }

    fn set_user_mode(&mut self) {
        let user_mode = DATA_LAYOUT.mux.body.user_mode;
        self.add(user_mode, 0);
    }

    fn set_next_major(&mut self, major: Major) {
        let next_major = DATA_LAYOUT.mux.body.next_major;
        self.add(next_major, major.as_u32());
    }

    fn set_halt(&mut self, sys_exit_code: u8, user_exit_code: u8, write_addr: WordAddr) {
        let major_select = DATA_LAYOUT.mux.body.major_select;
        let halt_cycle = DATA_LAYOUT.mux.body.major_mux;
        self.add(major_select[Major::ECall as usize], 0);
        self.add(major_select[Major::PageFault as usize], 0);
        self.add(major_select[Major::Halt as usize], 1);
        self.add(halt_cycle.sys_exit_code, sys_exit_code as u32);
        self.add(halt_cycle.user_exit_code, user_exit_code as u32);
        self.add(halt_cycle.write_addr, write_addr.0);
    }
}

impl TopMux {
    fn is_safe_verify_mem(&self) -> u8 {
        match self {
            TopMux::Body(Major::BigInt2, _) => 0,
            TopMux::Body(Major::VerifyAnd, _) => 0,
            TopMux::Body(Major::VerifyDivide, _) => 0,
            TopMux::Body(Major::PageFault, _) => 0,
            TopMux::Body(Major::Halt, _) => 2,
            TopMux::Body(_, _) => 1,
            _ => 0,
        }
    }
}

impl<'a> MachineContext<'a> {
    pub fn new(trace: &'a PreflightTrace) -> Self {
        scope!("prepare_trace");
        let _raw_cycles: Vec<_> = trace
            .pre
            .cycles
            .iter()
            .map(|x| {
                let (major, minor) = x.mux.as_body().unwrap_or((Major::Compute0, 0));
                RawPreflightCycle {
                    major: major.as_u32() as u8,
                    minor: minor as u8,
                    is_safe_exec: if x.back.is_some() { 1 } else { 0 },
                    is_safe_verify_mem: x.mux.is_safe_verify_mem(),
                    mem_idx: x.mem_idx as u32,
                    extra_idx: x.extra_idx as u32,
                }
            })
            .chain(trace.body.cycles.iter().map(|x| {
                let (major, minor) = x.mux.as_body().unwrap_or((Major::Compute0, 0));
                RawPreflightCycle {
                    major: major.as_u32() as u8,
                    minor: minor as u8,
                    is_safe_exec: if x.back.is_some() { 1 } else { 0 },
                    is_safe_verify_mem: x.mux.is_safe_verify_mem(),
                    mem_idx: (x.mem_idx + trace.pre.txns.len()) as u32,
                    extra_idx: (x.extra_idx + trace.pre.extras.len()) as u32,
                }
            }))
            .collect();

        let _raw_txns: Vec<_> = trace
            .pre
            .txns
            .iter()
            .map(|x| RawMemoryTransaction {
                cycle: x.cycle as u32,
                addr: x.addr.0,
                data: x.data,
            })
            .chain(trace.body.txns.iter().map(|x| RawMemoryTransaction {
                cycle: (x.cycle + trace.pre.cycles.len()) as u32,
                addr: x.addr.0,
                data: x.data,
            }))
            .collect();

        let _raw_extras: Vec<_> = trace
            .pre
            .extras
            .iter()
            .chain(trace.body.extras.iter())
            .copied()
            .collect();

        let is_trace = match tracing::level_filters::LevelFilter::current()
            .eq(&tracing::level_filters::LevelFilter::TRACE)
        {
            true => 1,
            false => 0,
        };

        let raw_trace = Box::new(RawPreflightTrace {
            cycles: _raw_cycles.as_ptr(),
            txns: _raw_txns.as_ptr(),
            extras: _raw_extras.as_ptr(),
            num_cycles: _raw_cycles.len() as u32,
            num_txns: _raw_txns.len() as u32,
            num_extras: _raw_extras.len() as u32,
            is_trace,
        });

        Self {
            trace,
            raw_trace,
            _raw_cycles,
            _raw_txns,
            _raw_extras,
        }
    }

    pub fn is_exec_par_safe(&self, cycle: usize) -> bool {
        self.get_cycle(cycle).back.is_some()
    }

    pub fn inject_exec_backs<'b>(
        &self,
        steps: usize,
        cycle: usize,
        offsets: &'b mut Vec<u32>,
        values: &'b mut Vec<BabyBearElem>,
    ) {
        let cur_cycle = self.get_cycle(cycle);
        if let Some(back) = &cur_cycle.back {
            let mut injector = Injector::new(steps, cycle, offsets, values);
            match back {
                Back::Null => (),
                Back::Body { pc } => {
                    injector.set_pc(*pc);
                    injector.set_user_mode();
                    injector.set_next_major(Major::MuxSize);
                }
                Back::Halt {
                    pc,
                    sys_exit_code,
                    user_exit_code,
                    write_addr,
                } => {
                    injector.set_pc(*pc);
                    injector.set_user_mode();
                    injector.set_halt(*sys_exit_code, *user_exit_code, *write_addr);
                    injector.set_next_major(Major::Halt);
                }
            }
        }
    }

    fn get_stage_offset(&self, cycle: usize) -> (&PreflightStage, usize) {
        if cycle < self.trace.pre.cycles.len() {
            (&self.trace.pre, 0)
        } else {
            (&self.trace.body, self.trace.pre.cycles.len())
        }
    }

    fn get_cycle(&self, cycle: usize) -> &PreflightCycle {
        let (stage, offset) = self.get_stage_offset(cycle);
        &stage.cycles[cycle - offset]
    }
}
