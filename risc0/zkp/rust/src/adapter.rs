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

use anyhow::{bail, Result};

use crate::{
    core::{fp::Fp, fp4::Fp4},
    taps::TapSet,
    INV_RATE,
};

#[derive(Clone, Copy)]
pub struct MixState {
    pub tot: Fp4,
    pub mul: Fp4,
}

pub trait CustomStep {
    fn call(&mut self, name: &str, extra: &str, args: &[Fp]) -> Result<Vec<Fp>>;
}

pub struct CircuitStepContext {
    pub size: usize,
    pub cycle: usize,
}

impl CircuitStepContext {
    fn mask(&self) -> usize {
        self.size - 1
    }

    pub fn _const(&self, value: u32, _loc: &str) -> Fp {
        Fp::from(value)
    }

    pub fn _get(&self, base: &[Fp], offset: usize, back: usize, _loc: &str) -> Fp {
        let cycle = self.cycle.wrapping_sub(back);
        let ret = base[offset * self.size + (cycle & self.mask())];
        // assert_ne!(ret, Fp::invalid());
        ret
    }

    pub fn _set(&self, base: &mut [Fp], value: Fp, offset: usize, _loc: &str) {
        let reg = &mut base[offset * self.size + self.cycle];
        assert!(*reg == Fp::invalid() || *reg == Fp::new(0) || *reg == value);
        *reg = value;
    }

    pub fn _get_global(&self, base: &[Fp], offset: usize, _loc: &str) -> Fp {
        base[offset]
    }

    pub fn _set_global(&self, base: &mut [Fp], value: Fp, offset: usize, _loc: &str) {
        base[offset] = value;
    }

    pub fn as_bool(&self, x: &Fp, _loc: &str) -> bool {
        *x != Fp::new(0)
    }

    pub fn _add(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a + b
    }

    pub fn _sub(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a - b
    }

    pub fn _mul(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a * b
    }

    pub fn _bitAnd(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        let a: u32 = a.into();
        let b: u32 = b.into();
        Fp::new(a & b)
    }

    pub fn _eqz(&self, a: Fp, loc: &str) -> Result<()> {
        if a != Fp::new(0) {
            bail!("0x{:08X} is not zero at: {}", u32::from(a), loc);
        }
        Ok(())
    }

    pub fn _inv(&self, a: Fp, _loc: &str) -> Fp {
        a.inv()
    }

    pub fn _isz(&self, a: Fp, _loc: &str) -> Fp {
        if a == Fp::new(0) {
            Fp::new(1)
        } else {
            Fp::new(0)
        }
    }
}

pub trait CircuitStepExec<S: CustomStep> {
    fn step_exec(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp>;
}

pub trait CircuitStepVerify<S: CustomStep> {
    fn step_verify(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp>;
}

pub trait CircuitStepAccum<S: CustomStep> {
    fn step_accum(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp>;
}

pub struct PolyFpContext {
    pub size: usize,
    pub cycle: usize,
    pub mix: Fp4,
}

impl PolyFpContext {
    fn mask(&self) -> usize {
        self.size - 1
    }

    pub fn _const(&self, value: u32, _loc: &str) -> Fp {
        Fp::from(value)
    }

    pub fn _get(&self, base: &[Fp], offset: usize, back: usize, _tap: usize, _loc: &str) -> Fp {
        // Cycle here is over the expanded domain
        let cycle = self.cycle.wrapping_sub(INV_RATE * back);
        base[offset * self.size + (cycle & self.mask())]
    }

    pub fn _get_global(&self, base: &[Fp], offset: usize, _loc: &str) -> Fp {
        base[offset]
    }

    pub fn _add(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a + b
    }

    pub fn _sub(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a - b
    }

    pub fn _mul(&self, a: Fp, b: Fp, _loc: &str) -> Fp {
        a * b
    }

    pub fn _true(&self, _loc: &str) -> MixState {
        MixState {
            tot: Fp4::from_u32(0),
            mul: Fp4::from_u32(1),
        }
    }

    pub fn _and_eqz(&self, x: MixState, val: Fp, _loc: &str) -> MixState {
        MixState {
            tot: x.tot + x.mul * val,
            mul: x.mul * self.mix,
        }
    }

    pub fn _and_cond(&self, x: MixState, cond: Fp, inner: MixState, _loc: &str) -> MixState {
        MixState {
            tot: x.tot + cond * inner.tot * x.mul,
            mul: x.mul * inner.mul,
        }
    }
}

pub trait PolyFp {
    fn poly_fp(
        &self,
        ctx: &PolyFpContext,
        code: &[Fp],
        out: &[Fp],
        data: &[Fp],
        mix: &[Fp],
        accum: &[Fp],
    ) -> MixState;
}

pub struct PolyExtContext {
    pub mix: Fp4,
}

impl PolyExtContext {
    pub fn _const(&self, value: u32, _loc: &str) -> Fp4 {
        Fp4::from_u32(value)
    }

    pub fn _get(&self, u: &[Fp4], tap: usize, _loc: &str) -> Fp4 {
        u[tap]
    }

    pub fn _get_global(&self, base: &[Fp], offset: usize, _loc: &str) -> Fp4 {
        Fp4::from_fp(base[offset])
    }

    pub fn _add(&self, a: Fp4, b: Fp4, _loc: &str) -> Fp4 {
        a + b
    }

    pub fn _sub(&self, a: Fp4, b: Fp4, _loc: &str) -> Fp4 {
        a - b
    }

    pub fn _mul(&self, a: Fp4, b: Fp4, _loc: &str) -> Fp4 {
        a * b
    }

    pub fn _true(&self, _loc: &str) -> MixState {
        MixState {
            tot: Fp4::from_u32(0),
            mul: Fp4::from_u32(1),
        }
    }

    pub fn _and_eqz(&self, x: MixState, val: Fp4, _loc: &str) -> MixState {
        MixState {
            tot: x.tot + x.mul * val,
            mul: x.mul * self.mix,
        }
    }

    pub fn _and_cond(&self, x: MixState, cond: Fp4, inner: MixState, _loc: &str) -> MixState {
        MixState {
            tot: x.tot + cond * inner.tot * x.mul,
            mul: x.mul * inner.mul,
        }
    }
}

pub trait PolyExt {
    fn poly_ext(&self, ctx: &PolyExtContext, u: &[Fp4], out: &[Fp], mix: &[Fp]) -> MixState;
}

pub trait TapsProvider {
    fn get_taps(&self) -> &TapSet;
}

pub trait CircuitInfo {
    fn output_size(&self) -> usize;

    fn mix_size(&self) -> usize;
}

pub trait CircuitDef<S: CustomStep>:
    CircuitInfo
    + CircuitStepAccum<S>
    + CircuitStepExec<S>
    + CircuitStepVerify<S>
    + PolyFp
    + PolyExt
    + TapsProvider
{
}

pub type Arg = usize;
pub type Var = usize;

pub struct CircuitStepDef {
    pub block: &'static [CircuitStep],
    pub ret: Var,
}

pub enum CircuitStep {
    Const(u32, &'static str),
    Get(Arg, usize, usize, &'static str),
    Set(Arg, Var, usize, &'static str),
    GetGlobal(Arg, usize, &'static str),
    SetGlobal(Arg, Var, usize, &'static str),
    If(Var, &'static [CircuitStep], &'static str),
    Add(Var, Var, &'static str),
    Sub(Var, Var, &'static str),
    Mul(Var, Var, &'static str),
    BitAnd(Var, Var, &'static str),
    EqZero(Var, &'static str),
    Inv(Var, &'static str),
    IsZero(Var, &'static str),
    Extern(&'static str, &'static str, &'static [Var], &'static str),
    Nondet(&'static [CircuitStep], &'static str),
}

impl CircuitStep {
    pub fn step<S: CustomStep>(
        &self,
        stack: &mut Vec<Fp>,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<()> {
        Ok(match self {
            CircuitStep::Const(value, _loc) => {
                stack.push(Fp::new(*value));
            }
            CircuitStep::Get(base, offset, back, _loc) => {
                let cycle = ctx.cycle.wrapping_sub(*back);
                let value = args[*base][offset * ctx.size + (cycle & ctx.mask())];
                // assert_ne!(value, Fp::invalid());
                stack.push(value);
            }
            CircuitStep::Set(base, value, offset, _loc) => {
                let value = stack[*value];
                let reg = &mut args[*base][offset * ctx.size + ctx.cycle];
                assert!(*reg == Fp::invalid() || *reg == Fp::new(0) || *reg == value);
                *reg = value;
            }
            CircuitStep::GetGlobal(base, offset, _loc) => {
                stack.push(args[*base][*offset]);
            }
            CircuitStep::SetGlobal(base, value, offset, _loc) => {
                args[*base][*offset] = stack[*value];
            }
            CircuitStep::If(cond, block, _loc) => {
                if stack[*cond] != Fp::new(0) {
                    let mut stack = stack.clone();
                    for op in block.iter() {
                        op.step(&mut stack, ctx, custom, args)?;
                    }
                }
            }
            CircuitStep::Add(x1, x2, _loc) => {
                stack.push(stack[*x1] + stack[*x2]);
            }
            CircuitStep::Sub(x1, x2, _loc) => {
                stack.push(stack[*x1] - stack[*x2]);
            }
            CircuitStep::Mul(x1, x2, _loc) => {
                stack.push(stack[*x1] * stack[*x2]);
            }
            CircuitStep::BitAnd(x1, x2, _loc) => {
                let x1: u32 = stack[*x1].into();
                let x2: u32 = stack[*x2].into();
                stack.push(Fp::new(x1 & x2));
            }
            CircuitStep::EqZero(x, loc) => {
                let value = stack[*x];
                if value != Fp::new(0) {
                    bail!("{x}: 0x{:08X} is not zero at: {}", u32::from(value), loc);
                }
            }
            CircuitStep::Inv(x, _loc) => {
                stack.push(stack[*x].inv());
            }
            CircuitStep::IsZero(x, _loc) => {
                stack.push(if stack[*x] == Fp::new(0) {
                    Fp::new(1)
                } else {
                    Fp::new(0)
                });
            }
            CircuitStep::Extern(name, extra, args, _loc) => {
                let args: Vec<Fp> = args.iter().map(|x| stack[*x]).collect();
                stack.extend(custom.call(name, extra, &args)?);
            }
            CircuitStep::Nondet(block, _loc) => {
                let mut stack = stack.clone();
                for op in block.iter() {
                    op.step(&mut stack, ctx, custom, args)?;
                }
            }
        })
    }
}

impl CircuitStepDef {
    pub fn step<S: CustomStep>(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp> {
        let mut stack = Vec::new();
        for op in self.block.iter() {
            op.step(&mut stack, ctx, custom, args)?;
        }
        Ok(stack[self.ret])
    }
}
