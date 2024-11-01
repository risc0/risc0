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

use num_derive::FromPrimitive;

#[allow(dead_code)]
pub struct Type {
    pub coeffs: u64,
    pub max_pos: u64,
    pub max_neg: u64,
    pub min_bits: u64,
}

#[allow(dead_code)]
pub struct Input {
    pub label: u64,
    pub bit_width: u32,
    pub min_bits: u16,
    pub is_public: bool,
}

#[derive(FromPrimitive)]
pub enum OpCode {
    Eqz = 0x0,
    Def = 0x1,
    Con = 0x2,
    Add = 0x8,
    Sub = 0x9,
    Mul = 0xA,
    Rem = 0xB,
    Quo = 0xC,
    Inv = 0xE,
}

pub struct Op {
    pub code: OpCode,
    pub result_type: usize,
    pub operand_a: usize,
    pub operand_b: usize,
}

pub struct Program {
    pub inputs: Vec<Input>,
    pub types: Vec<Type>,
    pub constants: Vec<u64>,
    pub ops: Vec<Op>,
}
