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

use alloc::{
    collections::{BTreeMap, BTreeSet, VecDeque},
    rc::Rc,
};
use core::cell::RefCell;

use anyhow::Result;
use lazy_regex::{regex, Captures};
use log::{debug, trace};
use num_traits::FromPrimitive;
use risc0_circuit_rv32im::CircuitImpl;
use risc0_core::field::{
    baby_bear::{BabyBear, BabyBearElem},
    Elem,
};
use risc0_zkp::{
    adapter::{CircuitInfo, CircuitStepHandler},
    core::sha::BLOCK_BYTES,
    prove::executor::Executor,
    MAX_CYCLES_PO2, ZK_CYCLES,
};
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{
        ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_T0},
        DIGEST_WORDS,
    },
    PAGE_SIZE, WORD_SIZE,
};

use super::{loader::Loader, plonk, SyscallContext, TraceEvent};
use crate::binfmt::image::{MemoryImage, PageTableInfo};

const IMM_BITS: usize = 12;

// The number of cycles required to compress a SHA-256 block.
const SHA_CYCLES: usize = 72;

// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

// The number of cycles required to compute a SHA-256 digest of a page.
const CYCLES_PER_PAGE: usize = SHA_CYCLES * BLOCKS_PER_PAGE;

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

pub trait HostHandler {
    fn is_trace_enabled(&self) -> bool;
    fn on_txrx(
        &mut self,
        ctx: &dyn SyscallContext,
        syscall_name: &str,
        to_guest_buf: &mut [u32],
    ) -> Result<(u32, u32)>;
    fn on_trace(&mut self, event: TraceEvent) -> Result<()>;
}

pub struct MemoryState {
    pub ram: Rc<RefCell<MemoryImage>>,

    // Plonk tables for sorting plonks in proper order
    pub ram_plonk: plonk::RamPlonk,
    pub bytes_plonk: plonk::BytesPlonk,

    // Plonk accumulations for compute_accum and verify_accum phases
    pub plonk_accum: BTreeMap<String, plonk::PlonkAccum<BabyBear>>,

    // Current cycle being run.
    cur_cycle: usize,
}

impl SyscallContext for MemoryState {
    #[track_caller]
    fn load_u8(&self, addr: u32) -> u8 {
        // debug!("load_u8: 0x{addr:08X}");
        self.ram.borrow().image[addr as usize]
    }

    #[track_caller]
    fn load_u32(&self, addr: u32) -> u32 {
        // debug!("load_u32: 0x{addr:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        let mut bytes = [0u8; WORD_SIZE];
        for i in 0..WORD_SIZE {
            bytes[i] = self.load_u8(addr + i as u32);
        }
        u32::from_le_bytes(bytes)
    }

    fn get_cycle(&self) -> usize {
        self.cur_cycle
    }
}

impl MemoryState {
    pub(crate) fn new(image: Rc<RefCell<MemoryImage>>) -> Self {
        Self {
            ram: image,
            ram_plonk: plonk::RamPlonk::new(),
            bytes_plonk: plonk::BytesPlonk::new(),
            plonk_accum: BTreeMap::new(),
            cur_cycle: 0,
        }
    }

    #[track_caller]
    fn store_u8(&mut self, addr: u32, value: u8) {
        // debug!("store_u8: 0x{addr:08X} <= 0x{value:08X}");
        self.ram.borrow_mut().image[addr as usize] = value;
    }

    #[track_caller]
    fn store_region(&mut self, addr: u32, slice: &[u8]) {
        // trace!("store_region: 0x{addr:08X} <= {} bytes", slice.len());
        for i in 0..slice.len() {
            self.store_u8(addr + i as u32, slice[i]);
        }
    }

    #[track_caller]
    fn store_u32(&mut self, addr: u32, value: u32) {
        // debug!("store_u32: 0x{addr:08X} <= 0x{value:08X}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        self.store_region(addr, &value.to_le_bytes());
    }
}

#[allow(dead_code)]
#[derive(Debug, num_derive::FromPrimitive, PartialEq)]
#[repr(u32)]
enum MajorType {
    Compute0,
    Compute1,
    Compute2,
    MemIo,
    Multiply,
    Divide,
    VerifyAnd,
    VerifyDivide,
    ECall,
    ShaInit,
    ShaLoad,
    ShaMain,
    PageFault,
    CopyIn,
    Halt,
    MuxSize,
}

impl MajorType {
    fn as_u32(self) -> u32 {
        self as u32
    }
}

#[derive(Debug)]
struct OpCode {
    mnemonic: &'static str,
    major: MajorType,
    minor: u32,
}

impl OpCode {
    fn new(mnemonic: &'static str, idx: u32) -> Self {
        Self {
            mnemonic,
            major: FromPrimitive::from_u32(idx / 8).unwrap(),
            minor: idx % 8,
        }
    }

    fn with_major_minor(mnemonic: &'static str, major: MajorType, minor: u32) -> Self {
        Self {
            mnemonic,
            major,
            minor,
        }
    }
}

enum IncludeDir {
    Read = 0b01,
    Write = 0b10,
    Both = 0b11,
}

struct PageFaults {
    reads: BTreeSet<u32>,
    writes: BTreeSet<u32>,
    force_flush: bool,
}

impl PageFaults {
    pub fn new() -> Self {
        Self {
            reads: BTreeSet::new(),
            writes: BTreeSet::new(),
            force_flush: false,
        }
    }

    pub fn include(&mut self, info: &PageTableInfo, addr: u32, dir: IncludeDir) {
        let dir = dir as u32;
        let mut addr = addr;
        loop {
            let page_idx = info.get_page_index(addr);
            let entry_addr = info.get_page_entry_addr(page_idx);
            if dir & IncludeDir::Read as u32 != 0 {
                self.reads.insert(page_idx);
            }
            if dir & IncludeDir::Write as u32 != 0 {
                self.writes.insert(page_idx);
            }
            if page_idx == info.root_idx {
                break;
            }
            addr = entry_addr;
        }
    }

    #[allow(dead_code)]
    fn dump(&self) {
        debug!("PageFaultInfo");
        debug!("  reads>");
        for idx in self.reads.iter().rev() {
            debug!("  0x{:08X}", idx);
        }
        debug!("  writes>");
        for idx in self.writes.iter().rev() {
            debug!("  0x{:08X}", idx);
        }
    }
}

fn setbits(x: u8) -> u32 {
    u32::MAX >> (32 - x)
}

fn split_word8(value: u32) -> (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem) {
    (
        BabyBearElem::new(value & 0xff),
        BabyBearElem::new(value >> 8 & 0xff),
        BabyBearElem::new(value >> 16 & 0xff),
        BabyBearElem::new(value >> 24 & 0xff),
    )
}

fn merge_word8((x0, x1, x2, x3): (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem)) -> u32 {
    let x0: u32 = x0.into();
    let x1: u32 = x1.into();
    let x2: u32 = x2.into();
    let x3: u32 = x3.into();
    x0 | x1 << 8 | x2 << 16 | x3 << 24
}

fn sign_extend(x: i32, bits: u32) -> i32 {
    let remain = WORD_SIZE as u32 * 8 - bits;
    x.wrapping_shl(remain).wrapping_shr(remain)
}

pub struct MachineContext<'a, H: HostHandler> {
    memory: MemoryState,
    handler: &'a mut H,
    trace_enabled: bool,

    is_halted: bool,

    // When the machine is in a flushing state, no new dirty pages will be recorded and the
    // next dirty page will be reported in a 'pageInfo' extern.
    is_flushing: bool,

    // Tracks pages that have already been paged in.
    finished_page_reads: BTreeSet<u32>,

    // This is just for diagnostics: tracks which words have been paged in.
    resident_words: BTreeSet<u32>,

    // Tracks which pages are dirty and need to be paged out in a subsquent flush
    dirty_pages: BTreeSet<u32>,

    last_pc: u32,
    exit_code: u32,
    segment_limit: usize,

    syscall_out_data: VecDeque<u32>,
    syscall_out_regs: (u32, u32),
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
                self.halt(cycle, args[0], args[1]);
                Ok(())
            }
            "trace" => self.trace(cycle, args[0]),
            "getMajor" => {
                outs[0] = self.get_major(args[0], args[1])?;
                Ok(())
            }
            "getMinor" => {
                let inst = merge_word8((args[0], args[1], args[2], args[3]));
                let opcode = self.decode(inst);
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
                (outs[0], outs[1], outs[2], outs[3]) = self.ram_read(args[0], args[1]);
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
            "syscallInit" => {
                self.syscall_init(cycle)?;
                Ok(())
            }
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

impl<'a, H: HostHandler> MachineContext<'a, H> {
    pub fn new(io: &'a mut H, image: Rc<RefCell<MemoryImage>>, segment_limit: usize) -> Self {
        MachineContext {
            memory: MemoryState::new(image),
            trace_enabled: io.is_trace_enabled(),
            handler: io,
            is_halted: false,
            is_flushing: false,
            syscall_out_data: VecDeque::new(),
            syscall_out_regs: (0, 0),
            resident_words: BTreeSet::new(),
            finished_page_reads: BTreeSet::new(),
            dirty_pages: BTreeSet::new(),
            last_pc: 0,
            exit_code: 0,
            segment_limit,
        }
    }

    fn halt(&mut self, cycle: usize, exit_code: BabyBearElem, pc: BabyBearElem) {
        if !self.is_halted {
            self.exit_code = exit_code.into();
            self.last_pc = pc.into();
            match self.exit_code {
                halt::TERMINATE => {
                    debug!("TERM[{cycle}]> pc: 0x{:08x}", self.last_pc);
                }
                halt::PAUSE => {
                    self.last_pc += 4;
                    debug!("PAUSE[{cycle}]> pc: 0x{:08x}", self.last_pc);
                }
                halt::SPLIT => {
                    self.last_pc += 4;
                    debug!("SPLIT[{cycle}]> pc: 0x{:08x}", self.last_pc);
                }
                _ => unimplemented!("Unsupported halt mode: {}", self.exit_code),
            }
            self.is_halted = true;
        }
    }

    fn get_major(&mut self, cycle: BabyBearElem, pc: BabyBearElem) -> Result<BabyBearElem> {
        let pc: u32 = pc.into();
        let inst = self.memory.load_u32(pc);
        let opcode = self.decode(inst);
        trace!("decode: {}", opcode.mnemonic);

        // determine if PageFaults are needed
        let faults = self.get_page_faults(pc, inst, &opcode);
        // faults.dump();

        let force_flush = faults.force_flush;
        if self.is_flushing {
            if !force_flush || !self.dirty_pages.is_empty() {
                return Ok(MajorType::PageFault.as_u32().into());
            }
            return Ok(opcode.major.as_u32().into());
        }

        if force_flush || self.needs_flush(cycle.into(), &faults) {
            self.is_flushing = true;
            debug!(
                "flush> {} pages, required_cycles: {}",
                self.dirty_pages.len(),
                self.dirty_pages.len() * (1 + CYCLES_PER_PAGE)
            );
            return Ok(MajorType::PageFault.as_u32().into());
        }

        self.dirty_pages.extend(faults.writes.iter());

        for page_idx in faults.reads {
            if !self.finished_page_reads.contains(&page_idx) {
                return Ok(MajorType::PageFault.as_u32().into());
            }
        }

        Ok(opcode.major.as_u32().into())
    }

    // Determine if a flush is required because there won't be enough cycles to
    // complete the current instruction assuming that paging out all dirty pages
    // up to this point require a certain amount of cycles.
    fn needs_flush(&self, cycle: u32, faults: &PageFaults) -> bool {
        let cycle = cycle as usize;
        assert!(self.segment_limit > cycle);
        // How many cycles remain in the current segment?
        let remaining_cycles = self.segment_limit - cycle;
        let reads = faults.reads.difference(&self.finished_page_reads).count();
        let writes = self.dirty_pages.union(&faults.writes).count();
        // How many cycles are required to execute the next instruction?
        // This sum is based on:
        // - ensure we don't split in the middle of a SHA compress
        // - each page_in requires 1 PageFault cycle + CYCLES_PER_PAGE cycles
        // - each page_out requires 1 PageFault cycle + CYCLES_PER_PAGE cycles
        // - leave room for 2 Reset, BytesFini, and RamFini cycles
        // - leave room for ZK cycles
        let required_cycles = SHA_CYCLES
            + reads * (1 + CYCLES_PER_PAGE)
            + writes * (1 + CYCLES_PER_PAGE)
            + 4
            + ZK_CYCLES;
        // debug!(
        //     "segment_limit: {}, cycle: {}, remaining_cycles: {}, required_cycles: {},
        // reads: {}, writes: {}",     self.segment_limit, cycle,
        // remaining_cycles, required_cycles, reads, writes );
        required_cycles > remaining_cycles
    }

    fn get_page_faults(&self, pc: u32, inst: u32, opcode: &OpCode) -> PageFaults {
        let info = &self.memory.ram.borrow().info;
        let mut faults = PageFaults::new();
        // While it's not technically true that all instructions cause writes to at
        // least one system register, it's safe to do this because the only cost
        // is doing an extra hash of a page that isn't actually dirty. The
        // benefit is that we don't have to identity instructions that don't
        // have any system register mutations.
        faults.include(info, SYSTEM.start() as u32, IncludeDir::Both);
        faults.include(info, pc, IncludeDir::Read);

        if opcode.major == MajorType::MemIo {
            let rs1 = (inst >> 15) & setbits(5);
            let base = self.memory.load_register(rs1 as usize);
            if opcode.minor < 5 {
                // load: I-type
                let imm = (inst >> 20) & setbits(12);
                let imm = sign_extend(imm as i32, IMM_BITS as u32);
                let addr = base.checked_add_signed(imm).unwrap();
                // debug!("  load: 0x{inst:08x}, M[x{rs1} + {imm}], addr: 0x{addr:08x}");
                faults.include(info, addr, IncludeDir::Read);
            } else {
                // store: S-type
                let imm_low = (inst >> 7) & setbits(5);
                let imm_high = (inst >> 25) & setbits(7);
                let imm = (imm_high << 5) | imm_low;
                let imm = sign_extend(imm as i32, IMM_BITS as u32);
                let addr = base.checked_add_signed(imm).unwrap();
                // debug!("  store: 0x{inst:08x}, M[x{rs1} + {imm}], addr: 0x{addr:08x}");
                faults.include(info, addr, IncludeDir::Both);
            }
        } else if opcode.major == MajorType::ECall {
            let minor = self.memory.load_register(REG_T0);
            if minor == ecall::SHA {
                let state_out_addr = self.memory.load_register(REG_A0);
                let state_in_addr = self.memory.load_register(REG_A1);
                let block1_addr = self.memory.load_register(REG_A2);
                let block2_addr = self.memory.load_register(REG_A3);
                let count = self.memory.load_register(REG_A4);
                for i in 0..DIGEST_WORDS {
                    faults.include(
                        info,
                        state_out_addr + (i * WORD_SIZE) as u32,
                        IncludeDir::Read,
                    );
                }
                for i in 0..DIGEST_WORDS {
                    faults.include(
                        info,
                        state_in_addr + (i * WORD_SIZE) as u32,
                        IncludeDir::Read,
                    );
                }
                for i in 0..count {
                    let addr1 = block1_addr + i * BLOCK_BYTES as u32;
                    let addr2 = block2_addr + i * BLOCK_BYTES as u32;
                    for j in 0..DIGEST_WORDS {
                        faults.include(info, addr1 + (j * WORD_SIZE) as u32, IncludeDir::Read);
                        faults.include(info, addr2 + (j * WORD_SIZE) as u32, IncludeDir::Read);
                    }
                }
            } else if minor == ecall::SOFTWARE {
                let out_addr = self.memory.load_register(REG_A0);
                let out_words = self.memory.load_register(REG_A1);
                let out_bytes = out_words * WORD_SIZE as u32;

                for addr in (out_addr..(out_addr + out_bytes)).step_by(WORD_SIZE) {
                    faults.include(info, addr, IncludeDir::Both);
                }
            } else if minor == ecall::HALT {
                let mode = self.memory.load_register(REG_A0);
                if mode == halt::PAUSE {
                    faults.force_flush = true;
                }
            }
        }

        faults
    }

    fn page_info(&mut self, pc: BabyBearElem) -> (BabyBearElem, BabyBearElem, BabyBearElem) {
        let pc: u32 = pc.into();
        let inst = self.memory.load_u32(pc);
        let opcode = self.decode(inst);
        let info = self.get_page_faults(pc, inst, &opcode);

        if self.is_flushing {
            if let Some(page_idx) = self.dirty_pages.pop_first() {
                // let info = &self.memory.ram.borrow().info;
                // debug!(
                //     "dirty> page_idx: 0x{page_idx:08X}, page_addr: {:08X}",
                //     info.get_page_addr(page_idx)
                // );
                return (BabyBearElem::ZERO, page_idx.into(), BabyBearElem::ZERO);
            }
        } else {
            for page_idx in info.reads.iter().rev() {
                if !self.finished_page_reads.contains(page_idx) {
                    self.finished_page_reads.insert(*page_idx);
                    // debug!("read> page_idx: 0x{page_idx:08X}");
                    return (BabyBearElem::ONE, (*page_idx).into(), BabyBearElem::ZERO);
                }
            }
        }

        (BabyBearElem::ZERO, BabyBearElem::ZERO, BabyBearElem::ONE)
    }

    fn trace(&mut self, cycle: usize, pc: BabyBearElem) -> Result<()> {
        if self.trace_enabled {
            let cycle = cycle as u32;
            let pc = pc.into();
            self.handler
                .on_trace(TraceEvent::InstructionStart { cycle, pc })?
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
        let mut numer = merge_word8(numer) as u32;
        let mut denom = merge_word8(denom) as u32;
        let sign: u32 = sign.into();
        // debug!("divide: [{sign}] {numer} / {denom}");
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
        // debug!("  quot: {quot}, rem: {rem}");
        (split_word8(quot), split_word8(rem))
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
        op: BabyBearElem,
    ) -> (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem) {
        let addr: u32 = addr.into();
        let op: u32 = op.into();
        let info = &self.memory.ram.borrow().info;
        if op == MemoryOp::PageIo.as_u32() {
            self.resident_words.insert(addr);
        } else {
            if !self.resident_words.contains(&addr) {
                let addr = addr * WORD_SIZE as u32;
                let page_idx = info.get_page_index(addr);
                let entry_addr = info.get_page_entry_addr(page_idx);
                debug!("  ram_read: 0x{addr:08x}, op: {op:?}, entry_addr: 0x{entry_addr:08x}");
                panic!("Memory read before page in: 0x{addr:08x}");
            }
        }
        let addr = addr * WORD_SIZE as u32;
        let word = self.memory.load_u32(addr);
        // debug!("ram_read: 0x{addr:08X} -> 0x{word:08X}");
        split_word8(word)
    }

    fn ram_write(
        &mut self,
        addr: BabyBearElem,
        data: (BabyBearElem, BabyBearElem, BabyBearElem, BabyBearElem),
        op: BabyBearElem,
    ) -> Result<()> {
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
        // debug!("ram_write> 0x{:08X} <= 0x{:08X}", addr, data);
        self.memory.store_u32(addr, data);
        if self.trace_enabled {
            let addr = addr as usize;
            if addr >= SYSTEM.start() && addr < SYSTEM.end() {
                self.handler.on_trace(TraceEvent::RegisterSet {
                    reg: (addr - SYSTEM.start()) / WORD_SIZE,
                    value: data,
                })?
            } else {
                self.handler.on_trace(TraceEvent::MemorySet {
                    addr: addr as u32,
                    value: data,
                })?
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

    fn syscall_init(&mut self, cycle: usize) -> Result<()> {
        assert!(self.syscall_out_data.is_empty());
        let to_guest_words = self.memory.load_register(REG_A1);

        let name_ptr = self.memory.load_register(REG_A2);

        let name = self.memory.load_string(name_ptr)?;
        debug!("SYS_IO[{cycle}] Guest requests {to_guest_words} words back");
        let mut to_guest_buf = vec![0u32; to_guest_words as usize];

        self.memory.cur_cycle = cycle;
        self.syscall_out_regs = self
            .handler
            .on_txrx(&self.memory, &name, &mut to_guest_buf)?;
        trace!("SYS_IO[{cycle}] (a0, a1): {:?}", self.syscall_out_regs);
        trace!("SYS_IO[{cycle}] data sent to guest: {to_guest_buf:?}");
        self.syscall_out_data = to_guest_buf.into();
        Ok(())
    }

    fn syscall_body(&mut self) -> Result<u32> {
        Ok(self.syscall_out_data.pop_front().unwrap_or_default())
    }

    fn syscall_fini(&mut self) -> Result<(u32, u32)> {
        debug!(
            "Syscall complete, output registers: {:?}",
            self.syscall_out_regs
        );
        Ok(self.syscall_out_regs)
    }

    fn decode(&self, word: u32) -> OpCode {
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
                    (0x0, 0x0) => OpCode::with_major_minor("ECALL", MajorType::ECall, 0),
                    (0x1, 0x0) => OpCode::with_major_minor("EBREAK", MajorType::ECall, 1),
                    _ => unreachable!(),
                },
                _ => unreachable!(),
            },
            _ => panic!("Illegal opcode: 0b{opcode:07b}"),
        }
    }
}

pub struct RV32Executor<'a, H: HostHandler> {
    pub executor: Executor<BabyBear, CircuitImpl, MachineContext<'a, H>>,
}

impl<'a, H: HostHandler> RV32Executor<'a, H> {
    pub fn new(
        circuit: &'static CircuitImpl,
        image: Rc<RefCell<MemoryImage>>,
        pc: u32,
        host: &'a mut H,
        segment_limit_po2: usize,
    ) -> Self {
        let mut io = vec![BabyBearElem::INVALID; CircuitImpl::OUTPUT_SIZE];
        debug!("run> pc: 0x{:08x}", pc);

        // initialize PC
        let pc_bytes = pc.to_le_bytes();
        for i in 0..WORD_SIZE {
            io[i] = (pc_bytes[i] as u32).into();
        }

        // initialize ImageID
        let image_id = image.borrow().get_root();
        let image_id = image_id.as_words();
        for i in 0..DIGEST_WORDS {
            let bytes = image_id[i].to_le_bytes();
            for j in 0..WORD_SIZE {
                io[(i + 1) * WORD_SIZE + j] = (bytes[j] as u32).into();
            }
        }

        let segment_limit = 2_usize.pow(segment_limit_po2 as u32);
        let machine = MachineContext::new(host, Rc::clone(&image), segment_limit);
        let executor = Executor::new(circuit, machine, 13, MAX_CYCLES_PO2, &io);
        Self { executor }
    }

    #[tracing::instrument(skip_all)]
    pub fn run(&mut self) -> Result<(usize, u32, u32)> {
        let loader = Loader::new();
        let cycles = loader.load(|chunk, fini| self.executor.step(chunk, fini))?;
        self.executor.finalize();
        Ok((
            cycles,
            self.executor.handler.exit_code,
            self.executor.handler.last_pc,
        ))
    }
}
