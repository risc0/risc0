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

use super::bibc;
use bibc::OpCode;
use bibc::Program;
use num_bigint::BigUint;

#[derive(Default)]
pub struct Witness {
    pub constant: Vec<BigUint>,
    pub public: Vec<BigUint>,
    pub private: Vec<BigUint>,
}

fn operands<'p>(op: &bibc::Op, op_index: usize, regs: &'p [BigUint]) -> (&'p BigUint, &'p BigUint) {
    assert!(op.operand_a < op_index);
    assert!(op.operand_b < op_index);
    (&regs[op.operand_a], &regs[op.operand_b])
}

fn operand_a<'p>(op: &bibc::Op, op_index: usize, regs: &'p [BigUint]) -> &'p BigUint {
    assert!(op.operand_a < op_index);
    &regs[op.operand_a]
}

pub fn eval(in_func: &Program, inputs: &[BigUint]) -> Witness {
    let mut wit: Witness = Default::default();
    let mut regs = vec![BigUint::ZERO; in_func.ops.len()];
    for op_index in 0..in_func.ops.len() {
        let op = &in_func.ops[op_index];
        match op.code {
            OpCode::Eqz => {
                let value = operand_a(op, op_index, &regs);
                assert_eq!(*value, BigUint::ZERO, "failed zero check");
                wit.private.push(value.clone());
            }
            OpCode::Def => {
                let wire = &in_func.inputs[op.operand_a];
                let value = &inputs[wire.label as usize];
                regs[op_index] = value.clone();
                if wire.is_public {
                    &mut wit.public
                } else {
                    &mut wit.private
                }
                .push(value.clone());
            }
            OpCode::Con => {
                let offset = op.operand_a;
                let words = op.operand_b;
                let mut value = BigUint::from(0_u64);
                for i in 0..words {
                    let word: u64 = in_func.constants[offset + i];
                    let mut tmp = BigUint::from(word);
                    tmp <<= i * 64;
                    value |= &tmp;
                }
                regs[op_index] = value.clone();
                wit.constant.push(value);
            }
            OpCode::Add => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                regs[op_index] = lhs + rhs;
            }
            OpCode::Sub => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                regs[op_index] = lhs - rhs;
            }
            OpCode::Mul => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                regs[op_index] = lhs * rhs;
            }
            OpCode::Rem => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                let value = lhs % rhs;
                regs[op_index] = value.clone();
                wit.private.push(value);
            }
            OpCode::Quo => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                let value = lhs / rhs;
                regs[op_index] = value.clone();
                wit.private.push(value);
            }
            OpCode::Inv => {
                let (lhs, rhs) = operands(op, op_index, &regs);
                let exp = rhs.clone() - 2u8;
                let value = lhs.modpow(&exp, rhs);
                regs[op_index] = value.clone();
                wit.private.push(value);
            }
        }
    }
    wit
}
