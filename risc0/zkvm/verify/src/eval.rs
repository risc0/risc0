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

use risc0_zkp_core::{fp::Fp, fp4::Fp4};

use crate::{
    poly_op::PolyOp,
    poly_ops::{RISC0_CONS, RISC0_FP4S, RISC0_POLY_OPS},
};

#[derive(Clone, Copy, Default)]
struct MixState {
    tot: Fp4,
    mul: Fp4,
}

impl MixState {
    pub fn assert_zero(self, val: Fp4, mix: Fp4) -> MixState {
        MixState {
            tot: self.tot + self.mul * val,
            mul: self.mul * mix,
        }
    }

    pub fn combine(self, cond: Fp4, inner: MixState) -> MixState {
        MixState {
            tot: self.tot + cond * self.mul * inner.tot,
            mul: self.mul * inner.mul,
        }
    }
}

pub fn evaluate(u: &[Fp4], g: &[Fp], mix: Fp4) -> Fp4 {
    let mut fps = vec![Fp4::default(); RISC0_FP4S];
    let mut cons = vec![MixState::default(); RISC0_CONS];
    let mut result = MixState::default();
    for op in RISC0_POLY_OPS.iter() {
        match op {
            PolyOp::Const { out, val } => fps[*out] = Fp4::from(*val),
            PolyOp::Get { out, idx } => fps[*out] = u[*idx],
            PolyOp::GetGlobal { out, idx } => fps[*out] = Fp4::from(g[*idx]),
            PolyOp::Begin { out } => {
                cons[*out] = MixState {
                    tot: Fp4::from(0),
                    mul: Fp4::from(1),
                }
            }
            PolyOp::AssertZero { out, orig, val } => {
                cons[*out] = cons[*orig].assert_zero(fps[*val], mix)
            }
            PolyOp::Combine {
                out,
                orig,
                cond,
                inner,
            } => cons[*out] = cons[*orig].combine(fps[*cond], cons[*inner]),
            PolyOp::Add { out, a, b } => fps[*out] = fps[*a] + fps[*b],
            PolyOp::Sub { out, a, b } => fps[*out] = fps[*a] - fps[*b],
            PolyOp::Mul { out, a, b } => fps[*out] = fps[*a] * fps[*b],
            PolyOp::Result { val } => result = cons[*val],
        }
    }
    result.tot
}
