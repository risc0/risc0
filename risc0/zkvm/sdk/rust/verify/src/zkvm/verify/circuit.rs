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

use alloc::{vec, vec::Vec};
use core::slice;

use risc0_zkp::{
    core::{
        fp::Fp,
        fp4::Fp4,
        log2_ceil,
        sha::{Digest, Sha, DIGEST_WORDS, DIGEST_WORD_SIZE},
        Random,
    },
    taps::{legacy::Taps, TapSet},
    verify::{self, read_iop::ReadIOP, VerificationError},
    MAX_CYCLES,
};

use crate::{
    zkvm::{
        poly_op::PolyOp,
        poly_ops::{RISC0_CONS, RISC0_FP4S, RISC0_POLY_OPS},
        taps::RISCV_TAPS,
    },
    ACCUM_MIX_GLOBAL_SIZE, OUTPUT_REGS,
};

const MIN_CYCLES: usize = 512;

pub struct MethodID {
    pub digests: Vec<Digest>,
}

impl TryFrom<&[u8]> for MethodID {
    type Error = VerificationError;

    fn try_from(bytes: &[u8]) -> Result<MethodID, VerificationError> {
        let words: Result<Vec<u32>, VerificationError> = bytes
            .chunks(DIGEST_WORD_SIZE)
            .map(|bytes| {
                Ok(u32::from_le_bytes(
                    bytes
                        .try_into()
                        .or(Err(VerificationError::ReceiptFormatError))?,
                ))
            })
            .collect();
        let digests: Result<Vec<Digest>, VerificationError> = words?
            .chunks(DIGEST_WORDS)
            .map(|digest| {
                Ok(Digest::new(
                    digest
                        .try_into()
                        .or(Err(VerificationError::ReceiptFormatError))?,
                ))
            })
            .collect();
        Ok(MethodID { digests: digests? })
    }
}

pub struct RV32Circuit<'a> {
    po2: u32,
    globals: Vec<Fp>,
    code_id: &'a MethodID,
}

impl<'a> RV32Circuit<'a> {
    pub fn new(code_id: &'a MethodID) -> Self {
        RV32Circuit {
            po2: 0,
            globals: vec![],
            code_id,
        }
    }
}

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

impl<'a> verify::Circuit for RV32Circuit<'a> {
    fn taps(&self) -> &TapSet {
        todo!()
    }

    fn execute<S: Sha>(&mut self, iop: &mut ReadIOP<S>) {
        for _ in 0..OUTPUT_REGS {
            let mut reg: u32 = 0;
            iop.read_u32s(slice::from_mut(&mut reg));
            self.globals.push(Fp::from(reg & 0xffff));
            self.globals.push(Fp::from(reg >> 16));
        }
        iop.read_u32s(slice::from_mut(&mut self.po2));
    }

    fn accumulate<S: Sha>(&mut self, iop: &mut ReadIOP<S>) {
        for _ in 0..ACCUM_MIX_GLOBAL_SIZE {
            self.globals.push(Fp::random(iop));
        }
    }

    fn po2(&self) -> u32 {
        self.po2
    }

    fn check_code(&self, root: &Digest) -> Result<(), VerificationError> {
        let which_code: usize = self.po2 as usize - log2_ceil(MIN_CYCLES as usize);
        if &self.code_id.digests[which_code] == root {
            Ok(())
        } else {
            Err(VerificationError::MethodVerificationError)
        }
    }

    fn compute_polynomial(&self, u: &[Fp4], mix: Fp4) -> Fp4 {
        let mut fps = vec![Fp4::default(); RISC0_FP4S];
        let mut cons = vec![MixState::default(); RISC0_CONS];
        let mut result = MixState::default();
        for op in &*RISC0_POLY_OPS {
            match *op {
                PolyOp::Const { out, val } => fps[out] = Fp4::from(val),
                PolyOp::Get { out, idx } => fps[out] = u[idx],
                PolyOp::GetGlobal { out, idx } => fps[out] = Fp4::from(self.globals[idx]),
                PolyOp::Begin { out } => {
                    cons[out] = MixState {
                        tot: Fp4::from(0),
                        mul: Fp4::from(1),
                    }
                }
                PolyOp::AssertZero { out, orig, val } => {
                    cons[out] = cons[orig].assert_zero(fps[val], mix)
                }
                PolyOp::Combine {
                    out,
                    orig,
                    cond,
                    inner,
                } => cons[out] = cons[orig].combine(fps[cond], cons[inner]),
                PolyOp::Add { out, a, b } => fps[out] = fps[a] + fps[b],
                PolyOp::Sub { out, a, b } => fps[out] = fps[a] - fps[b],
                PolyOp::Mul { out, a, b } => fps[out] = fps[a] * fps[b],
                PolyOp::Result { val } => result = cons[val],
            }
        }
        result.tot
    }
}
