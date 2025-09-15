use crate::constants::*;
use crate::host_calls::host_terminate;
use crate::kernel::{DEBUG_ENABLED, print};
use crate::kernel::{get_ureg, mret, set_ureg};
use no_std_strings::{str_format, str256};

// XXX SECURITY we should probably make the memory functions use the trampoline instead because we're in M-mode
pub fn emulate_compressed_instruction(mepc: usize, inst: u16) -> ! {
    debug_print!("Emulating compressed instruction at PC: {:#010x}", mepc);
    debug_print!("Instruction: {:#010x}", inst);
    let opcode = inst & 0x3;
    let funct3 = (inst >> 13) & 0x7;
    match opcode {
        0 => {
            match funct3 {
                0 => {
                    // c.addi4spn
                    let rd = (((inst >> 2) & 0x7) + 8) as usize;
                    // nzuimm[5:4|9:6|2|3] = inst[12:11|10:7|6|5]
                    let nzuimm = (((inst >> 1) & 0x3c0) // nzuimm[9:6]
                        | ((inst >> 7) & 0x30) // nzuimm[5:4]
                        | ((inst >> 2) & 0x8) // nzuimm[3]
                        | ((inst >> 4) & 0x4)) as u32; // nzuimm[2]
                    if nzuimm == 0 {
                        kpanic!("c.addi4spn: nzuimm cannot be zero");
                    }
                    let sp_value = get_ureg(2); // x2 is stack pointer
                    let result = sp_value.wrapping_add(nzuimm);
                    set_ureg(rd, result);
                    debug_print!(
                        "c.addi4spn: x{} = sp({:#010x}) + {:#x} = {:#010x}",
                        rd,
                        sp_value,
                        nzuimm,
                        result
                    );
                    // Increment MEPC by 2 (compressed instruction size)

                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                2 => {
                    // c.lw
                    // Expands to lw rd, offset(rs1), where rd=rd'+8 and rs1=rs1'+8.
                    let rd = (((inst >> 2) & 0x7) + 8) as usize;
                    let rs1 = (((inst >> 7) & 0x7) + 8) as usize;
                    // offset[5:3|2|6] = inst[12:10|6|5]
                    let offset = (((inst << 1) & 0x40) // imm[6]
                        | ((inst >> 7) & 0x38) // imm[5:3]
                        | ((inst >> 4) & 0x4)) as u32; // imm[2]
                    let rs1_value = get_ureg(rs1);
                    let addr = rs1_value.wrapping_add(offset);
                    debug_print!(
                        "c.lw: x{} = mem[x{}({:#010x}) + {:#x} = {:#010x}]",
                        rd,
                        rs1,
                        rs1_value,
                        offset,
                        addr
                    );
                    // Direct memory access - read 32-bit value
                    let value = unsafe { (addr as *const u32).read_volatile() };
                    set_ureg(rd, value);
                    debug_print!("c.lw: loaded value {:#010x}", value);
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                6 => {
                    // c.sw
                    // Expands to sw rs2, offset(rs1), where rs2=rs2'+8 and rs1=rs1'+8.
                    let rs2 = (((inst >> 2) & 0x7) + 8) as usize;
                    let rs1 = (((inst >> 7) & 0x7) + 8) as usize;
                    // offset[5:3|2|6] = inst[12:10|6|5]
                    let offset = (((inst << 1) & 0x40) // imm[6]
                        | ((inst >> 7) & 0x38) // imm[5:3]
                        | ((inst >> 4) & 0x4)) as u32; // imm[2]
                    let rs1_value = get_ureg(rs1);
                    let rs2_value = get_ureg(rs2);
                    let addr = rs1_value.wrapping_add(offset);
                    debug_print!(
                        "c.sw: mem[x{}({:#010x}) + {:#x} = {:#010x}] = x{}({:#010x})",
                        rs1,
                        rs1_value,
                        offset,
                        addr,
                        rs2,
                        rs2_value
                    );
                    // Direct memory access - write 32-bit value
                    unsafe { (addr as *mut u32).write_volatile(rs2_value) };
                    debug_print!("c.sw: stored value {:#010x}", rs2_value);
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                _ => {
                    kpanic!(
                        "Unsupported compressed instruction funct3: {} at PC: {:#010x}",
                        funct3,
                        mepc
                    );
                }
            }
        }
        1 => {
            // Quadrant 1
            match funct3 {
                0x0 => {
                    // c.addi
                    // Expands to addi rd, rd, nzimm.
                    let rd = ((inst >> 7) & 0x1f) as usize;
                    // nzimm[5|4:0] = inst[12|6:2]
                    let nzimm_raw = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                    // Sign-extended.
                    let nzimm = match (nzimm_raw & 0x20) == 0 {
                        true => nzimm_raw as u32,
                        false => (0xc0 | nzimm_raw) as i8 as i32 as u32,
                    };
                    if rd != 0 {
                        let rd_value = get_ureg(rd);
                        let result = rd_value.wrapping_add(nzimm);
                        set_ureg(rd, result);
                        debug_print!(
                            "c.addi: x{} = x{}({:#010x}) + {:#x} = {:#010x}",
                            rd,
                            rd,
                            rd_value,
                            nzimm,
                            result
                        );
                    } else {
                        debug_print!("c.addi: x0 (no-op)");
                    }
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                0x1 => {
                    // c.jal
                    // Expands to jal x1, offset.
                    // offset[11|4|9:8|10|6|7|3:1|5] = inst[12|11|10:9|8|7|6|5:3|2]
                    let offset_raw = ((inst >> 1) & 0x800) // offset[11]
                        | ((inst << 2) & 0x400) // offset[10]
                        | ((inst >> 1) & 0x300) // offset[9:8]
                        | ((inst << 1) & 0x80) // offset[7]
                        | ((inst >> 1) & 0x40) // offset[6]
                        | ((inst << 3) & 0x20) // offset[5]
                        | ((inst >> 7) & 0x10) // offset[4]
                        | ((inst >> 2) & 0xe); // offset[3:1]

                    // Sign-extended.
                    let offset = match (offset_raw & 0x800) == 0 {
                        true => offset_raw as u32,
                        false => (0xf000 | offset_raw) as i16 as i32 as u32,
                    };
                    let target_pc = mepc.wrapping_add(offset as usize);
                    let return_addr = mepc + 2; // Return address is PC + 2

                    debug_print!(
                        "c.jal: PC = {:#010x} + {:#x} = {:#010x}, return = {:#010x}",
                        mepc,
                        offset,
                        target_pc,
                        return_addr
                    );

                    // Save return address in x1
                    set_ureg(1, return_addr as u32);
                    // Update MEPC to the target PC (circuit bug: need to subtract 4)
                    unsafe { MEPC_PTR.write_volatile(target_pc - 4) };
                    mret()
                }
                0x2 => {
                    // c.li
                    // Expands to addi rd, x0, imm.
                    let rd = ((inst >> 7) & 0x1f) as usize;
                    // imm[5|4:0] = inst[12|6:2]
                    let imm_raw = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                    // Sign-extended.
                    let imm = match (imm_raw & 0x20) == 0 {
                        true => imm_raw as u32,
                        false => (0xc0 | imm_raw) as i8 as i32 as u32,
                    };
                    if rd != 0 {
                        set_ureg(rd, imm);
                        debug_print!("c.li: x{} = {:#x}", rd, imm);
                    } else {
                        debug_print!("c.li: x0 (no-op)");
                    }
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                0x3 => {
                    let rd = (inst >> 7) & 0x1f;
                    match rd {
                        0 => {
                            // No-op case
                            debug_print!("c.addi16sp/c.lui: rd=0 (no-op)");
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        2 => {
                            // c.addi16sp
                            // Expands to addi x2, x2, nzimm
                            // nzimm[9|4|6|8:7|5] = inst[12|6|5|4:3|2]
                            let nzimm_raw = ((inst >> 3) & 0x200) // nzimm[9]
                                | ((inst >> 2) & 0x10) // nzimm[4]
                                | ((inst << 1) & 0x40) // nzimm[6]
                                | ((inst << 4) & 0x180) // nzimm[8:7]
                                | ((inst << 3) & 0x20); // nzimm[5]
                            // Sign-extended.
                            let nzimm = match (nzimm_raw & 0x200) == 0 {
                                true => nzimm_raw as u32,
                                false => (0xfc00 | nzimm_raw) as i16 as i32 as u32,
                            };
                            if nzimm != 0 {
                                let sp_value = get_ureg(2); // x2 is stack pointer
                                let result = sp_value.wrapping_add(nzimm);
                                set_ureg(2, result);
                                debug_print!(
                                    "c.addi16sp: sp = sp({:#010x}) + {:#x} = {:#010x}",
                                    sp_value,
                                    nzimm,
                                    result
                                );
                            } else {
                                debug_print!("c.addi16sp: nzimm=0 (no-op)");
                            }
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        _ => {
                            // c.lui
                            // Expands to lui rd, nzimm.
                            // nzimm[17|16:12] = inst[12|6:2]
                            let nzimm_raw =
                                ((inst as u32) << 5) & 0x20000 | ((inst as u32) << 10) & 0x1f000;
                            // Sign-extended.
                            let nzimm = match (nzimm_raw & 0x20000) == 0 {
                                true => nzimm_raw,
                                false => (0xfffc0000 | nzimm_raw) as i32 as u32,
                            };
                            if nzimm != 0 {
                                set_ureg(rd as usize, nzimm);
                                debug_print!("c.lui: x{} = {:#x}", rd, nzimm);
                            } else {
                                debug_print!("c.lui: nzimm=0 (no-op)");
                            }
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                    }
                }
                0x4 => {
                    let funct2 = (inst >> 10) & 0x3;
                    match funct2 {
                        0x0 => {
                            // c.srli
                            // Expands to srli rd, rd, shamt, where rd=rd'+8.
                            let rd = (((inst >> 7) & 0b111) + 8) as usize;
                            // shamt[5|4:0] = inst[12|6:2]
                            let shamt = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                            let rd_value = get_ureg(rd);
                            let result = rd_value >> shamt;
                            set_ureg(rd, result);
                            debug_print!(
                                "c.srli: x{} = x{}({:#010x}) >> {} = {:#010x}",
                                rd,
                                rd,
                                rd_value,
                                shamt,
                                result
                            );
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        0x1 => {
                            // c.srai
                            // Expands to srai rd, rd, shamt, where rd=rd'+8.
                            let rd = (((inst >> 7) & 0b111) + 8) as usize;
                            // shamt[5|4:0] = inst[12|6:2]
                            let shamt = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                            let rd_value = get_ureg(rd);
                            let result = ((rd_value as i32) >> shamt) as u32;
                            set_ureg(rd, result);
                            debug_print!(
                                "c.srai: x{} = x{}({:#010x}) >> {} = {:#010x}",
                                rd,
                                rd,
                                rd_value,
                                shamt,
                                result
                            );
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        0x2 => {
                            // c.andi
                            // Expands to andi rd, rd, imm, where rd=rd'+8.
                            let rd = (((inst >> 7) & 0b111) + 8) as usize;
                            // imm[5|4:0] = inst[12|6:2]
                            let imm_raw = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                            // Sign-extended.
                            let imm = match (imm_raw & 0x20) == 0 {
                                true => imm_raw as u32,
                                false => (0xc0 | imm_raw) as i8 as i32 as u32,
                            };
                            let rd_value = get_ureg(rd);
                            let result = rd_value & imm;
                            set_ureg(rd, result);
                            debug_print!(
                                "c.andi: x{} = x{}({:#010x}) & {:#x} = {:#010x}",
                                rd,
                                rd,
                                rd_value,
                                imm,
                                result
                            );
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        0x3 => {
                            match ((inst >> 12) & 0b1, (inst >> 5) & 0b11) {
                                (0x0, 0x0) => {
                                    // c.sub
                                    // Expands to sub rd, rd, rs2, rd=rd'+8 and rs2=rs2'+8.
                                    let rd = (((inst >> 7) & 0b111) + 8) as usize;
                                    let rs2 = (((inst >> 2) & 0b111) + 8) as usize;
                                    let rd_value = get_ureg(rd);
                                    let rs2_value = get_ureg(rs2);
                                    let result = rd_value.wrapping_sub(rs2_value);
                                    set_ureg(rd, result);
                                    debug_print!(
                                        "c.sub: x{} = x{}({:#010x}) - x{}({:#010x}) = {:#010x}",
                                        rd,
                                        rd,
                                        rd_value,
                                        rs2,
                                        rs2_value,
                                        result
                                    );
                                    // Increment MEPC by 2 (compressed instruction size)
                                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                                    mret()
                                }
                                (0x0, 0x1) => {
                                    // c.xor
                                    // Expands to xor rd, rd, rs2, rd=rd'+8 and rs2=rs2'+8.
                                    let rd = (((inst >> 7) & 0b111) + 8) as usize;
                                    let rs2 = (((inst >> 2) & 0b111) + 8) as usize;
                                    let rd_value = get_ureg(rd);
                                    let rs2_value = get_ureg(rs2);
                                    let result = rd_value ^ rs2_value;
                                    set_ureg(rd, result);
                                    debug_print!(
                                        "c.xor: x{} = x{}({:#010x}) ^ x{}({:#010x}) = {:#010x}",
                                        rd,
                                        rd,
                                        rd_value,
                                        rs2,
                                        rs2_value,
                                        result
                                    );
                                    // Increment MEPC by 2 (compressed instruction size)
                                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                                    mret()
                                }
                                (0x0, 0x2) => {
                                    // c.or
                                    // Expands to or rd, rd, rs2, rd=rd'+8 and rs2=rs2'+8.
                                    let rd = (((inst >> 7) & 0b111) + 8) as usize;
                                    let rs2 = (((inst >> 2) & 0b111) + 8) as usize;
                                    let rd_value = get_ureg(rd);
                                    let rs2_value = get_ureg(rs2);
                                    let result = rd_value | rs2_value;
                                    set_ureg(rd, result);
                                    debug_print!(
                                        "c.or: x{} = x{}({:#010x}) | x{}({:#010x}) = {:#010x}",
                                        rd,
                                        rd,
                                        rd_value,
                                        rs2,
                                        rs2_value,
                                        result
                                    );
                                    // Increment MEPC by 2 (compressed instruction size)
                                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                                    mret()
                                }
                                (0x0, 0x3) => {
                                    // c.and
                                    // Expands to and rd, rd, rs2, rd=rd'+8 and rs2=rs2'+8.
                                    let rd = (((inst >> 7) & 0b111) + 8) as usize;
                                    let rs2 = (((inst >> 2) & 0b111) + 8) as usize;
                                    let rd_value = get_ureg(rd);
                                    let rs2_value = get_ureg(rs2);
                                    let result = rd_value & rs2_value;
                                    set_ureg(rd, result);
                                    debug_print!(
                                        "c.and: x{} = x{}({:#010x}) & x{}({:#010x}) = {:#010x}",
                                        rd,
                                        rd,
                                        rd_value,
                                        rs2,
                                        rs2_value,
                                        result
                                    );
                                    // Increment MEPC by 2 (compressed instruction size)
                                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                                    mret()
                                }
                                _ => {
                                    kpanic!(
                                        "Illegal compressed instruction: funct2=3, inst={:#06x} at PC: {:#010x}",
                                        inst,
                                        mepc
                                    );
                                }
                            }
                        }
                        _ => {
                            kpanic!(
                                "Illegal compressed instruction: funct2={} at PC: {:#010x}",
                                funct2,
                                mepc
                            );
                        }
                    }
                }
                0x5 => {
                    // c.j
                    // Expands to jal x0, offset.
                    // offset[11|4|9:8|10|6|7|3:1|5] = inst[12|11|10:9|8|7|6|5:3|2]
                    let offset_raw = ((inst >> 1) & 0x800) // offset[11]
                        | ((inst << 2) & 0x400) // offset[10]
                        | ((inst >> 1) & 0x300) // offset[9:8]
                        | ((inst << 1) & 0x80) // offset[7]
                        | ((inst >> 1) & 0x40) // offset[6]
                        | ((inst << 3) & 0x20) // offset[5]
                        | ((inst >> 7) & 0x10) // offset[4]
                        | ((inst >> 2) & 0xe); // offset[3:1]

                    // Sign-extended.
                    let offset = match (offset_raw & 0x800) == 0 {
                        true => offset_raw as u32,
                        false => (0xf000 | offset_raw) as i16 as i32 as u32,
                    };
                    let new_pc = mepc.wrapping_add(offset as usize);
                    debug_print!(
                        "c.j: PC = {:#010x} + {:#x} - 2 = {:#010x}",
                        mepc,
                        offset,
                        new_pc
                    );
                    // Update MEPC to the new PC (circuit bug: need to subtract 4)
                    unsafe { MEPC_PTR.write_volatile(new_pc - 4) };
                    mret()
                }
                0x6 => {
                    // c.beqz
                    // Expands to beq rs1, x0, offset, rs1=rs1'+8.
                    let rs1 = (((inst >> 7) & 0b111) + 8) as usize;
                    // offset[8|4:3|7:6|2:1|5] = inst[12|11:10|6:5|4:3|2]
                    let offset_raw = ((inst >> 4) & 0x100) // offset[8]
                        | ((inst << 1) & 0xc0) // offset[7:6]
                        | ((inst << 3) & 0x20) // offset[5]
                        | ((inst >> 7) & 0x18) // offset[4:3]
                        | ((inst >> 2) & 0x6); // offset[2:1]
                    // Sign-extended.
                    let offset = match (offset_raw & 0x100) == 0 {
                        true => offset_raw as u32,
                        false => (0xfe00 | offset_raw) as i16 as i32 as u32,
                    };
                    let rs1_value = get_ureg(rs1);
                    if rs1_value == 0 {
                        let new_pc = mepc.wrapping_add(offset as usize);
                        debug_print!(
                            "c.beqz: x{}({:#010x}) == 0, PC = {:#010x} + {:#x} - 2 = {:#010x}",
                            rs1,
                            rs1_value,
                            mepc,
                            offset,
                            new_pc
                        );
                        // Update MEPC to the new PC (circuit bug: need to subtract 4)
                        unsafe { MEPC_PTR.write_volatile(new_pc - 4) };
                        mret()
                    } else {
                        debug_print!("c.beqz: x{}({:#010x}) != 0, no branch", rs1, rs1_value);
                        // Increment MEPC by 2 (compressed instruction size)
                        unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                        mret()
                    }
                }
                0x7 => {
                    // c.bnez
                    // Expands to bne rs1, x0, offset, rs1=rs1'+8.
                    let rs1 = (((inst >> 7) & 0b111) + 8) as usize;
                    // offset[8|4:3|7:6|2:1|5] = inst[12|11:10|6:5|4:3|2]
                    let offset_raw = ((inst >> 4) & 0x100) // offset[8]
                        | ((inst << 1) & 0xc0) // offset[7:6]
                        | ((inst << 3) & 0x20) // offset[5]
                        | ((inst >> 7) & 0x18) // offset[4:3]
                        | ((inst >> 2) & 0x6); // offset[2:1]
                    // Sign-extended.
                    let offset = match (offset_raw & 0x100) == 0 {
                        true => offset_raw as u32,
                        false => (0xfe00 | offset_raw) as i16 as i32 as u32,
                    };
                    let rs1_value = get_ureg(rs1);
                    if rs1_value != 0 {
                        let new_pc = mepc.wrapping_add(offset as usize);
                        debug_print!(
                            "c.bnez: x{}({:#010x}) != 0, PC = {:#010x} + {:#x} - 2 = {:#010x}",
                            rs1,
                            rs1_value,
                            mepc,
                            offset,
                            new_pc
                        );
                        // Update MEPC to the new PC (circuit bug: need to subtract 4)
                        unsafe { MEPC_PTR.write_volatile(new_pc - 4) };
                        mret()
                    } else {
                        debug_print!("c.bnez: x{}({:#010x}) == 0, no branch", rs1, rs1_value);
                        // Increment MEPC by 2 (compressed instruction size)
                        unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                        mret()
                    }
                }
                _ => {
                    kpanic!(
                        "Unsupported compressed instruction funct3: {} at PC: {:#010x}",
                        funct3,
                        mepc
                    );
                }
            }
        }
        2 => {
            // Quadrant 2
            match funct3 {
                0x0 => {
                    // c.slli
                    // Expands to slli rd, rd, shamt.
                    let rd = ((inst >> 7) & 0x1f) as usize;
                    // shamt[5|4:0] = inst[12|6:2]
                    let shamt = ((inst >> 7) & 0x20) | ((inst >> 2) & 0x1f);
                    if rd != 0 {
                        let rd_value = get_ureg(rd);
                        let result = rd_value << shamt;
                        set_ureg(rd, result);
                        debug_print!(
                            "c.slli: x{} = x{}({:#010x}) << {} = {:#010x}",
                            rd,
                            rd,
                            rd_value,
                            shamt,
                            result
                        );
                    } else {
                        debug_print!("c.slli: x0 (no-op)");
                    }
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                0x2 => {
                    // c.lwsp
                    // Expands to lw rd, offset(x2).
                    let rd = ((inst >> 7) & 0x1f) as usize;
                    // offset[5|4:2|7:6] = inst[12|6:4|3:2]
                    let offset = (((inst << 4) & 0xc0) // offset[7:6]
                        | ((inst >> 7) & 0x20) // offset[5]
                        | ((inst >> 2) & 0x1c)) as u32; // offset[4:2]
                    let sp_value = get_ureg(2); // x2 is stack pointer
                    let addr = sp_value.wrapping_add(offset);
                    debug_print!(
                        "c.lwsp: x{} = mem[sp({:#010x}) + {:#x} = {:#010x}]",
                        rd,
                        sp_value,
                        offset,
                        addr
                    );
                    // Direct memory access - read 32-bit value
                    let value = unsafe { (addr as *const u32).read_volatile() };
                    set_ureg(rd, value);
                    debug_print!("c.lwsp: loaded value {:#010x}", value);
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                0x4 => {
                    match ((inst >> 12) & 0x1, (inst >> 2) & 0x1f) {
                        (0, 0) => {
                            // c.jr
                            // Expands to jalr x0, 0(rs1).
                            let rs1 = ((inst >> 7) & 0x1f) as usize;
                            if rs1 != 0 {
                                let rs1_value = get_ureg(rs1);
                                let new_pc = rs1_value as usize;
                                debug_print!(
                                    "c.jr: PC = x{}({:#010x}) - 2 = {:#010x}",
                                    rs1,
                                    rs1_value,
                                    new_pc
                                );
                                // Update MEPC to the new PC (circuit bug: need to subtract 4)
                                unsafe { MEPC_PTR.write_volatile(new_pc.wrapping_sub(4)) };
                                mret()
                            } else {
                                debug_print!("c.jr: x0 (illegal)");
                                kpanic!("c.jr: rs1 cannot be x0");
                            }
                        }
                        (0, _) => {
                            // c.mv
                            // Expands to add rd, x0, rs2.
                            let rd = ((inst >> 7) & 0x1f) as usize;
                            let rs2 = ((inst >> 2) & 0x1f) as usize;
                            if rs2 != 0 {
                                let rs2_value = get_ureg(rs2);
                                set_ureg(rd, rs2_value);
                                debug_print!("c.mv: x{} = x{}({:#010x})", rd, rs2, rs2_value);
                            } else {
                                debug_print!("c.mv: rs2=0 (illegal)");
                                kpanic!("c.mv: rs2 cannot be x0");
                            }
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        (1, 0) => {
                            let rd = ((inst >> 7) & 0x1f) as usize;
                            if rd == 0 {
                                // c.ebreak
                                // Expands to ebreak.
                                debug_print!("c.ebreak: Breakpoint instruction");
                                kpanic!("c.ebreak: Breakpoint instruction executed");
                            } else {
                                // c.jalr
                                // Expands to jalr x1, 0(rs1).
                                let rs1 = ((inst >> 7) & 0x1f) as usize;
                                let rs1_value = get_ureg(rs1);
                                let return_addr = mepc + 2; // Return address is PC + 2
                                let new_pc = rs1_value as usize;
                                set_ureg(1, return_addr as u32); // Save return address in x1
                                debug_print!(
                                    "c.jalr: x1 = {:#010x}, PC = x{}({:#010x}) - 2 = {:#010x}",
                                    return_addr,
                                    rs1,
                                    rs1_value,
                                    new_pc
                                );
                                // Update MEPC to the new PC (circuit bug: need to subtract 4)
                                unsafe { MEPC_PTR.write_volatile(new_pc.wrapping_sub(4)) };
                                mret()
                            }
                        }
                        (1, _) => {
                            // c.add
                            // Expands to add rd, rd, rs2.
                            let rd = ((inst >> 7) & 0x1f) as usize;
                            let rs2 = ((inst >> 2) & 0x1f) as usize;
                            if rs2 != 0 {
                                let rd_value = get_ureg(rd);
                                let rs2_value = get_ureg(rs2);
                                let result = rd_value.wrapping_add(rs2_value);
                                set_ureg(rd, result);
                                debug_print!(
                                    "c.add: x{} = x{}({:#010x}) + x{}({:#010x}) = {:#010x}",
                                    rd,
                                    rd,
                                    rd_value,
                                    rs2,
                                    rs2_value,
                                    result
                                );
                            } else {
                                debug_print!("c.add: rs2=0 (illegal)");
                                kpanic!("c.add: rs2 cannot be x0");
                            }
                            // Increment MEPC by 2 (compressed instruction size)
                            unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                            mret()
                        }
                        _ => {
                            kpanic!(
                                "Illegal compressed instruction: funct3=4, inst={:#06x} at PC: {:#010x}",
                                inst,
                                mepc
                            );
                        }
                    }
                }
                0x6 => {
                    // c.swsp
                    // Expands to sw rs2, offset(x2).
                    let rs2 = ((inst >> 2) & 0x1f) as usize;
                    // offset[5:2|7:6] = inst[12:9|8:7]
                    let offset = (((inst >> 1) & 0xc0) // offset[7:6]
                        | ((inst >> 7) & 0x3c)) as u32; // offset[5:2]
                    let sp_value = get_ureg(2); // x2 is stack pointer
                    let rs2_value = get_ureg(rs2);
                    let addr = sp_value.wrapping_add(offset);
                    debug_print!(
                        "c.swsp: mem[sp({:#010x}) + {:#x} = {:#010x}] = x{}({:#010x})",
                        sp_value,
                        offset,
                        addr,
                        rs2,
                        rs2_value
                    );
                    // Direct memory access - write 32-bit value
                    unsafe { (addr as *mut u32).write_volatile(rs2_value) };
                    debug_print!("c.swsp: stored value {:#010x}", rs2_value);
                    // Increment MEPC by 2 (compressed instruction size)
                    unsafe { MEPC_PTR.write_volatile(mepc - 2) };
                    mret()
                }
                _ => {
                    kpanic!(
                        "Unsupported compressed instruction funct3: {} at PC: {:#010x}",
                        funct3,
                        mepc
                    );
                }
            }
        }
        _ => {
            kpanic!(
                "Unsupported compressed instruction opcode: {} at PC: {:#010x}",
                opcode,
                mepc
            );
        }
    }
}

pub fn unaligned_instruction_execution(mepc: usize, instruction_h: u16) {
    // need to fixup
    let instruction_l = unsafe { (mepc as *const u16).add(1).read_volatile() };
    let instruction = (instruction_l as u32) << 16 | instruction_h as u32;
    kprint!("Fixing up unaligned instruction.. {:08x}", instruction);
    let opcode = instruction & 0x0000007f;
    let rd = (instruction & 0x00000f80) >> 7;
    let rs1 = (instruction & 0x000f8000) >> 15;
    let rs2 = (instruction & 0x01f00000) >> 20;
    let funct3 = (instruction & 0x00007000) >> 12;
    // Handle PC-relative instructions (AUIPC is now implemented)
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
        0x17 => {
            // AUIPC (Add Upper Immediate to PC)
            let imm = instruction & 0xfffff000; // 20-bit immediate in upper bits
            let result = mepc.wrapping_add(imm as usize);

            debug_print!(
                "AUIPC: PC={:#010x} + {:#x} = {:#010x} -> x{}",
                mepc,
                imm,
                result,
                rd
            );

            // Store result in destination register
            set_ureg(rd as usize, result as u32);
            // Set MEPC to next instruction
            unsafe { MEPC_PTR.write_volatile(mepc) };
            mret()
        }
        _ => {
            unsafe {
                // making trampoline
                set_mepc_fixup((mepc + 4) as u32);
                *USER_FIXUP_PTR = instruction;
                *USER_FIXUP_PTR.add(1) = 0xFFFF_FFFF;
                *MEPC_PTR = USER_FIXUP_ADDR - 4;
            }
            mret();
        }
    }
}

pub fn handle_mpec_fixup() -> ! {
    kprint!("Fixing up MEPC");
    let mepc_fixup = get_mepc_fixup();
    unsafe {
        *MEPC_PTR = (mepc_fixup - 4) as usize;
    }
    mret()
}

#[allow(dead_code)]
pub fn get_mepc_fixup() -> u32 {
    unsafe { *SHADOW_REGS_PTR.add(MEPC_FIXUP_OFFSET) }
}

#[allow(dead_code)]
fn set_mepc_fixup(value: u32) {
    unsafe {
        *SHADOW_REGS_PTR.add(MEPC_FIXUP_OFFSET) = value;
    }
}
