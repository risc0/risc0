// Copyright 2022 RISC Zero, Inc.
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

use std::collections::BTreeMap;

use anyhow::{bail, Result};
use bytemuck::Pod;
use lazy_regex::{regex, Captures};
use log::{debug, trace};
use risc0_circuit_rv32im::CircuitImpl;
use risc0_zkp::{
    adapter::{CircuitStepHandler, PolyExt},
    core::log2_ceil,
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem,
    },
    prove::executor::Executor,
    MAX_CYCLES_PO2, ZK_CYCLES,
};
use risc0_zkvm_platform::{
    memory::{FFPU, SYSTEM},
    syscall::{
        nr::{SYS_COMMIT, SYS_COMPUTE_POLY, SYS_CYCLE_COUNT, SYS_IO, SYS_LOG, SYS_PANIC},
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_A7},
    },
    PAGE_SIZE, WORD_SIZE,
};

use super::{elf::Program, loader::Loader, merge_word8, plonk, split_word8, TraceEvent};
use crate::{MemoryImage, CIRCUIT};

pub trait HostHandler {
    fn is_trace_enabled(&self) -> bool;
    fn on_commit(&mut self, buf: &[u32]) -> Result<()>;
    fn on_panic(&mut self, msg: &str) -> Result<()>;
    fn on_txrx(&mut self, channel: u32, buf: &[u8]) -> Result<Vec<u8>>;
    fn on_trace(&mut self, event: TraceEvent) -> Result<()>;
}

struct MemoryState {
    pub ram: BTreeMap<u32, u32>,
    // Ram in the FFPU section of memory; these RAM slots store four Fps instead of one u32.
    pub ffpu_ram: Vec<(BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem)>,

    // Plonk tables for sorting plonks in proper order
    pub ram_plonk: plonk::RamPlonk,
    pub bytes_plonk: plonk::BytesPlonk,

    // Plonk accumulations for compute_accum and verify_accum phases
    pub plonk_accum: BTreeMap<String, plonk::PlonkAccum<BabyBear>>,
}

impl MemoryState {
    #[track_caller]
    fn load_u8(&self, addr: u32) -> u8 {
        // debug!("load_u8: 0x{addr:08X}");
        // align to the nearest word
        let aligned = addr & !(WORD_SIZE as u32 - 1);
        let offset = addr % WORD_SIZE as u32;
        let word = self.load_u32(aligned);
        ((word >> (offset * 8)) & 0xff) as u8
    }

    #[track_caller]
    fn load_u32(&self, addr: u32) -> u32 {
        // debug!("load_u32: 0x{addr:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        let key = addr / 4;
        match self.ram.get(&key) {
            Some(word) => *word,
            None => panic!("addr out of range: 0x{addr:08X}"),
        }
    }

    fn load_register(&self, num: usize) -> u32 {
        self.load_u32((SYSTEM.start() + num * 4) as u32)
    }

    #[track_caller]
    fn load_region_u32(&self, start: u32, size: u32) -> Vec<u32> {
        (start..start + size)
            .step_by(WORD_SIZE)
            .map(|addr| self.load_u32(addr))
            .collect()
    }

    #[track_caller]
    fn load_region(&self, addr: u32, size: u32) -> Vec<u8> {
        let mut region = Vec::new();
        for addr in addr..addr + size {
            region.push(self.load_u8(addr));
        }
        region
    }

    #[track_caller]
    fn store_u8(&mut self, addr: u32, value: u8) {
        // debug!("store_u8: 0x{addr:08X} <= 0x{value:08X}");
        // align to the nearest word
        let aligned = addr & !(WORD_SIZE as u32 - 1);
        let offset = addr % WORD_SIZE as u32;
        let key = aligned / 4;
        let mut word = self.ram.get(&key).unwrap_or(&0) & !(0xff << (offset * 8));
        word |= (value as u32) << (offset * 8);
        self.store_u32(aligned, word);
    }

    #[track_caller]
    fn store_u32(&mut self, addr: u32, value: u32) {
        // debug!("store_u32: 0x{addr:08X} <= 0x{value:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        let key = addr / 4;
        self.ram.insert(key, value);
    }

    #[track_caller]
    fn store_region(&mut self, addr: u32, slice: &[u8]) {
        trace!("store_region: 0x{addr:08X} <= {} bytes", slice.len());
        for i in 0..slice.len() {
            self.store_u8(addr + i as u32, slice[i]);
        }
    }

    #[track_caller]
    fn store_region_u32(&mut self, addr: u32, slice: &[u32]) {
        assert!(addr % WORD_SIZE as u32 == 0);
        for (offset, word) in slice.iter().enumerate() {
            self.store_u32(addr + WORD_SIZE as u32 * offset as u32, *word);
        }
    }

    // Reads a slice of data from the guest's memory and interprets it
    // as the given type, which must be plain old data..  The address
    // provided is the guest's address of a SliceDescriptor structure.
    fn read_slice<T: Pod>(&self, desc_addr: u32) -> Vec<T> {
        let desc_bytes = self.load_region(desc_addr, 8);
        let size: u32 = *bytemuck::from_bytes(&desc_bytes[..4]);
        let addr: u32 = *bytemuck::from_bytes(&desc_bytes[4..]);
        let elt_size = core::mem::size_of::<T>();
        assert_eq!(elt_size % WORD_SIZE, 0, "T should be word aligned");
        assert_eq!(
            size as usize % elt_size,
            0,
            "slice does not end on a boundary of T; size={size}, elt_size={elt_size}"
        );
        let bytes = self.load_region(addr, size);
        bytes
            .chunks_exact(elt_size)
            .map(|chunk| *bytemuck::from_bytes(chunk))
            .collect()
    }

    // Reads words from guest's memory and transmutes it into the given value,
    // which should be repr(C) and plain old data.
    fn read_value<T: Pod>(&self, addr: u32) -> T {
        let size = core::mem::size_of::<T>();
        assert_eq!(size % WORD_SIZE, 0, "T should be word aligned");
        let bytes = self.load_region(addr, size as u32);
        *bytemuck::from_bytes(&bytes)
    }
}

pub struct MachineContext<'a, H: HostHandler> {
    memory: MemoryState,
    handler: &'a mut H,
    trace_enabled: bool,
    halted: bool,
    pc: u32,
}

#[derive(Debug)]
struct OpCode {
    mnemonic: &'static str,
    major: u32,
    minor: u32,
}

impl OpCode {
    fn new(mnemonic: &'static str, idx: u32) -> Self {
        Self {
            mnemonic,
            major: idx / 8,
            minor: idx % 8,
        }
    }

    fn with_major_minor(mnemonic: &'static str, major: u32, minor: u32) -> Self {
        Self {
            mnemonic,
            major,
            minor,
        }
    }
}

impl<'a, H: HostHandler> CircuitStepHandler<BabyBearElem> for MachineContext<'a, H> {
    fn call(
        &mut self,
        cycle: usize,
        name: &str,
        extra: &str,
        args: &[BabyBearElem],
        outs: &mut [BabyBearElem],
    ) -> Result<()> {
        match name {
            "halt" => {
                if !self.halted {
                    debug!("HALT: {cycle}");
                }
                self.halted = true;
                Ok(())
            }
            "trace" => self.trace(cycle, args[0]),
            "getMajor" => {
                // determine if page_fault is needed
                let opcode = self.decode((args[0], args[1], args[2], args[3]));
                outs[0] = BabyBearElem::new(opcode.major);
                trace!("decode: {}", opcode.mnemonic);
                Ok(())
            }
            "getMinor" => {
                let opcode = self.decode((args[0], args[1], args[2], args[3]));
                outs[0] = BabyBearElem::new(opcode.minor);
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
            "ramWrite" => {
                self.ram_write(args[0], (args[1], args[2], args[3], args[4]))?;
                Ok(())
            }
            "ramRead" => {
                (outs[0], outs[1], outs[2], outs[3]) = self.ram_read(args[0]);
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
            "syscall" => {
                (
                    (outs[0], outs[1], outs[2], outs[3]),
                    (outs[4], outs[5], outs[6], outs[7]),
                ) = self.syscall(cycle)?;
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

impl MemoryState {
    fn new() -> Self {
        Self {
            ram: BTreeMap::new(),
            ffpu_ram: Vec::new(),
            ram_plonk: plonk::RamPlonk::new(),
            bytes_plonk: plonk::BytesPlonk::new(),
            plonk_accum: BTreeMap::new(),
        }
    }
}

impl<'a, H: HostHandler> MachineContext<'a, H> {
    pub fn new(io: &'a mut H) -> Self {
        MachineContext {
            memory: MemoryState::new(),
            trace_enabled: io.is_trace_enabled(),
            handler: io,
            halted: false,
            pc: 0x00000000,
        }
    }

    fn trace(&mut self, cycle: usize, pc: BabyBearElem) -> Result<()> {
        self.pc = pc.into();
        if self.trace_enabled {
            self.handler.on_trace(TraceEvent::InstructionStart {
                cycle: cycle as u32,
                pc: self.pc,
            })?
        }
        Ok(())
    }

    fn divide(
        &self,
        numer: (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
        denom: (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
        sign: BabyBearElem,
    ) -> (
        (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
        (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
    ) {
        let mut numer = merge_word8(numer) as i64;
        let mut denom = merge_word8(denom) as i64;
        let sign: u32 = sign.into();
        // debug!("divide: [{sign}] {numer} / {denom}");
        let ones_comp = (sign == 2) as i64;
        let neg_numer = sign != 0 && numer < 0;
        let neg_denom = sign == 1 && denom < 0;
        if neg_numer {
            numer = -numer - ones_comp;
        }
        if neg_denom {
            denom = -denom - ones_comp;
        }
        let (mut quot, mut rem) = if denom == 0 {
            (0xffffffff, numer)
        } else {
            (numer / denom, numer % denom)
        };
        let quot_neg_out =
            (neg_numer as u32 ^ neg_denom as u32) - ((denom == 0) as u32 * neg_numer as u32);
        if quot_neg_out != 0 {
            quot = -quot - ones_comp;
        }
        if neg_numer {
            rem = -rem - ones_comp;
        }
        // debug!("  {quot}, {rem}");
        (
            split_word8(quot as i32 as u32),
            split_word8(rem as i32 as u32),
        )
    }

    fn extract_trace(&mut self, message: &str, args: &[BabyBearElem]) -> Result<()> {
        match message {
            msg if msg.starts_with("C%u: pc: %08x Decode") => {
                let (cycle, pc) = (args[0], args[1]);
                self.handler.on_trace(TraceEvent::InstructionStart {
                    cycle: cycle.into(),
                    pc: pc.into(),
                })?
            }
            "C%u: pc: %08x Final: 0x%04x%04x -> r%u, next: %08x" => {
                let (val_high, val_low, reg) = (args[2], args[3], args[4]);
                self.handler.on_trace(TraceEvent::RegisterSet {
                    reg: u32::from(reg) as usize,
                    value: ((u32::from(val_high)) * (1 << 16) + (u32::from(val_low))),
                })?
            }
            _ => (),
        }
        Ok(())
    }

    fn log(&mut self, msg: &str, args: &[BabyBearElem]) {
        if self.trace_enabled {
            self.extract_trace(msg, args).unwrap();
        }
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
                "x" => format!("{:0width$x}", next_arg()),
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
        trace!("{}", formatted);
    }

    fn ram_read(
        &mut self,
        addr: BabyBearElem,
    ) -> (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem) {
        let addr: u32 = addr.into();
        if addr as usize * 4 >= FFPU.start() {
            let ffpu_addr = addr as usize - FFPU.start() / 4;
            if ffpu_addr >= self.memory.ffpu_ram.len() {
                return (
                    BabyBearElem::ZERO,
                    BabyBearElem::ZERO,
                    BabyBearElem::ZERO,
                    BabyBearElem::ZERO,
                );
            }
            return self.memory.ffpu_ram[ffpu_addr];
        } else {
            let data = *self.memory.ram.entry(addr).or_insert(0);
            // debug!("data: 0x{data:08X}");
            split_word8(data)
        }
    }

    fn ram_write(
        &mut self,
        addr: BabyBearElem,
        data: (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
    ) -> Result<()> {
        let addr: u32 = addr.into();
        if addr as usize * 4 >= FFPU.start() {
            let ffpu_addr = addr as usize - FFPU.start() / 4;
            if self.memory.ffpu_ram.len() <= ffpu_addr {
                let z = BabyBearElem::ZERO;
                self.memory.ffpu_ram.resize(ffpu_addr + 1, (z, z, z, z));
            }
            self.memory.ffpu_ram[ffpu_addr] = data
        } else {
            let data = merge_word8(data);
            // debug!("ram_write> 0x{:08X} <= 0x{:08X}", addr * 4, data);
            self.memory.ram.insert(addr, data);
            if self.trace_enabled {
                let addr = (addr * 4) as usize;
                if addr >= SYSTEM.start() && addr < SYSTEM.end() {
                    self.handler.on_trace(TraceEvent::RegisterSet {
                        reg: (addr - SYSTEM.start()) / 4,
                        value: data,
                    })?
                } else {
                    self.handler.on_trace(TraceEvent::MemorySet {
                        addr: addr as u32,
                        value: data,
                    })?
                }
            }
        }
        Ok(())
    }

    fn plonk_read(&mut self, name: &str, outs: &mut [BabyBearElem]) {
        match name {
            "ram" => self.memory.ram_plonk.read(outs.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.read(outs.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_write(&mut self, name: &str, args: &[BabyBearElem]) {
        match name {
            "ram" => self.memory.ram_plonk.write(args.try_into().unwrap()),
            "bytes" => self.memory.bytes_plonk.write(args.try_into().unwrap()),
            _ => panic!("Unknown plonk type {name}"),
        }
    }

    fn plonk_read_accum(&mut self, name: &str, outs: &mut [BabyBearElem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.read(outs)
        } else {
            panic!("Unknown plonk accum {}", name);
        }
    }

    fn plonk_write_accum(&mut self, name: &str, args: &[BabyBearElem]) {
        if let Some(entry) = self.memory.plonk_accum.get_mut(name) {
            entry.write(args);
        } else {
            let mut accum = plonk::PlonkAccum::new();
            accum.write(args);
            self.memory.plonk_accum.insert(name.to_string(), accum);
        }
    }

    fn syscall(
        &mut self,
        cycle: usize,
    ) -> Result<(
        (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
        (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
    )> {
        let nr = self.memory.load_register(REG_A7);
        match nr {
            SYS_PANIC => {
                let msg_ptr = self.memory.load_register(REG_A0);
                let msg_len = self.memory.load_register(REG_A1);
                let buf = self.memory.load_region(msg_ptr, msg_len);
                let str = String::from_utf8(buf).unwrap();
                debug!("SYS_PANIC[{cycle}]> {str}");
                self.handler.on_panic(&str)?;
                Ok((split_word8(0), split_word8(0)))
            }
            SYS_LOG => {
                let msg_ptr = self.memory.load_register(REG_A0);
                let msg_len = self.memory.load_register(REG_A1);
                let buf = self.memory.load_region(msg_ptr, msg_len);
                let str = String::from_utf8(buf).unwrap();
                println!("R0VM[{cycle}] {}", str);
                Ok((split_word8(0), split_word8(0)))
            }
            SYS_IO => {
                let channel = self.memory.load_register(REG_A0);
                let buf_ptr = self.memory.load_register(REG_A1);
                let buf_len = self.memory.load_register(REG_A2);
                let out_ptr = self.memory.load_register(REG_A3);
                debug!("SYS_IO[{cycle}]");

                let buf = self.memory.load_region(buf_ptr, buf_len);
                let result = self.handler.on_txrx(channel, &buf)?;
                self.memory.store_region(out_ptr, &result);

                Ok((split_word8(result.len() as u32), split_word8(0)))
            }
            SYS_COMMIT => {
                let buf_ptr = self.memory.load_register(REG_A0);
                let buf_len = self.memory.load_register(REG_A1);
                debug!("SYS_COMMIT[{cycle}]> 0x{buf_ptr:08X} : {buf_len}");
                let buf = self.memory.load_region_u32(buf_ptr, buf_len);
                self.handler.on_commit(buf.as_slice())?;
                Ok((split_word8(0), split_word8(0)))
            }
            SYS_CYCLE_COUNT => {
                debug!("SYS_CYCLE_COUNT[{cycle}]> cycle = {cycle}");
                Ok((split_word8(cycle as u32), split_word8(0)))
            }
            SYS_COMPUTE_POLY => {
                let eval_u_ptr = self.memory.load_register(REG_A0);
                let poly_mix_ptr = self.memory.load_register(REG_A1);
                let out_ptr = self.memory.load_register(REG_A2);
                let mix_ptr = self.memory.load_register(REG_A3);
                let result_ptr = self.memory.load_register(REG_A4);
                debug!("SYS_COMPUTE_POLY[{cycle}]>");

                let eval_u: Vec<BabyBearExtElem> = self.memory.read_slice(eval_u_ptr);
                let poly_mix = self.memory.read_value(poly_mix_ptr);
                let out: Vec<BabyBearElem> = self.memory.read_slice(out_ptr);
                let mix: Vec<BabyBearElem> = self.memory.read_slice(mix_ptr);

                let args: &[&[BabyBearElem]] = &[&out, &mix];
                let result = CIRCUIT.poly_ext(&poly_mix, &eval_u, args);

                let words = result.tot.to_u32_words();
                self.memory.store_region_u32(result_ptr, &words);
                Ok((split_word8(words.len() as u32), split_word8(0)))
            }
            _ => bail!("Unsupported syscall: {nr}"),
        }
    }

    fn decode(&self, word: (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem)) -> OpCode {
        let word = merge_word8(word);
        let opcode = word & 0x0000007f;
        let rs2 = (word & 0x01f00000) >> 20;
        let funct3 = (word & 0x00007000) >> 12;
        let funct7 = (word & 0xfe000000) >> 25;
        // debug!("decode: 0x{word:08X}");

        match opcode {
            0b0000011 => match funct3 {
                0x0 => OpCode::new("LB", 24),
                0x1 => OpCode::new("LH", 25),
                0x2 => OpCode::new("LW", 26),
                0x4 => OpCode::new("LBU", 27),
                0x5 => OpCode::new("LHU", 28),
                _ => unreachable!(),
            },
            0b0010011 => match funct3 {
                0x0 => OpCode::new("ADDI", 7),
                0x1 => OpCode::new("SLLI", 37),
                0x2 => OpCode::new("SLTI", 11),
                0x3 => OpCode::new("SLTIU", 12),
                0x4 => OpCode::new("XORI", 8),
                0x5 => match funct7 {
                    0x00 => OpCode::new("SRLI", 46),
                    0x20 => OpCode::new("SRAI", 47),
                    _ => unreachable!(),
                },
                0x6 => OpCode::new("ORI", 9),
                0x7 => OpCode::new("ANDI", 10),
                _ => unreachable!(),
            },
            0b0010111 => OpCode::new("AUIPC", 22),
            0b0100011 => match funct3 {
                0x0 => OpCode::new("SB", 29),
                0x1 => OpCode::new("SH", 30),
                0x2 => OpCode::new("SW", 31),
                _ => unreachable!(),
            },
            0b0110011 => match (funct3, funct7) {
                (0x0, 0x00) => OpCode::new("ADD", 0),
                (0x0, 0x20) => OpCode::new("SUB", 1),
                (0x1, 0x00) => OpCode::new("SLL", 36),
                (0x2, 0x00) => OpCode::new("SLT", 5),
                (0x3, 0x00) => OpCode::new("SLTU", 6),
                (0x4, 0x00) => OpCode::new("XOR", 2),
                (0x5, 0x00) => OpCode::new("SRL", 44),
                (0x5, 0x20) => OpCode::new("SRA", 45),
                (0x6, 0x00) => OpCode::new("OR", 3),
                (0x7, 0x00) => OpCode::new("AND", 4),
                (0x0, 0x01) => OpCode::new("MUL", 32),
                (0x1, 0x01) => OpCode::new("MULH", 33),
                (0x2, 0x01) => OpCode::new("MULSU", 34),
                (0x3, 0x01) => OpCode::new("MULU", 35),
                (0x4, 0x01) => OpCode::new("DIV", 40),
                (0x5, 0x01) => OpCode::new("DIVU", 41),
                (0x6, 0x01) => OpCode::new("REM", 42),
                (0x7, 0x01) => OpCode::new("REMU", 43),
                _ => unreachable!(),
            },
            0b0110111 => OpCode::new("LUI", 21),
            0b1100011 => match funct3 {
                0x0 => OpCode::new("BEQ", 13),
                0x1 => OpCode::new("BNE", 14),
                0x4 => OpCode::new("BLT", 15),
                0x5 => OpCode::new("BGE", 16),
                0x6 => OpCode::new("BLTU", 17),
                0x7 => OpCode::new("BGEU", 18),
                _ => unreachable!(),
            },
            0b1100111 => match funct3 {
                0x0 => OpCode::new("JALR", 20),
                _ => unreachable!(),
            },
            0b1101111 => OpCode::new("JAL", 19),
            0b1110011 => match funct3 {
                0x0 => match (rs2, funct7) {
                    (0x0, 0x0) => OpCode::with_major_minor("ECALL", 8, 0),
                    (0x1, 0x0) => OpCode::with_major_minor("EBREAK", 8, 1),
                    _ => unreachable!(),
                },
                _ => unreachable!(),
            },
            _ => panic!("Illegal opcode: 0b{opcode:07b}"),
        }
    }
}

pub struct RV32Executor<'a, H: HostHandler> {
    image: MemoryImage,
    loader: Loader,
    entry: u32,
    pub executor: Executor<BabyBear, CircuitImpl, MachineContext<'a, H>>,
}

impl<'a, H: HostHandler> RV32Executor<'a, H> {
    pub fn new(circuit: &'static CircuitImpl, elf: &'a Program, io: &'a mut H) -> Self {
        debug!("image.size(): {}", elf.image.len());
        let machine = MachineContext::new(io);
        let min_po2 = log2_ceil(1570 + elf.image.len() / 3 + ZK_CYCLES);
        let executor = Executor::new(circuit, machine, min_po2, MAX_CYCLES_PO2);
        let image = MemoryImage::new(elf, PAGE_SIZE);
        Self {
            image,
            loader: Loader::new(&elf.image),
            entry: elf.entry,
            executor,
        }
    }

    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<usize> {
        let cycles = self
            .loader
            .load(self.entry, |chunk, fini| self.executor.step(chunk, fini))?;
        self.executor.finalize();
        Ok(cycles)
    }
}
