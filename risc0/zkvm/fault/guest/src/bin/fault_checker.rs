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

use risc0_zkvm::{guest::env, MiniMonitor};
use rrs_lib::{instruction_executor::InstructionExecutor, HartState};

pub fn main() {
    let mut mini_monitor: MiniMonitor = env::read();
    let regs = mini_monitor.registers;
    let pc = mini_monitor.pc;

    let mut instruction_executor = InstructionExecutor {
        mem: &mut mini_monitor,
        hart_state: &mut HartState {
            registers: regs,
            pc: pc,
            last_register_write: None,
        },
    };
    instruction_executor.step().expect_err(
        "fault checker expected instruction at 0x{pc:08x} to fail. Actual execution was successful",
    );
}
