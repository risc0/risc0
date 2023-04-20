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

use std::collections::{BTreeMap, BTreeSet, VecDeque};

use anyhow::{anyhow, Result};
use lazy_regex::{regex, Captures};
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem as Elem},
    Elem as _,
};
use risc0_zkp::adapter::CircuitStepHandler;
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{
        ecall, halt,
        reg_abi::{REG_A0, REG_T0},
    },
    WORD_SIZE,
};

use super::plonk;
use crate::{
    binfmt::image::MemoryImage,
    opcode::{MajorType, OpCode},
    session::PageFaults,
    ExitCode, Segment,
};

#[allow(dead_code)]
#[derive(Debug)]
enum MemoryOp {
    PageIo,
    Read,
    Write,
}

impl MemoryOp {
    fn as_u32(self) -> u32 {
        self as u32
    }
}

pub struct MemoryState {
    pub ram: MemoryImage,

    // Plonk tables for sorting plonks in proper order
    pub ram_plonk: plonk::RamPlonk,
    pub bytes_plonk: plonk::BytesPlonk,

    // Plonk accumulations for compute_accum and verify_accum phases
    pub plonk_accum: BTreeMap<String, plonk::PlonkAccum<BabyBear>>,
}

impl MemoryState {
    pub(crate) fn new(image: MemoryImage) -> Self {
        Self {
            ram: image,
            ram_plonk: plonk::RamPlonk::new(),
            bytes_plonk: plonk::BytesPlonk::new(),
            plonk_accum: BTreeMap::new(),
        }
    }

    #[track_caller]
    fn load_u8(&self, addr: u32) -> u8 {
        // log::debug!("load_u8: 0x{addr:08X}");
        self.ram.buf[addr as usize]
    }

    #[track_caller]
    fn load_u32(&self, addr: u32) -> u32 {
        // log::debug!("load_u32: 0x{addr:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        let mut bytes = [0u8; WORD_SIZE];
        for i in 0..WORD_SIZE {
            bytes[i] = self.load_u8(addr + i as u32);
        }
        u32::from_le_bytes(bytes)
    }

    fn load_register(&self, idx: usize) -> u32 {
        self.load_u32(get_register_addr(idx))
    }

    #[track_caller]
    fn store_u8(&mut self, addr: u32, value: u8) {
        // log::debug!("store_u8: 0x{addr:08X} <= 0x{value:08X}");
        self.ram.buf[addr as usize] = value;
    }

    #[track_caller]
    fn store_region(&mut self, addr: u32, slice: &[u8]) {
        // log::trace!("store_region: 0x{addr:08X} <= {} bytes", slice.len());
        for i in 0..slice.len() {
            self.store_u8(addr + i as u32, slice[i]);
        }
    }

    #[track_caller]
    fn store_u32(&mut self, addr: u32, value: u32) {
        // log::debug!("store_u32: 0x{addr:08X} <= 0x{value:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        self.store_region(addr, &value.to_le_bytes());
    }
}

fn get_register_addr(idx: usize) -> u32 {
    (SYSTEM.start() + idx * WORD_SIZE) as u32
}

fn split_word8(value: u32) -> (Elem, Elem, Elem, Elem) {
    (
        Elem::new(value & 0xff),
        Elem::new(value >> 8 & 0xff),
        Elem::new(value >> 16 & 0xff),
        Elem::new(value >> 24 & 0xff),
    )
}

fn merge_word8((x0, x1, x2, x3): (Elem, Elem, Elem, Elem)) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    let x2: u32 = x2.into();
    let x3: u32 = x3.into();
    x0 | x1 << 8 | x2 << 16 | x3 << 24
}

pub struct MachineContext {
    memory: MemoryState,
    faults: PageFaults,
    syscall_out_data: VecDeque<u32>,
    syscall_out_regs: VecDeque<(u32, u32)>,

    is_halted: bool,

    // When the machine is in a flushing state, no new dirty pages will be recorded and the
    // next dirty page will be reported in a 'pageInfo' extern.
    is_flushing: bool,

    // This is just for diagnostics: tracks which words have been paged in.
    resident_words: BTreeSet<u32>,

    exit_code: ExitCode,

    insn_counter: u32,
}

impl CircuitStepHandler<Elem> for MachineContext {
    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[Elem],
        outs: &mut [Elem],
    ) -> Result<()> {
        match name {
            "halt" => {
                self.halt(cycle, args[0], args[1]);
                Ok(())
            }
            "trace" => Ok(()),
            "getMajor" => {
                outs[0] = self.get_major(args[0], args[1])?;
                Ok(())
            }
            "getMinor" => {
                let insn = merge_word8((args[0], args[1], args[2], args[3]));
                let opcode = OpCode::decode(insn, 0)?;
                outs[0] = opcode.minor.into();
                Ok(())
            }
            "divide" => {
                (
                    (outs[0], outs[1], outs[2], outs[3]),
                    (outs[4], outs[5], outs[6], outs[7]),
                ) = self.divide(
                    (args[0], args[1], args[2], args[3]),
                    (args[4], args[5], args[6], args[7]),
                    args[8],
                );
                Ok(())
            }
            "pageInfo" => {
                (outs[0], outs[1], outs[2]) = self.page_info(args[0]);
                Ok(())
            }
            "ramWrite" => {
                self.ram_write(args[0], (args[1], args[2], args[3], args[4]), args[5])?;
                Ok(())
            }
            "ramRead" => {
                (outs[0], outs[1], outs[2], outs[3]) = self.ram_read(cycle, args[0], args[1]);
                Ok(())
            }
            "plonkWrite" => {
                self.plonk_write(extra, args);
                Ok(())
            }
            "plonkRead" => {
                self.plonk_read(extra, outs);
                Ok(())
            }
            "plonkWriteAccum" => {
                self.plonk_write_accum(extra, args);
                Ok(())
            }
            "plonkReadAccum" => {
                self.plonk_read_accum(extra, outs);
                Ok(())
            }
            "log" => {
                self.log(extra, args);
                Ok(())
            }
            "syscallInit" => Ok(()),
            "syscallBody" => {
                (outs[0], outs[1], outs[2], outs[3]) = split_word8(self.syscall_body()?);
                Ok(())
            }
            "syscallFini" => {
                let (a0, a1) = self.syscall_fini()?;
                (outs[0], outs[1], outs[2], outs[3]) = split_word8(a0);
                (outs[4], outs[5], outs[6], outs[7]) = split_word8(a1);
                Ok(())
            }
            _ => unimplemented!("Unsupported extern: {name}"),
        }
    }

    #[tracing::instrument(skip(self))]
    fn sort(&mut self, _: &str) {
        self.memory.ram_plonk.sort();
        self.memory.bytes_plonk.sort();
    }

    #[tracing::instrument(skip(self))]
    fn calc_prefix_products(&mut self) {
        for accum in &mut self.memory.plonk_accum {
            accum.1.calc_prefix_products()
        }
    }
}

impl MachineContext {
    pub fn new(segment: &Segment) -> Self {
        let syscall_out_data: Vec<u32> = segment
            .syscalls
            .iter()
            .flat_map(|syscall| syscall.to_guest.clone())
            .collect();
        let syscall_out_regs: Vec<(u32, u32)> = segment
            .syscalls
            .iter()
            .map(|syscall| syscall.regs)
            .collect();
        MachineContext {
            memory: MemoryState::new(segment.pre_image.clone()),
            faults: segment.faults.clone(),
            syscall_out_data: VecDeque::from(syscall_out_data),
            syscall_out_regs: VecDeque::from(syscall_out_regs),
            is_halted: false,
            is_flushing: false,
            resident_words: BTreeSet::new(),
            exit_code: segment.exit_code,
            insn_counter: 0,
        }
    }

    fn halt(&mut self, cycle: usize, exit_code: Elem, pc: Elem) {
        if !self.is_halted {
            let exit_code = exit_code.into();
            let pc: u32 = pc.into();
            match exit_code {
                halt::TERMINATE => {
                    log::debug!("HALT[{cycle}]> pc: 0x{pc:08x}");
                }
                halt::PAUSE => {
                    log::debug!("PAUSE[{cycle}]> pc: 0x{pc:08x}");
                    self.is_flushing = true;
                }
                halt::SPLIT => {
                    log::debug!("SPLIT[{cycle}]> pc: 0x{pc:08x}");
                }
                _ => unimplemented!("Unsupported exit_code: {exit_code}"),
            }
            self.is_halted = true;
        }
    }

    fn get_major(&mut self, cycle: Elem, pc: Elem) -> Result<Elem> {
        let cycle: u32 = cycle.into();
        let pc: u32 = pc.into();
        let insn = self.memory.load_u32(pc);
        let opcode = OpCode::decode(insn, pc)?;

        if opcode.major == MajorType::ECall {
            let minor = self.memory.load_register(REG_T0);
            if minor == ecall::HALT {
                let mode = self.memory.load_register(REG_A0);
                if mode == halt::PAUSE {
                    self.is_flushing = true;
                }
            }
        }

        if let ExitCode::SystemSplit(split_insn) = self.exit_code {
            if self.insn_counter == split_insn {
                if !self.is_flushing {
                    log::debug!("FLUSH[{}]> pc: 0x{pc:08x}", self.insn_counter);
                    self.is_flushing = true;
                }
            }
        }

        if !self.faults.reads.is_empty() {
            return Ok(MajorType::PageFault.as_u32().into());
        }

        if self.is_flushing {
            return Ok(MajorType::PageFault.as_u32().into());
        }

        log::debug!(
            "[{}] pc: 0x{:08x}, insn: 0x{:08x} => {:?}",
            cycle,
            pc,
            insn,
            opcode
        );
        self.insn_counter += 1;

        Ok(opcode.major.as_u32().into())
    }

    fn page_info(&mut self, _pc: Elem) -> (Elem, Elem, Elem) {
        if let Some(page_idx) = self.faults.reads.pop_last() {
            return (Elem::ONE, page_idx.into(), Elem::ZERO);
        }

        if self.is_flushing {
            if let Some(page_idx) = self.faults.writes.pop_first() {
                log::debug!("page_write: 0x{page_idx:08x}");
                return (Elem::ZERO, page_idx.into(), Elem::ZERO);
            }
        }

        (Elem::ZERO, Elem::ZERO, Elem::ONE)
    }

    fn divide(
        &self,
        numer: (Elem, Elem, Elem, Elem),
        denom: (Elem, Elem, Elem, Elem),
        sign: Elem,
    ) -> ((Elem, Elem, Elem, Elem), (Elem, Elem, Elem, Elem)) {
        let mut numer = merge_word8(numer) as u32;
        let mut denom = merge_word8(denom) as u32;
        let sign: u32 = sign.into();
        // log::debug!("divide: [{sign}] {numer} / {denom}");
        let ones_comp = (sign == 2) as u32;
        let neg_numer = sign != 0 && (numer as i32) < 0;
        let neg_denom = sign == 1 && (denom as i32) < 0;
        if neg_numer {
            numer = (!numer).overflowing_add(1 - ones_comp).0;
        }
        if neg_denom {
            denom = (!denom).overflowing_add(1 - ones_comp).0;
        }
        let (mut quot, mut rem) = if denom == 0 {
            (0xffffffff, numer)
        } else {
            (numer / denom, numer % denom)
        };
        let quot_neg_out =
            (neg_numer as u32 ^ neg_denom as u32) - ((denom == 0) as u32 * neg_numer as u32);
        if quot_neg_out != 0 {
            quot = (!quot).overflowing_add(1 - ones_comp).0;
        }
        if neg_numer {
            rem = (!rem).overflowing_add(1 - ones_comp).0;
        }
        // log::debug!("  quot: {quot}, rem: {rem}");
        (split_word8(quot), split_word8(rem))
    }

    fn log(&mut self, msg: &str, args: &[Elem]) {
        if log::max_level() < log::LevelFilter::Trace {
            // Don't bother to format it if we're not even logging.
            return;
        }

        // "msg" is given to us in C++-style formatting, so interpret it.
        let re = regex!("%([0-9]*)([xudw%])");
        let mut args_left = args;
        let mut next_arg = || {
            if args_left.is_empty() {
                panic!("Log arg mismatch, msg {msg}");
            }
            let arg: u32 = args_left[0].into();
            args_left = &args_left[1..];
            arg
        };
        let formatted = re.replace_all(msg, |captures: &Captures| {
            let width = captures
                .get(1)
                .map_or(0, |x| x.as_str().parse::<usize>().unwrap_or(0));
            let format = captures.get(2).map_or("", |x| x.as_str());
            match format {
                "u" => format!("{:width$}", next_arg()),
                "x" => {
                    let width = width.saturating_sub(2);
                    format!("0x{:0width$x}", next_arg())
                }
                "d" => format!("{:width$}", next_arg() as i32),
                "%" => format!("%"),
                "w" => {
                    let nexts = [next_arg(), next_arg(), next_arg(), next_arg()];
                    if nexts.iter().all(|v| *v <= 255) {
                        format!(
                            "0x{:08X}",
                            nexts[0] | (nexts[1] << 8) | (nexts[2] << 16) | (nexts[3] << 24)
                        )
                    } else {
                        format!(
                            "0x{:X}, 0x{:X}, 0x{:X}, 0x{:X}",
                            nexts[0], nexts[1], nexts[2], nexts[3]
                        )
                    }
                }
                _ => panic!("Unhandled printf format specification '{format}'"),
            }
        });
        assert_eq!(
            args_left.len(),
            0,
            "Args missing formatting: {:?} in {msg}",
            args_left
        );
        log::trace!("{}", formatted);
    }

    fn ram_read(&mut self, cycle: usize, addr: Elem, op: Elem) -> (Elem, Elem, Elem, Elem) {
        let addr: u32 = addr.into();
        let op: u32 = op.into();
        let info = &self.memory.ram.info;
        if op == MemoryOp::PageIo.as_u32() {
            self.resident_words.insert(addr);
        } else {
            if !self.resident_words.contains(&addr) {
                let addr = addr * WORD_SIZE as u32;
                let page_idx = info.get_page_index(addr);
                let entry_addr = info.get_page_entry_addr(page_idx);
                log::debug!("[{cycle}] ram_read: 0x{addr:08x}, op: {op:?}, entry_addr: 0x{entry_addr:08x}, page_idx: {page_idx}");
                panic!("Memory read before page in: 0x{addr:08x}");
            }
        }
        let addr = addr * WORD_SIZE as u32;
        let word = self.memory.load_u32(addr);
        // log::debug!("ram_read: 0x{addr:08X} -> 0x{word:08X}");
        split_word8(word)
    }

    fn ram_write(&mut self, addr: Elem, data: (Elem, Elem, Elem, Elem), op: Elem) -> Result<()> {
        let addr: u32 = addr.into();
        let op: u32 = op.into();
        if op == MemoryOp::PageIo.as_u32() {
            self.resident_words.insert(addr);
        } else {
            assert!(
                self.resident_words.contains(&addr),
                "Memory write before page in: 0x{addr:08x}"
            );
        }

        let data = merge_word8(data);
        let addr = addr * WORD_SIZE as u32;
        // log::debug!("ram_write> 0x{:08X} <= 0x{:08X}", addr, data);
        self.memory.store_u32(addr, data);

        Ok(())
    }

    fn plonk_read(&mut self, name: &str, outs: &mut [Elem]) {
        match name {
            "ram" => self.memory.ram_plonk.read(outs.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.read(outs.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_write(&mut self, name: &str, args: &[Elem]) {
        match name {
            "ram" => self.memory.ram_plonk.write(args.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.write(args.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_read_accum(&mut self, name: &str, outs: &mut [Elem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.read(outs)
        } else {
            panic!("Unknown plonk accum {}", name);
        }
    }

    fn plonk_write_accum(&mut self, name: &str, args: &[Elem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.write(args);
        } else {
            let mut accum = plonk::PlonkAccum::new();
            accum.write(args);
            self.memory.plonk_accum.insert(name.to_string(), accum);
        }
    }

    fn syscall_body(&mut self) -> Result<u32> {
        Ok(self.syscall_out_data.pop_front().unwrap_or_default())
    }

    fn syscall_fini(&mut self) -> Result<(u32, u32)> {
        let syscall_out_regs = self
            .syscall_out_regs
            .pop_front()
            .ok_or(anyhow!("Invalid syscall records"))?;
        log::debug!("syscall_fini: {:?}", syscall_out_regs);
        Ok(syscall_out_regs)
    }
}
