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

use super::calc_circuit;
use anyhow::Result;
use calc_circuit::{CircuitField, ExtVal, Val, REGISTER_GROUP_DATA};
use core::cell::RefCell;
use risc0_zirgen_dsl::{CycleContext, CycleRow, GlobalRow};
use risc0_zkp::{
    core::log2_ceil,
    field::{Elem, ExtElem, RootsOfUnity},
    hal::cpu::{CpuBuffer, CpuHal},
    INV_RATE,
};
use std::collections::VecDeque;

pub const _GLOBAL_MIX: usize = 1;
pub const GLOBAL_OUT: usize = 0;

pub struct CpuCircuitHal {
    from_user: VecDeque<Val>,
    to_user: VecDeque<Val>,
}

impl CpuCircuitHal {
    pub fn new(from_user: &[usize]) -> Self {
        Self {
            from_user: from_user.iter().map(|val| Val::new(*val as u32)).collect(),
            to_user: [].into(),
        }
    }
}

pub struct CpuExecContext {
    cycle: usize,
    tot_cycles: usize,
    from_user: RefCell<VecDeque<Val>>,
    to_user: RefCell<VecDeque<Val>>,
}

impl CycleContext for CpuExecContext {
    fn cycle(&self) -> usize {
        self.cycle
    }
    fn tot_cycles(&self) -> usize {
        self.tot_cycles
    }
}

pub struct ValidityCtx {
    cycle: usize,
    domain: usize,
    pub poly_mix: ExtVal,
}

impl CycleContext for ValidityCtx {
    fn cycle(&self) -> usize {
        self.cycle
    }
    fn tot_cycles(&self) -> usize {
        self.domain
    }
}

impl CpuExecContext {
    pub fn get_val_from_user(&self) -> Result<Val> {
        let mut from_user = RefCell::borrow_mut(&self.from_user);
        eprintln!("get_val_from_user, from_user = {from_user:?}");
        Ok(from_user.pop_front().unwrap())
    }

    pub fn output_to_user(&self, val: Val) -> Result<()> {
        let mut to_user = RefCell::borrow_mut(&self.to_user);
        to_user.push_back(val);
        eprintln!("output_to_user, to_user = {to_user:?}");
        Ok(())
    }

    pub fn log(&self, message: &str, x: impl AsRef<[Val]>) -> Result<()> {
        risc0_zirgen_dsl::codegen::default_log(message, x.as_ref())
    }
}

impl<'a> calc_circuit::CircuitHal<'a, CpuHal<CircuitField>> for CpuCircuitHal {
    fn step_exec(
        &self,
        tot_cycles: usize,
        data: &CpuBuffer<Val>,
        global: &CpuBuffer<Val>,
    ) -> Result<()> {
        let data = &data.as_slice_sync();
        let data = CycleRow { buf: data };
        let global = global.as_slice_sync();
        let global = GlobalRow { buf: &global };

        let mut exec_context = CpuExecContext {
            cycle: 0,
            tot_cycles,
            from_user: RefCell::new(self.from_user.clone()),
            to_user: RefCell::new(self.to_user.clone()),
        };
        for cycle in 0..tot_cycles {
            exec_context.cycle = cycle;
            tracing::trace!("exec {cycle}/{tot_cycles}");

            calc_circuit::step_top(&exec_context, &data, &global)?;
        }
        tracing::trace!("exec complete");

        Ok(())
    }

    fn step_accum(
        &self,
        _tot_cycles: usize,
        _accum: &CpuBuffer<Val>,
        _data: &CpuBuffer<Val>,
        _global: &CpuBuffer<Val>,
    ) -> Result<()> {
        // The calculator circuit has no arguments, so there's no work to do here
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

        let data = groups[REGISTER_GROUP_DATA].as_slice_sync();
        let data = CycleRow { buf: &data };
        let global = globals[GLOBAL_OUT].as_slice_sync();
        let global = GlobalRow { buf: &global };
        let check = orig_check.as_slice_sync();

        // TODO: modularize this
        (0..domain).into_iter().for_each(|cycle| {
            let tot = calc_circuit::validity::calculator(
                &ValidityCtx {
                    cycle,
                    domain,
                    poly_mix,
                },
                &data,
                &global,
            )
            .unwrap();
            let x = Val::ROU_FWD[po2 + EXP_PO2].pow(cycle);
            // TODO: what is this magic number 3?
            let y = (Val::new(3) * x).pow(1 << po2);
            let ret = tot.tot * (y - Val::new(1)).inv();

            for i in 0..ExtVal::EXT_SIZE {
                check.set(i * domain + cycle, ret.elems()[i]);
            }
        });
    }
}
