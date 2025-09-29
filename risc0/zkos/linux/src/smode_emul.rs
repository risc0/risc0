use crate::{
    constants::*,
    host_calls::{host_get_cycle, host_terminate, host_write},
    kernel::{
        DEBUG_ENABLED, get_ureg, get_vm_machine_mode, mret, print, set_ureg, set_vm_machine_mode,
    },
};
use no_std_strings::{str_format, str256};

// Trap routine for invalid VM mode access
fn trap_invalid_vm_mode(csr_name: &str) -> ! {
    kpanic!(
        "CSR {} access not allowed in current VM mode {}",
        csr_name,
        get_vm_machine_mode()
    );
}

const SBI_EXT_BASE: u32 = 0x10;
const SBI_EXT_DBCN: u32 = 0x4442434E;

// SBI constants
const SBI_ECALL_VERSION_MAJOR: u32 = 3;
const SBI_ECALL_VERSION_MINOR: u32 = 0;
const SBI_OPENSBI_IMPID: u32 = 1;

const SBI_SPEC_VERSION_MAJOR_OFFSET: u32 = 24;
const SBI_SPEC_VERSION_MAJOR_MASK: u32 = 0x7f;

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
const SBI_EXT_DBCN_CONSOLE_PUTCHAR: u32 = 0x2;

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
pub fn start_vmlinux() -> ! {
    debug_print!("Warning: No command line arguments provided, assuming vmlinux");
    // Copy DTB_DATA to USER_STACK_ADDR
    unsafe {
        core::ptr::copy_nonoverlapping(
            DTB_DATA.as_ptr(),
            USER_STACK_ADDR as *mut u8,
            DTB_DATA.len(),
        );
    }
    set_ureg(REG_A0, 0);
    // hartid
    set_ureg(REG_A1, USER_STACK_ADDR as u32);
    print("starting vmlinux");
    let user_start_addr = unsafe { USER_START_PTR.read_volatile() } - 4;
    set_vm_machine_mode(VM_MACHINE_MODE_EMULATED_S_MODE);
    unsafe {
        MEPC_PTR.write_volatile(user_start_addr);
    }
    mret()
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

pub fn get_sepc() -> u32 {
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

pub fn handle_umode_ecall() -> ! {
    let mepc = unsafe { MEPC_PTR.read_volatile() };
    debug_print!("handle_umode_ecall from PC: {:#010x}", mepc);
    set_sepc(mepc as u32);
    set_scause(8);
    set_stval(0);
    unsafe { *MEPC_PTR = get_stvec() as usize - 4 };
    set_vm_machine_mode(VM_MACHINE_MODE_EMULATED_S_MODE);
    mret();
}

pub fn handle_smode_ecall() -> ! {
    let nr = get_ureg(REG_A7);
    match nr {
        SBI_EXT_DBCN => {
            // SBI_EXT_CONSOLE
            match get_ureg(REG_A6) {
                SBI_EXT_DBCN_CONSOLE_WRITE => {
                    // print the ascii character
                    let msg_ptr = get_ureg(REG_A1) as *const u8;
                    let msg =
                        unsafe { core::slice::from_raw_parts(msg_ptr, get_ureg(REG_A0) as usize) };
                    host_write(1, msg.as_ptr(), msg.len());
                }
                SBI_EXT_DBCN_CONSOLE_READ => {
                    set_ureg(REG_A0, 0);
                    set_ureg(REG_A1, 0);
                }
                SBI_EXT_DBCN_CONSOLE_PUTCHAR => {
                    kpanic!("SBI_EXT_DBCN_CONSOLE_PUTCHAR not implemented");
                }
                _ => {
                    kpanic!("unknown sbi_ext_dbcn function: {}", get_ureg(REG_A6));
                }
            }
        }
        SBI_EXT_BASE => {
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
        }
        _ => {
            kpanic!("unknown sbi_ext function: {}", nr);
        }
    }
    mret()
}

pub fn handle_timeh(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("timeh");
    }

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
                debug_print!("Warning: Attempted to write immediate to read-only timeh CSR");
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

pub fn handle_time(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("time");
    }

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

pub fn handle_senvcfg(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("senvcfg");
    }

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

pub fn handle_scause(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("scause");
    }

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

pub fn handle_stval(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("stval");
    }

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

pub fn handle_sepc(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sepc");
    }

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

pub fn handle_sstatus(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sstatus");
    }

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

pub fn handle_scounteren(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("scounteren");
    }

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

pub fn handle_sip(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sip");
    }

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

pub fn handle_sie(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sie");
    }

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

pub fn handle_sdeleg(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sdeleg");
    }

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

pub fn handle_sscratch(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("sscratch");
    }

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

pub fn handle_stvec(funct3: u32, rd: u32, rs1: u32) {
    // Check if we're in emulated S-mode
    if get_vm_machine_mode() != VM_MACHINE_MODE_EMULATED_S_MODE {
        trap_invalid_vm_mode("stvec");
    }

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
