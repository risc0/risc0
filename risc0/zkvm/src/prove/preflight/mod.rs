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

//! Runs a rv32im execution in a riscv emulator in preparation for
//! evaluating the circuit.  Experimental.

use std::{
    collections::{BTreeMap, VecDeque},
    vec::Vec,
};

use anyhow::{anyhow, bail, Result};
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{ecall, reg_abi::*},
    WORD_SIZE,
};
use rrs_lib::{
    instruction_executor::InstructionExecutor,
    instruction_string_outputter::InstructionStringOutputter, process_instruction, HartState,
    MemAccessSize, Memory,
};

use crate::{
    prove::{io::SyscallContext, ProverOpts},
    sha::{DIGEST_BYTES, DIGEST_WORDS},
    MemoryImage,
};

mod opcode;
use opcode::{MajorType, OpCode};

fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}

// Information we need to generate for every preflight cycle.
#[allow(dead_code)]
struct Cycle {
    // Number of circuit cycles used by this preflight cycle.
    circuit_cycles: usize,

    // Program counter for the next cycle after this one
    new_pc: u32,
}

struct MemState {
    // Map from (address, cycle) to value for all memory writes
    history: BTreeMap<(u32, usize), u32>,

    // Current memory state
    ram: MemoryImage,

    // Current cycle number, in preflight cycles (one cycle per instruction).
    cur_cycle: usize,
}

#[allow(dead_code)]
struct SyscallHistory {
    out_data: VecDeque<u32>,
    out_regs: (u32, u32),
}

/// Tracks the state of a preflight execution
pub struct Preflight<'a> {
    // Current RAM state
    mem: MemState,

    // Prover options
    opts: ProverOpts<'a>,

    // Cycle information for each cycle we've executed
    cycles: Vec<Cycle>,

    // System call results, indexed by preflight cycle
    #[allow(dead_code)]
    syscalls: BTreeMap<usize, SyscallHistory>,

    // State that rsslib neads
    hart_state: HartState,

    halted: bool,
}

impl<'a> Preflight<'a> {
    /// Creates a new preflight from the given memory image
    pub fn new(entry: u32, mem_init: MemoryImage, opts: ProverOpts<'a>) -> Self {
        let mut hart_state = HartState::new();
        hart_state.pc = entry;
        Self {
            syscalls: BTreeMap::new(),
            mem: MemState::new(mem_init),
            cycles: Vec::new(),
            hart_state,
            halted: false,
            opts,
        }
    }

    /// Returns true if this run has called sys_halt
    pub fn is_halted(&self) -> bool {
        self.halted
    }

    /// Execute one instruction
    pub fn step(&mut self) -> Result<()> {
        assert!(!self.halted);
        let c = self.run_cycle()?;
        self.cycles.push(c);
        self.mem.cur_cycle = self.cycles.len();
        Ok(())
    }

    fn run_cycle(&mut self) -> Result<Cycle> {
        if self.halted {
            bail!("Halted");
        }
        let inst = self.mem.load_u32(self.hart_state.pc);
        let opcode = OpCode::decode(inst);

        if opcode.major == MajorType::ECall {
            let cycle = self.do_ecall()?;
            self.hart_state.pc = cycle.new_pc;
            return Ok(cycle);
        }
        if log::log_enabled!(log::Level::Trace) {
            let mut outputter = InstructionStringOutputter {
                insn_pc: self.hart_state.pc,
            };
            let desc = process_instruction(&mut outputter, inst);
            log::trace!(
                "pc=0x{:08x}: inst=0x{:08x} {}",
                outputter.insn_pc,
                inst,
                desc.as_ref().map(String::as_str).unwrap_or("(unknown)")
            );
        }
        InstructionExecutor {
            hart_state: &mut self.hart_state,
            mem: &mut self.mem,
        }
        .step()
        .map_err(|err| anyhow!("{:?}", err))?;

        let circuit_cycles = match opcode.mnemonic {
            "XORI" | "ORI" | "ANDI" | "SRLI" | "SRAI" | "XOR" | "OR" | "AND" | "DIV" | "DIVU"
            | "REM" | "REMU" | "SRL" | "SRA" => 2,
            _ => 1,
        };

        if let Some(reg) = self.hart_state.last_register_write {
            // This instruction updated a register; save it to the register section of our
            // RAM
            self.mem.store_register(reg, self.hart_state.registers[reg]);
        }

        Ok(Cycle {
            circuit_cycles,
            new_pc: self.hart_state.pc,
        })
    }

    fn do_ecall(&mut self) -> Result<Cycle> {
        let new_pc = self.hart_state.pc + WORD_SIZE as u32;
        match self.mem.load_register(REG_T0) {
            ecall::HALT => {
                self.halted = true;
                Ok(Cycle {
                    new_pc,
                    circuit_cycles: 1,
                })
            }
            ecall::OUTPUT => {
                // TODO
                Ok(Cycle {
                    new_pc,
                    circuit_cycles: 1,
                })
            }
            ecall::SHA => {
                let [out_state, in_state, mut block1_ptr, mut block2_ptr, count] =
                    [REG_A0, REG_A1, REG_A2, REG_A3, REG_A4].map(|reg| self.mem.load_register(reg));

                // Sha setup
                let mut circuit_cycles = 1;

                let in_state_vec = self.mem.load_region(in_state, DIGEST_BYTES as u32);
                let mut state: [u32; DIGEST_WORDS] =
                    bytemuck::cast_slice(&in_state_vec).try_into().unwrap();
                for word in &mut state {
                    *word = word.to_be();
                }

                log::debug!("Initial sha state: {state:08x?}");

                for _ in 0..count {
                    let mut block = [0u32; DIGEST_WORDS * 2];
                    for i in 0..DIGEST_WORDS {
                        block[i] = self.mem.load_u32(block1_ptr + (i * WORD_SIZE) as u32);
                        //.to_be();
                    }
                    for i in 0..DIGEST_WORDS {
                        block[DIGEST_WORDS + i] =
                            self.mem.load_u32(block2_ptr + (i * WORD_SIZE) as u32);
                        //.to_be();
                    }
                    log::debug!("Compressing block {block:02x?}");
                    sha2::compress256(
                        &mut state,
                        &[*generic_array::GenericArray::from_slice(
                            bytemuck::cast_slice(&block),
                        )],
                    );

                    circuit_cycles += 72;
                    block1_ptr += DIGEST_BYTES as u32 * 2;
                    block2_ptr += DIGEST_BYTES as u32 * 2;
                }
                log::debug!("Final sha state: {state:08x?}");

                for word in &mut state {
                    *word = u32::from_be(*word);
                }
                self.mem
                    .store_region(out_state, bytemuck::cast_slice(&state));

                Ok(Cycle {
                    new_pc,
                    circuit_cycles,
                })
            }
            ecall::SOFTWARE => {
                let to_guest_ptr = self.mem.load_register(REG_A0);
                let to_guest_words = self.mem.load_register(REG_A1);
                let name_ptr = self.mem.load_register(REG_A2);
                let syscall_name = self.mem.load_string(name_ptr)?;

                log::debug!(
                    "Guest called syscall {syscall_name} requesting {to_guest_words} words back"
                );

                // One cycle for the ecall cycle, then one for each chunk or
                // portion thereof then one to save output (a0, a1)
                let chunks = align_up(to_guest_words as usize, WORD_SIZE);
                let circuit_cycles = 1 + chunks + 1;

                let mut to_guest = vec![0u32; to_guest_words as usize];

                let (a0, a1): (u32, u32);

                if let Some(cb) = self.opts.syscall_handlers.get(&syscall_name) {
                    (a0, a1) = cb.syscall(&syscall_name, &self.mem, &mut to_guest)?;
                    self.mem
                        .store_region(to_guest_ptr, bytemuck::cast_slice(&to_guest));
                } else {
                    bail!("Unknown syscall {syscall_name}");
                }
                self.mem.store_register(REG_A0, a0);
                self.mem.store_register(REG_A1, a1);
                self.hart_state.registers[REG_A0] = a0;
                self.hart_state.registers[REG_A1] = a1;

                Ok(Cycle {
                    new_pc,
                    circuit_cycles,
                })
            }
            ecall => bail!("Unknown ecall {ecall:?}"),
        }
    }
}

impl MemState {
    fn new(ram: MemoryImage) -> Self {
        let history = ram
            .image
            .chunks(WORD_SIZE)
            .enumerate()
            .filter_map(|(addrword, bytes)| {
                let addr = addrword * WORD_SIZE;
                let val = u32::from_le_bytes(bytes.try_into().unwrap());
                if val == 0 {
                    None
                } else {
                    Some(((addr as u32, 0), val))
                }
            })
            .collect();
        MemState {
            ram,
            history,
            cur_cycle: 0,
        }
    }
}

// This is how we expose our RAM to rrs_lib.
impl Memory for MemState {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        match size {
            MemAccessSize::Byte => Some(self.load_u8(addr) as u32),
            MemAccessSize::HalfWord => {
                Some((self.load_u8(addr) as u32) + ((self.load_u8(addr + 1) as u32) << 8))
            }
            MemAccessSize::Word => Some(self.load_u32(addr)),
        }
    }

    fn write_mem(&mut self, addr: u32, size: MemAccessSize, store_data: u32) -> bool {
        let addr_word = addr & !(WORD_SIZE as u32 - 1);
        let mut word = self.load_u32(addr_word);
        match size {
            MemAccessSize::Byte => {
                let mut bytes = word.to_le_bytes();
                bytes[addr as usize & 0x3] = store_data as u8;
                word = u32::from_le_bytes(bytes);
            }
            MemAccessSize::HalfWord => match addr & 0x2 {
                0x0 => word = (word & !0xFFFF) | store_data,
                0x02 => word = (word & 0xFFFF) | (store_data << 16),
                _ => unreachable!(),
            },
            MemAccessSize::Word => word = store_data,
        };
        self.store_u32(addr_word, word);
        true
    }
}

impl SyscallContext for MemState {
    fn get_cycle(&self) -> usize {
        self.cur_cycle
    }

    fn load_u32(&self, addr: u32) -> u32 {
        u32::from_le_bytes(
            self.ram.image[addr as usize..addr as usize + WORD_SIZE]
                .try_into()
                .unwrap(),
        )
    }

    fn load_u8(&self, addr: u32) -> u8 {
        self.ram.image[addr as usize]
    }

    fn load_region(&self, addr: u32, len: u32) -> Vec<u8> {
        self.ram.image[addr as usize..(addr + len) as usize].to_vec()
    }
}

impl MemState {
    // Gets the most recent write for this address strictly before 'cycle', or 0.
    #[allow(dead_code)]
    fn get(&self, cycle: usize, addr: u32) -> u32 {
        let mut r = self.history.range((0, 0)..(addr, cycle));
        if let Some((&(saved_addr, saved_cycle), &saved_value)) = r.next_back() {
            if saved_addr == addr {
                assert!(saved_cycle < cycle);
                return saved_value;
            }
        }
        0
    }

    fn store_u32(&mut self, addr: u32, val: u32) {
        self.history.insert((addr, self.cur_cycle), val);
        self.ram.image[addr as usize..addr as usize + WORD_SIZE]
            .clone_from_slice(&val.to_le_bytes());
    }

    fn store_register(&mut self, reg: usize, val: u32) {
        self.store_u32((SYSTEM.start() + reg * WORD_SIZE) as u32, val)
    }

    fn store_region(&mut self, start: u32, data: &[u32]) {
        for (addr, word) in (start..start + (data.len() * WORD_SIZE) as u32)
            .step_by(WORD_SIZE)
            .zip(data.iter().copied())
        {
            self.store_u32(addr, word)
        }
    }
}

// These tests come from:
// https://github.com/riscv-software-src/riscv-tests
// They were built using the toolchain from:
// https://github.com/risc0/toolchain/releases/tag/2022.03.25
#[cfg(test)]
mod riscv_tests {
    use super::Preflight;
    macro_rules! test_case {
        ($func_name:ident) => {
            #[test_log::test]
            #[cfg_attr(feature = "cuda", serial_test::serial)]
            fn $func_name() {
                use std::io::Read;

                use flate2::read::GzDecoder;
                use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};
                use tar::Archive;
                use $crate::{MemoryImage, Program, ProverOpts};

                let bytes = include_bytes!("../../testdata/riscv-tests.tgz");
                let gz = GzDecoder::new(&bytes[..]);
                let mut tar = Archive::new(gz);
                for entry in tar.entries().unwrap() {
                    let mut entry = entry.unwrap();
                    if !entry.header().entry_type().is_file() {
                        continue;
                    }
                    let path = entry.path().unwrap();
                    let filename = path.file_name().unwrap().to_str().unwrap();
                    if filename != stringify!($func_name) {
                        continue;
                    }
                    let mut elf = Vec::new();
                    entry.read_to_end(&mut elf).unwrap();

                    let program = Program::load_elf(elf.as_slice(), MEM_SIZE as u32).unwrap();
                    let image = MemoryImage::new(&program, PAGE_SIZE as u32);

                    let mut preflight = Preflight::new(program.entry, image, ProverOpts::default());
                    while !preflight.is_halted() {
                        preflight.step().unwrap()
                    }
                }
            }
        };
    }

    test_case!(add);
    test_case!(addi);
    test_case!(and);
    test_case!(andi);
    test_case!(auipc);
    test_case!(beq);
    test_case!(bge);
    test_case!(bgeu);
    test_case!(blt);
    test_case!(bltu);
    test_case!(bne);
    test_case!(div);
    test_case!(divu);
    test_case!(jal);
    test_case!(jalr);
    test_case!(lb);
    test_case!(lbu);
    test_case!(lh);
    test_case!(lhu);
    test_case!(lui);
    test_case!(lw);
    test_case!(mul);
    test_case!(mulh);
    test_case!(mulhsu);
    test_case!(mulhu);
    test_case!(or);
    test_case!(ori);
    test_case!(rem);
    test_case!(remu);
    test_case!(sb);
    test_case!(sh);
    test_case!(simple);
    test_case!(sll);
    test_case!(slli);
    test_case!(slt);
    test_case!(slti);
    test_case!(sltiu);
    test_case!(sltu);
    test_case!(sra);
    test_case!(srai);
    test_case!(srl);
    test_case!(srli);
    test_case!(sub);
    test_case!(sw);
    test_case!(xor);
    test_case!(xori);
}
