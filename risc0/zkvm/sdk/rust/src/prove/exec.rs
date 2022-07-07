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

use std::collections::{BTreeMap, HashMap};

use log::debug;
use risc0_circuit_rv32im_legacy::CircuitImpl;
use risc0_zkp::{
    adapter::{CircuitDef, CustomStep},
    core::{fp::Fp, sha::DIGEST_WORDS},
    ZK_CYCLES,
};

use crate::platform::memory::MEM_BITS;

pub struct MachineState {
    memory: HashMap<u32, u32>,
}

impl CircuitDef<MachineState> for CircuitImpl {}

impl CustomStep for MachineState {
    fn call(&mut self, name: &str, extra: &str, args: &[Fp]) -> Vec<Fp> {
        match name {
            "divide32" => {
                let ((x0, x1), (x2, x3)) = self.divide32((args[0], args[1]), (args[2], args[3]));
                vec![x0, x1, x2, x3]
            }
            "log" => {
                self.log(extra, args);
                vec![]
            }
            "memCheck" => {
                let (x0, x1, x2, x3, x4) = self.mem_check();
                vec![x0, x1, x2, x3, x4]
            }
            "memRead" => {
                let (x0, x1) = self.mem_read(args[0], args[1]);
                vec![x0, x1]
            }
            "memWrite" => {
                self.mem_write(args[0], args[1], (args[2], args[3]));
                vec![]
            }
            _ => unreachable!(),
        }
    }
}

impl MachineState {
    pub fn new() -> Self {
        MachineState {
            memory: HashMap::new(),
        }
    }

    fn split_word(&self, value: u32) -> (Fp, Fp) {
        (Fp::new(value & 0xffff), Fp::new(value >> 16))
    }

    fn merge_word(&self, (low, high): (Fp, Fp)) -> u32 {
        let low: u32 = low.into();
        let high: u32 = high.into();
        low | high << 16
    }

    fn divide32(&self, numer: (Fp, Fp), denom: (Fp, Fp)) -> ((Fp, Fp), (Fp, Fp)) {
        let numer = self.merge_word(numer);
        let denom = self.merge_word(denom);
        let (quot, rem) = if denom == 0 {
            (0xffffffff, numer)
        } else {
            (numer / denom, numer % denom)
        };
        (self.split_word(quot), self.split_word(rem))
    }

    fn log(&self, msg: &str, _args: &[Fp]) {
        debug!("{}", msg);
    }

    fn mem_check(&self) -> (Fp, Fp, Fp, Fp, Fp) {
        todo!()
    }

    fn mem_read(&self, cycle: Fp, addr: Fp) -> (Fp, Fp) {
        debug!("[{}] R: 0x{:08X}", u32::from(cycle), u32::from(addr));
        let value = self.memory[&addr.into()];
        self.split_word(value)
    }

    fn mem_write(&mut self, cycle: Fp, addr: Fp, value: (Fp, Fp)) {
        let word = self.merge_word(value);
        debug!(
            "[{}] W: 0x{:08X} <= 0x{:08X}",
            u32::from(cycle),
            u32::from(addr),
            word
        );
        self.memory.insert(addr.into(), word);
    }
}

enum CodeCycleKind {
    Normal,
    Final,
    Init,
    MemWrite,
    Reset,
    Fini,
    NumKinds,
}

enum DataCycleKind {
    Decode,
    Compute0,
    Compute1,
    Compute2,
    Compute3,
    Multiply,
    Divide,
    Final,
    ShaSync,
    ShaControl,
    ShaData,
    Halt,
    NumKinds,
}

enum ShaCycleKind {
    Control,
    Load,
    Mix,
    NumKinds,
}

const SHA_INIT: [u32; DIGEST_WORDS] = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
];

const SHA_ROUND: [u32; 64] = [
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
];

fn cond(expr: bool) -> Fp {
    Fp::new(if expr { 1 } else { 0 })
}

pub fn setup_code(code: &mut [Fp], steps: usize, start_addr: u32, image: &BTreeMap<u32, u32>) {
    const CYCLE_POS: usize = 0;
    const TYPE_POS: usize = CYCLE_POS + 1;
    const SHA_POS: usize = TYPE_POS + CodeCycleKind::NumKinds as usize;
    const P1_POS: usize = SHA_POS + ShaCycleKind::NumKinds as usize;
    const P2_POS: usize = P1_POS + 1;
    const DATA_POS: usize = P2_POS + 1;
    const DATA2_POS: usize = DATA_POS + 2;
    const PROLOG_SIZE: usize = 3; // INIT + RESET + FINI
    const ONE: Fp = Fp::new(1);

    if image.len() + PROLOG_SIZE + ZK_CYCLES > steps {
        panic!(); //TODO
    }

    for i in 0..steps {
        code[i] = Fp::new(i as u32);
    }

    code[(TYPE_POS + CodeCycleKind::Init as usize) * steps] = ONE;
    for (cycle, (addr, word)) in image.iter().enumerate() {
        let cycle = cycle + 1;
        code[(TYPE_POS + CodeCycleKind::MemWrite as usize) * steps + cycle] = ONE;
        code[P1_POS * steps + cycle] = Fp::new(addr / 4);
        code[P2_POS * steps + cycle] = cond(addr / 4 >= (1 << (MEM_BITS - 1)));
        code[(DATA_POS + 0) * steps + cycle] = Fp::new(word & 0xffff);
        code[(DATA_POS + 1) * steps + cycle] = Fp::new(word >> 16);
    }

    let mut cycle = image.len() + 1;
    code[(TYPE_POS + CodeCycleKind::Reset as usize) * steps + cycle] = ONE;
    code[P1_POS * steps + cycle] = Fp::new(start_addr);
    cycle += 1;
    let base_cycle = cycle;
    while cycle + 1 + ZK_CYCLES < steps {
        let inst_phase = (cycle - base_cycle) % 3;
        let sha_phase = (cycle - base_cycle) % 72;
        if inst_phase == 2 {
            code[(TYPE_POS + CodeCycleKind::Final as usize) * steps + cycle] = ONE;
        } else {
            code[(TYPE_POS + CodeCycleKind::Normal as usize) * steps + cycle] = ONE;
        }
        if sha_phase < 4 {
            code[(SHA_POS + ShaCycleKind::Control as usize) * steps + cycle] = ONE;
            code[P1_POS * steps + cycle] = Fp::new(sha_phase as u32);
            code[P2_POS * steps + cycle] = cond(sha_phase == 0);
            let init1 = SHA_INIT[3 - sha_phase];
            code[(DATA_POS + 0) * steps + cycle] = Fp::new(init1 & 0xffff);
            code[(DATA_POS + 1) * steps + cycle] = Fp::new(init1 >> 16);
            let init2 = SHA_INIT[7 - sha_phase];
            code[(DATA2_POS + 0) * steps + cycle] = Fp::new(init2 & 0xffff);
            code[(DATA2_POS + 1) * steps + cycle] = Fp::new(init2 >> 16);
        } else if sha_phase < 20 {
            code[(SHA_POS + ShaCycleKind::Load as usize) * steps + cycle] = ONE;
            let round = SHA_ROUND[sha_phase - 4];
            code[(DATA_POS + 0) * steps + cycle] = Fp::new(round & 0xffff);
            code[(DATA_POS + 1) * steps + cycle] = Fp::new(round >> 16);
        } else if sha_phase < 68 {
            code[(SHA_POS + ShaCycleKind::Mix as usize) * steps + cycle] = ONE;
            code[P1_POS * steps + cycle] = cond(sha_phase >= 64);
            code[P2_POS * steps + cycle] = cond(sha_phase == 67);
            let round = SHA_ROUND[sha_phase - 4];
            code[(DATA_POS + 0) * steps + cycle] = Fp::new(round & 0xffff);
            code[(DATA_POS + 1) * steps + cycle] = Fp::new(round >> 16);
        } else {
            code[(SHA_POS + ShaCycleKind::Control as usize) * steps + cycle] = ONE;
            code[P1_POS * steps + cycle] = Fp::new((sha_phase - 64 + 4) as u32);
        }
        cycle += 1;
    }
    code[(TYPE_POS + CodeCycleKind::Fini as usize) * steps + cycle] = ONE;
}

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;

    use log::debug;
    use risc0_circuit_rv32im_legacy::CircuitImpl;
    use risc0_zkp::{
        adapter::{CircuitInfo, CircuitStepContext, CircuitStepExec},
        core::fp::Fp,
    };

    use crate::{CODE_SIZE, DATA_SIZE};

    use super::{setup_code, MachineState};

    fn init() {
        let _ = env_logger::builder().is_test(true).try_init();
    }

    const PROGRAM_START: u32 = 0x0200_0000;

    #[test]
    fn execute() {
        init();

        let steps = 256;
        let circuit = CircuitImpl::new();
        let mut machine = MachineState::new();
        machine.memory.insert(0, 0);

        let mut output = vec![Fp::new(0); circuit.output_size()];
        let mut code = vec![Fp::new(0); CODE_SIZE * steps];
        let mut data = vec![Fp::new(0); DATA_SIZE * steps];

        // Make an elf with a single ecall instruction
        let mut elf = BTreeMap::new();
        elf.insert(PROGRAM_START, 0x00000073);
        setup_code(&mut code, steps, PROGRAM_START, &elf);

        let args: &mut [&mut [Fp]] = &mut [&mut code, &mut output, &mut data, &mut [], &mut []];

        for cycle in 0..10 {
            debug!("cycle: {cycle}");
            circuit.step_exec(
                &CircuitStepContext { size: steps, cycle },
                &mut machine,
                args,
            );
        }
    }
}
