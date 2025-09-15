// Copyright 2025 RISC Zero, Inc.
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

#![allow(dead_code)]

use core::{alloc::Layout, ptr::NonNull};
use no_std_strings::{str_format, str256};
use rlsf::Tlsf;

use crate::constants::*;
// host_argc, host_argv
use crate::host_calls::{host_get_cycle, host_log, host_terminate};
use crate::softfloat::{
    emulate_fp_instruction, emulate_fp_load_store, get_fcsr, get_fflags, get_frm, init_softfloat,
    set_fcsr, set_fflags, set_frm,
};

// Debug configuration - set to true to enable debug prints, false to disable
pub const DEBUG_ENABLED: bool = cfg!(debug_assertions);

// Debug print macro that avoids str_format evaluation when debug is disabled
#[macro_export]
macro_rules! debug_print {
    ($($arg:tt)*) => {
        if DEBUG_ENABLED {
            let msg = str_format!(str256, $($arg)*);
            print(&msg);
        }
    };
}

macro_rules! kprint {
    ($($arg:tt)*) => {
            let msg = str_format!(str256, $($arg)*);
            print(&msg);
    };
}

// Debug print macro for simple string literals (no formatting)
macro_rules! debug_print_simple {
    ($msg:literal) => {
        if DEBUG_ENABLED {
            print($msg);
        }
    };
}

#[macro_export]
macro_rules! kpanic {
    ($($arg:tt)*) => {
        kprint!($($arg)*);
        host_terminate(1, 0);
        #[allow(unreachable_code)]
        loop {}
    };
}

// Embedded device tree blob (DTB) for RISC-V system
#[allow(dead_code)]
const DTB_DATA: [u8; 952] = [
    0xd0, 0x0d, 0xfe, 0xed, 0x00, 0x00, 0x03, 0xb8, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x02, 0xf4,
    0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xc4, 0x00, 0x00, 0x02, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x1b, 0x7a, 0x6b, 0x76, 0x6d,
    0x2c, 0x72, 0x76, 0x33, 0x32, 0x2d, 0x6e, 0x6f, 0x6d, 0x6d, 0x75, 0x00, 0x72, 0x69, 0x73, 0x63,
    0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x26,
    0x7a, 0x6b, 0x56, 0x4d, 0x20, 0x52, 0x56, 0x33, 0x32, 0x20, 0x4e, 0x4f, 0x4d, 0x4d, 0x55, 0x20,
    0x28, 0x53, 0x42, 0x49, 0x2d, 0x74, 0x69, 0x6d, 0x65, 0x72, 0x20, 0x2b, 0x20, 0x68, 0x76, 0x63,
    0x20, 0x63, 0x6f, 0x6e, 0x73, 0x6f, 0x6c, 0x65, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x63, 0x68, 0x6f, 0x73, 0x65, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x33,
    0x00, 0x00, 0x00, 0x2c, 0x65, 0x61, 0x72, 0x6c, 0x79, 0x70, 0x72, 0x69, 0x6e, 0x74, 0x6b, 0x20,
    0x65, 0x61, 0x72, 0x6c, 0x79, 0x63, 0x6f, 0x6e, 0x3d, 0x73, 0x62, 0x69, 0x20, 0x63, 0x6f, 0x6e,
    0x73, 0x6f, 0x6c, 0x65, 0x3d, 0x68, 0x76, 0x63, 0x30, 0x20, 0x69, 0x6e, 0x69, 0x74, 0x3d, 0x2f,
    0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01,
    0x63, 0x70, 0x75, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x35, 0x00, 0x98, 0x96, 0x80, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x63, 0x70, 0x75, 0x40,
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x1b,
    0x72, 0x69, 0x73, 0x63, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x48, 0x63, 0x70, 0x75, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0a,
    0x00, 0x00, 0x00, 0x58, 0x72, 0x76, 0x33, 0x32, 0x69, 0x6d, 0x61, 0x66, 0x64, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x62, 0x6e, 0x6f, 0x6e, 0x65,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x6b,
    0x6f, 0x6b, 0x61, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x69, 0x6e, 0x74, 0x65,
    0x72, 0x72, 0x75, 0x70, 0x74, 0x2d, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6c, 0x65, 0x72,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x1b,
    0x72, 0x69, 0x73, 0x63, 0x76, 0x2c, 0x63, 0x70, 0x75, 0x2d, 0x69, 0x6e, 0x74, 0x63, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x72, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x6d, 0x65, 0x6d, 0x6f,
    0x72, 0x79, 0x40, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x00, 0x48, 0x6d, 0x65, 0x6d, 0x6f, 0x72, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x54, 0x00, 0x01, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x61, 0x63, 0x6c, 0x69, 0x6e, 0x74, 0x2d, 0x6d,
    0x74, 0x69, 0x6d, 0x65, 0x72, 0x40, 0x63, 0x32, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x1b, 0x72, 0x69, 0x73, 0x63,
    0x76, 0x2c, 0x61, 0x63, 0x6c, 0x69, 0x6e, 0x74, 0x2d, 0x6d, 0x74, 0x69, 0x6d, 0x65, 0x72, 0x00,
    0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x54, 0xc2, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xa0,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x00, 0x00, 0xb4, 0x00, 0x98, 0x96, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x09, 0x23, 0x61, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x2d, 0x63, 0x65, 0x6c,
    0x6c, 0x73, 0x00, 0x23, 0x73, 0x69, 0x7a, 0x65, 0x2d, 0x63, 0x65, 0x6c, 0x6c, 0x73, 0x00, 0x63,
    0x6f, 0x6d, 0x70, 0x61, 0x74, 0x69, 0x62, 0x6c, 0x65, 0x00, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x00,
    0x62, 0x6f, 0x6f, 0x74, 0x61, 0x72, 0x67, 0x73, 0x00, 0x74, 0x69, 0x6d, 0x65, 0x62, 0x61, 0x73,
    0x65, 0x2d, 0x66, 0x72, 0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x79, 0x00, 0x64, 0x65, 0x76, 0x69,
    0x63, 0x65, 0x5f, 0x74, 0x79, 0x70, 0x65, 0x00, 0x72, 0x65, 0x67, 0x00, 0x72, 0x69, 0x73, 0x63,
    0x76, 0x2c, 0x69, 0x73, 0x61, 0x00, 0x6d, 0x6d, 0x75, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x00, 0x73,
    0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x23, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x72, 0x75, 0x70, 0x74,
    0x2d, 0x63, 0x65, 0x6c, 0x6c, 0x73, 0x00, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x72, 0x75, 0x70, 0x74,
    0x2d, 0x63, 0x6f, 0x6e, 0x74, 0x72, 0x6f, 0x6c, 0x6c, 0x65, 0x72, 0x00, 0x70, 0x68, 0x61, 0x6e,
    0x64, 0x6c, 0x65, 0x00, 0x69, 0x6e, 0x74, 0x65, 0x72, 0x72, 0x75, 0x70, 0x74, 0x73, 0x2d, 0x65,
    0x78, 0x74, 0x65, 0x6e, 0x64, 0x65, 0x64, 0x00, 0x63, 0x6c, 0x6f, 0x63, 0x6b, 0x2d, 0x66, 0x72,
    0x65, 0x71, 0x75, 0x65, 0x6e, 0x63, 0x79, 0x00,
];
#[allow(dead_code)]
const fn get_dtb_data() -> &'static [u8] {
    &DTB_DATA
}

#[derive(Clone, Copy)]
enum Err {
    NoMem = -12,
    Inval = -22,
}

static mut BRK: u32 = USER_HEAP_START_ADDR as u32;

type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;
static mut HEAP: Heap = Heap::new();

#[cfg(target_arch = "riscv32")]
core::arch::global_asm!(include_str!("kernel.s"));

#[cfg(target_arch = "riscv32")]
#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    unsafe { core::arch::asm!("unimp", options(noreturn)) }
}

pub fn get_ureg(idx: usize) -> u32 {
    // x0 (register 0) should always return 0
    if idx == 0 {
        return 0;
    }
    unsafe { USER_REGS_PTR.add(idx).read() }
}

pub fn set_ureg(idx: usize, word: u32) {
    // Guard against writing to x0 (register 0) - it should always remain 0
    if idx == 0 {
        return;
    }
    unsafe { USER_REGS_PTR.add(idx).write_volatile(word) };
}

// Supervisor CSR access functions
// These read/write from the shadow register area at 0xffff_5000

fn get_stvec() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(STVEC_OFFSET) }
}

fn set_stvec(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(STVEC_OFFSET) = value;
    }
}

fn get_sscratch() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SSCRATCH_OFFSET) }
}

fn set_sscratch(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SSCRATCH_OFFSET) = value;
    }
}

fn get_sdeleg() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SDELEG_OFFSET) }
}

fn set_sdeleg(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SDELEG_OFFSET) = value;
    }
}

fn get_sie() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SIE_OFFSET) }
}

fn set_sie(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SIE_OFFSET) = value;
    }
}

fn get_sip() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SIP_OFFSET) }
}

fn set_sip(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SIP_OFFSET) = value;
    }
}

fn get_scounteren() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SCOUNTEREN_OFFSET) }
}

fn set_scounteren(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SCOUNTEREN_OFFSET) = value;
    }
}

fn get_sstatus() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SSTATUS_OFFSET) }
}

fn set_sstatus(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SSTATUS_OFFSET) = value;
    }
}

fn get_sepc() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SEPC_OFFSET) }
}

fn set_sepc(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SEPC_OFFSET) = value;
    }
}

fn get_stval() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(STVAL_OFFSET) }
}

fn set_stval(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(STVAL_OFFSET) = value;
    }
}

fn get_scause() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SCAUSE_OFFSET) }
}

fn set_scause(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SCAUSE_OFFSET) = value;
    }
}

fn get_senvcfg() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(SENVCFG_OFFSET) }
}

fn set_senvcfg(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(SENVCFG_OFFSET) = value;
    }
}

fn get_ilrsc() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(ILRSC_OFFSET) }
}

fn set_ilrsc(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(ILRSC_OFFSET) = value;
    }
}

fn get_ilrsc_set() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(ILRSC_SET_OFFSET) }
}

fn set_ilrsc_set(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(ILRSC_SET_OFFSET) = value;
    }
}

// Invalidate LR/SC reservation (call this when other memory operations occur)
#[allow(dead_code)]
fn invalidate_lrsc_reservation() {
    set_ilrsc_set(0);
}

// CSR (Control and Status Register) emulation
unsafe fn emulate_csr_instruction(insn: u32, mepc: usize) -> ! {
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let csr_addr = (insn >> 20) & 0xfff;

    debug_print!(
        "Emulating CSR instruction at PC: {:#010x}, funct3={}, rd={}, rs1={}, csr={:#03x}",
        mepc,
        funct3,
        rd,
        rs1,
        csr_addr
    );

    // Log CSR operations for debugging
    let operation = match funct3 {
        0x0 => "invalid",
        0x1 => "csrrw",
        0x2 => "csrrs",
        0x3 => "csrrc",
        0x5 => "csrrwi",
        0x6 => "csrrsi",
        0x7 => "csrrci",
        _ => "unknown",
    };

    debug_print!(
        "CSR {} {}: csr=0x{:03x}, rd=x{}, rs1=x{} (PC=0x{:08x})\n",
        operation,
        if funct3 >= 0x5 {
            "immediate"
        } else {
            "register"
        },
        csr_addr,
        rd,
        rs1,
        mepc
    );

    // Handle floating point CSR operations
    match csr_addr {
        0x001 => {
            // fflags - Floating point exception flags
            match funct3 {
                0x1 => {
                    // csrrw (read and write) - fsflags rs1, fflags
                    let current_flags = get_fflags();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fflags(rs1_value);
                    }
                    set_ureg(rd as usize, current_flags);

                    debug_print!(
                        "fsflags: read flags {:#02x}, wrote {:#02x}",
                        current_flags,
                        if rs1 != 0 { get_ureg(rs1 as usize) } else { 0 }
                    );
                }
                0x2 => {
                    // csrrs (read and set) - fsflags rs1, fflags
                    let current_flags = get_fflags();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fflags(current_flags | rs1_value);
                    }
                    set_ureg(rd as usize, current_flags);

                    debug_print!("fsflags: read flags {:#02x}", current_flags);
                }
                0x3 => {
                    // csrrc (read and clear) - fsflags rs1, fflags
                    let current_flags = get_fflags();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fflags(current_flags & !rs1_value);
                    }
                    set_ureg(rd as usize, current_flags);

                    debug_print!(
                        "fsflags: read flags {:#02x}, cleared {:#02x}",
                        current_flags,
                        if rs1 != 0 { get_ureg(rs1 as usize) } else { 0 }
                    );
                }
                0x5 => {
                    // csrrwi (read and write immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrwi, rs1 field contains the immediate
                    set_fflags(imm);
                    set_ureg(rd as usize, current_flags);

                    debug_print!(
                        "fsflags: read flags {:#02x}, wrote immediate {:#02x}",
                        current_flags,
                        imm
                    );
                }
                0x6 => {
                    // csrrsi (read and set immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrsi, rs1 field contains the immediate
                    set_fflags(current_flags | imm);
                    set_ureg(rd as usize, current_flags);

                    debug_print!(
                        "fsflags: read flags {:#02x}, set immediate {:#02x}",
                        current_flags,
                        imm
                    );
                }
                0x7 => {
                    // csrrci (read and clear immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrci, rs1 field contains the immediate
                    set_fflags(current_flags & !imm);
                    set_ureg(rd as usize, current_flags);

                    debug_print!(
                        "fsflags: read flags {:#02x}, clear immediate {:#02x}",
                        current_flags,
                        imm
                    );
                }
                _ => {
                    kpanic!("Unsupported fflags funct3: {}", funct3);
                }
            }
        }
        0x002 => {
            // frm - Floating point rounding mode
            match funct3 {
                0x2 => {
                    // csrrs (read and set) - fsrm rs1, frm
                    let current_frm = get_frm();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_frm(current_frm | rs1_value);
                    }
                    set_ureg(rd as usize, current_frm);

                    debug_print!("fsrm: read frm {:#02x}", current_frm);
                }
                0x5 => {
                    // csrrwi (read and write immediate) - fsrm rs1, frm
                    let current_frm = get_frm();
                    let immediate_value = rs1; // rs1 field contains the immediate value
                    set_frm(immediate_value);
                    set_ureg(rd as usize, current_frm);

                    debug_print!(
                        "fsrm: csrrwi frm {:#02x} -> {:#02x}",
                        current_frm,
                        immediate_value
                    );
                }
                _ => {
                    kpanic!("Unsupported frm funct3: {}", funct3);
                }
            }
        }
        0x003 => {
            // fcsr - Floating point control and status register
            match funct3 {
                0x1 => {
                    // csrrw (read and write) - fscsr rs1, fcsr
                    let current_fcsr = get_fcsr();
                    let rs1_value = get_ureg(rs1 as usize);
                    set_fcsr(rs1_value);
                    set_ureg(rd as usize, current_fcsr);

                    debug_print!(
                        "fscsr: csrrw fcsr {:#02x} -> {:#02x}",
                        current_fcsr,
                        rs1_value
                    );
                }
                0x2 => {
                    // csrrs (read and set) - fscsr rs1, fcsr
                    let current_fcsr = get_fcsr();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fcsr(current_fcsr | rs1_value);
                    }
                    set_ureg(rd as usize, current_fcsr);

                    debug_print!("fscsr: read fcsr {:#02x}", current_fcsr);
                }
                0x5 => {
                    // csrrwi (read and write immediate) - fscsr rs1, fcsr
                    let current_fcsr = get_fcsr();
                    let immediate_value = rs1; // rs1 field contains the immediate value
                    set_fcsr(immediate_value);
                    set_ureg(rd as usize, current_fcsr);

                    debug_print!(
                        "fscsr: csrrwi fcsr {:#02x} -> {:#02x}",
                        current_fcsr,
                        immediate_value
                    );
                }
                _ => {
                    kpanic!("Unsupported fcsr funct3: {}", funct3);
                }
            }
        }
        // Supervisor CSRs
        0x105 => {
            // stvec - Supervisor trap vector base address
            match funct3 {
                0x1 => {
                    // csrrw (read and write)
                    let current_value = get_stvec();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stvec(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    // csrrs (read and set)
                    let current_value = get_stvec();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stvec(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    // csrrc (read and clear)
                    let current_value = get_stvec();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stvec(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    // csrrwi (read and write immediate)
                    let current_value = get_stvec();
                    let imm = rs1;
                    set_stvec(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    // csrrsi (read and set immediate)
                    let current_value = get_stvec();
                    let imm = rs1;
                    set_stvec(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    // csrrci (read and clear immediate)
                    let current_value = get_stvec();
                    let imm = rs1;
                    set_stvec(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported stvec funct3: {}", funct3);
                }
            }
        }
        0x140 => {
            // sscratch - Supervisor scratch register
            match funct3 {
                0x1 => {
                    let current_value = get_sscratch();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sscratch(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_sscratch();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sscratch(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_sscratch();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sscratch(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_sscratch();
                    let imm = rs1;
                    set_sscratch(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_sscratch();
                    let imm = rs1;
                    set_sscratch(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_sscratch();
                    let imm = rs1;
                    set_sscratch(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sscratch funct3: {}", funct3);
                }
            }
        }
        0x102 => {
            // sdeleg - Supervisor delegation register
            match funct3 {
                0x1 => {
                    // csrrw (read and write)
                    let current_value = get_sdeleg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sdeleg(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    // csrrs (read and set)
                    let current_value = get_sdeleg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sdeleg(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    // csrrc (read and clear)
                    let current_value = get_sdeleg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sdeleg(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    // csrrwi (read and write immediate)
                    let current_value = get_sdeleg();
                    let imm = rs1;
                    set_sdeleg(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    // csrrsi (read and set immediate)
                    let current_value = get_sdeleg();
                    let imm = rs1;
                    set_sdeleg(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    // csrrci (read and clear immediate)
                    let current_value = get_sdeleg();
                    let imm = rs1;
                    set_sdeleg(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                0x0 => {
                    // funct3 = 0 is not a valid CSR instruction according to RISC-V spec
                    // This might be a misidentified instruction or a non-standard extension
                    debug_print!("Warning: Invalid CSR funct3=0 for sdeleg, treating as csrrw");
                    let current_value = get_sdeleg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sdeleg(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sdeleg funct3: {}", funct3);
                }
            }
        }
        0x104 => {
            // sie - Supervisor interrupt enable
            match funct3 {
                0x1 => {
                    let current_value = get_sie();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sie(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_sie();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sie(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_sie();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sie(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_sie();
                    let imm = rs1;
                    set_sie(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_sie();
                    let imm = rs1;
                    set_sie(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_sie();
                    let imm = rs1;
                    set_sie(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sie funct3: {}", funct3);
                }
            }
        }
        0x144 => {
            // sip - Supervisor interrupt pending
            match funct3 {
                0x1 => {
                    let current_value = get_sip();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sip(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_sip();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sip(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_sip();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sip(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_sip();
                    let imm = rs1;
                    set_sip(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_sip();
                    let imm = rs1;
                    set_sip(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_sip();
                    let imm = rs1;
                    set_sip(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sip funct3: {}", funct3);
                }
            }
        }
        0x106 => {
            // scounteren - Supervisor counter enable
            match funct3 {
                0x1 => {
                    let current_value = get_scounteren();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scounteren(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_scounteren();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scounteren(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_scounteren();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scounteren(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_scounteren();
                    let imm = rs1;
                    set_scounteren(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_scounteren();
                    let imm = rs1;
                    set_scounteren(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_scounteren();
                    let imm = rs1;
                    set_scounteren(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported scounteren funct3: {}", funct3);
                }
            }
        }
        0x100 => {
            // sstatus - Supervisor status register
            match funct3 {
                0x1 => {
                    let current_value = get_sstatus();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sstatus(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_sstatus();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sstatus(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_sstatus();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sstatus(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_sstatus();
                    let imm = rs1;
                    set_sstatus(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_sstatus();
                    let imm = rs1;
                    set_sstatus(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_sstatus();
                    let imm = rs1;
                    set_sstatus(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sstatus funct3: {}", funct3);
                }
            }
        }
        0x141 => {
            // sepc - Supervisor exception program counter
            match funct3 {
                0x1 => {
                    let current_value = get_sepc();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sepc(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_sepc();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sepc(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_sepc();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_sepc(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_sepc();
                    let imm = rs1;
                    set_sepc(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_sepc();
                    let imm = rs1;
                    set_sepc(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_sepc();
                    let imm = rs1;
                    set_sepc(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported sepc funct3: {}", funct3);
                }
            }
        }
        0x143 => {
            // stval - Supervisor trap value
            match funct3 {
                0x1 => {
                    let current_value = get_stval();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stval(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_stval();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stval(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_stval();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_stval(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_stval();
                    let imm = rs1;
                    set_stval(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_stval();
                    let imm = rs1;
                    set_stval(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_stval();
                    let imm = rs1;
                    set_stval(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported stval funct3: {}", funct3);
                }
            }
        }
        0x142 => {
            // scause - Supervisor cause register
            match funct3 {
                0x1 => {
                    let current_value = get_scause();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scause(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_scause();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scause(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_scause();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_scause(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_scause();
                    let imm = rs1;
                    set_scause(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_scause();
                    let imm = rs1;
                    set_scause(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_scause();
                    let imm = rs1;
                    set_scause(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported scause funct3: {}", funct3);
                }
            }
        }
        0x10A => {
            // senvcfg - Supervisor environment configuration
            match funct3 {
                0x1 => {
                    let current_value = get_senvcfg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_senvcfg(rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x2 => {
                    let current_value = get_senvcfg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_senvcfg(current_value | rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x3 => {
                    let current_value = get_senvcfg();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_senvcfg(current_value & !rs1_value);
                    }
                    set_ureg(rd as usize, current_value);
                }
                0x5 => {
                    let current_value = get_senvcfg();
                    let imm = rs1;
                    set_senvcfg(imm);
                    set_ureg(rd as usize, current_value);
                }
                0x6 => {
                    let current_value = get_senvcfg();
                    let imm = rs1;
                    set_senvcfg(current_value | imm);
                    set_ureg(rd as usize, current_value);
                }
                0x7 => {
                    let current_value = get_senvcfg();
                    let imm = rs1;
                    set_senvcfg(current_value & !imm);
                    set_ureg(rd as usize, current_value);
                }
                _ => {
                    kpanic!("Unsupported senvcfg funct3: {}", funct3);
                }
            }
        }
        0xc01 => {
            // time - Time counter (read-only)
            match funct3 {
                0x2 => {
                    // csrrs (read and set) - rd, rs1, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to set read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                0x1 => {
                    // csrrw (read and write) - rd, rs1, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to write read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                0x3 => {
                    // csrrwi (read and write immediate) - rd, imm, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to write immediate to read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                0x5 => {
                    // csrrci (read and clear immediate) - rd, imm, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually clear it, so just return current value
                        debug_print!("Warning: Attempted to clear read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                0x6 => {
                    // csrrsi (read and set immediate) - rd, imm, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to set immediate on read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                0x7 => {
                    // csrrci (read and clear immediate) - rd, imm, time
                    let current_time = host_get_cycle();
                    let time = (current_time & 0xFFFFFFFF) as u32;
                    if rs1 != 0 {
                        // For time CSR, we can't actually clear it, so just return current value
                        debug_print!("Warning: Attempted to clear read-only time CSR");
                    }
                    set_ureg(rd as usize, time);
                }
                _ => {
                    kpanic!("Unsupported time CSR funct3: {}", funct3);
                }
            }
        }
        0xc81 => {
            // timeh - Time counter high (read-only)
            match funct3 {
                0x2 => {
                    // csrrs (read and set) - rd, rs1, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to set read-only timeh CSR");
                    }
                    set_ureg(rd as usize, timeh);
                }
                0x1 => {
                    // csrrw (read and write) - rd, rs1, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to write read-only timeh CSR");
                    }
                    set_ureg(rd as usize, timeh);
                }
                0x3 => {
                    // csrrwi (read and write immediate) - rd, imm, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually set it, so just return current value
                        debug_print!(
                            "Warning: Attempted to write immediate to read-only timeh CSR"
                        );
                    }
                    set_ureg(rd as usize, timeh);
                }
                0x5 => {
                    // csrrci (read and clear immediate) - rd, imm, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually clear it, so just return current value
                        debug_print!("Warning: Attempted to clear read-only timeh CSR");
                    }
                    set_ureg(rd as usize, timeh);
                }
                0x6 => {
                    // csrrsi (read and set immediate) - rd, imm, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually set it, so just return current value
                        debug_print!("Warning: Attempted to set immediate on read-only timeh CSR");
                    }
                    set_ureg(rd as usize, timeh);
                }
                0x7 => {
                    // csrrci (read and clear immediate) - rd, imm, timeh
                    let current_time = host_get_cycle();
                    let timeh = (current_time >> 32) as u32;
                    if rs1 != 0 {
                        // For timeh CSR, we can't actually clear it, so just return current value
                        debug_print!("Warning: Attempted to clear read-only timeh CSR");
                    }
                    set_ureg(rd as usize, timeh);
                }
                _ => {
                    kpanic!("Unsupported timeh CSR funct3: {}", funct3);
                }
            }
        }
        _ => {
            kpanic!("Unsupported CSR address: {:#03x}", csr_addr);
        }
    }

    mret()
}

#[allow(unused)]
enum AuxType {
    Null = 0,
    Ignore = 1,
    ExecFd = 2,
    Phdr = 3,
    PhEnt = 4,
    PhNum = 5,
    PageSz = 6,
    Base = 7,
    Flags = 8,
    Entry = 9,
    NotElf = 10,
    Uid = 11,
    EUid = 12,
    Gid = 13,
    EGid = 14,
    Platform = 15,
    HwCap = 16,
    ClkTck = 17,
    Secure = 23,
    BasePlatform = 24,
    Random = 25,
    HwCap2 = 26,
    ExecFn = 31,
    SysInfo = 32,
    SysInfoEhdr = 33,
}

struct UserStack {
    sp: *mut usize,
    strs_ptr: *mut u8,
}

impl UserStack {
    fn new() -> Self {
        Self {
            sp: USER_STACK_PTR as *mut usize,
            strs_ptr: ASCII_TABLE_PTR as *mut u8,
        }
    }

    fn add_word(&mut self, word: usize) {
        unsafe {
            self.sp.write_volatile(word);
            self.sp = self.sp.add(1);
        }
    }

    #[allow(dead_code)]
    fn add_null(&mut self) {
        self.add_word(0);
    }

    #[allow(dead_code)]
    fn add_aux_word(&mut self, atype: AuxType, word: usize) {
        self.add_word(atype as usize);
        self.add_word(word);
    }

    fn add_str(&mut self, str: &[u8]) {
        let strs_ptr = self.strs_ptr;
        unsafe {
            strs_ptr.copy_from(str.as_ptr(), str.len());
            self.strs_ptr = strs_ptr.add(str.len() + 1);
        }
        self.add_word(strs_ptr as usize);
    }
}

impl Err {
    pub fn as_errno(&self) -> u32 {
        *self as u32
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn kstart() -> ! {
    let user_start_addr = unsafe { USER_START_PTR.read_volatile() } - 4;
    unsafe {
        MEPC_PTR.write_volatile(user_start_addr);
    }

    //let mut stack = UserStack::new();

    debug_print_simple!("kstart");
    // args - get actual argc and argv from host
    /*
    let argc = host_argc();
    debug_print!("argc is {argc}");
    // Check if we have any arguments
    if argc == 0 {
        debug_print!("Error: No command line arguments provided (argc = 0)");
        host_terminate(255, 0);
    }

    stack.add_word(argc as usize);

    // XXX we should review this code from a security perspective
    // Get each argument from host and add to stack
    for i in 0..argc {
        let mut arg_buffer = [0u32; 256]; // 1024 bytes as u32 array for proper alignment
        debug_print!("arg {i}");
        let arg_len = host_argv(i, arg_buffer.as_mut_ptr() as *mut u8, arg_buffer.len() * 4);
        // we want to make this string null-terminated, so we add 1 to the length
        let arg_len = arg_len + 1;
        if arg_len > 0 && arg_len <= (arg_buffer.len() * 4) as u32 {
            // Create a byte slice with the actual argument length
            let arg_bytes: &[u8] = bytemuck::cast_slice(&arg_buffer);
            let arg_slice = &arg_bytes[..arg_len as usize];
            // Print the argument as a string (not null-terminated, may not be valid UTF-8)
            // Now arg_slice is a null-terminated string; trim at the first null for display.
            let nul_pos = arg_slice
                .iter()
                .position(|&b| b == 0)
                .unwrap_or(arg_slice.len());
            let arg_str = &arg_slice[..nul_pos];
            match core::str::from_utf8(arg_str) {
                Ok(s) => debug_print!(
                    "arg {i}: \"{s}\" ({arg_len}, null-terminated)"
                ),
                Err(_) => debug_print!(
                    "arg {i}: <non-utf8> {:?} ({arg_len}, null-terminated)",
                    arg_str
                ),
            }
            stack.add_str(arg_slice);
        } else {
            // Fallback to empty string if something goes wrong
            stack.add_str(b"");
        }
    }
    stack.add_null();

    // env
    stack.add_null();

    // aux
    stack.add_aux_word(AuxType::PageSz, PAGE_SIZE); // auxv[0]
    stack.add_aux_word(AuxType::Uid, 1); // auxv[1]
    stack.add_aux_word(AuxType::EUid, 1); // auxv[2]
    stack.add_aux_word(AuxType::Gid, 1); // auxv[3]
    stack.add_aux_word(AuxType::EGid, 1); // auxv[4]
    // Add AT_PHDR, AT_PHNUM, AT_PHENT
    // Define the AuxType variants if not already defined:
    //     Phdr = ...,
    //     Phnum = ...,
    //     Phent = ...,
    // Use the constants for addresses and sizes
    stack.add_aux_word(AuxType::Phdr, unsafe { USER_PHDR_ADDR_PTR.read_volatile() }); // auxv[5]
    stack.add_aux_word(AuxType::PhNum, unsafe {
        USER_PHDR_NUM_ADDR_PTR.read_volatile()
    }); // auxv[6]
    stack.add_aux_word(AuxType::PhEnt, USER_PHENT_SIZE); // auxv[7]
    stack.add_aux_word(AuxType::Null, 0); // auxv[8]

    set_ureg(REG_SP, USER_STACK_PTR as u32); */

    /* let block: &[u8] = unsafe { core::slice::from_raw_parts(USER_HEAP_START_PTR, USER_HEAP_SIZE) };
    #[allow(static_mut_refs)]
    unsafe {
        HEAP.insert_free_block_ptr(block.into());
    }
    */

    // Initialize floating point registers to zero at startup
    init_softfloat();
    // Copy DTB_DATA to USER_STACK_ADDR
    unsafe {
        core::ptr::copy_nonoverlapping(
            DTB_DATA.as_ptr(),
            USER_STACK_ADDR as *mut u8,
            DTB_DATA.len(),
        );
    }
    //stack.add_str(&DTB_DATA);
    set_ureg(REG_A0, 0); // hartid

    set_ureg(REG_A1, USER_STACK_ADDR as u32);
    print("return from kstart");
    mret()
}

pub fn mret() -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        core::arch::asm!("mret", options(noreturn))
    }
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

const SBI_EXT_BASE: u32 = 0x10;
const SBI_EXT_DBCN: u32 = 0x4442434E;

// SBI constants
const SBI_ECALL_VERSION_MAJOR: u32 = 3;
const SBI_ECALL_VERSION_MINOR: u32 = 0;
const SBI_OPENSBI_IMPID: u32 = 1;

const SBI_SPEC_VERSION_MAJOR_OFFSET: u32 = 24;
const SBI_SPEC_VERSION_MAJOR_MASK: u32 = 0x7f;
const SBI_SPEC_VERSION_MINOR_MASK: u32 = 0xffffff;

// SBI Base Extension function IDs
const SBI_EXT_BASE_GET_SPEC_VERSION: u32 = 0x0;
const SBI_EXT_BASE_GET_IMP_ID: u32 = 0x1;
const SBI_EXT_BASE_GET_IMP_VERSION: u32 = 0x2;
const SBI_EXT_BASE_PROBE_EXT: u32 = 0x3;
const SBI_EXT_BASE_GET_MVENDORID: u32 = 0x4;
const SBI_EXT_BASE_GET_MARCHID: u32 = 0x5;
const SBI_EXT_BASE_GET_MIMPID: u32 = 0x6;
const SBI_EXT_DBCN_CONSOLE_WRITE: u32 = 0x0;
const SBI_EXT_DBCN_CONSOLE_READ: u32 = 0x1;
const SBI_EXT_DBCN_CONSOLE_WRITE_BYTE: u32 = 0x2;

#[unsafe(no_mangle)]
unsafe extern "C" fn ecall_dispatch() -> ! {
    debug_print!("ecall: {}", get_ureg(REG_A7));
    let nr = get_ureg(REG_A7);
    if nr == SBI_EXT_DBCN {
        // SBI_EXT_CONSOLE
        if get_ureg(REG_A6) == SBI_EXT_DBCN_CONSOLE_WRITE {
            // print the ascii character
            let msg_ptr = get_ureg(REG_A1) as *const u8;
            let msg = unsafe { core::slice::from_raw_parts(msg_ptr, get_ureg(REG_A0) as usize) };
            host_log(msg.as_ptr(), msg.len());
        }
    } else if nr == SBI_EXT_BASE {
        let msg = str_format!(str256, "sbi_ext_base: {}", get_ureg(REG_A6));
        print(&msg);
        match get_ureg(REG_A6) {
            SBI_EXT_BASE_GET_SPEC_VERSION => {
                // Return SBI spec version 3.0
                let mut value = (SBI_ECALL_VERSION_MAJOR << SBI_SPEC_VERSION_MAJOR_OFFSET)
                    & (SBI_SPEC_VERSION_MAJOR_MASK << SBI_SPEC_VERSION_MAJOR_OFFSET);
                value |= SBI_ECALL_VERSION_MINOR;
                set_ureg(REG_A0, 0); // Success
                set_ureg(REG_A1, value); // Version value
            }
            SBI_EXT_BASE_GET_IMP_ID => {
                // Return OpenSBI implementation ID
                set_ureg(REG_A0, 0); // Success
                set_ureg(REG_A1, SBI_OPENSBI_IMPID); // OpenSBI implementation ID
            }
            SBI_EXT_BASE_GET_IMP_VERSION => {
                // TODO: Implement implementation version
                set_ureg(REG_A0, 0); // Version 0
                set_ureg(REG_A1, 0); // OpenSBI implementation ID
            }
            SBI_EXT_BASE_GET_MVENDORID => {
                // TODO: Implement machine vendor ID
                set_ureg(REG_A0, 0); // Unknown vendor
                set_ureg(REG_A1, 0); // OpenSBI implementation ID
            }
            SBI_EXT_BASE_GET_MARCHID => {
                // TODO: Implement machine architecture ID
                set_ureg(REG_A0, 0); // Unknown architecture
                set_ureg(REG_A1, 0); // OpenSBI implementation ID
            }
            SBI_EXT_BASE_GET_MIMPID => {
                // TODO: Implement machine implementation ID
                set_ureg(REG_A0, 0); // Unknown implementation
                set_ureg(REG_A1, 0); // OpenSBI implementation ID
            }
            SBI_EXT_BASE_PROBE_EXT => {
                let msg = str_format!(str256, "sbi_ext_base_probe_ext: {:x}", get_ureg(REG_A0));
                print(&msg);
                if get_ureg(REG_A0) == 0x4442434E {
                    set_ureg(REG_A0, 0);
                    set_ureg(REG_A1, 1);
                } else {
                    set_ureg(REG_A0, 0);
                    set_ureg(REG_A1, 0);
                }
            }
            _ => {
                debug_print!("Unsupported SBI base function: {}", get_ureg(REG_A6));
                set_ureg(REG_A0, 0); // Return 0 for unsupported functions
            }
        }
    } else if nr == SYS_EXIT {
        syscall1(sys_exit);
    } else {
        kpanic!("syscall: {nr}");
    }
    mret();

    /*     let msg = str_format!(str256, "syscall: {nr} (a7={})", get_ureg(17));
    print(&msg);

    // Debug: check all registers around a7
    let msg2 = str_format!(
        str256,
        "DEBUG: a5={}, a6={}, a7={}, s0={}",
        get_ureg(15),
        get_ureg(16),
        get_ureg(17),
        get_ureg(18)
    );
    print(&msg2);
    match nr {
        SYS_IOCTL => syscall3(sys_ioctl),
        SYS_READ => syscall3(sys_read),
        SYS_WRITE => syscall3(sys_write),
        SYS_WRITEV => syscall3(sys_writev),
        SYS_EXIT => syscall1(sys_exit),
        SYS_EXIT_GROUP => syscall1(sys_exit_group),
        SYS_SET_TID_ADDRESS => syscall1(sys_set_tid_address),
        SYS_TKILL => syscall2(sys_tkill),
        SYS_SIGALTSTACK => syscall2(sys_sigaltstack),
        SYS_RT_SIGACTION => syscall4(sys_rt_sigaction),
        SYS_RT_SIGPROCMASK => syscall4(sys_rt_sigprocmask),
        SYS_BRK => syscall1(sys_brk),
        SYS_MMAP => syscall6(sys_mmap),
        SYS_MUNMAP => syscall2(sys_munmap),
        SYS_PPOLL => syscall5(sys_ppoll),
        _ => {
            let msg = str_format!(str256, "syscall: {nr}");
            print(&msg);
            set_ureg(REG_A0, 0);
        }
    }

    mret() */
}

#[unsafe(no_mangle)]
unsafe extern "C" fn illegal_instruction_dispatch() -> ! {
    // Get the saved PC from MEPC (where the illegal instruction occurred)
    let mepc = unsafe { MEPC_PTR.read_volatile() };

    // Read the instruction as a u32
    let instruction = unsafe { (mepc as *const u32).read_volatile() };

    // Decode instruction fields
    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    let funct7 = (instruction & 0xfe000000) >> 25;

    debug_print!(
        "Decoded instruction: {:#08x}, opcode={:#02x}, funct7={:#02x}",
        instruction,
        opcode,
        funct7
    );

    // Check if this is a fence instruction (0x0ff0000f)
    if instruction == 0x0ff0000f {
        // Fence instruction - treat as null-op and continue
        // mret will automatically increment MEPC by 4, so we don't need to do anything
        /* let msg = str_format!(str256, "Emulating fence instruction at PC: {:#010x}", mepc);
        print(&msg); */
        mret()
    }

    // Check if this is a fence.i instruction (0x0000100f)
    if instruction == 0x0000100f {
        // Fence.i instruction - treat as null-op and continue
        // mret will automatically increment MEPC by 4, so we don't need to do anything
        /* let msg = str_format!(
            str256,
            "Emulating fence.i instruction at PC: {:#010x}",
            mepc
        );
        print(&msg); */
        mret()
    }

    // Check if this is a fence rw,rw instruction (0x0330000f)
    if instruction == 0x0330000f {
        // Fence rw,rw instruction - ensure all read and write operations before this fence
        // are completed before any read and write operations after this fence
        // In our emulated environment, we can treat this as a memory barrier
        debug_print!("Emulating fence rw,rw instruction at PC: {:#010x}", mepc);
        // For now, treat as null-op since we don't have complex memory ordering
        // In a real implementation, this would ensure memory ordering constraints
        mret()
    }

    // Check if this is a fence ow,ow instruction (0x0550000f)
    if instruction == 0x0550000f {
        // Fence ow,ow instruction - ensure all "other" and write operations before this fence
        // are completed before any "other" and write operations after this fence
        // In our emulated environment, we can treat this as a memory barrier
        debug_print!("Emulating fence ow,ow instruction at PC: {:#010x}", mepc);
        // For now, treat as null-op since we don't have complex memory ordering
        // In a real implementation, this would ensure memory ordering constraints
        mret()
    }

    // Check for floating point operations (opcode 0x43) - R4-type instructions
    if opcode == 0x43 {
        /*let msg = str_format!(
            str256,
            "Processing R4-type FP instruction: {:#08x} at PC: {:#010x}",
            instruction,
            mepc
        );
        print(&msg); */
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point operations (opcode 0x47) - R4-type instructions
    if opcode == 0x47 {
        /* let msg = str_format!(
            str256,
            "Processing R4-type FP instruction: {:#08x} at PC: {:#010x}",
            instruction,
            mepc
        );
        print(&msg); */
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point operations (opcode 0x4b) - R4-type instructions
    if opcode == 0x4b {
        /* let msg = str_format!(
            str256,
            "Processing R4-type FP instruction: {:#08x} at PC: {:#010x}",
            instruction,
            mepc
        );
        print(&msg); */
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point operations (opcode 0x4f) - R4-type instructions
    if opcode == 0x4f {
        debug_print!(
            "Processing R4-type FP instruction: {:#08x} at PC: {:#010x}",
            instruction,
            mepc
        );
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point operations (opcode 0x53)
    if opcode == 0x53 {
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point operations (opcode 0x63) - alternative encoding
    if opcode == 0x63 {
        debug_print!(
            "Processing R4-type FP instruction: {:#08x} at PC: {:#010x}",
            instruction,
            mepc
        );
        unsafe {
            emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point load/store operations (opcode 0x07 = Load-FP, 0x27 = Store-FP)
    if opcode == 0x07 || opcode == 0x27 {
        unsafe {
            emulate_fp_load_store(instruction, mepc);
        }
    }

    // Check for CSR operations (opcode 0x73)
    if opcode == 0x73 {
        unsafe {
            emulate_csr_instruction(instruction, mepc);
        }
    }

    // Check for RV32A atomic memory operations
    if opcode == 0x2f {
        emulate_atomic_instruction(mepc, rd, rs1, rs2, funct3, funct7);
    }

    // Log the illegal instruction event and terminate
    kpanic!(
        "Illegal instruction at PC: {:#010x}, instr: {:#010x}",
        mepc,
        instruction
    );
}

fn emulate_atomic_instruction(mepc: usize, rd: u32, rs1: u32, rs2: u32, funct3: u32, funct7: u32) {
    let funct5 = (funct7 & 0b1111100) >> 2;
    let _aq = (funct7 & 0b0000010) >> 1;
    // acquire access
    let _rl = funct7 & 0b0000001;
    // release access

    match (funct3, funct5) {
        (0x2, 0x00) => {
            // amoadd.w - atomic memory operation: add word
            debug_print!(
                "Emulating amoadd.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to add from rs2 register
            let add_value = get_ureg(rs2 as usize);

            // Perform atomic add operation
            let new_value = current_value.wrapping_add(add_value);
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x01) => {
            // amoswap.w - atomic memory operation: swap word
            debug_print!(
                "Emulating amoswap.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to swap from rs2 register
            let swap_value = get_ureg(rs2 as usize);

            // Perform atomic swap operation
            unsafe {
                (addr as *mut u32).write_volatile(swap_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x04) => {
            // amoxor.w - atomic memory operation: XOR word
            debug_print!(
                "Emulating amoxor.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to XOR from rs2 register
            let xor_value = get_ureg(rs2 as usize);

            // Perform atomic XOR operation
            let new_value = current_value ^ xor_value;
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x08) => {
            // amoor.w - atomic memory operation: OR word
            debug_print!(
                "Emulating amoor.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to OR from rs2 register
            let or_value = get_ureg(rs2 as usize);

            // Perform atomic OR operation
            let new_value = current_value | or_value;
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x0c) => {
            // amoand.w - atomic memory operation: AND word
            debug_print!(
                "Emulating amoand.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to AND from rs2 register
            let and_value = get_ureg(rs2 as usize);

            // Perform atomic AND operation
            let new_value = current_value & and_value;
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x10) => {
            // amomin.w - atomic memory operation: minimum word (signed)
            debug_print!(
                "Emulating amomin.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to compare from rs2 register
            let compare_value = get_ureg(rs2 as usize);

            // Perform atomic minimum operation (signed comparison)
            let current_signed = current_value as i32;
            let compare_signed = compare_value as i32;
            let new_value = if current_signed < compare_signed {
                current_value
            } else {
                compare_value
            };
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x14) => {
            // amomax.w - atomic memory operation: maximum word (signed)
            debug_print!(
                "Emulating amomax.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to compare from rs2 register
            let compare_value = get_ureg(rs2 as usize);

            // Perform atomic maximum operation (signed comparison)
            let current_signed = current_value as i32;
            let compare_signed = compare_value as i32;
            let new_value = if current_signed > compare_signed {
                current_value
            } else {
                compare_value
            };
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x18) => {
            // amominu.w - atomic memory operation: minimum word (unsigned)
            debug_print!(
                "Emulating amominu.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to compare from rs2 register
            let compare_value = get_ureg(rs2 as usize);

            // Perform atomic minimum operation (unsigned comparison)
            let new_value = if current_value < compare_value {
                current_value
            } else {
                compare_value
            };
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x1c) => {
            // amomaxu.w - atomic memory operation: maximum word (unsigned)
            debug_print!(
                "Emulating amomaxu.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read current value from memory
            let current_value = unsafe { (addr as *const u32).read_volatile() };

            // Get value to compare from rs2 register
            let compare_value = get_ureg(rs2 as usize);

            // Perform atomic maximum operation (unsigned comparison)
            let new_value = if current_value > compare_value {
                current_value
            } else {
                compare_value
            };
            unsafe {
                (addr as *mut u32).write_volatile(new_value);
            }

            // Write original value to rd register
            // XXX check for rd = 0?
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x02) => {
            // lr.w - Load Reserved Word
            debug_print!(
                "Emulating lr.w at PC: {:#010x}, rd={}, rs1={}",
                mepc,
                rd,
                rs1
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Read value from memory
            let value = unsafe { (addr as *const u32).read_volatile() };

            // Set reservation: store the reserved address in ILRSC shadow register
            set_ilrsc(addr);

            // Set reservation state: store 1 (valid) in ILRSC_SET shadow register
            set_ilrsc_set(1);

            // Write loaded value to rd register
            set_ureg(rd as usize, value);

            debug_print!(
                "lr.w: loaded {:#010x} from {:#010x}, set reservation",
                value,
                addr
            );

            mret()
        }
        (0x2, 0x03) => {
            // sc.w - Store Conditional Word
            debug_print!(
                "Emulating sc.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                mepc,
                rd,
                rs1,
                rs2
            );

            // Get address from rs1 register
            let addr = get_ureg(rs1 as usize);

            // Check alignment (4-byte aligned for 32-bit words)
            if addr % 4 != 0 {
                kpanic!("Address misaligned: {:#010x}", addr);
            }

            // Get value to store from rs2 register
            let store_value = get_ureg(rs2 as usize);

            // Check if reservation is valid
            let reserved_addr = get_ilrsc();
            let reservation_valid = get_ilrsc_set();

            if reservation_valid == 1 && reserved_addr == addr {
                // Reservation is valid - perform the store
                unsafe {
                    (addr as *mut u32).write_volatile(store_value);
                }

                // Clear reservation
                set_ilrsc_set(0);

                // Write 0 to rd register (success)
                set_ureg(rd as usize, 0);

                debug_print!(
                    "sc.w: stored {:#010x} to {:#010x}, success",
                    store_value,
                    addr
                );
            } else {
                // Reservation is invalid - don't store, write 1 to rd (failure)
                set_ureg(rd as usize, 1);

                let msg = str_format!(
                    str256,
                    "sc.w: reservation invalid (addr={:#010x}, reserved={:#010x}, valid={}), failure",
                    addr,
                    reserved_addr,
                    reservation_valid
                );
                print(&msg);
            }

            mret()
        }
        _ => {
            // Other atomic operations not implemented yet
            let msg = str_format!(
                str256,
                "Unimplemented atomic operation: funct3={:#x}, funct5={:#x}",
                funct3,
                funct5
            );
            print(&msg);
        }
    }
}

pub fn print(msg: &str) {
    let msg = msg.as_bytes();
    host_log(msg.as_ptr(), msg.len());
}

fn set_result(result: Result<u32, Err>) {
    set_ureg(REG_A0, result.unwrap_or_else(|e| e.as_errno()));
}

fn syscall1<F: Fn(u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0)));
}

fn syscall2<F: Fn(u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0), get_ureg(REG_A1)));
}

fn syscall3<F: Fn(u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0), get_ureg(REG_A1), get_ureg(REG_A2)));
}

fn syscall4<F: Fn(u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
    ));
}

fn syscall5<F: Fn(u32, u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
        get_ureg(REG_A4),
    ));
}

fn syscall6<F: Fn(u32, u32, u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
        get_ureg(REG_A4),
        get_ureg(REG_A5),
    ));
}

/// change the location of the program break
///
/// https://man7.org/linux/man-pages/man2/brk.2.html
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L194
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L381
fn sys_brk(addr: u32) -> Result<u32, Err> {
    let ret = unsafe {
        if addr > USER_HEAP_START_ADDR as u32 {
            BRK = addr;
        }
        BRK
    };

    // let msg = str_format!(str256, "sys_brk(0x{addr:08x}) -> 0x{ret:08x}");
    // print(&msg);

    Ok(ret)
}

/// https://man7.org/linux/man-pages/man2/mmap.2.html
/// https://elixir.bootlin.com/linux/v5.15.5/source/arch/riscv/kernel/sys_riscv.c#L30
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L1583
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L1404
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L1282
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L1056
fn sys_mmap(
    _addr: u32,
    len: u32,
    _prot: u32,
    _flags: u32,
    fd: u32,
    _offset: u32,
) -> Result<u32, Err> {
    let _fd = fd as i32;

    // let msg = str_format!(
    //     str256,
    //     "sys_mmap(0x{_addr:08x}, {len}, {_prot}, 0x{_flags:08x}, {_fd}, {_offset})"
    // );
    // print(&msg);

    if len == 0 {
        return Err(Err::Inval);
    }

    #[allow(static_mut_refs)]
    let ptr = unsafe {
        let layout = Layout::from_size_align(len as usize, PAGE_SIZE).unwrap_unchecked();
        let ptr = HEAP.allocate(layout).ok_or(Err::NoMem)?.as_ptr();
        if !ptr.is_null() {
            ptr.write_bytes(0, layout.size());
        }
        ptr
    };

    // let msg = str_format!(str256, "{ptr:?}");
    // print(&msg);

    Ok(ptr as u32)
}

/// https://man7.org/linux/man-pages/man2/mmap.2.html
fn sys_munmap(addr: u32, _len: u32) -> Result<u32, Err> {
    let ptr = addr as *mut u8;

    // let msg = str_format!(str256, "sys_munmap({ptr:?}, {_len})");
    // print(&msg);

    if ptr.is_null() {
        return Err(Err::Inval);
    }

    #[allow(static_mut_refs)]
    unsafe {
        HEAP.deallocate(NonNull::new_unchecked(ptr), PAGE_SIZE)
    };

    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/read.2.html
fn sys_read(_fd: u32, _buf: u32, _count: u32) -> Result<u32, Err> {
    // const HOST_ECALL_READ: u32 = 1;
    // let msg = str_format!(str256, "sys_read({fd}, {buf:?}, {count})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/write.2.html
fn sys_write(fd: u32, buf: u32, count: u32) -> Result<u32, Err> {
    do_write(fd as i32, buf as *const u8, count as usize).map(|x| x as u32)
}

fn do_write(fd: i32, buf: *const u8, count: usize) -> Result<usize, Err> {
    // let msg = str_format!(str256, "do_write({fd}, {buf:?}, {count})");
    // print(&msg);

    if fd == 1 || fd == 2 {
        host_log(buf, count);
    }

    Ok(count)
}

#[repr(C)]
struct IoVec {
    iov_base: *mut u8,
    iov_len: usize,
}

/// https://man7.org/linux/man-pages/man2/writev.2.html
fn sys_writev(fd: u32, vec_ptr: u32, vlen: u32) -> Result<u32, Err> {
    let fd = fd as i32;
    let vec_ptr = vec_ptr as *const IoVec;
    let vec = unsafe { core::slice::from_raw_parts(vec_ptr, vlen as usize) };

    // let msg = str_format!(str256, "sys_writev({fd}, {vec_ptr:?}, {vlen})");
    // print(&msg);

    let mut total: usize = 0;
    for iov in vec {
        total += do_write(fd, iov.iov_base, iov.iov_len)?;
    }
    Ok(total as u32)
}

/// https://man7.org/linux/man-pages/man2/ioctl.2.html
fn sys_ioctl(fd: u32, _cmd: u32, arg: u32) -> Result<u32, Err> {
    let _fd = fd as i32;
    let _arg = arg as *const u8;
    // let msg = str_format!(str256, "sys_ioctl({fd}, {cmd}, 0x{arg:08x})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/_exit.2.html
fn sys_exit(error_code: u32) -> Result<u32, Err> {
    let msg = str_format!(str256, "sys_exit({error_code})");
    print(&msg);
    host_terminate(error_code, 0);
}

/// https://man7.org/linux/man-pages/man2/exit_group.2.html
fn sys_exit_group(_error_code: u32) -> Result<u32, Err> {
    // let msg = str_format!(str256, "sys_exit_group({error_code})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/tkill.2.html
fn sys_tkill(_pid: u32, _sig: u32) -> Result<u32, Err> {
    // let msg = str_format!(str256, "sys_tkill({_pid}, {_sig})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/set_tid_address.2.html
fn sys_set_tid_address(tidptr: u32) -> Result<u32, Err> {
    let _tidptr = tidptr as *const u8;
    let msg = str_format!(str256, "sys_set_tid_address({tidptr:?})");
    print(&msg);
    Ok(1)
}

/// https://man7.org/linux/man-pages/man2/sigaltstack.2.html
fn sys_sigaltstack(uss: u32, uoss: u32) -> Result<u32, Err> {
    let _uss = uss as *const u8;
    let _uoss = uoss as *const u8;
    // let msg = str_format!(str256, "sys_sigaltstack({uss:?}, {uoss:?})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/sigaction.2.html
fn sys_rt_sigaction(_sig: u32, act: u32, oact: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _act = act as *const u8;
    let _oact = oact as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_rt_sigaction({_sig}, {_act:?}, {_oact:?}, {_sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/sigprocmask.2.html
fn sys_rt_sigprocmask(_how: u32, nset: u32, oset: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _nset = nset as *const u8;
    let _oset = oset as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_rt_sigprocmask({_how}, {_nset:?}, {_oset:?}, {_sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/poll.2.html
fn sys_ppoll(ufds: u32, _nfds: u32, tsp: u32, sigmask: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _ufds = ufds as *const u8;
    let _tsp = tsp as *const u8;
    let _sigmask = sigmask as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_ppoll({ufds:?}, {nfds}, {tsp:?}, {sigmask:?}, {sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}
