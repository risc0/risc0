use crate::constants::*;
use crate::host_calls::host_terminate;
use crate::kernel::{DEBUG_ENABLED, TRACE_ENABLED, print};
use crate::kernel::{get_ureg, mret, set_ureg};
use no_std_strings::{str_format, str256};

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

pub fn emulate_atomic_instruction(
    mepc: usize,
    rd: u32,
    rs1: u32,
    rs2: u32,
    funct3: u32,
    funct7: u32,
) {
    let funct5 = (funct7 & 0b1111100) >> 2;
    let _aq = (funct7 & 0b0000010) >> 1;
    // acquire access
    let _rl = funct7 & 0b0000001;
    // release access

    match (funct3, funct5) {
        (0x2, 0x00) => {
            // amoadd.w - atomic memory operation: add word
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x01) => {
            // amoswap.w - atomic memory operation: swap word
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x04) => {
            // amoxor.w - atomic memory operation: XOR word
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x08) => {
            // amoor.w - atomic memory operation: OR word
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x0c) => {
            // amoand.w - atomic memory operation: AND word
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x10) => {
            // amomin.w - atomic memory operation: minimum word (signed)
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x14) => {
            // amomax.w - atomic memory operation: maximum word (signed)
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x18) => {
            // amominu.w - atomic memory operation: minimum word (unsigned)
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x1c) => {
            // amomaxu.w - atomic memory operation: maximum word (unsigned)
            trace_print!(
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

            // Write original value to rd register (set_ureg handles x0 case)
            set_ureg(rd as usize, current_value);

            mret()
        }
        (0x2, 0x02) => {
            // lr.w - Load Reserved Word
            trace_print!(
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

            trace_print!(
                "lr.w: loaded {:#010x} from {:#010x}, set reservation",
                value,
                addr
            );

            mret()
        }
        (0x2, 0x03) => {
            // sc.w - Store Conditional Word
            trace_print!(
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

                trace_print!(
                    "sc.w: stored {:#010x} to {:#010x}, success",
                    store_value,
                    addr
                );
            } else {
                // Reservation is invalid - don't store, write 1 to rd (failure)
                set_ureg(rd as usize, 1);

                trace_print!(
                    "sc.w: reservation invalid (addr={:#010x}, reserved={:#010x}, valid={}), failure",
                    addr,
                    reserved_addr,
                    reservation_valid,
                );
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
