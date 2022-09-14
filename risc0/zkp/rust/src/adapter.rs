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
    core::{fp::Fp, fp4::Fp4},
    taps::{RegisterGroup, TapSet},
    INV_RATE,
};

#[derive(Clone, Copy)]
pub struct MixState {
    pub tot: Fp4,
    pub mul: Fp4,
}

pub trait CustomStep {
    fn call(&mut self, name: &str, extra: &str, args: &[Fp], outs: &mut [Fp]) -> Result<()>;
}

pub struct CircuitStepContext {
    pub size: usize,
    pub cycle: usize,
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
    fn step_verify_bytes(
        &self,
        ctx: &CircuitStepContext,
        custom: &mut S,
        args: &mut [&mut [Fp]],
    ) -> Result<Fp>;

    fn step_verify_mem(
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
    fn poly_fp(&self, ctx: &PolyFpContext, args: &[&[Fp]]) -> MixState;
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
    fn poly_ext(&self, ctx: &PolyExtContext, u: &[Fp4], args: &[&[Fp]]) -> MixState;
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

pub struct PolyFpStepDef {
    pub block: &'static [PolyFpStep],
    pub ret: Var,
}

pub enum PolyFpStep {
    Const(u32, &'static str),
    Get(Arg, usize, usize, &'static str),
    GetGlobal(Arg, usize, &'static str),
    Add(Var, Var, &'static str),
    Sub(Var, Var, &'static str),
    Mul(Var, Var, &'static str),
    True(&'static str),
    AndEqz(Var, Var, &'static str),
    AndCond(Var, Var, Var, &'static str),
}

impl PolyFpStep {
    pub fn step(
        &self,
        fp_vars: &mut Vec<Fp>,
        mix_vars: &mut Vec<MixState>,
        ctx: &PolyFpContext,
        args: &[&[Fp]],
    ) {
        match self {
            PolyFpStep::Const(value, _loc) => {
                fp_vars.push(Fp::new(*value));
            }
            PolyFpStep::Get(base, offset, back, _loc) => {
                // Cycle here is over the expanded domain
                let cycle = ctx.cycle.wrapping_sub(INV_RATE * back);
                let value = args[*base][offset * ctx.size + (cycle & ctx.mask())];
                fp_vars.push(value);
            }
            PolyFpStep::GetGlobal(base, offset, _loc) => {
                fp_vars.push(args[*base][*offset]);
            }
            PolyFpStep::Add(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] + fp_vars[*x2]);
            }
            PolyFpStep::Sub(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] - fp_vars[*x2]);
            }
            PolyFpStep::Mul(x1, x2, _loc) => {
                fp_vars.push(fp_vars[*x1] * fp_vars[*x2]);
            }
            PolyFpStep::True(_loc) => {
                mix_vars.push(MixState {
                    tot: Fp4::from_u32(0),
                    mul: Fp4::from_u32(1),
                });
            }
            PolyFpStep::AndEqz(x, val, _loc) => {
                let x = mix_vars[*x];
                let val = fp_vars[*val];
                mix_vars.push(MixState {
                    tot: x.tot + x.mul * val,
                    mul: x.mul * ctx.mix,
                });
            }
            PolyFpStep::AndCond(x, cond, inner, _loc) => {
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

impl PolyFpStepDef {
    pub fn step(&self, ctx: &PolyFpContext, args: &[&[Fp]]) -> MixState {
        let mut fp_vars = Vec::new();
        let mut mix_vars = Vec::new();
        for op in self.block.iter() {
            op.step(&mut fp_vars, &mut mix_vars, ctx, args);
        }
        mix_vars[self.ret]
    }
}

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
    pub fn step(
        &self,
        fp_vars: &mut Vec<Fp4>,
        mix_vars: &mut Vec<MixState>,
        ctx: &PolyExtContext,
        u: &[Fp4],
        args: &[&[Fp]],
    ) {
        match self {
            PolyExtStep::Const(value, _loc) => {
                fp_vars.push(Fp4::from_u32(*value));
            }
            PolyExtStep::Get(tap, _loc) => {
                fp_vars.push(u[*tap]);
            }
            PolyExtStep::GetGlobal(base, offset, _loc) => {
                fp_vars.push(Fp4::from_fp(args[*base][*offset]));
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
                    tot: Fp4::from_u32(0),
                    mul: Fp4::from_u32(1),
                });
            }
            PolyExtStep::AndEqz(x, val, _loc) => {
                let x = mix_vars[*x];
                let val = fp_vars[*val];
                mix_vars.push(MixState {
                    tot: x.tot + x.mul * val,
                    mul: x.mul * ctx.mix,
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
    pub fn step(&self, ctx: &PolyExtContext, u: &[Fp4], args: &[&[Fp]]) -> MixState {
        let mut fp_vars = Vec::with_capacity(self.block.len() - (self.ret + 1));
        let mut mix_vars = Vec::with_capacity(self.ret + 1);
        for op in self.block.iter() {
            op.step(&mut fp_vars, &mut mix_vars, ctx, u, args);
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
