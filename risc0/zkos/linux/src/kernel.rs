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

use crate::atomic_emul::emulate_atomic_instruction;
use crate::compressed_emul::{
    emulate_compressed_instruction, handle_mpec_fixup, unaligned_instruction_execution,
};
use crate::constants::*;
use crate::host_calls::{host_argc, host_log, host_terminate};
use crate::linux_abi::{handle_linux_syscall, start_linux_binary};
use crate::smode_emul::*;
use crate::softfloat::{
    emulate_fp_instruction, emulate_fp_load_store, handle_float_csr_exception,
    handle_float_csr_fcsr, handle_float_csr_frm, init_softfloat,
};
// Debug configuration - set to true to enable debug prints, false to disable
pub const DEBUG_ENABLED: bool = false;
pub const TRACE_ENABLED: bool = false;
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

macro_rules! trace_print {
    ($($arg:tt)*) => {
        if TRACE_ENABLED {
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
    kpanic!("Panic: {}", _info);
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

pub fn get_vm_machine_mode() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(VM_MACHINE_MODE) }
}

#[allow(dead_code)]
pub fn set_vm_machine_mode(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(VM_MACHINE_MODE) = value;
    }
}

// CSR (Control and Status Register) emulation
unsafe fn emulate_csr_instruction(insn: u32, mepc: usize) -> ! {
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let csr_addr = (insn >> 20) & 0xfff;

    trace_print!(
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
    if DEBUG_ENABLED && csr_addr != 0x100 {
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
    }

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
            handle_stvec(funct3, rd, rs1);
        }
        0x140 => {
            handle_sscratch(funct3, rd, rs1);
        }
        0x102 => {
            handle_sdeleg(funct3, rd, rs1);
        }
        0x104 => {
            handle_sie(funct3, rd, rs1);
        }
        0x144 => {
            handle_sip(funct3, rd, rs1);
        }
        0x106 => {
            handle_scounteren(funct3, rd, rs1);
        }
        0x100 => {
            handle_sstatus(funct3, rd, rs1);
        }
        0x141 => {
            handle_sepc(funct3, rd, rs1);
        }
        0x143 => {
            handle_stval(funct3, rd, rs1);
        }
        0x142 => {
            handle_scause(funct3, rd, rs1);
        }
        0x10A => {
            handle_senvcfg(funct3, rd, rs1);
        }
        0xc01 => {
            handle_time(funct3, rd, rs1);
        }
        0xc81 => {
            handle_timeh(funct3, rd, rs1);
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
        VM_MACHINE_MODE_EMULATED_U_MODE => handle_umode_ecall(),
        _ => {
            kpanic!("unknown machine mode {}", get_vm_machine_mode());
        }
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn illegal_instruction_dispatch() -> ! {
    // Get the saved PC from MEPC (where the illegal instruction occurred)
    let mepc = unsafe { MEPC_PTR.read_volatile() };
    // Read the instruction as a u16 first
    let instruction_h = unsafe { (mepc as *const u16).read_volatile() };
    if instruction_h & 0x3 != 0x3 {
        emulate_compressed_instruction(mepc, instruction_h)
    } else if mepc % 4 != 0 {
        unaligned_instruction_execution(mepc, instruction_h);
    }

    let instruction_l = unsafe { (mepc as *const u16).add(1).read_volatile() };
    let instruction = (instruction_l as u32) << 16 | instruction_h as u32;
    if instruction == 0xffff_ffff {
        handle_mpec_fixup()
    }
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
        trace_print!("Emulating fence rw,rw instruction at PC: {:#010x}", mepc);
        // For now, treat as null-op since we don't have complex memory ordering
        // In a real implementation, this would ensure memory ordering constraints
        mret()
    }

    // Check if this is a fence ow,ow instruction (0x0550000f)
    if instruction == 0x0550000f {
        // Fence ow,ow instruction - ensure all "other" and write operations before this fence
        // are completed before any "other" and write operations after this fence
        // In our emulated environment, we can treat this as a memory barrier
        trace_print!("Emulating fence ow,ow instruction at PC: {:#010x}", mepc);
        // For now, treat as null-op since we don't have complex memory ordering
        // In a real implementation, this would ensure memory ordering constraints
        mret()
    }

    // Decode instruction fields
    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    let funct7 = (instruction & 0xfe000000) >> 25;
    trace_print!(
        "Decoded instruction: {:#08x}, opcode={:#02x}, funct7={:#02x}",
        instruction,
        opcode,
        funct7
    );
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
        trace_print!(
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

    // Check for SYSTEM operations (opcode 0x73)
    if opcode == 0x73 {
        // Check if this is a privileged system instruction (funct3=000)
        if funct3 == 0x0 {
            // Extract funct12 field (bits [31:20])
            let funct12 = (instruction >> 20) & 0xfff;

            // Check for sret instruction (funct12 = 0x102)
            if funct12 == 0x102 {
                if get_vm_machine_mode() == VM_MACHINE_MODE_EMULATED_S_MODE {
                    set_vm_machine_mode(VM_MACHINE_MODE_EMULATED_U_MODE);
                    unsafe {
                        MEPC_PTR.write_volatile(get_sepc() as usize - 4);
                    }
                    mret()
                } else {
                    // should be
                    kpanic!("sret instruction intercepted at PC: {:#010x}", mepc);
                }
            } else if funct12 == 0x105 {
                // WFI, null-op
                mret()
            }

            // Handle other privileged system instructions here if needed
            kpanic!(
                "Unsupported privileged system instruction: funct12={:#03x} at PC: {:#010x}",
                funct12,
                mepc
            );
        } else {
            // This is a CSR instruction (funct3 != 000)
            unsafe {
                emulate_csr_instruction(instruction, mepc);
            }
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

pub fn print(msg: &str) {
    let msg = msg.as_bytes();
    host_log(msg.as_ptr(), msg.len());
}

#[unsafe(no_mangle)]
unsafe extern "C" fn instruction_misaligned_dispatch() -> ! {
    // Get the saved PC from MEPC (where the misaligned instruction occurred)
    let mepc = unsafe { MEPC_PTR.read_volatile() };

    // Read the instruction that caused the misaligned jump
    let instruction = unsafe { (mepc as *const u32).read_volatile() };

    // Decode instruction fields
    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    let _funct7 = (instruction & 0xfe000000) >> 25;

    debug_print!(
        "Instruction misaligned dispatch: PC={:#010x}, instr={:#010x}, opcode={:#02x}",
        mepc,
        instruction,
        opcode
    );

    match opcode {
        0x63 => {
            // Branch instructions (beq, bne, blt, bge, bltu, bgeu)
            let imm = ((instruction & 0x80000000) >> 19) // imm[12]
                | ((instruction & 0x7e000000) >> 20) // imm[10:5]
                | ((instruction & 0x00000f00) >> 7) // imm[4:1]
                | ((instruction & 0x00000080) << 4); // imm[11]

            // Sign-extend the immediate
            let offset = if (imm & 0x1000) != 0 {
                imm | 0xffffe000
            } else {
                imm
            };

            let rs1_value = get_ureg(rs1 as usize);
            let rs2_value = get_ureg(rs2 as usize);
            let should_branch = match funct3 {
                0x0 => rs1_value == rs2_value,                   // beq
                0x1 => rs1_value != rs2_value,                   // bne
                0x4 => (rs1_value as i32) < (rs2_value as i32),  // blt
                0x5 => (rs1_value as i32) >= (rs2_value as i32), // bge
                0x6 => rs1_value < rs2_value,                    // bltu
                0x7 => rs1_value >= rs2_value,                   // bgeu
                _ => false,
            };

            if should_branch {
                let target_pc = (mepc as i32).wrapping_add(offset as i32) as usize;
                debug_print!(
                    "Branch taken: PC={:#010x} + {:#x} = {:#010x}",
                    mepc,
                    offset,
                    target_pc
                );
                // Set MEPC to the target address (circuit bug: subtract 4)
                unsafe { MEPC_PTR.write_volatile(target_pc.wrapping_sub(4)) };
            } else {
                debug_print!("Branch not taken, continuing sequentially");
                // Set MEPC to next instruction
                unsafe { MEPC_PTR.write_volatile(mepc) };
            }
            mret()
        }
        0x6f => {
            // JAL (Jump and Link)
            let imm = ((instruction & 0x80000000) >> 11) // imm[20]
                | ((instruction & 0x7fe00000) >> 20) // imm[10:1]
                | ((instruction & 0x00100000) >> 9) // imm[11]
                | (instruction & 0x000ff000); // imm[19:12]

            // Sign-extend the immediate
            let offset = if (imm & 0x100000) != 0 {
                imm | 0xffe00000
            } else {
                imm
            };

            let target_pc = (mepc as i32).wrapping_add(offset as i32) as usize;
            let return_addr = mepc + 4;

            debug_print!(
                "JAL: PC={:#010x} + {:#x} = {:#010x}, return={:#010x}",
                mepc,
                offset,
                target_pc,
                return_addr
            );

            // Save return address in rd
            set_ureg(rd as usize, return_addr as u32);
            // Set MEPC to the target address (circuit bug: subtract 4)
            unsafe { MEPC_PTR.write_volatile(target_pc.wrapping_sub(4)) };
            mret()
        }
        0x67 => {
            // JALR (Jump and Link Register)
            let imm = (instruction & 0xfff00000) >> 20; // Sign-extended 12-bit immediate

            let rs1_value = get_ureg(rs1 as usize);
            let target_pc = ((rs1_value as i32).wrapping_add(imm as i32) as usize) & !1; // Clear LSB
            let return_addr = mepc + 4;

            debug_print!(
                "JALR: x{}({:#010x}) + {:#x} = {:#010x}, return={:#010x}",
                rs1,
                rs1_value,
                imm,
                target_pc,
                return_addr
            );

            // Save return address in rd
            set_ureg(rd as usize, return_addr as u32);
            // Set MEPC to the target address (circuit bug: subtract 4)
            unsafe { MEPC_PTR.write_volatile(target_pc.wrapping_sub(4)) };
            mret()
        }
        _ => {
            kpanic!(
                "Instruction address misaligned trap: unsupported opcode {:#02x} at PC {:#010x}",
                opcode,
                mepc
            );
        }
    }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn instruction_fault_dispatch() -> ! {
    kpanic!("Instruction access fault trap - not implemented");
}

#[unsafe(no_mangle)]
unsafe extern "C" fn breakpoint_dispatch() -> ! {
    kpanic!("Breakpoint trap - not implemented");
}

#[unsafe(no_mangle)]
unsafe extern "C" fn load_address_misaligned_dispatch() -> ! {
    kpanic!("Load address misaligned trap - not implemented");
}

#[unsafe(no_mangle)]
unsafe extern "C" fn load_access_fault_dispatch() -> ! {
    let epc = unsafe { MEPC_PTR.read_volatile() };
    kpanic!(
        "Load access fault trap - not implemented, at PC: {:#010x}",
        epc
    );
}

#[unsafe(no_mangle)]
unsafe extern "C" fn store_address_misaligned_dispatch() -> ! {
    kpanic!("Store address misaligned trap - not implemented");
}

#[unsafe(no_mangle)]
unsafe extern "C" fn store_access_fault_dispatch() -> ! {
    kpanic!("Store access fault trap - not implemented");
}
