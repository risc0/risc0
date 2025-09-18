#![allow(dead_code)]

pub const REG_SP: usize = 2;
pub const REG_A0: usize = 10;
pub const REG_A1: usize = 11;
pub const REG_A2: usize = 12;
pub const REG_A3: usize = 13;
pub const REG_A4: usize = 14;
pub const REG_A5: usize = 15;
pub const REG_A6: usize = 16;
pub const REG_A7: usize = 17;

// Floating point register pub constants
pub const NUM_FP_REGS: usize = 32;
#[allow(dead_code)]
pub const FP_REG_SIZE: usize = 8; // 64-bit registers
#[allow(dead_code)]
pub const FP_REGS_SIZE: usize = NUM_FP_REGS * FP_REG_SIZE; // 256 bytes total

pub const USER_REGS_PTR: *mut u32 = 0xffff_0080 as *mut u32;
pub const MEPC_PTR: *mut usize = 0xffff_0200 as *mut usize;
// Floating point register storage area (32 x 64-bit registers = 256 bytes)
pub const FP_REGS_PTR: *mut u64 = 0xffff_4000 as *mut u64;
// Floating point control and status register (FCSR) storage
#[allow(dead_code)]
pub const FCSR_PTR: *mut u32 = 0xffff_4100 as *mut u32;
pub const USER_START_PTR: *const usize = 0x0001_0000 as *const usize;
pub const USER_STACK_ADDR: usize = 0xbf00_0000;
pub const USER_STACK_PTR: *const usize = USER_STACK_ADDR as *const usize;
pub const USER_FIXUP_ADDR: usize = 0xbfff_0000;
pub const USER_FIXUP_PTR: *mut u32 = USER_FIXUP_ADDR as *mut u32;
#[allow(dead_code)]
pub const USER_STACK_SIZE: usize = 2 * 1024 * 1024;
pub const USER_HEAP_START_ADDR: usize = 0x0800_0000; // TODO: figure out where data ends in user program
#[allow(dead_code)]
pub const USER_HEAP_START_PTR: *const u8 = USER_HEAP_START_ADDR as *const u8;
pub const USER_HEAP_SIZE: usize = 0x40000000;
#[allow(dead_code)]
pub const USER_HEAP_END_ADDR: usize = USER_HEAP_START_ADDR + USER_HEAP_SIZE;
#[allow(dead_code)]
pub const USER_PHENT_SIZE: usize = 32; // ELF32_Phdr size in bytes

pub const PAGE_SIZE: usize = 4096;
// pub const AT_VECTOR_SIZE_BASE: usize = 20;
// pub const AT_VECTOR_SIZE_ARCH: usize = 7;
// pub const AT_VECTOR_SIZE: usize = 2 * (AT_VECTOR_SIZE_ARCH + AT_VECTOR_SIZE_BASE + 1);
pub const ASCII_TABLE_PTR: *const u8 = 0xbf00_0200 as *const u8;

/// Program header table address (stored in memory)
#[allow(dead_code)]
pub const USER_PHDR_ADDR_PTR: *const usize = 0xffff_3000 as *const usize;
/// Program header count address (stored in memory)
#[allow(dead_code)]
pub const USER_PHDR_NUM_ADDR_PTR: *const usize = 0xffff_3008 as *const usize;

// Shadow register storage area for supervisor CSRs (starting at 0xffff_5000)
pub const SHADOW_REGS_PTR: *mut u32 = 0xffff_5000 as *mut u32;

// Supervisor CSR offsets within shadow register area
pub const STVEC_OFFSET: usize = 0; // Supervisor trap vector base address
pub const SSCRATCH_OFFSET: usize = 1; // Supervisor scratch register
pub const SDELEG_OFFSET: usize = 2; // Supervisor delegation register
pub const SIE_OFFSET: usize = 3; // Supervisor interrupt enable
pub const SIP_OFFSET: usize = 4; // Supervisor interrupt pending
pub const SCOUNTEREN_OFFSET: usize = 5; // Supervisor counter enable
pub const SSTATUS_OFFSET: usize = 6; // Supervisor status register
pub const SEPC_OFFSET: usize = 7; // Supervisor exception program counter
pub const STVAL_OFFSET: usize = 8; // Supervisor trap value
pub const SCAUSE_OFFSET: usize = 9; // Supervisor cause register
pub const SENVCFG_OFFSET: usize = 10; // Supervisor environment configuration
pub const ILRSC_OFFSET: usize = 11; // Instruction LR/SC register
pub const ILRSC_SET_OFFSET: usize = 12; // Instruction LR/SC set register
pub const VM_MACHINE_MODE: usize = 13; // 0 = linux abi, 1 = emulated s-mode 2 = emulated u-mode
pub const MEPC_FIXUP_OFFSET: usize = 14; // MEPC fixup offset
pub const VM_MACHINE_MODE_LINUX_ABI: u32 = 0;
pub const VM_MACHINE_MODE_EMULATED_S_MODE: u32 = 1;
pub const VM_MACHINE_MODE_EMULATED_U_MODE: u32 = 2;

// Kernel heap constants
// Kernel stack is at 0xfff00000, heap is 16MB below it
pub const KERNEL_HEAP_START_ADDR: usize = 0xfef00000; // 16MB below kernel stack
pub const KERNEL_HEAP_SIZE: usize = 1024 * 1024; // 1MB heap
pub const KERNEL_HEAP_END_ADDR: usize = KERNEL_HEAP_START_ADDR + KERNEL_HEAP_SIZE;
