// Copyright 2022 Risc0, Inc.
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

use alloc::vec::Vec;

use anyhow::Result;

use crate::{
    field::{Elem, ExtElem, Field},
    taps::{RegisterGroup, TapSet},
};

#[derive(Clone, Copy)]
pub struct MixState<EE: ExtElem> {
    pub tot: EE,
    pub mul: EE,
}

pub trait CircuitStepHandler<E: Elem> {
    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[E],
        outs: &mut [E],
    ) -> Result<()>;

    fn sort(&mut self, name: &str);
    fn calc_prefix_products(&mut self);
}

pub struct CircuitStepContext {
    pub size: usize,
    pub cycle: usize,
}

pub trait CircuitStep<E: Elem> {
    fn step_exec<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [E]],
    ) -> Result<E>;

    fn step_verify_bytes<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [E]],
    ) -> Result<E>;

    fn step_verify_mem<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [E]],
    ) -> Result<E>;

    fn step_compute_accum<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [E]],
    ) -> Result<E>;

    fn step_verify_accum<S: CircuitStepHandler<E>>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [E]],
    ) -> Result<E>;
}

pub trait PolyFp<F: Field> {
    fn poly_fp(
        &self,
        cycle: usize,
        steps: usize,
        mix: &F::ExtElem,
        args: &[&[F::Elem]],
    ) -> F::ExtElem;
}

pub trait PolyExt<F: Field> {
    fn poly_ext(
        &self,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) -> MixState<F::ExtElem>;
}

pub trait TapsProvider {
    fn get_taps(&self) -> &'static TapSet<'static>;

    fn code_size(&self) -> usize {
        self.get_taps().group_size(RegisterGroup::Code)
    }
}

pub trait CircuitInfo {
    const OUTPUT_SIZE: usize;
    const MIX_SIZE: usize;
}

pub trait CircuitDef<F: Field>:
    CircuitInfo + CircuitStep<F::Elem> + PolyFp<F> + PolyExt<F> + TapsProvider + Sync
{
}

pub type Arg = usize;
pub type Var = usize;

pub struct PolyExtStepDef {
    pub block: &'static [PolyExtStep],
    pub ret: Var,
}

pub enum PolyExtStep {
    Const(u32, &'static str),
    Get(usize, &'static str),
    GetGlobal(Arg, usize, &'static str),
    Add(Var, Var, &'static str),
    Sub(Var, Var, &'static str),
    Mul(Var, Var, &'static str),
    True(&'static str),
    AndEqz(Var, Var, &'static str),
    AndCond(Var, Var, Var, &'static str),
}

impl PolyExtStep {
    pub fn step<F: Field>(
        &self,
        fp_vars: &mut Vec<F::ExtElem>,
        mix_vars: &mut Vec<MixState<F::ExtElem>>,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) {
        match self {
            PolyExtStep::Const(value, _loc) => {
                let elem = F::Elem::from_u64(*value as u64);
                fp_vars.push(F::ExtElem::from_subfield(&elem));
            }
            PolyExtStep::Get(tap, _loc) => {
                fp_vars.push(u[*tap]);
            }
            PolyExtStep::GetGlobal(base, offset, _loc) => {
                fp_vars.push(F::ExtElem::from_subfield(&args[*base][*offset]));
            }
            PolyExtStep::Add(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] + fp_vars[*x2]);
            }
            PolyExtStep::Sub(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] - fp_vars[*x2]);
            }
            PolyExtStep::Mul(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] * fp_vars[*x2]);
            }
            PolyExtStep::True(_loc) => {
                mix_vars.push(MixState {
                    tot: F::ExtElem::ZERO,
                    mul: F::ExtElem::ONE,
                });
            }
            PolyExtStep::AndEqz(x, val, _loc) => {
                let x = mix_vars[*x];
                let val = fp_vars[*val];
                mix_vars.push(MixState {
                    tot: x.tot + x.mul * val,
                    mul: x.mul * *mix,
                });
            }
            PolyExtStep::AndCond(x, cond, inner, _loc) => {
                let x = mix_vars[*x];
                let cond = fp_vars[*cond];
                let inner = mix_vars[*inner];
                mix_vars.push(MixState {
                    tot: x.tot + cond * inner.tot * x.mul,
                    mul: x.mul * inner.mul,
                });
            }
        }
    }
}

impl PolyExtStepDef {
    pub fn step<F: Field>(
        &self,
        mix: &F::ExtElem,
        u: &[F::ExtElem],
        args: &[&[F::Elem]],
    ) -> MixState<F::ExtElem> {
        let mut fp_vars = Vec::with_capacity(self.block.len() - (self.ret + 1));
        let mut mix_vars = Vec::with_capacity(self.ret + 1);
        for op in self.block.iter() {
            op.step::<F>(&mut fp_vars, &mut mix_vars, mix, u, args);
        }
        assert_eq!(
            fp_vars.len(),
            self.block.len() - (self.ret + 1),
            "Miscalculated capacity for fp_vars"
        );
        assert_eq!(
            mix_vars.len(),
            self.ret + 1,
            "Miscalculated capacity for mix_vars"
        );
        mix_vars[self.ret]
    }
}
