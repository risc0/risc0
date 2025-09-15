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

use no_std_strings::{str_format, str256};

use crate::constants::*;
use crate::host_calls::{host_argc, host_get_cycle, host_log, host_terminate};
use crate::linux_abi::{handle_linux_syscall, start_linux_binary};
use crate::smode_emul::{handle_smode_ecall, start_vmlinux};
use crate::softfloat::{
    emulate_fp_instruction, emulate_fp_load_store,
    handle_float_csr_exception, handle_float_csr_fcsr, handle_float_csr_frm, init_softfloat,
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

fn get_vm_machine_mode() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(VM_MACHINE_MODE) }
}

#[allow(dead_code)]
fn set_vm_machine_mode(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(VM_MACHINE_MODE) = value;
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
            handle_float_csr_exception(funct3, rs1, rd);
        }
        0x002 => {
            handle_float_csr_frm(funct3, rs1, rd);
        }
        0x003 => {
            handle_float_csr_fcsr(funct3, rs1, rd);
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

#[unsafe(no_mangle)]
unsafe extern "C" fn kstart() -> ! {
    // Initialize floating point registers to zero at startup
    init_softfloat();

    debug_print_simple!("kstart");
    // args - get actual argc and argv from host
    let argc = host_argc();
    debug_print!("argc is {argc}");
    // Check if we have any arguments
    if argc == 0 {
        start_vmlinux()
    } else {
        start_linux_binary(argc)
    }
}

pub fn mret() -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        core::arch::asm!("mret", options(noreturn))
    }
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

#[unsafe(no_mangle)]
unsafe extern "C" fn ecall_dispatch() -> ! {
    match get_vm_machine_mode() {
        VM_MACHINE_MODE_LINUX_ABI => handle_linux_syscall(),
        VM_MACHINE_MODE_EMULATED_S_MODE => handle_smode_ecall(),
        _ => {
            kpanic!("unknown machine mode {}", get_vm_machine_mode());
        }
    }
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
