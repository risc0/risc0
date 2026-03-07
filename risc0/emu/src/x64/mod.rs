// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![allow(unused)]

mod emit;
mod memory;
mod page;
#[cfg(test)]
mod tests;

use std::{
    arch::asm,
    cell::{Cell, RefCell},
    collections::{BTreeMap, BTreeSet, HashMap},
    mem::offset_of,
    ptr,
    sync::{Arc, Once, OnceLock},
};

use anyhow::{Result, anyhow, bail};
use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
    x64::{Assembler, X64Relocation},
};
use enum_map::EnumMap;
use libc::{
    MAP_ANON, MAP_FAILED, MAP_PRIVATE, PROT_NONE, PROT_READ, PROT_WRITE, SA_SIGINFO, c_int, c_void,
    mmap, mprotect, sigaction, sigemptyset, siginfo_t, ucontext_t,
};
use risc0_binfmt::{MemoryImage, Page, Program, WordAddr};
use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

use self::memory::{HostMemory, PageBytes, PageSlot};
use self::page::{PAGE_OFFSET_MASK, PAGE_SHIFT, PAGE_SIZE, PAGE_WRITABLE_FLAG};
use crate::rv32im::{Instruction, REG_MAX, RvOp, WORD_SIZE};

pub const MACHINE_REGS_ADDR: u32 = 0xffff_0000;
pub const USER_REGS_ADDR: u32 = 0xffff_0080;

#[repr(u32)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
pub enum Terminal {
    Jump,
    Break,
    Trap,
}

impl Terminal {
    fn from_u32(word: u32) -> Option<Self> {
        match word {
            0 => Some(Self::Jump),
            1 => Some(Self::Break),
            2 => Some(Self::Trap),
            _ => None,
        }
    }
}

/// General-purpose registers.
#[repr(u8)]
#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum GPR {
    RAX = 0,
    RCX = 1,
    RDX = 2,
    RBX = 3,
    RSP = 4,
    RBP = 5,
    RSI = 6,
    RDI = 7,
    R8 = 8,
    R9 = 9,
    R10 = 10,
    R11 = 11,
    R12 = 12,
    R13 = 13,
    R14 = 14,
    R15 = 15,
}

impl From<GPR> for u8 {
    fn from(val: GPR) -> Self {
        val as u8
    }
}

#[allow(clippy::upper_case_acronyms)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum Loc {
    GPR(GPR),
    Memory(GPR, i32),
    Imm8(u8),
    Imm32(u32),
    Zero,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Size {
    S8,
    S16,
    S32,
}

#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum Extend {
    None,
    Sign,
    Zero,
}

fn map_reg_to_loc(idx: u32) -> Loc {
    // SystemV C ABI calling conventions
    // callee: rbx, rsp, rbp, r12, r13, r14, r15
    // caller: rax, rdi, rsi, rdx, rcx, r8, r9, r10, r11
    // reserved:
    //   rax: scratch/tmp
    //   rbx: ptr to registers mapped in memory
    //   r15: guest base address
    REGISTER_MAPPING[idx as usize]
}

impl Instruction {
    fn rd_loc(&self) -> Loc {
        map_reg_to_loc(self.rd)
    }

    fn rs1_loc(&self) -> Loc {
        map_reg_to_loc(self.rs1)
    }

    fn rs2_loc(&self) -> Loc {
        map_reg_to_loc(self.rs2)
    }
}

// reserved: rax, rbx, rcx, rdx, r15
// used:     rdi, rsi, rbp, r8, r9, r10, r11, r12, r13, r14
// not used: rsp

const REGISTER_MAPPING: [Loc; REG_MAX] = [
    Loc::Zero,                                    // x0  (zero)
    Loc::GPR(GPR::R13),                           // x1  (ra)
    Loc::Memory(GPR::RBX, 2 * WORD_SIZE as i32),  // x2  (sp)
    Loc::Memory(GPR::RBX, 3 * WORD_SIZE as i32),  // x3  (gp)
    Loc::Memory(GPR::RBX, 4 * WORD_SIZE as i32),  // x4  (tp)
    Loc::GPR(GPR::R14),                           // x5  (t0)
    Loc::Memory(GPR::RBX, 6 * WORD_SIZE as i32),  // x6  (t1)
    Loc::Memory(GPR::RBX, 7 * WORD_SIZE as i32),  // x7  (t2)
    Loc::GPR(GPR::RBP),                           // x8  (s0)
    Loc::Memory(GPR::RBX, 9 * WORD_SIZE as i32),  // x9  (s1)
    Loc::GPR(GPR::RDI),                           // x10 (a0)
    Loc::GPR(GPR::RSI),                           // x11 (a1)
    Loc::GPR(GPR::R8),                            // x12 (a2)
    Loc::GPR(GPR::R9),                            // x13 (a3)
    Loc::GPR(GPR::R10),                           // x14 (a4)
    Loc::GPR(GPR::R11),                           // x15 (a5)
    Loc::GPR(GPR::R12),                           // x16 (a6)
    Loc::Memory(GPR::RBX, 17 * WORD_SIZE as i32), // x17 (a7)
    Loc::Memory(GPR::RBX, 18 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 19 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 20 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 21 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 22 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 23 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 24 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 25 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 26 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 27 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 28 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 29 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 30 * WORD_SIZE as i32),
    Loc::Memory(GPR::RBX, 31 * WORD_SIZE as i32),
];

// #[allow(clippy::identity_op)]
// const REGISTER_MAPPING: [Loc; REG_MAX] = [
//     Loc::Zero,                                    // x0  (zero)
//     Loc::Memory(GPR::RBX, 1 * WORD_SIZE as i32),  // x1  (ra)
//     Loc::Memory(GPR::RBX, 2 * WORD_SIZE as i32),  // x2  (sp)
//     Loc::Memory(GPR::RBX, 3 * WORD_SIZE as i32),  // x3  (gp)
//     Loc::Memory(GPR::RBX, 4 * WORD_SIZE as i32),  // x4  (tp)
//     Loc::Memory(GPR::RBX, 5 * WORD_SIZE as i32),  // x5  (t0)
//     Loc::Memory(GPR::RBX, 6 * WORD_SIZE as i32),  // x6  (t1)
//     Loc::Memory(GPR::RBX, 7 * WORD_SIZE as i32),  // x7  (t2)
//     Loc::Memory(GPR::RBX, 8 * WORD_SIZE as i32),  // x8  (s0)
//     Loc::Memory(GPR::RBX, 9 * WORD_SIZE as i32),  // x9  (s1)
//     Loc::Memory(GPR::RBX, 10 * WORD_SIZE as i32), // x10 (a0)
//     Loc::Memory(GPR::RBX, 11 * WORD_SIZE as i32), // x11 (a1)
//     Loc::Memory(GPR::RBX, 12 * WORD_SIZE as i32), // x12 (a2)
//     Loc::Memory(GPR::RBX, 13 * WORD_SIZE as i32), // x13 (a3)
//     Loc::Memory(GPR::RBX, 14 * WORD_SIZE as i32), // x14 (a4)
//     Loc::Memory(GPR::RBX, 15 * WORD_SIZE as i32), // x15 (a5)
//     Loc::Memory(GPR::RBX, 16 * WORD_SIZE as i32), // x16 (a6)
//     Loc::Memory(GPR::RBX, 17 * WORD_SIZE as i32), // x17 (a7)
//     Loc::Memory(GPR::RBX, 18 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 19 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 20 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 21 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 22 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 23 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 24 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 25 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 26 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 27 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 28 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 29 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 30 * WORD_SIZE as i32),
//     Loc::Memory(GPR::RBX, 31 * WORD_SIZE as i32),
// ];

const GUEST_RAM_SIZE: usize = 1 << 32; // 4GB

const JITCTX_REGISTERS_OFFSET: i32 = offset_of!(JitContext, registers) as i32;
const JITCTX_CURRENT_TAG_OFFSET: i32 = offset_of!(JitContext, current_tag) as i32;
const JITCTX_PAGE_TABLE_OFFSET: i32 = offset_of!(JitContext, page_table) as i32;
const JITCTX_LOAD_PAGE_MISS_OFFSET: i32 = offset_of!(JitContext, jit_load_page_miss) as i32;
const JITCTX_STORE_PAGE_MISS_OFFSET: i32 = offset_of!(JitContext, jit_store_page_miss) as i32;

const HOST_WORD_SIZE: usize = (usize::BITS / u8::BITS) as usize;
const HOST_PAGE_SIZE: usize = 4096;

#[derive(Copy, Clone, PartialEq, Eq)]
#[repr(u32)]
enum RegisterMode {
    User = 0,
    Machine = 1,
}

impl RegisterMode {
    fn from_u32(v: u32) -> Self {
        match v {
            0 => Self::User,
            1 => Self::Machine,
            v => panic!("unknown mode {v}"),
        }
    }
}

// This is visible to the generated x64 code.
#[repr(C)]
pub struct JitContext {
    pub pc: u32,
    registers: [u32; REG_MAX],
    current_tag: u16,
    page_table: *mut PageSlot,
    jit_load_page_miss: extern "C" fn(ctx: *mut JitContext, vaddr: u32) -> *const u8,
    jit_store_page_miss: extern "C" fn(ctx: *mut JitContext, vaddr: u32) -> *const u8,
    ram: HostMemory,
    mode: RegisterMode,
}

#[derive(Clone, Default)]
pub struct BlockInfo {
    pub op_counts: EnumMap<RvOp, u32>,
    pub start_pc: u32,
    pub end_pc: u32,
}

pub struct Translator {
    asm: Assembler,
    pub ctx: JitContext,
    labels: BTreeMap<u32, AssemblyOffset>,
    fixups: BTreeMap<u32, Vec<AssemblyOffset>>,
    instr_counts: BTreeMap<AssemblyOffset, EnumMap<RvOp, u32>>,
}

impl Translator {
    pub fn new(program: Program) -> Result<Self> {
        tracing::trace!("JIT Translation new");

        let mut ctx = JitContext::new(program.entry);

        for (page_idx, page) in program.image.pages {
            ctx.ram.add_page(page_idx, page);
        }

        Ok(Self {
            asm: emit::make_assembler()?,
            ctx,
            labels: Default::default(),
            fixups: Default::default(),
            instr_counts: BTreeMap::new(),
        })
    }

    fn fetch(&mut self) -> Instruction {
        Instruction::new(self.ctx.load_u32(self.ctx.pc))
    }

    fn next(&mut self) {
        self.ctx.pc += WORD_SIZE as u32;
    }

    fn jit_block(&mut self) -> Result<AssemblyOffset> {
        tracing::debug!("jit_block: {:#10x}", self.ctx.pc);
        let start = self.asm.offset();

        loop {
            let offset = self.asm.offset();
            self.labels.insert(self.ctx.pc, offset);
            self.process_fixups(offset)?;

            let insn = self.fetch();
            let (op, terminal) = self.dispatch(insn)?;

            for addr in start.0..=offset.0 {
                let counts = self.instr_counts.entry(AssemblyOffset(addr)).or_default();
                if let Some(op) = op {
                    counts[op] += 1;
                }
            }
            if terminal {
                break;
            }

            self.next();
        }

        tracing::debug!("commit");
        self.asm.commit()?;
        // self.dump(start);

        Ok(start)
    }

    fn process_fixups(&mut self, offset: AssemblyOffset) -> Result<()> {
        if let Some(fixups) = self.fixups.remove(&self.ctx.pc) {
            let kind = X64Relocation::from_size(RelocationSize::DWord);
            for jmp_offset in fixups {
                tracing::debug!("fixup: {jmp_offset:x?} -> {offset:x?}");
                self.asm.alter(|modifier| {
                    // goto the rel32 operand of the source jump instruction
                    modifier.goto(AssemblyOffset(jmp_offset.0 + 1));
                    // compute the rel32 offset from the end of the jump instruction
                    let offset = offset.0 as isize - WORD_SIZE as isize;
                    // perform the actual patch
                    modifier.bare_relocation(offset as usize, 0, 0, kind.clone());
                })?;
            }
        }
        Ok(())
    }

    fn enter_offset(&self) -> Result<AssemblyOffset, DynasmError> {
        self.asm
            .labels()
            .resolve_static(&StaticLabel::global("enter"))
    }

    fn resume(&mut self) -> Result<()> {
        // TODO: clear state
        Ok(())
    }

    pub fn jit_one(&mut self) -> Result<(Terminal, BlockInfo)> {
        let start_pc = self.ctx.pc;

        let (retval, op_counts) = if let Some(&offset) = self.labels.get(&self.ctx.pc) {
            tracing::debug!("existing label: {:#10x}", self.ctx.pc);
            self.enter_block(offset)?
        } else {
            let offset = self.jit_block()?;
            self.enter_block(offset)?
        };

        let terminal =
            Terminal::from_u32((retval >> 32) as u32).ok_or_else(|| anyhow!("Invalid terminal"))?;
        let end_pc = self.ctx.pc;

        let pc = (retval & 0xffffffff) as u32;
        self.ctx.pc = pc;
        tracing::trace!("jit block ran; new pc = {pc:x}; terminal = {terminal:?}");

        let info = BlockInfo {
            op_counts,
            start_pc,
            end_pc,
        };

        Ok((terminal, info))
    }

    fn jit_loop(&mut self) -> Result<Terminal> {
        // self.dump(self.enter_offset()?);
        loop {
            let (terminal, _) = self.jit_one()?;

            match terminal {
                Terminal::Jump => (),
                Terminal::Break | Terminal::Trap => return Ok(terminal),
            }
        }
    }

    fn enter_block(&mut self, offset: AssemblyOffset) -> Result<(u64, EnumMap<RvOp, u32>)> {
        tracing::debug!("enter_block: {offset:x?}");
        let counts = self.instr_counts.get(&offset).unwrap().clone();
        let enter = self.enter_offset()?;
        let reader = self.asm.reader();
        let exe = reader.lock();
        let enter_ptr = exe.ptr(enter);
        let block_ptr = exe.ptr(offset);
        let ctx_ptr = &mut self.ctx as *mut JitContext;
        tracing::trace!("enter: {enter_ptr:?}, block: {block_ptr:?}, ctx: {ctx_ptr:?}");
        let enter: extern "C" fn(*const u8, *mut JitContext) -> u64 =
            unsafe { std::mem::transmute(enter_ptr) };
        let retval = enter(block_ptr, ctx_ptr);

        Ok((retval, counts))
    }

    fn disasm(&self, start: AssemblyOffset, print_pos: bool) -> Vec<String> {
        use iced_x86::Formatter;

        let reader = self.asm.reader();
        let data = reader.lock();

        let mut fmt = iced_x86::NasmFormatter::new();
        let mut decoder = iced_x86::Decoder::new(64, &data[start.0..], 0);

        let mut lines = Vec::new();
        while decoder.can_decode() {
            let pos = start.0 + decoder.position();
            let insn = decoder.decode();
            let mut line = String::new();
            fmt.format(&insn, &mut line);
            if print_pos {
                // lines.push(format!(
                //     "{pos:#04x}: {line} {:02x?}",
                //     &data[pos..pos + insn.len()]
                // ));
                lines.push(format!("{pos:#04x}: {line}"));
            } else {
                lines.push(line);
            }
        }
        lines
    }

    fn dump(&self, start: AssemblyOffset) {
        let lines = self.disasm(start, true);
        for line in lines {
            tracing::debug!("{line}");
        }
    }
}

impl JitContext {
    fn new(pc: u32) -> Self {
        let mut ram = HostMemory::new();
        let mut s = Self {
            pc,
            registers: [0; REG_MAX],
            current_tag: 1,
            page_table: ram.slots.as_mut_ptr(),
            jit_load_page_miss: JitContext::jit_load_page_miss_trampoline,
            jit_store_page_miss: JitContext::jit_store_page_miss_trampoline,
            ram,
            mode: RegisterMode::User,
        };
        s.load_registers();
        s
    }

    pub fn set_mode(&mut self, mode: u32) {
        let mode = RegisterMode::from_u32(mode);

        if self.mode == mode {
            return;
        }

        self.write_registers();

        self.mode = mode;

        self.load_registers();
    }

    pub fn get_mode(&self) -> u32 {
        self.mode as u32
    }

    fn write_registers(&mut self) {
        match self.mode {
            RegisterMode::User => {
                self.write_registers_to_addr(USER_REGS_ADDR);
            }
            RegisterMode::Machine => {
                self.write_registers_to_addr(MACHINE_REGS_ADDR);
            }
        }
    }

    fn load_registers(&mut self) {
        match self.mode {
            RegisterMode::User => {
                self.load_registers_from_addr(USER_REGS_ADDR);
            }
            RegisterMode::Machine => {
                self.load_registers_from_addr(MACHINE_REGS_ADDR);
            }
        }
    }

    fn write_registers_to_addr(&mut self, mut addr: u32) {
        for i in 0..self.registers.len() {
            let value = self.registers[i];
            self.store_u32_internal(addr, value);
            addr += WORD_SIZE as u32;
        }
    }

    fn load_registers_from_addr(&mut self, mut addr: u32) {
        for i in 0..self.registers.len() {
            let value = self.load_u32_internal(addr);
            self.registers[i] = value;
            addr += WORD_SIZE as u32;
        }
    }

    extern "C" fn jit_load_page_miss_trampoline(ctx: *mut JitContext, page_idx: u32) -> *const u8 {
        unsafe { &mut *ctx }.jit_load_page_miss(page_idx)
    }

    extern "C" fn jit_store_page_miss_trampoline(ctx: *mut JitContext, page_idx: u32) -> *const u8 {
        unsafe { &mut *ctx }.jit_store_page_miss(page_idx)
    }

    #[inline]
    fn jit_load_page_miss(&mut self, page_idx: u32) -> *const u8 {
        tracing::info!("jit_load_page_miss: {page_idx:#08x}");
        let page = self
            .ram
            .ensure_page_read_for_segment(self.current_tag, page_idx);
        page.as_ptr()
    }

    #[inline]
    fn jit_store_page_miss(&mut self, page_idx: u32) -> *const u8 {
        tracing::info!("jit_store_page_miss: {page_idx:#010x}");
        let page = self
            .ram
            .ensure_page_write_for_segment(self.current_tag, page_idx);
        page.as_ptr()
    }

    fn load_u32_internal(&mut self, addr: u32) -> u32 {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;

        let page = self
            .ram
            .ensure_page_read_for_segment(self.current_tag, page_idx);

        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);
        let word = unsafe {
            let ptr = page.as_ptr().add(offset) as *const u32;
            u32::from_le(ptr.read_unaligned())
        };

        word
    }

    pub fn load_u32(&mut self, addr: u32) -> u32 {
        let reg_base = match self.mode {
            RegisterMode::User => USER_REGS_ADDR,
            RegisterMode::Machine => MACHINE_REGS_ADDR,
        };

        if addr >= reg_base && addr < reg_base + REG_MAX as u32 {
            panic!("read from register being used");
        }

        self.load_u32_internal(addr)
    }

    pub fn load_register(&mut self, base_waddr: u32, idx: usize) -> u32 {
        let requested_mode = if base_waddr == USER_REGS_ADDR / WORD_SIZE as u32 {
            RegisterMode::User
        } else if base_waddr == MACHINE_REGS_ADDR / WORD_SIZE as u32 {
            RegisterMode::Machine
        } else {
            unimplemented!("unknown register address {base_waddr:?}");
        };

        if self.mode == requested_mode {
            self.registers[idx]
        } else {
            let addr = (base_waddr + idx as u32) * WORD_SIZE as u32;
            self.load_u32(addr)
        }
    }

    fn store_u32_internal(&mut self, addr: u32, word: u32) {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;

        let page = self
            .ram
            .ensure_page_write_for_segment(self.current_tag, page_idx);
        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);
        unsafe {
            let ptr = page.as_mut_ptr().add(offset) as *mut u32;
            ptr.write_unaligned(word.to_le());
        }
    }

    pub fn store_u32(&mut self, addr: u32, word: u32) {
        let reg_base = match self.mode {
            RegisterMode::User => USER_REGS_ADDR,
            RegisterMode::Machine => MACHINE_REGS_ADDR,
        };

        if addr >= reg_base && addr < reg_base + REG_MAX as u32 {
            panic!("write to register being used");
        }

        self.store_u32_internal(addr, word);
    }

    pub fn store_register(&mut self, base_waddr: u32, idx: usize, word: u32) {
        let requested_mode = if base_waddr == USER_REGS_ADDR / WORD_SIZE as u32 {
            RegisterMode::User
        } else if base_waddr == MACHINE_REGS_ADDR / WORD_SIZE as u32 {
            RegisterMode::Machine
        } else {
            unimplemented!("unknown register address {base_waddr:?}");
        };

        if self.mode == requested_mode {
            self.registers[idx] = word;
        } else {
            let addr = (base_waddr + idx as u32) * WORD_SIZE as u32;
            self.store_u32(addr, word);
        }
    }

    pub fn peek_page(&mut self, page_idx: u32) -> &PageBytes {
        todo!()
    }

    fn dump_registers(&self) {
        for (i, reg) in self.registers.iter().enumerate() {
            tracing::debug!("x{i}: {reg:#010x}");
        }
    }

    /// sparse MemoryImage containing all touched pages since last checkpoint
    pub fn partial_image(&mut self) -> BTreeMap<u32, Page> {
        self.write_registers();
        self.ram.partial_image(self.current_tag)
    }

    /// the indexes of all the touched pages since last checkpoint
    pub fn page_indexes(&self) -> BTreeSet<u32> {
        self.ram.page_indexes(self.current_tag)
    }

    /// the count of all touched pages since last checkpoint
    pub fn touched_pages(&self) -> u64 {
        self.ram.touched_pages
    }

    /// clear all tracked pages
    pub fn paging_checkpoint(&mut self) {
        self.ram.touched_pages = 0;
        self.current_tag += 1;
        assert!(self.current_tag < PAGE_WRITABLE_FLAG, "too many segments");
    }

    /// the full memory image containing all pages
    pub fn full_image(&self) -> MemoryImage {
        self.ram.full_image()
    }
}

#[allow(unused)]
#[inline(always)]
fn debug_str(s: &str) {
    // Best effort; ignore errors.
    let _ = unsafe { libc::write(2, s.as_ptr() as *const c_void, s.len()) };
}

#[allow(unused)]
#[inline(always)]
fn debug_hex(label: &str, value: usize) {
    debug_str(label);
    const HEX: &[u8; 16] = b"0123456789abcdef";
    let mut buf = [0u8; 18]; // "0x" + 16 hex digits
    buf[0] = b'0';
    buf[1] = b'x';
    for i in 0..16 {
        let shift = (15 - i) * 4;
        buf[2 + i] = HEX[((value >> shift) & 0xf)];
    }
    let _ = unsafe { libc::write(2, buf.as_ptr() as *const c_void, buf.len()) };
    debug_str("\n");
}
