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
use crate::{atomics::emulate_atomic_instruction, constants::MEPC_PTR, mret};

/// # Safety
/// This function must only be called in contexts where it is safe to read
/// from the address stored in MEPC_PTR, which should point to the location
/// of the illegal instruction. It is marked unsafe and uses raw pointer access.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn trap_handler() -> ! {
    // Get the saved PC from MEPC (where the illegal instruction occurred)
    let mepc = unsafe { MEPC_PTR.read_volatile() };
    // Read the instruction as a u16 first
    let instruction_h = unsafe { (mepc as *const u16).read_volatile() };
    if instruction_h & 0x3 != 0x3 {
        panic!("Illegal instruction: {instruction_h:x}");
    } else if mepc % 4 != 0 {
        panic!("Instruction not aligned: {instruction_h:x}");
    }

    let instruction_l = unsafe { (mepc as *const u16).add(1).read_volatile() };
    let instruction = (instruction_l as u32) << 16 | instruction_h as u32;

    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    let funct7 = (instruction & 0xfe000000) >> 25;
    // Check for RV32A atomic memory operations
    if opcode == 0x2f {
        emulate_atomic_instruction(rd, rs1, rs2, funct3, funct7);
    }

    // Check for floating point operations (opcode 0x43/0x47/0x4b/0x4f) - R4-type instructions
    // These should call emulate_fmadd directly, not go through funct7 dispatch
    if opcode == 0x43 || opcode == 0x47 || opcode == 0x4b || opcode == 0x4f {
        crate::softfloat::emulate_fmadd(instruction);
    }

    // Check for floating point operations (opcode 0x53)
    if opcode == 0x53 {
        unsafe {
            crate::softfloat::emulate_fp_instruction(instruction, mepc);
        }
    }

    // Check for floating point load/store operations (opcode 0x07 = Load-FP, 0x27 = Store-FP)
    if opcode == 0x07 || opcode == 0x27 {
        unsafe {
            crate::softfloat::emulate_fp_load_store(instruction, mepc);
        }
    }

    // Check for SYSTEM operations (opcode 0x73)
    if opcode == 0x73 {
        // This is a CSR instruction (funct3 != 000)
        if funct3 != 0x0 {
            unsafe {
                emulate_csr_instruction(instruction, mepc);
            }
        }
    }

    // Emulate fence, fence.i, fence rw,rw and fence ow,ow - null-op
    if instruction == 0x0ff0000f
        || instruction == 0x0000100f
        || instruction == 0x0330000f
        || instruction == 0x0550000f
    {
        mret()
    }
    // Log the illegal instruction event and terminate
    panic!(
        "Illegal instruction or trap at PC: {:#010x}, instr: {:#010x}",
        mepc, instruction
    );
}

// CSR (Control and Status Register) emulation
unsafe fn emulate_csr_instruction(insn: u32, _mepc: usize) -> ! {
    let funct3 = (insn >> 12) & 0x7;
    let rd = (insn >> 7) & 0x1f;
    let rs1 = (insn >> 15) & 0x1f;
    let csr_addr = (insn >> 20) & 0xfff;

    // Handle floating point CSR operations
    match csr_addr {
        0x001 => {
            crate::softfloat::handle_float_csr_exception(funct3, rs1, rd);
        }
        0x002 => {
            crate::softfloat::handle_float_csr_frm(funct3, rs1, rd);
        }
        0x003 => {
            crate::softfloat::handle_float_csr_fcsr(funct3, rs1, rd);
        }
        _ => {
            panic!("Unsupported CSR address: {:#03x}", csr_addr);
        }
    }

    mret()
}
