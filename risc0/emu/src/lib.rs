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

mod memory;
mod page;
pub mod rv32im;

#[cfg(test)]
mod tests;

#[cfg(target_arch = "x86_64")]
pub mod x86_64;

#[cfg(target_arch = "x86_64")]
use x86_64::emit;

#[cfg(target_arch = "aarch64")]
pub mod aarch64;

#[cfg(target_arch = "aarch64")]
use aarch64::emit;

use std::{
    arch::asm,
    cell::{Cell, RefCell},
    collections::{BTreeMap, BTreeSet, HashMap},
    mem::offset_of,
    ptr,
    sync::{Arc, Once, OnceLock},
};

use anyhow::{Result, anyhow, bail};
use derive_more::Debug;
use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
};

#[cfg(target_arch = "x86_64")]
use dynasmrt::x64::Assembler;

#[cfg(target_arch = "aarch64")]
use dynasmrt::aarch64::Assembler;

use enum_map::EnumMap;
use libc::{
    MAP_ANON, MAP_FAILED, MAP_PRIVATE, PROT_NONE, PROT_READ, PROT_WRITE, SA_SIGINFO, c_int, c_void,
    mmap, mprotect, sigaction, sigemptyset, siginfo_t, ucontext_t,
};
use risc0_binfmt::{ByteAddr, MemoryImage, Page, Program, WordAddr};
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
    QuotaExhausted,
}

impl Terminal {
    fn from_u32(word: u32) -> Option<Self> {
        match word {
            0 => Some(Self::Jump),
            1 => Some(Self::Break),
            2 => Some(Self::Trap),
            3 => Some(Self::QuotaExhausted),
            _ => None,
        }
    }
}

const GUEST_RAM_SIZE: usize = 1 << 32; // 4GB

const JITCTX_QUOTA_OFFSET: i32 = offset_of!(JitContext, quota) as i32;
const JITCTX_REGISTERS_OFFSET: i32 = offset_of!(JitContext, registers) as i32;
const JITCTX_CURRENT_TAG_OFFSET: i32 = offset_of!(JitContext, current_tag) as i32;
const JITCTX_PAGE_TABLE_OFFSET: i32 = offset_of!(JitContext, page_table) as i32;
const JITCTX_LOAD_PAGE_MISS_OFFSET: i32 = offset_of!(JitContext, jit_load_page_miss) as i32;
const JITCTX_STORE_PAGE_MISS_OFFSET: i32 = offset_of!(JitContext, jit_store_page_miss) as i32;
const JITCTX_BLOCK_COUNT_TABLE_OFFSET: i32 =
    offset_of!(JitContext, jit_block_count_table_ptr) as i32;

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
    quota: u64,
    registers: [u32; REG_MAX],
    registers_dirty: bool,
    current_tag: u16,
    page_table: *mut PageSlot,
    jit_load_page_miss: extern "C" fn(ctx: *mut JitContext, vaddr: u32) -> *const u8,
    jit_store_page_miss: extern "C" fn(ctx: *mut JitContext, vaddr: u32) -> *const u8,
    ram: HostMemory,
    mode: RegisterMode,

    jit_block_count_table: Vec<u32>,
    jit_block_count_table_ptr: *mut u32,
}

#[derive(Clone, Debug, Default)]
pub struct BlockInfo {
    pub op_counts: EnumMap<RvOp, u32>,
    #[debug("0x{start_pc:x}")]
    pub start_pc: u32,
    #[debug("0x{end_pc:x}")]
    pub end_pc: u32,
}

#[derive(Clone, Debug, Default)]
pub struct BlockRun {
    pub info: BlockInfo,
    pub count: u32,
}

pub struct Translator {
    asm: Assembler,
    pub ctx: JitContext,
    labels: BTreeMap<u32, AssemblyOffset>,
    fixups: BTreeMap<u32, Vec<AssemblyOffset>>,
    block_infos: BTreeMap<AssemblyOffset, BlockInfo>,
    jit_block_id_to_offset: BTreeMap<usize, AssemblyOffset>,
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
            block_infos: Default::default(),
            jit_block_id_to_offset: Default::default(),
        })
    }

    fn fetch(&mut self) -> Instruction {
        Instruction::new(self.ctx.load_u32(self.ctx.pc))
    }

    fn next(&mut self) {
        self.ctx.pc += WORD_SIZE as u32;
    }

    fn jit_block(
        &mut self,
        point_calculator: impl Fn(&BlockInfo) -> u64,
    ) -> Result<AssemblyOffset> {
        let start = self.asm.offset();
        let start_pc = self.ctx.pc;

        tracing::trace!("jit_block: {:#10x}: offset = {start:?}", self.ctx.pc);

        let mut fixup_locs = vec![];

        loop {
            let offset = self.asm.offset();
            fixup_locs.push((offset, self.ctx.pc));

            let insn = self.fetch();
            let (op, terminal) = self.dispatch(insn)?;

            for addr in start.0..=offset.0 {
                let info = self
                    .block_infos
                    .entry(AssemblyOffset(addr))
                    .or_insert_with(|| BlockInfo {
                        op_counts: Default::default(),
                        start_pc: self.ctx.pc,
                        end_pc: self.ctx.pc,
                    });
                if matches!(terminal, Some(Terminal::Break)) {
                    info.end_pc = self.ctx.pc;
                } else {
                    if let Some(op) = op {
                        info.op_counts[op] += 1;
                    }
                    info.end_pc = self.ctx.pc + WORD_SIZE as u32;
                }
            }
            if terminal.is_some() {
                break;
            }

            self.next();
        }

        tracing::trace!("commit");
        self.asm.commit()?;

        for (offset, target_pc) in fixup_locs {
            self.process_fixups(offset, target_pc, &point_calculator)?;
        }

        let id = self.ctx.new_jit_block_id();
        self.jit_block_id_to_offset.insert(id, start);

        let dest_prologue_offset = self.asm.offset();
        let points = point_calculator(self.block_infos.get(&start).unwrap());
        tracing::trace!("jit block points = {points}");

        self.block_prologue(id as u32, points);
        self.jump(start);

        self.labels.insert(start_pc, dest_prologue_offset);

        self.asm.commit()?;

        // self.dump(start);

        Ok(dest_prologue_offset)
    }

    fn add_jump_entry(
        &mut self,
        jmp_offset: AssemblyOffset,
        dest_offset: AssemblyOffset,
        target_pc: u32,
        point_calculator: impl Fn(&BlockInfo) -> u64,
    ) -> Result<()> {
        let id = self.ctx.new_jit_block_id();
        self.jit_block_id_to_offset.insert(id, dest_offset);

        let dest_prologue_offset = self.asm.offset();
        let points = point_calculator(self.block_infos.get(&dest_offset).unwrap());
        self.block_prologue(id as u32, points);
        self.jump(dest_offset);

        self.labels.insert(target_pc, dest_prologue_offset);

        tracing::trace!(
            "fixup: {jmp_offset:x?} -> {dest_offset:x?} prologue offset: {dest_prologue_offset:?}"
        );

        emit::patch_jump(&mut self.asm, jmp_offset, dest_prologue_offset)?;

        Ok(())
    }

    fn process_fixups(
        &mut self,
        dest_offset: AssemblyOffset,
        target_pc: u32,
        point_calculator: impl Fn(&BlockInfo) -> u64,
    ) -> Result<()> {
        if let Some(fixups) = self.fixups.remove(&target_pc) {
            for jmp_offset in fixups {
                self.add_jump_entry(jmp_offset, dest_offset, target_pc, &point_calculator)?;
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
        Ok(())
    }

    pub fn jit_one_inner(
        &mut self,
        point_calculator: impl Fn(&BlockInfo) -> u64,
    ) -> Result<(Terminal, Vec<BlockRun>)> {
        let retval = if let Some(&offset) = self.labels.get(&self.ctx.pc) {
            tracing::trace!("existing label: {:#10x}", self.ctx.pc);
            self.enter_block(offset)?
        } else {
            let offset = self.jit_block(point_calculator)?;
            self.enter_block(offset)?
        };

        self.ctx.registers_dirty = true;

        let terminal =
            Terminal::from_u32((retval >> 32) as u32).ok_or_else(|| anyhow!("Invalid terminal"))?;

        let pc = (retval & 0xffffffff) as u32;
        self.ctx.pc = pc;
        tracing::trace!("jit block ran; new pc = {pc:x}; terminal = {terminal:?}");

        let mut runs = vec![];
        for (id, count) in self.ctx.jit_block_count_table.iter_mut().enumerate() {
            if *count > 0 {
                let offset = self.jit_block_id_to_offset.get(&id).unwrap();
                let info = self.block_infos.get(offset).unwrap();
                runs.push(BlockRun {
                    info: info.clone(),
                    count: *count,
                });
                *count = 0;
            }
        }

        assert!(!runs.is_empty());

        tracing::trace!(
            "jit_one runs: {:?}",
            runs.iter().map(|r| r.count).collect::<Vec<_>>()
        );

        Ok((terminal, runs))
    }

    pub fn jit_one(
        &mut self,
        quota: u64,
        point_calculator: impl Fn(&BlockInfo) -> u64,
    ) -> Result<(Terminal, Vec<BlockRun>)> {
        tracing::trace!("jit_one quota = {quota}");

        let mut runs_total = vec![];
        self.ctx.quota = quota;

        loop {
            let (terminal, runs) = self.jit_one_inner(&point_calculator)?;
            runs_total.extend(runs);

            if !matches!(terminal, Terminal::Jump) {
                self.ctx.write_registers();
                return Ok((terminal, runs_total));
            }
        }
    }

    fn jit_loop(&mut self) -> Result<Terminal> {
        self.ctx.quota = u64::MAX;
        loop {
            let (terminal, _) = self.jit_one_inner(|_| 0)?;

            match terminal {
                Terminal::Jump => (),
                Terminal::Break | Terminal::Trap | Terminal::QuotaExhausted => return Ok(terminal),
            }
        }
    }

    fn enter_block(&mut self, offset: AssemblyOffset) -> Result<u64> {
        tracing::trace!("enter_block: {offset:x?}");
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

        Ok(retval)
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
            registers_dirty: false,
            current_tag: 1,
            page_table: ram.slots.as_mut_ptr(),
            jit_load_page_miss: JitContext::jit_load_page_miss_trampoline,
            jit_store_page_miss: JitContext::jit_store_page_miss_trampoline,
            ram,
            mode: RegisterMode::User,
            quota: 0,
            jit_block_count_table: vec![],
            jit_block_count_table_ptr: std::ptr::null_mut(),
        };
        s.load_registers();
        s
    }

    pub fn new_jit_block_id(&mut self) -> usize {
        let new_id = self.jit_block_count_table.len();
        self.jit_block_count_table.push(0);
        self.jit_block_count_table_ptr = self.jit_block_count_table.as_mut_ptr();
        new_id
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
        self.registers_dirty = false;
    }

    fn write_registers_to_image(&self, mut addr: u32, image: &mut MemoryImage) {
        for i in 0..self.registers.len() {
            let value = self.registers[i];
            image.set_word(ByteAddr(addr).waddr(), value);
            addr += WORD_SIZE as u32;
        }
    }

    fn load_registers_from_addr(&mut self, mut addr: u32) {
        for i in 0..self.registers.len() {
            let value = self.load_u32_internal(addr);
            self.registers[i] = value;
            addr += WORD_SIZE as u32;
        }
        self.registers_dirty = false;
    }

    extern "C" fn jit_load_page_miss_trampoline(ctx: *mut JitContext, page_idx: u32) -> *const u8 {
        unsafe { &mut *ctx }.jit_load_page_miss(page_idx)
    }

    extern "C" fn jit_store_page_miss_trampoline(ctx: *mut JitContext, page_idx: u32) -> *const u8 {
        unsafe { &mut *ctx }.jit_store_page_miss(page_idx)
    }

    #[inline]
    fn jit_load_page_miss(&mut self, page_idx: u32) -> *const u8 {
        tracing::trace!("jit_load_page_miss: {page_idx:#010x}");
        let page = self
            .ram
            .ensure_page_read_for_segment(self.current_tag, page_idx);
        page.as_ptr()
    }

    #[inline]
    fn jit_store_page_miss(&mut self, page_idx: u32) -> *const u8 {
        tracing::trace!("jit_store_page_miss: {page_idx:#010x}");
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
        unsafe {
            let ptr = page.as_ptr().add(offset) as *const u32;
            u32::from_le(ptr.read_unaligned())
        }
    }

    pub fn load_u32(&mut self, addr: u32) -> u32 {
        let reg_base = match self.mode {
            RegisterMode::User => USER_REGS_ADDR,
            RegisterMode::Machine => MACHINE_REGS_ADDR,
        };

        if addr >= reg_base && addr < reg_base + REG_MAX as u32 && self.registers_dirty {
            panic!("read from dirty register");
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

        if addr >= reg_base && addr < reg_base + REG_MAX as u32 && self.registers_dirty {
            panic!("write to dirty register");
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
        // add two for csr touches
        self.ram.touched_pages + 2
    }

    /// clear all tracked pages
    pub fn paging_checkpoint(&mut self) {
        self.ram.touched_pages = 0;
        self.current_tag += 1;
        assert!(self.current_tag < PAGE_WRITABLE_FLAG, "too many segments");
    }

    /// the full memory image containing all pages
    pub fn full_image(&self) -> MemoryImage {
        let mut image = self.ram.full_image();

        match self.mode {
            RegisterMode::User => {
                self.write_registers_to_image(USER_REGS_ADDR, &mut image);
            }
            RegisterMode::Machine => {
                self.write_registers_to_image(MACHINE_REGS_ADDR, &mut image);
            }
        }

        image
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
