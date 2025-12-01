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
    sync::Once,
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
const QUOTA_OFFSET: usize = offset_of!(JitContext, quota);
const RAM_OFFSET: usize = offset_of!(JitContext, ram);
const REGISTERS_OFFSET: usize = offset_of!(JitContext, registers);
// const PGTBL_OFFSET: usize = offset_of!(JitContext, page_table);
const GUEST_RAM_SIZE: usize = 1 << 32; // 4GB

const QUOTA_REL_OFFSET: i32 = QUOTA_OFFSET as i32 - REGISTERS_OFFSET as i32;
const RAM_REL_OFFSET: i32 = RAM_OFFSET as i32 - REGISTERS_OFFSET as i32;
// const PGTBL_REL_OFFSET: i32 = PGTBL_OFFSET as i32 - REGISTERS_OFFSET as i32;

const NUM_PAGES: usize = 4 * 1024 * 1024;
const INVALID_IDX: u32 = 0;

// This is visible to the generated x64 code.
#[repr(C)]
struct JitContext {
    pc: u32,
    quota: u32,
    ram: *mut u8,
    pub(crate) registers: [u32; REG_MAX],
}

struct Machine {
    ctx: JitContext,
    text: BTreeMap<u32, u32>,
}

impl Machine {
    fn new(program: Program) -> Result<Self> {
        let ram = unsafe {
            let addr = mmap(
                ptr::null_mut(),
                GUEST_RAM_SIZE,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE | MAP_ANON,
                -1,
                0,
            );
            if addr == MAP_FAILED {
                bail!("mmap failed");
            }
            addr as *mut u8
        };

        tracing::debug!("ram: {ram:?}");
        let ram_slice = unsafe { std::slice::from_raw_parts_mut(ram, GUEST_RAM_SIZE) };
        let word_slice: &mut [u32] = bytemuck::cast_slice_mut(ram_slice);
        for (&addr, &word) in program.image.iter() {
            word_slice[addr as usize / 4] = word;
        }

        let page_table = vec![INVALID_IDX; NUM_PAGES];
        Ok(Self {
            ctx: JitContext {
                pc: program.entry,
                quota: MAX_QUOTA,
                ram,
                registers: [0; REG_MAX],
            },
            text: program.image,
        })
    }

    fn fetch(&mut self) -> Instruction {
        Instruction::new(self.text[&self.ctx.pc])
    }

    fn next(&mut self) {
        self.ctx.pc += WORD_SIZE as u32;
    }
}

impl JitContext {
    fn load_register(&self, idx: usize) -> Result<u32> {
        Ok(self.registers[idx])
    }

    fn store_register(&mut self, idx: usize, word: u32) -> Result<()> {
        self.registers[idx] = word;
        Ok(())
    }

    fn dump_registers(&self) {
        for (i, reg) in self.registers.iter().enumerate() {
            tracing::debug!("x{i}: {reg:#010x}");
        }
    }
}

struct Translator {
    asm: Assembler,
    pub(crate) machine: Machine,
    labels: BTreeMap<u32, AssemblyOffset>,
    fixups: BTreeMap<u32, Vec<AssemblyOffset>>,
}

const HOST_WORD_SIZE: usize = usize::BITS as usize / 8;
const HOST_PAGE_SIZE: usize = 4096;

const CALLEE_REGISTERS: &[GPR] = &[GPR::RBX, GPR::RBP, GPR::R12, GPR::R13, GPR::R14, GPR::R15];
const STACK_SPACE: usize = CALLEE_REGISTERS.len() * HOST_WORD_SIZE;

impl Translator {
    fn new(program: Program) -> Result<Self> {
        Ok(Self {
            asm: emit::make_assembler()?,
            machine: Machine::new(program)?,
            labels: Default::default(),
            fixups: Default::default(),
        })
    }

    fn jit_block(&mut self) -> Result<AssemblyOffset> {
        tracing::debug!("jit_block: {:#10x}", self.machine.ctx.pc);
        let start = self.asm.offset();

        loop {
            let offset = self.asm.offset();
            self.labels.insert(self.machine.ctx.pc, offset);
            self.process_fixups(offset)?;

            let insn = self.machine.fetch();
            // self.step_prologue();
            if let Some(terminal) = self.dispatch(insn)? {
                break;
            }
            // self.step_epilogue();
            self.machine.next();
        }

        tracing::debug!("commit");
        self.asm.commit()?;
        self.dump(start);

        Ok(start)
    }

    fn process_fixups(&mut self, offset: AssemblyOffset) -> Result<()> {
        if let Some(fixups) = self.fixups.remove(&self.machine.ctx.pc) {
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
        let mut state = VmState {
            guest_base: self.machine.ctx.ram,
            guest_size: GUEST_RAM_SIZE,
            fault_addr: ptr::null_mut(),
            gregs: [0; 23],
            have_pending_fault: false,
        };
        VM_STATE.with(|tls| {
            *tls.borrow_mut() = Some(state);
        });

        if unsafe {
            mprotect(
                self.machine.ctx.ram as *mut c_void,
                GUEST_RAM_SIZE,
                PROT_NONE,
            )
        } != 0
        {
            bail!("mprotect(PROT_NONE) failed");
        }

        Ok(())
    }

    fn jit_loop(&mut self) -> Result<Terminal> {
        ensure_segv_handler_installed();

        self.dump(self.enter_offset()?);
        loop {
            let retval = if let Some(&offset) = self.labels.get(&self.machine.ctx.pc) {
                tracing::debug!("existing label: {:#10x}", self.machine.ctx.pc);
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
                    self.machine.ctx.quota = MAX_QUOTA;
                }
            }
            // self.machine.dump_registers();
            tracing::trace!("next pc: {pc:#10x}");
            self.machine.ctx.pc = pc;
        }
    }

    fn enter_block(&mut self, offset: AssemblyOffset) -> Result<u64> {
        tracing::debug!("enter_block: {offset:x?}");
        let enter = self.enter_offset()?;
        let reader = self.asm.reader();
        let exe = reader.lock();
        let enter_ptr = exe.ptr(enter);
        let block_ptr = exe.ptr(offset);
        let registers_ptr = self.machine.ctx.registers.as_mut_ptr();
        tracing::trace!(
            "enter_ptr: {enter_ptr:?}, block_ptr: {block_ptr:?}, registers_ptr: {registers_ptr:?}"
        );
        let enter: extern "C" fn(*const u8, *mut u32) -> u64 =
            unsafe { std::mem::transmute(enter_ptr) };
        Ok(enter(block_ptr, registers_ptr))
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

// Per-thread VM state. In your real code you'll add instr metadata, cycles, etc.
#[derive(Debug)]
struct VmState {
    guest_base: *mut u8,
    guest_size: usize,
    fault_addr: *mut u8,
    gregs: [i64; 23],
    have_pending_fault: bool,
}

// Thread-local pointer to VmState for the current thread.
// Only threads running guest code set this.
thread_local! {
    pub static VM_STATE: RefCell<Option<VmState>> = const { RefCell::new(None) };
}

// Install-once guard for SIGSEGV handler.
static INSTALL_SEGV_ONCE: Once = Once::new();

// Store old handler to chain for non-guest faults, if you want to be fancy later.
// static mut OLD_SEGV: sigaction = unsafe { std::mem::zeroed() };

/// Ensure SIGSEGV handler is installed once.
fn ensure_segv_handler_installed() {
    INSTALL_SEGV_ONCE.call_once(install_segv_handler);
}

/// Install a SA_SIGINFO SIGSEGV handler using libc::sigaction.
fn install_segv_handler() {
    extern "C" fn handler(sig: c_int, info: *mut siginfo_t, uctx: *mut c_void) {
        unsafe { segv_trampoline(sig, info, uctx) };
    }

    let mut sa: sigaction = unsafe { std::mem::zeroed() };
    sa.sa_sigaction = handler as usize;
    sa.sa_flags = SA_SIGINFO;

    unsafe { sigemptyset(&mut sa.sa_mask) };

    // let mut old: sigaction = unsafe { std::mem::zeroed() };
    let res = unsafe { sigaction(libc::SIGSEGV, &sa, ptr::null_mut()) };
    if res != 0 {
        panic!("sigaction(SIGSEGV) failed");
    }

    // unsafe {
    //     OLD_SEGV = old;
    // }

    tracing::info!("SIGSEGV handler installed");
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
        buf[2 + i] = HEX[((value >> shift) & 0xf) as usize];
    }
    let _ = unsafe { libc::write(2, buf.as_ptr() as *const c_void, buf.len()) };
    debug_str("\n");
}

/// The raw SIGSEGV handler. Very tiny and async-signal-safe:
/// - identify if it's our guest
/// - stash fault info in per-thread VmState
/// - patch RIP to jit_fault_handler
unsafe fn segv_trampoline(sig: c_int, info: *mut siginfo_t, uctx: *mut c_void) {
    VM_STATE.with_borrow_mut(|vm_state| {
        if let Some(vm_state) = vm_state {
            let fault_addr = unsafe { (&*info).si_addr() } as *mut u8;

            let base = vm_state.guest_base as usize;
            let end = base + vm_state.guest_size;
            let fault = fault_addr as usize;

            if fault < base || fault >= end {
                // Fault outside guest memory: not ours.
                // debug_str("out of range\n");
                // debug_hex("fault: ", fault);
                // debug_hex("base: ", base);
                // debug_hex("end: ", end);
                default_handler(sig);
                return;
            }

            let uctx = unsafe { &mut *(uctx as *mut ucontext_t) };
            vm_state.have_pending_fault = true;
            vm_state.fault_addr = fault_addr;
            vm_state.gregs = uctx.uc_mcontext.gregs;

            unsafe extern "C" {
                fn jit_fault_handler();
            }

            uctx.uc_mcontext.gregs[libc::REG_RIP as usize] =
                jit_fault_handler as usize as libc::greg_t;

            // let page_base = (fault_addr as usize & !(HOST_PAGE_SIZE - 1)) as *mut c_void;
            // if unsafe { mprotect(page_base, HOST_PAGE_SIZE, PROT_READ | PROT_WRITE) } != 0 {
            //     tracing::error!("mprotect failed");
            //     default_handler(sig);
            // }
        } else {
            default_handler(sig);
        }
    });
}

fn default_handler(sig: c_int) {
    unsafe {
        libc::signal(sig, libc::SIG_DFL);
        libc::raise(sig);
    }
}

#[unsafe(no_mangle)]
extern "C" fn jit_fault_slow() -> *const i64 {
    tracing::info!("page fault!");

    VM_STATE.with_borrow(|vm_state| {
        let vm_state = vm_state.as_ref().unwrap();
        tracing::debug!("vm_state: {vm_state:#x?}");

        let page_base = (vm_state.fault_addr as usize & !(HOST_PAGE_SIZE - 1)) as *mut c_void;
        let page_idx = (page_base as usize - vm_state.guest_base as usize) / 1024;
        tracing::info!("page_idx: {page_idx:#08x}");

        if unsafe { mprotect(page_base, HOST_PAGE_SIZE, PROT_READ | PROT_WRITE) } != 0 {
            tracing::error!("mprotect failed");
        }

        vm_state.gregs.as_ptr()
    })
}
