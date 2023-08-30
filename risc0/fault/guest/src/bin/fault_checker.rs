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

use risc0_zkvm::{guest::env, FaultCheckMonitor};
use rrs_lib::{instruction_executor::InstructionExecutor, HartState};

pub fn main() {
    let fault_monitor: FaultCheckMonitor = env::read();

    let mut instruction_executor = InstructionExecutor {
        mem: &mut fault_monitor.clone(),
        hart_state: &mut HartState {
            registers: fault_monitor.regs,
            pc: fault_monitor.pc,
            last_register_write: None,
        },
    };
    instruction_executor.step().expect_err(
        "fault checker expected instruction at 0x{pc:08x} to fail. Actual execution was successful",
    );
    env::commit(&fault_monitor.post_id);
}
