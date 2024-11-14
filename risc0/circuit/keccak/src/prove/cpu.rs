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

use super::{keccak_circuit, CircuitImpl};
use anyhow::{anyhow, Result};
use core::cell::RefCell;
use keccak_circuit::{CircuitField, ExtVal, Val, REGISTER_GROUP_ACCUM, REGISTER_GROUP_DATA};
use rayon::iter::IntoParallelIterator;
use rayon::prelude::*;
use risc0_zirgen_dsl::{CycleContext, CycleRow, GlobalRow};
use risc0_zkp::{
    adapter::PolyFp,
    core::log2_ceil,
    field::baby_bear::{BabyBearElem, BabyBearExtElem},
    field::{map_pow, Elem, ExtElem, RootsOfUnity},
    hal::cpu::{CpuBuffer, CpuHal},
    INV_RATE,
};
use std::collections::VecDeque;

pub const GLOBAL_MIX: usize = 0;
pub const GLOBAL_OUT: usize = 1;

pub struct CpuCircuitHal {
    mem: RefCell<Vec<Val>>,
    input: RefCell<VecDeque<u32>>,
}

impl CpuCircuitHal {
    pub fn new(input: VecDeque<u32>) -> Self {
        Self {
            mem: RefCell::new(Vec::new()),
            input: RefCell::new(input),
        }
    }
}

pub struct CpuExecContext<'a> {
    cycle: usize,
    tot_cycles: usize,
    mem: &'a RefCell<Vec<Val>>,

    elems_per_word: &'a RefCell<usize>,
    input: &'a RefCell<VecDeque<u32>>,
    input_elems: &'a RefCell<VecDeque<Val>>,
}

impl<'a> CycleContext for CpuExecContext<'a> {
    fn cycle(&self) -> usize {
        self.cycle
    }
    fn tot_cycles(&self) -> usize {
        self.tot_cycles
    }
}

impl<'a> CpuExecContext<'a> {
    pub fn get_cycle(&self) -> Result<Val> {
        Ok(Val::new(self.cycle as u32))
    }

    pub fn simple_memory_peek(&self, addr: Val) -> Result<Val> {
        let addr = u32::from(addr) as usize;
        let val = self
            .mem
            .borrow()
            .get(addr)
            .as_deref()
            .ok_or(anyhow!("invalid address {addr}"))
            .copied();
        tracing::trace!("Peeking {addr:?} -> {val:?}");
        val
    }

    pub fn simple_memory_poke(&self, addr: Val, val: Val) -> Result<()> {
        let addr = u32::from(addr) as usize;
        let mut mem = self.mem.borrow_mut();
        if mem.len() <= addr {
            mem.resize(addr + 1, Val::ZERO);
        }
        tracing::trace!("Poking {addr:?} from {:?} to {val:?}", mem[addr]);
        mem[addr] = val;
        Ok(())
    }

    pub fn configure_input(&self, elems_per_word: Val) -> Result<()> {
        let elems_per_word = u32::from(elems_per_word) as usize;
        let mut stored = self.elems_per_word.borrow_mut();
        if *stored != elems_per_word {
            tracing::trace!("Configuring {elems_per_word:?} elements per word");
        }
        assert!(self.input_elems.borrow().is_empty());
        *stored = elems_per_word;
        Ok(())
    }
    pub fn read_input(&self) -> Result<Val> {
        let mut elems = self.input_elems.borrow_mut();
        if elems.is_empty() {
            let word = self.input.borrow_mut().pop_front().expect("Input underrun");
            match *self.elems_per_word.borrow() {
                1 => elems.push_back(Val::from(word)),
                2 => elems.extend([word & 0xFFFF, word >> 16].map(Val::new)),
                4 => elems.extend(word.to_le_bytes().map(u32::from).map(Val::new)),
                elems_per_word @ _ => panic!("Unknown input configuration {}", elems_per_word),
            }
            tracing::trace!("Refilling input buffer from 0x{word:x} -> {elems:?}");
        }

        let val = elems.pop_front().expect("Input underrun");
        tracing::trace!("Read returns {val:?}");
        Ok(val)
    }

    pub fn abort(&self) -> Result<()> {
        Err(anyhow!("circuit aborted proving"))
    }

    pub fn assert(&self, condition: Val, message: &str) -> Result<()> {
        if condition == Val::ZERO {
            Err(anyhow!(message.to_owned()))
        } else {
            Ok(())
        }
    }

    pub fn log(&self, message: &str, x: impl AsRef<[Val]>) -> Result<()> {
        risc0_zirgen_dsl::codegen::default_log(message, x.as_ref())
    }

    // Stubs so we can compile with calculator circuit for rapid iteration
    #[allow(dead_code)]
    pub fn get_val_from_user(&self) -> Result<Val> {
        Ok(1u32.into())
    }
    #[allow(dead_code)]
    pub fn output_to_user(&self, _ov: Val) -> Result<()> {
        Ok(())
    }
}

impl<'a> keccak_circuit::CircuitHal<'a, CpuHal<CircuitField>> for CpuCircuitHal {
    fn step_exec(
        &self,
        tot_cycles: usize,
        data: &CpuBuffer<Val>,
        global: &CpuBuffer<Val>,
    ) -> Result<()> {
        let elems_per_word = &RefCell::new(0);
        let input_elems: &RefCell<VecDeque<Val>> = &RefCell::new(Default::default());

        let data = &data.as_slice_sync();
        let data = CycleRow { buf: data };
        let global = global.as_slice_sync();
        let global = GlobalRow { buf: &global };

        for cycle in 0..tot_cycles {
            tracing::trace!("exec {cycle}/{tot_cycles}");
            let exec_context = CpuExecContext {
                mem: &self.mem,
                cycle,
                tot_cycles,
                elems_per_word,
                input: &self.input,
                input_elems,
            };

            keccak_circuit::step_top(&exec_context, &data, &global)?;
        }
        tracing::trace!("exec complete");

        Ok(())
    }

    fn step_accum(
        &self,
        tot_cycles: usize,
        accum: &CpuBuffer<Val>,
        data: &CpuBuffer<Val>,
        mix: &CpuBuffer<Val>,
    ) -> Result<()> {
        let mem = &RefCell::default();
        let elems_per_word = &RefCell::default();
        let input = &RefCell::default();
        let input_elems = &RefCell::default();

        let orig_accum = accum;

        let data = &data.as_slice_sync();
        let data = CycleRow { buf: data };
        let mix = mix.as_slice_sync();
        let mix = GlobalRow { buf: &mix };

        for cycle in 0..tot_cycles {
            tracing::trace!("accum {cycle}/{tot_cycles}");
            let accum = &orig_accum.as_slice_sync();
            let accum = CycleRow { buf: accum };
            let exec_context = CpuExecContext {
                mem,
                cycle,
                tot_cycles,
                elems_per_word,
                input,
                input_elems,
            };
            keccak_circuit::step_top_accum(&exec_context, &accum, &data, &mix)?;
        }
        Ok(())
    }
}

impl risc0_zkp::hal::CircuitHal<CpuHal<CircuitField>> for CpuCircuitHal {
    fn accumulate(
        &self,
        _ctrl: &CpuBuffer<Val>,
        _io: &CpuBuffer<Val>,
        _data: &CpuBuffer<Val>,
        _mix: &CpuBuffer<Val>,
        _accum: &CpuBuffer<Val>,
        _steps: usize,
    ) {
    }

    fn eval_check(
        &self,
        orig_check: &CpuBuffer<Val>,
        groups: &[&CpuBuffer<Val>],
        globals: &[&CpuBuffer<Val>],
        poly_mix: ExtVal,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let poly_mix_pows = map_pow(dbg!(poly_mix), crate::info::POLY_MIX_POWERS);

        // SAFETY: Convert a borrow of a cell into a raw const slice so that we can pass
        // it over the thread boundary. This should be safe because the scope of the
        // usage is within this function and each thread access will not overlap with
        // each other.

        let data = groups[dbg!(REGISTER_GROUP_DATA)].as_slice();
        let data = unsafe { std::slice::from_raw_parts(data.as_ptr(), data.len()) };
        let accum = groups[dbg!(REGISTER_GROUP_ACCUM)].as_slice();
        let accum = unsafe { std::slice::from_raw_parts(accum.as_ptr(), accum.len()) };
        let mix = globals[GLOBAL_MIX].as_slice();
        let mix = unsafe { std::slice::from_raw_parts(mix.as_ptr(), mix.len()) };
        let out = globals[GLOBAL_OUT].as_slice();
        let out = unsafe { std::slice::from_raw_parts(out.as_ptr(), out.len()) };
        let check = orig_check.as_slice();
        let check = unsafe { std::slice::from_raw_parts(check.as_ptr(), check.len()) };
        let poly_mix_pows = poly_mix_pows.as_slice();

        let args: &[&[BabyBearElem]] = &[&accum, &data, &out, &mix];

        (0..domain).into_par_iter().for_each(|cycle| {
            let tot = CircuitImpl.poly_fp(cycle, domain, poly_mix_pows, args);
            let x = BabyBearElem::ROU_FWD[po2 + EXP_PO2].pow(cycle);
            // TODO: what is this magic number 3?
            let y = (BabyBearElem::new(3) * x).pow(1 << po2);
            let ret = tot * (y - BabyBearElem::new(1)).inv();

            // SAFETY: This conversion is to make the check slice mutable, which should be
            // safe because each thread access will not overlap with each other.
            let check = unsafe {
                std::slice::from_raw_parts_mut(check.as_ptr() as *mut BabyBearElem, check.len())
            };
            for i in 0..BabyBearExtElem::EXT_SIZE {
                check[i * domain + cycle] = ret.elems()[i];
            }
        });
    }
}
