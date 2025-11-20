// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{io::Read, ops::Rem};

use anyhow::{Result, anyhow};
use byteorder::{LittleEndian, ReadBytesExt};
use malachite::{
    Integer, Natural,
    base::num::{
        arithmetic::traits::{DivRem, ModInverse},
        basic::traits::Zero,
    },
};
use num_derive::FromPrimitive;
use num_traits::FromPrimitive;

// NOTE: Fields in Type and Input are currently unused, but are read to consume the associated
// bytes from the stream when decoding the program.

#[derive(Debug)]
pub(crate) struct Type {
    /// Number of byte-limbs (i.e. coefficients) in the number associated with this type.
    pub coeffs: u64,
    #[expect(dead_code)]
    max_pos: u64,
    #[expect(dead_code)]
    max_neg: u64,
    #[expect(dead_code)]
    min_bits: u64,
}

#[derive(Debug)]
pub(crate) struct Input {
    #[expect(dead_code)]
    label: u64,
    #[expect(dead_code)]
    bit_width: u32,
    #[expect(dead_code)]
    min_bits: u16,
    #[expect(dead_code)]
    is_public: bool,
}

#[derive(Debug, FromPrimitive)]
pub(crate) enum OpCode {
    Const = 0x2, // unary: constant index
    Load = 0x3,  // unary: constant index
    Store = 0x4, // unary: constant index
    Norm = 0x5,  // unary: bigint
    Add = 0x8,   // binary: bigint, bigint
    Sub = 0x9,   // binary: bigint, bigint
    Mul = 0xA,   // binary: bigint, bigint
    Rem = 0xB,   // binary: bigint, bigint
    Quo = 0xC,   // binary: bigint, bigint
    Inv = 0xE,   // binary: bigint, bigint
    Div = 0xF,   // binary: bigint, bigint
}

#[derive(Debug)]
pub(crate) struct Op {
    /// 4-bit opcode enum.
    pub code: OpCode,
    /// 12-bit index into [Program::types]  to access the [Type] for the result.
    pub result_type: usize,
    /// 24-bit field `a` of the op. Semantics are operation-specific.
    ///
    /// In the arithmatic ops, a is the index into the list of op results for the lhs.
    pub a: usize,
    /// 24-bit field `b` of the op. Semantics are operation-specific.
    ///
    /// In the arithmatic ops, b is the index into the list of op results for the rhs.
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
            label: stream.read_u64::<LittleEndian>()?,
            bit_width: stream.read_u32::<LittleEndian>()?,
            min_bits: stream.read_u16::<LittleEndian>()?,
            is_public: stream.read_u16::<LittleEndian>()? != 0,
        })
    }
}

impl Type {
    pub fn decode<R: Read>(stream: &mut R) -> Result<Self> {
        Ok(Self {
            coeffs: stream.read_u64::<LittleEndian>()?,
            max_pos: stream.read_u64::<LittleEndian>()?,
            max_neg: stream.read_u64::<LittleEndian>()?,
            min_bits: stream.read_u64::<LittleEndian>()?,
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
        // DO NOT MERGE
        #[inline(always)]
        fn print_op(name: &str) {
            if option_env!("BIGINT2_DEBUG").is_some() {
                eprintln!("bigint2::eval {name}");
            }
        }

        let mut regs = vec![Integer::ZERO; self.ops.len()];
        let mut op_index = 0;
        for op in self.ops.iter() {
            tracing::trace!("[{op_index}]: {op:?}");
            match op.code {
                OpCode::Const => {
                    print_op("const");
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
                    print_op("load");
                    let typ = &self.types[op.result_type];
                    let count = typ.coeffs.next_multiple_of(16) as u32;
                    let value = io.load(op.arena(), op.offset(), count)?;
                    regs[op_index] = value.into();
                }
                OpCode::Store => {
                    print_op("store");
                    let typ = &self.types[op.result_type];
                    let count = typ.coeffs.next_multiple_of(16) as u32;
                    let value = &regs[op.b];
                    io.store(op.arena(), op.offset(), count, value.unsigned_abs_ref())?;
                }
                OpCode::Add => {
                    print_op("add");
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs + rhs;
                }
                OpCode::Norm => {
                    print_op("norm");
                    let (val, _, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = val.clone();
                }
                OpCode::Sub => {
                    print_op("sub");
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs - rhs;
                }
                OpCode::Mul => {
                    print_op("mul");
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs * rhs;
                }
                OpCode::Rem => {
                    print_op("rem");
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs % rhs;
                }
                OpCode::Quo => {
                    print_op("quo");
                    let (lhs, rhs, dst) = operands_mut(op, op_index, &mut regs);
                    *dst = lhs / rhs;
                }
                OpCode::Div => {
                    print_op("div");
                    let (lhs, rhs, quo, rem) = operands_mut_div(op, op_index, &mut regs);
                    (*quo, *rem) = lhs.div_rem(rhs);
                    op_index += 1;
                }
                OpCode::Inv => {
                    print_op("inv");
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

            op_index += 1;
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

fn operands_mut_div<'a>(
    op: &Op,
    op_index: usize,
    regs: &'a mut [Integer],
) -> (&'a Integer, &'a Integer, &'a mut Integer, &'a mut Integer) {
    assert!(op.a < op_index);
    assert!(op.b < op_index);
    let (prefix, suffix) = regs.split_at_mut(op_index);

    let lhs = &prefix[op.a];
    let rhs = &prefix[op.b];

    let (a, b) = suffix.split_at_mut(1);
    let quo = &mut a[0];
    let rem = &mut b[0];

    (lhs, rhs, quo, rem)
}
