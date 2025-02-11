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

use std::{io::Read, ops::Rem};

use anyhow::{anyhow, Result};
use byteorder::{LittleEndian, ReadBytesExt};
use malachite::{
    num::{arithmetic::traits::ModInverse, basic::traits::Zero},
    Integer, Natural,
};
use num_derive::FromPrimitive;
use num_traits::FromPrimitive;

#[derive(Debug)]
pub(crate) struct Type {
    pub coeffs: u64,
    _max_pos: u64,
    _max_neg: u64,
    _min_bits: u64,
}

#[derive(Debug)]
pub(crate) struct Input {
    _label: u64,
    _bit_width: u32,
    _min_bits: u16,
    _is_public: bool,
}

#[derive(Debug, FromPrimitive)]
pub(crate) enum OpCode {
    Const = 0x2, // unary: constant index
    Load = 0x3,  // unary: constant index
    Store = 0x4, // unary: constant index
    Add = 0x8,   // binary
    Sub = 0x9,   // binary
    Mul = 0xA,   // binary
    Rem = 0xB,   // binary
    Quo = 0xC,   // binary
    Inv = 0xE,   // binary
}

#[derive(Debug)]
pub(crate) struct Op {
    pub code: OpCode,
    pub result_type: usize,
    pub a: usize,
    pub b: usize,
}

pub(crate) struct Program {
    pub inputs: Vec<Input>,
    pub types: Vec<Type>,
    pub constants: Vec<u64>,
    pub ops: Vec<Op>,
}

pub(crate) trait BigIntIO {
    fn load(&mut self, arena: u32, offset: u32, count: u32) -> Result<Natural>;

    fn store(&mut self, arena: u32, offset: u32, count: u32, value: &Natural) -> Result<()>;
}

impl Op {
    pub fn arena(&self) -> u32 {
        (self.a >> 16) as u32
    }

    pub fn offset(&self) -> u32 {
        (self.a & 0xffff) as u32
    }

    pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
        let bits = stream.read_u64::<LittleEndian>()?;
        let opcode = FromPrimitive::from_u32((bits & 0x0F) as u32);
        Ok(Self {
            code: opcode.ok_or_else(|| anyhow!("Invalid BigInt2 bytecode"))?,
            result_type: ((bits >> 4) & 0x0FFF) as usize,
            a: ((bits >> 16) & 0x00FFFFFF) as usize,
            b: ((bits >> 40) & 0x00FFFFFF) as usize,
        })
    }
}

impl Input {
    pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
        Ok(Self {
            _label: stream.read_u64::<LittleEndian>()?,
            _bit_width: stream.read_u32::<LittleEndian>()?,
            _min_bits: stream.read_u16::<LittleEndian>()?,
            _is_public: stream.read_u16::<LittleEndian>()? != 0,
        })
    }
}

impl Type {
    pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
        Ok(Self {
            coeffs: stream.read_u64::<LittleEndian>()?,
            _max_pos: stream.read_u64::<LittleEndian>()?,
            _max_neg: stream.read_u64::<LittleEndian>()?,
            _min_bits: stream.read_u64::<LittleEndian>()?,
        })
    }
}

impl Program {
    pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
        // Read the header. Validate magic number and version.
        let mut magic = [0u8; 4];
        stream.read_exact(&mut magic)?;
        assert_eq!(magic, [0x62, 0x69, 0x62, 0x63]);

        let version = stream.read_u32::<LittleEndian>()?;
        assert_eq!(version, 1);

        let num_inputs = stream.read_u32::<LittleEndian>()? as usize;
        let num_types = stream.read_u32::<LittleEndian>()? as usize;
        let num_constants = stream.read_u32::<LittleEndian>()? as usize;
        let num_ops = stream.read_u32::<LittleEndian>()? as usize;

        // Allocate storage for the program sections, then read each one.
        let mut result = Self {
            inputs: Vec::with_capacity(num_inputs),
            types: Vec::with_capacity(num_types),
            constants: Vec::with_capacity(num_constants),
            ops: Vec::with_capacity(num_ops),
        };
        for _ in 0..num_inputs {
            result.inputs.push(Input::decode(stream)?);
        }
        for _ in 0..num_types {
            result.types.push(Type::decode(stream)?);
        }
        for _ in 0..num_constants {
            result.constants.push(stream.read_u64::<LittleEndian>()?);
        }
        for _ in 0..num_ops {
            result.ops.push(Op::decode(stream)?);
        }
        Ok(result)
    }

    pub fn eval<T: BigIntIO>(&self, io: &mut T) -> Result<()> {
        let mut regs = vec![Integer::ZERO; self.ops.len()];
        for (op_index, op) in self.ops.iter().enumerate() {
            tracing::trace!("[{op_index}]: {op:?}");
            match op.code {
                OpCode::Const => {
                    let offset = op.a;
                    let words = op.b;
                    let mut value = Natural::from(0_u64);
                    for i in 0..words {
                        let word: u64 = self.constants[offset + i];
                        value |= Natural::from(word) << (i * 64);
                    }
                    regs[op_index] = Integer::from(value);
                }
                OpCode::Load => {
                    let typ = &self.types[op.result_type];
                    let count = typ.coeffs.next_multiple_of(16) as u32;
                    let value = io.load(op.arena(), op.offset(), count)?;
                    regs[op_index] = value.into();
                }
                OpCode::Store => {
                    let typ = &self.types[op.result_type];
                    let count = typ.coeffs.next_multiple_of(16) as u32;
                    let value = &regs[op.b];
                    io.store(op.arena(), op.offset(), count, value.unsigned_abs_ref())?;
                }
                OpCode::Add => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs + rhs;
                }
                OpCode::Sub => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs - rhs;
                }
                OpCode::Mul => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs * rhs;
                }
                OpCode::Rem => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs % rhs;
                }
                OpCode::Quo => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs / rhs;
                }
                OpCode::Inv => {
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    let lhs = lhs.unsigned_abs_ref();
                    let rhs = rhs.unsigned_abs_ref();

                    *dst = lhs
                        .rem(rhs)
                        .mod_inverse(rhs)
                        .ok_or_else(|| anyhow!("divide by zero"))?
                        .into();
                }
            }
        }
        Ok(())
    }
}

fn operands_mut<'a>(
    op: &Op,
    op_index: usize,
    regs: &'a mut [Integer],
) -> (&'a Integer, &'a Integer, &'a mut Integer) {
    assert!(op.a < op_index);
    assert!(op.b < op_index);
    let (prefix, suffix) = regs.split_at_mut(op_index);

    let lhs = &prefix[op.a];
    let rhs = &prefix[op.b];

    let dst = &mut suffix[0];

    (lhs, rhs, dst)
}
