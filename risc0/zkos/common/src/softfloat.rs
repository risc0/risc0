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

use softfloat_sys::{
    f32_add, f32_div, f32_eq, f32_le, f32_lt, f32_lt_quiet, f32_mul, f32_mulAdd, f32_sqrt, f32_sub,
    f32_to_f64, f32_to_i32, f32_to_ui32, f64_add, f64_div, f64_eq, f64_le, f64_lt, f64_lt_quiet,
    f64_mul, f64_mulAdd, f64_sqrt, f64_sub, f64_to_f32, f64_to_i32, f64_to_ui32, float32_t,
    float64_t, i32_to_f32, i32_to_f64, softfloat_exceptionFlags_read_helper,
    softfloat_exceptionFlags_write_helper, softfloat_roundingMode_read_helper,
    softfloat_roundingMode_write_helper, ui32_to_f32, ui32_to_f64,
};

use crate::{constants::KERNEL_START_ADDR, get_ureg, mret, set_ureg};

const NUM_FP_REGS: usize = 32;
static mut FP_REGS: [u64; NUM_FP_REGS] = [0u64; NUM_FP_REGS];

pub fn init_softfloat() {
    init_fp_regs();

    // Initialize FCSR to zero at startup
    set_fcsr(0);

    // Initialize softfloat library state
    unsafe {
        softfloat_roundingMode_write_helper(0); // Round to nearest even
        softfloat_exceptionFlags_write_helper(0); // Clear all exception flags
    }
}

pub fn handle_float_csr_exception(funct3: u32, rs1: u32, rd: u32) {
    // fflags - Floating point exception flags
    match funct3 {
        0x1 => {
            // csrrw (read and write) - fsflags rs1, fflags
            let current_flags = get_fflags();
            let rs1_value = get_ureg(rs1 as usize);
            set_fflags(rs1_value);
            set_ureg(rd as usize, current_flags);
        }
        0x2 => {
            // csrrs (read and set) - fsflags rs1, fflags
            let current_flags = get_fflags();
            if rs1 != 0 {
                let rs1_value = get_ureg(rs1 as usize);
                set_fflags(current_flags | rs1_value);
            }
            set_ureg(rd as usize, current_flags);
        }
        0x3 => {
            // csrrc (read and clear) - fsflags rs1, fflags
            let current_flags = get_fflags();
            if rs1 != 0 {
                let rs1_value = get_ureg(rs1 as usize);
                set_fflags(current_flags & !rs1_value);
            }
            set_ureg(rd as usize, current_flags);
        }
        0x5 => {
            // csrrwi (read and write immediate) - fsflags uimm, fflags
            let current_flags = get_fflags();
            let imm = rs1; // In csrrwi, rs1 field contains the immediate
            set_fflags(imm);
            set_ureg(rd as usize, current_flags);
        }
        0x6 => {
            // csrrsi (read and set immediate) - fsflags uimm, fflags
            let current_flags = get_fflags();
            let imm = rs1; // In csrrsi, rs1 field contains the immediate
            set_fflags(current_flags | imm);
            set_ureg(rd as usize, current_flags);
        }
        0x7 => {
            // csrrci (read and clear immediate) - fsflags uimm, fflags
            let current_flags = get_fflags();
            let imm = rs1; // In csrrci, rs1 field contains the immediate
            set_fflags(current_flags & !imm);
            set_ureg(rd as usize, current_flags);
        }
        _ => {
            panic!("Unsupported fflags funct3: {}", funct3);
        }
    }
}

pub fn handle_float_csr_frm(funct3: u32, rs1: u32, rd: u32) {
    // frm - Floating point rounding mode
    match funct3 {
        0x1 => {
            // csrrw (read and write) - fsrm rs1, frm
            let current_frm = get_frm();
            let rs1_value = get_ureg(rs1 as usize);
            set_frm(rs1_value);
            set_ureg(rd as usize, current_frm);
        }
        0x2 => {
            // csrrs (read and set) - fsrm rs1, frm
            let current_frm = get_frm();
            if rs1 != 0 {
                let rs1_value = get_ureg(rs1 as usize);
                set_frm(current_frm | rs1_value);
            }
            set_ureg(rd as usize, current_frm);
        }
        0x5 => {
            // csrrwi (read and write immediate) - fsrm rs1, frm
            let current_frm = get_frm();
            let immediate_value = rs1; // rs1 field contains the immediate value
            set_frm(immediate_value);
            set_ureg(rd as usize, current_frm);
        }
        _ => {
            panic!("Unsupported frm funct3: {}", funct3);
        }
    }
}

pub fn handle_float_csr_fcsr(funct3: u32, rs1: u32, rd: u32) {
    // fcsr - Floating point control and status register
    match funct3 {
        0x1 => {
            // csrrw (read and write) - fscsr rs1, fcsr
            let current_fcsr = get_fcsr();
            let rs1_value = get_ureg(rs1 as usize);
            set_fcsr(rs1_value);
            set_ureg(rd as usize, current_fcsr);
        }
        0x2 => {
            // csrrs (read and set) - fscsr rs1, fcsr
            let current_fcsr = get_fcsr();
            if rs1 != 0 {
                let rs1_value = get_ureg(rs1 as usize);
                set_fcsr(current_fcsr | rs1_value);
            }
            set_ureg(rd as usize, current_fcsr);
        }
        0x5 => {
            // csrrwi (read and write immediate) - fscsr rs1, fcsr
            let current_fcsr = get_fcsr();
            let immediate_value = rs1; // rs1 field contains the immediate value
            set_fcsr(immediate_value);
            set_ureg(rd as usize, current_fcsr);
        }
        _ => {
            panic!("Unsupported fcsr funct3: {}", funct3);
        }
    }
}

fn get_fp_reg(idx: usize) -> u64 {
    unsafe { FP_REGS[idx] }
}

fn set_fp_reg(idx: usize, value: u64) {
    unsafe {
        FP_REGS[idx] = value;
    };
}

pub fn init_fp_regs() {
    // Initialize all floating point registers to zero
    for i in 0..NUM_FP_REGS {
        set_fp_reg(i, 0);
    }
}

// FCSR (Floating Point Control and Status Register) access functions
// These integrate with softfloat's global state
pub fn get_fcsr() -> u32 {
    let fflags = unsafe { softfloat_exceptionFlags_read_helper() } as u32;
    let frm = unsafe { softfloat_roundingMode_read_helper() } as u32;
    fflags | (frm << 5)
}

pub fn set_fcsr(value: u32) {
    let fflags = value & 0x1F;
    let frm = (value >> 5) & 0x7;
    unsafe {
        softfloat_exceptionFlags_write_helper(fflags as u8);
        softfloat_roundingMode_write_helper(frm as u8);
    }
}

pub fn get_fflags() -> u32 {
    (unsafe { softfloat_exceptionFlags_read_helper() }) as u32
}

pub fn set_fflags(value: u32) {
    unsafe { softfloat_exceptionFlags_write_helper((value & 0x1F) as u8) };
}

pub fn get_frm() -> u32 {
    (unsafe { softfloat_roundingMode_read_helper() }) as u32
}

pub fn set_frm(value: u32) {
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

#[allow(dead_code)]
fn get_f64_rs3(insn: u32) -> u64 {
    get_fp_reg_from_insn(insn, 27)
}

fn set_f32_rd(insn: u32, value: u32) {
    // According to RISC-V spec, single-precision values stored in double-precision registers
    // have their upper 32 bits set to 0xffffffff (NaN-boxing)
    let extended_value = value as u64 | 0xffffffff00000000;
    set_fp_reg_from_insn(insn, 7, extended_value);
}

fn set_f64_rd(insn: u32, value: u64) {
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
pub unsafe fn emulate_fp_instruction(insn: u32, _mepc: usize) -> ! {
    let funct7 = (insn >> 25) & 0x7f;

    // Floating point registers should be initialized at startup, not on every instruction
    // Note: Rounding mode is set by each individual emulation function as needed

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
        0x70 => emulate_fmv_if(insn),  // FMV (float to int)
        0x71 => emulate_fmv_if(insn),  // FCLASS.D
        0x78 => emulate_fmv_fi(insn),  // FMV (int to float)
        _ => {
            panic!("Unsupported FP instruction: funct7={:#02x}", funct7);
        }
    }
}

// Floating point arithmetic operations
fn emulate_fadd(insn: u32) -> ! {
    let precision = get_precision(insn);

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat flags before operation (so only this operation's flags are set)
    unsafe { softfloat_exceptionFlags_write_helper(0) };

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

        // Sync softfloat exception flags back to FCSR
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

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

        // Sync softfloat exception flags back to FCSR
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, normalized_result);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fsub(insn: u32) -> ! {
    let precision = get_precision(insn);

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat flags before operation (so only this operation's flags are set)
    unsafe { softfloat_exceptionFlags_write_helper(0) };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);

        // Use proper softfloat subtraction - this will automatically call our custom softfloat_raiseFlags
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_sub(f32_rs1, f32_rs2) };

        // Check what softfloat set in its internal state
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);

        // Use proper softfloat subtraction
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_sub(f64_rs1, f64_rs2) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fmul(insn: u32) -> ! {
    let precision = get_precision(insn);

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat flags before operation (so only this operation's flags are set)
    unsafe { softfloat_exceptionFlags_write_helper(0) };

    // Get rounding mode from instruction or FCSR
    let rm = get_rm(insn);
    let rounding_mode = if rm == 7 {
        get_frm() as u8 // Dynamic rounding mode from FCSR
    } else {
        rm as u8 // Static rounding mode from instruction
    };
    unsafe { softfloat_roundingMode_write_helper(rounding_mode) };

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);

        // Use proper softfloat multiplication
        let f32_rs1 = float32_t { v: rs1 };
        let f32_rs2 = float32_t { v: rs2 };
        let result = unsafe { f32_mul(f32_rs1, f32_rs2) };

        // Check what softfloat set in its internal state
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);

        // Use proper softfloat multiplication
        let f64_rs1 = float64_t { v: rs1 };
        let f64_rs2 = float64_t { v: rs2 };
        let result = unsafe { f64_mul(f64_rs1, f64_rs2) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision: {}", precision);
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

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();

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

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

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

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision: {}", precision);
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
                panic!("Unsupported fsgnj rm: {}", rm);
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
                panic!("Unsupported fsgnj rm: {}", rm);
            }
        };
        set_f64_rd(insn, result);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fmin(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rm = get_rm(insn);

    if rm >= 2 {
        panic!("Unsupported fmin/fmax rm: {}", rm);
    }

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat flags before operation (so only this operation's flags are set)
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
            if use_rs1 { rs1 } else { rs2 }
        };

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

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
                if use_rs1 { rs1 } else { rs2 }
            }
        };

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result);
    } else {
        panic!("Unsupported fmin/fmax precision: {}", precision);
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

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();

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

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

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

        // Update FCSR with softfloat flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fcmp(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rm = get_rm(insn);
    let rd = (insn >> 7) & 0x1f;

    // Save existing FCSR flags before clearing softfloat's internal flags.
    // Note: get_fflags() reads from softfloat_exceptionFlags, so we must save
    // the accumulated flags BEFORE clearing softfloat's internal state, otherwise
    // we would lose previously accrued exception flags (violating RISC-V spec
    // requirement that flags are accrued across operations until software clears them).
    let existing_fflags = get_fflags();
    // Clear softfloat flags before operation (so only this operation's flags are set)
    unsafe { softfloat_exceptionFlags_write_helper(0) };

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
                panic!("Unsupported fcmp rm: {}", rm);
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
                panic!("Unsupported fcmp rm: {}", rm);
            }
        };
        set_ureg(rd as usize, result as u32);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    // Sync softfloat exception flags to FCSR before returning.
    // The softfloat comparison functions (f32_eq/f32_le/f32_lt and f64_* variants)
    // correctly set the invalid exception flag according to RISC-V spec:
    // - FEQ: only sNaN raises invalid
    // - FLT/FLE: any NaN raises invalid
    let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
    // Accumulate: OR the new flags from this operation with the existing accumulated flags.
    // This preserves flags from previous operations, as required by RISC-V spec (accrued flags).
    // Note: We do NOT clear flags after setting them, because set_fflags() writes to
    // softfloat_exceptionFlags (which is our FCSR storage), and we want the accumulated flags
    // to persist for the next operation. The initial clear at the start of each operation
    // ensures we only capture flags from the current operation.
    set_fflags(existing_fflags | softfloat_flags as u32);

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

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat exception flags and sync rounding mode before conversion
    unsafe {
        softfloat_exceptionFlags_write_helper(0);
        softfloat_roundingMode_write_helper(rounding_mode);
    }

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
            2 => {
                // fcvt.l.s - signed 64-bit conversion (RV64, but might appear in RV32 code)
                // For RV32, treat as 32-bit signed conversion
                unsafe { f32_to_i32(f32_rs1, rounding_mode, true) as u32 }
            }
            3 => {
                // fcvt.lu.s - unsigned 64-bit conversion (RV64)
                // For RV32, treat as 32-bit unsigned conversion
                unsafe { f32_to_ui32(f32_rs1, rounding_mode, true) as u32 }
            }
            _ => {
                panic!("Unsupported fcvt rs2: {} (insn={:#010x})", rs2, insn);
            }
        };
        set_ureg(rd as usize, result);

        // Sync softfloat exception flags with FCSR for single precision (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);
    } else if precision == PRECISION_D {
        let rs1 = get_f64_rs1(insn);
        let f64_rs1 = float64_t { v: rs1 };
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
            2 => {
                // fcvt.l.d - signed 64-bit conversion (RV64)
                // For RV32, treat as 32-bit signed conversion
                unsafe { f64_to_i32(f64_rs1, rounding_mode, true) as u32 }
            }
            3 => {
                // fcvt.lu.d - unsigned 64-bit conversion (RV64)
                // For RV32, treat as 32-bit unsigned conversion
                unsafe { f64_to_ui32(f64_rs1, rounding_mode, true) as u32 }
            }
            _ => {
                panic!("Unsupported fcvt rs2: {} (insn={:#010x})", rs2, insn);
            }
        };
        set_ureg(rd as usize, result);

        // Sync softfloat exception flags with FCSR for double precision (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fcvt_fi(insn: u32) -> ! {
    // Integer to float conversion
    let precision = get_precision(insn);
    let rs1_idx = (insn >> 15) & 0x1f;
    let rs1 = get_ureg(rs1_idx as usize);
    let rs2 = (insn >> 20) & 0x1f;

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();
    // Clear softfloat exception flags and sync rounding mode before conversion
    unsafe {
        softfloat_exceptionFlags_write_helper(0);
        softfloat_roundingMode_write_helper(get_frm() as u8);
    }

    if precision == PRECISION_S {
        // Single precision output
        let result = match rs2 {
            0 => {
                // W - signed word (32-bit)
                unsafe { i32_to_f32(rs1 as i32) }
            }
            1 => {
                // WU - unsigned word (32-bit)
                unsafe { ui32_to_f32(rs1) }
            }
            _ => {
                panic!("Unsupported fcvt rs2: {}", rs2);
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
                unsafe { ui32_to_f64(rs1) }
            }
            _ => {
                panic!("Unsupported fcvt rs2: {}", rs2);
            }
        };
        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    // Sync softfloat exception flags with FCSR (accumulate with existing flags)
    let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
    set_fflags(existing_fflags | softfloat_flags as u32);

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
            if sign == 0 { 1 << 4 } else { 1 << 3 } // +0 or -0
        } else {
            // Subnormal
            if sign == 0 { 1 << 5 } else { 1 << 2 } // +subnormal or -subnormal
        }
    } else if exp == 0xff {
        if frac == 0 {
            // Infinity
            if sign == 0 { 1 << 7 } else { 1 << 0 } // +inf or -inf
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
        if sign == 0 { 1 << 6 } else { 1 << 1 } // +normal or -normal
    }
}

fn classify_f64(value: u64) -> u64 {
    let sign = (value >> 63) & 1;
    let exp = (value >> 52) & 0x7ff;
    let frac = value & 0xfffffffffffff;

    if exp == 0 {
        if frac == 0 {
            // Zero
            if sign == 0 { 1 << 4 } else { 1 << 3 } // +0 or -0
        } else {
            // Subnormal
            if sign == 0 { 1 << 5 } else { 1 << 2 } // +subnormal or -subnormal
        }
    } else if exp == 0x7ff {
        if frac == 0 {
            // Infinity
            if sign == 0 { 1 << 7 } else { 1 << 0 } // +inf or -inf
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
        if sign == 0 { 1 << 6 } else { 1 << 1 } // +normal or -normal
    }
}

fn emulate_fmv_if(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rd = (insn >> 7) & 0x1f;
    let rs2 = (insn >> 20) & 0x1f;
    let funct7 = (insn >> 25) & 0x7f;
    let funct3 = (insn >> 12) & 0x7;

    if rs2 == 0 && (funct7 == 0x70 || funct7 == 0x71) && funct3 == 0x1 {
        // fclass instruction
        if funct7 == 0x70 && precision == PRECISION_S {
            // fclass.s
            let rs1 = get_f32_rs1(insn);
            let classification = classify_f32(rs1);
            set_ureg(rd as usize, classification);
        } else if funct7 == 0x71 && precision == PRECISION_D {
            // fclass.d
            let rs1 = get_f64_rs1(insn);
            let classification = classify_f64(rs1);
            set_ureg(rd as usize, classification as u32);
        } else {
            panic!(
                "Unsupported fclass: funct7=0x{:x}, precision={}",
                funct7, precision
            );
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
            panic!("Unsupported fmv.x precision: {}", precision);
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
            panic!("Unsupported fmv.x precision: {}", precision);
        }
    } else {
        panic!("Unsupported rs2 value for 0x70: {}", rs2);
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
        // fmv.d.x requires RV64 (64-bit integer source)
        // Since get_ureg only returns u32 (32-bit registers), this emulator is RV32
        panic!("fmv.d.x requires RV64");
    } else {
        panic!("Unsupported precision: {}", precision);
    }

    mret()
}

fn emulate_fcvt_ff(insn: u32) -> ! {
    let precision = get_precision(insn);
    let rs2 = (insn >> 20) & 0x1f; // rs2 field indicates conversion type
    let rm = (insn >> 12) & 0x7; // funct3 field contains rounding mode
    let rounding_mode = if rm == 7 {
        get_frm() as u8 // Dynamic rounding mode from FCSR
    } else {
        rm as u8 // Static rounding mode from instruction
    };

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();

    if precision == PRECISION_S {
        // Single precision output - convert from double to single
        if rs2 != 1 {
            panic!("Invalid fcvt.s.d: rs2={}", rs2);
        }

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Set rounding mode from instruction's rm field
        unsafe { softfloat_roundingMode_write_helper(rounding_mode) };

        let rs1 = get_f64_rs1(insn);
        let f64_rs1 = float64_t { v: rs1 };
        let result = unsafe { f64_to_f32(f64_rs1) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        // Double precision output - convert from single to double
        if rs2 != 0 {
            panic!("Invalid fcvt.d.s: rs2={}", rs2);
        }

        // Clear softfloat flags before operation
        unsafe { softfloat_exceptionFlags_write_helper(0) };

        // Set rounding mode from instruction's rm field (for consistency, even though conversion is exact)
        unsafe { softfloat_roundingMode_write_helper(rounding_mode) };

        let rs1 = get_f32_rs1(insn);
        let f32_rs1 = float32_t { v: rs1 };
        let result = unsafe { f32_to_f64(f32_rs1) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f64_rd(insn, result.v);
    } else {
        panic!("Unsupported precision for fcvt_ff: {}", precision);
    }

    mret()
}

pub fn emulate_fmadd(insn: u32) -> ! {
    // R4-type instruction format:
    // [31:27] rs3 (5 bits, 3rd source reg)
    // [26:25] funct2 (2 bits, must be 00 for FMA ops)
    // [24:20] rs2 (5 bits, 2nd source reg)
    // [19:15] rs1 (5 bits, 1st source reg)
    // [14:12] rm (3 bits, rounding mode)
    // [11:7]  rd (5 bits, destination reg)
    // [6:0]   opcode (7 bits, = 1000011 for F[SD]MADD)

    let funct2 = (insn >> 25) & 0x3;
    let rm = (insn >> 12) & 0x7; // rounding mode
    let opcode = insn & 0x7f;

    // Determine precision from funct2 (00 = single, 01 = double)
    let precision = if funct2 == 0 {
        PRECISION_S
    } else {
        PRECISION_D
    };

    // Determine negation from bits 3 and 2 of the instruction (following riscv-pk)
    let neg_a = (insn >> 3) & 1 != 0;
    let neg_c = (insn >> 2) & 1 != 0;

    // Validate that this is a supported R4-type opcode
    match opcode {
        0x43 | 0x47 | 0x4b | 0x4f => {
            // Valid R4-type opcodes
        }
        _ => {
            panic!(
                "Invalid fmadd opcode: {:#02x} (funct2={:#02x}, rm={:#02x})",
                opcode, funct2, rm
            );
        }
    }

    // Save existing FCSR flags before clearing softfloat's internal flags
    let existing_fflags = get_fflags();

    if precision == PRECISION_S {
        let rs1 = get_f32_rs1(insn);
        let rs2 = get_f32_rs2(insn);
        let rs3 = get_f32_rs3(insn);

        // Apply negation by flipping the sign bit
        let rs1_val = if neg_a { rs1 ^ 0x80000000 } else { rs1 };
        let rs3_val = if neg_c { rs3 ^ 0x80000000 } else { rs3 };

        // Clear softfloat flags and set rounding mode before operation
        let rounding_mode = if rm == 7 {
            get_frm() as u8 // Dynamic rounding mode from FCSR
        } else {
            rm as u8 // Static rounding mode from instruction
        };
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        let f32_rs1 = float32_t { v: rs1_val };
        let f32_rs2 = float32_t { v: rs2 };
        let f32_rs3 = float32_t { v: rs3_val };
        let result = unsafe { f32_mulAdd(f32_rs1, f32_rs2, f32_rs3) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        set_f32_rd(insn, result.v);
    } else if precision == PRECISION_D {
        // For R4-type instructions, field layout is:
        // rs1: bits 19-15, rs2: bits 24-20, rs3: bits 31-27, rd: bits 11-7
        let rs1 = get_f64_rs1(insn);
        let rs2 = get_f64_rs2(insn);
        let rs3 = get_fp_reg_from_insn(insn, 27); // rs3 is in bits 31-27 for R4-type

        // Apply negation by flipping the sign bit
        let rs1_val = if neg_a { rs1 ^ 0x8000000000000000 } else { rs1 };
        let rs3_val = if neg_c { rs3 ^ 0x8000000000000000 } else { rs3 };

        // Clear softfloat flags and set rounding mode before operation
        let rounding_mode = if rm == 7 {
            get_frm() as u8 // Dynamic rounding mode from FCSR
        } else {
            rm as u8 // Static rounding mode from instruction
        };
        unsafe {
            softfloat_exceptionFlags_write_helper(0);
            softfloat_roundingMode_write_helper(rounding_mode);
        };

        let f64_rs1 = float64_t { v: rs1_val };
        let f64_rs2 = float64_t { v: rs2 };
        let f64_rs3 = float64_t { v: rs3_val };

        let result = unsafe { f64_mulAdd(f64_rs1, f64_rs2, f64_rs3) };

        // Update our FCSR with softfloat's flags (accumulate with existing flags)
        let softfloat_flags = unsafe { softfloat_exceptionFlags_read_helper() };
        set_fflags(existing_fflags | softfloat_flags as u32);

        // For R4-type instructions, rd is in bits 11-7
        let rd = (insn >> 7) & 0x1f;
        set_fp_reg(rd as usize, result.v);
    } else {
        panic!("Unsupported precision for fmadd: {}", precision);
    }

    mret()
}

/// # Safety
/// This function is unsafe because it performs raw pointer dereferencing and might cause undefined behavior
/// if given an invalid instruction or memory address.
/// Caller must ensure that emulation context, memory layout, and all invariants required by floating-point
/// loads and stores are respected.
pub unsafe fn emulate_fp_load_store(insn: u32, _mepc: usize) -> ! {
    let opcode = insn & 0x7f;
    let funct3 = (insn >> 12) & 0x7;
    let rs1 = (insn >> 15) & 0x1f;

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

    match (opcode, funct3) {
        (0x07, 2) => {
            // flw - floating point load word (32-bit)
            // Check 4-byte alignment
            if !addr.is_multiple_of(4) {
                panic!("Address misaligned: {:#010x}", addr);
            }

            if addr >= KERNEL_START_ADDR as u32 {
                panic!("FP load operation on kernel memory: {:#010x}", addr);
            }

            // Load 32-bit value from memory
            let value = unsafe { (addr as *const u32).read_volatile() };

            // Store in floating point register (as 32-bit in 64-bit register)
            set_f32_rd(insn, value);
        }
        (0x07, 3) => {
            // fld - floating point load double (64-bit)
            // Check 8-byte alignment
            if !addr.is_multiple_of(8) {
                panic!("Address misaligned: {:#010x}", addr);
            }

            if addr >= KERNEL_START_ADDR as u32 {
                panic!("FP load operation on kernel memory: {:#010x}", addr);
            }

            // Load 64-bit value from memory
            let value = unsafe { (addr as *const u64).read_volatile() };

            // Store in floating point register
            set_f64_rd(insn, value);
        }
        (0x27, 2) => {
            // fsw - floating point store word (32-bit)
            // Check 4-byte alignment
            if !addr.is_multiple_of(4) {
                panic!("Address misaligned: {:#010x}", addr);
            }

            if addr >= KERNEL_START_ADDR as u32 {
                panic!("FP store operation on kernel memory: {:#010x}", addr);
            }

            // Get 32-bit value from floating point register
            let value = get_f32_rs2(insn);

            // Store 32-bit value to memory
            unsafe {
                (addr as *mut u32).write_volatile(value);
            }
        }
        (0x27, 3) => {
            // fsd - floating point store double (64-bit)
            // Check 8-byte alignment
            if !addr.is_multiple_of(8) {
                panic!("Address misaligned: {:#010x}", addr);
            }

            if addr >= KERNEL_START_ADDR as u32 {
                panic!("FP store operation on kernel memory: {:#010x}", addr);
            }

            // Get 64-bit value from floating point register
            let value = get_f64_rs2(insn);

            // Store 64-bit value to memory
            unsafe {
                (addr as *mut u64).write_volatile(value);
            }
        }
        _ => {
            panic!("Unsupported FP load/store funct3: {}", funct3);
        }
    }

    mret()
}
