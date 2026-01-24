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
use crate::{constants::KERNEL_START_ADDR, get_ureg, mret, set_ureg};

static mut ILRSC: u32 = 0;
static mut ILRSC_SET: u32 = 0;

fn get_ilrsc() -> u32 {
    unsafe { ILRSC }
}

fn set_ilrsc(value: u32) {
    unsafe {
        ILRSC = value;
    }
}

fn get_ilrsc_set() -> u32 {
    unsafe { ILRSC_SET }
}

fn set_ilrsc_set(value: u32) {
    unsafe {
        ILRSC_SET = value;
    }
}

// Invalidate LR/SC reservation (call this when other memory operations occur)
#[allow(dead_code)]
fn invalidate_lrsc_reservation() {
    set_ilrsc_set(0);
}

/// Macro to handle common atomic memory operation pattern
macro_rules! atomic_op {
    ($rd:expr, $rs1:expr, $rs2:expr, $op:expr) => {{
        // Get address from rs1 register
        let addr = get_ureg($rs1 as usize);

        // Check alignment (4-byte aligned for 32-bit words)
        if !addr.is_multiple_of(4) {
            panic!("Address misaligned: {:#010x}", addr);
        }

        if addr >= KERNEL_START_ADDR as u32 {
            panic!("Atomic operation on kernel memory: {:#010x}", addr);
        }

        // Read current value from memory
        let current_value = unsafe { (addr as *const u32).read_volatile() };

        // Get value from rs2 register
        let rs2_value = get_ureg($rs2 as usize);

        // Perform the operation
        let new_value = $op(current_value, rs2_value);
        unsafe {
            (addr as *mut u32).write_volatile(new_value);
        }

        // Write original value to rd register
        set_ureg($rd as usize, current_value);

        mret()
    }};
}

/// Macro to handle common memory address validation and read
macro_rules! validate_and_read {
    ($rs1:expr) => {{
        // Get address from rs1 register
        let addr = get_ureg($rs1 as usize);

        // Check alignment (4-byte aligned for 32-bit words)
        if !addr.is_multiple_of(4) {
            panic!("Address misaligned: {:#010x}", addr);
        }

        if addr >= KERNEL_START_ADDR as u32 {
            panic!("Atomic operation on kernel memory: {:#010x}", addr);
        }

        // Read value from memory
        let value = unsafe { (addr as *const u32).read_volatile() };

        (addr, value)
    }};
}

// lr.w - Load Reserved Word
fn emulate_lr_w(rd: u32, rs1: u32) -> ! {
    let (addr, value) = validate_and_read!(rs1);

    // Set reservation: store the reserved address in ILRSC shadow register
    set_ilrsc(addr);

    // Set reservation state: store 1 (valid) in ILRSC_SET shadow register
    set_ilrsc_set(1);

    // Write loaded value to rd register
    set_ureg(rd as usize, value);

    mret()
}

// sc.w - Store Conditional Word
fn emulate_sc_w(rd: u32, rs1: u32, rs2: u32) -> ! {
    let (addr, _) = validate_and_read!(rs1);

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
    } else {
        // Reservation is invalid - clear reservation, don't store, write 1 to rd (failure)
        set_ilrsc_set(0);
        set_ureg(rd as usize, 1);
    }

    mret()
}

pub fn emulate_atomic_instruction(rd: u32, rs1: u32, rs2: u32, funct3: u32, funct7: u32) -> ! {
    let funct5 = (funct7 & 0b1111100) >> 2;
    let _aq = (funct7 & 0b0000010) >> 1;
    // acquire access
    let _rl = funct7 & 0b0000001;
    // release access

    match (funct3, funct5) {
        (0x2, 0x00) => {
            // amoadd.w - atomic memory operation: add word
            atomic_op!(rd, rs1, rs2, |current: u32, add: u32| current
                .wrapping_add(add))
        }
        (0x2, 0x01) => {
            // amoswap.w - atomic memory operation: swap word
            atomic_op!(rd, rs1, rs2, |_current: u32, swap: u32| swap)
        }
        (0x2, 0x04) => {
            // amoxor.w - atomic memory operation: XOR word
            atomic_op!(rd, rs1, rs2, |current: u32, xor: u32| current ^ xor)
        }
        (0x2, 0x08) => {
            // amoor.w - atomic memory operation: OR word
            atomic_op!(rd, rs1, rs2, |current: u32, or: u32| current | or)
        }
        (0x2, 0x0c) => {
            // amoand.w - atomic memory operation: AND word
            atomic_op!(rd, rs1, rs2, |current: u32, and: u32| current & and)
        }
        (0x2, 0x10) => {
            // amomin.w - atomic memory operation: minimum word (signed)
            atomic_op!(rd, rs1, rs2, |current: u32, compare: u32| {
                let current_signed = current as i32;
                let compare_signed = compare as i32;
                if current_signed < compare_signed {
                    current
                } else {
                    compare
                }
            })
        }
        (0x2, 0x14) => {
            // amomax.w - atomic memory operation: maximum word (signed)
            atomic_op!(rd, rs1, rs2, |current: u32, compare: u32| {
                let current_signed = current as i32;
                let compare_signed = compare as i32;
                if current_signed > compare_signed {
                    current
                } else {
                    compare
                }
            })
        }
        (0x2, 0x18) => {
            // amominu.w - atomic memory operation: minimum word (unsigned)
            atomic_op!(rd, rs1, rs2, |current: u32, compare: u32| {
                if current < compare { current } else { compare }
            })
        }
        (0x2, 0x1c) => {
            // amomaxu.w - atomic memory operation: maximum word (unsigned)
            atomic_op!(rd, rs1, rs2, |current: u32, compare: u32| {
                if current > compare { current } else { compare }
            })
        }
        (0x2, 0x02) => emulate_lr_w(rd, rs1),
        (0x2, 0x03) => emulate_sc_w(rd, rs1, rs2),
        _ => {
            panic!(
                "Unimplemented atomic operation: funct3={:#x}, funct5={:#x}",
                funct3, funct5
            );
        }
    }
}
