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

use std::sync::atomic::{AtomicUsize, Ordering};

use anyhow::Result;
use rayon::prelude::*;
use risc0_circuit_rv32im_sys::ffi::{RawMemoryTransaction, RawPreflightCycle, RawPreflightTrace};
use risc0_zkp::{field::baby_bear::BabyBearElem, hal::cpu::SyncSlice};

use crate::{
    prove::{
        emu::{
            addr::{ByteAddr, WordAddr},
            mux::{Major, TopMux},
            preflight::{Back, PreflightCycle, PreflightStage, PreflightTrace},
        },
        hal::cpp::SyncMachineContext,
    },
    CIRCUIT,
};

struct Injector<'a> {
    steps: usize,
    cycle: usize,
    data: &'a SyncSlice<'a, BabyBearElem>,
}

pub struct MachineContext {
    trace: PreflightTrace,
    raw_machine_ctx: SyncMachineContext,
    _raw_trace: Box<RawPreflightTrace>,
    _raw_cycles: Vec<RawPreflightCycle>,
    _raw_txns: Vec<RawMemoryTransaction>,
    _raw_extras: Vec<u32>,
}

impl<'a> Injector<'a> {
    fn new(steps: usize, cycle: usize, data: &'a SyncSlice<'a, BabyBearElem>) -> Self {
        Self { steps, cycle, data }
    }

    fn get_idx(&self, reg: usize) -> usize {
        reg * self.steps + self.cycle - 1
    }

    fn set_pc(&self, pc: ByteAddr) {
        let pc = pc + 4u32;
        let bytes = pc.0.to_le_bytes();
        let bot2 = bytes[3] & 0b11;
        let top2 = bytes[3] >> 2 & 0b11;
        self.data.set(self.get_idx(6), (bytes[0] as u32).into()); // body->pc.bytes[0]
        self.data.set(self.get_idx(7), (bytes[1] as u32).into()); // body->pc.bytes[1]
        self.data.set(self.get_idx(8), (bytes[2] as u32).into()); // body->pc.bytes[2]
        self.data.set(self.get_idx(70), (bot2 as u32).into()); // body->pc.twits[0]
        self.data.set(self.get_idx(71), (top2 as u32).into()); // body->pc.twits[1]
    }

    fn set_next_major(&self, major: Major) {
        self.data.set(self.get_idx(99), major.as_u32().into()); // body->nextMajor
    }

    fn set_halt(&self, sys_exit_code: u8, user_exit_code: u8, write_addr: WordAddr) {
        self.data.set(self.get_idx(108), 0u32.into()); // body->majorSelect->at(MajorType::kECall): 8
        self.data.set(self.get_idx(112), 0u32.into()); // body->majorSelect->at(MajorType::kPageFault): 12
        self.data.set(self.get_idx(115), 1u32.into()); // body->majorSelect->at(MajorType::kHalt): 15
        self.data
            .set(self.get_idx(116), (sys_exit_code as u32).into()); // HaltCycle::sysExitCode
        self.data
            .set(self.get_idx(117), (user_exit_code as u32).into()); // HaltCycle::userExitCode
        self.data.set(self.get_idx(118), write_addr.0.into()); // HaltCycle::writeAddr
    }
}

impl MachineContext {
    pub fn new(steps: usize, trace: PreflightTrace) -> Self {
        nvtx::range_push!("prepare_trace");
        let _raw_cycles: Vec<_> = trace
            .pre
            .cycles
            .iter()
            .map(|x| {
                let (major, minor) = x.mux.as_body().unwrap_or((Major::Compute0, 0));
                RawPreflightCycle {
                    major: major.as_u32(),
                    minor,
                    mem_idx: x.mem_idx.load(Ordering::Relaxed),
                    extra_idx: x.extra_idx.load(Ordering::Relaxed),
                }
            })
            .chain(trace.body.cycles.iter().map(|x| {
                let (major, minor) = x.mux.as_body().unwrap_or((Major::Compute0, 0));
                RawPreflightCycle {
                    major: major.as_u32(),
                    minor,
                    mem_idx: x.mem_idx.load(Ordering::Relaxed) + trace.pre.txns.len(),
                    extra_idx: x.extra_idx.load(Ordering::Relaxed) + trace.pre.extras.len(),
                }
            }))
            .collect();
        let _raw_txns: Vec<_> = trace
            .pre
            .txns
            .iter()
            .map(|x| RawMemoryTransaction {
                cycle: x.cycle,
                addr: x.addr.0,
                data: x.data,
            })
            .chain(trace.body.txns.iter().map(|x| RawMemoryTransaction {
                cycle: x.cycle + trace.pre.cycles.len(),
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

        let _raw_trace = Box::new(RawPreflightTrace {
            cycles: _raw_cycles.as_ptr(),
            txns: _raw_txns.as_ptr(),
            extras: _raw_extras.as_ptr(),
            is_trace,
        });
        let raw_machine_ctx = CIRCUIT.alloc_machine_ctx(_raw_trace.as_ref(), steps);
        nvtx::range_pop!();

        Self {
            trace,
            raw_machine_ctx,
            _raw_trace,
            _raw_cycles,
            _raw_txns,
            _raw_extras,
        }
    }

    pub fn is_exec_par_safe(&self, cycle: usize) -> bool {
        let cur_cycle = self.get_cycle(cycle);
        // let is_safe = cur_cycle.back.is_some();
        // tracing::debug!("is_exec_par_safe: {cycle} <= {is_safe}");
        cur_cycle.back.is_some()
    }

    pub fn inject_exec_backs(&self, steps: usize, cycle: usize, data: &SyncSlice<BabyBearElem>) {
        let cur_cycle = self.get_cycle(cycle);
        if let Some(back) = &cur_cycle.back {
            let injector = Injector::new(steps, cycle, data);
            match back {
                Back::Null => (),
                Back::Body { pc } => {
                    injector.set_pc(*pc);
                    injector.set_next_major(Major::MuxSize);
                }
                Back::Halt {
                    pc,
                    sys_exit_code,
                    user_exit_code,
                    write_addr,
                } => {
                    injector.set_pc(*pc);
                    injector.set_halt(*sys_exit_code, *user_exit_code, *write_addr);
                    injector.set_next_major(Major::Halt);
                }
            }
        }
    }

    #[tracing::instrument(skip_all)]
    pub fn sort(&mut self, name: &str) {
        nvtx::range_push!("sort({name})");
        match name {
            "ram" => CIRCUIT.sort_ram(&self.raw_machine_ctx).unwrap(),
            "bytes" => CIRCUIT.sort_bytes(&self.raw_machine_ctx).unwrap(),
            _ => unimplemented!("Unknown argument type {name}"),
        };
        nvtx::range_pop!();
    }

    pub fn step_exec(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        // let cur_cycle = self.get_cycle(cycle);
        // tracing::debug!("[{cycle}] {:?}", cur_cycle);
        CIRCUIT.par_step_exec(steps, cycle, &self.raw_machine_ctx, args)
    }

    fn next_step_exec(
        &self,
        steps: usize,
        last_cycle: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
        counts: Option<&[AtomicUsize]>,
    ) {
        if cycle == 0 || self.is_exec_par_safe(cycle) {
            // tracing::debug!("step_exec: {cycle}");
            self.step_exec(steps, cycle, args).unwrap();

            let mut seq_cycle = cycle + 1;
            while seq_cycle < last_cycle && !self.is_exec_par_safe(seq_cycle) {
                self.step_exec(steps, seq_cycle, args).unwrap();
                seq_cycle += 1;
            }

            if let Some(counts) = counts {
                let cycles = seq_cycle - cycle;
                counts[cycles].fetch_add(1, Ordering::SeqCst);
            }
        }
    }

    pub fn rev_step_exec(&self, steps: usize, last_cycle: usize, args: &[SyncSlice<BabyBearElem>]) {
        (0..last_cycle).rev().for_each(|cycle| {
            self.next_step_exec(steps, last_cycle, cycle, args, None);
        });
    }

    pub fn par_step_exec(&self, steps: usize, last_cycle: usize, args: &[SyncSlice<BabyBearElem>]) {
        let counts: Vec<_> = (0..last_cycle).map(|_| AtomicUsize::new(0)).collect();

        (0..last_cycle).into_par_iter().for_each(|cycle| {
            self.next_step_exec(steps, last_cycle, cycle, args, Some(&counts));
        });

        for (cycles, count) in counts.iter().enumerate() {
            let count = count.load(Ordering::Relaxed);
            if count > 0 {
                tracing::debug!("cycles: {cycles} -> {count}");
            }
        }
    }

    pub fn step_verify_mem(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        // let cur_cycle = self.get_cycle(cycle);
        // tracing::debug!("[{cycle}] {cur_cycle:?}");
        CIRCUIT.par_step_verify_mem(steps, cycle, &self.raw_machine_ctx, args)
    }

    fn is_verify_mem_par_safe(&self, cycle: usize) -> bool {
        let cur_cycle = self.get_cycle(cycle);
        match cur_cycle.mux {
            TopMux::Body(Major::VerifyAnd, _) => false,
            TopMux::Body(Major::VerifyDivide, _) => false,
            TopMux::Body(Major::PageFault, _) => false,
            TopMux::Body(Major::Halt, _) => false,
            TopMux::Body(_, _) => true,
            _ => false,
        }
    }

    pub fn inject_verify_mem_backs(
        &self,
        steps: usize,
        cycle: usize,
        data: SyncSlice<BabyBearElem>,
    ) {
        if self.is_verify_mem_par_safe(cycle) {
            CIRCUIT
                .inject_ram_backs(&self.raw_machine_ctx, steps, cycle, data)
                .unwrap();
        }
    }

    pub fn par_step_verify_mem(
        &self,
        steps: usize,
        last_cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) {
        let counts: Vec<_> = (0..last_cycle).map(|_| AtomicUsize::new(0)).collect();

        (0..last_cycle).into_par_iter().for_each(|cycle| {
            if cycle == 0 || self.is_verify_mem_par_safe(cycle) {
                // tracing::trace!("step_verify_mem({cycle})");
                self.step_verify_mem(steps, cycle, args).unwrap();

                let mut seq_cycle = cycle + 1;
                while seq_cycle < last_cycle && !self.is_verify_mem_par_safe(seq_cycle) {
                    self.step_verify_mem(steps, seq_cycle, args).unwrap();
                    seq_cycle += 1;
                }

                let cycles = seq_cycle - cycle;
                counts.get(cycles).unwrap().fetch_add(1, Ordering::SeqCst);
            }
        });

        for (cycles, count) in counts.iter().enumerate() {
            let count = count.load(Ordering::Relaxed);
            if count > 0 {
                tracing::debug!("cycles: {cycles} -> {count}");
            }
        }
    }

    pub fn step_verify_bytes(
        &self,
        steps: usize,
        cycle: usize,
        args: &[SyncSlice<BabyBearElem>],
    ) -> Result<BabyBearElem> {
        CIRCUIT.par_step_verify_bytes(steps, cycle, &self.raw_machine_ctx, args)
    }
}

impl MachineContext {
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
