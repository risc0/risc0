// Copyright 2025 RISC Zero, Inc.
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
#[cfg(test)]
mod tests;

use std::{
    arch::asm,
    cell::{Cell, RefCell},
    collections::BTreeMap,
    mem::offset_of,
    ptr,
    sync::{Arc, Once},
};

use anyhow::{Result, anyhow, bail};
use dynasmrt::{
    AssemblyOffset, DynasmApi as _, DynasmError, DynasmLabelApi,
    components::StaticLabel,
    relocations::{Relocation as _, RelocationSize},
    x64::{Assembler, X64Relocation},
};
use libc::{
    MAP_ANON, MAP_FAILED, MAP_PRIVATE, PROT_NONE, PROT_READ, PROT_WRITE, SA_SIGINFO, c_int, c_void,
    mmap, mprotect, sigaction, sigemptyset, siginfo_t, ucontext_t,
};
use risc0_binfmt::Program;

use crate::rv32im::{Instruction, REG_MAX, RvOp, WORD_SIZE};

#[repr(u32)]
#[derive(Copy, Clone, Debug, Eq, PartialEq, Ord, PartialOrd, Hash)]
enum Terminal {
    Jump,
    Break,
    Trap,
    Split,
}

impl Terminal {
    fn from_u32(word: u32) -> Option<Self> {
        match word {
            0 => Some(Self::Jump),
            1 => Some(Self::Break),
            2 => Some(Self::Trap),
            3 => Some(Self::Split),
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

const MAX_QUOTA: u32 = 1_000_000;
const GUEST_RAM_SIZE: usize = 1 << 32; // 4GB

const QUOTA_OFFSET: usize = offset_of!(JitContext, quota);
const REGISTERS_OFFSET: usize = offset_of!(JitContext, registers);
const TLB_OFFSET: usize = offset_of!(JitContext, tlb);
const TLB_MISS_OFFSET: usize = offset_of!(JitContext, tlb_miss);

const NUM_PAGES: usize = 4 * 1024 * 1024;
const INVALID_IDX: u32 = 0;

const HOST_WORD_SIZE: usize = usize::BITS as usize / 8;
const HOST_PAGE_SIZE: usize = 4096;
const GUEST_PAGE_SIZE: usize = 1024;

const CALLEE_REGISTERS: &[GPR] = &[GPR::RBX, GPR::RBP, GPR::R12, GPR::R13, GPR::R14, GPR::R15];
const STACK_SPACE: usize = CALLEE_REGISTERS.len() * HOST_WORD_SIZE;

const PAGE_SHIFT: u32 = 10;
const PAGE_SIZE: usize = 1 << PAGE_SHIFT;
const PAGE_OFFSET_MASK: u32 = PAGE_SIZE as u32 - 1;
const TLB_SIZE: usize = 1024;
const TLB_MASK: u32 = TLB_SIZE as u32 - 1;
const TLB_ENTRY_SHIFT: u32 = std::mem::size_of::<TlbEntry>().ilog2();
const TLB_TAG_OFFSET: usize = offset_of!(TlbEntry, tag);
const TLB_HOST_PAGE_OFFSET: usize = offset_of!(TlbEntry, host_page);
const TLB_VALID_TAG_MASK: u32 = 1 << (32 - 1);

type Page = [u8; PAGE_SIZE];

// This is visible to the generated x64 code.
#[repr(C)]
struct JitContext {
    pc: u32,
    quota: u32,
    satp: u32,
    registers: [u32; REG_MAX],
    tlb_miss: extern "C" fn(ctx: *mut JitContext, vaddr: u32) -> *const u8,
    tlb: Tlb,
    phys_pages: Vec<Option<Arc<Page>>>,
}

#[repr(C)]
#[derive(Clone, Copy, Default)]
struct TlbEntry {
    pub tag: u32,
    pub host_page: *const u8,
}

#[repr(C)]
struct Tlb {
    pub entries: [TlbEntry; TLB_SIZE],
}

struct Translator {
    asm: Assembler,
    ctx: JitContext,
    labels: BTreeMap<u32, AssemblyOffset>,
    fixups: BTreeMap<u32, Vec<AssemblyOffset>>,
}

impl Translator {
    fn new(program: Program) -> Result<Self> {
        let mut ctx = JitContext {
            pc: program.entry,
            satp: 0,
            quota: MAX_QUOTA,
            registers: [0; REG_MAX],
            tlb: Tlb::default(),
            tlb_miss: JitContext::tlb_miss_trampoline,
            phys_pages: vec![None; NUM_PAGES],
        };

        for (addr, word) in program.image {
            ctx.store_u32(addr, word)?;
        }

        Ok(Self {
            asm: emit::make_assembler()?,
            ctx,
            labels: Default::default(),
            fixups: Default::default(),
        })
    }

    fn fetch(&mut self) -> Instruction {
        Instruction::new(self.ctx.load_u32(self.ctx.pc).unwrap())
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
            // self.step_prologue();
            if let Some(terminal) = self.dispatch(insn)? {
                break;
            }
            // self.step_epilogue();
            self.next();
        }

        tracing::debug!("commit");
        self.asm.commit()?;
        self.dump(start);

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

    fn jit_loop(&mut self) -> Result<Terminal> {
        // ensure_segv_handler_installed();

        self.dump(self.enter_offset()?);
        loop {
            let retval = if let Some(&offset) = self.labels.get(&self.ctx.pc) {
                tracing::debug!("existing label: {:#10x}", self.ctx.pc);
                self.enter_block(offset)?
            } else {
                let offset = self.jit_block()?;
                self.enter_block(offset)?
            };

            let terminal = Terminal::from_u32((retval >> 32) as u32)
                .ok_or_else(|| anyhow!("Invalid terminal"))?;
            let pc = (retval & 0xffffffff) as u32;
            match terminal {
                Terminal::Jump => (),
                Terminal::Break | Terminal::Trap => return Ok(terminal),
                Terminal::Split => {
                    tracing::debug!("split");
                    self.ctx.quota = MAX_QUOTA;
                }
            }
            // self.dump_registers();
            tracing::trace!("next pc: {pc:#10x}");
            self.ctx.pc = pc;
        }
    }

    fn enter_block(&mut self, offset: AssemblyOffset) -> Result<u64> {
        tracing::debug!("enter_block: {offset:x?}");
        let enter = self.enter_offset()?;
        let reader = self.asm.reader();
        let exe = reader.lock();
        let enter_ptr = exe.ptr(enter);
        let block_ptr = exe.ptr(offset);
        let ctx_ptr = &mut self.ctx as *mut JitContext;
        tracing::trace!("enter: {enter_ptr:?}, block: {block_ptr:?}, ctx: {ctx_ptr:?}");
        let enter: extern "C" fn(*const u8, *mut JitContext) -> u64 =
            unsafe { std::mem::transmute(enter_ptr) };
        Ok(enter(block_ptr, ctx_ptr))
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

impl Default for Tlb {
    fn default() -> Self {
        Self {
            entries: [TlbEntry::default(); TLB_SIZE],
        }
    }
}

impl JitContext {
    extern "C" fn tlb_miss_trampoline(ctx: *mut JitContext, vaddr: u32) -> *const u8 {
        unsafe { &mut *ctx }.tlb_miss(vaddr)
    }

    #[inline]
    fn tlb_miss(&mut self, vaddr: u32) -> *const u8 {
        tracing::info!("tlb_miss: {vaddr:#010x}");

        let vpn = vaddr >> PAGE_SHIFT;
        let index = vpn & TLB_MASK;
        tracing::debug!("vpn: {vpn:#08x}, index: {index:#08x}");
        let host_page_ptr = self.ensure_phys_page(vpn as usize);

        let entry = &mut self.tlb.entries[index as usize];
        entry.tag = vpn | TLB_VALID_TAG_MASK;
        entry.host_page = host_page_ptr;

        host_page_ptr

        // let paddr = match self.translate_vaddr_sv32(vaddr) {
        //     Ok(paddr) => paddr,
        //     Err(_) => panic!("page fault in tlb_lookup"),
        // };

        // let page_idx = paddr >> PAGE_SHIFT;
        // let host_page_ptr = self.ensure_phys_page(page_idx as usize);

        // let entry = &mut self.tlb.entries[index as usize];
        // let tag = vpn & TLB_VALID_MASK;
        // entry.tag = tag;
        // entry.host_page = host_page_ptr;

        // host_page_ptr
    }

    fn translate_vaddr_sv32(&self, vaddr: u32) -> Result<u32> {
        let root_ppn = self.satp & 0x003f_ffff;
        let vpn0 = (vaddr >> 12) & 0x3ff;
        let vpn1 = (vaddr >> 22) & 0x3ff;

        let mut ppn = root_ppn;
        let mut level = 1;
        for vpn in [vpn1, vpn0] {
            let pte_addr = (ppn << 12) + (vpn * 4);
            let pte = self.load_u32(pte_addr)?;

            let valid = (pte & 0x1) != 0;
            let readable = (pte & 0x2) != 0;
            let writable = (pte & 0x4) != 0;
            let executable = (pte & 0x8) != 0;

            if !valid || (!readable && writable) {
                bail!("Invalid PTE");
            }

            let is_leaf = readable || writable;
            if is_leaf {
                if level != 0 {
                    bail!("Unsupported superpage");
                }

                let ppn = (pte >> 10) & 0x003f_ffff;
                let page_offset = vaddr & PAGE_OFFSET_MASK;
                let paddr = (ppn << 12) | page_offset;
                return Ok(paddr);
            } else {
                ppn = (pte >> 10) & 0x003f_ffff;
                level -= 1;
            }
        }

        Err(anyhow!("Invalid vaddr"))
    }

    fn ensure_phys_page(&mut self, page_idx: usize) -> *const u8 {
        tracing::debug!("ensure_phys_page: {page_idx:#08x}");

        if page_idx >= self.phys_pages.len() {
            panic!("phys_pages too small");
        }

        let page = &mut self.phys_pages[page_idx];
        if page.is_none() {
            *page = Some(Arc::new([0; PAGE_SIZE]));
        }

        page.as_ref().unwrap().as_ptr()
    }

    fn load_u32(&self, paddr: u32) -> Result<u32> {
        let page_idx = (paddr >> PAGE_SHIFT) as usize;
        let offset = (paddr & PAGE_OFFSET_MASK) as usize;
        if page_idx >= self.phys_pages.len() {
            return Err(anyhow!("Invalid page_idx"));
        }

        let Some(ref page) = self.phys_pages[page_idx] else {
            return Err(anyhow!("Empty page"));
        };

        let end = offset + WORD_SIZE;
        if end > page.len() {
            bail!("load_u32 crosses page boundary");
        }

        let bytes: [u8; WORD_SIZE] = page[offset..end]
            .try_into()
            .expect("slice is exactly 4 bytes");
        Ok(u32::from_le_bytes(bytes))
    }

    fn store_u32(&mut self, paddr: u32, word: u32) -> Result<()> {
        let page_idx = (paddr >> PAGE_SHIFT) as usize;
        let offset = (paddr & PAGE_OFFSET_MASK) as usize;
        if page_idx >= self.phys_pages.len() {
            return Err(anyhow!("Invalid page_idx"));
        }

        let page = &mut self.phys_pages[page_idx];
        if page.is_none() {
            *page = Some(Arc::new([0; PAGE_SIZE]));
        }

        let page = page.as_mut().unwrap();
        let page = Arc::get_mut(page).ok_or_else(|| anyhow!("Page isn't unique"))?;
        let end = offset + WORD_SIZE;
        if end > page.len() {
            bail!("store_u32 crosses page boundary");
        }

        let bytes = word.to_le_bytes();
        page[offset..end].copy_from_slice(&bytes);

        Ok(())
    }

    fn dump_registers(&self) {
        for (i, reg) in self.registers.iter().enumerate() {
            tracing::debug!("x{i}: {reg:#010x}");
        }
    }
}
