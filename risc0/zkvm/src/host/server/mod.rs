// Copyright 2023 RISC Zero, Inc.
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

pub(crate) mod exec;
pub(crate) mod prove;
pub(crate) mod session;
#[cfg(test)]
mod testutils;

use risc0_circuit_rv32im::prove::vm::opcode::OpCode;
use rrs_lib::{instruction_string_outputter::InstructionStringOutputter, process_instruction};

fn opcode_str(opcode: &OpCode) -> String {
    let mut outputter = InstructionStringOutputter {
        insn_pc: opcode.insn_pc,
    };
    let desc = process_instruction(&mut outputter, opcode.insn);
    format!("{}", desc.unwrap_or(opcode.mnemonic.into()))
}
