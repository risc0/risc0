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

use core::{alloc::Layout, ptr::NonNull};

use no_std_strings::{str256, str_format};
use rlsf::Tlsf;
use softfloat_sys::{
    f32_add, f32_div, f32_eq, f32_isSignalingNaN, f32_le, f32_lt, f32_lt_quiet, f32_mul,
    f32_mulAdd, f32_sqrt, f32_sub, f32_to_f64, f32_to_i32, f32_to_ui32, f64_add, f64_div, f64_eq,
    f64_isSignalingNaN, f64_le, f64_lt, f64_lt_quiet, f64_mul, f64_mulAdd, f64_sqrt, f64_sub,
    f64_to_f32, f64_to_i32, f64_to_ui32, float32_t, float64_t, i32_to_f32, i32_to_f64,
    softfloat_exceptionFlags_read_helper, softfloat_exceptionFlags_write_helper,
    softfloat_roundingMode_read_helper, softfloat_roundingMode_write_helper, ui32_to_f32,
    ui32_to_f64,
};

const REG_SP: usize = 2;
const REG_A0: usize = 10;
const REG_A1: usize = 11;
const REG_A2: usize = 12;
const REG_A3: usize = 13;
const REG_A4: usize = 14;
const REG_A5: usize = 15;
// const REG_A6: usize = 16;
const REG_A7: usize = 17;

// Floating point register constants
const NUM_FP_REGS: usize = 32;
const FP_REG_SIZE: usize = 8; // 64-bit registers
const FP_REGS_SIZE: usize = NUM_FP_REGS * FP_REG_SIZE; // 256 bytes total

const USER_REGS_PTR: *mut u32 = 0xffff_0080 as *mut u32;
const MEPC_PTR: *mut usize = 0xffff_0200 as *mut usize;
// Floating point register storage area (32 x 64-bit registers = 256 bytes)
const FP_REGS_PTR: *mut u64 = 0xfff_4000 as *mut u64;
// Floating point control and status register (FCSR) storage
const FCSR_PTR: *mut u32 = 0xfff_4100 as *mut u32;
const USER_START_PTR: *const usize = 0x0001_0000 as *const usize;
const USER_STACK_ADDR: usize = 0xbfff_0000;
const USER_STACK_PTR: *const usize = USER_STACK_ADDR as *const usize;
const USER_STACK_SIZE: usize = 2 * 1024 * 1024;
const USER_HEAP_START_ADDR: usize = 0x0800_0000; // TODO: figure out where data ends in user program
const USER_HEAP_START_PTR: *const u8 = USER_HEAP_START_ADDR as *const u8;
const USER_HEAP_SIZE: usize = 0x40000000;
const USER_HEAP_END_ADDR: usize = USER_HEAP_START_ADDR + USER_HEAP_SIZE;
const USER_PHENT_SIZE: usize = 32; // ELF32_Phdr size in bytes

const ARGC: usize = 1;
const PROGRAM_NAME: &[u8] = b"r0vm";
const PAGE_SIZE: usize = 4096;
// const AT_VECTOR_SIZE_BASE: usize = 20;
// const AT_VECTOR_SIZE_ARCH: usize = 7;
// const AT_VECTOR_SIZE: usize = 2 * (AT_VECTOR_SIZE_ARCH + AT_VECTOR_SIZE_BASE + 1);
const ASCII_TABLE_PTR: *const u8 = 0xbfff_0200 as *const u8;

/// Program header table address (stored in memory)
const USER_PHDR_ADDR_PTR: *const usize = 0xffff_3000 as *const usize;
/// Program header count address (stored in memory)
const USER_PHDR_NUM_ADDR_PTR: *const usize = 0xffff_3008 as *const usize;

const SYS_IOCTL: u32 = 29;
const SYS_READ: u32 = 63;
const SYS_WRITE: u32 = 64;
const SYS_WRITEV: u32 = 66;
const SYS_EXIT: u32 = 93;
const SYS_EXIT_GROUP: u32 = 94;
const SYS_SET_TID_ADDRESS: u32 = 96;
const SYS_TKILL: u32 = 130;
const SYS_SIGALTSTACK: u32 = 132;
const SYS_RT_SIGACTION: u32 = 134;
const SYS_RT_SIGPROCMASK: u32 = 135;
const SYS_BRK: u32 = 214;
const SYS_MUNMAP: u32 = 215;
const SYS_MMAP: u32 = 222;
const SYS_PPOLL: u32 = 414;

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

fn get_ureg(idx: usize) -> u32 {
    // x0 (register 0) should always return 0
    if idx == 0 {
        return 0;
    }
    unsafe { USER_REGS_PTR.add(idx).read() }
}

fn set_ureg(idx: usize, word: u32) {
    // Guard against writing to x0 (register 0) - it should always remain 0
    if idx == 0 {
        return;
    }
    unsafe { USER_REGS_PTR.add(idx).write_volatile(word) };
}

fn get_fp_reg(idx: usize) -> u64 {
    unsafe { FP_REGS_PTR.add(idx).read() }
}

fn set_fp_reg(idx: usize, value: u64) {
    unsafe { FP_REGS_PTR.add(idx).write_volatile(value) };
}

fn init_fp_regs() {
    // Initialize all floating point registers to zero
    for i in 0..NUM_FP_REGS {
        set_fp_reg(i, 0);
    }
}

// FCSR (Floating Point Control and Status Register) access functions
// These integrate with softfloat's global state
fn get_fcsr() -> u32 {
    let fflags = unsafe { softfloat_exceptionFlags_read_helper() } as u32;
    let frm = unsafe { softfloat_roundingMode_read_helper() } as u32;
    fflags | (frm << 5)
}

fn set_fcsr(value: u32) {
    let fflags = value & 0x1F;
    let frm = (value >> 5) & 0x7;
    unsafe {
        softfloat_exceptionFlags_write_helper(fflags as u8);
        softfloat_roundingMode_write_helper(frm as u8);
    }
}

fn get_fflags() -> u32 {
    (unsafe { softfloat_exceptionFlags_read_helper() }) as u32
}

fn set_fflags(value: u32) {
    unsafe { softfloat_exceptionFlags_write_helper((value & 0x1F) as u8) };
}

fn get_frm() -> u32 {
    (unsafe { softfloat_roundingMode_read_helper() }) as u32
}

fn set_frm(value: u32) {
    unsafe { softfloat_roundingMode_write_helper((value & 0x7) as u8) };
}

// Floating point register access macros (similar to riscv-pk)
fn get_fp_reg_from_insn(insn: u32, pos: u32) -> u64 {
    let reg_idx = ((insn >> pos) & 0x1f) as usize;
    get_fp_reg(reg_idx)
}

fn set_fp_reg_from_insn(insn: u32, pos: u32, value: u64) {
    let reg_idx = ((insn >> pos) & 0x1f) as usize;
    set_fp_reg(reg_idx, value);
}

// Floating point register access for specific instruction fields
fn get_f32_rs1(insn: u32) -> u32 {
    get_fp_reg_from_insn(insn, 15) as u32
}

fn get_f32_rs2(insn: u32) -> u32 {
    get_fp_reg_from_insn(insn, 20) as u32
}

fn get_f32_rs3(insn: u32) -> u32 {
    get_fp_reg_from_insn(insn, 27) as u32
}

fn get_f64_rs1(insn: u32) -> u64 {
    get_fp_reg_from_insn(insn, 15)
}

fn get_f64_rs2(insn: u32) -> u64 {
    get_fp_reg_from_insn(insn, 20)
}

fn get_f64_rs3(insn: u32) -> u64 {
    get_fp_reg_from_insn(insn, 27)
}

fn set_f32_rd(insn: u32, value: u32) {
    set_fp_reg_from_insn(insn, 7, value as u64);
}

fn set_f64_rd(insn: u32, value: u64) {
    let rd = (insn >> 7) & 0x1f;
    let msg_debug = str_format!(
        str256,
        "DEBUG: set_f64_rd: storing {:#016x} to f{}",
        value,
        rd
    );
    print(&msg_debug);
    set_fp_reg_from_insn(insn, 7, value);
}

// Floating point instruction precision and rounding mode extraction
fn get_precision(insn: u32) -> u32 {
    (insn >> 25) & 3
}

fn get_rm(insn: u32) -> u32 {
    (insn >> 12) & 7
}

const PRECISION_S: u32 = 0; // Single precision (32-bit)
const PRECISION_D: u32 = 1; // Double precision (64-bit)

// Main floating point emulation function
unsafe fn emulate_fp_instruction(insn: u32, mepc: usize) -> ! {
    let funct7 = (insn >> 25) & 0x7f;
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let rs2 = (insn >> 20) & 0x1f;

    // Setup static rounding mode (equivalent to riscv-pk's SETUP_STATIC_ROUNDING)
    let rm = (insn >> 12) & 0x7; // funct3 field contains rounding mode
    let rounding_mode = if rm == 7 {
        get_frm() as u8 // Dynamic rounding mode from FCSR
    } else {
        rm as u8 // Static rounding mode from instruction
    };
    softfloat_roundingMode_write_helper(rounding_mode);

    let msg = str_format!(
        str256,
        "Emulating FP instruction at PC: {:#010x}, funct7={:#02x}, funct3={}, rd={}, rs1={}, rs2={}, rm={}",
        mepc, funct7, funct3, rd, rs1, rs2, rm
    );
    print(&msg);

    // Floating point registers should be initialized at startup, not on every instruction

    // Dispatch based on funct7 (main opcode for floating point instructions)
    match funct7 {
        0x00 => emulate_fadd(insn),    // FADD.S
        0x01 => emulate_fadd(insn),    // FADD.D
        0x04 => emulate_fsub(insn),    // FSUB.S
        0x05 => emulate_fsub(insn),    // FSUB.D
        0x08 => emulate_fmul(insn),    // FMUL.S
        0x09 => emulate_fmul(insn),    // FMUL.D
        0x0c => emulate_fdiv(insn),    // FDIV.S
        0x0d => emulate_fdiv(insn),    // FDIV.D
        0x10 => emulate_fsgnj(insn),   // FSGNJ.S
        0x11 => emulate_fsgnj(insn),   // FSGNJ.D
        0x14 => emulate_fmin(insn),    // FMIN.S
        0x15 => emulate_fmin(insn),    // FMIN.D
        0x20 => emulate_fcvt_ff(insn), // FCVT.S.D
        0x21 => emulate_fcvt_ff(insn), // FCVT.D.S
        0x2c => emulate_fsqrt(insn),   // FSQRT.S
        0x2d => emulate_fsqrt(insn),   // FSQRT.D
        0x50 => emulate_fcmp(insn),    // FCMP.S (FEQ, FLT, FLE)
        0x51 => emulate_fcmp(insn),    // FCMP.D (FEQ, FLT, FLE)
        0x60 => emulate_fcvt_if(insn), // FCVT (float to int)
        0x61 => emulate_fcvt_if(insn), // FCVT (double to int)
        0x68 => emulate_fcvt_fi(insn), // FCVT (int to float)
        0x69 => emulate_fcvt_fi(insn), // FCVT (int to double)
        0x43 => emulate_fmadd(insn),   // FMADD.S
        0x44 => emulate_fmadd(insn),   // FMADD.D
        0x47 => emulate_fmadd(insn),   // FMSUB.S
        0x48 => emulate_fmadd(insn),   // FMSUB.D
        0x4b => emulate_fmadd(insn),   // FNMSUB.S
        0x4c => emulate_fmadd(insn),   // FNMSUB.D
        0x4f => emulate_fmadd(insn),   // FNMADD.S
        0x4e => emulate_fmadd(insn),   // FNMADD.D
        0x70 => emulate_fmv_if(insn),  // FMV (float to int)
        0x78 => emulate_fmv_fi(insn),  // FMV (int to float)
        _ => {
            let msg = str_format!(str256, "Unsupported FP instruction: funct7={:#02x}", funct7);
            print(&msg);
            host_terminate(1, 0);
        }
    }
}

// Floating point arithmetic operations
fn emulate_fadd(insn: u32) -> ! {
    let precision = get_precision(insn);

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        // Use proper softfloat addition
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_add(f32_rs1, f32_rs2) };

        // Check if result is NaN and normalize to canonical NaN if needed
        let normalized_result =
            if (result.v & 0x7f800000) == 0x7f800000 && (result.v & 0x007fffff) != 0 {
                // This is a NaN, normalize to canonical quiet NaN
                0x7fc00000
            } else {
                result.v
            };

        set_f32_rd(insn, normalized_result);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        // Use proper softfloat addition
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_add(f64_rs1, f64_rs2) };

        // Check if result is NaN and normalize to canonical NaN if needed
        let normalized_result = if (result.v & 0x7ff0000000000000) == 0x7ff0000000000000
            && (result.v & 0x000fffffffffffff) != 0
        {
            // This is a NaN, normalize to canonical quiet NaN
            0x7ff8000000000000
        } else {
            result.v
        };

        set_f64_rd(insn, normalized_result);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fsub(insn: u32) -> ! {
    let precision = get_precision(insn);

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Use proper softfloat subtraction - this will automatically call our custom softfloat_raiseFlags
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_sub(f32_rs1, f32_rs2) };

        // Debug: Print operation details
        let msg = str_format!(
            str256,
            "fsub.s: rs1={:#x}, rs2={:#x}, result={:#x}",
            rs1,
            rs2,
            result.v
        );
        print(&msg);

        // Check what softfloat set in its internal state
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        let msg2 = str_format!(str256, "softfloat internal flags: {:#x}", softfloat_flags);
        print(&msg2);

        // Update our FCSR with softfloat's flags
        set_fflags(softfloat_flags as u32);

        let msg3 = str_format!(str256, "FCSR after update: {:#x}", get_fflags());
        print(&msg3);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Use proper softfloat subtraction
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_sub(f64_rs1, f64_rs2) };

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fmul(insn: u32) -> ! {
    let precision = get_precision(insn);

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Use proper softfloat multiplication
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_mul(f32_rs1, f32_rs2) };

        // Debug: Print operation details
        let msg = str_format!(
            str256,
            "fmul.s: rs1={:#x}, rs2={:#x}, result={:#x}",
            rs1,
            rs2,
            result.v
        );
        print(&msg);

        // Check what softfloat set in its internal state
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        let msg2 = str_format!(str256, "softfloat internal flags: {:#x}", softfloat_flags);
        print(&msg2);

        // Update our FCSR with softfloat's flags
        set_fflags(softfloat_flags as u32);

        let msg3 = str_format!(str256, "FCSR after update: {:#x}", get_fflags());
        print(&msg3);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Use proper softfloat multiplication
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_mul(f64_rs1, f64_rs2) };

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fdiv(insn: u32) -> ! {
    let precision = get_precision(insn);

    // Setup rounding mode (funct3 field contains rounding mode)
    let rm = (insn >> 12) & 0x7; // funct3 field contains rounding mode
    let rounding_mode = if rm == 7 {
        get_frm() as u8 // Dynamic rounding mode from FCSR
    } else {
        rm as u8 // Static rounding mode from instruction
    };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        // Clear softfloat flags and set rounding mode before operation
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        // Use proper softfloat division
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_div(f32_rs1, f32_rs2) };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        // Clear softfloat flags and set rounding mode before operation
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        // Use proper softfloat division
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_div(f64_rs1, f64_rs2) };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fsgnj(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rm = get_rm(insn);

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        // Simple sign manipulation (we'll need proper softfloat later)
        let result = match rm {
            0 => (rs1 & 0x7fffffff) | (rs2 & 0x80000000),  // fsgnj
            1 => (rs1 & 0x7fffffff) | (!rs2 & 0x80000000), // fsgnjn
            2 => (rs1 & 0x7fffffff) | ((rs1 ^ rs2) & 0x80000000), // fsgnjx
            _ => {
                let msg = str_format!(str256, "Unsupported fsgnj rm: {}", rm);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_f32_rd(insn, result);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        // Simple sign manipulation (we'll need proper softfloat later)
        let result = match rm {
            0 => (rs1 & 0x7fffffffffffffff) | (rs2 & 0x8000000000000000), // fsgnj
            1 => (rs1 & 0x7fffffffffffffff) | (!rs2 & 0x8000000000000000), // fsgnjn
            2 => (rs1 & 0x7fffffffffffffff) | ((rs1 ^ rs2) & 0x8000000000000000), // fsgnjx
            _ => {
                let msg = str_format!(str256, "Unsupported fsgnj rm: {}", rm);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_f64_rd(insn, result);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fmin(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rm = get_rm(insn);

    if rm >= 2 {
        let msg = str_format!(str256, "Unsupported fmin/fmax rm: {}", rm);
        print(&msg);
        host_terminate(1, 0);
    }

    // Clear softfloat flags before operation
    unsafe {
        softfloat_exceptionFlags_write_helper(0);
    };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };

        // Check if either operand is NaN
        let rs1_is_nan = (rs1 & 0x7f800000) == 0x7f800000 && (rs1 & 0x7fffff) != 0;
        let rs2_is_nan = (rs2 & 0x7f800000) == 0x7f800000 && (rs2 & 0x7fffff) != 0;

        // Follow riscv-pk approach: use proper floating-point comparison
        let arg1 = if rm == 1 { f32_rs2 } else { f32_rs1 };
        let arg2 = if rm == 1 { f32_rs1 } else { f32_rs2 };

        // Special case: handle signed zeros
        let rs1_is_zero = (rs1 & 0x7fffffff) == 0;
        let rs2_is_zero = (rs2 & 0x7fffffff) == 0;

        let result = if rs1_is_nan && rs2_is_nan {
            // Special case: if both operands are NaN, return canonical NaN (test expectation)
            0x7fc00000 // canonical NaN for single precision
        } else if rs1_is_zero && rs2_is_zero {
            // Both are zeros, for fmin return the negative zero, for fmax return the positive zero
            if rm == 0 {
                // fmin
                if rs1 == 0x80000000 || rs2 == 0x80000000 {
                    0x80000000 // return negative zero
                } else {
                    0x00000000 // return positive zero
                }
            } else {
                // fmax
                if rs1 == 0x00000000 || rs2 == 0x00000000 {
                    0x00000000 // return positive zero
                } else {
                    0x80000000 // return negative zero
                }
            }
        } else {
            // riscv-pk logic: use_rs1 = f32_lt_quiet(arg1, arg2) || isNaNF32UI(rs2)
            let use_rs1 = unsafe { f32_lt_quiet(arg1, arg2) } || rs2_is_nan;
            if use_rs1 {
                rs1
            } else {
                rs2
            }
        };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f32_rd(insn, result);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };

        // Check if either operand is NaN
        let rs1_is_nan =
            (rs1 & 0x7ff0000000000000) == 0x7ff0000000000000 && (rs1 & 0xfffffffffffff) != 0;
        let rs2_is_nan =
            (rs2 & 0x7ff0000000000000) == 0x7ff0000000000000 && (rs2 & 0xfffffffffffff) != 0;

        // Special case: if both operands are NaN, return canonical NaN (test expectation)
        let result = if rs1_is_nan && rs2_is_nan {
            0x7ff8000000000000 // canonical NaN
        } else {
            // Special case: handle signed zeros
            let rs1_is_zero = (rs1 & 0x7fffffffffffffff) == 0;
            let rs2_is_zero = (rs2 & 0x7fffffffffffffff) == 0;

            if rs1_is_zero && rs2_is_zero {
                // Both are zeros, for fmin return the negative zero, for fmax return the positive zero
                if rm == 0 {
                    // fmin
                    if rs1 == 0x8000000000000000 || rs2 == 0x8000000000000000 {
                        0x8000000000000000 // return negative zero
                    } else {
                        0x0000000000000000 // return positive zero
                    }
                } else {
                    // fmax
                    if rs1 == 0x0000000000000000 || rs2 == 0x0000000000000000 {
                        0x0000000000000000 // return positive zero
                    } else {
                        0x8000000000000000 // return negative zero
                    }
                }
            } else {
                // Follow riscv-pk approach: use proper floating-point comparison
                let arg1 = if rm == 1 { f64_rs2 } else { f64_rs1 };
                let arg2 = if rm == 1 { f64_rs1 } else { f64_rs2 };

                // riscv-pk logic: use_rs1 = f64_lt_quiet(arg1, arg2) || isNaNF64UI(rs2)
                let use_rs1 = unsafe { f64_lt_quiet(arg1, arg2) } || rs2_is_nan;
                if use_rs1 {
                    rs1
                } else {
                    rs2
                }
            }
        };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        // Debug: print flags for NaN test
        if rs1_is_nan || rs2_is_nan {
            let msg = str_format!(
                str256,
                "fmin/fmax NaN: rs1={:x} rs2={:x} result={:x} flags={}",
                rs1,
                rs2,
                result,
                softfloat_flags
            );
            print(&msg);
        }
        // Debug: print for zero test
        if (rs1 == 0x8000000000000000 && rs2 == 0x0000000000000000)
            || (rs1 == 0x0000000000000000 && rs2 == 0x8000000000000000)
        {
            let msg = str_format!(
                str256,
                "fmin/fmax zero: rs1=0x{:x}, rs2=0x{:x}, result=0x{:x}, rm={}, flags={}",
                rs1,
                rs2,
                result,
                rm,
                softfloat_flags
            );
            print(&msg);
        }
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result);
    } else {
        let msg = str_format!(str256, "Unsupported fmin/fmax precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fsqrt(insn: u32) -> ! {
    let precision = get_precision(insn);

    // Setup rounding mode (funct3 field contains rounding mode)
    let rm = (insn >> 12) & 0x7; // funct3 field contains rounding mode
    let rounding_mode = if rm == 7 {
        get_frm() as u8 // Dynamic rounding mode from FCSR
    } else {
        rm as u8 // Static rounding mode from instruction
    };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        // Clear softfloat flags and set rounding mode before operation
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        // Use proper softfloat square root
        let f32_rs1 = float32_t { v: rs1 };
        let result = unsafe { f32_sqrt(f32_rs1) };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        // Clear softfloat flags and set rounding mode before operation
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        // Use proper softfloat square root
        let f64_rs1 = float64_t { v: rs1 };
        let result = unsafe { f64_sqrt(f64_rs1) };

        // Update FCSR with softfloat flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fcmp(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rm = get_rm(insn);
    let rd = (insn >> 7) & 0x1f;

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = match rm {
            0 => {
                // fle - floating point less than or equal
                if unsafe { f32_le(f32_rs1, f32_rs2) } {
                    1
                } else {
                    0
                }
            }
            1 => {
                // flt - floating point less than
                if unsafe { f32_lt(f32_rs1, f32_rs2) } {
                    1
                } else {
                    0
                }
            }
            2 => {
                // feq - floating point equal
                if unsafe { f32_eq(f32_rs1, f32_rs2) } {
                    1
                } else {
                    0
                }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcmp rm: {}", rm);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_ureg(rd as usize, result);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = match rm {
            0 => {
                // fle - floating point less than or equal
                if unsafe { f64_le(f64_rs1, f64_rs2) } {
                    1
                } else {
                    0
                }
            }
            1 => {
                // flt - floating point less than
                if unsafe { f64_lt(f64_rs1, f64_rs2) } {
                    1
                } else {
                    0
                }
            }
            2 => {
                // feq - floating point equal
                if unsafe { f64_eq(f64_rs1, f64_rs2) } {
                    1
                } else {
                    0
                }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcmp rm: {}", rm);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_ureg(rd as usize, result as u32);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fcvt_if(insn: u32) -> ! {
    // Float to integer conversion
    let precision = get_precision(insn);
    let funct3 = (insn >> 12) & 0x7; // This is the rounding mode (rm)
    let rd = (insn >> 7) & 0x1f;
    let rs2 = (insn >> 20) & 0x1f; // This determines signed (0) vs unsigned (1) conversion
                                   // Use funct3 as rounding mode if it's not 111 (DYN), otherwise use FRM
    let rounding_mode = if funct3 == 7 {
        get_frm() as u8
    } else {
        funct3 as u8
    };

    // Clear softfloat exception flags and sync rounding mode before conversion
    unsafe {
        softfloat_exceptionFlags_write_helper(0);
        softfloat_roundingMode_write_helper(rounding_mode);
    }

    let msg = str_format!(
        str256,
        "fcvt_if: insn={:#010x}, precision={}, rs2={}, rd={}, rounding_mode={}",
        insn,
        precision,
        rs2,
        rd,
        rounding_mode
    );
    print(&msg);

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let f32_rs1 = float32_t { v: rs1 };
        let result = match rs2 {
            0 => {
                // fcvt.w.s - signed 32-bit conversion
                unsafe { f32_to_i32(f32_rs1, rounding_mode, true) as u32 }
            }
            1 => {
                // fcvt.wu.s - unsigned 32-bit conversion
                // Follow riscv-pk approach: use softfloat directly and let it handle special cases
                unsafe { f32_to_ui32(f32_rs1, rounding_mode, true) as u32 }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcvt rs2: {}", rs2);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_ureg(rd as usize, result);

        // Sync softfloat exception flags with FCSR for single precision
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);
    } else if precision == PRECISION_D {
        let rs1_reg = (insn >> 15) & 0x1f;
        let rs1 = get_f64_rs1(insn);
        let f64_rs1 = float64_t { v: rs1 };
        let msg = str_format!(
            str256,
            "fcvt_if: rs1_reg={}, double input value: {:#016x}",
            rs1_reg,
            rs1
        );
        print(&msg);
        let result = match rs2 {
            0 => {
                // fcvt.w.d - signed 32-bit conversion
                unsafe { f64_to_i32(f64_rs1, rounding_mode, true) as u32 }
            }
            1 => {
                // fcvt.wu.d - unsigned 32-bit conversion
                // Follow riscv-pk approach: use softfloat directly and let it handle special cases
                unsafe { f64_to_ui32(f64_rs1, rounding_mode, true) as u32 }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcvt rs2: {}", rs2);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_ureg(rd as usize, result);
        let msg = str_format!(str256, "fcvt_if: result={:#010x}", result);
        print(&msg);

        // Sync softfloat exception flags with FCSR for double precision
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);
        let msg = str_format!(
            str256,
            "fcvt_if: result={:#08x}, softfloat_flags={:#02x}, fcsr_flags={:#02x}",
            result,
            softfloat_flags,
            get_fflags()
        );
        print(&msg);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fcvt_fi(insn: u32) -> ! {
    // Integer to float conversion
    let precision = get_precision(insn);
    let funct3 = (insn >> 12) & 0x7;
    let rs2 = (insn >> 20) & 0x1f; // rs2 field determines signed vs unsigned
    let rs1_idx = (insn >> 15) & 0x1f;
    let rs1 = get_ureg(rs1_idx as usize);
    let _rounding_mode = get_frm() as u8;

    // Clear softfloat exception flags before operation
    unsafe { softfloat_exceptionFlags_write_helper(0) };

    let msg = str_format!(
        str256,
        "fcvt_fi: insn={:#010x}, precision={}, funct3={}, rs2={}, rs1={:#010x}",
        insn,
        precision,
        funct3,
        rs2,
        rs1
    );
    print(&msg);

    if precision == PRECISION_S {
        // Single precision output
        let result = match rs2 {
            0 => {
                // W - signed word (32-bit)
                unsafe { i32_to_f32(rs1 as i32) }
            }
            1 => {
                // WU - unsigned word (32-bit)
                unsafe { ui32_to_f32(rs1 as u32) }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcvt rs2: {}", rs2);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        // Double precision output
        let result = match rs2 {
            0 => {
                // W - signed word (32-bit)
                unsafe { i32_to_f64(rs1 as i32) }
            }
            1 => {
                // WU - unsigned word (32-bit)
                unsafe { ui32_to_f64(rs1 as u32) }
            }
            _ => {
                let msg = str_format!(str256, "Unsupported fcvt rs2: {}", rs2);
                print(&msg);
                host_terminate(1, 0);
            }
        };
        set_f64_rd(insn, result.v);
        let msg = str_format!(str256, "fcvt_fi: result={:#016x}", result.v);
        print(&msg);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    // Sync softfloat exception flags with FCSR
    let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
    set_fflags(softfloat_flags as u32);
    let msg = str_format!(
        str256,
        "fcvt_if: softfloat_flags={:#02x}, fcsr_flags={:#02x}",
        softfloat_flags,
        get_fflags()
    );
    print(&msg);

    mret()
}

// Floating-point classification functions
fn classify_f32(value: u32) -> u32 {
    let sign = (value >> 31) & 1;
    let exp = (value >> 23) & 0xff;
    let frac = value & 0x7fffff;

    if exp == 0 {
        if frac == 0 {
            // Zero
            if sign == 0 {
                1 << 4
            } else {
                1 << 3
            } // +0 or -0
        } else {
            // Subnormal
            if sign == 0 {
                1 << 5
            } else {
                1 << 2
            } // +subnormal or -subnormal
        }
    } else if exp == 0xff {
        if frac == 0 {
            // Infinity
            if sign == 0 {
                1 << 7
            } else {
                1 << 0
            } // +inf or -inf
        } else {
            // NaN
            if (frac & 0x400000) != 0 {
                1 << 9
            } else {
                1 << 8
            } // quiet NaN or signaling NaN
        }
    } else {
        // Normal number
        if sign == 0 {
            1 << 6
        } else {
            1 << 1
        } // +normal or -normal
    }
}

fn classify_f64(value: u64) -> u64 {
    let sign = (value >> 63) & 1;
    let exp = (value >> 52) & 0x7ff;
    let frac = value & 0xfffffffffffff;

    if exp == 0 {
        if frac == 0 {
            // Zero
            if sign == 0 {
                1 << 4
            } else {
                1 << 3
            } // +0 or -0
        } else {
            // Subnormal
            if sign == 0 {
                1 << 5
            } else {
                1 << 2
            } // +subnormal or -subnormal
        }
    } else if exp == 0x7ff {
        if frac == 0 {
            // Infinity
            if sign == 0 {
                1 << 7
            } else {
                1 << 0
            } // +inf or -inf
        } else {
            // NaN
            if (frac & 0x8000000000000) != 0 {
                1 << 9
            } else {
                1 << 8
            } // quiet NaN or signaling NaN
        }
    } else {
        // Normal number
        if sign == 0 {
            1 << 6
        } else {
            1 << 1
        } // +normal or -normal
    }
}

fn emulate_fmv_if(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rd = (insn >> 7) & 0x1f;
    let rs2 = (insn >> 20) & 0x1f;
    let funct7 = (insn >> 25) & 0x7f;
    let funct3 = (insn >> 12) & 0x7;

    if rs2 == 0 && funct7 == 0x70 && funct3 == 0x1 {
        // fclass instruction
        if precision == PRECISION_S {
            let rs1 = get_f32_rs1(insn);
            let classification = classify_f32(rs1);
            set_ureg(rd as usize, classification);
        } else if precision == PRECISION_D {
            let rs1 = get_f64_rs1(insn);
            let classification = classify_f64(rs1);
            set_ureg(rd as usize, classification as u32);
        } else {
            let msg = str_format!(str256, "Unsupported fclass precision: {}", precision);
            print(&msg);
            host_terminate(1, 0);
        }
    } else if rs2 == 0 && funct7 == 0x70 && funct3 == 0x0 {
        // fmv.x instruction - Float to integer move
        if precision == PRECISION_S {
            let rs1 = get_f32_rs1(insn);
            set_ureg(rd as usize, rs1);
        } else if precision == PRECISION_D {
            let rs1 = get_f64_rs1(insn);
            set_ureg(rd as usize, rs1 as u32);
        } else {
            let msg = str_format!(str256, "Unsupported fmv.x precision: {}", precision);
            print(&msg);
            host_terminate(1, 0);
        }
    } else if rs2 == 1 {
        // fmv.x instruction - Float to integer move
        if precision == PRECISION_S {
            let rs1 = get_f32_rs1(insn);
            set_ureg(rd as usize, rs1);
        } else if precision == PRECISION_D {
            let rs1 = get_f64_rs1(insn);
            set_ureg(rd as usize, rs1 as u32);
        } else {
            let msg = str_format!(str256, "Unsupported fmv.x precision: {}", precision);
            print(&msg);
            host_terminate(1, 0);
        }
    } else {
        let msg = str_format!(str256, "Unsupported rs2 value for 0x70: {}", rs2);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fmv_fi(insn: u32) -> ! {
    // Integer to float move
    let precision = get_precision(insn);
    let rs1_idx = (insn >> 15) & 0x1f;
    let rs1 = get_ureg(rs1_idx as usize);

    if precision == PRECISION_S {
        set_f32_rd(insn, rs1);
    } else if precision == PRECISION_D {
        set_f64_rd(insn, rs1 as u64);
    } else {
        let msg = str_format!(str256, "Unsupported precision: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fcvt_ff(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rs2 = (insn >> 20) & 0x1f; // rs2 field indicates conversion type

    let msg = str_format!(
        str256,
        "fcvt_ff: insn={:#010x}, precision={}, rs2={}",
        insn,
        precision,
        rs2
    );
    print(&msg);

    let rs1 = (insn >> 15) & 0x1f;
    let rd = (insn >> 7) & 0x1f;
    let msg2 = str_format!(str256, "fcvt_ff: rs1={}, rd={}", rs1, rd);
    print(&msg2);

    if precision == PRECISION_S {
        // Single precision output - convert from double to single
        let msg = str_format!(str256, "fcvt_ff: PRECISION_S branch, rs2={}", rs2);
        print(&msg);
        if rs2 != 1 {
            let msg = str_format!(str256, "Invalid fcvt.s.d: rs2={}", rs2);
            print(&msg);
            host_terminate(1, 0);
        }

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Set rounding mode to RNE (Round to Nearest, ties to Even)
        unsafe { softfloat_roundingMode_write_helper(0) };

        let rs1 = get_f64_rs1(insn);
        let f64_rs1 = float64_t { v: rs1 };
        let msg3 = str_format!(str256, "fcvt_ff: rs1=0x{:x}", rs1);
        print(&msg3);
        let result = unsafe { f64_to_f32(f64_rs1) };
        let msg4 = str_format!(str256, "fcvt_ff: result=0x{:x}", result.v);
        print(&msg4);

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        let msg5 = str_format!(str256, "fcvt_ff: softfloat_flags=0x{:x}", softfloat_flags);
        print(&msg5);
        set_fflags(softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        // Double precision output - convert from single to double
        if rs2 != 0 {
            let msg = str_format!(str256, "Invalid fcvt.d.s: rs2={}", rs2);
            print(&msg);
            host_terminate(1, 0);
        }

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        let rs1 = get_f32_rs1(insn);
        let f32_rs1 = float32_t { v: rs1 };
        let result = unsafe { f32_to_f64(f32_rs1) };

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision for fcvt_ff: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

fn emulate_fmadd(insn: u32) -> ! {
    let precision = get_precision(insn);
    let funct7 = (insn >> 25) & 0x7f;

    // Determine the operation type based on funct7
    let (neg_a, neg_c) = match funct7 {
        0x43 => (false, false), // FMADD:  rs1 * rs2 + rs3
        0x47 => (false, true),  // FMSUB:  rs1 * rs2 - rs3
        0x4b => (true, true),   // FNMSUB: -(rs1 * rs2) - rs3
        0x4f => (true, false),  // FNMADD: -(rs1 * rs2) + rs3
        _ => {
            let msg = str_format!(str256, "Invalid fmadd funct7: {:#02x}", funct7);
            print(&msg);
            host_terminate(1, 0);
        }
    };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        let rs3 = get_f32_rs3(insn);

        // Apply negation by flipping the sign bit
        let rs1_val = if neg_a { rs1 ^ 0x80000000 } else { rs1 };
        let rs3_val = if neg_c { rs3 ^ 0x80000000 } else { rs3 };

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        let f32_rs1 = float32_t { v: rs1_val };
        let f32_rs2 = float32_t { v: rs2 };
        let f32_rs3 = float32_t { v: rs3_val };
        let result = unsafe { f32_mulAdd(f32_rs1, f32_rs2, f32_rs3) };

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        let rs3 = get_f64_rs3(insn);

        // Apply negation by flipping the sign bit
        let rs1_val = if neg_a { rs1 ^ 0x8000000000000000 } else { rs1 };
        let rs3_val = if neg_c { rs3 ^ 0x8000000000000000 } else { rs3 };

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        let f64_rs1 = float64_t { v: rs1_val };
        let f64_rs2 = float64_t { v: rs2 };
        let f64_rs3 = float64_t { v: rs3_val };
        let result = unsafe { f64_mulAdd(f64_rs1, f64_rs2, f64_rs3) };

        // Update our FCSR with softfloat's flags
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        let msg = str_format!(str256, "Unsupported precision for fmadd: {}", precision);
        print(&msg);
        host_terminate(1, 0);
    }

    mret()
}

// Floating point load/store emulation
unsafe fn emulate_fp_load_store(insn: u32, mepc: usize) -> ! {
    let opcode = insn & 0x7f;
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let rs2 = (insn >> 20) & 0x1f;

    // Extract immediate based on instruction type
    let imm = if opcode == 0x27 {
        // S-type immediate for store instructions (opcode 0x27)
        let imm_11_5 = (insn >> 25) & 0x7f;
        let imm_4_0 = (insn >> 7) & 0x1f;
        let imm_raw = (imm_11_5 << 5) | imm_4_0;
        // Sign extend the 12-bit immediate
        if imm_raw & 0x800 != 0 {
            imm_raw | 0xfffff000
        } else {
            imm_raw
        }
    } else {
        // I-type immediate for load instructions (opcode 0x07)
        let imm_raw = (insn >> 20) & 0xfff;
        // Sign extend the 12-bit immediate
        if imm_raw & 0x800 != 0 {
            imm_raw | 0xfffff000
        } else {
            imm_raw
        }
    };

    // Calculate address: rs1 + immediate
    let base_addr = get_ureg(rs1 as usize);
    let addr = base_addr.wrapping_add(imm);

    let msg = str_format!(
        str256,
        "Emulating FP load/store at PC: {:#010x}, opcode={:#02x}, funct3={}, rd={}, rs1={}, addr={:#010x}",
        mepc,
        opcode,
        funct3,
        rd,
        rs1,
        addr
    );
    print(&msg);

    match (opcode, funct3) {
        (0x07, 2) => {
            // flw - floating point load word (32-bit)
            // Check 4-byte alignment
            if addr % 4 != 0 {
                let msg = str_format!(
                    str256,
                    "Address misaligned for flw: {:#010x}, continuing anyway",
                    addr
                );
                print(&msg);
                // For now, continue execution instead of terminating
                // In a real implementation, this should raise a misalignment exception
            }

            // Load 32-bit value from memory
            let value = (addr as *const u32).read_volatile();

            // Store in floating point register (as 32-bit in 64-bit register)
            set_f32_rd(insn, value);

            let msg = str_format!(str256, "flw: loaded {:#010x} into f{}", value, rd);
            print(&msg);
        }
        (0x07, 3) => {
            // fld - floating point load double (64-bit)
            // Check 8-byte alignment
            if addr % 8 != 0 {
                let msg = str_format!(
                    str256,
                    "Address misaligned for fld: {:#010x}, continuing anyway",
                    addr
                );
                print(&msg);
                // For now, continue execution instead of terminating
                // In a real implementation, this should raise a misalignment exception
            }

            // Load 64-bit value from memory
            let value = (addr as *const u64).read_volatile();

            // Store in floating point register
            set_f64_rd(insn, value);

            let msg = str_format!(str256, "fld: loaded {:#016x} into f{}", value, rd);
            print(&msg);
        }
        (0x27, 2) => {
            // fsw - floating point store word (32-bit)
            // Check 4-byte alignment
            if addr % 4 != 0 {
                let msg = str_format!(
                    str256,
                    "Address misaligned for fsw: {:#010x}, continuing anyway",
                    addr
                );
                print(&msg);
                // For now, continue execution instead of terminating
                // In a real implementation, this should raise a misalignment exception
            }

            // Get 32-bit value from floating point register
            let value = get_f32_rs2(insn);

            // Store 32-bit value to memory
            (addr as *mut u32).write_volatile(value);

            let msg = str_format!(str256, "fsw: stored {:#010x} from f{}", value, rs2);
            print(&msg);
        }
        (0x27, 3) => {
            // fsd - floating point store double (64-bit)
            // Check 8-byte alignment
            if addr % 8 != 0 {
                let msg = str_format!(
                    str256,
                    "Address misaligned for fsd: {:#010x}, continuing anyway",
                    addr
                );
                print(&msg);
                // For now, continue execution instead of terminating
                // In a real implementation, this should raise a misalignment exception
            }

            // Get 64-bit value from floating point register
            let msg_debug = str_format!(str256, "DEBUG: About to read from f{} (rs2={})", rs2, rs2);
            print(&msg_debug);
            let value = get_f64_rs2(insn);
            let msg_debug2 = str_format!(str256, "DEBUG: Read value {:#016x} from f{}", value, rs2);
            print(&msg_debug2);

            // Store 64-bit value to memory
            (addr as *mut u64).write_volatile(value);

            let msg = str_format!(
                str256,
                "fsd: stored {:#016x} from f{} at addr {:#010x}",
                value,
                rs2,
                addr
            );
            print(&msg);
        }
        _ => {
            let msg = str_format!(str256, "Unsupported FP load/store funct3: {}", funct3);
            print(&msg);
            host_terminate(1, 0);
        }
    }

    mret()
}

// CSR (Control and Status Register) emulation
unsafe fn emulate_csr_instruction(insn: u32, mepc: usize) -> ! {
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let csr_addr = (insn >> 20) & 0xfff;

    let msg = str_format!(
        str256,
        "Emulating CSR instruction at PC: {:#010x}, funct3={}, rd={}, rs1={}, csr={:#03x}",
        mepc,
        funct3,
        rd,
        rs1,
        csr_addr
    );
    print(&msg);

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

                    let msg = str_format!(
                        str256,
                        "fsflags: read flags {:#02x}, wrote {:#02x}",
                        current_flags,
                        if rs1 != 0 { get_ureg(rs1 as usize) } else { 0 }
                    );
                    print(&msg);
                }
                0x2 => {
                    // csrrs (read and set) - fsflags rs1, fflags
                    let current_flags = get_fflags();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fflags(current_flags | rs1_value);
                    }
                    set_ureg(rd as usize, current_flags);

                    let msg = str_format!(str256, "fsflags: read flags {:#02x}", current_flags);
                    print(&msg);
                }
                0x3 => {
                    // csrrc (read and clear) - fsflags rs1, fflags
                    let current_flags = get_fflags();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fflags(current_flags & !rs1_value);
                    }
                    set_ureg(rd as usize, current_flags);

                    let msg = str_format!(
                        str256,
                        "fsflags: read flags {:#02x}, cleared {:#02x}",
                        current_flags,
                        if rs1 != 0 { get_ureg(rs1 as usize) } else { 0 }
                    );
                    print(&msg);
                }
                0x5 => {
                    // csrrwi (read and write immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrwi, rs1 field contains the immediate
                    set_fflags(imm);
                    set_ureg(rd as usize, current_flags);

                    let msg = str_format!(
                        str256,
                        "fsflags: read flags {:#02x}, wrote immediate {:#02x}",
                        current_flags,
                        imm
                    );
                    print(&msg);
                }
                0x6 => {
                    // csrrsi (read and set immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrsi, rs1 field contains the immediate
                    set_fflags(current_flags | imm);
                    set_ureg(rd as usize, current_flags);

                    let msg = str_format!(
                        str256,
                        "fsflags: read flags {:#02x}, set immediate {:#02x}",
                        current_flags,
                        imm
                    );
                    print(&msg);
                }
                0x7 => {
                    // csrrci (read and clear immediate) - fsflags uimm, fflags
                    let current_flags = get_fflags();
                    let imm = rs1; // In csrrci, rs1 field contains the immediate
                    set_fflags(current_flags & !imm);
                    set_ureg(rd as usize, current_flags);

                    let msg = str_format!(
                        str256,
                        "fsflags: read flags {:#02x}, clear immediate {:#02x}",
                        current_flags,
                        imm
                    );
                    print(&msg);
                }
                _ => {
                    let msg = str_format!(str256, "Unsupported fflags funct3: {}", funct3);
                    print(&msg);
                    host_terminate(1, 0);
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

                    let msg = str_format!(str256, "fsrm: read frm {:#02x}", current_frm);
                    print(&msg);
                }
                _ => {
                    let msg = str_format!(str256, "Unsupported frm funct3: {}", funct3);
                    print(&msg);
                    host_terminate(1, 0);
                }
            }
        }
        0x003 => {
            // fcsr - Floating point control and status register
            match funct3 {
                0x2 => {
                    // csrrs (read and set) - fscsr rs1, fcsr
                    let current_fcsr = get_fcsr();
                    if rs1 != 0 {
                        let rs1_value = get_ureg(rs1 as usize);
                        set_fcsr(current_fcsr | rs1_value);
                    }
                    set_ureg(rd as usize, current_fcsr);

                    let msg = str_format!(str256, "fscsr: read fcsr {:#02x}", current_fcsr);
                    print(&msg);
                }
                _ => {
                    let msg = str_format!(str256, "Unsupported fcsr funct3: {}", funct3);
                    print(&msg);
                    host_terminate(1, 0);
                }
            }
        }
        _ => {
            let msg = str_format!(str256, "Unsupported CSR address: {:#03x}", csr_addr);
            print(&msg);
            host_terminate(1, 0);
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

    fn add_null(&mut self) {
        self.add_word(0);
    }

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

#[no_mangle]
unsafe extern "C" fn kstart() -> ! {
    let user_start_addr = USER_START_PTR.read_volatile() - 4;
    MEPC_PTR.write_volatile(user_start_addr);

    let mut stack = UserStack::new();

    // args
    stack.add_word(ARGC);
    stack.add_str(PROGRAM_NAME);
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
    stack.add_aux_word(AuxType::Phdr, USER_PHDR_ADDR_PTR.read_volatile()); // auxv[5]
    stack.add_aux_word(AuxType::PhNum, USER_PHDR_NUM_ADDR_PTR.read_volatile()); // auxv[6]
    stack.add_aux_word(AuxType::PhEnt, USER_PHENT_SIZE); // auxv[7]
    stack.add_aux_word(AuxType::Null, 0); // auxv[8]

    set_ureg(REG_SP, USER_STACK_PTR as u32);

    let block: &[u8] = core::slice::from_raw_parts(USER_HEAP_START_PTR, USER_HEAP_SIZE);
    #[allow(static_mut_refs)]
    HEAP.insert_free_block_ptr(block.into());

    // Initialize floating point registers to zero at startup
    init_fp_regs();

    // Initialize FCSR to zero at startup
    set_fcsr(0);

    // Initialize softfloat library state
    unsafe {
        softfloat_roundingMode_write_helper(0); // Round to nearest even
        softfloat_exceptionFlags_write_helper(0); // Clear all exception flags
    }

    print("return from kstart");
    mret()
}

fn mret() -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        core::arch::asm!("mret", options(noreturn))
    }
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

#[no_mangle]
unsafe extern "C" fn ecall_dispatch() -> ! {
    let nr = get_ureg(REG_A7);

    let msg = str_format!(str256, "syscall: {nr} (a7={})", get_ureg(17));
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

    mret()
}

#[no_mangle]
unsafe extern "C" fn illegal_instruction_dispatch() -> ! {
    // Get the saved PC from MEPC (where the illegal instruction occurred)
    let mepc = MEPC_PTR.read_volatile();

    // Read the instruction as a u32
    let instruction = (mepc as *const u32).read_volatile();

    // Decode instruction fields
    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    let funct7 = (instruction & 0xfe000000) >> 25;

    // Check if this is a fence instruction (0x0ff0000f)
    if instruction == 0x0ff0000f {
        // Fence instruction - treat as null-op and continue
        // mret will automatically increment MEPC by 4, so we don't need to do anything
        let msg = str_format!(str256, "Emulating fence instruction at PC: {:#010x}", mepc);
        print(&msg);
        mret()
    }

    // Check for floating point operations (opcode 0x53)
    if opcode == 0x53 {
        return emulate_fp_instruction(instruction, mepc);
    }

    // Check for floating point load/store operations (opcode 0x07 = Load-FP, 0x27 = Store-FP)
    if opcode == 0x07 || opcode == 0x27 {
        return emulate_fp_load_store(instruction, mepc);
    }

    // Check for CSR operations (opcode 0x73)
    if opcode == 0x73 {
        return emulate_csr_instruction(instruction, mepc);
    }

    // Check for RV32A atomic memory operations
    if opcode == 0x2f {
        let funct5 = (funct7 & 0b1111100) >> 2;
        let _aq = (funct7 & 0b0000010) >> 1; // acquire access
        let _rl = funct7 & 0b0000001; // release access

        match (funct3, funct5) {
            (0x2, 0x00) => {
                // amoadd.w - atomic memory operation: add word
                let msg = str_format!(
                    str256,
                    "Emulating amoadd.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to add from rs2 register
                let add_value = get_ureg(rs2 as usize);

                // Perform atomic add operation
                let new_value = current_value.wrapping_add(add_value);
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x01) => {
                // amoswap.w - atomic memory operation: swap word
                let msg = str_format!(
                    str256,
                    "Emulating amoswap.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to swap from rs2 register
                let swap_value = get_ureg(rs2 as usize);

                // Perform atomic swap operation
                (addr as *mut u32).write_volatile(swap_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x04) => {
                // amoxor.w - atomic memory operation: XOR word
                let msg = str_format!(
                    str256,
                    "Emulating amoxor.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to XOR from rs2 register
                let xor_value = get_ureg(rs2 as usize);

                // Perform atomic XOR operation
                let new_value = current_value ^ xor_value;
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x08) => {
                // amoor.w - atomic memory operation: OR word
                let msg = str_format!(
                    str256,
                    "Emulating amoor.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to OR from rs2 register
                let or_value = get_ureg(rs2 as usize);

                // Perform atomic OR operation
                let new_value = current_value | or_value;
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x0c) => {
                // amoand.w - atomic memory operation: AND word
                let msg = str_format!(
                    str256,
                    "Emulating amoand.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to AND from rs2 register
                let and_value = get_ureg(rs2 as usize);

                // Perform atomic AND operation
                let new_value = current_value & and_value;
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x10) => {
                // amomin.w - atomic memory operation: minimum word (signed)
                let msg = str_format!(
                    str256,
                    "Emulating amomin.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

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
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x14) => {
                // amomax.w - atomic memory operation: maximum word (signed)
                let msg = str_format!(
                    str256,
                    "Emulating amomax.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

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
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x18) => {
                // amominu.w - atomic memory operation: minimum word (unsigned)
                let msg = str_format!(
                    str256,
                    "Emulating amominu.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to compare from rs2 register
                let compare_value = get_ureg(rs2 as usize);

                // Perform atomic minimum operation (unsigned comparison)
                let new_value = if current_value < compare_value {
                    current_value
                } else {
                    compare_value
                };
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

                mret()
            }
            (0x2, 0x1c) => {
                // amomaxu.w - atomic memory operation: maximum word (unsigned)
                let msg = str_format!(
                    str256,
                    "Emulating amomaxu.w at PC: {:#010x}, rd={}, rs1={}, rs2={}",
                    mepc,
                    rd,
                    rs1,
                    rs2
                );
                print(&msg);

                // Get address from rs1 register
                let addr = get_ureg(rs1 as usize);

                // Check alignment (4-byte aligned for 32-bit words)
                if addr % 4 != 0 {
                    let msg = str_format!(str256, "Address misaligned: {:#010x}", addr);
                    print(&msg);
                    host_terminate(1, 0);
                }

                // Read current value from memory
                let current_value = (addr as *const u32).read_volatile();

                // Get value to compare from rs2 register
                let compare_value = get_ureg(rs2 as usize);

                // Perform atomic maximum operation (unsigned comparison)
                let new_value = if current_value > compare_value {
                    current_value
                } else {
                    compare_value
                };
                (addr as *mut u32).write_volatile(new_value);

                // Write original value to rd register
                // XXX check for rd = 0?
                set_ureg(rd as usize, current_value);

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

    // Log the illegal instruction event
    let msg = str_format!(
        str256,
        "Illegal instruction at PC: {:#010x}, instr: {:#010x}",
        mepc,
        instruction
    );
    print(&msg);

    // Terminate the program with error code
    host_terminate(1, 0);
}

fn print(msg: &str) {
    let msg = msg.as_bytes();
    host_log(msg.as_ptr(), msg.len());
}

fn host_terminate(_a0: u32, _a1: u32) -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        const HOST_ECALL_TERMINATE: u32 = 0;
        core::arch::asm!("ecall",
            in("a7") HOST_ECALL_TERMINATE,
            in("a0") _a0,
            in("a1") _a1,
            options(noreturn)
        )
    };
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

fn host_log(_msg_ptr: *const u8, _msg_len: usize) {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        const HOST_ECALL_WRITE: u32 = 2;
        core::arch::asm!("ecall",
            in("a7") HOST_ECALL_WRITE,
            in("a0") 0,
            in("a1") _msg_ptr,
            in("a2") _msg_len,
        )
    };
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
